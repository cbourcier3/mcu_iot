#include "lib_lcd_backlight.h"


unsigned char _displayfunction = 0x00;
unsigned char _displaycontrol = 0x00;
 
int lcd_init(i2c_t bus)
{
       int Res;
       
       i2c_init(bus); 
             
       // Init partie LCD
       //Initialize displayfunction parameter for setting up LCD display
       _displayfunction |= LCD_2LINE;
       _displayfunction |= LCD_5x10DOTS;
       
       xtimer_usleep(30*US_PER_MS); // Wait > 30ms
        
       Res = lcd_sendcmd(bus,(LCD_FUNCTIONSET | _displayfunction));
       if (Res != 0) return  -1;
              
       xtimer_usleep(40);    // Wait > 39µs
       
       Res = lcd_displayOn(bus);
       if (Res != 0) return  -1;
       
       Res = lcd_clear(bus);
       if (Res != 0) return  -1;
       
       // Init RGB lib_lcd_backlight device
       Res = i2c_acquire(bus);
       if (Res != 0) return -1;
             
       Res = i2c_write_reg(bus,BCK_ADDR,0,0,0);
       if (Res != 0) return -1;
       
       Res = i2c_write_reg(bus,BCK_ADDR,1,0,0);
       if (Res != 0) return -1;
       
       Res = i2c_write_reg(bus,BCK_ADDR,0x08,0xAA,0);
       if (Res != 0) return -1;
       
       i2c_release(bus);

       return 0;
}
 
int    lcd_displayOn(i2c_t bus)
{
       _displaycontrol |= LCD_DISPLAYON;
       return lcd_sendcmd(bus,(LCD_DISPLAYCONTROL | _displaycontrol)); 
}
 
int    lcd_clear(i2c_t bus)
{
       return lcd_sendcmd(bus,LCD_CLEARDISPLAY); 
}

int lcd_sendcmd(i2c_t bus,unsigned char cmd)
{
       int Res = 0;
       Res = i2c_acquire(bus);
       if (Res != 0) return -1;
       Res = i2c_write_reg(bus, LCD_ADDR,CMD_REG, cmd, 0);
       if (Res != 0) return -1;
       i2c_release(bus);
       return Res;
}

int lcd_setRGB(i2c_t bus,unsigned char Red,unsigned char Green,unsigned char Blue)
{
       int Res = 0;
       Res = i2c_acquire(bus);
       if (Res != 0) return -1;
       Res = i2c_write_reg(bus, BCK_ADDR,BLUE_REG, Blue, 0);
       if (Res != 0) return -1;
       Res = i2c_write_reg(bus, BCK_ADDR,RED_REG, Red, 0);
       if (Res != 0) return -1;
       Res = i2c_write_reg(bus, BCK_ADDR,GREEN_REG, Green, 0);
       if (Res != 0) return -1;
       i2c_release(bus);
       return Res;
}


int lcd_putch(i2c_t bus,unsigned char Car)
{
       int Res = 0;
       Res = i2c_acquire(bus);
       if (Res != 0) return -1;
       Res = i2c_write_reg(bus, LCD_ADDR, DATA_REG, Car, 0);
       if (Res != 0) return -1;
       i2c_release(bus);
       return Res;
}

int lcd_puts(i2c_t bus,unsigned char *pCar)
{
       int Res = 0;
       for (int i =0; i< 16; i++)
       {
              if(pCar[i]!='\0')
                    Res = lcd_putch(bus,pCar[i]);
              else break; 
       }
       return Res;
}
