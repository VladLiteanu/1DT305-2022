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
| <img src="https://user-images.githubusercontent.com/50659238/176025896-7f03844e-f51b-40e6-ba05-075ba9666d51.jpg" width="309"> | Arduino Uno R3 | [€23](https://www.amazon.de/-/en/A000066-Arduino-Accessory-Parent/dp/B008GRTSV6/) |
| <img src="https://user-images.githubusercontent.com/50659238/176027382-d2b1d9e4-8d72-42af-86de-e2711e146f2f.jpg" width="309"> | Arduino Uno WiFi R2 | [€45](https://www.amazon.de/-/en/Arduino-UNO-WiFi-REV2-ABX00021/dp/B07MK598QV/) | 
| <img src="https://user-images.githubusercontent.com/50659238/176028006-e0387cc2-0383-4f80-995d-66d125ce7686.jpg" width="309"> | UNO R3 Electronics Project Starter Kit | [kr82](https://www.amazon.se/-/en/gp/product/B08NW2VPJL/) |
| <img src="https://user-images.githubusercontent.com/50659238/176030379-a37d8895-9ec4-49df-8d1f-22f802817824.jpg" width="309"> | ELEGOO Revised Electronics Learning Set | [€16](https://www.amazon.de/-/en/gp/product/B01M7N4WB6/) | 
| <img src="https://user-images.githubusercontent.com/50659238/176028419-0240ee4e-a91b-4c5b-9715-3560b134f4b2.jpg" width="309"> | KEYESTUDIO Upgraded 37-in-1 Sensor Module V3.0 | [kr339](https://www.amazon.se/-/en/gp/product/B0834KMKNH/) |
| <img src="https://user-images.githubusercontent.com/50659238/176028737-c1aae07a-2424-4b51-9e5f-db828fd64e5a.jpg" width="309"> | Leicke ULL Power Supply 9V 2A | [kr85](https://www.amazon.se/-/en/gp/product/B01GRS5V8E/) |
| <img src="https://user-images.githubusercontent.com/50659238/176029071-e08fa035-804d-47b5-a13b-f1b520f06864.jpg" width="309"> | Zkee Shop MFRC-522 RFID RF Module | [kr65](https://www.amazon.se/-/en/gp/product/B072BQWVN7) |
| <img src="https://user-images.githubusercontent.com/50659238/176029396-41743017-34b1-41e6-b0b1-5c11efc4f77e.jpg" width="309"> | AZDelivery 1.3-inch OLED 128 x 64 pixels I2C | [kr124](https://www.amazon.se/gp/product/B078J78R45/) |
| <img src="https://user-images.githubusercontent.com/50659238/176029620-6ba31235-4e77-4d9a-9fc2-0d74c305f0a5.jpg" width="309"> | HALJIA 9V Battery Holder Box | [kr71](https://www.amazon.se/gp/product/B06WGQKJ5P/) |
| <img src="https://user-images.githubusercontent.com/50659238/176030113-88402bc4-1572-48e0-af44-11d01fe8c1a1.jpg" width="309"> | TECNOIOT 2pcs ra-01 lora sx1278 433mhz ra01 | [€26](https://www.amazon.de/gp/product/B083M6P9SK/) | 

- The Arduino board will be used to connect to the sensors, the internet, and each other.
- The starting kits will be used for the breadboards, the wires, and the power supplies. 
- From the Keyestudio pack, we'll use: RGB LED, 4-digit LED digital tube, Motor Module, Capacitive Touch, Photocell, Analog Temperature, Analog Sound, Steam Moisture, DHT11, and PIR Motion Sensor.
These are sensors we can interact with or give us information about our surroundings. 
- The 9V power supply will be used to provide extra power to the sensors.
- The RFID sensor will be used to read information from a card.
- The display is used for showing information about the RIFD sensor and cards.
- The battery holder is used for powering one of the Arduino boards. 
- Lora can be used to transmit data between the Arduino borards.

## Computer setup

#### Chosen IDE
Arduino boards have their own IDEs called Arduino IDE, which can be used for writing and uploading code to boards. 
For installation instructions, please refer to the official helping guide [here](https://www.arduino.cc/en/Guide#:~:text=Install%20the%20Arduino%20Desktop%20IDE).

#### Uploading the code 
After installing the IDE, you will be welcomed by an interface that looks something like this:

<img src="https://user-images.githubusercontent.com/50659238/176256639-39688f83-9ca3-40c3-8fe9-9dc2bda8a748.png" width="500">

From here, you can write your code, and when you are satisfied, you can press the verify button on the top left to compile the code and check for errors.

By navigating to the "Tools" menu at the top of the IDE and then clicking on the "Manage Libraries", a new window will pop up where you can search and install extra libraries to use in your code. 

For this tutorial, we will use the following libraries: DHT sensor library by Adafruit, TM1637 Driver by AKJ, math.h, SPI.h, WiFiNINA, Wire.h, ArduinoHttpClient, ArduinoJson by Benoit Blanchon, MFRC522 by GithubCommunity, Arduino.h, and U8g2 by Oliver.

Some of the libraries are installed by default, and some need to be installed from the library manager.

For uploading code to the boards, please follow the official documentation [here](https://support.arduino.cc/hc/en-us/articles/4733418441116-Upload-a-sketch-in-Arduino-IDE).

For more information, please refer to the following documentation: 
- [Installing Libraries](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries)
- [Installing the core for megaAVR boards](https://docs.arduino.cc/software/ide-v1/tutorials/getting-started/cores/arduino-megaavr)
- [Overview of the Arduino IDE](https://docs.arduino.cc/software/ide-v1/tutorials/Environment).

## Putting everything together

Due to the large number of sensors used, I couldn't find an online circuit creator with all of them. Therefore I created it with Photoshop. No parts of the following image are at the correct scale. 

<img src="https://user-images.githubusercontent.com/50659238/176761089-8eda45cf-c92c-4763-98fa-4840728105f3.jpg" width="700">

Note that the red wires represent power, and the black ones are the ground. The other colors are standard connections to the Arduino.

Keep in mind that the RFID reader and Lora use 3.3V while everything else uses 5V. 

The Lora module is not portrayed in the diagram above because it wasn't working and I ended up not using it. For a tutorial on how to connect it, you can follow [this](https://iotdesignpro.com/projects/lora-communication-between-two-arduino-using-LoRa-Module-SX1278). You can use pins 10-13 for both the RFID reader and Lora simultaneously.

Because Lora did not work correctly for me, the connection between the Arduino boards had to be made through I2C. As a result, because the OLED display also uses I2C, it stops working while the Arduino boards are connected to each other. This persists even if I specify different addresses. However, the display does work if the boards are disconnected from each other.

## Platform 

Because of my previous programming experiences, I decided to make the assignment more of a challenge by not using any preexisting platforms and making my own. 

For the server's database, I use MongoDB Atlas to store everything in the cloud and make the data accessible from anywhere. 
I created a simple ER diagram to showcase how the data is stored and how it interacts. 

<img src="https://user-images.githubusercontent.com/50659238/176765003-ed0b1bb4-7510-4e70-9b38-b41e3c52a5e4.png" width="500">

The server was created using Nodejs and hosted on Heroku. The server and database are connected for data transfer. The source code for the server can be found in [/src/backend](https://github.com/VladLiteanu/1DT305-2022/tree/main/src/backend).

For the frontend, I again went with Nodejs as well as React and Chartjs for displaying the data neatly. The source code can be found in [/src/arduino-client](https://github.com/VladLiteanu/1DT305-2022/tree/main/src/arduino-client).

## The Code

As mentioned above, I didn't go with any preexisting platforms, and I will briefly explain how to run the front and backend. 

### Running the server 

Firstly you need to install Nodejs from [here](https://nodejs.org/en/download/). 

For instructions, follow the official windows documentation [here](https://docs.microsoft.com/en-us/windows/dev-environment/javascript/nodejs-on-windows).  

You will also need to choose whether to run the database locally or in the cloud. For running it locally, you would need to install MongoDB from [here](https://www.mongodb.com/try/download/community).  

For creating a MongoDB Atlas cluster, follow the first ~4 minutes of [this](https://youtu.be/084rmLU1UgA) video and either replace what is in the quotes in the app.js file or add it as a global variable as MONGODB_URI.

```js
var mongoURI = process.env.MONGODB_URI || 'mongodb://localhost:27017/arduinoDB';
```

You can clone or download the source code from this repository. Once that is done, you need to navigate to /src/backend and run the following commands one at a time. 

```
npm install
npm start
```

If everything went well, you should see this message.

<img src="https://user-images.githubusercontent.com/50659238/176967104-5ca7ac55-6c52-4243-9871-990906f55033.png" width="700">


### Running the frontend

You'll firstly need to install Nodejs as described above. 

Navigate to /src/arduino-client and run the same commands as before. 

```
npm install
npm start
```

If everything went well, you should see this message and a new browser window should open.

<img src="https://user-images.githubusercontent.com/50659238/176967315-cd1244ed-6616-4b3b-8fe3-3b817fba0790.png" width="500">


### Arduino code

Before uploading the code for the Arduino Uno wifi, you'll need to change the following line in "src/Arduino uno wifi r2/Arduino uno wifi r2.ino" file to connect to your server. 

```cpp
char server[] = "url";
```

You might also need to change the path on line 146 depending on how the server is configured. 

For sending the device name, uncomment the code in the setup function. 

## Transmitting the data

The data from the Arduino Uno r3 is transmitted through I2C whenever a card is scanned, and we create an interrupt to make sure that the data is received by the other Arduino. 

The sensor data from the Arduino Uno Wifi is collected and sent every 5 seconds as stated by the delay constant, but it can easily be changed to transfer more or less frequently.

The data from the sensors is compiled into a JSON object and is RESTfully sent through HTTP to the server along with the necessary header data. 

As mentioned previously, the original plan was to use both Lora and Wifi. Still, in the end, we only use Wifi for wireless transfer and I2C for communication between the two Arduino boards. 

The choice to use HTTP requests instead of MQTT or other similar transport protocols is because doing it this way makes it possible to gather and transfer data from anywhere as long as there is a Wifi connection with no additional setup or program installation necessary. If the setup works at home, it will also work elsewhere, as long as you provide the Wifi credentials. 

Taking it a step further, one could, in theory, create a mobile hotspot and send the environmental data wherever you are, telling you if you are justified to feel uncomfortable because of the heat. 

While Wifi does consume more energy than other alternatives like Lora, the range is practically infinite as long as you can find a Wifi hotspot. 

## Presenting the data

The frontend of the project is, as stated before, built by me using Nodejs, React, and Chartjs. It is a simple application for displaying the data in charts and is easily upgradable and modifiable. It was also made reactive down to a width of around 600px, making it possible to correctly view the data on small and big displays. 

The data is displayed on a line graph with the information on the Y-axis and the time on the X-axis, showing how the data changes over time.

<img src="https://user-images.githubusercontent.com/50659238/176964807-9175ef38-9164-4434-a709-cbbc31f13507.png" width="900">

You can also hover over any part of the graph to see the exact data stored in the database. 

<img src="https://user-images.githubusercontent.com/50659238/176965182-2244bf44-bdcc-490c-82f9-eabd4558d262.png" width="900">

The data from the sensors is saved in the database every time the Arduino sends a post request. The frontend and Arduino requests must go through the server to access the database. The following image shows what the data looks like inside the database using MongoDB Atlas.

<img src="https://user-images.githubusercontent.com/50659238/176965732-da42ddf9-2050-49be-89a3-a6323f28bfa0.png" width="900">

This is what the server response is when sending a get request for the data. The server also contains some unused CRUD functions that can be used for deleting or updating data.

<img src="https://user-images.githubusercontent.com/50659238/176966356-4a0dae88-0839-49fe-9820-41bfb9d7f6db.png" width="900">

## Finalizing the design


