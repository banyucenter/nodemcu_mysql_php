/*
 *  ENviando dados por requisição HTTP GET para o local host.
 */

#include <ESP8266WiFi.h>

const char* ssid     = "ivonir";//nome da rede
const char* password = "ivonir1225";//senha da rede

const char* host = "192.168.0.138";//ip do host que será enviada os dados

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Conectando com ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");  
  Serial.println("Endereco IP: ");
  Serial.println(WiFi.localIP());
}
//dados dos sensores que será enviados
float sensor1 = 10;  
float sensor2 = 20;
float sensor3 = 30;

void loop() {
  //dados atualizados a cada ciclo
  sensor1 = sensor1 + 2;
  sensor2 += 2;
  sensor3 += 2;
  
  Serial.print("Conectando com ");
  Serial.println(host);
  
  WiFiClient client;
  const int httpPort = 80;//porta da conexão TCP
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // Agora criaremos uma URI para a requisição
  String url = "/nodemcu_mysql_php/salvar.php?";
  url += "sensor1=";
  url += sensor1;
  url += "&sensor2=";
  url += sensor2;
  url += "&sensor3=";
  url += sensor3;
  
  Serial.print("Requisitando URL: ");
  Serial.println(url);
  
  // Envia a requisição para o servidor
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Conexao: fechada\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Cliente exedeu o tempo limite !");
      client.stop();
      return;
    }
    delay(10000);
  }
  
  while(client.available()){
    String line = client.readStringUntil('\r');
    //Serial.print(line);
    if(line.indexOf("salvo_com_sucesso") != -1){
      Serial.println();
      Serial.print("Salvo com seucesso!");
    }else if(line.indexOf("erro_ao_salva") != -1){
      Serial.println();
      Serial.print("Erro ao salvar");
    }
  }
  
  Serial.println();
  Serial.println("conexão fechada!");
}

