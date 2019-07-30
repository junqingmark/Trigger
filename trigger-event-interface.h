#ifndef _TRIGGER_EVENT_INTERFACE_H_
#define _TRIGGER_EVENT_INTERFACE_H_
class TriggerEventInterface
{
public:
    enum Options
    {
        KEEP_ALIVE_AFTER_TRIGGER,
        DELETE_AFTER_TRIGGER

    };

    virtual void Trigger() = 0;

protected:
    TriggerEventInterface(){};

public:
    virtual ~TriggerEventInterface();
    TriggerEventInterface(const TriggerEventInterface&) = delete;
    TriggerEventInterface& operator=(const TriggerEventInterface&) = delete;
};

#endif //_TRIGGER_EVENT_INTERFACE_H_