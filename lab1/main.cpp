#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
using namespace std;

void displayMatrix(const vector<vector<double>>& matrix, int dim)
{
    for (int row = 0; row < dim; row++)
    {
        for (int col = 0; col < dim; col++)
        {
            cout << matrix[row][col] << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
}

vector<vector<double>> multiplyMatrices(const vector<vector<double>>& first,
                                         const vector<vector<double>>& second,
                                         int dim, long long& opCount)
{
    vector<vector<double>> result(dim, vector<double>(dim, 0.0));

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < dim; k++)
            {
                sum += first[i][k] * second[k][j];
                opCount++;
            }
            result[i][j] = sum;
        }
    }

    return result;
}

int main()
{
    ifstream fin("input.txt");

    if (!fin.is_open())
    {
        cerr << "Error: cannot open input.txt" << endl;
        return 1;
    }

    int dim;
    fin >> dim;

    vector<vector<double>> mat1(dim, vector<double>(dim, 0.0));
    vector<vector<double>> mat2(dim, vector<double>(dim, 0.0));

    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            fin >> mat1[i][j];

    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            fin >> mat2[i][j];

    fin.close();

    cout << "Matrix A:" << endl;
    displayMatrix(mat1, dim);

    cout << "Matrix B:" << endl;
    displayMatrix(mat2, dim);

    long long opCount = 0;
    auto t1 = chrono::steady_clock::now();
    vector<vector<double>> result = multiplyMatrices(mat1, mat2, dim, opCount);
    auto t2 = chrono::steady_clock::now();

    auto elapsed = chrono::duration_cast<chrono::microseconds>(t2 - t1);

    cout << "Operations: " << opCount << endl;
    cout << "Time: " << elapsed.count() << " us" << endl << endl;

    cout << "Result matrix C = A * B:" << endl;
    displayMatrix(result, dim);

    ofstream fout("output.txt");
    fout << "Dimension: " << dim << "\n";
    fout << "Operations: " << opCount << "\n";
    fout << "Time: " << elapsed.count() << " us\n\n";

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
            fout << result[i][j] << "\t";
        fout << "\n";
    }

    fout.close();

    return 0;
}
