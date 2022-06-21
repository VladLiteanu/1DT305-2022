// Include the neccessary libraries
#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>
#include <U8x8lib.h>
#include <LoRa.h>
#include <Wire.h>

// Constants to store pins and delays
#define SS_PIN (byte)10
#define RST_PIN (byte)8 // Important, pin 9 is used by LoRa module even if overridden
#define TOUCH (byte)7
#define VIBRATION (byte)6
#define LORA_NSS (byte)2
#define LORA_RESET (byte)3
#define LORA_DIO0 (byte)4
#define DELAY (int)2000
#define DELAY_VIBRATION (byte)150
// Change this to the UID of the card you want to use
#define C_UID "B5 67 0F AD"

// Create RIFD instance
MFRC522 mfrc522(SS_PIN, RST_PIN);
// Create display instance
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);

// Counter to count the number of LoRa messages sent
int counter = 0;

void setup()
{
    // Set the display font
    u8x8.setFont(u8x8_font_victoriamedium8_r);
    // Initialize the display
    u8x8.begin();
    // Start I2C communication 
    Wire.begin(9);
    // Initiate a serial communication
    Serial.begin(9600);
    // Initiate SPI bus
    SPI.begin();
    // Initiate the RFID module
    mfrc522.PCD_Init();
    // Tell the display to show what is sent to it
    u8x8.setPowerSave(0);
    // Initiate the touch and vibration modules
    pinMode(TOUCH, INPUT);
    pinMode(VIBRATION, OUTPUT);
    // Override the default pins for the LoRa module (NSS, RESET, DIO0)
    LoRa.setPins(LORA_NSS, LORA_RESET, LORA_DIO0);
    // Start the LoRa module and check for errors
    if (!LoRa.begin(433E6))
    {
        // If the LoRa module failed to start, print an error message
        Serial.println("Starting LoRa failed!");
        u8x8.drawString(0, 0, "Starting LoRa ");
        u8x8.drawString(0, 1, "failed!");
        // Create and infinite loop untill reset
        while (1)
            ;
    }
    // If the LoRa module started successfully, print a message
    Serial.println("Please place your card on the reader...");
    Serial.println();
}

void loop()
{
    // Tell the user to place the card on the reader
    u8x8.drawString(0, 0, "Please place ");
    u8x8.drawString(0, 1, "your card on ");
    u8x8.drawString(0, 2, "the reader...");
    // Look for new cards
    if (!mfrc522.PICC_IsNewCardPresent())
        return;
    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial())
        return;
    // Check if the user is touching the sensor
    if (digitalRead(TOUCH) == HIGH)
    {
        // If the user is touching the sensor, display a message
        Serial.println("Touch detected");
        u8x8.clearDisplay();
        u8x8.drawString(0, 0, "Touch detected");

        // Show UID on serial monitor and display
        Serial.print("UID string: ");
        u8x8.drawString(0, 1, "UID string: ");
        // Create a string to store the UID
        String content = "";
        // Loop through the UID of the card
        for (byte i = 0; i < mfrc522.uid.size; i++)
        {
            // Print the UID on the serial monitor
            Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
            Serial.print(mfrc522.uid.uidByte[i], HEX);
            // Add the UID to the string
            content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
            content.concat(String(mfrc522.uid.uidByte[i], HEX));
        }
        Serial.println();
        Serial.print("Message: ");
        // Change the message to be upper case
        content.toUpperCase();
        // Print the UID on the display
        u8x8.drawString(0, 2, content.substring(1).c_str());
        // Check if the card's UID is the correct one
        if (content.substring(1) == C_UID)
        {
            // If the card's UID is correct, print a message
            Serial.println("Access granted");
            u8x8.drawString(0, 3, "Access granted");
            // Make the vibration module vibrate
            analogWrite(VIBRATION, DELAY_VIBRATION);
            delay(DELAY_VIBRATION);
            analogWrite(VIBRATION, 0);
            // transmit to device #9
            Wire.beginTransmission(9);
            // Send data
            Wire.write(1);
            // stop transmitting
            Wire.endTransmission();
            // Send a message with the LoRa module
            sendMessage(content);
            // Increment the counter
            counter++;
        }
        else
        {
            // If the card's UID is not correct, print a message
            Serial.println("Access denied");
            u8x8.drawString(0, 3, "Access denied");
            // Make the vibration module vibrate
            // transmit to device #9
            Wire.beginTransmission(9);
            // Send data
            Wire.write(0);
            // stop transmitting
            Wire.endTransmission();
            analogWrite(VIBRATION, DELAY_VIBRATION);
            delay(DELAY_VIBRATION);
            analogWrite(VIBRATION, 0);
        }
    }
    else
    {
        // If the user is not touching the sensor, display a message
        u8x8.clearDisplay();
        Serial.println("You have to touch the sensor");
        u8x8.drawString(0, 0, "You have to ");
        u8x8.drawString(0, 1, "touch the sensor");
    }
    // Display the number of messages sent
    Serial.println();
    Serial.print("Sending packet: ");
    Serial.println(counter);
    u8x8.drawString(0, 5, "Packets sent: ");
    u8x8.drawString(13, 5, String(counter).c_str());
    // Wait for a while
    delay(DELAY);
    // Clear the display
    u8x8.clearDisplay();
}

// Function to send a message with the LoRa module
void sendMessage(String message)
{
    LoRa.beginPacket();
    LoRa.print(message);
    LoRa.endPacket();
    Serial.print("Message sent with lora!");
    u8x8.drawString(0, 5, "Message sent!");
}
