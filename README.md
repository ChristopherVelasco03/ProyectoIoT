# 🤖 AILedMaster 🚀

¡Bienvenido a tu nuevo proyecto de chatbot IA! Este bot se hace pasar por una IA y permite a los usuarios interactuar con él para controlar un LED integrado. Interactuando con la IA, como por ejemplo: encender la luz y apagar la luz. ¡Sigue leyendo para más detalles!

# Proyecto NodeMCU 8266 y Gemini IA para Control de Iluminación

## 1. Definición del Proyecto

Este proyecto tiene como objetivo proporcionar un sistema de control de iluminación inteligente y eficiente energéticamente utilizando la placa NodeMCU 8266 y la inteligencia artificial de Gemini. Los usuarios pueden controlar la iluminación a través de comandos de voz dirigidos a la IA, permitiendo encender y apagar luces de manera sencilla y eficaz.

### Claridad y Relevancia del Objetivo

El objetivo de este proyecto es crear un sistema de control de iluminación que no solo sea fácil de usar, sino que también promueva el ahorro de energía. Esto es relevante tanto desde un punto de vista tecnológico, al integrar IA y IoT, como social, al contribuir a la eficiencia energética y la comodidad en el hogar.

### Innovación y Aplicabilidad

Este proyecto ofrece una solución innovadora al combinar el control por voz mediante IA con un sistema de iluminación basado en IoT. Sus aplicaciones prácticas incluyen hogares inteligentes y sistemas de gestión de edificios, proporcionando un acceso conveniente y un uso eficiente de los recursos energéticos.

## 2. Materiales Necesarios

### Lista Completa de Materiales

- Placa NodeMCU 8266
- Conexión a Internet (Wi-Fi)
- Cable de datos USB para NodeMCU

### Disponibilidad y Coste

Todos los materiales mencionados son fácilmente accesibles y de bajo costo. La placa NodeMCU 8266 es económica y ampliamente disponible en tiendas de electrónica y en línea.

## 3. Configuración del Hardware

### Conexión y Configuración de Sensores

En este proyecto, la NodeMCU 8266 no requiere sensores adicionales, ya que su función principal es controlar la iluminación mediante comandos a través de la IA de Gemini. A continuación se detallan las conexiones básicas:

- **LED Integrado en NodeMCU**: Conectado a través del pin D0 (GPIO16).

### Programación del Microcontrolador

La NodeMCU 8266 se programa para recibir comandos de la IA y controlar el estado del LED. El código puede ser escrito en Arduino IDE, utilizando la biblioteca ESP8266WiFi para la conexión a Internet y la API de Gemini para recibir los comandos.

```cpp
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
```

## 4. Almacenamiento de Datos

### Estructura de la Base de Datos

En este proyecto, no se requiere una base de datos compleja. Los datos relevantes son los comandos recibidos y el estado del LED (encendido/apagado), los cuales pueden ser almacenados en variables locales en el microcontrolador.

### Conexión y Almacenamiento de Datos

La conexión y almacenamiento de los datos se maneja localmente en la NodeMCU, y los comandos de la IA se procesan en tiempo real.

## 5. Desarrollo del Modelo de IA

### Preparación de Datos

La preparación de datos en este contexto implica asegurar que los comandos sean interpretados correctamente por la IA de Gemini.

### Selección y Entrenamiento del Modelo

El modelo de IA utilizado por Gemini está preentrenado para interpretar el como encender la luz y apagar la luz.

### Validación y Ajuste del Modelo

La validación del modelo se realiza probando diferentes comandos para garantizar que la IA responda adecuadamente y controle el LED según lo esperado.

## 6. Desarrollo de la Interfaz de Usuario

### Diseño de la Interfaz

La interfaz de usuario en este proyecto se basa en la comunicación por chat con la IA de Gemini, que es intuitiva y fácil de usar.

![image](https://github.com/ChristopherVelasco03/ProyectoIoT/assets/155390541/3d26c889-fc75-4167-b0a4-73e750ba0b6f)

### Implementación de Notificaciones

Las notificaciones y alertas no son necesarias en este caso, ya que el control es en tiempo real y directo a través de comandos.

## 7. Pruebas y Validación

### Pruebas Funcionales

Se han realizado pruebas exhaustivas para asegurar que los comandos sean interpretados correctamente y que el LED responda adecuadamente, encendiéndose y apagándose según los comandos.

![image](https://github.com/ChristopherVelasco03/ProyectoIoT/assets/155390541/8170c1db-0497-48b7-9594-9818d97139c7)

![image](https://github.com/ChristopherVelasco03/ProyectoIoT/assets/155390541/ea6c2b1c-f397-4002-999d-42d585b6bd0e)

![image](https://github.com/ChristopherVelasco03/ProyectoIoT/assets/155390541/98feb47e-aea8-4f06-ae95-57ef610e49c1)

![image](https://github.com/ChristopherVelasco03/ProyectoIoT/assets/155390541/20540eaa-11a8-498c-9c1b-cf7ca13087ca)

### Precisión del Modelo

La IA de Gemini ha demostrado ser precisa en la interpretación de comandos de voz bajo diferentes condiciones, garantizando un control confiable del sistema de iluminación.

-----
¡Gracias por usar este proyecto! Si tienes alguna pregunta o necesitas ayuda, no dudes en contactarme.
