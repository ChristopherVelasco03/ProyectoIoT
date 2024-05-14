# 🤖 AILedMaster 🚀

¡Bienvenido a tu nuevo proyecto de bot en Telegram! Este bot se hace pasar por una IA y permite a los usuarios interactuar con él para controlar un LED integrado. Usa comandos sencillos como `ledon` y `ledoff` para encender y apagar el LED. ¡Sigue leyendo para más detalles!

## 📋 Descripción del Proyecto

Este proyecto utiliza un ESP32 o ESP8266 para conectarse a Wi-Fi y controlar un LED mediante comandos enviados a través de un bot de Telegram. El bot responde a comandos específicos para encender, apagar y verificar el estado del LED.

## 🚀 Comenzando

### Requisitos

- Una placa ESP32 o ESP8266
- Conexión a Internet
- Cuenta de Telegram

### Configuración

1. **Clona el repositorio:**
   ```bash
   git clone https://github.com/tu-usuario/tu-repo.git
   cd tu-repo
   ```

2. **Instala las librerías necesarias:**
   - [Universal Telegram Bot Library](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot)
   - [ArduinoJson](https://github.com/bblanchon/ArduinoJson)

3. **Configura las credenciales Wi-Fi y el token del bot:**
   En el archivo `main.ino`, reemplaza las siguientes líneas con tus credenciales:
   ```cpp
   const char* ssid = "TU_SSID";
   const char* password = "TU_PASSWORD";
   #define BOTtoken "TU_BOT_TOKEN"  // Token del bot de Telegram
   #define CHAT_ID "TU_CHAT_ID"  // ID del chat de Telegram
   ```

### Uso y ejemplo

Carga el código en tu ESP32 o ESP8266 y abre el monitor serie para ver los mensajes de depuración. Asegúrate de que tu dispositivo esté conectado a la red Wi-Fi.

![image](https://github.com/ChristopherVelasco03/ProyectoIoT/assets/155390541/4b6ceb3f-7fbf-44e6-aaca-fe37f9e03f8f)


### Comandos del Bot

- `/start` - Muestra un mensaje de bienvenida y lista de comandos.
- `/led_on` - Enciende el LED.
- `/led_off` - Apaga el LED.
- `/state` - Muestra el estado actual del LED (encendido/apagado).

## 🔧 Código

```cpp
#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   
#include <ArduinoJson.h>

const char* ssid = "TU_SSID";
const char* password = "TU_PASSWORD";
#define BOTtoken "TU_BOT_TOKEN"
#define CHAT_ID "TU_CHAT_ID"

#ifdef ESP8266
  X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;
const int ledPin = 2;
bool ledState = LOW;

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Usuario no autorizado", "");
      continue;
    }

    String text = bot.messages[i].text;
    Serial.println(text);
    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Bienvenido, " + from_name + ".\n";
      welcome += "Usa los siguientes comandos para controlar el LED.\n\n";
      welcome += "/led_on para encender el LED \n";
      welcome += "/led_off para apagar el LED \n";
      welcome += "/state para ver el estado actual del LED \n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "/led_on") {
      bot.sendMessage(chat_id, "LED encendido", "");
      ledState = HIGH;
      digitalWrite(ledPin, ledState);
    }

    if (text == "/led_off") {
      bot.sendMessage(chat_id, "LED apagado", "");
      ledState = LOW;
      digitalWrite(ledPin, ledState);
    }

    if (text == "/state") {
      if (digitalRead(ledPin)){
        bot.sendMessage(chat_id, "El LED está encendido", "");
      } else {
        bot.sendMessage(chat_id, "El LED está apagado", "");
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  #ifdef ESP8266
    configTime(0, 0, "pool.ntp.org");
    client.setTrustAnchors(&cert);
  #endif

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  #endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("respuesta recibida");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
```

## 🤝 Contribuciones

¡Las contribuciones son bienvenidas! Si tienes alguna mejora o nueva funcionalidad que te gustaría añadir, por favor abre un issue o envía un pull request.

## 📄 Licencia

Este proyecto está bajo la Licencia MIT. Consulta el archivo [LICENSE](LICENSE) para más detalles.

## 🌟 Agradecimientos

- [Brian Lough](https://github.com/witnessmenow) por la fantástica [librería Universal Telegram Bot](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot).

¡Gracias por usar este proyecto! Si tienes alguna pregunta o necesitas ayuda, no dudes en contactarme.

---
¡Diviértete controlando tu LED con Telegram! 🚀💡
