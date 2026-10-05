import numpy as np

def read_matrix(filename, n):
    matrix = []
    with open(filename, 'r') as f:
        for _ in range(n):
            row = list(map(float, f.readline().split()))
            matrix.append(row)
    return np.array(matrix)

def main():
    n = 3  # размер матрицы
    
    A = read_matrix('Matrix(A).txt', n)
    B = read_matrix('Matrix(B).txt', n)
    
    C_numpy = np.dot(A, B)
    
    print("Матрица A:")
    print(A)
    print("\nМатрица B:")
    print(B)
    print("\nРезультат A * B (NumPy):")
    print(C_numpy)

if __name__ == '__main__':
    main()
