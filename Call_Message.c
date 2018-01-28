


void make_call()
{
char ch;



char  arr[]={"Uart Initializing.."};
char  arr1[]={"Sending AT Command"};
char  arr2[]={"Calling. To User"};		//message buffers for tft display to print messages
char  arr3[]={"Call Disconnect.."};

			GLCD_clearLn(10) ;		/// in my code i used line no 1 so thats why i write 10,  and its a line clear functin its only clear line no 10.
			GLCD_displayStringLn(10, arr);	//simply printing buffer 0 message by sending line number and buffer as arguments
			printf("Uart Initializing...\n\r");
			delayMs(0,2000);

				GLCD_clearLn(10) ;
				GLCD_displayStringLn(10, arr1);			// same process for buffer 1 data
				printf("Uart sending AT command\n\r");		// printf function is used for debugging using semihosting we can remove this line after debugg
				uart0_tx("AT\r\n");				//	sendig AT Command to  gsm module

					printf("Delay call for 1sec\n\r");
					delayMs(0,1000);

					printf("Uart receiving data\n\r");	
					ch=uart0_rx();				// here am receiving acknowledge by gsm
					uart1_tx(ch);				// sending receving char from uart0 to uart1 for debugg purpose 

						printf("Uart Receive AFTER AT:%c\n",ch);
						printf("Delay call for 1sec\n\r");
						delayMs(0,1000);


							printf("Uart sending Mobile No\n\r");
							uart0_tx("ATD972835736*;\r\n");		//sending mobile number to uart0 //u can change this mobile no with ur own mob no . last * is nothing its 10th digit of my mobile no so thats why i hide it 
							GLCD_clearLn(10) ;
							GLCD_displayStringLn(10, arr2);			//printing buffer 2 

								printf("Uart receiving data\n\r");
								ch=uart0_rx();				//receiving acknowledge
								uart1_tx(ch);


									printf("Uart Receiving:%c\n",ch);
									printf("Delay call for 5sec\n\r");
									delayMs(0,35000);
									uart0_tx("ATH\r\n");	//call disconnect command send to uart for miss call purpose
									
									ch=uart0_rx();
									uart1_tx(ch);
									GLCD_clearLn(10) ;
									GLCD_displayStringLn(10, arr3);			// printing buffer data arr3
									delayMs(0,3000);
									GLCD_clearLn(10) ;

}



void send_message()
{

char ch;
char  arr[]={"Uart Initializing.."};
char  arr1[]={"Sending AT Command"};
char  arr2[]={"MSG TO 972835736*"};		// data buffer for sending sms
char  arr3[]={"MSG SEND DONE"};

			GLCD_clearLn(10) ;
			GLCD_displayStringLn(10, arr);
			printf("Uart Initializing...\n\r");	//printing buffer0 on tft 
			delayMs(0,2000);

				GLCD_clearLn(10) ;		//clear line and for printing new buffer data
				GLCD_displayStringLn(10, arr1);  	//printing buffer1 
				printf("Uart sending AT command\n\r");
				uart0_tx("AT\r\n");			//sending at command
			
					ch=uart0_rx();		//receving acknowledge
					delayMs(0,2000)
			
						uart0_tx("AT+CMGF=1\r\n");			//Sets the GSM Module in Text Mode
						ch=uart0_rx();					//receving acknowledge
						delayMs(0,2000); 				 // Delay of 1000 milli seconds or 1 second
				
							GLCD_clearLn(10) ;
							GLCD_displayStringLn(10, arr2);

							  	uart0_tx("AT+CMGS=\"+91972835736*\"\r\n");	 // Replace x with mobile number
								ch=uart0_rx();					//receving acknowledge
								delayMs(2000);

								uart0_tx("I am SMS from LPC1768");		// The SMS text you want to send
				 				delayMs(1000);
				 				uart0_tx((char)26);				// ASCII code of CTRL+Z
				
									ch=uart0_rx();					//receving acknowledge
									GLCD_clearLn(10) ;
									GLCD_displayStringLn(10, arr3);
					  				delayMs(3000);

}























