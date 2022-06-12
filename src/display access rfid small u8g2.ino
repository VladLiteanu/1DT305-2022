#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>
#include <U8x8lib.h>
#include <LoRa.h>

#define SS_PIN (byte)10
#define RST_PIN (byte)8 // Important, pin 9 is used by LoRa module even if not connected 
#define TOUCH (byte)7
#define VIBRATION (byte)6
#define LORA_NSS (byte)2
#define LORA_RESET (byte)3
#define LORA_DIO0 (byte)4
#define DELAY (int)3000
#define DELAY_VIBRATION (byte)150

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);

int counter = 0;

void setup()
{
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    Serial.begin(9600); // Initiate a serial communication
    SPI.begin();        // Initiate  SPI bus
    mfrc522.PCD_Init(); // Initiate MFRC522
    u8x8.begin();
    u8x8.setPowerSave(0);
    pinMode(TOUCH, INPUT);
    pinMode(VIBRATION, OUTPUT);
    LoRa.setPins(LORA_NSS, LORA_RESET, LORA_DIO0); // set CS, reset, IRQ pin
    LoRa.setTxPower(2);
    Serial.println("Please place your card on the reader...");
    Serial.println();
    if (!LoRa.begin(433E6))
    {
        Serial.println("Starting LoRa failed!");
        u8x8.drawString(0, 0, "Starting LoRa ");
        u8x8.drawString(0, 1, "failed!");
        while (1)
            ;
    }
}

void loop()
{
    u8x8.drawString(0, 0, "Please place ");
    u8x8.drawString(0, 1, "your card on ");
    u8x8.drawString(0, 2, "the reader...");
    // Look for new cards
    if (!mfrc522.PICC_IsNewCardPresent())
        return;

    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial())
        return;

    if (digitalRead(TOUCH) == HIGH)
    {
        Serial.println("Touch detected");
        u8x8.clearDisplay();
        u8x8.drawString(0, 0, "Touch detected");

        // Show UID on serial monitor
        Serial.print("UID string: ");
        u8x8.drawString(0, 1, "UID string: ");
        String content = "";
        for (byte i = 0; i < mfrc522.uid.size; i++)
        {
            Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
            Serial.print(mfrc522.uid.uidByte[i], HEX);
            content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
            content.concat(String(mfrc522.uid.uidByte[i], HEX));
        }
        Serial.println();
        Serial.print("Message: ");
        content.toUpperCase();
        u8x8.drawString(0, 2, content.substring(1).c_str());
        if (content.substring(1) == "B5 67 0F AD") // change here the UID of the card/cards that you want to give access
        {
            Serial.println("Access granted");
            u8x8.drawString(0, 3, "Access granted");
            analogWrite(VIBRATION, DELAY_VIBRATION);
            delay(DELAY_VIBRATION);
            analogWrite(VIBRATION, 0);
            sendMessage(content);
            counter++;
        }
        else
        {
            Serial.println("Access denied");
            u8x8.drawString(0, 3, "Access denied");
            analogWrite(VIBRATION, DELAY_VIBRATION);
            delay(DELAY_VIBRATION);
            analogWrite(VIBRATION, 0);
        }
    }
    else
    {
        u8x8.clearDisplay();
        Serial.println("You have to touch the sensor");
        u8x8.drawString(0, 0, "You have to ");
        u8x8.drawString(0, 1, "touch the sensor");
    }
    Serial.println();
    Serial.print("Sending packet: ");
    Serial.println(counter);
    u8x8.drawString(0, 5, "Packets sent: ");
    u8x8.drawString(13, 5, String(counter).c_str());
    delay(DELAY);
    u8x8.clearDisplay();
}

void sendMessage(String message)
{
    LoRa.beginPacket();
    LoRa.print(message);
    LoRa.endPacket();
    Serial.print("Message sent!");
    u8x8.drawString(0, 5, "Message sent!");
}