#include "file-descriptor-monitor.h"

struct FileDescriptorMonitor::Impl
{
Impl(int fileDescriptor, CallbackFunction* callback, int eventsToMonitor);


int mFileDescriptor;
CallbackFunction mCallback;
int mEventsToMonitor;


};