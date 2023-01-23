//Functions
void move_forward(); //This function controls the direction of the motors that are connected to the wheels
void move_backward(); //This function controls the direction of the motors that are connected to the wheels
void move_right(); //This function controls the direction of the motors that are connected to the wheels
void move_left(); //This function controls the direction of the motors that are connected to the wheels
void stop(); // This function controls the motors and will stop them once it is called in the program

void interrupt(); //This contains all the things related the interrupt on RB0 and TIM0

void usDelay(unsigned int);
void msDelay(unsigned int);
void msDelay2(unsigned int); // We have a copy from msDelay; so it can be called from the interrupt

void port_initialize(); // This function will initalize all the ports needed for the program

///Variables
char frequency = 15;
char counter = 0;



void interrupt(){
 if(INTCON & 0x02) // This if statement will be TRUE; in case there was change on RB0
  {
    stop();
    move_forward();
    msDelay2(2000);
    stop();
    INTCON = INTCON & 0xFD;
  }
  
  if (INTCON & 0x04) //This if statement will be TRUE; in case there was overflow in TM0
 {
  INTCON = INTCON & 0xFB;
  if (!counter--)
  {
   counter = frequency;
   PORTC = PORTC ^ 0x01;
  }
 }

}


void main(){
port_initialize();
T1CON = 0x00;
//Register Configuration
        INTCON = INTCON | 0x90;
        OPTION_REG =  0x87;
// End of Register Configuration


     while(1)
     {
if (PORTC & 0x20)    // The if statement will depend on what the pins RC5,RC6 and RC7 receives from the ESP wifi module
      {
              //    If RC6 is one
               if (PORTC & 0x40)
               {
               //   If RC7 is one
                if (PORTC & 0x80)
                {
                 move_forward();
                }
                else
                {
                 move_left();
                }
               }
               else
               {
                if (PORTC & 0x80)
                {
                 move_right();
                }
                else
                {
                 move_backward();


                }
               }
              }
              else
              {
               stop();
              }
     }
}

//Start of control direction functions
void move_forward()
{
 PORTD = 0x55; // Here All pins are zero except for 0101 0101, R0,R2,R4,R6
 INTCON = INTCON & 0xDF;
 frequency = 16;
 PORTC = PORTC & 0xFE;
}

void move_backward()
{
 PORTD = 0xAA; // Here all pins are same except for 1010 1010, R1,R3,R5,R7
 INTCON = INTCON | 0x20;
 frequency = 16;
}

void move_right(){

 PORTD = 0x69; // RD0,RD1,RD6,RD7 1010; RD2,RD3,RD4,RD5 0101 -> 0110 1001
 INTCON = INTCON & 0xDF;
 frequency = 16;
 PORTC = PORTC & 0xFE;
}

void move_left(){
 PORTD = 0x99; //RD0,RD1,RD6,RD7 0101; RD2,RD3,RD4,RD5 1010 -> 1001 0110
 INTCON = INTCON & 0xDF;
 frequency = 16;
 PORTC = PORTC & 0xFE;
}

void stop()
{
 PORTD = 0x00;
 INTCON = INTCON & 0xDF;
 PORTC = PORTC & 0xFE;
}
// End of control direction function

// Start of Delay functions
void usDelay(unsigned int uscnt){
     unsigned int us;
     for(us=0;us<uscnt;us++){
        asm NOP; // Takes 0.5us
        asm NOP; // Takes 0.5us
     }
}

void msDelay(unsigned int mscnt){
     unsigned int ms;
     unsigned int cnt;
     for(ms=0;ms<mscnt;ms++){
      for(cnt=0;cnt<155;cnt++);//1ms
     }
}

void msDelay2(unsigned int mscnt){
     unsigned int ms;
     unsigned int cnt;
     for(ms=0;ms<mscnt;ms++){
      for(cnt=0;cnt<155;cnt++);//1ms
     }
}
// End of Delay functions

// This where the PORTS will be initialized
void port_initialize(){
//PORTS Direction Configuration
     TRISD=0x00; // This will make PORTD output all of it
     PORTD=0x00; // This will make PORTD pins all zero
     TRISC=0xFE; // This will make PORTC output all of it
     PORTC=0x00; // This will make PORTC pins all zero
     TRISB=0x05; // RB1 is for the trigger as an output and RB2 is for the echo as an input
     PORTB=PORTB&0x00; // This will make PORTB pins all zero
}
