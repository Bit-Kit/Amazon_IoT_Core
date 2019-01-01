#include <ESP8266WiFi.h>
#include <AmazonIOTClient.h>
#include <Esp8266AWSImplementations.h>
Esp8266HttpClient httpClient;
Esp8266DateTimeProvider dateTimeProvider;
AmazonIOTClient iotClient;
ActionError actionError;
const char* ssid = "XXXXXXX";
const char* password = "XXXXXXX";
void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect to WAP
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  iotClient.setAWSRegion("eu-west-1");
  iotClient.setAWSEndpoint("amazonaws.com");
  iotClient.setAWSDomain("zxzxzxzxzxzxzxzx-ats.iot.eu-west-1.amazonaws.com");
  iotClient.setAWSPath("/things/esp8266/shadow");
  iotClient.setAWSKeyID("ZZZZZZZZZZZZZZZ");
  iotClient.setAWSSecretKey("YYYYYYYYYYYYYYYYYYYYYYYYYYY");
  iotClient.setHttpClient(&httpClient);
  iotClient.setDateTimeProvider(&dateTimeProvider);
}

void loop(){
  char* shadow = "{\"temp\":{\"reported\": {\"value\": \"bar\"}}}";

  char* result = iotClient.update_shadow(shadow, actionError);
  Serial.print(result);

  delay(5000); //5sec
}
