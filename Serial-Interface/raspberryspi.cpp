#include "regset.h"
#include "raspberryspi.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <stddef.h>

raspberryspi::raspberryspi()
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
    spi_addr = base_addr + SPI_OFF/4;
    gpio_addr = base_addr + GPIO_OFF/4;
    /* Configure the SPI */
    SpiConfig();
}

raspberryspi::raspberryspi(void* mapping)
{
    this->mapping = mapping;
    base_addr = (volatile uint32_t*)mapping;
    spi_addr = base_addr + SPI_OFF/4;
    gpio_addr = base_addr + GPIO_OFF/4;
    /* Configure the SPI */
    SpiConfig();
}

raspberryspi::raspberryspi(uint32_t* base_addr)
{
    this->base_addr = base_addr;
    spi_addr = this->base_addr + SPI_OFF/4;
    gpio_addr = this->base_addr + GPIO_OFF/4;
    /*Configure the SPI */
    SpiConfig();
}

void raspberryspi::SelectSlave(uint8_t slave) 
{
    /* native slave select */
    switch (slave)
    {
        case (0) :
            CLRBITA(cs_reg, CS+1); CLRBITA(cs_reg, CS+0);
            break;
        case (1) :
            CLRBITA(cs_reg, CS+1); SETBITA(cs_reg, CS+0);
            break;
        case (2) :
            SETBITA(cs_reg, CS+1); CLRBITA(cs_reg, CS+0);
            break;
    }
    //TODO: GPIO Slave Select
}

void raspberryspi::SendRecieveBytes(unsigned char *rbuf, unsigned char *tbuf, uint8_t size)
{
    // Set TA to 1
    SETBITA(cs_reg, TA);
    //Poll TXD and RXD while write bytes to FIFOs
    int rcount = 0;
    int tcount = 0;
    volatile uint32_t *fifo = spi_addr + FIFO_OFF/4;
    while (rcount < size && tcount < size) 
    {
        while (READBITA(cs_reg, TXD) && tcount < size)
        {
            *fifo = tbuf[tcount]; 
            tcount++;
        }
        while (READBITA(cs_reg, RXD) && rcount < size)
        {
            rbuf[rcount] = *fifo; 
            rcount++;
        }
    }
    while (READBITA(cs_reg, DONE)) { }
    CLRBITA(cs_reg, TA);
}

void raspberryspi::SendBytes(unsigned char *tbuf, uint8_t size)
{
    // Set TA to 1
    SETBITA(cs_reg, TA);
    //Poll TXD and RXD while write bytes to FIFOs
    int tcount = 0;
    char rbuf;
    volatile uint32_t *fifo = spi_addr + FIFO_OFF/4;
    while (tcount < size) 
    {
        while (READBITA(cs_reg, TXD) && tcount < size)
        {
            *fifo = tbuf[tcount]; 
            tcount++;
        }
        while (READBITA(cs_reg, RXD))
        {
            rbuf = *fifo; 
        }
    }
    while (READBITA(cs_reg, DONE)) { }
    CLRBITA(cs_reg, TA);
}

void raspberryspi::RecieveBytes(unsigned char *rbuf, uint8_t size)
{
    // Set TA to 1
    SETBITA(cs_reg, TA);
    //Poll TXD and RXD while write bytes to FIFOs
    int rcount = 0;
    volatile uint32_t *fifo = spi_addr + FIFO_OFF/4;
    while (rcount < size) 
    {
        while (READBITA(cs_reg, TXD))
        {
            *fifo = 0x00; 
        }
        while (READBITA(cs_reg, RXD) && rcount < size)
        {
            rbuf[rcount] = *fifo; 
            rcount++;
        }
    }
    while (READBITA(cs_reg, DONE)) { }
    CLRBITA(cs_reg, TA);
}

void raspberryspi::GpioConfig()
{
    volatile uint32_t *fsel_reg = gpio_addr + GPFSEL_OFF/4;
    volatile uint32_t fsel_regVal = *fsel_reg;
    SETREGV(fsel_regVal, ((CE1_N%10)*3+0), 0x04, BLEN_3);
    SETREGV(fsel_regVal, ((CE0_N%10)*3+0), 0x04, BLEN_3);
    SETREGV(fsel_regVal, ((MISO%10)*3+0),  0x04, BLEN_3);
    SETREGV(fsel_regVal, ((MOSI%10)*3+0),  0x04, BLEN_3);
    SETREGV(fsel_regVal, ((SCLK%10)*3+0),  0x04, BLEN_3);
    *fsel_reg = fsel_regVal;
}

void raspberryspi::SpiConfig()
{
    cs_reg = spi_addr + CS_OFF/4; //SPI Control Register
    SETBITA(cs_reg, CSPOL); //set Chip Select Active Low)
    SETBITA(cs_reg, CPOL); //Set the Clock to Active High
    SETBITA(cs_reg, CPHA); //Set SCLK Transition at the middle of the data bit
    SETREGA(cs_reg, CS, 0x00, BLEN_2); //Set Chip Select 0
    cs_reg = NULL;
}
