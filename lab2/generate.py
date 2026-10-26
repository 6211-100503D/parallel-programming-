import random

SIZE = 200

def generate_matrix(filename, size):
    with open(filename, 'w') as f:
        for _ in range(size):
            row = [round(random.uniform(1.0, 5.0), 2) for _ in range(size)]
            f.write(" ".join(map(str, row)) + "\n")

if __name__ == "__main__":
    generate_matrix("matrix_A.txt", SIZE)
    generate_matrix("matrix_B.txt", SIZE)
    print(f"Матрицы {SIZE}x{SIZE} успешно созданы (matrix_A.txt, matrix_B.txt)")
