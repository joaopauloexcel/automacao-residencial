#include <ESP8266WiFi.h>//Biblioteca do WiFi.
#include <WiFiUdp.h>//Biblioteca do UDP.
 
WiFiUDP udp;//Cria um objeto da classe UDP.

const int LM35 = 0;
float temperatura = 0;
int ADClido = 16;
float valor=0;

#define Delay_node 500
#define Delay_rasp 500
#define Delay_le 500
#define Delay_con 1000

int Tempo_node= 0;
int Tempo_rasp = 0;
int Tempo_le = 0;

const char* ssid1 = "Loading";
const char* password1 = "teste123";
const char* host = "192.168.0.149";
 
void le_temperatura();
void envia_rasp();
void envia_node();
 
void setup()
{
   Serial.begin(115200);
   pinMode(D4, OUTPUT);//Habilita o LED onboard como saida.
   digitalWrite(D4, 1);//Desliga o LED.
   WiFi.mode(WIFI_STA);//Define o ESP8266 como Station.
}
 
void loop()
{
   if(millis() - Tempo_le >=Delay_le)
  {
    Tempo_le=millis();
    le_temperatura();
  }
  if(millis() - Tempo_rasp >=Delay_rasp)
  {
    Tempo_rasp=millis();
    envia_rasp();
  }
  if(millis() - Tempo_node >=Delay_node)
  {
    Tempo_node=millis();
     envia_node();
  }
}
 
void envia_rasp(){
  Serial.println("Conectando ao rasp");
  WiFi.begin(ssid1, password1);  
  while(WiFi.status() != WL_CONNECTED) {
    delay(150);
    Serial.println(".");
    if (Tempo_rasp <=Delay_con) {
      loop();
    }
  }
  delay(1);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    return;
  }
  Serial.println("Conectado Rasp");
  // Enviando para o host a temperatura lida.
  client.print(String("GET /grava_temperatura.php?valor=") + (valor) +
                      " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  Serial.print("Enviado: ");
  Serial.println(valor);
  client.flush();
  client.stop();
}

void envia_node(){
   Serial.println("Conectando ao node");
   WiFi.begin("NodeMCU", ""); 
   while(WiFi.status() != WL_CONNECTED) {
    delay(150);
    Serial.println(".");
    if (Tempo_node <=Delay_con) {
      loop();
    }
  }
  Serial.println("Conectado Node");
  delay(1);
  udp.beginPacket("192.168.4.1", 555);//Inicializa o pacote de transmissao ao IP e PORTA.
  udp.println(valor);//Adiciona-se o valor ao pacote.
  Serial.print("Enviado: ");
  Serial.print(valor);
  udp.endPacket();//Finaliza o pacote e envia.
  udp.stop();
}

void le_temperatura(){
  ADClido = analogRead(LM35);
  temperatura = (ADClido/1024.0) * 3300; 
  valor = temperatura/10; //transformo em Xº
  Serial.println(valor);
}
