// #ifndef WIFI_COMMUNICATION_H
// #define WIFI_COMMUNICATION_H

#include <WiFi.h>
#include "..\..\SECRETS\secret.h"
//#include "/path/to/your/library/library.h"
// Network Wi-Fi Info
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
byte mac[6];

void wifi_connection() // Wi-Fi Connection
{
    Serial.println(WiFi.status());
    /*    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Communication with WiFi module failed!");
        delay(10000);
        NVIC_SystemReset(); // Reset the Arduino
    }*/

    int i = 0;
    Serial.println("Connecting to WiFi: ");
    while (WiFi.begin(ssid, password) != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
        i++;
        if (i > 30) {
            break;
        }
    }
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("\nFailed to connect to Wi-Fi!");
        //NVIC_SystemReset(); // Reset the Arduino
    }
    Serial.println("\nConnected to Wi-Fi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    WiFi.macAddress(mac);
    Serial.print("MAC: ");
    Serial.print(mac[5], HEX);
    Serial.print(":");
    Serial.print(mac[4], HEX);
    Serial.print(":");
    Serial.print(mac[3], HEX);
    Serial.print(":");
    Serial.print(mac[2], HEX);
    Serial.print(":");
    Serial.print(mac[1], HEX);
    Serial.print(":");
    Serial.println(mac[0], HEX);
} //////////////////////////////////////////////////////////////////////////////////////////////////

bool wifi_reconnection() {
    bool attempt;
    int i = 0;
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Reconnecting to WiFi: ");
        while (WiFi.begin(ssid, password) != WL_CONNECTED)
        {
            Serial.print(".");
            delay(1000);
            i++;
            if (i > 5)
            {
                attempt = false;
                break;
            }
            else {
                attempt = true;
            }
        }
    }
return attempt;
}
// #endif