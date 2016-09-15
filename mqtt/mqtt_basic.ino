#include <WiFiClient.h>
#include <Dhcp.h>
#include <WiFiUdp.h>
#include <Dns.h>
#include <WiFi.h>
#include <WiFiServer.h>

#include <Dhcp.h>
#include <EthernetUdp.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <Dns.h>
#include <WiFi.h>
#include <EthernetServer.h>

/*
 Basic MQTT example

 This sketch demonstrates the basic capabilities of the library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 
*/

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <WiFi.h>

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(172, 20, 9, 11);
IPAddress server(37, 187, 106, 16);

//WifiStuff
char ssid[] = "WLL"; //  your network SSID (name) 
char pass[] = "22Modvx#";    // your network password (use for WPA, or use as key for WEP)
WiFiClient wclient;
int status = WL_IDLE_STATUS;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

EthernetClient ethClient;
PubSubClient client(wclient);

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic","hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.print("Setup!");
  Serial.begin(57600);

  client.setServer(server, 1883);
  client.setCallback(callback);

  //wifi stuff
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.print("WiFi shield not present");
    // don't continue:
    while (true);
  }
  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0")
    Serial.print("Please upgrade firmware");

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Trying SSID: ");
    Serial.print(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);
    // wait 3 seconds for connection:
    Serial.print("Waiting...");
    delay(4000);
  }
  

  //Ethernet.begin(mac, ip);
  // Allow the hardware to sort itself out
  delay(1500);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
