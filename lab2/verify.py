import time

def read_matrix(filename):
    matrix = []
    with open(filename, 'r') as f:
        for line in f:
            row = tuple(map(float, line.strip().split()))
            matrix.append(row)
    return matrix

def multiply_sequential(A, B, size):
    C = [[0.0] * size for _ in range(size)]
    for i in range(size):
        for j in range(size):
            for k in range(size):
                C[i][j] += A[i][k] * B[k][j]
    return C

def verify():
    size = 200
    print("Чтение данных...")
    A = read_matrix("matrix_A.txt")
    B = read_matrix("matrix_B.txt")
    
    print("Последовательное умножение для проверки...")
    start = time.time()
    C_seq = multiply_sequential(A, B, size)
    seq_time = time.time() - start
    
    C_omp = read_matrix("result_matrix.txt")
    
    is_correct = True
    for i in range(size):
        for j in range(size):
            if abs(C_seq[i][j] - C_omp[i][j]) > 1e-5:
                is_correct = False
                break
    
    report = {
        "status": "УСПЕШНО" if is_correct else "ОШИБКА",
        "seq_time": f"{seq_time:.4f} сек",
        "matrix_size": f"{size}x{size}"
    }
    
    print(f"\n--- Отчет о проверке ---")
    print(f"Размер матрицы: {report['matrix_size']}")
    print(f"Последовательное время: {report['seq_time']}")
    print(f"Статус совпадения с OpenMP: {report['status']}")

if __name__ == "__main__":
    verify()
