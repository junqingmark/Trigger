#ifndef _FILE_DESCRIPTOR_MONITOR_H_
#define _FILE_DESCRIPTOR_MONITOR_H_
#include "call-back.h"

class FileDescriptorMonitor
{
public:
    enum EventType
    {
        FD_NO_EVENT = 0x01,
        FD_READABLE = 0x02,
        FD_WRITABLE = 0x03,
        FD_ERROR = 0x04
    };

    FileDescriptorMonitor(int fileDescriptor, CallbackBase* callback, int eventBitMask);
    ~FileDescriptorMonitor();
    FileDescriptorMonitor(const FileDescriptorMonitor&)=delete;
    FileDescriptorMonitor& operator=(const FileDescriptorMonitor&)=delete;

private:
    struct Impl;
    Impl* mImpl;

};

#endif //_FILE_DESCRIPTOR_MONITOR_H_