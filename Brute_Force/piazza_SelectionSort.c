#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CNT 1000

int main()
{
  int temp = 0;
	int random = 0; 
  int data[CNT];

	for (int i = 0; i < 1000; i++) { 
		random = rand()%1000; 
		data[i]=random;
	}
  printf("\n");

  clock_t start = clock();

  //Selection Sort
  for (int i = 0; i < CNT ; i++) {
    for (int j = i+1; j < CNT ; j++) {
        if (data[i] > data[j]) {
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
  }

  clock_t end = clock();

  for (int i = 0; i < CNT; i++) {
      printf("%d, ", data[i]);
  }

  printf("\n\n소요 시간: %lf초\n", (double)(end - start) / CLOCKS_PER_SEC);

  return 0;
}