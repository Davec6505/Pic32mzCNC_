#line 1 "C:/Users/Git/Pic32mzCNC/Config.c"
#line 1 "c:/users/git/pic32mzcnc/config.h"







extern unsigned char LCD_01_ADDRESS;
extern bit oneShotA; sfr;
extern bit oneShotB; sfr;




struct Timer{
unsigned int uSec;
unsigned int uMs;
unsigned int uSSec;
unsigned int OlduSSec;
unsigned int mSec;
unsigned short Sec;
unsigned short OldSec;
};
extern struct Timer TMR;


void PinMode();
void UartConfig();
void set_performance_mode();
void Uart2InterruptSetup();
void InitTimer6();
void InitTimer7();
void InitTimer8();
void LcdI2CConfig();
void OutPutPulseXYZ();
void initDMA_global();
void initDMA0();
void initDMA1();
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic32/include/built_in.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic32/packages/i2c_lcd/uses/i2c_lcd.h"
#line 59 "c:/users/public/documents/mikroelektronika/mikroc pro for pic32/packages/i2c_lcd/uses/i2c_lcd.h"
typedef enum{
 _LCD_FIRST_ROW = 1,
 _LCD_SECOND_ROW,
 _LCD_THIRD_ROW,
 _LCD_FOURTH_ROW,
 _LCD_CLEAR,
 _LCD_RETURN_HOME,
 _LCD_CURSOR_OFF,
 _LCD_UNDERLINE_ON,
 _LCD_BLINK_CURSOR_ON,
 _LCD_MOVE_CURSOR_LEFT,
 _LCD_MOVE_CURSOR_RIGHT,
 _LCD_TURN_ON,
 _LCD_TURN_OFF,
 _LCD_SHIFT_LEFT,
 _LCD_SHIFT_RIGHT,
 _LCD_INCREMENT_NO_SHIFT
}Cmd_Type;

extern Cmd_Type Cmd;



  unsigned char  I2C_PCF8574_Write( unsigned char  addr, unsigned char  Data);
 void I2C_LCD_putcmd( unsigned char  addr,  unsigned char  dta, unsigned char  cmdtype);
 void I2C_LCD_goto( unsigned char  addr, unsigned char  row,  unsigned char  col);
 void I2C_Lcd_Cmd( unsigned char  addr,Cmd_Type cmd, unsigned char  col);
 void I2C_LCD_putch( unsigned char  addr,  unsigned char  dta);
 void I2C_LCD_Out( unsigned char  addr,  unsigned char  row,  unsigned char  col,  unsigned char  *s);
 void I2C_Lcd_Chr( unsigned char  addr,  unsigned char  row,  unsigned char  col,  unsigned char  out_char);
 void I2C_LCD_init( unsigned char  addr);
 void I2C_LCD_init4l( unsigned char  addr);
#line 5 "C:/Users/Git/Pic32mzCNC/Config.c"
void PinMode(){

 SYSKEY = 0xAA996655;
 SYSKEY = 0x556699AA;
 CFGCONbits.OCACLK = 1;
 SYSKEY = 0x33333333;

 JTAGEN_bit = 0;
 Delay_ms(100);


 ANSELA = 0X0000;
 ANSELB = 0X0000;
 ANSELC = 0X0000;
 ANSELD = 0X0000;
 ANSELE = 0X0000;
 ANSELG = 0X0000;

 CNPUB = 0x0000;


 TRISA9_bit = 0;
 TRISE7_bit = 0;
 TRISF1_bit = 0;
 TRISG0_bit = 0;
 TRISG1_bit = 0;


 TRISB0_bit = 1;
 TRISC3_bit = 1;
 TRISG7_bit = 1;
 TRISG8_bit = 1;
 TRISF0_bit = 0;


 Unlock_IOLOCK();
 PPS_Mapping_NoLock(_RPE8, _OUTPUT, _U2TX);
 PPS_Mapping_NoLock(_RPE9, _INPUT, _U2RX);
 PPS_Mapping_NoLock(_RPB9, _OUTPUT, _NULL);
 PPS_Mapping_NoLock(_RPB10, _OUTPUT, _NULL);
 PPS_Mapping_NoLock(_RPF1, _OUTPUT, _OC3);
 PPS_Mapping_NoLock(_RPG0, _OUTPUT, _OC4);
 PPS_Mapping_NoLock(_RPG1, _OUTPUT, _OC6);
 Lock_IOLOCK();



 UartConfig();



 set_performance_mode();







 InitTimer6();
 InitTimer7();
 InitTimer8();


 LcdI2CConfig();



 initDMA_global();
 initDMA0();
 initDMA1();



 OutPutPulseXYZ();

}

void UartConfig(){


 UART2_Init_Advanced(256000, 50000 , _UART_LOW_SPEED, _UART_8BIT_NOPARITY, _UART_ONE_STOPBIT);
 UART_Set_Active(&UART2_Read, &UART2_Write, &UART2_Data_Ready, &UART2_Tx_Idle);
 Delay_ms(100);
}



void Uart2InterruptSetup(){
 URXISEL0_bit = 0;
 URXISEL1_bit = 1;
 IEC4.B18 = 1;

 U2RXIP0_bit = 1;
 U2RXIP1_bit = 1;
 U2RXIP2_bit = 1;

 URXISEL1_U2STA_bit = 0;
 U2RXIF_bit = 0;
}

void set_performance_mode(){


 DI();


 SYSKEY = 0xAA996655;
 SYSKEY = 0x556699AA;


 PB1DIVbits.PBDIV = 1;


 UEN0_bit = 1;
 UEN1_bit = 1;
 PB2DIVbits.ON = 1;
 while(!PB2DIVbits.PBDIVRDY);
 PB2DIVbits.PBDIV = 0x07;


 PB3DIVbits.ON = 1;
 while(!PB3DIVbits.PBDIVRDY);
 PB3DIVbits.PBDIV = 3;


 PB4DIVbits.ON = 1;
 while (!PB4DIVbits.PBDIVRDY);
 PB4DIVbits.PBDIV = 0;


 PB5DIVbits.ON = 1;
 while(!PB5DIVbits.PBDIVRDY);
 PB5DIVbits.PBDIV = 1;


 PB7DIVbits.ON = 1;
 while(!PB7DIVbits.PBDIVRDY);
 PB7DIVbits.PBDIV = 0;


 PB8DIVbits.ON = 1;
 while(!PB8DIVbits.PBDIVRDY);
 PB8DIVbits.PBDIV = 1;


 PRECONbits.PFMSECEN = 0;
 PRECONbits.PREFEN = 0b11;
 PRECONbits.PFMWS = 0b100;
#line 162 "C:/Users/Git/Pic32mzCNC/Config.c"
 SYSKEY = 0x33333333;
}


void OutPutPulseXYZ(){
#line 172 "C:/Users/Git/Pic32mzCNC/Config.c"
 OC3CON = 0x0000;
 OC6CON = 0x0000;


 T2CON = 0x0000;
 T4CON = 0x0000;


 T2CON = 0x0060;
 T4CON = 0x0060;


 PR2 = 0xFFFF;
 PR4 = 0xFFFF;


 OC3CON = 0x0004;
 OC6CON = 0x0004;
#line 198 "C:/Users/Git/Pic32mzCNC/Config.c"
 OC3R = 0x5;
 OC3RS = 0x234;
 OC6R = 0x5;
 OC6RS = 0x234;


 OC3IP0_bit = 1;
 OC3IP1_bit = 1;
 OC3IP2_bit = 0;
 OC3IS0_bit = 0;
 OC3IS1_bit = 0;
 OC3IF_bit = 0;
 OC3IE_bit = 1;

 OC6IP0_bit = 1;
 OC6IP1_bit = 1;
 OC6IP2_bit = 0;
 OC6IS0_bit = 1;
 OC6IS1_bit = 0;
 OC6IF_bit = 0;
 OC6IE_bit = 1;


 T2CONSET = 0x8000;
 T4CONSET = 0x8000;





}


void InitTimer6(){
 T6CON = 0x8000;
 T6IP0_bit = 0;
 T6IP1_bit = 0;
 T6IP2_bit = 1;
 T6IS0_bit = 1;
 T6IS1_bit = 0;
 T6IF_bit = 0;
 T6IE_bit = 0;
 PR6 = 500;
 TMR6 = 0;
}



void InitTimer7(){
 T7CON = 0x8000;
 T7IP0_bit = 0;
 T7IP1_bit = 0;
 T7IP2_bit = 1;
 T7IS0_bit = 1;
 T7IS1_bit = 1;
 T7IF_bit = 0;
 T7IE_bit = 0;
 PR7 = 50000;
 TMR7 = 0;
}


void InitTimer8(){
 T8CON = 0x8000;
 T8IP0_bit = 0;
 T8IP1_bit = 0;
 T8IP2_bit = 1;
 T8IS0_bit = 0;
 T8IS1_bit = 1;
 T8IF_bit = 0;
 T8IE_bit = 0;
 PR8 = 50;
 TMR8 = 0;
}

void LcdI2CConfig(){

 I2C4_Init_Advanced(50000, 100000);
 I2C_Set_Active(&I2C4_Start, &I2C4_Restart, &I2C4_Read, &I2C4_Write,
 &I2C4_Stop,&I2C4_Is_Idle);
 Delay_ms(100);
 I2C_LCD_init(LCD_01_ADDRESS);
 Delay_ms(100);
 I2C_Lcd_Cmd(LCD_01_ADDRESS,_LCD_FIRST_ROW,1);
 I2C_Lcd_Cmd(LCD_01_ADDRESS,_LCD_CURSOR_OFF,1);
 I2C_Lcd_Cmd(LCD_01_ADDRESS,_LCD_CLEAR,1);
}



void initDMA_global(){
 DMACON = 1<<16;
 DCH0CON = 0x03;
}


void initDMA0(){
 DMACONbits.ON = 1;
 DCH0CONbits.CHAEN = 1;
 DCH0CONbits.CHPATLEN = 0;
 DMA0IE_bit = 0;
 DMA0IF_bit = 0;

 DCH0ECON =(146 << 8 ) | 0x30;
 DCH0DAT = 0x0D;

 DCH0SSA = KVA_TO_PA(0xBF822230);
 DCH0DSA = KVA_TO_PA(0xA0002000);

 DCH0SSIZ = 200 ;
 DCH0DSIZ = 200 ;
 DCH0CSIZ = 200 ;

 DCH0INTCLR = 0x00FF00FF ;
 CHBCIE_bit = 1 ;
 CHERIE_bit = 1 ;



 IPC33CLR = 0x0000001F ;
 DMA0IP2_bit = 1 ;
 DMA0IP1_bit = 0 ;
 DMA0IP0_bit = 1 ;
 DMA0IS1_bit = 1 ;
 DMA0IS0_bit = 1 ;

 DMA0IE_bit = 1 ;
 CHEN_bit = 1 ;

}


void initDMA1(){

 DMA1IE_bit = 0 ;
 DMA1IF_bit = 0 ;
 DCH1CONbits.CHPATLEN = 0;
 DCH1ECON=(147 << 8)| 0x30;
 DCH1SSA = KVA_TO_PA(0xA0002200) ;
 DCH1DSA = KVA_TO_PA(0xBF822220) ;
 DCH1DAT = 0x0D;

 DCH1SSIZ = 200 ;

 DCH1DSIZ = 1 ;

 DCH1CSIZ = 200 ;

 DCH1INTCLR = 0x00FF00FF ;
 CHBCIE_DCH1INT_bit = 1 ;
 CHERIE_DCH1INT_bit = 1 ;

 DMA1IP2_bit = 1 ;
 DMA1IP1_bit = 0 ;
 DMA1IP0_bit = 1 ;
 DMA1IS1_bit = 0 ;
 DMA1IS0_bit = 1 ;
 DMA1IE_bit = 1 ;
}
