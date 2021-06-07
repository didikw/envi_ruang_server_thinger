#define THINGER_SERVER "https://THINGER.SERVER.DOMAIN"

#include <ThingerESP8266.h>
#include "DHT.h"
#include "MQ135.h"

// Define and initialise the sensor
#define DHTPIN 2
#define DHTTYPE DHT11
#define RZERO 76.63
#define USERNAME "thinger_account_username"
#define DEVICE_ID "thinger_device_named"
#define DEVICE_CREDENTIAL "thinger_device_credential"

DHT dht(DHTPIN, DHTTYPE);
const int ANALOGPIN=0;
MQ135 gasSensor = MQ135(ANALOGPIN);
// Setup device details
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
float hum,temp,ppm,rzero,crzero,cppm,rstan,air1,digout1;
float air=0;
float digout;
String status0="";
String status1="";

void setup() {
  // Setup WiFi
  Serial.begin(115200);
  dht.begin();
  thing.add_wifi("SSID", "SSID_PWD");
  Serial.println(WiFi.localIP());
  // Define the 'thing' with a name and data direction
   thing["dh11"] >> [](pson& out){
    out["humidity"] = hum;
    out["celsius"] = temp;
    out["ppm"] = ppm;
    out["rzero"] = rzero;
    out["crzero"] = crzero;
    out["rstan"] = rstan;
    out["cppm"] = cppm;
    out["air"] = air1;
    out["digout"] = digout1;
    out["status1"] = status0;
  };
}

void loop() {
  thing.handle();

  float h = dht.readHumidity(); //Membaca kelembaban
  float t = dht.readTemperature(); //Membaca suhu dalam satuan Celcius
  float f = dht.readTemperature(true); //Membaca suhu dalam satuan Fahrenheit
  Serial.println(hum);
  Serial.println(temp);
  float ppm1 = gasSensor.getPPM();
  float rzeroo = gasSensor.getRZero();
  float correctedrzero_ = gasSensor.getCorrectedRZero(t,h);
  float resistance_ = gasSensor.getResistance();
  float correctedppm_ = gasSensor.getCorrectedPPM(t,h);
  air = analogRead(A0);
  digout = digitalRead(0);
  
  Serial.print("ppm = ");Serial.print(ppm1);
  Serial.println(rzeroo);
  Serial.println(correctedrzero_);
  Serial.println(resistance_);
  Serial.print("cppm = ");
  Serial.print(correctedppm_);
  Serial.println(air);
  Serial.println(digout,DEC);
  if(cppm>150)
    {
      status0= "ADA ASAP";
      Serial.println(status0);
      }
      else if(cppm<150)
      {
       status0 = "AMAN"; 
       Serial.println(status0);
        }
  
  delay(3600);
  //digitalWrite(D0, LOW);
  
  hum = h;
  temp = t;
  ppm = ppm1;
  rzero = rzeroo;
  crzero = correctedrzero_;
  rstan = resistance_;
  cppm = correctedppm_;
  air1 = air;
  digout1 = digout;
  status1 = status0;
}
