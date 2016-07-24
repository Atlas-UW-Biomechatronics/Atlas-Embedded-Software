#ifndef DATALOGGERSPI_H 
    #define DATALOGGERSPI_H
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#define MSB_FIRST 0
#define LSB_FIRST 1

class DataLoggerSpi{

    public:
        DataLoggerSpi();
        DataLoggerSpi(std::string devPath, uint8_t mode, uint8_t bitsPerWord, uint32_t speed, uint8_t justification);
        ~DataLoggerSpi();
        int spiWriteRead( unsigned char *tdata, unsigned char *rdata );
        int spiWrite    ( unsigned char *tdata                       );
        int spiRead     (                       unsigned char *rdata );

    private:
        //SPI Mode being used (SPI_MODE_0 or SPI_MODE_1, SPI_MODE_2, SPI_MODE_3) 
        uint8_t mode;
        //bit width of word
        uint8_t bitsPerWord;
        //bus speed or SPI clock frequency: 0.5, 1, 2, 4, 8, 16, 32 MHz
        uint32_t speed;
        //justification
        uint8_t justification;
        //file descriptor for the device
        int spifd;

        int spiOpen(std::string devPath);
        int spiClose();

};

#endif
