#include <stdio.h>
#include <sys/time.h>
#include <unistd.h> // For usleep()

int main()
{
    struct timeval start, end;
    long seconds, microseconds;
    double elapsed;

    // نحصل على الوقت قبل العملية
    gettimeofday(&start, NULL);

    // نقوم بعملية تأخير لمدة 500 ميلي ثانية (0.5 ثانية)
    usleep(5000000); 

    // نحصل على الوقت بعد العملية
    gettimeofday(&end, NULL);

    // نحسب الفرق بين الوقتين
    seconds  = end.tv_sec  - start.tv_sec;
    microseconds = end.tv_usec - start.tv_usec;
    elapsed = seconds + microseconds * 1e-6;
    printf("time start : %ld\n", start.tv_sec);
    printf("time end : %ld\n", end.tv_sec);
    printf("time : %.6f s\n", elapsed);

    return 0;
}