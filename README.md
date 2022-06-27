# Indoor room monitoring with arduino 

###### Authored by [Vlad Liteanu](https://github.com/VladLiteanu) (gl222nf) 

This is the repository for the "Introduction to Applied IoT" summer course 2022. 

This tutorial will facilitate the necessary information for building a room monitoring device with Arduino and creating or running the software for storing and displaying the collected data.
It shows how to connect and use sensors such as an OLED display, an RFID reader, wifi, motion sensors, and more. 

With intermediate knowledge along with some previous experience with Arduino and sensors, and some backend and frontend development experience, this project can be finished in about fifteen to twenty-five hours. 

## Objective 

Summer in Sweden can sometimes be very uncomfortable for people not used to high temperatures. As one of those people, I realized I did not have a reasonably accurate thermometer. So I decided to create one myself to know beyond a doubt when I am justified to feel uncomfortable.

From a glorified thermometer to an all-around room monitoring device is a long way. Still, I decided that the extra information received from the sensors could aid my feeling of discomfort. 

## Material

The following materials are needed for the project: 

| Hardware Image | Name | Price and Link |
| --- | --- | --- |
|<img src="https://user-images.githubusercontent.com/50659238/176025896-7f03844e-f51b-40e6-ba05-075ba9666d51.jpg" width="309"> | Arduino Uno R3 | [€23](https://www.amazon.de/-/en/A000066-Arduino-Accessory-Parent/dp/B008GRTSV6/) |
| <img src="https://user-images.githubusercontent.com/50659238/176027382-d2b1d9e4-8d72-42af-86de-e2711e146f2f.jpg" width="309"> | Arduino Uno WiFi R2 | [€45](https://www.amazon.de/-/en/Arduino-UNO-WiFi-REV2-ABX00021/dp/B07MK598QV/) | 
| <img src="https://user-images.githubusercontent.com/50659238/176028006-e0387cc2-0383-4f80-995d-66d125ce7686.jpg" width="309"> | UNO R3 Electronics Project Starter Kit | [kr82](https://www.amazon.se/-/en/gp/product/B08NW2VPJL/) |
| <img src="https://user-images.githubusercontent.com/50659238/176030379-a37d8895-9ec4-49df-8d1f-22f802817824.jpg" width="309"> | ELEGOO Revised Electronics Learning Set | [€16](https://www.amazon.de/-/en/gp/product/B01M7N4WB6/) | 
| <img src="https://user-images.githubusercontent.com/50659238/176028419-0240ee4e-a91b-4c5b-9715-3560b134f4b2.jpg" width="309"> | KEYESTUDIO Upgraded 37-in-1 Sensor Module V3.0 | [kr339](https://www.amazon.se/-/en/gp/product/B0834KMKNH/) |
| <img src="https://user-images.githubusercontent.com/50659238/176028737-c1aae07a-2424-4b51-9e5f-db828fd64e5a.jpg" width="309"> | Leicke ULL Power Supply 9V 2A | [kr85](https://www.amazon.se/-/en/gp/product/B01GRS5V8E/) |
| <img src="https://user-images.githubusercontent.com/50659238/176029071-e08fa035-804d-47b5-a13b-f1b520f06864.jpg" width="309"> | Zkee Shop MFRC-522 RFID RF Module | [kr65](https://www.amazon.se/-/en/gp/product/B072BQWVN7) |
| <img src="https://user-images.githubusercontent.com/50659238/176029396-41743017-34b1-41e6-b0b1-5c11efc4f77e.jpg" width="309"> | AZDelivery 1.3-inch OLED 128 x 64 pixels I2C | [kr124](https://www.amazon.se/gp/product/B078J78R45/) |
| <img src="https://user-images.githubusercontent.com/50659238/176029620-6ba31235-4e77-4d9a-9fc2-0d74c305f0a5.jpg" width="309"> | HALJIA 9V Battery Holder Box | [kr71](https://www.amazon.se/gp/product/B06WGQKJ5P/) |
| <img src="https://user-images.githubusercontent.com/50659238/176030113-88402bc4-1572-48e0-af44-11d01fe8c1a1.jpg" width="309"> | TECNOIOT 2pcs ra-01 lora sx1278 433mhz ra01 | [€26](https://www.amazon.de/gp/product/B083M6P9SK/) | 










