#include "RaspberrySPi.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <stddef.h>

RaspberrySPi::RaspberrySPi()
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
    spi_addr = base_addr + SPI_OFFSET/4;
    gpio_addr = base_addr + GPIO_OFFSET/4;
    /* Configure the SPI */
    SpiConfig();
}

RaspberrySPi::RaspberrySPi(void* mapping)
{
    this->mapping = mapping;
    base_addr = (volatile uint32_t*)mapping;
    spi_addr = base_addr + SPI_OFFSET/4;
    gpio_addr = base_addr + GPIO_OFFSET/4;
    /* Configure the SPI */
    SpiConfig();
}

RaspberrySPi::RaspberrySPi(uint32_t* base_addr)
{
    this->base_addr = base_addr;
    spi_addr = this->base_addr + SPI_OFFSET/4;
    gpio_addr = this->base_addr + GPIO_OFFSET/4;
    /*Configure the SPI */
    SpiConfig();
}

void RaspberrySPi::GpioConfig()
{
    volatile uint32_t *fsel_reg = gpio_addr + GPFSEL/4;
    volatile uint32_t fsel_regVal = *fsel_reg;
    SETBITV(fsel_regVal, (CE1_N%10)*3+0); CLRBITV(fsel_regVal, (CE1_N%10)*3+1); CLRBITV(fsel_regVal, (CE1_N%10)*3+2);
    SETBITV(fsel_regVal, (CE0_N%10)*3+0); CLRBITV(fsel_regVal, (CE0_N%10)*3+1); CLRBITV(fsel_regVal, (CE0_N%10)*3+2);
    SETBITV(fsel_regVal, (MISO%10)*3+0);  CLRBITV(fsel_regVal, (MISO%10)*3+1); CLRBITV(fsel_regVal, (MISO%10)*3+2);
    SETBITV(fsel_regVal, (MOSI%10)*3+0);
    CLRBITV(fsel_regVal, (MOSI%10)*3+1);
    CLRBITV(fsel_regVal, (MOSI%10)*3+2);   
}

void RaspberrySPi::SpiConfig()
{
    volatile uint32_t *cs_reg = spi_addr + CS_OFFSET/4; //SPI Control Register
    SETBITA(cs_reg, CSPOL); //set Chip Select Active Low)
    SETBITA(cs_reg, CPOL); //Set the Clock to Active High
    SETBITA(cs_reg, CPHA); //Set SCLK Transition at the middle of the data bit
    CLRBITA(cs_reg, CS+1); SETBITA(cs_reg, CS); //CHIP SELECT 1;
    cs_reg = NULL;
}
