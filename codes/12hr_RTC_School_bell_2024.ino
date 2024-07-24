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
int in1 = 8; 
int Min;
int Sec;
int period;
int activate=0;

void setup()
{
  rtc.begin();            // Setup RTC
  Serial.begin(9600);
  pinMode(in1,OUTPUT);
  lcd.begin();       // Setup LCD to 16x2 characters

  // To set date and time (run once only)
  // The following lines can be commented out to use the values already stored in the DS3231
  rtc.setDate(24,7,2024);
  rtc.setTime(8,59,57);
  rtc.setDOW(FRIDAY);
}


void loop()
{
 t=rtc.getTime();
 Hour = t.hour;
 Min = t.min;
 Sec = t.sec;
 day = t.dow;

//Display Date
 lcd.setCursor(0, 0);
 lcd.print(rtc.getDateStr());
//string dow;
switch (day)
 {
    case 1: lcd.setCursor(0, 12);
            lcd.print("MON");
            break;
    case 2: lcd.setCursor(0, 12);
            lcd.print("TUE");
            break;
    case 3: lcd.setCursor(0, 12);
            lcd.print("WED");
            break;
    case 4: lcd.setCursor(0, 12);
            lcd.print("THU");
            break;
    case 5: lcd.setCursor(0, 12);
            lcd.print("FRI");
            break;
    case 6: lcd.setCursor(0, 12);
            lcd.print("SAT");
            break;
    case 7: lcd.setCursor(0, 12);
            lcd.print("SUN");
            break;
    default:lcd.setCursor(0, 12);
            lcd.print("ERR");
            break;
 }    

// Display time
 //lcd.setCursor(0, 1);
 //lcd.print("Time: ");
 lcd.setCursor(5, 1);
 Serial.println(rtc.getTimeStr());
 lcd.print(rtc.getTimeStr());

//Display Period Number
lcd.setCursor(13, 1);
lcd.print("P: ");
lcd.setCursor(15, 1);
lcd.print(period);

/**********************************/
 //Monday to Thursday Time-Table
 if(day==1 || day==2 || day==3 || day==4)
 {
   if((Hour==9 && Min==0 && Sec<=1)||(Hour==9 && Min==45 && Sec<=1)||(Hour==10 && Min==40 && Sec<=1)||(Hour==11 && Min==25 && Sec<=1)||(Hour==12 && Min==10 && Sec<=1)||(Hour==13 && Min==35 && Sec<=1)||(Hour==14 && Min==30 && Sec<=1)||(Hour==15 && Min==40 && Sec<=1))
   {
     digitalWrite(in1,HIGH);
     if (activate == 0)
     {
       period = period +1;
       activate =1;
     }
   }
  else if ((Hour==10 && Min==30 && Sec<=2)||(Hour==12 && Min==50 && Sec<=2)||(Hour==15 && Min==20 && Sec<=2)||(Hour==16 && Min==12 && Sec<=2))  // Recess break time (Long ring bell)
  {
    digitalWrite(in1,HIGH);
    lcd.setCursor(11, 1);
    lcd.print("Break");
    delay(500);
    lcd.clear();
  }
//   else if ((Hour==15 && Min==25 && Sec<=2))
//   {
//    digitalWrite(in1,HIGH);
//    lcd.setCursor(9, 1);
//    lcd.print("E CLASS");
//   }
else if ((Hour==15 && Min==20 && Sec<=3)||(Hour==16 && Min==15 && Sec<=3))  // School time over (Long Ring bell)
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
 
/**********************************/
 //Friday's Time-Table
else if (day==5)   
 {
    if((Hour==9 && Min==0 && Sec<=1)||(Hour==9 && Min==45 && Sec<=1)||(Hour==10 && Min==40 && Sec<=1)||(Hour==11 && Min==25 && Sec<=1)||(Hour==12 && Min==10 && Sec<=1)||(Hour==14 && Min==0 && Sec<=1)||(Hour==14 && Min==45 && Sec<=1)||(Hour==15 && Min==40 && Sec<=1))
   {
     digitalWrite(in1,HIGH);
     if (activate == 0)
     {
       period = period +1;
       activate =1;
     }
   }
  else if ((Hour==10 && Min==30 && Sec<=2)||(Hour==12 && Min==50 && Sec<=2)||(Hour==15 && Min==20 && Sec<=2)||(Hour==16 && Min==12 && Sec<=2))  // Recess break time (Long ring bell)
  {
    digitalWrite(in1,HIGH);
    lcd.setCursor(11, 1);
    lcd.print("Break");
    delay(500);
    lcd.clear();
  }
//   else if ((Hour==15 && Min==25 && Sec<=2))
//   {
//    digitalWrite(in1,HIGH);
//    lcd.setCursor(9, 1);
//    lcd.print("E CLASS");
//   }
else if ((Hour==15 && Min==20 && Sec<=3)||(Hour==16 && Min==15 && Sec<=3))  // School time over (Long Ring bell)
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