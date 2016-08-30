#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define DUP10(a) a a a a a a a a a a

int main()
{
    struct timeval start;
    int r = gettimeofday(&start, NULL);
    if (r == -1)
    {
        perror("gettimeofday");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 10000000; j++) {
            __asm__ __volatile__ (
                DUP10(DUP10(DUP10("nop\n")))
            );
        }

        struct timeval now;
        r = gettimeofday(&now, NULL);
        if (r == -1)
        {
            perror("gettimeofday");
            return EXIT_FAILURE;
        }

        long long ms = (now.tv_sec - start.tv_sec) * 1000000LL + (now.tv_usec - start.tv_usec);
        ms /= (i+1);
        // ns per iteration: total time in ns / iteration = ms * 1000 / (1e7*1e3) = ms / 1e7
        // MIPS: 1000 / ns per iteration = 1000 / ms * 1e7 = 1e10 / ms
        printf("MIPS: %lld\n", 10000000000LL/ms);
    }
}
