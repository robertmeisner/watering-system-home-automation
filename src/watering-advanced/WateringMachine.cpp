#include "WateringMachine.h"
#include "WateringMachineConfig.h"
#include "WateringMachineStateBase.h"
#include "CustomLog.h"
#include "Light.h"
#include "MoistureSensor.h"
#include "SimplePump.h"
#include "IdleState.h"
#include "StateFactory.h"

WateringMachine::WateringMachine(WateringMachineConfig &doc, StateFactory &sf, Light &l, SimplePump &sp, std::vector<MoistureSensor> &ms) : config(doc), stateFactory(sf), light(l), pump(sp), moistureSensors(ms)
{
}
void WateringMachine::turnLight()
{
    this->state->handleLighting();
}
void WateringMachine::turnIdle()
{
    this->state->handleIdle();
}
void WateringMachine::turnWatering()
{
    this->state->handleWatering();
}
WateringMachine *WateringMachine::setState(StateType type)
{
    this->state = this->stateFactory.getState(type, this);
    this->state->init();
    return this;
}

float WateringMachine::getMoistureAvg()
{
    if (this->moistureSensors.size() == 0)
    {
        cLog("No Moisture Sensors detected.", DebugLevel::FATAL);
        return 100;
    }

    float avg = 0;
    for (std::vector<MoistureSensor>::iterator it = this->moistureSensors.begin(); it != this->moistureSensors.end(); ++it)
    {
        avg += it->readAvg();
    }

    cLog(String("Average for all Moisture sensors reads: ") + (avg / this->moistureSensors.size()));
    return avg / this->moistureSensors.size();
}
bool WateringMachine::init()
{
    // inititate the components
    this->light.init();
    for (std::vector<MoistureSensor>::iterator it = this->moistureSensors.begin(); it != this->moistureSensors.end(); ++it)
    {
        it->init();
    }
    this->pump.init();
    //set initital state
    this->setState(StateType::IDLE_STATE); //init juz tutaj ma miejsce
}
void WateringMachine::tick()
{
    this->state->tick();
}
