#include <stdio.h>
#include <stdlib.h>

int josephus(int n, int k) {
    int index = 0;
    int *people = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        people[i] = i + 1;
    }
    int remaining = n; 

    while (remaining > 1) {
        index = (index + k - 1) % remaining; 

        for (int i = index; i < remaining - 1; i++) {
            people[i] = people[i + 1];
        }

        remaining--; 
    }

    int last_person = people[0]; 
    free(people); 
    return last_person;
}

int main() {
    int n, k;

    printf("총 인원: ");
    scanf("%d", &n);
    printf("제거할 간격: ");
    scanf("%d", &k);

    int last_person = josephus(n, k);

    printf("마지막으로 남는 사람 위치: %d\n", last_person);

    return 0;
}
