#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "AEE-I";
const char* password = "53968517";

WebServer server(80);

Servo servoMotor;

// posição inicial
int repouso = 0;

// posição que aperta botão
int apertar = 90;

void pressionarBotao() {

  // mover servo
  servoMotor.write(apertar);

  delay(1000);

  // voltar posição
  servoMotor.write(repouso);

  server.send(200, "text/plain", "Botão pressionado");
}

void setup() {

  Serial.begin(115200);

  // servo no pino 13
  servoMotor.attach(13);

  servoMotor.write(repouso);

  // conectar wifi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado!");

  Serial.print("IP ESP32: ");
  Serial.println(WiFi.localIP());

  // rota do botão
  server.on("/pressionar", pressionarBotao);

  server.begin();
}

void loop() {

  server.handleClient();

}