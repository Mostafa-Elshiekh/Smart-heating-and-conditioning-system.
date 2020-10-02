   void lcd_init();
  void lcd_command(char cmd)  ;                                                                //send commends to LCD
  void lcd_out(unsigned char value)  ;                                                       // send data to LCD as (char)
  void lcd_print(char *str) ;                                                                          // print string
  void lcd_go_to(unsigned char x,unsigned char y) ;                        // determine position
  void lcd_int(int value)  ;                                                                           // print integer value
  void lcd_num(int n);
  char keypad(void);
  void Pin_Direction(uint8_t  base , uint8_t  bin , uint8_t  state );  //base is register bin
  void Port_Direction(uint8_t  base  , uint8_t  state ) ;                     //base is register bin
uint8_t  Port_Write(uint8_t  base , uint8_t  value);










