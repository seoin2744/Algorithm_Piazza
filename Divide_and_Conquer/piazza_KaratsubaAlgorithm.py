import time

def karatsuba(x,y) :
    if len(str(x))==1 or len(str(y))==1: # 입력 값이 한 자리 숫자
        return x*y
    
    m = min(len(str(x)),len(str(y))) // 2 
    a=int(str(x)[:-m])
    b=int(str(x)[-m:])
    c=int(str(y)[:-m]) # 뒤에서 m번째 문자 이전까지. ex) s = "abcdefghij" [:-4] 뒤에서 4번째 문자 이전까지. "abcdef"
    d=int(str(y)[-m:]) # s = "abcdefghij" [3:]: 앞에서 3번째 문자('d')부터 끝까지. 결과: "defghij" [-3:]: 뒤에서 3번째 문자('h')부터 끝까지. 결과: "hij"

    z2=karatsuba(a,c)
    z0=karatsuba(b,d)
    z1=karatsuba(a+b,c+d) -z2 -z0    
    
    return z2*10**(2*m) + z1*10**m + z0
    
if __name__ == "__main__":
    
    start_time = time.time()
    
    print("결과 :",karatsuba(2462,8014))
    end_time = time.time()
    
    elapsed_time = end_time - start_time
    
    print(f"실행 시간: {elapsed_time:.6f} 초")

