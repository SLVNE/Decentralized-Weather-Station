#include <Wire.h>
#include <WiFiNINA.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1021.221)
#define SECRET_SSID "COhatch"   //Your SSID
#define SECRET_PASS "CO2016!!"  //Your password

Adafruit_BME280 bme;

// Old code for when I was implementing a display
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
char ssid[] = SECRET_SSID;        // network SSID (name)
char pass[] = SECRET_PASS;    // network password (use for WPA, or use as key for WEP)
int keyIndex = 0;  // network key index number (needed only for WEP)
float referencePressure = 1018.6;  // hPa local QFF (official meteor-station reading)
float outdoorTemp = 4.7;           // C  measured local outdoor temp.
float barometerAltitude = 1650.3;  // meters ... map readings + barometer position

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  Serial.begin(9600);

  // check if bme sensor is available
  if (!bme.begin(0x76)) {
		Serial.println("Could not find a valid BME280 sensor, check wiring!");
		while (1);
	}
   
  pinMode(LED_BUILTIN, OUTPUT);

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // connect board to a WPA/WPA2 wirelessnetwork
    status = WiFi.begin(ssid, pass);
  }
  // check if the module has connected to the internet
  if(status = WL_CONNECTED){
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Connected.");
  }
  // prepare server for transmitting data
  server.begin();
  // the weather module is connected now, let's print this status
  printWifiStatus();
  // begin module-sensor correspondence
  Wire.begin();
}

void loop() {
  // collect measurements from the sensor
  float temp(bme.readTemperature()), hum(bme.readHumidity()), pres(bme.readPressure()/ 100.0F), alt(bme.readAltitude(SEALEVELPRESSURE_HPA));
  WiFiClient client = server.available();
  // perform a check on the availability of the server
  if (client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true;  // an HTTP request ends with a blank line, we'll use this for a switch later in the code
    while (client.connected()) {        // run for as long as the client instance is connected to server
      if (client.available()) {         // check if the client is available
        char c = client.read();
        Serial.write(c);
        // if newline received and the line is blank, the HTTP request has ended and we can proceed with creating a HTTP header
        if (c == '\n' && currentLineIsBlank) {
          // dynamically generate a HTTP response header and refresh the page automatically every 5 sec
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close"); 
          client.println("Refresh: 5");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head>");
          client.print("<title>Decentralized Weather Station</title>");
          client.println("</head>");
          client.print("<body>");
          client.print("<h1><center>DECENTRALIZED WEATHER STATION</center></h1>");
          client.print("<h2><center>Weinstein Readings:</center></h2>");
          client.print("</body>");
          client.print("</html>");
          client.print("<center>");
          client.print("<h2><p>Temp: ");
          client.print(temp);
          client.print(" C");
          client.println("<br />");
          client.println("<br />");
          client.print("\t\tHumidity: ");
          client.print(hum);
          client.print("% RH");
          client.println("<br />");
          client.println("<br />");
          client.print("\t\tPressure: ");
          client.print(pres);
          client.print(" hPa");
          client.println("<br />");
          client.println("<br />");
          client.print("\t\tAltitude: ");
          client.print(alt);
          client.print(" m");
          client.println("<br />");
          client.println("<br />");
          client.print("\t\tDew point: ");
          client.print(temp - ((100-hum)/5));
          client.print(" C");
          client.println("<br />");
          client.println("</html>");
          client.print("<style>body{background-color: White ;}");// You can choose your backround-color
          break;
        }
        if (c == '\n') {
          // starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // got a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser some time to receive the data
    delay(1);
    // close the connection to refresh the page
    client.stop();
    Serial.println("client disconnected");
  }
}

void printWifiStatus() {
  // print the SSID of the network the module is attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  // print received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}