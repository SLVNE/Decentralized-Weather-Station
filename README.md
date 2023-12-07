# Decentralized-Weather-Station

CSC4640 Microcontroller Programming - Final Project Proposal
Decentralized Environmental Monitoring Station
Member Names: Silvian Ene

1. What project?
I am building a standalone environmental monitoring station that would make its
user less reliant on centralized monitoring stations that may or may not tamper
with data or provide inaccurate information due to their distance from the
house/place where the user is actually located.
The data that will be shown consists of Altitude, Weather, and Temperature.
More might be added depending on how smoothly the project goes.
Parts list:
• BME280 High Precision Altimeter Atmospheric Sensor $20
• Jumper wires $5
• Arduino Uno Board $25
• Adafruit 128x64 OLED Display Feather Wing $20
• Powerbank $20
It works by collecting environmental data from the BME280 sensor, process that
data using the Arduino Board, and show the results on the OLED Display.

2. Design specifications:
- Altitude: +-3 meters
- Pressure: 300-1100hPa +=1hPa
- Humidity: 0-100% with +-3% accuracy.
- Temperature: -20 to +45 Celsius with an accuracy of +-1 degree.

The project will be powered by a powerbank to increase ease of use for the user,
the approximate weight will be under 1lb and its size will roughly be 15x5x5cm.

3. Bill of Materials:
- BME280 $10
- Jumper wires $5
- Arduino Uno Board $25
- Adafruit 128x64 OLED Display Feather Wing $20
- Powerbank / 9V battery (To be determined) $20
Total Projected Cost: $80.

4. Block Diagram: Attached in PDF.

5. Tentative schematic Attached in PDF

6. Testing plan
The project will be tested by comparing the temperature and humidity sensor with
instruments found in my house. Altitude and pressure will be tested by comparing
data from my phone with the data we get from the Arduino’s system.

7. Timeline
November 1-15th research and development (R&D)
November 15th
-25th finish first prototype and make sure everything works well.
November 25th – December 1st complete the final version and get ready to present.
December 4th – I will present the project in the classroom.
