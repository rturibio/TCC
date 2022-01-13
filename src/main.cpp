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

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char *ssid     = "Mokinho3";
const char *password = "lianei1965";
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = -10800;  // set offset
NTPClient timeClient(ntpUDP, "south-america.pool.ntp.org", utcOffsetInSeconds);
char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};  
int ver_wifi = 0;
int buttonState = 0;
int var = 0;
int var2 = 0;
int h1med1, m1med1,h2med1, m2med1,h3med1, m3med1,h4med1, m4med1,h5med1, m5med1= 0;
int hora = 0;
int minn = 0;
int segg = 0;
int led = 26;
int countdown_time = 0;

void config_lcd();
void rtc_off();
void rtc_conf();
void ver_horario();

String str1,str2,str3,str4,str5,str6 = "";
String nmed1, horamed11,horamed12,horamed13,horamed14,horamed15 = "";
String tobesend;
String message = "";
char incomingChar;
String stringOne = "";
String teste = "";
String serialResponse = "";

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

void setup(){
  pinMode(19, OUTPUT);
  pinMode(18, INPUT);
  digitalWrite(19,HIGH);
  config_lcd();
  pinMode (led, OUTPUT);

SerialBT.begin("ESP32_Bluetooth_Rian"); //Bluetooth device name
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
 
 timeClient.begin();
}

void loop() {
  buttonState = digitalRead(18);
  
  if (countdown_time == 86400)
  {
   Serial.println("Reconnecting to WiFi...");
   WiFi.disconnect();
   WiFi.reconnect();
   countdown_time = 0;
  }
  

  if (buttonState == 1)
  {
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
    }
 }

 if (var == 99)
 {

  String stringtwo = teste;
  char Buf[100];
  stringtwo.toCharArray(Buf, 100);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
  char str1[15] = "";
  char str2[15] = "";
  char str3[15] = "";
  char str4[15] = "";
  char str5[15] = "";
  char str6[15] = "";

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
  strtokIndx = strtok(NULL, "");
  strcpy(str6,strtokIndx);


  Serial.println("");
  Serial.println(str1);
  Serial.println(str2);
  Serial.println(str3);
  Serial.println(str4);
  Serial.println(str5);  
  Serial.println(str6);

  nmed1 = str1;
  horamed11 = str2;
  horamed12 = str3;
  horamed13 = str4;
  horamed14 = str5;
  horamed15 = str6;

 // char strH1med1[15] = "";
 // char strM1med1[15] = "";
 // char strH2med1[15] = "";
 // char strM2med1[15] = "";
 // char strH3med1[15] = "";
 // char strM3med1[15] = "";
 // char strH4med1[15] = "";
 // char strM4med1[15] = "";
 // char strH5med1[15] = "";
 // char strM5med1[15] = "";
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

  Serial.println(strH1med1);
  Serial.println(strM1med1);
  Serial.println(strH2med1);
  Serial.println(strM2med1); 
  Serial.println(strH3med1);
  Serial.println(strM4med1); 
  Serial.println(strH4med1);
  Serial.println(strM4med1); 
  Serial.println(strH5med1);
  Serial.println(strM5med1);    

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
  digitalWrite (led, LOW);
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

//######### Verificador de Hora/Min/Seg
if(hora == nstrH1med1 && minn == nstrM1med1 && segg == 01)
{
digitalWrite (led, HIGH);
Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+554896092817";
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed1);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed11);
tobesend = tobesend + "&apikey=826148";
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
digitalWrite (led, HIGH);
Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+554896092817";
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed1);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed12);
tobesend = tobesend + "&apikey=826148";
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
digitalWrite (led, HIGH);
Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+554896092817";
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed1);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed13);
tobesend = tobesend + "&apikey=826148";
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
digitalWrite (led, HIGH);
Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+554896092817";
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed1);
tobesend = tobesend + "+Horario+-+";
tobesend = tobesend + String(horamed14);
tobesend = tobesend + "&apikey=826148";
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
digitalWrite (led, HIGH);
Serial.print("connecting to ");
Serial.println("whatsapp");
HTTPClient http; //Declare an object of class HTTPClient
//Specify request destination
tobesend = "http://api.callmebot.com/whatsapp.php?";
tobesend = tobesend + "phone=+554896092817";
tobesend = tobesend + "&text=Medicamento+Dispensado+:+";
tobesend = tobesend + String(nmed1);
tobesend = tobesend + "+Horario+:+";
tobesend = tobesend + String(horamed15);
tobesend = tobesend + "&apikey=826148";
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
   Serial.println("Reconnecting to WiFi...");
   WiFi.disconnect();
   WiFi.reconnect();
   delay(1000);
   countdown_time = countdown_time + 1;
  }