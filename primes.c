#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

#define UPTO 10000000

long int count,      /* number of primes */
lastprime;  /* the last prime found */


void serial_primes(long int n) {
    long int i, num, divisor, quotient, remainder;

    if (n < 2) return;
    count = 1;                         /* 2 is the first prime */
    lastprime = 2;

    for (i = 0; i < (n-1)/2; ++i) {    /* For every odd number */
        num = 2*i + 3;

        divisor = 1;
        do
        {
            divisor += 2;                  /* Divide by the next odd */
            quotient  = num / divisor;
            remainder = num % divisor;
        } while (remainder && divisor <= quotient);  /* Don't go past sqrt */

        if (remainder || divisor == num) /* num is prime */
        {
            count++;
            lastprime = num;
        }
    }
}


void openmp_primes(long int n) {
    long int i, num, divisor, quotient, remainder;

    if (n < 2) return;
    count = 1;                         /* 2 is the first prime */
    lastprime = 2;

    #pragma omp parallel for private(num, divisor, quotient , remainder) reduction(+ : count) reduction(max : lastprime) schedule(runtime)
    for (i = 0; i < (n-1)/2; ++i) {    /* For every odd number */
        num = 2 * i + 3;

        divisor = 1;
        do {
            divisor += 2;                  /* Divide by the next odd */
            quotient = num / divisor;
            remainder = num % divisor;
        } while (remainder && divisor <= quotient);  /* Don't go past sqrt */

        if (remainder || divisor == num) /* num is prime */
        {
            count++;
            lastprime = num;
        }
    }
}


int main()
{
    struct timeval tv1, tv2;
    double time;
    omp_set_dynamic(0);


    printf("Serial and parallel prime number calculations:\n\n");

    //Serial
    gettimeofday(&tv1, NULL);
    serial_primes(UPTO);        /* time it */
    gettimeofday(&tv2, NULL);
    time = (tv2.tv_sec - tv1.tv_sec) + (tv2.tv_usec - tv1.tv_usec) * 1.0E-6;
    printf("[serial] count = %ld, last = %ld (time = %lf)\n", count, lastprime, time);


    //Parallel
    gettimeofday(&tv1, NULL);
    openmp_primes(UPTO);
    gettimeofday(&tv2, NULL);

    time = (tv2.tv_sec - tv1.tv_sec) + (tv2.tv_usec - tv1.tv_usec) * 1.0E-6;
    printf("[openmp] count = %ld, last = %ld (time = %lf)\n", count, lastprime, time);

    return 0;
}