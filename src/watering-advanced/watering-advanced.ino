#include "Arduino.h"
#include "ArduinoJson.h"
#include "SimplePump.h"
#include "Light.h"
#include "MoistureSensor.h"
#include "MechanicalButton.h"
#include "CustomLog.h"
#include "WateringMachine.h"

#include "WateringMachineStateBase.h"
#include "LightingState.h"
#include "IdleState.h"
#include "WateringState.h"

#include "StateFactory.h"

//MechanicalButton *mb = new MechanicalButton(12);
// calling global variables in global scope is not permitted oO //cry
//https://community.blynk.cc/t/error-isr-not-in-iram/37426/16
//ICACHE_RAM_ATTR void mbInterruptHandler(void)
//{
// xc->handleInterrupt();
//}
#define WATERING_TEST
WateringMachine *wateringMachine;

void setup()
{
    // initialize the serial communication:
    Serial.begin(115200);
    cLog("Setting up the Watering Machine");
    StaticJsonDocument<500> doc;
    /*
      #define LIGHT_DURATION 3600000  //1h in ms
      #define LIGHT_INTERVAL 86400000 //24h in ms
#define WATERING_CYCLE_DURATION 10000
#define WATERING_CYCLES 250
#define WATERING_CYCLE_PAUSE_DURATION 5000
#define WATERING_MOISTURE_CRITICAL 45
      */
    char json[] =
        "{\"sensor\":\"gps\",\"LIGHTING_INTERVAL\":82800000,\"LIGHTING_DURATION\":3600000,\"WATERING_MAX_DURATION\":1000,\"MOISTURE_TRESHOLD\":34,\"data\":[48.756080,2.302038]}";
    cLog("Deserializing Config");
    cLog(json);
    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, json);

    // Test if parsing succeeds.
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return;
    }
    const char *sensor = doc["sensor"];
    long time = doc["time"];
    double latitude = doc["data"][0];
    double longitude = doc["data"][1];

    StateFactory sf; //tak sie tworzy obiekty bez parametrow?!?!?!?!
    SimplePump pump(4, 0);
    Light light(5);
    std::vector<MoistureSensor> sensors;
    sensors.push_back(MoistureSensor(6));
    sensors.push_back(MoistureSensor(7));
    //mb->setupInterruptHandler(12, mbInterruptHandler, CHANGE);

    wateringMachine = new WateringMachine(doc, sf, light, pump, sensors);
    wateringMachine->init();
    cLog("Setting up has finished");
};
void loop(){
    wateringMachine->tick();
};
