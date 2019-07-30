#ifndef _TRIGGER_EVENT_H_
#define _TRIGGER_EVENT_H_
namespace
{
typedef void(*Function)(void);
}
#include "trigger-event-interface.h"
class TriggerEvent : public TriggerEventInterface
{
public:
    TriggerEvent(Function callback, TriggerEventInterface::Options options);
    ~TriggerEvent();

public:
    void Trigger();

private:
    void Triggered(FileDescriptorMonitor::EventType eventBitMask);

private:
    FileDescriptorMonitor* mFileDescriptorMonitor;
    Function mFunction;
    int mFileDescriptor;
    TriggerEventInterface::Options mOptions;

};
#endif