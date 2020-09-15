#include <Arduino.h>
#include "SpiSlave.h"

//---------- constructor ----------------------------------------------------

SPISlave::SPISlave()
{

}

//------------------ mode ---------------------------------------------------

void SPISlave::mode(byte config)
{  byte tmp;
   // initialize the SPI pins
 pinMode(SCK_PIN, OUTPUT);
 pinMode(MOSI_PIN, OUTPUT);
 pinMode(MISO_PIN, INPUT);
 pinMode(SS_PIN, OUTPUT);

 // enable SPI master with configuration byte specified
 SPCR = 0;
 SPCR = (config & 0x7F) | (1<<SPE) | (1<<MSTR);
 tmp = SPSR;
 tmp = SPDR;
}
void SPISlave::SPI_SlaveInit(void)
{
 /* Set MISO output, all others input */
 //DDR_SPI = ( 1 <<DD_MISO);
 pinMode(SCK_PIN, INPUT);
 pinMode(MOSI_PIN, INPUT);
 pinMode(MISO_PIN, OUTPUT);
 pinMode(SS_PIN, INPUT);
 /* Enable SPI */
// SPCR = ( 1 <<SPE)|(0<<MSTR);
  SPCR = B01000000;//SPIE=0,SPE=1,DORD=0,MSTR=0,CPOL=0,CPOL=0,SPR=00
}

uint8_t SPISlave::SPI_SlaveReceive(void)
{
 /*Wait for reception complete */
 while(!(SPSR & (1<<SPIF)))
     ;
   /* Return Data Register */
   return SPDR;
}
//------------------ transfer -----------------------------------------------

uint8_t SPISlave::transfer(uint8_t value)
{
 SPDR = value;
 while (!(SPSR & (1<<SPIF))) ;
 return SPDR;
}


uint8_t SPISlave::transfer(uint8_t value, uint8_t period)
{
 SPDR = value;
 if (period > 0) delayMicroseconds(period);
 while (!(SPSR & (1<<SPIF))) ;
 return SPDR;
}


//---------- preinstantiate SPI object --------------------------------------

SPISlave SpiSlave = SPISlave();
