


void make_call()
{
char ch;



char  arr[]={"Uart Initializing.."};
char  arr1[]={"Sending AT Command"};
char  arr2[]={"Calling. To User"};
char  arr3[]={"Call Disconnect.."};

			GLCD_clearLn(10) ;
			GLCD_displayStringLn(10, arr);
			printf("Uart Initializing...\n\r");
			delayMs(0,2000);

				GLCD_clearLn(10) ;
				GLCD_displayStringLn(10, arr1);
				printf("Uart sending AT command\n\r");
				uart0_tx("AT\r\n");

					printf("Delay call for 1sec\n\r");
					delayMs(0,1000);

					printf("Uart receiving data\n\r");
					ch=uart0_rx();
					uart1_tx(ch);

						printf("Uart Receive AFTER AT:%c\n",ch);
						printf("Delay call for 1sec\n\r");
						delayMs(0,1000);


							printf("Uart sending Mobile No\n\r");
							uart0_tx("ATD9728357365;\r\n");
							GLCD_clearLn(10) ;
							GLCD_displayStringLn(10, arr2);

								printf("Uart receiving data\n\r");
								ch=uart0_rx();
								uart1_tx(ch);


									printf("Uart Receiving:%c\n",ch);
									printf("Delay call for 5sec\n\r");
									delayMs(0,35000);
									uart0_tx("ATH\r\n");
									ch=uart0_rx();
									uart1_tx(ch);
									GLCD_clearLn(10) ;
									GLCD_displayStringLn(10, arr3);
									delayMs(0,3000);
									GLCD_clearLn(10) ;

}



void send_message()
{

char ch;
char  arr[]={"Uart Initializing.."};
char  arr1[]={"Sending AT Command"};
char  arr2[]={"MSG TO 9728357365"};
char  arr3[]={"MSG SEND DONE"};

			GLCD_clearLn(10) ;
			GLCD_displayStringLn(10, arr);
			printf("Uart Initializing...\n\r");
			delayMs(0,2000);

				GLCD_clearLn(10) ;
				GLCD_displayStringLn(10, arr1);
				printf("Uart sending AT command\n\r");
				uart0_tx("AT\r\n");
			
					ch=uart0_rx();		//receving acknowledge
					delayMs(0,2000)
			
						uart0_tx("AT+CMGF=1\r\n");			//Sets the GSM Module in Text Mode
						ch=uart0_rx();					//receving acknowledge
						delayMs(0,2000); 				 // Delay of 1000 milli seconds or 1 second
				
							GLCD_clearLn(10) ;
							GLCD_displayStringLn(10, arr2);

							  	uart0_tx("AT+CMGS=\"+919728357365\"\r\n");	 // Replace x with mobile number
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

	

























}























