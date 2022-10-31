#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "AAATI";
const char *password = "AAATI@2022";
int PWMA=5;//Right side 
int PWMB=4;//Left side 
int DA=0;//Right reverse 
int DB=2;//Left reverse 
AsyncWebServer server(80);
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
       <style>
          .bola-direcional {
            width: 150px;
            height: 150px;
            border-radius: 50%;
            background: #bdbdbd;
            position: relative;
            z-index: 9999;
            margin: 47px 0 0 46px;
            box-shadow: inset 0px 0px 7px #AEACAC;
            border: 1px solid #bdbdbd;
          }
          .gambi {
            width: 114px;
            height: 40px;
            background: #5B5B5B;
            position: absolute;
            z-index: 999991;
            margin: -97px 0 0 17px;
          }
          .dir-l-r{
            width: 120px;
            height: 40px;
            background: #5B5B5B;
            position: relative;
            z-index: 99999;
            margin: 55px auto;
            box-shadow: -1px 1px 3px #333;
            border: 2px solid #333;
            border-radius: 3px;
          }
          .bola-meio-dir {
            width: 30px;
            height: 30px;
            border-radius: 50%;
            background: #5A5A5A;
            margin: -90px 0 0 59px;
            position: absolute;
            z-index: 999999;
            box-shadow: inset 0px 0px 10px #1F1F1F;
          }
          .dir-u-d{
            width: 40px;
            height: 120px;
            background: #5B5B5B;
            position: relative;
            z-index: 99999;
            margin: -137px auto;
            box-shadow: -1px 1px 3px #333;
            border: 2px solid #333;
            border-radius: 3px;
          }
          
          
          .arrow-r, .arrow-l, .arrow-u, .arrow-d{
            position: absolute;
            margin: -89px 0 0 110px;
            z-index: 999999;
          }
          .arrow-l {
            margin: -89px 0 0 -1px;
            -webkit-transform: rotate(180deg);
          }
          .arrow-u {
            margin: -142px 0 0 56px;
            -webkit-transform: rotate(-90deg);
          }
          .arrow-d {
            margin: -33px 0 0 55px;
            -webkit-transform: rotate(90deg);
          }
          .arrow-r:before, .arrow-l:before, .arrow-u:before, .arrow-d:before {
            content: "";
            display: inline-block;
            vertical-align: middle;
            margin-right: 10px;
            width: 10px; 
            height: 0; 
            border-top: 12px solid transparent;
            border-bottom: 12px solid transparent;
            border-left: 20px solid #6E6C6C;
          }
          .arrow-l:before{
            border-top: 12px solid transparent;
            border-bottom: 12px solid transparent;
            border-left: 20px solid #6E6C6C;
          }
          .arrow-u:before{
            border-top: 12px solid transparent;
            border-bottom: 12px solid transparent;
            border-left: 20px solid #6E6C6C;
          }
          .arrow-d:before{
            border-top: 12px solid transparent;
            border-bottom: 12px solid transparent;
            border-left: 20px solid #6E6C6C;
          }
     </style>
</head>
<body>
  <div class="bola-direcional">
      <div class="dir-l-r"></div>
      <div class="bola-meio-dir"></div>
      <div class="gambi"></div>
      <div class="arrow-r" onmousedown="Direta()" onmouseup="Parar()" ontouchstart="Direta()" ontouchend="Parar()"></div>
      <div class="arrow-l" onmousedown="Esquerda()" onmouseup="Parar()" ontouchstart="Esquerda()" ontouchend="Parar()"></div>
      <div class="arrow-u" onmousedown="Frente()" onmouseup="Parar()" ontouchstart="Frente()" ontouchend="Parar()"></div>
      <div class="arrow-d" onmousedown="Tras()" onmouseup="Parar()" ontouchstart="Tras()" ontouchend="Parar()"></div>
      <div class="dir-u-d"></div>
  </div>
</body>
<script>
function Frente () {
  var xhttp = new XMLHttpRequest();
  xhttp.open("POST", "/Frente", true);
  xhttp.send();
}
function Tras () {
  var xhttp = new XMLHttpRequest();
  xhttp.open("POST", "/Tras", true);
  xhttp.send();
}
function Direta () {
  var xhttp = new XMLHttpRequest();
  xhttp.open("POST", "/Direta", true);
  xhttp.send();
}
function Esquerda () {
  var xhttp = new XMLHttpRequest();
  xhttp.open("POST", "/Esquerda", true);
  xhttp.send();
}
function Parar () {
  var xhttp = new XMLHttpRequest();
  xhttp.open("POST", "/Parar", true);
  xhttp.send();
}
</script>
</html>)rawliteral";

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password, 12, true, 1);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
 pinMode(PWMA, OUTPUT); 
 pinMode(PWMB, OUTPUT); 
 pinMode(DA, OUTPUT); 
 pinMode(DB, OUTPUT);
  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  server.on("/Frente", HTTP_POST, [](AsyncWebServerRequest *request){
   frente();
   request->send_P(200,"application/json","{'resultado':'OK'}");
  });
  server.on("/Tras", HTTP_POST, [](AsyncWebServerRequest *request){
   tras();
   request->send_P(200,"application/json","{'resultado':'OK'}");
  });
  server.on("/Esquerda", HTTP_POST, [](AsyncWebServerRequest *request){
   esquerda();
   request->send_P(200,"application/json","{'resultado':'OK'}");
  });
  server.on("/Direta", HTTP_POST, [](AsyncWebServerRequest *request){
   direita();
   request->send_P(200,"application/json","{'resultado':'OK'}");
  });
  server.on("/Parar", HTTP_POST, [](AsyncWebServerRequest *request){
   parar();
   request->send_P(200,"application/json","{'resultado':'OK'}");
  });
  server.begin();
}
void esquerda()
{
  digitalWrite(PWMA, 450); 
  digitalWrite(DA, HIGH); 
    
  digitalWrite(PWMB, 450); 
  digitalWrite(DB, LOW);
}

void direita()
{
   digitalWrite(PWMA, 450); 
  digitalWrite(DA, LOW); 
   
  digitalWrite(PWMB, 450); 
  digitalWrite(DB, HIGH);
}
void parar()
{
  digitalWrite(PWMA, LOW); 
  digitalWrite(DA, LOW); 
     
  digitalWrite(PWMB, LOW); 
  digitalWrite(DB, LOW); 
}
void frente()
{
  digitalWrite(PWMA, HIGH); 
  digitalWrite(DA, LOW); 
    
  digitalWrite(PWMB, HIGH); 
  digitalWrite(DB, LOW);
}
void tras()
{
  digitalWrite(PWMA, HIGH); 
  digitalWrite(DA, HIGH); 
     
  digitalWrite(PWMB, HIGH); 
  digitalWrite(DB, HIGH);
}

void loop(){  
}
