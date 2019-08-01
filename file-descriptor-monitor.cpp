#include "file-descriptor-monitor.h"
#include <pthread.h>
#include <sys/epoll.h>

struct FileDescriptorMonitor::Impl
{
    Impl(int fileDescriptor, CallbackBase* callback, int eventsToMonitor)
    : mFileDescriptor(fileDescriptor),
    mCallback(callback),
    mEventsToMonitor(eventsToMonitor)
    {

    }

    ~Impl()
    {
        delete mCallback;
    }

    int mFileDescriptor;
    CallbackBase* mCallback;
    int mEventsToMonitor;
    pthread_t mThreadId;
    static int ep_fd;

    static void* EventDispatch(void* data)
    {
        Impl* impl = reinterpret_cast<Impl*>(data);
        int type = FileDescriptorMonitor::FD_NO_EVENT;

        struct epoll_event events;
        while(true)
        {
            int ret = epoll_wait(ep_fd, &events, 1, 5000);
            if(ret > 0)
            {
                if(events.events & EPOLLIN)
                {
                    type = FileDescriptorMonitor::FD_READABLE;
                }
                if(events.events & EPOLLOUT)
                {
                    type = FileDescriptorMonitor::FD_WRITABLE;
                }

                if(type != FileDescriptorMonitor::FD_NO_EVENT)
                {
                    CallbackBase::Execute(*(impl->mCallback), static_cast< FileDescriptorMonitor::EventType >(type ));
                }
            }

        }

    }

};

int FileDescriptorMonitor::Impl::ep_fd = -1;

FileDescriptorMonitor::FileDescriptorMonitor(int fileDescriptor, CallbackBase* callback, int eventBitmask)
{
    mImpl = new Impl(fileDescriptor, callback, eventBitmask);
    if(fileDescriptor < 1)
    {
        printf("Invalid File descriptor");
        return;
    }

    int events = 0;
    if( eventBitmask & FD_READABLE)
    {
        events = EPOLLIN;
    }
    if( eventBitmask & FD_WRITABLE)
    {
        events |= EPOLLOUT;
    }
    mImpl->mEventsToMonitor = events;
    
    struct epoll_event ev;
    Impl::ep_fd = epoll_create1(0);
    ev.data.fd = Impl::ep_fd;
    ev.events = 0;
    if (Impl::ep_fd < 0)
    {
        perror("epoll_create fail: ");
        return ;
    }

    if(mImpl->mEventsToMonitor & EPOLLIN)
    {
        ev.events |= EPOLLIN;
    }
    if(mImpl->mEventsToMonitor & EPOLLOUT)
    {
        ev.events |= EPOLLOUT;
    }

    int ret = epoll_ctl(Impl::ep_fd, EPOLL_CTL_ADD, mImpl->mFileDescriptor, &ev);
    if (ret < 0)
    {
        perror("epoll ctl failed:");
        return;
    }

    pthread_create(&(mImpl->mThreadId), NULL, Impl::EventDispatch, reinterpret_cast<void*>(mImpl));
}

FileDescriptorMonitor::~FileDescriptorMonitor()
{

    delete mImpl;
    mImpl = nullptr;
}