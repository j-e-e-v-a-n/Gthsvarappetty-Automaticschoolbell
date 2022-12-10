 /* 
Connect SDA and SCL pins of RTC DS3231 to pins A4 and A5 of Arduino Uno board.
You can find the latest version of the library of DS3231 at  http://www.RinkyDinkElectronics.com/
*/
#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>

//LCD pin to Arduino

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

DS3231 rtc(SDA,SCL);
Time t;
int day; // MONDAY=1,TUESDAY=2, WEDNESDAY=3,THURSDAY=4, FRIDAY=5, SATURDAY=6, SUNDAY=7
int Hour;
int Min;
int Sec;
int h;     //for 12 hour time format
int period;
int activate=0;
int in1 = 8; 

void setup()
{
  rtc.begin();            // Setup RTC
  Serial.begin(9600);
  pinMode(in1,OUTPUT);
  lcd.begin();       // Setup LCD to 16x2 characters

  // To set date and time (run once only)
  // The following lines can be commented out to use the values already stored in the DS3231
  // rtc.setDate(9,12,2022);
  // rtc.setTime(13,23,30);
  // rtc.setDOW(FRIDAY);
}
void loop()
{
 t=rtc.getTime();
 Hour = t.hour;
 Min = t.min;
 Sec = t.sec;
 day = t.dow;
 h = t.hour;        //for 12 hour time format
  if(h==12)
    {
      AM=0;
    }
  else if (h>12)
    {
      AM=0;
      h=h-12;
    }
 else if (h==0)
    {
      AM=1;
      h=12;
    } 

 // Display time
 lcd.setCursor(0, 0);
 lcd.print("Time: ");
 lcd.setCursor(5, 0);
 lcd.print(h);  
 lcd.setCursor(7, 0);
 lcd.print(":");
 lcd.setCursor(8, 0);
 lcd.print(Min);
 lcd.setCursor(10, 0);
 lcd.print(":");
 lcd.setCursor(11, 0);
 lcd.print(Sec);
 
 if(AM==1)
  {
    lcd.setCursor(14, 0);
    lcd.print("AM");
  }
 else
  {
    lcd.setCursor(14, 0);
    lcd.print("PM");
  }
 
 //Display Date
 lcd.setCursor(0, 1);
 lcd.print(rtc.getDateStr());

//Display Period Number
lcd.setCursor(13, 1);
lcd.print("P: ");
lcd.setCursor(15, 1);
lcd.print(period);

 //Monday to Thursday Time-Table
 if(day==1 || day==2 || day==3 || day==4)
 {
   if((Hour==9 && Min==0 && Sec<=1)||(Hour==9 && Min==55 && Sec<=1)||(Hour==10 && Min==50 && Sec<=1)||(Hour==11 && Min==35 && Sec<=1)||(Hour==12 && Min==50 && Sec<=1)||(Hour==13 && Min==25 && Sec<=1)||(Hour==14 && Min==5 && Sec<=1)||(Hour==15 && Min==40 && Sec<=1))
   {
     digitalWrite(in1,HIGH);
     if (activate == 0)
     {
       period = period +1;
       activate =1;
     }
   }
  else if ((Hour==10 && Min==40 && Sec<=2)||(Hour==12 && Min==20 && Sec<=2)||(Hour==14 && Min==0 && Sec<=2)||(Hour==15 && Min==20 && Sec<=2)||(Hour==16 && Min==12 && Sec<=2))  // Recess break time (Long ring bell)
  {
    digitalWrite(in1,HIGH);
    lcd.setCursor(11, 1);
    lcd.print("Break");
    delay(500);
    lcd.clear();
  }
   else if ((Hour==15 && Min==25 && Sec<=2))
   {
    digitalWrite(in1,HIGH);
    lcd.setCursor(9, 1);
    lcd.print("E CLASS");
   }
else if ((Hour==16 && Min==15 && Sec<=3))  // School time over (Long Ring bell)
  {
    digitalWrite(in1,HIGH);
    lcd.setCursor(11, 1);
    lcd.print("Over");
    period =0;
    delay(500);
    lcd.clear();
  }

else 
  { 
    digitalWrite(in1,LOW);
    activate =0;
  }
 }
 

 //Friday's Time-Table
else if (day==5)   
 {
    if((Hour==9 && Min==0 && Sec<=1)||(Hour==9 && Min==50 && Sec<=1)||(Hour==10 && Min==35 && Sec<=1)||(Hour==11 && Min==15 && Sec<=1)||(Hour==11 && Min==55 && Sec<=1)||(Hour==13 && Min==50 && Sec<=1)||(Hour==14 && Min==20 && Sec<=1)||(Hour==14 && Min==50 && Sec<=1)||(Hour==15 && Min==20 && Sec<=1))
    {
     digitalWrite(in1,HIGH);
     if (activate == 0)
      {
       period = period +1;
      activate =1;
      }
    }
    else if ((Hour==10 && Min==30 && Sec<=1)||(Hour==12 && Min==35 && Sec<=1)||(Hour==14 && Min==50 && Sec<=1)||(Hour==15 && Min==20 && Sec<=1)||(Hour==16 && Min==12 && Sec<=1))  // Recess break time (Long ring bell)
    {
      digitalWrite(in1,HIGH);
      lcd.setCursor(11, 1);
      lcd.print("Break");
      delay(500);
      lcd.clear();
    }
    else if ((Hour==15 && Min==25 && Sec<=2))
    {
      digitalWrite(in1,HIGH);
      lcd.setCursor(9, 1);
      lcd.print("E CLASS");
    }
    else if ((Hour==16 && Min==15 && Sec<=3))  // School time over (Long Ring bell)
    {
      digitalWrite(in1,HIGH);
      lcd.setCursor(11, 1);
      lcd.print("Over");
      period =0;
      delay(500);
      lcd.clear();
    }
    else 
    { 
      digitalWrite(in1,LOW);
      activate =0;
    }
  }
else
 {
  

  }

 }