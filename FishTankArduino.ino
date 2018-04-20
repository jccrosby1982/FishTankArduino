#include <SPI.h>
#include <WiFi.h>

WiFiClient client;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  //setup the wifi connection
  setupWifi("SSID", "PASSWORD");
}

void loop() {
  double temp = 72.6;
  String temp_str = String(temp);
  sendThingspeak(temp_str, "6.2", "24");
  delay(16000);
}

void sendThingspeak(String temp, String ph, String turbidity){
    //connect to server
    Serial.println("\nStarting connection to server...");
    // if you get a connection, report back via serial:
    if (client.connect("api.thingspeak.com", 80)) {
    Serial.println("Connected to server");
    // Make a HTTP request:
    client.println("GET /update?api_key=HN90RV1R8XIM72XR&field1=" + temp + "&field2=" + ph + "&field3=" + turbidity + " HTTP/1.1");
    Serial.println("Request sent");
    client.println("Host: api.thingspeak.com");
    client.print("Connection: close\n");
    Serial.println("Connection closed");
    client.println();
  }
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();
  }  
}

void setupWifi(char* ssid, char* pass){
  int status = WL_IDLE_STATUS;
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }
  //check firmware version
  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}






