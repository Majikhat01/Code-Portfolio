#include "utils.h"
#include "secrets.h"

// Constants for time management
const long uS_TO_S_FACTOR = 1000000;
const long TIME_TO_SLEEP = 60 * uS_TO_S_FACTOR;

// Network and MQTT clients
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

// MQTT Topics
const char AWS_IOT_PUBLISH_TOPIC[] = "poolTables/RackEm-MC-test2/bat-test2";
const char AWS_IOT_STATUS_TOPIC[] = "poolTables/RackEm-MC-test2/status";
const char AWS_IOT_SUBSCRIBE_TOPIC[] = "poolTables/RackEm-MC-test2/commands";

// NTP and time management
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -25200;  // Mountain Time (MT)
const int daylightOffset_sec = 3600;  // Daylight Saving Time

String getFormattedTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return "";  // Return an empty string if time could not be obtained
    }
    
    char timeString[64]; // Buffer to hold the formatted date and time
    strftime(timeString, sizeof(timeString), "%Y-%m-%d_%H:%M:%S", &timeinfo);
    return String(timeString);  // Convert char array to String and return
}

void setupAWSIoT() {
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
  client.setServer(AWS_IOT_ENDPOINT, 8883);
  client.setCallback(messageHandler);
}

void ensureConnections() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  if (!client.connected()) {
    connectMQTT();
  }
}

void connectWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void connectMQTT() {
  Serial.println("Ensuring NTP time sync...");
  if (!timeIsSynchronized()) {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    waitForSync();
  }

  Serial.println("Connecting to AWS IoT...");
  setupAWSIoT();
  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(5000);
    Serial.println();
    printMQTTState(client.state());
  }
  if (client.connected()) {
    Serial.println("Connected to AWS IoT");
    client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
    Serial.println("Subscribed to AWS IoT topics!");
  } else {
    Serial.println("AWS IoT Timeout!");
  }
}

void waitForSync() {
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    delay(100);
    now = time(nullptr);
  }
  Serial.println("NTP time synchronized");
}

bool timeIsSynchronized() {
  struct tm timeinfo;
  return getLocalTime(&timeinfo) && time(nullptr) > 24 * 3600;
}

void printMQTTState(int state) {
  switch (state) {
    case -4: Serial.println("MQTT_CONNECTION_TIMEOUT - the server didn't respond within the keepalive time"); break;
    case -3: Serial.println("MQTT_CONNECTION_LOST - the network connection was broken"); break;
    case -2: Serial.println("MQTT_CONNECT_FAILED - the network connection failed"); break;
    case -1: Serial.println("MQTT_DISCONNECTED - the client is disconnected cleanly"); break;
    case 0:  Serial.println("MQTT_CONNECTED - the client is connected"); break;
    case 1:  Serial.println("MQTT_CONNECT_BAD_PROTOCOL - the server doesn't support the requested version of MQTT"); break;
    case 2:  Serial.println("MQTT_CONNECT_BAD_CLIENT_ID - the server rejected the client identifier"); break;
    case 3:  Serial.println("MQTT_CONNECT_UNAVAILABLE - the server was unable to accept the connection"); break;
    case 4:  Serial.println("MQTT_CONNECT_BAD_CREDENTIALS - the username/password were rejected"); break;
    case 5:  Serial.println("MQTT_CONNECT_UNAUTHORIZED - the client was not authorized to connect"); break;
    default: Serial.println("Unknown error");
  }
}
