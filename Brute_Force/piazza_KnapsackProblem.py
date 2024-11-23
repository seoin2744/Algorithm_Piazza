import time  # 시간을 측정하기 위한 time 모듈 추가

class Item:
    def __init__(self, weight, value):
        self.weight = weight  # 물건의 무게
        self.value = value    # 물건의 가치

class Knapsack:
    def __init__(self, w_max, items):
        self.w_max = w_max    # 배낭의 최대 용량
        self.items = items    # 물건 리스트
        self.best = []        # 최적의 조합을 저장할 리스트

    def result(self, frac):
        print(f'최대 가치: {sum([item.value for item in self.best])}')
        print('선택된 물건:')
        for item in self.best:
            print(f'무게: {item.weight}, 가치: {item.value}')

class BFKnapsack(Knapsack):    
    def zero_one_solve(self):
        n = len(self.items)  # 물건의 개수
        m = 0                # 최대 가치 (초기값 0)
        self.best = []       # 최대 가치 조합

        # 시간 측정을 시작
        start_time = time.time()

        # 모든 가능한 부분집합을 생성 (2^n 개의 부분집합)
        for i in range(2 ** n):
            sub_items = []      # 현재 부분집합에 들어가는 물건들
            sub_total = [0, 0]  # 무게합, 가치합 (초기값 0)

            for j in range(n):
                # i >> j는 i의 j번째 비트를 확인함, 그 값이 1이면 물건을 선택
                if (i >> j) & 1:
                    item = self.items[j]
                    sub_items.append(item)
                    sub_total[0] += item.weight  # 무게 더함
                    sub_total[1] += item.value   # 가치 더함

            # 배낭의 용량을 초과했는지 확인
            exceeded = sub_total[0] > self.w_max
            # 새로운 조합의 가치가 현재 최대 가치보다 높은지 확인
            better = sub_total[1] > m

            # 용량을 초과하지 않고 가치가 더 높으면 최적 조합으로 갱신
            if not exceeded and better:
                m = sub_total[1]  # 최대 가치 갱신
                self.best = sub_items  # 최적 조합 갱신

        # 시간 측정을 종료
        end_time = time.time()
        elapsed_time = end_time - start_time

        # 결과 출력
        self.result(frac=False)

        # 수행 시간 출력
        print(f"실행 시간: {elapsed_time:.6f} 초")


# 메인 함수
if __name__ == "__main__":
# .py 파일에는 __name__이라는 숨겨진 변수가 있다. 이 변수는 모듈의 이름을 가지고 있는 변수로, 현재 .py 파일의 이름을 가지고 있는 변수
# name 변수를 통해 현재 스크립트 파일이 시작점인지 모듈인지 판단한다.

    w_max = int(input("배낭의 최대 용량을 입력하세요: "))  # 배낭의 최대 용량 입력
    n = int(input("물건의 개수를 입력하세요: "))            # 물건의 개수 입력

    items = []
    for i in range(n):
        weight = int(input(f"물건 {i + 1}의 무게를 입력하세요: "))  # 물건의 무게 입력
        value = int(input(f"물건 {i + 1}의 가치를 입력하세요: "))  # 물건의 가치 입력
        items.append(Item(weight, value))  # 입력받은 물건을 리스트에 추가

    # Brute Force 방식의 배낭 문제 인스턴스 생성 
    # 인스턴스란 "어떤 클래스의 실체(객체)"를 의미
    knapsack = BFKnapsack(w_max, items)
    # 문제 해결
    knapsack.zero_one_solve()
