void uart0_init(uint32_t );
char uart0_rx(void);
void uart0_tx(char *ch);

void uart1_init(uint32_t );
char uart1_rx(void);
void uart1_tx(char *ch);
void delayMs(uint8_t timer_num, uint32_t delayInMs);
void make_a_call();
void send_message();
