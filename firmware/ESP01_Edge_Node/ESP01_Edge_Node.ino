#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// =============================================================================
// NETWORK CONFIGURATION
// =============================================================================
const char* ssid     = "Malshan’s Iphone";
const char* password = "12345678";

// Host PC IPv4 address running Mosquitto
const char* mqtt_server = "172.20.10.7";
const int   mqtt_port   = 1883;

// =============================================================================
// NODE IDENTITY & MQTT TOPICS (ESP01)
// =============================================================================
const char* mqtt_clientid = "EE2120_ESP8266_01";
const char* mqtt_user     = "esp01";
const char* mqtt_password = "stud1"; // Password set in mosquitto_passwd

const char* temp_topic       = "EE2120/ESP01/temp";
const char* led_topic        = "EE2120/ESP01/LED/cmd";
const char* led_status_topic = "EE2120/ESP01/LED/status";

// =============================================================================
// HARDWARE DEFINITION & ACTIVE-LOW LOGIC
// =============================================================================
#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

// ESP8266 onboard LED is typically Active-LOW
#define LED_ON  LOW
#define LED_OFF HIGH

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsgTime = 0;

// -----------------------------------------------------------------------------
// Inbound MQTT Callback Handler
// -----------------------------------------------------------------------------
void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("[RX] Topic: ");
  Serial.print(topic);
  Serial.print(" | Payload: ");
  Serial.println(message);

  if (String(topic) == led_topic) {
    if (message == "1") {
      digitalWrite(LED_BUILTIN, LED_ON);
      client.publish(led_status_topic, "1");
      Serial.println("[ACTUATOR] LED -> ON | State Verified: 1");
    } else if (message == "0") {
      digitalWrite(LED_BUILTIN, LED_OFF);
      client.publish(led_status_topic, "0");
      Serial.println("[ACTUATOR] LED -> OFF | State Verified: 0");
    }
  }
}

// -----------------------------------------------------------------------------
// Wi-Fi Connection Manager
// -----------------------------------------------------------------------------
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("[WIFI] Connecting to SSID: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("[WIFI] Connection Established");
  Serial.print("[WIFI] Device Assigned IP: ");
  Serial.println(WiFi.localIP());
}

// -----------------------------------------------------------------------------
// MQTT Broker Session Manager
// -----------------------------------------------------------------------------
void reconnect() {
  while (!client.connected()) {
    Serial.print("[MQTT] Connecting to Broker as ");
    Serial.print(mqtt_clientid);
    Serial.print("...");

    if (client.connect(mqtt_clientid, mqtt_user, mqtt_password)) {
      Serial.println(" Connected.");

      // Subscribe to command channel
      client.subscribe(led_topic);
      Serial.print("[MQTT] Subscribed to topic: ");
      Serial.println(led_topic);

      // Publish initial state verification
      // If pin reads LOW, LED is ON (state 1), else OFF (state 0)
      int currentLedState = (digitalRead(LED_BUILTIN) == LED_ON) ? 1 : 0;
      client.publish(led_status_topic, currentLedState ? "1" : "0");
    } else {
      Serial.print(" Failed (rc=");
      Serial.print(client.state());
      Serial.println("). Retrying in 2 seconds...");
      delay(2000);
    }
  }
}

// -----------------------------------------------------------------------------
// Setup & Main Loop
// -----------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LED_OFF); // Initialize turned off

  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Telemetry loop: 1 Hz interval
  unsigned long now = millis();
  if (now - lastMsgTime > 1000) {
    lastMsgTime = now;

    // Simulated temperature reading: 20.0 to 40.0 °C
    float temperature = random(200, 400) / 10.0;

    char tempString[8];
    dtostrf(temperature, 1, 1, tempString);

    client.publish(temp_topic, tempString);

    Serial.print("[TX] Telemetry: ");
    Serial.print(temp_topic);
    Serial.print(" = ");
    Serial.print(tempString);
    Serial.println(" °C");
  }
}