// Include the neccessary libraries
#include "DHT.h"
#include <TM1637.h>
#include <math.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"
#include "Wire.h"
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>

// Define the pins used by the sensors as constants
#define DHTPIN 4
#define MOTIONPIN 3
#define DHTTYPE DHT11
#define LIGHTPIN 0
#define REDLED 11
#define BLUELED 10
#define GREENLED 9
#define ANALOGTEMPPIN 2
#define STEAMPIN 3
#define SOUNDPIN 1
#define DISPLAYDIO 5
#define DISPLAYCLK 6
#define DELAY 5000

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);
// Initialize the TM1637 display
TM1637 tm(DISPLAYCLK, DISPLAYDIO);

// Get the wifi name and password from the secrets file
char ssid[] = SECRET_SSID;   // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS; // the Wifi radio's status
char server[] = "url";

WiFiClient wifi;
HttpClient client = HttpClient(wifi, server, 80);

int x = 0;

void setup()
{
    // Initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial)
    {
        ;
    }
    Wire.begin(9);

    // Initialize the pins used by the sensors
    pinMode(MOTIONPIN, INPUT);
    pinMode(REDLED, OUTPUT);
    pinMode(BLUELED, OUTPUT);
    pinMode(GREENLED, OUTPUT);
    // Initialize the DHT sensor
    dht.begin();
    // Initialize the TM1637 display
    tm.begin();
    // Attempt to connect to Wifi network:
    while (status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        // Connect to WPA/WPA2 network:
        status = WiFi.begin(ssid, pass);
        // Wait 10 seconds for connection:
        delay(10000);
    }
    // Inform the used of the connection status and information
    Serial.print("You're connected to the network");
    printCurrentNet();
    printWifiData();
    Wire.onReceive(receiveEvent);
    /*
    // Send the device data
        StaticJsonDocument<48> device;
        device["name"] = "arduino-wifi-r2";
        String json;
        serializeJson(device, json);
        String contentType = "application/json";

        client.post("/api/devices", contentType, json);
        int statusCode = client.responseStatusCode();
        String response = client.responseBody();

        Serial.print("Status code: ");
        Serial.println(statusCode);
        Serial.print("Response: ");

        Serial.println(response);
        */
}

void loop()
{
    while (status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        // Connect to WPA/WPA2 network:
        status = WiFi.begin(ssid, pass);
        // Wait 10 seconds for connection:
        delay(10000);
    }

    Serial.println(x);
    // Get the information from the sendors
    double ATemp = getAnalogTemp();
    float hum = getDHTHumidity();
    float DHTTemp = getDHTTemp();
    int steam = getSteam();
    int sound = getSound();
    byte motion = getMotion();
    int lightValue = getLight();
    double averageTemp = (ATemp + DHTTemp) / 2;
    float heatIndex = getDHTHeatIndex(averageTemp, hum, false);

    StaticJsonDocument<200> sensorData;
    sensorData["sound"] = sound;
    sensorData["analogTemp"] = ATemp;
    sensorData["dhtTemp"] = DHTTemp;
    sensorData["humidity"] = hum;
    sensorData["heatIndex"] = heatIndex;
    sensorData["light"] = lightValue;
    sensorData["motion"] = motion;
    sensorData["steam"] = steam;
    sensorData["device"] = "62b233763ff0f0d7de03b867";

    String json;
    serializeJson(sensorData, json);
    String contentType = "application/json";

    client.post("/api/sensorDatas", contentType, json);
    int statusCode = client.responseStatusCode();
    String response = client.responseBody();

    Serial.print("Status code: ");
    Serial.println(statusCode);
    Serial.print("Response: ");
    Serial.println(response);

    /*
        // Print the analog temperature to the serial port
        Serial.print("Analog Temp:");
        Serial.print(ATemp);
        Serial.println("C");

        // Print the DHT humidity to the serial port
        Serial.print("Humidity: ");
        Serial.print(hum);
        Serial.println("% ");

        // Print the DHT temperature to the serial port
        Serial.print("DHT Temperature: ");
        Serial.print(DHTTemp);
        Serial.println("°C ");

        // Print the heat index to the serial port
        Serial.print("Heat index: ");

        Serial.print(heatIndex);
        Serial.println("°C ");

        // Print the steam to the serial port
        Serial.print("Moisture is ");
        Serial.println(steam);

        // Print the sound to the serial port
        Serial.print("Sound: ");
        Serial.println(sound);

        // Print the motion to the serial port
        if (motion == 1)
            Serial.println("Somebody is in this area!");
        else if (motion == 0)
            Serial.println("No one!");

        // Print the light to the serial port
        Serial.print("Light value: ");
        Serial.println(lightValue);
*/
    // Control the REG LED color
    controlRGBLED(0, 0, 255);

    // Control the display output
    controlDisplay("13.37");

    // Wait for one second
    delay(DELAY);
}

void receiveEvent(int bytes)
{
    x = Wire.read(); // read one character from the I2C
}

// Function to get the analog temperature from the sensor
double getAnalogTemp()
{
    // Read the analog temperature sensor
    double ATemp = analogRead(ANALOGTEMPPIN);
    // Convert the reading to voltage
    ATemp = (ATemp / 1023) * 5;
    // Convert the voltage to temperature
    ATemp = (5 - ATemp) / ATemp * 4700;
    ATemp = (1 / (log(ATemp / 10000) / 3950 + 1 / (25 + 273.15))) - 273.15;
    // Return the temperature
    return ATemp;
}

// Function to get the DHT temperature from the sensor
float getDHTTemp()
{
    // Get the temperature from the DHT sensor
    float DHTTemp = dht.readTemperature();
    // Check if the temperature is valid
    if (isnan(DHTTemp))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return 1;
    }
    // Return the temperature
    return DHTTemp;
}

// Function to get the DHT humidity from the sensor
float getDHTHumidity()
{
    // Get the humidity from the DHT sensor
    float DHTHum = dht.readHumidity();
    // Check if the humidity is valid
    if (isnan(DHTHum))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return 1;
    }
    // Return the humidity
    return DHTHum;
}

// Function to calculate the DHT heat index
float getDHTHeatIndex(float temp, float hum, bool isFahreheit)
{
    // Calculate the heat index with the formula from the DHT sensor
    float DHTHeatIndex = dht.computeHeatIndex(temp, hum, isFahreheit);
    // Check if the heat index is valid
    return DHTHeatIndex;
}

// Function to get the steam from the sensor
int getSteam()
{
    // Read the steam value from the sensor
    int steam = analogRead(STEAMPIN);
    // Return the steam value
    return steam;
}

// Function to get the sound from the sensor
int getSound()
{
    // Read the sound value from the sensor
    int sound = analogRead(SOUNDPIN);
    // Return the sound value
    return sound;
}

// Function to get the motion from the sensor
byte getMotion()
{
    // Read the motion value
    byte motion = digitalRead(MOTIONPIN);
    // Return the motion value
    return motion;
}

// Function to get the light from the sensor
int getLight()
{
    // Read the light value from the sensor
    int lightValue = analogRead(LIGHTPIN);
    return lightValue;
}

// Function to control the RGB LED
void controlRGBLED(int red, int green, int blue)
{
    // Set each LED to the specified value
    analogWrite(REDLED, red);
    analogWrite(GREENLED, green);
    analogWrite(BLUELED, blue);
}

// Function to control the display
void controlDisplay(String str)
{
    // Display the string on the display
    tm.display(str);
}

// Function to print the current Wifi information
void printWifiData()
{
    // Print your board's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
    Serial.println(ip);
    // Print your MAC address:
    byte mac[6];
    WiFi.macAddress(mac);
    Serial.print("MAC address: ");
    printMacAddress(mac);
}

// Function to print the current network information
void printCurrentNet()
{
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
    // print the MAC address of the router you're attached to:
    byte bssid[6];
    WiFi.BSSID(bssid);
    Serial.print("BSSID: ");
    printMacAddress(bssid);
    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.println(rssi);
    // print the encryption type:
    byte encryption = WiFi.encryptionType();
    Serial.print("Encryption Type:");
    Serial.println(encryption, HEX);
    Serial.println();
}

// Function to print the MAC address
void printMacAddress(byte mac[])
{
    for (int i = 5; i >= 0; i--)
    {
        if (mac[i] < 16)
        {
            Serial.print("0");
        }
        Serial.print(mac[i], HEX);
        if (i > 0)
        {
            Serial.print(":");
        }
    }
    Serial.println();
}