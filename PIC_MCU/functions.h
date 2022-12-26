
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
