#include "lib_max31855.h"


int max31855_init(spi_t bus, spi_cs_t cs)
{
	spi_init(bus);
	return spi_init_cs(bus, cs);

}

int max31855_readtemp(spi_t bus, spi_cs_t cs, unsigned char * pBuffRes)
{
	spi_acquire(bus, cs, SPI_MODE_0, SPI_CLK_5MHZ);
	spi_transfer_bytes(bus, cs, true, NULL, pBuffRes, 4);	

	spi_release(bus);
	return 1;
}

float max31855_decodetemp(unsigned char * pBuffRes)
{
	uint16_t tempInt = ((pBuffRes[0]&0x7F)<<4) + ((pBuffRes[1]&0xF0)>>4);
	
	float tempFloat = tempInt + 0.5*((pBuffRes[1]&0x08)>>3) + 0.25*((pBuffRes[1]&0x04)>>2);
	return tempFloat;
}





