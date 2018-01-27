#ifndef CAN_SPI
#define CAN_SPI

void spiMasterINIT();
unsigned char spiMasterTRANSMIT(unsigned char data);
void spiMasterChipSelect(unsigned char state);
void extInterruptINIT(void (*handler)(void));
unsigned char readRegister(unsigned char address);
void writeRegister(unsigned char address, unsigned char value);
unsigned char setBitTiming(unsigned char rCNF1,unsigned char rCNF2,unsigned char rCNF3);
void resetMCP2515();
void setAcceptanceCriteria (unsigned char address,unsigned long criterion,unsigned char is_ext);
void initMCP2515(void);
void sendCANmsg(unsigned char bi,unsigned long id,unsigned char * data,unsigned char prop);
void interruptMCP2515(void);

#endif
