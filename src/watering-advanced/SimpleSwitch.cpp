#include "SimpleSwitch.h"
#include "CustomLog.h"
//IMPLEMENTATION
bool SimpleSwitchInitMockFunc()
{
  return true;
}
SimpleSwitch::SimpleSwitch(bool onFunc(), bool offFunc(), bool initFunc()) : SwitchStateMachine()
{
  this->_onFunc = onFunc;
  this->_offFunc = offFunc;
  if (initFunc != nullptr)
    this->_initFunc = initFunc;
  else
    this->_initFunc = SimpleSwitchInitMockFunc;
}
bool SimpleSwitch::init()
{
  cLog("Initiating SimpleSwitch");
  return this->_initFunc();
}
bool SimpleSwitch::turnOff()
{
  SwitchStates stateTmp = this->state;
  this->nextState(SwitchCommand::COMMAND_OFF);
  return true;
}
bool SimpleSwitch::turnOn()
{

  this->_onFunc();
  return SwitchStates::SWITCH_ON == this->nextState(SwitchCommand::COMMAND_ON);
}