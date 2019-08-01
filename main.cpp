#include "file-descriptor-monitor.h"
#include "call-back.h"
#include <sys/eventfd.h>
#include <cstdio>
#include <unistd.h>
#include <sys/time.h>

void printLog(void)
{
    printf("=====printLog\n");    
}
int main(int argc, char* argv[])
{
    uint64_t count = 0;
    int ret = 0;
    int i = 0;

    printf("EFD_NONBLOCK:%d\n",EFD_NONBLOCK);
    int efd = eventfd(0, EFD_NONBLOCK);
    if (efd < 0)
    {
        perror("eventfd failed.");
        return -1;
    }

    FileDescriptorMonitor* monitor = new FileDescriptorMonitor(efd, MakeCallback(printLog), FileDescriptorMonitor::FD_READABLE);
    // for (i = 0; i < 5; i++)
    // {
        count = 4;
        ret = write(efd, &count, sizeof(count));
        if (ret < 0)
        {
            perror("write event fd fail:");
            return -1;

        }
        else
        {
            struct timeval tv;

            gettimeofday(&tv, NULL);
            printf("success write to efd, write %d bytes(%llu) at %lds %ldus\n",
                   ret, count, tv.tv_sec, tv.tv_usec);
        }

        sleep(1);
    // }

    return 0;
}