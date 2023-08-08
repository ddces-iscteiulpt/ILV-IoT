// Internal files
#include "setup.h"
#include "SECRETS\secret.h"
// Functions
#include "functions\network\wifi_api.h"
#include "functions\network\mqtt_api.h"
#include "functions\tf_sensor_api.h"
#include "functions\json_api.h"
#include "functions\encryption_api.h"
// Libraries
#include <ArduinoLowPower.h>

// Sensors Pins Relays
const int relay_pin_arr[] = RELAY_PIN_LINE;

// Constants de calculate de Volume
const float max_length = MAX_LENGTH;                                          // comprimento em cm
const float max_width = MAX_WIDTH;                                            // largura em cm
const float max_height = MAX_HEIGHT;                                          // altura em cm
const double max_volume = max_length * max_width * max_height;                // Volume total da caixa em vazio (cm3)
const double cell_area = (max_length / N_LINES) * (max_width / N_CELLS_LINE); // Area de cada celula (cm2)
const int n_sensors = N_SENSORS;                                              // Numero de sensores
const float time_msg = TIME_MSG;                                              // tempo entre mensagens em minutos


void setup() {
  Serial.begin(115200);                                                       // Initialize Serial port
  Wire.begin();
  for (int i = 0; i < sizeof(relay_pin_arr); i++) { pinMode(relay_pin_arr[i], OUTPUT); }

  //wifi_connection();

  //mqtt_connection();
  //mqttClient.beginMessage(topic);
  digitalWrite(relay_pin_arr[0], HIGH);
  delay(1000);
  create_TF_addresses();
  for (int i = 0; i < n_sensors; i++) {
    setup_TF_sensor(addr_array[i]);
    delay(1000);
  }
}

void loop() {
    Serial.println("Reconnecting to WiFi: ");
    bool wifi_rec = wifi_reconnection();
    //bool wifi_rec = true;
        if (wifi_rec = false)
    {
      Serial.println("Failed to reconnect to Wi-Fi!");
    }
    if (wifi_rec = true) {
      Serial.println("Reconnected to Wi-Fi!");
      //mqtt_connection();
      digitalWrite(relay_pin_arr[0], HIGH);
      delay(1000);

      for (int i = 0; i < n_sensors; i++)
      {
        Serial.println("...");
        Serial.print("Get Serial Number " + String(addr_array[i]) + ": ");
        /*
        if (tflI2C.Get_Prod_Code(tfCode, addr_array[i]))
        {
          for (uint8_t i = 0; i < 14; ++i)
          {
            Serial.print(char(tfCode[i]));
          }
          Serial.println();
        }
        else
        {
          tflI2C.printStatus();
        }
        */
        delay(200);
        volume_array[i] = get_measure_TF_sensor(addr_array[i], i);
        delay(1000);
      }
      digitalWrite(relay_pin_arr[0], LOW);
      float sum_height = 0; // some of all heights
      for (int i = 0; i < n_sensors; ++i)
      {
        sum_height += volume_array[i];
      }
      Serial.println("\n##########");
      double free_volume = (cell_area * sum_height);
      Serial.println("Volume livre = " + String(free_volume) + " cm3");
      Serial.println("Volume maximo = " + String(max_volume) + " cm3");
      double full_volume = (free_volume / max_volume) * 100;
      Serial.println("Volume ocupado = " + String(full_volume) + " %");
      Serial.println("##########");

      String encryptedVolume = encrypt(String(full_volume), xor_key);
      Serial.println("Encrypted: " + encryptedVolume);
      /*
      while (reconnection_mqtt())
      {
        reconnection_mqtt();
      }
      */
      mqttClient.loop(); // Maintain the MQTT connection
      String sensor_name = "Sensor_test_01";
      String msg_t = String(full_volume);
      //send_message_mqtt(create_json_message(sensor_name, String(free_volume), String(full_volume), encryptedVolume, volume_array, n_sensors));
      delay(1000);
      WiFi.end();
    }
    //LowPower.deepSleep(TIME_MSG * 60 * 1000);
    delay(TIME_MSG * 60 * 1000);
}
