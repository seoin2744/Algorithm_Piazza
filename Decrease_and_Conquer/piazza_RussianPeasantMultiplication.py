import time

def mul(x, y):
    return x * y

def RPM(x, y):
    result = 0 
    n, m = x, y

    while n > 0:
        if n % 2 == 0: 
            n = n // 2
            m = m * 2
        else:
            result += m 
            n = (n - 1) // 2
            m = m * 2
    return result

x = 519534236238247351384500342837
y = 239925363457925217438408

start_time = time.perf_counter()
print("일반 수식 처리 결과:", mul(x, y))
total_time = time.perf_counter() - start_time
print(f"일반 수식 처리 시간 : {total_time:.8f} seconds")

start_time = time.perf_counter()
print("Russian peasant 방식 결과 :", RPM(x, y))
total_time = time.perf_counter() - start_time
print(f"Russian peasant 방식 시간: {total_time:.8f} seconds")
