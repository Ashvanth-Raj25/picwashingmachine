/*
 * File:   washingmachine.c
 * Author: ashva
 *
 * Created on 25 July, 2025, 1:01 PM
 */// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
int i,c,feature,stop;
char str[30]="POWER ON";
char str1[30]="MACHINE STATUS";
char str2[30]="SPIN MODE";
char str3[30]="RINSE MODE";
char str4[30]="DRY MODE";
char str5[30]="MACHINE STOPPED";
char str6[30]="SELECT FEATURE";
void display(char*);
void enable();
void command(char,char);
void delay(unsigned int);
void timer(int);
void low();
void medium();
void high();
void main(void) 
{
 PORTA=PORTB=PORTD=PORTC=PORTE=0X00;
 TRISA=0X1F;
 TRISB=TRISC=TRISE=TRISD=0X00;
 ANSEL=ANSELH=0X00;
  OPTION_REG =0x87;
    TMR0=39;
 command(0,0x38);
 command(0,0x0e);
 command(0,0x01);
 while(1)
 {
     if(RA0==1)
     {
         c=1;
         command(0,0x01);
         command(0,0x80);
         display(str);
         command(0,0xc0);
         display(str6);
         while(RA0==1);
     }
     if(RA2==1 &&c==1)
     {
     {
     
         feature++;
     } 
      while(RA2==1);
     }
       if(RA1==1 && c==1)
         {
    if(feature==1)
         {      command(0,0x01);
                 command(0,0x80);
             display(str1);
                 low();
         }
             if(feature==2)
             {
                 command(0,0x01);
                 command(0,0x80);
             display(str1);
                 medium();
             }
             if(feature==3)
             {
                 command(0,0x01);
                 command(0,0x80);
             display(str1);
                 high();
             }
    if(feature>3)
    {
        feature=0;
    }
             while(RA1==1);
       }
     
 }
}
 

void display(char *string)
{
    for(i=0;string[i]!='\0';i++)
    {
        
        command(1,string[i]);
    }
}
void enable()
{
    RE1=1;
    delay(50);
    RE1=0;
    delay(50);
}
void command(char re,char rs)
{
    RE0=re;
    PORTD=rs;
    enable();
}
void delay(unsigned int a)
{
    while(a--);
}
void low()
{
             //command(0,0x01);
             command(0,0xc0);
             display(str2);
             RB0=1;
             timer(5);
             RB1=1;RB0=0;
             timer(5);
             RB1=0;RB0=0;
}
void medium()
{            //command(0,0x01);
             command(0,0xc0);
             display(str3);
             RB0=1;
             timer(4);
             RB1=1;RB0=0;
             timer(4);
             RB1=0;RB0=0;
}
void high()
{           
            //command(0,0x01);
            command(0,0xc0);
             display(str4);
             RB0=1;
             timer(3);
             RB1=1;RB0=0;
             timer(3);
             RB1=0;RB0=0;
}
void timer(int a)
{
    int count=a*18;
    while(count)
    {
        if(RA4==1)
        {   stop=1;
            command(0,0x01);
            command(0,0x80);
            display(str5);
           break;
        }
    if(T0IF==1)
    {
        count--;
        T0IF=0;
        TMR0=39;
    }
        if(stop==1)
        {
         
         PORTB=0;
         c=0;
         feature=0;
         stop=0;
         
        }
    }
}