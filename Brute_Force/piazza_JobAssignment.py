import itertools
import time

# Job과 Person의 수
N = 10

# 주어진 비용 배열
cost = [
    [13,  6,  7, 12, 14, 15, 10, 11, 15,  4],
    [ 8, 14, 11,  9,  6, 14,  7,  9, 16, 12],
    [10,  8, 10, 10,  8, 15, 11,  5,  7,  9],
    [13, 13, 16,  9, 13, 16, 15,  9, 14, 16],
    [11,  4,  9, 14, 12, 11,  5, 16,  8, 14],
    [ 7, 10, 12, 13,  4, 11, 16, 12, 15,  9],
    [ 6, 11, 10, 11, 13, 15,  7, 16, 11, 12],
    [ 7, 15,  5, 10,  4, 16, 12,  4, 10, 16],
    [ 5, 14, 10, 15,  8,  8,  8, 14, 14,  4],
    [ 8, 11,  4, 16,  8, 12,  4, 14,  9,  6]
]

# 최소 비용을 찾는 함수 (Brute Force 방식)
def find_min_cost_brute_force(cost):
    # 작업자 수 (Person 수 = Job 수)
    N = len(cost)
    
    # 가능한 모든 작업 할당 조합을 생성 (0, 1, ..., N-1 작업에 대한 모든 순열)
    jobs = range(N)
    all_permutations = itertools.permutations(jobs)
    
    # 최소 비용을 저장할 변수 (초기값은 무한대로 설정)
    min_cost = float('inf')
    best_permutation = None
    
    # 모든 할당 조합에 대해 비용 계산
    for perm in all_permutations:
        current_cost = 0
        for person in range(N):
            current_cost += cost[person][perm[person]]  # 작업 할당에 대한 비용 계산
        
        # 최소 비용 갱신
        if current_cost < min_cost:
            min_cost = current_cost
            best_permutation = perm

    return min_cost, best_permutation

# 실행 시간 측정을 위한 코드
if __name__ == "__main__":
    # 시작 시간 기록
    start_time = time.time()
    
    # Brute Force 방식으로 최소 비용 찾기
    min_cost, best_permutation = find_min_cost_brute_force(cost)
    
    # 종료 시간 기록
    end_time = time.time()
    
    # 수행 시간 계산
    elapsed_time = end_time - start_time
    
    # 결과 출력
    print(f"최소 비용: {min_cost}")
    print(f"최적 작업 할당: {best_permutation}")
    print(f"실행 시간: {elapsed_time:.6f} 초")
