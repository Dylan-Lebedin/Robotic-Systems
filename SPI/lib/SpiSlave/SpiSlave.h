#ifndef SpiSlave_h
#define SpiSlave_h

#include <Arduino.h>
#include <inttypes.h>

#define SCK_PIN   13
#define MISO_PIN  12
#define MOSI_PIN  11
#define SS_PIN    10

class SPISlave
{
 public:
   SPISlave(void);
   void mode(uint8_t);
   void SPI_SlaveInit(void);
   uint8_t SPI_SlaveReceive(void);
   uint8_t transfer(uint8_t);
   uint8_t transfer(uint8_t, uint8_t);
};

extern SPISlave SpiSlave;

#endif