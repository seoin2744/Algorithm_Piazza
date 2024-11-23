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

  //버블 정렬
  for (int i = 0; i < CNT - 1; i++) {
    for (int j = 0; j < CNT - 1 - i; j++) { //i는 정렬된 개수 (버블정렬은 맨 뒤부터 큰 수대로 정렬됨)
        if (data[j] > data[j + 1]) {
            temp = data[j];
            data[j] = data[j + 1];
            data[j+1] = temp;
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

// start는 clock() 함수가 호출된 시점에서 반환된 클럭 틱 값.
// end는 버블 정렬이 완료된 후 호출된 시점에서의 클럭 틱 값.
// clock_t: 시스템 클럭 틱의 개수를 저장하는 자료형.

// clock() 함수로 얻은 결과는 클럭 틱의 개수이므로, 이를 초 단위로 변환하려면 클럭 틱을 초로 변환할 필요가 있습니다. 
// 이때 사용하는 상수가 CLOCKS_PER_SEC입니다. 이는 1초에 해당하는 클럭 틱의 수를 나타냅니다.