#ifndef raspberryspi_H
#define raspberryspi_H

#include <stdint.h>

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

/* SPI Control Bits */
#define               TXD 18
#define               RXD 17
#define              DONE 16
#define                TA 7
#define             CSPOL 6
#define              CPOL 3
#define              CPHA 2
#define                CS 0

/* SPI GPIO Pins */
#define        GPFSEL_OFF GPFSEL3_OFF
#define             CE1_N 35
#define             CE0_N 36
#define              MISO 37
#define              MOSI 38
#define              SCLK 39    

class raspberryspi 
{
    public:
        /* pointer to memory mapped to physical memory */
        void *mapping;

    private:
        /* pointers to peripheral addresses */
        volatile uint32_t *base_addr;
        volatile uint32_t *gpio_addr;
        volatile uint32_t *spi_addr;
        /* pointers to spi and gpio registers */
        volatile uint32_t *cs_reg;

    public:
        //Call when /dev/mem has not been mapped
        raspberryspi();
        //Call when pointers to physical memory already exists
        raspberryspi(void* mapping);
        raspberryspi(uint32_t* base_addr);
        //SPI Functions
        void SelectSlave(uint8_t slave);
        void SendRecieveBytes(unsigned char *rbuf, unsigned char *tbuf, uint8_t size);
        void SendBytes(unsigned char *tbuf, uint8_t size);
        void RecieveBytes(unsigned char *rbuf, uint8_t size);

    private:
        /* Configures GPIO pins in AF */
        void GpioConfig();
        /* Configures the SPI settings */
        void SpiConfig();
    
};
#endif
