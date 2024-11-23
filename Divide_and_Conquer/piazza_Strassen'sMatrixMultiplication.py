import numpy as np

def strassen(A, B):
    if A.size == 1:
        return A * B
    
    n = A.shape[0] // 2
    A00, A01, A10, A11 = A[:n, :n], A[:n, n:], A[n:, :n], A[n:, n:]
    B00, B01, B10, B11 = B[:n, :n], B[:n, n:], B[n:, :n], B[n:, n:]

    M1 = strassen(A00 + A11, B00 + B11)
    M2 = strassen(A10 + A11, B00)
    M3 = strassen(A00, B01 - B11)
    M4 = strassen(A11, B10 - B00)
    M5 = strassen(A00 + A01, B11)
    M6 = strassen(A10 - A00, B00 + B01)
    M7 = strassen(A01 - A11, B10 + B11)

    C00 = M1 + M4 - M5 + M7
    C01 = M3 + M5
    C10 = M2 + M4
    C11 = M1 + M3 - M2 + M6

    C = np.vstack([np.hstack([C00, C01]), np.hstack([C10, C11])])
    return C

A = np.array([[10, 8], [12, 11]])
B = np.array([[4, 9], [8, 13]])
C = strassen(A, B)
print(C)
