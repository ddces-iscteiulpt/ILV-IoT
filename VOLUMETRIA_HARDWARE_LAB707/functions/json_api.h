#include <ArduinoJson.h>

String create_json_message(String sensor, String volume, String percentage, String encrypted_msg, const float volume_array[], int array_size)
{
    // Create a JSON object using the ArduinoJson library
    StaticJsonDocument<500> jsonDocument;

    // Add data to the JSON object
    jsonDocument["sensor"] = sensor;
    jsonDocument["volume"] = volume;
    jsonDocument["percentage"] = percentage;
    jsonDocument["encrypted_msg"] = encrypted_msg;

    // Add array to the JSON object
    JsonArray array = jsonDocument.createNestedArray("volume_array");
    for (int i = 0; i < array_size; i++) {
        array.add(volume_array[i]);
    }
   
    // Serialize the JSON object to a string
    String jsonString;
    serializeJson(jsonDocument, jsonString);

    return jsonString;
}
