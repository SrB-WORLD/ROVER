#include <SPI.h>
#include <WiFi101.h>
#include <WiFiServer.h>
#include <WiFiClient.h>

char ssid[] = "Showrob"; // your network SSID (name)
char pass[] = "234156987"; // your network password

int status = WL_IDLE_STATUS;
IPAddress nodeIP(172, 20, 10, 4);  // IP address of your Node.js server
WiFiServer httpServer(80); // HTTP server on port 80

WiFiClient client;

const int sensorPin = A0;
long int voltage;
int plotter = 0;
const float restValue = 2780;
const float threshold = 20;

void setup() {
  pinMode(sensorPin,INPUT);
  Serial1.begin(600);

  Serial.begin(9600);

  // Check for the presence of the WiFi shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true); // Don't proceed if WiFi shield is not present
  }

  // Attempt to connect to WiFi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass); // Connect to WiFi network
    delay(1); // Wait 10 seconds for connection
  }
  Serial.println("Connected to WiFi");

  // Start the HTTP server
  httpServer.begin();
  Serial.println("HTTP server started");

  // Print the IP address of the Arduino
  Serial.print("Arduino IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected to the HTTP server
  WiFiClient client = httpServer.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("New client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request
  if (request.indexOf("/fetchPolarity") != -1) {
    sendPolarityData(client);
  }
  else if(request.indexOf("/forward") != -1){
    forward(client);
  }
  else if(request.indexOf("/fetchIR") != -1){
    IR(client);
  }

  else {
    client.println("HTTP/1.1 404 Not Found");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<body>");
    client.println("<h1>Not Found</h1>");
    client.println("</body>");
    client.println("</html>");
  }

  // Close the connection
  client.stop();
  Serial.println("Client disconnected");

  delay(1); // Delay before checking for new clients again
}

void sendPolarityData(WiFiClient client) {
  String data = magnet(); // Replace with actual data to send
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(data);
}
void forward(WiFiClient client){
  
  String data = "Some polarity data"; // Replace with actual data to send
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(data);
  
}

void IR(WiFiClient client){
  
  String data = IR(); // Replace with actual data to send
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(data);
  
}

String magnet(){
    voltage = analogRead(sensorPin) * 4.88;
    String polarity;
    Serial.println(voltage);

    if(voltage > restValue + threshold){
      polarity = "south";
      return polarity;
      //Serial.print("The polarity is ");
      //Serial.println(polarity);
    }   
    else if(voltage < restValue - threshold){
      polarity = "north";
      return polarity;
      Serial.print("The polarity is ");
      Serial.println(polarity);
    }
    else{
      polarity = "uncertain";
      return polarity;
      //Serial.print("The polarity is: ");
      //Serial.println(polarity);
    }
  }

  String IR(){
    String species= "abronia";
    return species;
  }


