#include <WiFi.h>
const char* ssid = "Cinnabon";
const char* password = "4hoursLong:)";
WiFiServer server(80);
String header = "";
void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
int val = 2;
String response = "N/A";
void loop(){
  WiFiClient client = server.available();   
  if (client) {
    Serial.println("New Client.");          
    String currentLine = "";                
    while (client.connected()) {            
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                    
        header += c;
        if (c == '\n') {                    
          
          if(header.indexOf("GET /1") >= 0){
              response = "Incorrect";
            }
            else if(header.indexOf("GET /2") >= 0){
              response = "correct";
            }
            else if(header.indexOf("GET /3") >= 0){
              response = "Incorrect";
            }
            else if(header.indexOf("GET /4") >= 0){
              response = "Incorrect";
            }
            else{
              response = "Please select a number.";
            }
          if (currentLine.length() == 0) {
            //header response
            client.println("HTTPS/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            Serial.println(header);
            // header doc
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".container {display: grid; grid-template-columns: 100px 100px 100px; padding: 2px; justify-self: center;}");
            client.println(".container > div {text-align: center; font-size:30px; border: 1px solid black; background-color: #f1f1f1; padding: 10px;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            //request handling
            
            //body
            client.println("<body><h1>Guess the value</h1>");

            client.println("<div class=\"container\">");
            client.println("<div><a href=\"1\">1</a></div>");
            client.println("<div><a href=\"2\">2</a></div>");
            client.println("<div><a href=\"3\">3</a></div>");
            client.println("<div><a href=\"4\">4</a></div>");
            client.println("<div><a href=\"5\">5</a></div>");
            client.println("<div><a href=\"6\">6</a></div>");
            client.println("<div><a href=\"7\">7</a></div>");
            client.println("<div><a href=\"8\">8</a></div>");
            client.println("<div><a href=\"9\">9</a></div>");
            client.println("<div class=\"\"><div><a href=\"0\">0</a></div></div>");
            client.println("</div>");   
            client.println("<p>" + response + "</p>");
            client.println("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;      
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}