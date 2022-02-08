#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NTPClient.h>
#include <WiFi.h>
#include "RTClib.h"
#include "time.h"
#include "BluetoothSerial.h"
#include <LiquidCrystal_I2C.h>
#include <HTTPClient.h>
#include <Servo.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define SERVO_PIN1 4
#define SERVO_PIN2 13
#define SERVO_PIN3 12
#define SERVO_PIN4 14
#define SERVO_PIN5 27

Servo servoMotor1;
Servo servoMotor2;
Servo servoMotor3;
Servo servoMotor4;
Servo servoMotor5;

BluetoothSerial SerialBT;
RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char *ssid     = "";
const char *password = "";
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = -10800;  // set offset
NTPClient timeClient(ntpUDP, "south-america.pool.ntp.org", utcOffsetInSeconds);
char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};  
int ver_wifi = 0;
int buttonState = 0;
int buttonState2 = 0;
int roda3 = 0;
int roda1 = 0;
int roda2 = 0;
int roda4 = 0;
int roda5 = 0;
int buttontest = 0;
int ver = 0;
int var = 0;
int var2 = 0;
int h1med1, m1med1,h2med1, m2med1,h3med1, m3med1,h4med1, m4med1,h5med1, m5med1= 0;
int hora = 0;
int minn = 0;
int segg = 0;
int countdown_time = 0;
int i = 0;
int menu = 0;
int countwifi =0;
int countinsert = 0;
int r1 = 0, r2 = 0, r3 = 0, r4 = 0 , r5 = 0;
int pos1 = 0,pos2 = 0,pos3 = 0,pos4 = 0,pos5 = 0;
int pos = 0;
int angulo = 0;

void config_lcd();
void rtc_off();
void rtc_conf();
void ver_horario();

String str1,str2,str3,str4,str5,str6,str7,str8,str9,str10  = "";
String str11,str12,str13,str14,str15,str16,str17,str18,str19,str20  = "";
String str21,str22,str23,str24,str25,str26,str27,str28,str29,str30  = "";
String nmed1, horamed11,horamed12,horamed13,horamed14,horamed15 = "";
String nmed2, horamed21,horamed22,horamed23,horamed24,horamed25 = "";
String nmed3, horamed31,horamed32,horamed33,horamed34,horamed35 = "";
String nmed4, horamed41,horamed42,horamed43,horamed44,horamed45 = "";
String nmed5, horamed51,horamed52,horamed53,horamed54,horamed55 = "";
String nwifi, swifi = "";
String tobesend;
String message = "";
char incomingChar;
String stringOne = "";
String teste = "";
String serialResponse = "";
String tel , apkey= "";
char myStg[10];
char myStg2[10];
char myStg3[10];
char myStg4[10];
char myStg5[10];

  char strH1med1[15] = "";
  char strM1med1[15] = "";
  char strH2med1[15] = "";
  char strM2med1[15] = "";
  char strH3med1[15] = "";
  char strM3med1[15] = "";
  char strH4med1[15] = "";
  char strM4med1[15] = "";
  char strH5med1[15] = "";
  char strM5med1[15] = "";

  char strH1med2[15] = "";
  char strM1med2[15] = "";
  char strH2med2[15] = "";
  char strM2med2[15] = "";
  char strH3med2[15] = "";
  char strM3med2[15] = "";
  char strH4med2[15] = "";
  char strM4med2[15] = "";
  char strH5med2[15] = "";
  char strM5med2[15] = "";

  char strH1med3[15] = "";
  char strM1med3[15] = "";
  char strH2med3[15] = "";
  char strM2med3[15] = "";
  char strH3med3[15] = "";
  char strM3med3[15] = "";
  char strH4med3[15] = "";
  char strM4med3[15] = "";
  char strH5med3[15] = "";
  char strM5med3[15] = "";

  char strH1med4[15] = "";
  char strM1med4[15] = "";
  char strH2med4[15] = "";
  char strM2med4[15] = "";
  char strH3med4[15] = "";
  char strM3med4[15] = "";
  char strH4med4[15] = "";
  char strM4med4[15] = "";
  char strH5med4[15] = "";
  char strM5med4[15] = "";

  char strH1med5[15] = "";
  char strM1med5[15] = "";
  char strH2med5[15] = "";
  char strM2med5[15] = "";
  char strH3med5[15] = "";
  char strM3med5[15] = "";
  char strH4med5[15] = "";
  char strM4med5[15] = "";
  char strH5med5[15] = "";
  char strM5med5[15] = "";

void setup(){
  pinMode(19, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(18, INPUT);
  pinMode(23, INPUT);
  pinMode(32, INPUT_PULLDOWN);
  pinMode(35, INPUT_PULLDOWN);
  pinMode(34, INPUT_PULLDOWN);
  pinMode(25, INPUT_PULLDOWN);
  pinMode(26, INPUT_PULLDOWN);
  digitalWrite(19,HIGH);
  digitalWrite(5,HIGH);
  config_lcd();
  servoMotor1.attach(SERVO_PIN1);
  servoMotor2.attach(SERVO_PIN2);
  servoMotor3.attach(SERVO_PIN3);
  servoMotor4.attach(SERVO_PIN4);
  servoMotor5.attach(SERVO_PIN5);

SerialBT.begin("ESP32_Bluetooth"); //Bluetooth device name
WiFi.begin(ssid, password);

  
  for (int i = 0; i <= 5; i++){
  if ( WiFi.status() != WL_CONNECTED ) 
  {
    delay ( 1000 );
    Serial.print ( "." );
    ver_wifi = 1;
  
 }
}
if ( WiFi.status() != WL_CONNECTED ){ 
 
 rtc_off();
 ver_wifi = 0;
}
 
 timeClient.begin();
}

void loop() {
  
  buttonState = digitalRead(18);
  buttonState2 = digitalRead(23);
  roda3 = digitalRead(32);
  roda1 = digitalRead(35);
  roda2 = digitalRead(34);
  roda4 = digitalRead(25);
  roda5 = digitalRead(26);

  if (countdown_time == 3600)
  {
   Serial.println("Reconnecting to WiFi...");
   WiFi.disconnect();
   WiFi.reconnect();
   countdown_time = 0;
  }

  if (buttonState == 1)
  {
    //Serial.println("Chave bluetooth Ligada");
    while (SerialBT.available()){
    char incomingChar = SerialBT.read();
    stringOne += incomingChar;
    if (incomingChar != '\n'){
      lcd.clear();  
      message += String(incomingChar);
    } else {
      message = "";
    }
      //Serial.println(message);
      teste = message;
      //Serial.println(teste);
      var = 99;
      countwifi = 1;
    }
 }

  if (buttonState2 == 1)
  {
    //#############################################################################
    
    Serial.println("Funcao de insercao de medicamentos");
    lcd.clear();
    lcd.setCursor (0,0); //   column, row
    lcd.print("Insercao de");
    lcd.setCursor (0,1); //   column, row
    lcd.print("Medicamentos");
    delay(3000);  

  for (size_t i = 0; i < 30; i++)
  {
    lcd.clear();
    lcd.setCursor (0,0); //   column, row
    lcd.print("R1:");
    lcd.setCursor (3,0); //   column, row
    lcd.print(r1);

    lcd.setCursor (6,0); //   column, row
    lcd.print("R2:");
    lcd.setCursor (9,0); //   column, row
    lcd.print(r2);

    lcd.setCursor (12,0); //   column, row
    lcd.print("R3:");
    lcd.setCursor (12,1); //   column, row
    lcd.print(r3);

    lcd.setCursor (0,1); //   column, row
    lcd.print("R4:");
    lcd.setCursor (3,1); //   column, row
    lcd.print(r4);

    lcd.setCursor (6,1); //   column, row
    lcd.print("R5:");
    lcd.setCursor (9,1); //   column, row
    lcd.print(r5);
  
  roda3 = digitalRead(32);
  roda1 = digitalRead(35);
  roda2 = digitalRead(34);
  roda4 = digitalRead(25);
  roda5 = digitalRead(26);

  if (roda1 == 1)
  {
    Serial.println("Roda 1");
    r1 = r1 +1 ;
    Serial.println(r1);
    
    if(r1 == 31){
      r1 = 0;
    }
    servoMotor1.write(93); //clockwise rotation
    delay(95); //rotation duration in ms
    servoMotor1.detach(); //detach servo to prevent “creeping” effect
    delay(125); //short pause
    servoMotor1.attach(SERVO_PIN1); //reattach servo to pin 
  }

  if (roda2 == 1)
  {

    Serial.println("Roda 2");
    r2 = r2 +1 ;
    Serial.println(r2);
    if(r2 == 31){
      r2 = 0;
    }
    servoMotor2.write(93); //clockwise rotation
    delay(95); //rotation duration in ms
    servoMotor2.detach(); //detach servo to prevent “creeping” effect
    delay(125); //short pause
    servoMotor2.attach(SERVO_PIN2); //reattach servo to pin 
  }

  if (roda3 == 1)
  {

    Serial.println("Roda 3");
    r3 = r3 + 1 ;
    Serial.println(r3);
    if(r3 == 31){
      r3 = 0;
    }
    servoMotor3.write(93); //clockwise rotation
    delay(95); //rotation duration in ms
    servoMotor3.detach(); //detach servo to prevent “creeping” effect
    delay(125); //short pause
    servoMotor3.attach(SERVO_PIN3); //reattach servo to pin 
  }  

    if (roda4 == 1)
  {

    Serial.println("Roda 4");
    r4 = r4 +1 ;
    Serial.println(r4);
    if(r4 == 31){
      r4 = 0;
    }
    servoMotor4.write(93); //clockwise rotation
    delay(95); //rotation duration in ms
    servoMotor4.detach(); //detach servo to prevent “creeping” effect
    delay(125); //short pause
    servoMotor4.attach(SERVO_PIN4); //reattach servo to pin 
  }
   
   if (roda5 == 1)
  {

    Serial.println("Roda 5");
    r5 = r5 +1 ;
    Serial.println(r5);
    if(r5 == 31){
      r5 = 0;
    }
    servoMotor5.write(93); //clockwise rotation
    delay(95); //rotation duration in ms
    servoMotor5.detach(); //detach servo to prevent “creeping” effect
    delay(125); //short pause
    servoMotor5.attach(SERVO_PIN5); //reattach servo to pin 
  }

   delay(1000);
   countinsert = countinsert +1;

  }
  countinsert = 0;
 }

 if (var == 99)
 {

  String stringtwo = teste;
  char Buf[250];
  stringtwo.toCharArray(Buf, 250);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
  char str1[15] = "";
  char str2[15] = "";
  char str3[15] = "";
  char str4[15] = "";
  char str5[15] = "";
  char str6[15] = "";
  char str7[15] = "";
  char str8[15] = "";
  char str9[15] = "";
  char str10[15] = "";

  char str11[15] = "";
  char str12[15] = "";
  char str13[15] = "";
  char str14[15] = "";
  char str15[15] = "";
  char str16[15] = "";
  char str17[15] = "";
  char str18[15] = "";
  char str19[15] = "";
  char str20[15] = "";

  char str21[15] = "";
  char str22[15] = "";
  char str23[15] = "";
  char str24[15] = "";
  char str25[15] = "";
  char str26[15] = "";
  char str27[15] = "";
  char str28[15] = "";
  char str29[15] = "";
  char str30[15] = "";
  char str31[15] = "";
  char str32[15] = "";
  char str33[15] = "";
  char str34[15] = "";

  char* strtokIndx;
  strtokIndx = strtok(Buf, "-");
  strcpy(str1,strtokIndx);
  strtokIndx = strtok(NULL,"-");
  strcpy(str2,strtokIndx);
  strtokIndx = strtok(NULL,"-");
  strcpy(str3,strtokIndx);
  strtokIndx = strtok(NULL,"-");
  strcpy(str4,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str5,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str6,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str7,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str8,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str9,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str10,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str11,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str12,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str13,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str14,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str15,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str16,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str17,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str18,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str19,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str20,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str21,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str22,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str23,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str24,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str25,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str26,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str27,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str28,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str29,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str30,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str31,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str32,strtokIndx);
  strtokIndx = strtok(NULL, "-");
  strcpy(str33,strtokIndx);
  strtokIndx = strtok(NULL, "");
  strcpy(str34,strtokIndx);

  nmed1 = str1;
  horamed11 = str2;
  horamed12 = str3;
  horamed13 = str4;
  horamed14 = str5;
  horamed15 = str6;

  nmed2 = str7;
  horamed21 = str8;
  horamed22 = str9;
  horamed23 = str10;
  horamed24 = str11;
  horamed25 = str12;

  nmed3 = str13;
  horamed31 = str14;
  horamed32 = str15;
  horamed33 = str16;
  horamed34 = str17;
  horamed35 = str18;

  nmed4 = str19;
  horamed41 = str20;
  horamed42 = str21;
  horamed43 = str22;
  horamed44 = str23;
  horamed45 = str24;

  nmed5 = str25;
  horamed51 = str26;
  horamed52 = str27;
  horamed53 = str28;
  horamed54 = str29;
  horamed55 = str30;

  ssid = str31;
  password = str32;

  tel = str33;
  apkey = str34;

  char* strtokIndx2;

  strtokIndx2 = strtok(str2, ":");
  strcpy(strH1med1,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM1med1,strtokIndx2);

  strtokIndx2 = strtok(str3, ":");
  strcpy(strH2med1,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM2med1,strtokIndx2);

  strtokIndx2 = strtok(str4, ":");
  strcpy(strH3med1,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM3med1,strtokIndx2);

  strtokIndx2 = strtok(str5, ":");
  strcpy(strH4med1,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM4med1,strtokIndx2);

  strtokIndx2 = strtok(str6, ":");
  strcpy(strH5med1,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM5med1,strtokIndx2);

  //############

  strtokIndx2 = strtok(str8, ":");
  strcpy(strH1med2,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM1med2,strtokIndx2);

  strtokIndx2 = strtok(str9, ":");
  strcpy(strH2med2,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM2med2,strtokIndx2);

  strtokIndx2 = strtok(str10, ":");
  strcpy(strH3med2,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM3med2,strtokIndx2);

  strtokIndx2 = strtok(str11, ":");
  strcpy(strH4med2,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM4med2,strtokIndx2);

  strtokIndx2 = strtok(str12, ":");
  strcpy(strH5med2,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM5med2,strtokIndx2);

  //$$$$$$$$$$$$$$$$$$$$$$$$$$$

  strtokIndx2 = strtok(str14, ":");
  strcpy(strH1med3,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM1med3,strtokIndx2);

  strtokIndx2 = strtok(str15, ":");
  strcpy(strH2med3,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM2med3,strtokIndx2);

  strtokIndx2 = strtok(str16, ":");
  strcpy(strH3med3,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM3med3,strtokIndx2);

  strtokIndx2 = strtok(str17, ":");
  strcpy(strH4med3,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM4med3,strtokIndx2);

  strtokIndx2 = strtok(str18, ":");
  strcpy(strH5med3,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM5med3,strtokIndx2);

  //&&&&&&&&&&&&&&&&&&&&&

  strtokIndx2 = strtok(str20, ":");
  strcpy(strH1med4,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM1med4,strtokIndx2);

  strtokIndx2 = strtok(str21, ":");
  strcpy(strH2med4,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM2med4,strtokIndx2);

  strtokIndx2 = strtok(str22, ":");
  strcpy(strH3med4,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM3med4,strtokIndx2);

  strtokIndx2 = strtok(str23, ":");
  strcpy(strH4med4,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM4med4,strtokIndx2);

  strtokIndx2 = strtok(str24, ":");
  strcpy(strH5med4,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM5med4,strtokIndx2);

  //%%%%%%%%%%%%%%%%%%%%%%%%%%
  
  strtokIndx2 = strtok(str26, ":");
  strcpy(strH1med5,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM1med5,strtokIndx2);

  strtokIndx2 = strtok(str27, ":");
  strcpy(strH2med5,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM2med5,strtokIndx2);

  strtokIndx2 = strtok(str28, ":");
  strcpy(strH3med5,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM3med5,strtokIndx2);

  strtokIndx2 = strtok(str29, ":");
  strcpy(strH4med5,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM4med5,strtokIndx2);

  strtokIndx2 = strtok(str30, ":");
  strcpy(strH5med5,strtokIndx2);
  strtokIndx2 = strtok(NULL,"\n\t");
  strcpy(strM5med5,strtokIndx2);   

  var = 1; 
 }

  //######### Funcionando
  if(ver_wifi == 0){
  rtc_conf();
  }else{  
  timeClient.update();
  lcd.clear();
  lcd.setCursor (0,1); //   column, row
  lcd.print(daysOfTheWeek[timeClient.getDay()]);
  lcd.setCursor (8,1); //   column, row
  lcd.print(timeClient.getFormattedTime());
  hora = timeClient.getHours();
  minn = timeClient.getMinutes();
  segg = timeClient.getSeconds();
  delay(1000);

  countdown_time = countdown_time + 1;
  //#########
   
  }

int str_len = nmed1.length()+ 1;
char Newnmed1[str_len];
nmed1.toCharArray(Newnmed1, str_len);

int nstrH1med1 = atoi(strH1med1);
int nstrM1med1 = atoi(strM1med1);
int nstrH2med1 = atoi(strH2med1);
int nstrM2med1 = atoi(strM2med1);
int nstrH3med1 = atoi(strH3med1);
int nstrM3med1 = atoi(strM3med1);
int nstrH4med1 = atoi(strH4med1);
int nstrM4med1 = atoi(strM4med1);
int nstrH5med1 = atoi(strH5med1);
int nstrM5med1 = atoi(strM5med1);

int nstrH1med2 = atoi(strH1med2);
int nstrM1med2 = atoi(strM1med2);
int nstrH2med2 = atoi(strH2med2);
int nstrM2med2 = atoi(strM2med2);
int nstrH3med2 = atoi(strH3med2);
int nstrM3med2 = atoi(strM3med2);
int nstrH4med2 = atoi(strH4med2);
int nstrM4med2 = atoi(strM4med2);
int nstrH5med2 = atoi(strH5med2);
int nstrM5med2 = atoi(strM5med2);

int nstrH1med3 = atoi(strH1med3);
int nstrM1med3 = atoi(strM1med3);
int nstrH2med3 = atoi(strH2med3);
int nstrM2med3 = atoi(strM2med3);
int nstrH3med3 = atoi(strH3med3);
int nstrM3med3 = atoi(strM3med3);
int nstrH4med3 = atoi(strH4med3);
int nstrM4med3 = atoi(strM4med3);
int nstrH5med3 = atoi(strH5med3);
int nstrM5med3 = atoi(strM5med3);

int nstrH1med4 = atoi(strH1med4);
int nstrM1med4 = atoi(strM1med4);
int nstrH2med4 = atoi(strH2med4);
int nstrM2med4 = atoi(strM2med4);
int nstrH3med4 = atoi(strH3med4);
int nstrM3med4 = atoi(strM3med4);
int nstrH4med4 = atoi(strH4med4);
int nstrM4med4 = atoi(strM4med4);
int nstrH5med4 = atoi(strH5med4);
int nstrM5med4 = atoi(strM5med4);

int nstrH1med5 = atoi(strH1med5);
int nstrM1med5 = atoi(strM1med5);
int nstrH2med5 = atoi(strH2med5);
int nstrM2med5 = atoi(strM2med5);
int nstrH3med5 = atoi(strH3med5);
int nstrM3med5 = atoi(strM3med5);
int nstrH4med5 = atoi(strH4med5);
int nstrM4med5 = atoi(strM4med5);
int nstrH5med5 = atoi(strH5med5);
int nstrM5med5 = atoi(strM5med5);



//######### Verificador de Hora/Min/Seg
if(hora == nstrH1med1 && minn == nstrM1med1 && segg == 01)
{

servoMotor1.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor1.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor1.attach(SERVO_PIN1); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed1);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed11);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH2med1 && minn == nstrM2med1 && segg == 01)
{

servoMotor1.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor1.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor1.attach(SERVO_PIN1); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed1);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed12);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH3med1 && minn == nstrM3med1 && segg == 01)
{

servoMotor1.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor1.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor1.attach(SERVO_PIN1); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed1);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed13);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH4med1 && minn == nstrM4med1 && segg == 01)
{

servoMotor1.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor1.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor1.attach(SERVO_PIN1); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed1);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed14);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH5med1 && minn == nstrM5med1 && segg == 01)
{

servoMotor1.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor1.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor1.attach(SERVO_PIN1); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&apikey="+ String(apkey);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed1);
tobesend = tobesend + "+Horario+:+";
tobesend = tobesend + String(horamed15);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request
if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

//segunda verificacao
if(hora == nstrH1med2 && minn == nstrM1med2 && segg == 01)
{

servoMotor2.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor2.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor2.attach(SERVO_PIN2); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed2);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed21);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH2med2 && minn == nstrM2med2 && segg == 01)
{

servoMotor2.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor2.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor2.attach(SERVO_PIN2); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed2);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed22);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH3med2 && minn == nstrM3med2 && segg == 01)
{

servoMotor2.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor2.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor2.attach(SERVO_PIN2); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed2);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed23);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH4med2 && minn == nstrM4med2 && segg == 01)
{

servoMotor2.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor2.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor2.attach(SERVO_PIN2); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed2);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed24);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH5med2 && minn == nstrM5med2 && segg == 01)
{

servoMotor2.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor2.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor2.attach(SERVO_PIN2); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed2);
tobesend = tobesend + "+Horario+:+";
tobesend = tobesend + String(horamed25);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

//terceira verificacao
if(hora == nstrH1med3 && minn == nstrM1med3 && segg == 01)
{

servoMotor3.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor3.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor3.attach(SERVO_PIN3); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed3);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed31);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH2med3 && minn == nstrM2med3 && segg == 01)
{

servoMotor3.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor3.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor3.attach(SERVO_PIN3); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed3);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed32);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH3med3 && minn == nstrM3med3 && segg == 01)
{

servoMotor3.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor3.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor3.attach(SERVO_PIN3); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed3);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed33);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH4med3 && minn == nstrM4med3 && segg == 01)
{

servoMotor3.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor3.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor3.attach(SERVO_PIN3); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed3);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed34);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH5med3 && minn == nstrM5med3 && segg == 01)
{

servoMotor3.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor3.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor3.attach(SERVO_PIN3); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed3);
tobesend = tobesend + "+Horario+:+";
tobesend = tobesend + String(horamed35);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

//quarta verificacao
if(hora == nstrH1med4 && minn == nstrM1med4 && segg == 01)
{

servoMotor4.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor4.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor4.attach(SERVO_PIN4); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed4);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed41);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH2med4 && minn == nstrM2med4 && segg == 01)
{

servoMotor4.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor4.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor4.attach(SERVO_PIN4); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed4);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed42);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH3med4 && minn == nstrM3med4 && segg == 01)
{

servoMotor4.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor4.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor4.attach(SERVO_PIN4); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed4);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed43);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH4med4 && minn == nstrM4med4 && segg == 01)
{

servoMotor4.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor4.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor4.attach(SERVO_PIN4); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed4);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed44);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH5med4 && minn == nstrM5med4 && segg == 01)
{

servoMotor4.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor4.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor4.attach(SERVO_PIN4); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed4);
tobesend = tobesend + "+Horario+:+";
tobesend = tobesend + String(horamed45);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

//quinta verificacao
if(hora == nstrH1med5 && minn == nstrM1med5 && segg == 01)
{

servoMotor5.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor5.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor5.attach(SERVO_PIN5); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed5);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed51);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH2med5 && minn == nstrM2med5 && segg == 01)
{

servoMotor5.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor5.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor5.attach(SERVO_PIN5); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed5);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed52);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH3med5 && minn == nstrM3med5 && segg == 01)
{

servoMotor5.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor5.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor5.attach(SERVO_PIN5); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed5);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed53);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH4med5 && minn == nstrM4med5 && segg == 01)
{

servoMotor5.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor5.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor5.attach(SERVO_PIN5); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed5);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed54);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}

if(hora == nstrH5med5 && minn == nstrM5med5 && segg == 01)
{

servoMotor5.write(93); //clockwise rotation
delay(95); //rotation duration in ms
servoMotor5.detach(); //detach servo to prevent “creeping” effect
delay(125); //short pause
servoMotor5.attach(SERVO_PIN5); //reattach servo to pin 

Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+55";
tobesend = tobesend + String(tel);
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed5);
tobesend = tobesend + "+Horario+:+";
tobesend = tobesend + String(horamed55);
tobesend = tobesend + "&apikey="+ String(apkey);
http.begin(tobesend);
int httpCode = http.GET(); //Send the request

if (httpCode > 0)
{
//Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}

http.end(); //Close connection
}


if (countwifi == 1)
{
  WiFi.begin(ssid, password);

  
  for (int i = 0; i <= 10; i++){
  if ( WiFi.status() != WL_CONNECTED ) 
  {
    delay ( 1000 );
    Serial.print ( "." );
    ver_wifi = 1;
  
 }
}
if ( WiFi.status() != WL_CONNECTED ){ 
 
 rtc_off();
 ver_wifi = 0;
  }
  countwifi = 99;
}
//#################################
}

void config_lcd()
{
   Serial.begin(115200);
   lcd.init();
   lcd.backlight();
   lcd.clear();
   lcd.setCursor (0,0); //   column, row
   lcd.print("Buscando Horario");
   lcd.setCursor (0,1); //   column, row
   lcd.print("E Informacoes");
   delay(1000);
}

void rtc_off()
{
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void rtc_conf()
{
   DateTime now = rtc.now();
   char dateBuffer[12];

   lcd.clear();
   lcd.setCursor (0,1); //   column, row
   lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
   
   sprintf(dateBuffer,"%02u:%02u:%02u ",now.hour(),now.minute(),now.second());
   hora = now.hour();
   minn = now.minute();
   segg = now.second();

   lcd.setCursor (8,1); //   column, row
   lcd.print(dateBuffer);
   delay(1000);
   countdown_time = countdown_time + 1;
  }