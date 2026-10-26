#include <iostream>
#include <vector>
#include <fstream>
#include <omp.h>

using namespace std;

vector<vector<double>> read_matrix(const string& filename, int size) {
    vector<vector<double>> matrix(size, vector<double>(size));
    ifstream file(filename);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            file >> matrix[i][j];
        }
    }
    file.close();
    return matrix;
}

void multiply_omp(const vector<vector<double>>& A, 
                  const vector<vector<double>>& B, 
                  vector<vector<double>>& C, 
                  int size, int num_threads) {
    
    omp_set_num_threads(num_threads);
    
    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            double sum = 0.0;
            for (int k = 0; k < size; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

int main() {
    int size = 200;
    int max_threads = 8;

    vector<vector<double>> A = read_matrix("matrix_A.txt", size);
    vector<vector<double>> B = read_matrix("matrix_B.txt", size);
    vector<vector<double>> C(size, vector<double>(size, 0.0));

    cout << "=== Parallel Matrix Multiplication (OpenMP) ===" << endl;
    cout << "Matrix size: " << size << "x" << size << endl;
    cout << "Threads | Time (seconds)" << endl;
    cout << "--------------------------------" << endl;

    for (int threads = 1; threads <= max_threads; threads *= 2) {
        double start = omp_get_wtime();
        multiply_omp(A, B, C, size, threads);
        double end = omp_get_wtime();
        double time_elapsed = end - start;
        cout << "   " << threads << "    | " << time_elapsed << " s" << endl;
    }

    ofstream out_file("result_matrix.txt");
    if (out_file.is_open()) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                out_file << C[i][j] << (j == size - 1 ? "" : " ");
            }
            out_file << "\n";
        }
        out_file.close();
        cout << "Result saved to result_matrix.txt" << endl;
    }

    return 0;
}
