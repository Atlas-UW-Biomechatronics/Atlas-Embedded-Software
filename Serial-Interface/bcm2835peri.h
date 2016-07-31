#ifndef _BCM2835PERI_
    #define _BCM2835PERI_

#include <stdint.h>

/* States */
#define              HIGH 0x01
#define               LOW 0x00

/* Peripheral Address Start */
#define BCM2835_PERI_BASE 0x20000000
/* Peripheral Address Offset */
#define          GPIO_OFF 0x00200000
#define           SPI_OFF 0x00204000
/* Peripheral Memory Block Size */
#define        BLOCK_SIZE 0x01000000

/* GPIO Register Offsets */
#define       GPFSEL0_OFF 0x00000000
#define       GPFSEL1_OFF 0x00000004
#define       GPFSEL2_OFF 0x00000008
#define       GPFSEL3_OFF 0x0000000C
#define       GPFSEL4_OFF 0x00000010
#define       GPFSEL5_OFF 0x00000014
#define        GPSET0_OFF 0x0000001C
#define        GPSET1_OFF 0x00000020
#define        GPCLR0_OFF 0x00000028
#define        GPCLR1_OFF 0x0000002C

/* SPI Register Offsets */
#define            CS_OFF 0x00000000
#define          FIFO_OFF 0x00000004   
#define           CLK_OFF 0x00000008
#define          DLEN_OFF 0x0000000C
#define          LTOH_OFF 0x00000010
#define            DC_OFF 0x00000014

/* GPIO Registers */
#define        GPIO_FSEL0 (gpio_addr+GPFSEL0_OFF/4)
#define        GPIO_FSEL1 (gpio_addr+GPFSEL1_OFF/4)
#define        GPIO_FSEL2 (gpio_addr+GPFSEL2_OFF/4)
#define        GPIO_FSEL3 (gpio_addr+GPFSEL3_OFF/4)
#define        GPIO_FSEL4 (gpio_addr+GPFSEL4_OFF/4)
#define        GPIO_FSEL5 (gpio_addr+GPFSEL5_OFF/4)
#define      GPIO_FSEL(P) (gpio_addr+GPFSEL0_OFF/4 + P/10)
#define         GPIO_SET0 (gpio_addr+GPSET0_OFF/4)
#define         GPIO_SET1 (gpio_addr+GPSET1_OFF/4)
#define       GPIO_SET(P) (gpio_addr+GPSET0_OFF/4 + P/32)
#define         GPIO_CLR0 (gpio_addr+GPCLR0_OFF/4)
#define         GPIO_CLR1 (gpio_addr+GPCLR1_OFF/4)
#define       GPIO_CLR(P) (gpio_addr+GPCLR0_OFF/4 + P/32) 

/* SPI Registers */
#define            SPI_CS (spi_addr+CS_OFF/4)
#define          SPI_FIFO (spi_addr+FIFO_OFF/4)

/* SPI Control Bits */
#define               TXD 18
#define               RXD 17
#define              DONE 16
#define                TA 7
#define             CSPOL 6
#define             CLEAR 4
#define              CPOL 3
#define              CPHA 2
#define                CS 0

/* SPI GPIO Pins */
#define             CE1_N 35
#define             CE0_N 36
#define              MISO 37
#define              MOSI 38
#define              SCLK 39

/* SPI GPIO Chip Select Pins */
#define               CE0 0
#define               CE1 1
#define               CE2 2

class bcm2835peri 
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
        /* Call when /dev/mem has not been mapped */
        bcm2835peri();
        /* Call when pointers to physical memory already exists */
        bcm2835peri(void* mapping);
        bcm2835peri(uint32_t* base_addr);
        /* GPIO Functions */
        inline void pinset(uint8_t pin, uint8_t state);
        inline void pinfsel(uint8_t pin, uint8_t func);
        /* SPI Functions */
        void spiconfig();
        void spiselect(uint8_t slave);
        void spigpioselect(uint8_t slave);
        void spitransfer(unsigned char *rbuf, unsigned char *tbuf, uint8_t size);
        void spisend(unsigned char *tbuf, uint8_t size);
        void spirecieve(unsigned char *rbuf, uint8_t size);

    private:
        /* Sets the peripheral addresses */
        void periaddrset();
        /* Configures SPI pins in AF */
        void spipinsconfig();
};
#endif
