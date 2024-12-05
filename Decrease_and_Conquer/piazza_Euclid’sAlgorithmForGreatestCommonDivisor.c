#include <stdio.h>

int gcd(int m, int n) {
    int r; 
    printf("최대공약수를 찾는 과정:\n");
    while (n != 0) {
        r = m % n;
        printf("m = %d, n = %d, m %% n = %d\n", m, n, r);
        m = n;
        n = r; 
    }
    return m; 
}

int main() {
    int a, b;

    printf("두 수를 입력하세요 (공백으로 구분): ");
    scanf("%d %d", &a, &b);

    int result = gcd(a, b);

    printf("최대공약수: %d\n", result);

    return 0;
}