
#ifndef W_M_STATE_BASE_H
#define W_M_STATE_BASE_H
class WateringMachine;
class WateringMachineStateBase
{
public:
    WateringMachineStateBase();
    WateringMachineStateBase(WateringMachine *context);
    // Class destructor for WateringMachineStateBase (Declared as virtual)
     ~WateringMachineStateBase() {}
     //maybe do it pure virtual?
    virtual char* getName(); ;
    virtual bool handleWatering() ;
    virtual bool handleLighting() ;
    virtual bool handleIdle() ;
    virtual bool init() ;
    virtual bool tick() ;
    virtual bool setContext(WateringMachine *context) ;

protected:
  WateringMachine *context;
};
#endif