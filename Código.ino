#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// SSID y contraseña de tu red WiFi
const char* ssid = "";  // Reemplaza con tu SSID
const char* password = "";  // Reemplaza con tu contraseña

// Definición del pin GPIO al que está conectada la luz
const int LED_PIN = 2;  // Cambia esto según el pin que estés usando

ESP8266WebServer server(80);

// Función para manejar CORS
void handleCors() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  server.send(204);  // Sin contenido para las solicitudes OPTIONS
}

// Función para manejar la solicitud de encender la luz
void handleEncender() {
  digitalWrite(LED_PIN, HIGH);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Luz encendida");
}

// Función para manejar la solicitud de apagar la luz
void handleApagar() {
  digitalWrite(LED_PIN, LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Luz apagada");
}

void setup() {
  // Inicializar el pin GPIO para la luz
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Asegúrate de que la luz está apagada al inicio

  // Iniciar la comunicación serie para depuración
  Serial.begin(115200);

  // Conectar a la red WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red WiFi...");
  }
  Serial.println("Conectado a la red WiFi");

  // Configurar las rutas del servidor web
  server.on("/encender", HTTP_GET, handleEncender);
  server.on("/apagar", HTTP_GET, handleApagar);
  server.on("/apagar", HTTP_OPTIONS, handleCors);
  server.on("/encender", HTTP_OPTIONS, handleCors);

  // Iniciar el servidor web
  server.begin();
  Serial.println("Servidor web iniciado");
}

void loop() {
  // Manejar las solicitudes de los clientes
  server.handleClient();
}
