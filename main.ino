#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Wi-Fi Credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Telegram Bot Credentials
const char* botToken = "YOUR_TELEGRAM_BOT_TOKEN";
const String chatID = "YOUR_TELEGRAM_CHAT_ID";

// Light Sensor Pin
#define LIGHT_SENSOR_PIN A0  // Analog pin for MH Light Sensor

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");
    
    client.setInsecure();  // Required for Telegram SSL
}

void loop() {
    int lightValue = analogRead(LIGHT_SENSOR_PIN);
    Serial.print("Light Sensor Value: ");
    Serial.println(lightValue);

    String message = "🌞 Light Sensor Data:\n";
    message += "🔹 Intensity: " + String(lightValue) + "\n";
    message += "📅 Time: " + String(millis() / 1000) + "s since start";

    bot.sendMessage(chatID, message, "");

    delay(5000);  // Send data every 5 seconds
}
