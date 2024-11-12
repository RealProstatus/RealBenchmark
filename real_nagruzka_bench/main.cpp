#include<iostream>
#include<cmath>
#include<chrono>

using namespace std;

const double x_max = 10000.0;
const double d_x = 1.0e-2;
const double my_gamma = 1.0f;
const int arr_size = 1 + (x_max / d_x);
const double PI = 3.1415926535897932;
const double d_t = 1.0e-6;
const double t_max = 1;

int main() {
	double* current = new double[arr_size];
	for (int i = 0; i < arr_size; i++)
		current[i] = 1 - cos((2 * PI * i * d_x) / x_max);

	double* next = new double[arr_size];
	next[0] = next[arr_size - 1] = 0;

	double k = (my_gamma * d_t) / (d_x * d_x);

	auto start = chrono::high_resolution_clock::now();
	for (int t = 0; t < (int)(t_max / d_t); t++) {
		for (int i = 1; i < (arr_size - 1); i++) {
			next[i] = current[i] + k * (current[i - 1] - 2.0 * current[i] + current[i + 1]);
		}
		swap(next, current);
	}

	auto stop = chrono::high_resolution_clock::now();
	delete[] next;
	delete[] current;

	chrono::duration<float> result = stop - start;

	cout << "Time: " << result.count() << " seconds" << endl;
	cout << "Performance: " << (5.0 * (t_max / d_t) * (arr_size - 2)) / (result.count()*1.0e9) << "  GFLOPS";
	
}