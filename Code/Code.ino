#define BLYNK_PRINT Serial 
#include <Adafruit_Sensor.h>
#include <DHT.h>                      //Including the DHT library
#include <ESP8266WiFi.h>              //Including the ESP8266 WiFi library in order to usm them
#include <BlynkSimpleEsp8266.h>       //library for linking up Blynk with ESP8266
#include <Wire.h>                     //For using I2C connection of BMP180 in order to connect it to the board
#include <Adafruit_BMP085.h> 

Adafruit_BMP085 bmp;                  //Defining the object bmp
#define I2C_SCL 14                    //Connect SCL pin of BMP180 to GPIO14 of Nodemcu
#define I2C_SDA 12                    //Connect SDA pin of BMP180 to GPIO12 of Nodemcu

char auth[] = "aaaaaaaaaaaaa"; //Enter the Auth code which was send by Blink
char ssid[] = "aaaaaaaaaaa";  //Enter your WIFI Name
char pass[] = "aaaaaaaaaaaaa";  //Enter your WIFI Password

#define DHTPIN 13                                    //Connect the DHT11 sensor's data pin to GPIO13 of Nodemcu    
#define DHTTYPE DHT11                                //Mention the type of sensor we are using, Here it it DHT11
DHT dht(DHTPIN, DHTTYPE);                            //Defining the pin and the dhttype
BlynkTimer timer;

float dst,bt,bp,ba,kt,kh,ka;
char dstmp[20],btmp[20],bprs[20],balt[20];
bool bmp085_present=true;

void weather() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int r = analogRead(A0);
  int set = 10;

  r = map(r, 0, 1023, 100, 0);
  if (isnan(h) || isnan(t)) {
    Serial.println("SENSOR DHT11 TIDAK TERBACA !");
    return;
  }
  if
  (!bmp.begin()) 
          {
              Serial.println("BMP180 TIDAK TERBACA !");
              while (1) {}
          }
  if (r > set)
          {
              Blynk.notify("HUJAN!HUJAN!HUJAN!");
          }
float bp =  bmp.readPressure()/100; // Division by 100 makes it in millibars        
float ba =  bmp.readAltitude();     
float bt =  bmp.readTemperature();
float dst = bmp.readSealevelPressure()/100;
ka = ba + 47;

  Blynk.virtualWrite(V0, t);   //V0 is for Temperature
  Blynk.virtualWrite(V1, h);   //V1 is for Humidity
  Blynk.virtualWrite(V2, r);   //V2 is for Rainfall
  Blynk.virtualWrite(V3, bp);  //V3 is for Pressure
  Blynk.virtualWrite(V4, ba);  //V4 is for Altitude
  Blynk.virtualWrite(V5, dst); //V5 is for deep sea
  Blynk.virtualWrite(V6, ka);  //V6 is for deep sea
}

void setup() {
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass,"blynk-cloud.com", 8080);
  dht.begin();
  Wire.begin(I2C_SDA, I2C_SCL); //Initializing the I2C connection
  delay(10);
  // Setup a function to be called every second
  timer.setInterval(10L, weather);
}

void loop() {
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}
