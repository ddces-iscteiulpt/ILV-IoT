#include <Wire.h>
#include <TFLI2C.h> // TFLuna-I2C Library v.0.2.0
TFLI2C tflI2C;
#include "..\setup.h"

// Configuração de Sensores LUNA
int16_t tfAddr = TFL_DEF_ADR; // Use this default I2C address
uint16_t tfFrame = 200;
uint8_t tfCode[14]; // device serial number

// Configuração de Sensores TF-LUNA
int16_t addr_array[N_SENSORS] = {0x10, 0x18, 0x19, 0x20, 0x24, 0x33, 0x36, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x21, 0x22, 0x23, 0x30};
int16_t tfDist_array[N_SENSORS] = {0};
int16_t tfFlux_array[N_SENSORS] = {0};
int16_t tfTemp_array[N_SENSORS] = {0};
float volume_array[N_SENSORS] = {0};

void setup_TF_sensor(uint16_t adr)
{    
    // Set I2C Address (assuming adr is the correct I2C address)
    if (tflI2C.Set_I2C_Addr(adr, adr))
    {
        Serial.println("TF-Luna sensor at address " + String(adr) + " is ready!");
        // Set Frame Rate
        Serial.print("Set Frame Rate to: ");
        if (tflI2C.Set_Frame_Rate(tfFrame, adr))
        {
            Serial.println(tfFrame);
        }
        else
        {
            Serial.println("Failed to set Frame Rate!");
            // You can take appropriate action here, such as retrying or reporting the error
            return;
        }
        delay(1000);

        // Save Settings
        Serial.print("Save Settings to: ");
        if (tflI2C.Save_Settings(adr))
        {
            Serial.println(adr);
        }
        else
        {
            Serial.println("Failed to save settings!");
            // You can take appropriate action here, such as retrying or reporting the error
            return;
        }
        delay(1000);
    }
    else
    {
        Serial.println("Sensor not found at address " + String(adr));
        // You can take appropriate action here, such as retrying or reporting the error
        return;
    }
}


int16_t get_measure_TF_sensor(uint16_t adr, int i)
{
    if (tflI2C.getData(tfDist_array[i], tfFlux_array[i], tfTemp_array[i], adr))
    {
        tfTemp_array[i] = tfTemp_array[i] / 100;
        Serial.println("LUNA_" + String(i) + " - " + String(tfDist_array[i]) + " cm" + " - " + String(tfTemp_array[i]) + " ºC" + " - " + "Range: " + String(tfFlux_array[i]));
    }
    delay(300);

    return tfDist_array[i] + 1.5;
}
/*
int16_t get_measure_TF_sensor(uint16_t adr, int i)
{
    // Attempt to get sensor data from TFLuna
    if (tflI2C.getData(tfDist_array[i], tfFlux_array[i], tfTemp_array[i], adr))
    {
        // Successful reading, process the data

        // Check if the distance value is within acceptable range
        if (tfDist_array[i] >= 0 && tfDist_array[i] <= 1000)
        {
            // Convert temperature from 1/100 degrees Celsius to degrees Celsius
            tfTemp_array[i] = tfTemp_array[i] / 100;
            Serial.println("LUNA_" + String(i) + " - " + String(tfDist_array[i]) + " cm" + " - " + String(tfTemp_array[i]) + " ºC" + " - " + "Range: " + String(tfFlux_array[i]));
            delay(1000);
            // Return the distance value + 1.5 cm to account for the empty height
            return tfDist_array[i] + 1.5;
        }
        else
        {
            // Distance value is not valid, handle the error here
            Serial.println("LUNA_" + String(i) + " - Invalid distance value: " + String(tfDist_array[i]));
            // You can return a special value or raise an error flag to indicate the problem
            return 0; // Or any other suitable value indicating an error
        }
    }
    else
    {
        // Failed to read sensor data, handle the error here
        Serial.println("LUNA_" + String(i) + " - Sensor not found or not responding");
        // You can return a special value or raise an error flag to indicate the problem
        return 0; // Or any other suitable value indicating an error
    }
}
*/

/*
for (int i = 0; i < n_sensors; i++)
{
    Serial.println("...");
    Serial.print("Get Serial Number " + String(addr_array[i]) + ": ");
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
    delay(200);

    volume_array[i] = get_measure_TF_sensor(addr_array[i], i);
}
*/