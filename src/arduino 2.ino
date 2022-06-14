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
#define ANALOGTEMPPIN 2
#define STEAMPIN 3
#define SOUNDPIN 4
#define DISPLAYDIO 5
#define DISPLAYCLK 6
#define DELAY 1000

DHT dht(DHTPIN, DHTTYPE);
TM1637 tm(DISPLAYCLK, DISPLAYDIO);

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        ;
    }
    pinMode(MOTIONPIN, INPUT);
    pinMode(REDLED, OUTPUT);
    pinMode(BLUELED, OUTPUT);
    pinMode(GREENLED, OUTPUT);
    dht.begin();
    tm.begin();
}

void loop()
{
    double ATemp = getAnalogTemp();
    Serial.print("Analog Temp:"); // Display the temperature on Serial monitor
    Serial.print(ATemp);
    Serial.println("C");

    float hum = getDHTHumidity();
    // Read temperature as Celsius (the default)
    float DHTTemp = getDHTTemp();

    // Compute heat index in Celsius (isFahreheit = false)
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.println("% ");
    Serial.print("DHT Temperature: ");
    Serial.print(DHTTemp);
    Serial.println("°C ");
    Serial.print("Heat index: ");
    double averageTemp = (ATemp + DHTTemp) / 2;
    float heatIndex = getDHTHeatIndex(averageTemp, hum, false);
    Serial.print(heatIndex);
    Serial.println("°C ");

    int steam = getSteam();
    Serial.print("Moisture is ");
    Serial.println(steam);

    int sound = getSound();
    Serial.print("Sound: ");
    Serial.println(sound);

    byte motion = getMotion();
    if (motion == 1)
        Serial.println("Somebody is in this area!");
    else if (motion == 0)
        Serial.println("No one!");

    int lightValue = getLight();
    Serial.print("Light value: ");
    Serial.println(lightValue);

    controlRGBLED(0, 0, 255);

    controlDisplay("13.37");

    delay(DELAY);
}

double getAnalogTemp()
{
    double ATemp = analogRead(ANALOGTEMPPIN); // Connect LM35 on Analog 0
    ATemp = (ATemp / 1023) * 5;
    ATemp = (5 - ATemp) / ATemp * 4700;
    ATemp = (1 / (log(ATemp / 10000) / 3950 + 1 / (25 + 273.15))) - 273.15;
    return ATemp;
}

float getDHTTemp()
{
    float DHTTemp = dht.readTemperature();
    if (isnan(DHTTemp))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return 1;
    }
    return DHTTemp;
}

float getDHTHumidity()
{
    float DHTHum = dht.readHumidity();
    if (isnan(DHTHum))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return 1;
    }
    return DHTHum;
}

float getDHTHeatIndex(float temp, float hum, bool isFahreheit)
{
    float DHTHeatIndex = dht.computeHeatIndex(temp, hum, isFahreheit);
    return DHTHeatIndex;
}

int getSteam()
{
    int steam = analogRead(STEAMPIN);
    return steam;
}

int getSound()
{
    int sound = analogRead(SOUNDPIN);
    return sound;
}

byte getMotion()
{
    byte motion = digitalRead(MOTIONPIN);
    return motion;
}

int getLight()
{
    int lightValue = analogRead(LIGHTPIN);
    return lightValue;
}

void controlRGBLED(int red, int green, int blue)
{
    analogWrite(REDLED, red);
    analogWrite(GREENLED, green);
    analogWrite(BLUELED, blue);
}

void controlDisplay(String str)
{
    tm.display(str);
}
