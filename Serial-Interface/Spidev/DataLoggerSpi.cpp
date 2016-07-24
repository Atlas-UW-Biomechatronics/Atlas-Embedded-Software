#include "DataLoggerSpi.h"
#include <sys/ioctl.h>

using namespace std;

DataLoggerSpi::DataLoggerSpi()
{
    /* Open Spi Device */
    string devPath = "/dev/spidev0.0";
    if (spiOpen(devPath) < 0)
        exit(-1);
    
    /*Set Spi Settings*/
    mode = SPI_MODE_3;
    bitsPerWord = 8;
    speed = 1000000;
    justification = 1;

    /*Configure Clock Phase and Clock Polarity*/
    if (ioctl(this->spifd, SPI_IOC_WR_MODE, &mode) < 0)
        printf("Could not set Clock Phase / Polarity");
    /*Configure Justifcation (!=0 -> LSB, ==0 -> MSB)*/
    if (ioctl(this->spifd, SPI_IOC_WR_LSB_FIRST, &justification) < 0);
        printf("Could not set justification");
    /*Configure Bits Per Word*/
    if (ioctl(this->spifd, SPI_IOC_WR_BITS_PER_WORD, &bitsPerWord) < 0)
        printf("Could not set Bits Per Word");
    /*Configure max speed*/
    if (ioctl(this->spifd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0)
        printf("Could not set the speed");
}

DataLoggerSpi::DataLoggerSpi(std::string devPath, uint8_t mode, uint8_t bitsPerWord, uint32_t speed, uint8_t justification)
{
    /* Open Spi Device */
    if (spiOpen(devPath) < 0)
        exit(-1);
    
    this->mode = mode;
    this->bitsPerWord = bitsPerWord;
    this->speed = speed;
    this->justification = justification;

    /*Configure Clock Phase and Clock Polarity*/
    if (ioctl(this->spifd, SPI_IOC_WR_MODE, &mode) < 0)
        printf("Could not set Clock Phase / Polarity");
    /*Configure Justifcation (!=0 -> LSB, ==0 -> MSB)*/
    if (ioctl(this->spifd, SPI_IOC_WR_LSB_FIRST, &justification) < 0);
        printf("Could not set justification");
    /*Configure Bits Per Word*/
    if (ioctl(this->spifd, SPI_IOC_WR_BITS_PER_WORD, &bitsPerWord) < 0)
        printf("Could not set Bits Per Word");
    /*Configure max speed*/
    if (ioctl(this->spifd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0)
        printf("Could not set the speed");
}

int DataLoggerSpi::spiWriteRead(unsigned char *tdata, unsigned char *rdata)
{
    struct spi_ioc_transfer message;
    message.tx_buf = (unsigned long)tdata;
    message.rx_buf = (unsigned long)rdata;
    message.len = sizeof(unsigned char);
    message.speed_hz = this->speed;
    message.bits_per_word = this->bitsPerWord;
    message.delay_usecs = 0;
    message.cs_change = 1;
   return ioctl(this->spifd, SPI_IOC_MESSAGE(1), &message);
}

int DataLoggerSpi::spiWrite(unsigned char *tdata)
{
    struct spi_ioc_transfer message;
    message.tx_buf = (unsigned long)tdata;
    message.rx_buf = (unsigned long)NULL;
    message.len = sizeof(unsigned char);
    message.speed_hz = this->speed;
    message.bits_per_word = this->bitsPerWord;
    message.delay_usecs = 0;
    message.cs_change = 1;
    return ioctl(this->spifd, SPI_IOC_MESSAGE(1), &message);
}

int DataLoggerSpi::spiRead(unsigned char *rdata)
{
    struct spi_ioc_transfer message;
    message.tx_buf = (unsigned long)NULL;
    message.rx_buf = (unsigned long)rdata;
    message.len = sizeof(unsigned char);
    message.speed_hz = this->speed;
    message.bits_per_word = this->bitsPerWord;
    message.delay_usecs = 0;
    message.cs_change = 1;
    return ioctl(this->spifd, SPI_IOC_MESSAGE(1), &message);
}

int DataLoggerSpi::spiOpen(std::string devPath)
{
    char *spiDev = (char*)devPath.c_str();
    if (this->spifd = open(spiDev, O_RDWR) < 0)
        return -1;
    else
        return 1;
}

int DataLoggerSpi::spiClose()
{
    return close(this->spifd);
}
