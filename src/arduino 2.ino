#include "DHT.h"
#include <TM1637.h>
#include <math.h>

#define DHTPIN 4
#define MOTIONPIN 3
#define DHTTYPE DHT11
#define LIGHTPIN 5
#define REDLED 11
#define BLUELED 10
#define GREENLED 9

DHT dht(DHTPIN, DHTTYPE);
TM1637 tm(6, 5);

void setup()
{
    Serial.begin(9600);
    pinMode(MOTIONPIN, INPUT);
    pinMode(REDLED, OUTPUT);
    pinMode(BLUELED, OUTPUT);
    pinMode(GREENLED, OUTPUT);
    dht.begin();
    tm.begin();
}

void loop()
{
    double ATemp = analogRead(2); // Connect LM35 on Analog 0
    ATemp = (ATemp / 1023) * 5;
    ATemp = (5 - ATemp) / ATemp * 4700;
    ATemp = (1 / (log(ATemp / 10000) / 3950 + 1 / (25 + 273.15))) - 273.15;
    Serial.print("Analog Temp:"); // Display the temperature on Serial monitor
    Serial.print(ATemp);
    Serial.println("C");

    float hum = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float DHTTemp = dht.readTemperature();
    // Check if any reads failed and exit early (to try again).
    if (isnan(hum) || isnan(DHTTemp))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }
    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(DHTTemp, hum, false);
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.println("% ");
    Serial.print("DHT Temperature: ");
    Serial.print(DHTTemp);
    Serial.println("°C ");
    Serial.print("Heat index: ");
    Serial.print(hic);
    Serial.println("°C ");

    int steam;
    steam = analogRead(3);
    Serial.print("Moisture is ");
    Serial.println(steam);

    int sound;
    sound = analogRead(4); // connect mic sensor to Analog 0
    Serial.print("Sound: ");
    Serial.println(sound); // print the sound value on serial monitor

    byte motion = digitalRead(MOTIONPIN);
    if (motion == 1)
        Serial.println("Somebody is in this area!");
    else if (motion == 0)
        Serial.println("No one!");

    int lightValue = 0;
    lightValue = analogRead(LIGHTPIN);
    Serial.print("Light value: ");
    Serial.println(lightValue);

    for (int color = 255; color > 0; color--)
    {
        analogWrite(11, color);
        analogWrite(10, 255 - color);
        analogWrite(9, 128 - color);
        delay(2);
    }

    // tm.display(1234);
    // Display float:
    tm.display(29.65);
    // Display String:
    // tm.display("PLAY");
    // tm.display("STOP");

    delay(1000);
}