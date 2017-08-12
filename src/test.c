#include <mylib.h>
#include <framebuffer.h>

#define NULL (void*) 0
#define true 1
#define false 0

/*
 * Functions
 */

void sleep_one_sec(void);
float sht30_convert_temperature(unsigned short value);
float sht30_convert_humidity(unsigned short value);
unsigned char goto_sleep();
unsigned char init();

static char buffer[250];

/*
 *  Globals
 */    

int main() 
{ 
  unsigned short temp;
  unsigned short humidity;
  unsigned char result;
  
  unsigned char loop_counter=0;
  
  init();
          
  while ( true ) 
  {          
    if ( ++loop_counter > 5 ) {
        loop_counter = 0;
        if ( ! goto_sleep() ) 
        {          
          print("failed to sleep...");
          framebuffer_update_display(); 
          sleep_one_sec();            
          continue;
        }            
    }
    
    framebuffer_clear();     
    cursor_home();    
    
    if ( sht30_read( &temp, &humidity ) ) 
    {
          debug_blink_red(1);      
          // read temperature
          print_float( sht30_convert_temperature( temp ) );
          println(" c");
              
          // read humidity
          print_float( sht30_convert_humidity( humidity ) );   
          println(" %");    
    } else {
        debug_blink_red(3);  
        println("error");
    }     
    framebuffer_update_display(); 
    sleep_one_sec();       
    sleep_one_sec();           
  }
  
  error:
  while (1 ) {
  }
}

unsigned char goto_sleep() 
{  
  if ( ! lcd_display_off() ) {
    debug_blink_red(4);
    return 0;
  }
  
  enter_sleepmode();
    
  init();
    
  return 1;
}

unsigned char init() 
{
  i2c_setup( LCD_ADR );
  
  if ( ! lcd_reset_display() ) {
    debug_blink_red(2);
    return 0;
  }
  
  if ( ! lcd_display_on() ) {
    debug_blink_red(3);
    return 0;
  }
  
  framebuffer_clear();    
   
  println("ready");
  framebuffer_update_display();     
  return 1;
}

float sht30_convert_temperature(unsigned short value) 
{
  float result = value;
  result = -45 + 175 * ( result / 0xffff );
  return result;
}

float sht30_convert_humidity(unsigned short value) 
{
  float result = value;
  result = 100.0 * ( result / 0xffff );
  return result;
}

void sleep_one_sec(void) 
{
  for ( unsigned char i = 5 ; i > 0  ; i--) {
    util_msleep(200);    
  }
}
