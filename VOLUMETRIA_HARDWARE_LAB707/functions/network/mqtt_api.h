#include <WiFiNINA.h>
WiFiSSLClient wifiClient;
#include <PubSubClient.h>
PubSubClient mqttClient(wifiClient);
#include "..\..\SECRETS\secret.h"

// MQTT broker's domain, port (TLS), User, Password, Topic
const int mqttPort = 8883;
const char *mqttServer = SECRET_BROKER_MQTT;
const char *mqttUsername = SECRET_SSID_MQTT;
const char *mqttPassword = SECRET_PASS_MQTT;
const char *mqttID = SECRET_ID_MQTT;
const char topic[] = SECRET_TOPIC_MQTT;
// char send_msg[50];

void mqtt_connection() // MQTT Connection
{
    mqttClient.setServer(mqttServer, mqttPort);
    // Set MQTT server and callback function
    // mqttClient.setCallback(callback);             ////////
    // Connect to the MQTT broker (TLS)
    Serial.print("Connecting to MQTT broker...");
    while (!mqttClient.connect(mqttID, mqttUsername, mqttPassword))
    {
        Serial.print(".");
        delay(1000);
    }

    if (mqttClient.connected())
    {
        Serial.println("\nConnected to MQTT broker!");
    }
    else
    {
        Serial.println("\nFailed to connect to MQTT broker!");
    }
} 

bool reconnection_mqtt()
{
    bool x;
    if (!mqttClient.connected())
    {
        // Reconnect if the MQTT connection is lost
        Serial.print("Attempting MQTT reconnection...");
        while (!mqttClient.connect(mqttID, mqttUsername, mqttPassword))
        {
            Serial.print(".");
            delay(1000);
        }
    }
    if (mqttClient.connected())
    {
        Serial.println("\nReconnected to MQTT broker!");
        x = false;
    }
    else
    {
        Serial.println("\nFailed to reconnect to MQTT broker!");
        x = true;
    }
    return x;
}

void send_message_mqtt(String jsonString) // Send message using mqttClient
{
    if (mqttClient.connected())
    {
        // Publish the JSON data to the MQTT topic
        if (mqttClient.publish(topic, jsonString.c_str()))
        {
            Serial.println("Message sent successfully!");
        }
        else
        {
            Serial.println("Failed to send message!");
        }
    }
    if (!mqttClient.connected())
    {
        Serial.println("Failed to send message!");
    }
}

void callback(char *topic, byte *payload, unsigned int length) // MQTT message callback function (optional)
{
    // Handle incoming MQTT messages here
    Serial.print("Message received in topic: ");
    Serial.println(topic);
    Serial.print("Payload: ");
    for (unsigned int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}