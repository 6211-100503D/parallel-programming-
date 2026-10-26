#include <iostream>
#include <vector>
#include <fstream>
#include <omp.h>

using namespace std;

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
    int size = 400;
    int max_threads = 8; 

    vector<vector<double>> A(size, vector<double>(size, 1.5));
    vector<vector<double>> B(size, vector<double>(size, 2.0));
    vector<vector<double>> C(size, vector<double>(size, 0.0));

    cout << "=== Parallel Matrix Multiplication (OpenMP) ===\n";
    cout << "Matrix size: " << size << "x" << size << "\n";
    cout << "Threads | Time (seconds)\n";
    cout << "--------------------------------\n";

    for (int threads = 1; threads <= max_threads; threads *= 2) {
        auto start = omp_get_wtime(); 
        
        multiply_omp(A, B, C, size, threads);
        
        auto end = omp_get_wtime();
        double time_elapsed = end - start;
        
        cout << "   " << threads << "    | " << time_elapsed << " s\n";
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
        cout << "\nResult saved to result_matrix.txt\n";
    }

    return 0;
}
