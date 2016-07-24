#ifndef RASPBERRYSPI_H
#define RASPBERRYSPI_H

#include <stdint.h>

/* Peripheral Address Start */
#define BCM2835_PERI_BASE 0x20000000
/* Peripheral Address Offset */
#define       GPIO_OFFSET 0x00200000
#define        SPI_OFFSET 0x00204000
/* Peripheral Memory Block Size */
#define        BLOCK_SIZE 0x01000000

/* GPIO Register Offsets */
#define           GPFSEL0 0x00000000
#define           GPFSEL1 0x00000004
#define           GPFSEL2 0x00000008
#define           GPFSEL3 0x0000000C
#define           GPFSEL4 0x00000010
#define           GPFSEL5 0x00000014
#define            GPSET0 0x0000001C
#define            GPSET1 0x00000020
#define            GPCLR0 0x00000028
#define            GPCLR1 0x0000002C

/* SPI Register Offsets */
#define         CS_OFFSET 0x00000000
#define       FIFO_OFFSET 0x00000004   
#define        CLK_OFFSET 0x00000008
#define       DLEN_OFFSET 0x0000000C
#define       LTOH_OFFSET 0x00000010
#define         DC_OFFSET 0x00000014

/* SPI Control Bits */
#define             CSPOL 6
#define              CPOL 3
#define              CPHA 2
#define                CS 0

/* SPI GPIO Pins */
#define            GPFSEL GPFSEL3
#define             CE1_N 35
#define             CE0_N 36
#define              MISO 37
#define              MOSI 38
#define              SCLK 39    

/* Set and Clear Bits from register value */
#define SETBITV(R, P) R |= 0x01<<P
#define CLRBITV(R, P) R &= ~(0x01<<P)
/* Set and Clear Bits from register address */
#define SETBITA(R, P)  *R |= 0x01<<P
#define CLRBITA(R, P)  *R &= ~(0x01<<P)
/* Read the value of a bit from register value */
#define READBITV(R, P) ((R>>P)%2)
/* Read the value of a bit from register address */
#define READBITA( R, P ) ((*R>>P)%2)

class RaspberrySPi 
{
    public:
        /* pointer to memory mapped to physical memory */
        void *mapping;

    private:
        /* pointers to peripheral addresses */
        volatile uint32_t *base_addr;
        volatile uint32_t *gpio_addr;
        volatile uint32_t *spi_addr;

    public:
        //Call when /dev/mem has not been mapped
        RaspberrySPi();
        //Call when pointers to physical memory already exists
        RaspberrySPi(void* mapping);
        RaspberrySPi(uint32_t* base_addr);

    private:
        /* Configures GPIO pins in AF */
        void GpioConfig();
        /* Configures the SPI settings */
        void SpiConfig();
    
};
#endif
