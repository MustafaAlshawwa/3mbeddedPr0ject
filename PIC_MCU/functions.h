
# a synchronous delay of 50 ms
sync_delay_50ms()
{
  char i = 50;
  unsigned int j = 2000;
  while(i--)
  {
    j = 2000;
    while(j--)
      j=j;
  }
}

# A function to turn on the buzzer that is connected at RC0
void Buzzer_on()
{
 PORTC = PORTC | 0x01; // Here all pins are same except for RC0 is on
}

# A function to turn on the buzzer that is connected at RC0
void Buzzer_off()
{
 PORTC = PORTC & 0xFE; // Here all pins are same except for RC0 is off
}

# A function to control the direction of the motors 
void move_forward(){
 PORTD = 0x05; // Here all pins are same except for RC0 is on 
}

# A function to control the direction of the motors 
void move_back(){
 PORTD = 0x0A; // Here all pins are same except for RC0 is off 
}

# A function to control the direction of the motors
void move_right(){
  PORTD = 0x09; // Here all pins are zero except for RC0 and RC3
}

# A function to control the direction of the motors
void move_left(){
  PORTD = 0x06; // Here all pins are zero except for RC1 and RC2 
}


# Demo function for interrupt vector at RB0
void interrupt()
{
 Buzzer_on();
 sync_delay_50ms();
 sync_delay_50ms();
 sync_delay_50ms();
 sync_delay_50ms();
 Buzzer_off();
 INTCON = INTCON &  0xFD;
}
