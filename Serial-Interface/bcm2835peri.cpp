#include "regops.h"
#include "bcm2835peri.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <stddef.h>

bcm2835peri::bcm2835peri()
{
    /* Open /dev/mem */
    int fd = -1;
    if (fd = open("/dev/mem", O_RDONLY) < 0 );
        throw -1;
    /* Create a map to physical memory */
    mapping = mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)BCM2835_PERI_BASE);
    if (mapping == MAP_FAILED)
        throw -2;
    /* Create pointers to physical addresses using the mapping */
    base_addr = (volatile uint32_t*)mapping;
    periaddrset();
}

bcm2835peri::bcm2835peri(void* mapping)
{
    /* Create the peripheral mappings */
    this->mapping = mapping;
    base_addr = (volatile uint32_t*)mapping;
    periaddrset();
}

bcm2835peri::bcm2835peri(uint32_t* base_addr)
{
    /* Create the peripheral mappings */
    this->mapping = (void*)base_addr;
    this->base_addr = base_addr;
    periaddrset();
}

inline void bcm2835peri::pinset(uint8_t pin, uint8_t state)
{
    state==HIGH ? SETBITA(GPIO_SET(pin), pin%32) : CLRBITA(GPIO_SET(pin), pin%32);    
}

inline void bcm2835peri::pinfsel(uint8_t pin, uint8_t func)
{
    SETREGA(GPIO_FSEL(pin), pin%10*3, func, BLEN_3);
}

void bcm2835peri::spiselect(uint8_t slave) 
{
    switch (slave)
    {
        case (0) :
            CLRBITA(SPI_CS, CS+1); CLRBITA(SPI_CS, CS+0);
            break;
        case (1) :
            CLRBITA(SPI_CS, CS+1); SETBITA(SPI_CS, CS+0);
            break;
        case (2) :
            SETBITA(SPI_CS, CS+1); CLRBITA(SPI_CS, CS+0);
            break;
    }
}

void bcm2835peri::spigpioselect(uint8_t slave)
{
    pinset(CE0, LOW);
    pinset(CE1, LOW);
    pinset(CE2, LOW);
    pinset(slave, HIGH);
}

void bcm2835peri::spitransfer(unsigned char *rbuf, unsigned char *tbuf, uint8_t size)
{
    // Clear FIFOs
    SETREGA(SPI_CS, CLEAR, 0x03, BLEN_2);
    // Set TA to 1
    SETBITA(SPI_CS, TA);
    // Poll TXD and RXD while write bytes to FIFOs
    int rcount = 0;
    int tcount = 0;
    volatile uint32_t *fifo = spi_addr + FIFO_OFF/4;
    while (rcount < size && tcount < size) 
    {
        while (READBITA(SPI_CS, TXD) && tcount < size)
        {
            *fifo = tbuf[tcount]; 
            tcount++;
        }
        while (READBITA(SPI_CS, RXD) && rcount < size)
        {
            rbuf[rcount] = *fifo; 
            rcount++;
        }
    }
    while (!READBITA(SPI_CS, DONE)) { }
    CLRBITA(SPI_CS, TA);
}

void bcm2835peri::spisend(unsigned char *tbuf, uint8_t size)
{
    // Clear FIFOs
    SETREGA(SPI_CS, CLEAR, 0x03, BLEN_2);
    // Set TA to 1
    SETBITA(SPI_CS, TA);
    // Poll TXD and RXD while write bytes to FIFOs
    int tcount = 0;
    char rbuf;
    volatile uint32_t *fifo = spi_addr + FIFO_OFF/4;
    while (tcount < size) 
    {
        while (READBITA(SPI_CS, TXD) && tcount < size)
        {
            *fifo = tbuf[tcount]; 
            tcount++;
        }
        while (READBITA(SPI_CS, RXD))
        {
            rbuf = *fifo; 
        }
    }
    while (!READBITA(SPI_CS, DONE)) { }
    CLRBITA(SPI_CS, TA);
}

void bcm2835peri::spirecieve(unsigned char *rbuf, uint8_t size)
{
    // Clear FIFOs
    SETREGA(SPI_CS, CLEAR, 0x03, BLEN_2);
    // Set TA to 1
    SETBITA(SPI_CS, TA);
    // Poll TXD and RXD while write bytes to FIFOs
    int rcount = 0;
    volatile uint32_t *fifo = spi_addr + FIFO_OFF/4;
    while (rcount < size) 
    {
        while (READBITA(SPI_CS, TXD))
        {
            *fifo = 0x01; 
        }
        while (READBITA(SPI_CS, RXD) && rcount < size)
        {
            rbuf[rcount] = *fifo; 
            rcount++;
        }
    }
    while (!READBITA(SPI_CS, DONE)) { }
    CLRBITA(SPI_CS, TA);
}

void bcm2835peri::periaddrset()
{
    spi_addr = this->base_addr + SPI_OFF/4;
    gpio_addr = this->base_addr + GPIO_OFF/4;
}

void bcm2835peri::spipinsconfig()
{
    volatile uint32_t *fsel_reg = gpio_addr + CE1_N/10;
    volatile uint32_t fsel_regVal = *fsel_reg;
    SETREGV(fsel_regVal, ((CE1_N%10)*3), 0x04, BLEN_3);
    SETREGV(fsel_regVal, ((CE0_N%10)*3), 0x04, BLEN_3);
    SETREGV(fsel_regVal, ((MISO%10)*3),  0x04, BLEN_3);
    SETREGV(fsel_regVal, ((MOSI%10)*3),  0x04, BLEN_3);
    SETREGV(fsel_regVal, ((SCLK%10)*3),  0x04, BLEN_3);
    *fsel_reg = fsel_regVal;
}

void bcm2835peri::spiconfig()
{
    /* Set appropriate settings for the SPI */
    SETBITA(SPI_CS, CSPOL); // Set Chip Select Active Low)
    SETBITA(SPI_CS, CPOL); // Set the Clock to Active High
    SETBITA(SPI_CS, CPHA); // Set SCLK Transition at the middle of the data bit
    SETREGA(SPI_CS, CS, 0x00, BLEN_2); //Set Chip Select 0
    /* Configure the pins in AF */
    spipinsconfig();
}
