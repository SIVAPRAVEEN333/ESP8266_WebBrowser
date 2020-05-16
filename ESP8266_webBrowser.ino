#include <ESP8266WiFi.h>

#define Control_Pin LED_BUILTIN

const char *ssid="ACT108377024771";
const char *password="72694397";

//#define ssid "ACT108377024771"
//#define password "72694397"


unsigned char led_status=0;
WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(Control_Pin,OUTPUT);
digitalWrite(Control_Pin,LOW);
Serial.println();
Serial.println("Connecting to");
Serial.println(ssid);

WiFi.begin(ssid,password);
while(WiFi.status() != WL_CONNECTED)
{
  delay(500);
  Serial.println("Trying to connect...");
}
Serial.println("");
Serial.println("WiFi Connected...");

server.begin();
Serial.println("Server Started");
Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
WiFiClient client=server.available();

if(!client)
{
  return;
}
Serial.println("New Client...");
while(!client.available())
{
  delay(1);
}
String data=client.readStringUntil('\r');
Serial.println(data);
client.flush();

if(data.indexOf("/ledoff") !=-1)
{
  led_status=0;
  digitalWrite(Control_Pin,LOW);
  Serial.println("LED_OFF");
}
else if(data.indexOf("/ledoff") !=-1)
{
  led_status=1;
  digitalWrite(Control_Pin,HIGH);
  Serial.println("LED_ON");
}
String web="HTTP/1.1 200 OK\r\nContent-Type:text/html\r\n\r\n ";
web += "<html>\r\n";
web += "<html>\r\n";
web += "<h1>LED Status <h1>\r\n";
web += "<p>\r\n";

if(led_status==1)
{
  web +="LED On\r\n"; 
}
else
{
  web +="LED Off\r\n";
}

web += "</p>\r\n";
web += "<p>\r\n";
web += "a href=\"/ledon\">\r\n";
web += "<button>LED On</button>\r\n";
web += "</a>\r\n";
web += "</p>\r\n";

web += "<a href=\"/ledoff\">\r\n";
web += "<button>LED Off</button>\r\n";
web += "</a>\r\n";

web += "</body>\r\n";
web += "</html>\r\n";
client.print(web);
}
