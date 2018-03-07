// last update 07/03/2018 
// address : 0x07
// payload char[16]


#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>

#define POTAR A0
#define PR_1 A1
#define PR_2 A2
#define PR_3 A3
#define DHTPIN 3
#define DHTTYPE DHT22  

#define DECIMAL_PRECISION 100

DHT dht(DHTPIN, DHTTYPE);

unsigned char message[16] = {0};

long update_time;
void setup() {
  // DEBUG
  Serial.begin(9600);
  Serial.println("test");

  pinMode(POTAR, INPUT);
  pinMode(PR_1, INPUT);
  pinMode(PR_2, INPUT);
  pinMode(PR_3, INPUT);
  dht.begin();

  Wire.begin(0x07);
  Wire.onRequest(requestEvent);

  update_time = 0;
}

void requestEvent(){

  Serial.println("catch request !");
  message[7] = map(analogRead(POTAR), 0, 1023, 0, 255);
  Wire.write(message, 16);

  
}

void loop() {
 
  if(millis() - update_time > 3000){
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (isnan(h) || isnan(t)) {
      // DEBUG
      Serial.println("Failed to read from DHT sensor!");
    }else{
      message[0] = (int) t;
      message[1] = ((int) (t * DECIMAL_PRECISION) % DECIMAL_PRECISION);
      message[2] = (int) h;
      message[3] = ((int) (h * DECIMAL_PRECISION) % DECIMAL_PRECISION);
    }

    // DEBUG
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.println(t);

    message[4] = map(analogRead(PR_1), 0, 600, 0, 255);
    message[5] = map(analogRead(PR_2), 0, 600, 0, 255);
    message[6] = map(analogRead(PR_3), 0, 600, 0, 255);

    Serial.print("lux_1: ");
    Serial.print(message[4]);
    Serial.print(" lux_2: ");
    Serial.print(message[5]);
    Serial.print(" lux_3: ");
    Serial.print(message[6]);
    Serial.print(" Potar: ");
    Serial.println(map(analogRead(POTAR), 0, 1023, 0, 255));

    update_time = millis();
  }
}
