/*
 * caninterfacing_avr.c
 *
 * Created: 23-Jan-18 7:46:57 PM
 *  Author: SAI
 */ 

#include <avr/io.h>
#include "can_spi.h"
#include "avr/interrupt.h"
#include "MCP2515.h"
//#include "MCP2515-interface.h"
#define getMode (readRegister(CANSTAT) >> 5)
#define setMode(mode) { changeBits(CANCTRL, (7 << REQOP0), \
		(mode << REQOP0));while(getMode != mode);}
#define setRollover(v) changeBits(RXB0CTRL, 1 << BUKT, v << BUKT);
#define setMask(n, c, e) setAcceptanceCriteria(RXMnSIDH(n), c, e)
#define setFilter(n, c, e) setAcceptanceCriteria(RXFnSIDH(n), c, e)
#define getData(n) msgReceived[6+i]
#define getId (unsigned short)((msgReceived[1]<<3)|(msgReceived[2]>>5))
#define getLength msgReceived[5] >> 4
/* Configuration routine */



void initMCP2515(void)
{
  /* Initialize SPI as a master device, on frequency < 10Mhz */
  spiMasterINIT();
  /* Send reset instruction */
  resetMCP2515();
  /* Set configuration mode */
  //setMode(CONFIGURATION_MODE);
  /* Set bit timing only - this is feeder, no listening required */
 // setBitTiming(0x04, 0xD2, 0x42);
  /* Get into normal mode and setup communication */
  //setMode(NORMAL_MODE);
}

/** Send a CAN message
* \param bi transmit buffer index
* \param id message identifier
* \param data pointer to data to be stored
* \param prop message properties, the octet has following structure:
*
- bits 7:6 - message priority (higher the better)
*
- bit 5
- if set, message is remote request (RTR)
*
- bit 4
- if set, message is considered to have ext. id.
*
- bits 3:0 - message length (0 to 8 bytes) */
void sendCANmsg(unsigned char bi,unsigned long id,unsigned char * data,unsigned char prop)
{
  /* Initialize reading of the receive buffer */
  spiMasterChipSelect(1);
  /* Send header and address */
  spiMasterTRANSMIT(WRITE_INSTRUCTION);
  spiMasterTRANSMIT(TXBnCTRL(bi));
  /* Setup message priority */
  spiMasterTRANSMIT(prop >> 6);
  /* Setup standard or extended identifier*/
  if(prop & 0x10)
  {
    spiMasterTRANSMIT((unsigned char)(id>>3));
    spiMasterTRANSMIT((unsigned char)(id<<5)|(1<<EXIDE)|((unsigned char)(id>>27)));
    spiMasterTRANSMIT((unsigned char)(id>>19));
    spiMasterTRANSMIT((unsigned char)(id>>19));
  }
  else
  {
    spiMasterTRANSMIT((unsigned char)(id>>3));
    spiMasterTRANSMIT((unsigned char)(id<<5));
  }
  /* Setup message length and RTR bit */
  spiMasterTRANSMIT((prop & 0x0F) | ((prop & 0x20) ? (1 << RTR) : 0));

  /* Store the message into the buffer */
  for(unsigned char i = 0; i < (prop & 0x0F); i++)
    spiMasterTRANSMIT(data[i]);
  /* Release the bus */
  spiMasterChipSelect(0);
  /* Send request to send */
  //sendRTS(bi);
}


/* Make some delay */
void doDelay()
{
  unsigned char i,j,k;
  for(i=0;i<255;i++)
  for(j=0;j<255;j++)
  for(k=0;k<5;k++);
}



/* Main routine */
int main(void)
{
  unsigned char data[8] = "Hello w!";
  /* initialize CAN */
  initMCP2515();
  /* Enable global interrupt flag */
  sei();
  /* Send the messages periodically */
  while(1)
  {
    sendCANmsg(0, 0x7E1, data, 8);
    doDelay();
  }
return 0;
}
