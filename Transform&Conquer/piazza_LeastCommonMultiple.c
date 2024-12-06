#include <stdio.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm(long long a, long long b) {
    return (a / gcd(a, b)) * b; 
}

int main() {
    long long a = 569482193847;
    long long b = 781935476203;

    long long result = lcm(a, b);

    printf("LCM(%lld, %lld) = %lld\n", a, b, result);

    return 0;
}
