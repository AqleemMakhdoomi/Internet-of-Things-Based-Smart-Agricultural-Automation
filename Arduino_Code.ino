/* Comment this out to disable prints and save space */

#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <DHT.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "32bda6a0ced449be9fc6eb26a8a5ff03";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Abc";
char pass[] = "arshid11";

// Hardware Serial on Mega, Leonardo, Micro...
//#define EspSerial Serial1

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(10, 11); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

#define DHTPIN 7          // What digital pin we're connected to
//int moisture =0;
#define echoPin 5
#define trigPin 6
int moisture =0;
float t = 0;
int distance =0;
 int gas = 0;
// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  int duration;
  digitalWrite(trigPin, HIGH);
  delay(100);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = 15 - ((duration / 2) / 29.1);//This is used to calculate the water level by dividing the distance by 2 because it calculates double distance.
  //We are using 29.1 as the 
  Serial.print(distance);
  Serial.print("CM");
  Serial.println("");
  //delay(100);
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  int moisture = analogRead(A0);
  int rain = analogRead(A1);
  int gas = analogRead(A2);
  rain = map(rain, 1023, 0, 0, 100);
  gas = map(gas, 1023, 0, 100, 0);
  moisture = map(moisture, 1023, 0, 0, 100);
if (distance>8)
{
  digitalWrite(2,HIGH);
  digitalWrite(4,LOW);
  Blynk.virtualWrite(V7, HIGH);
  Blynk.virtualWrite(V8, LOW);
  Blynk.notify("Water Pump Turned On and Drain Off");
  Blynk.email("smartagriculture2018@gmail.com","Pump Alert!","Water Pump Turned On and Drain Off");
  }
else if (distance < 7)
{
  
  digitalWrite(2,LOW);
  digitalWrite(4,HIGH);
  Blynk.virtualWrite(V7, LOW);
  Blynk.virtualWrite(V8, HIGH);
  Blynk.notify("Drain Pump Turned On and Water Pump Off");
  Blynk.email("smartagriculture2018@gmail.com","Drain Alert!","Drain Pump Turned On and Water Pump Off");
  }

else{
  
  
  digitalWrite(2,LOW);
  digitalWrite(4, LOW);
  Blynk.virtualWrite(V7, LOW);
  Blynk.virtualWrite(V8, LOW);
  Blynk.notify("Drain Pump and Water Pump Off");
    }
if (moisture<50 || (moisture<50&&t>22) )
{
  digitalWrite(12,HIGH);
  Blynk.notify("Sprinklers Turned On Due to Low Soil Moisture.");
  Blynk.email("smartagriculture2018@gmail.com","Sprinkler On Alert!","Sprinklers Turned On Due to Low Soil Moisture.");
  }

else{
  
  digitalWrite(12,LOW);
  Blynk.notify("Sprinklers Turned Off Due to Balanced Soil Moisture.");
  Blynk.email("smartagriculture2018@gmail.com","Sprinkler On Alert!","Sprinklers Turned Off Due to Balanced Soil Moisture.");
}

if (gas>50)
{
  
  digitalWrite(8,HIGH);
  Blynk.virtualWrite(V9, HIGH);
  Blynk.notify("Air Purifier Turned On Due to Bad Air Quality.");
  Blynk.email("smartagriculture2018@gmail.com","Sprinkler On Alert!","Air Purifier Turned On Due to Bad Air Quality.");
  }

else {
  
  digitalWrite(8,LOW);
  Blynk.virtualWrite(V9, LOW);
  Blynk.notify("Air Purifier Turned Off Due to Balanced Air Quality.");
  Blynk.email("smartagriculture2018@gmail.com","Sprinkler On Alert!","Air Purifier Turned Off Due to Balanced Air Quality.");
  }


  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // We shouldn't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V1, rain);
  Blynk.virtualWrite(V2, moisture);
  Blynk.virtualWrite(V3, gas);
  Blynk.virtualWrite(V4, distance*100);




}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8442);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(12,OUTPUT);
  digitalWrite(2,LOW);
  digitalWrite(4,LOW);
  digitalWrite(8,LOW);
  digitalWrite(12,LOW);
}

void loop()
{
  Blynk.run();
  timer.run();




  
}

