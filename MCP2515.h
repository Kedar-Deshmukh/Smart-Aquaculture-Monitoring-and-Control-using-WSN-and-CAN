#ifndef MCP2515_DEFS
#define MCP2515_DEFS
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//MCP2515 pins - PDIP/SOIC Package
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define TXCAN 1           //Transmit CAN signal (To CAN transciever)
#define RXCAN 2           //Receive CAN signal (From CAN transciever)
#define CLKOUT_SOF 3      //Clock out, can be used as clock source for MCU's / SOF signal
#define TX0RTS 4          // (NEG) Request to send input for TXB0 / digital input (with 100k pullup)
#define TX1RTS 5          // (NEG) Request to send input for TXB1 / digital input (with 100k pullup)
#define TX2RTS 6          // (NEG) Request to send input for TXB2 / digital input (with 100k pullup)
#define OSC2 7            //Oscillator output
#define OSC1 8            //Oscillator input
#define VSS 9             //Ground
#define RX1BF 10          // (NEG) RXB1 full interrupt signal / digital output
#define RX0BF 11          // (NEG) RXB0 full interrupt signal / digital output
#define INT 12            // (NEG) nterrupt pin (for MCU, reduces SPI overhead)
#define SCK 13            //SPI clock
#define SI 14             //SPI slave input
#define SO 15             //SPI slave output
#define CS 16             // (NEG) SPI chip select
#define RESET 17           // (NEG) Reset pin (should be connected via RC with tau > 128 osc. ticks)
#define VDD 18            //Power supply
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//MCP2515 pins - TSSOP Package
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define TSSOP_TXCAN 1         //Transmit CAN signal (To CAN transciever)
#define TSSOP_RXCAN 2         //Receive CAN signal (From CAN transciever)
#define TSSOP_CLKOUT_SOF 3    //Clock out, can be used as clock source for MCU's / SOF signal
#define TSSOP_TX0RTS 4        // (NEG) Request to send input for TXB0 / digital input (with 100k pullup)
#define TSSOP_TX1RTS 5        // (NEG) Request to send input for TXB1 / digital input (with 100k pullup)
#define TSSOP_TX2RTS 7        // (NEG) Request to send input for TXB2 / digital input (with 100k pullup)
#define TSSOP_OSC2 8          //Oscillator output
#define TSSOP_OSC1 9          //Oscillator input
#define TSSOP_VSS 10          //Ground
#define TSSOP_RX1BF 11        // (NEG) RXB1 full interrupt signal / digital output
#define TSSOP_RX0BF 12        // (NEG) RXB0 full interrupt signal / digital output
#define TSSOP_INT 13          // (NEG) nterrupt pin (for MCU, reduces SPI overhead)
#define TSSOP_SCK 14          //SPI clock
#define TSSOP_SI 16           //SPI slave input
#define TSSOP_SO 17           //SPI slave output
#define TSSOP_CS 18           // (NEG) SPI chip select
#define TSSOP_RESE9 19        // (NEG) Reset pin (should be connected via RC with tau > 128 osc. ticks)
#define TSSOP_VDD 20          //Power supply



//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//MCP2515 instructions & modes & interrupt codes & buffer indexes
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define RESET_INSTRUCTION 0xC0
#define READ_INSTRUCTION 0x03
#define WRITE_INSTRUCTION 0x02
#define READRX_INSTRUCTION 0x90
#define LOADTX_INSTRUCTION 0x40
#define RTS_INSTRUCTION 0x80
#define READSTAT_INSTRUCTION 0xA0
#define RXSTAT_INSTRUCTION 0xB0
#define BITMODIFY_INSTRUCTION 0x05



// Flags in the result of READ STATE instruction
// (Can be used as bit masks for each flag)
#define STATE_RX0_FULL (0x01<<0)
#define STATE_RX1_FULL (0x01 << 1)
#define STATE_TX0_TXREQ (0x01 << 2)
#define STATE_TX0_EMPTY (0x01 << 3)
#define STATE_TX1_TXREQ (0x01 << 4)
#define STATE_TX1_EMPTY (0x01 << 5)
#define STATE_TX2_TXREQ (0x01 << 6)
#define STATE_TX2_EMPTY (0x01 << 7)


//RX status instruction - mask bits in result state
#define RM_POS (0x03 << 6)       // Received message position
#define EXT_MSG (0x01 << 4)      // Is message extended?
#define REMOTE_MSG (0x01 << 3)   // Is message remote?
#define AFM (0x07 << 0)         // Acceptanc filter match


// Masks for informations contained in the result of RX state instruction
#define RXSTATE_MSG_POSITION 0xC0        // xx000000
#define RXSTATE_MSG_TYPE 0x18            // 000xx000
#define RXSTATE_ACCEPT_FILTER 0x07       // 00000xxx


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//MCP2515 buffers
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Indexes of RX and TX buffers
#define NO_FILTERS 6
#define NO_MASKS 2
#define NO_TX_BUFFERS 3
#define NO_RX_BUFFERS 2
#define TXB0 0
#define TXB1 1
#define TXB2 2
#define RXB0 0
#define RXB1 1



//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//CP2515 buffers
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define RXF0 0
#define RXF1 1
#define RXF2 2
#define RXF3 3
#define RXF4 4
#define RXF5 5



//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//MCP2515 registers
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=
// Transmit & receive error counters
#define TEC 0x1C // Transmit error counter
#define REC 0x1D // Receive error counter


// Bit definitions for register BFPCTRL
// (RXn buffer pin control and status)
#define BFPCTRL 0x0C
#define B1BFS 5
#define B0BFS 4
#define B1BFE 3
#define B0BFE 2
#define B1BFM 1
#define B0BFM 0


// Bit definitions for register CANCTRL
// (CAN control register)
#define CANCTRL 0x0F
#define REQOP2 7
#define REQOP1 6
#define REQOP0 5
#define ABAT 4
#define OSM 3
#define CLKEN 2
#define CLKPRE1 1
#define CLKPRE0 0


// Bit definitions for register CANSTAT
// (CAN status register)
#define CANSTAT 0x0E
#define OPMOD2 7
#define OPMOD1 6
#define OPMOD0 5
#define ICOD2 3
#define ICOD1 2
#define ICOD0 1


// Bit definitions for register CNF3
// (Configuration 3 register)
#define CNF3 0x28
#define SOF 7
#define WAKFIL 6
#define PHSEG22 2
#define PHSEG21 1
#define PHSEG20 0


// Bit definitions for register CNF2
// (Configuration 2 register)
#define CNF2 0x29
#define BTLMODE 7
#define SAM 6
#define PHSEG12 5
#define PHSEG11 4
#define PHSEG10 3
#define PRSEG2 2
#define PRSEG1 1
#define PRSEG0 0


// Bit definitions for register CNF1
// (Configuration 1 register)
#define CNF1 0x2A
#define SJW1 7
#define SJW0 6
#define BRP5 5
#define BRP4 4
#define BRP3 3
#define BRP2 2
#define BRP1 1
#define BRP0 0


// Bit definitions for register CANINTE
// (Interrupt enable register)
#define CANINTE 0x2B
#define MERRE 7
#define WAKIE 6
#define ERRIE 5
#define TX2IE 4
#define TX1IE 3
#define TX0IE 2
#define RX1IE 1
#define RX0IE 0


// Bit definitions for register CANINTF
// (Interrupt flag register)
#define CANINTF 0x2C
#define MERRF 7
#define WAKIF 6
#define ERRIF 5
#define TX2IF 4
#define TX1IF 3
#define TX0IF 2
#define RX1IF 1
#define RX0IF 0


// Bit definitions for register EFLG
// (Error flag register)
#define EFLG 0x2D
#define RX1OVR 7
#define RX0OVR 6
#define TXBO 5
#define TXEP 4
#define RXEP 3
#define TXWAR 2
#define RXWAR 1
#define EWARN 0






// Bit definitions for registers TXBnCTRL
// (Transmit buffer n control register)
#define TXBnCTRL(n) 0x30+(n*0x10)
#define TXB0CTRL TXBnCTRL(0)
#define TXB1CTRL TXBnCTRL(1)
#define TXB2CTRL TXBnCTRL(2)
#define ABTF 6               // R-0, Message aborted flag bit
#define MLOA 5               // R-0, Message lost arbitration bit
#define TXERR 4              // R-0, Transmit error detected bit
#define TXREQ 3              // RW-0, Message transmit request bit
#define TXP1 1              // RW-0, Transmit buffer priority bit 1
#define TXP0 0             // RW-0, Tra



// Bit definitions for registers TXBnDLC
// (Transmit buffer data length control)
#define TXBnDLC(n) 0x35+(n*0x10)
#define TXB0DLC TXBnSIDH(0)
#define TXB2DLC TXBnSIDH(1)
#define TXB1DLC TXBnSIDH(2)
#define SID10 7
#define SID9 6
#define SID8 5
#define SID7 4
#define SID6 3
#define SID5 2
#define SID4 1
#define SID3 0




// Bit definitions for register TXBnSIDL
// (Transmit buffer n - standard identifier low)
#define TXBnSIDL(n) 0x32+(n*0x10)
#define TXB0SIDL TXBnSIDL(0)
#define TXB1SIDL TXBnSIDL(1)
#define TXB2SIDL TXBnSIDL(2)
#define SID2 7
#define SID1 6
#define SID0 5
#define EXIDE 3
#define EID17 1
#define EID16 0


// Bit definitions for register TXBnEID8
// (Transmit buffer n - extended identifier high)
#define TXBnEID8(n) 0x33+(n*0x10)
#define TXB0EID8 TXBnEID8(0)
#define TXB1EID8 TXBnEID8(1)
#define TXB2EID8 TXBnEID8(2)
#define EID15 7
#define EID14 6
#define EID13 5
#define EID12 4
#define EID11 3
#define EID10 2
#define EID9 1
#define EID8 0



// Bit definitions for register TXBnEID0
// (Transmit buffer n - extended identifier high)
#define TXBnEID0(n) 0x34+(n*0x10)
#define TXB0EID0 TXBnEID0(0)
#define TXB1EID0 TXBnEID0(1)
#define TXB2EID0 TXBnEID0(2)
#define EID7 7
#define EID6 6
#define EID5 5
#define EID4 4
#define EID3 3
#define EID2 2
#define EID1 1
#define EID0 0


// Bit definitions for registers TXBnDm
// (Transmit buffer N data byte M)
#define TXBnDm(n,m) 0x36+(n*0x10)+m
#define TXBnDm7 7
#define TXBnDm6 6
#define TXBnDm5 5
#define TXBnDm4 4
#define TXBnDm3 3
#define TXBnDm2 2
#define TXBnDm1 1
#define TXBnDm0 0


// Bit definitions for register TXRTSCTRL
// (TXn buffer pin control and status)
#define TXRTSCTRL 0x0D
#define B2RTS 5 // R, TX2RTS pin state bit
#define B1RTS 4 // R, TX1RTS pin state bit
#define B0RTS 3 // R, TX0RTS pin unction enable bit
#define B2RTSM 2 // RW-0, TX2RTS pin mode bit
#define B1RTSM 1 // RW-0, TX1RTS pin mode bit
#define B0RTSM 0 // RW-0, TX1RTS pin mode bit


// Bit definitions for registers RXBnCTRL
// (Receive buffer n control register)
#define RXBnCTRL(n) 0x60+(n*0x10)
#define RXB0CTRL RXBnCTRL(0)
#define RXB1CTRL RXBnCTRL(1)
#define RXM1 6 // RW-0, Receive buffer operating mode bit 1
#define RXM0 5 // RW-0, Receive buffer operating mode bit 0
#define RXRTR 3 // R-0, Receive remote transfer request bit
#define BUKT 2 // RW-0, Rollover enable bit (used only by RXB0CTRL)
#define FILHIT2 2 // R-0, Filter hit bit 2 (used only by RXB1CTRL)
#define FILHIT1 1 // R-0, Filter hit bit 1 (used only by RXB1CTRL)
#define FILHIT0 0 // R-0, Filter hit bit 0



// Bit definitions for registers RXBnSIDH
// (Receive buffer n standard identifier high)
#define RXBnSIDH(n) 0x61+(n*0x10)
#define RXB0SIDH RXBnSIDH(0)
#define RXB1SIDH RXBnSIDH(1)
#define SID10 7
#define SID9 6
#define SID8 5
#define SID7 4
#define SID6 3
#define SID5 2
#define SID4 1
#define SID3 0



// Bit definitions for register RXBnSIDL
// (Receive buffer n - standard identifier low)
#define RXBnSIDL(n) 0x62+(n*0x10)
#define RXB0SIDL RXBnSIDL(0)
#define RXB1SIDL RXBnSIDL(1)
#define SID2 7
#define SID1 6
#define SID0 5
#define SRR 4
#define IDE 3
#define EID17 1
 #define EID16 0



 // Bit definitions for register RXBnEID8
// (Revceive buffer n - extended identifier high)
#define RXBnEID8(n) 0x63+(n*0x10)
#define RXB0EID8 RXBnEID8(0)
#define RXB1EID8 RXBnEID8(1)
#define EID15 7
#define EID14 6
#define EID13 5
#define EID12 4
#define EID11 3
#define EID10 2
#define EID9 1
#define EID8 0


// Bit definitions for register RXBnEID0
// (Receive buffer n - extended identifier high)
#define RXBnEID0(n) 0x64+(n*0x10)
#define RXB0EID0 RXBnEID0(0)
#define RXB1EID0 RXBnEID0(1)
#define EID7 7
#define EID6 6
#define EID5 5
#define EID4 4
#define EID3 3
#define EID2 2
#define EID1 1
#define EID0 0



// Bit definitions for registers RXBnDLC
// (Receive buffer data length control)
#define RXBnDLC(n) 0x65+(n*0x10)
#define RXB0DLC RXBnDLC(0)
#define RXB1DLC RXBnDLC(1)
#define RTR 6
#define DLC3 3
#define DLC2 2
#define DLC1 1
#define DLC0 0



// Bit definitions for registers RXBnDm
// (Receive buffer N data byte M)
#define RXBnDm(n,m) 0x66 + (n*0x10) + m
#define RXBnDm7 7
#define RXBnDm6 6
#define RXBnDm5 5
#define RXBnDm4 4
#define RXBnDm3 3
#define RXBnDm2 2
#define RXBnDm1 1
#define RXBnDm0 0



// Bit definitions for registers RXFnSIDH
// (Filter n standard identifier high)
#define RXFnSIDH(n) 0+(n*4)+((n>2)?4:0)
#define RXF0SIDH RXFnSIDH(0)
#define RXF1SIDH RXFnSIDH(1)
#define RXF2SIDH RXFnSIDH(2)
#define RXF3SIDH RXFnSIDH(3)
#define RXF4SIDH RXFnSIDH(4)
#define RXF5SIDH RXFnSIDH(5)



// Bits are same as in TXBnSIDH
// Bit definitions for register RXFnSIDL
// (Filter n - standard identifier low)
#define RXFnSIDL(n) 1+(n*4)+((n>2)?4:0
#define RXF0SIDL RXFnSIDL(0)
#define RXF1SIDL RXFnSIDL(1)
#define RXF2SIDL RXFnSIDL(2)
#define RXF3SIDL RXFnSIDL(3)
#define RXF4SIDL RXFnSIDL(4)
#define RXF5SIDL RXFnSIDL(5)

//Bits are same as in TXBnSIDL
// Bit definitions for register RXFnEID8
// (Filter n - extended identifier high
#define RXFnEID8(n) 2+(n*4)+((n>2)?4:0)
#define RXF0EID8 RXFnEID8(0)
#define RXF1EID8 RXFnEID8(1)
#define RXF2EID8 RXFnEID8(2)
#define RXF3EID8 RXFnEID8(3)
#define RXF4EID8 RXFnEID8(4)
#define RXF5EID8 RXFnEID8(5)


// Bits EID15-EID8 are same as in TXBnEID8
// Bit definitions for register RXFnEID0
// (Filter buffer n - extended identifier low)
#define RXFnEID0(n) 3+(n*4)+((n>2)?4:0)
#define RXF0EID0 RXFnEID0(0)
#define RXF1EID0 RXFnEID0(1)
#define RXF2EID0 RXFnEID0(2)
#define RXF3EID0 RXFnEID0(3)
#define RXF4EID0 RXFnEID0(4)
#define RXF5EID0 RXFnEID0(5)


// Bits EID7-EID0 are same as in TXBnEID0
// Bit definitions for registers RXMnSIDH
// (Mask n standard identifier high)
#define RXMnSIDH(n) 0x20+(n*4)
#define RXM0SIDH RXMnSIDH(0)
#define RXM1SIDH RXMnSIDH(1)
// Bits are same as in TXBnSIDH
// Bit definitions for register RXMnSIDL
// (Mask n - standard identifier low)
#define RXMnSIDL(n) 0x21+(n*4)
#define RXM0SIDL RXMnSIDL(0)
#define RXM1SIDL RXMnSIDL(1)
//Bits are are same as in TXBnSIDL
// Bit definitions for register RXMnEID8
// (Filter n - extended identifier high)
#define RXMnEID8(n) 0x22+(n*4)
#define RXM0EID8 RXMnEID8(0)
#define RXM1EID8 RXMnEID8(1)
// Bits EID15-EID8 are same as in TXBnEID8


// Bit definitions for register RXMnEID0
// (Filter buffer n - extended identifier high)
#define RXMnEID0(n) 0x23+(n*4)
#define RXM0EID0 RXMnEID0(0)
#define RXM1EID0 RXMnEID0(1)
// Bits EID7-EID0 are same as in TXBnEID0



/** List of registers which are accessible from BIT MODIFY instruction. You can use following code
* to declare array with all registers which are supported by "Bit modify" instruction:
* \code
* unsigned char test[] = {BIT_MODIFY_SUPPORTED_REGISTERS};
* \endcode
*/
#define BIT_MODIFY_SUPPORTED_REGISTERS BFPCTRL,TXRTSCTRL,CANCTRL,CNF3,CNF2,CNF1,CANINTE,CANINTF,EFLG,TXB0CTRL,TXB1CTRL,TXB2CTRL,RXB0CTRL,RXB1CTRL
#endif
