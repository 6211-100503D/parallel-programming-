import random

def generate_matrix(n, filename):
    with open(filename, 'w') as f:
        f.write(f"{n}\n")
        for i in range(n):
            row = [random.randint(1, 10) for _ in range(n)]
            f.write(' '.join(map(str, row)) + '\n')

if __name__ == '__main__':
    n = 3
    generate_matrix(n, 'Matrix(A).txt')
    generate_matrix(n, 'Matrix(B).txt')
    print(f"Сгенерированы матрицы {n}x{n}")
