#include <iostream>
#include <immintrin.h>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>

constexpr size_t N = 8; 

int main() {
    alignas(32) float a[N] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    alignas(32) float b[N] = {8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
    alignas(32) float scalar_result[N];
    alignas(32) float vector_result[N];

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i) {
        scalar_result[i] = a[i] / b[i];
    }
    auto scalar_time = std::chrono::high_resolution_clock::now() - start;

    __m256 vec_a = _mm256_load_ps(a);
    __m256 vec_b = _mm256_load_ps(b);
    
    start = std::chrono::high_resolution_clock::now();
    __m256 vec_result = _mm256_div_ps(vec_a, vec_b);  // Single instruction for 8 divisions
    auto vector_time = std::chrono::high_resolution_clock::now() - start;
    
    _mm256_store_ps(vector_result, vec_result);

    bool correct = true;
    for (size_t i = 0; i < N; ++i) {
        if (std::fabs(scalar_result[i] - vector_result[i]) > 1e-6f) {
            correct = false;
            break;
        }
    }

    auto scalar_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(scalar_time).count();
    auto vector_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(vector_time).count();
    double speedup = (vector_ns > 0) ? static_cast<double>(scalar_ns) / vector_ns : 0.0;

    std::cout << "AVX256 Division Demo (8 floats)\n";
    std::cout << "Results match: " << (correct ? "YES" : "NO") << "\n";
    std::cout << "Scalar time: " << scalar_ns << " ns\n";
    std::cout << "Vector time: " << vector_ns << " ns\n";
    std::cout << "Speedup: " << std::fixed << std::setprecision(2) << speedup << "x\n\n";

    constexpr size_t LARGE_N = 1024;
    alignas(32) std::vector<float> large_a(LARGE_N);
    alignas(32) std::vector<float> large_b(LARGE_N);
    alignas(32) std::vector<float> large_scalar(LARGE_N);
    alignas(32) std::vector<float> large_vector(LARGE_N);
    
    for (size_t i = 0; i < LARGE_N; ++i) {
        large_a[i] = static_cast<float>(i + 1);
        large_b[i] = static_cast<float>(LARGE_N - i);
    }
    
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < LARGE_N; ++i) {
        large_scalar[i] = large_a[i] / large_b[i];
    }
    scalar_time = std::chrono::high_resolution_clock::now() - start;
    
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < LARGE_N; i += 8) {
        __m256 va = _mm256_load_ps(&large_a[i]);
        __m256 vb = _mm256_load_ps(&large_b[i]);
        __m256 vr = _mm256_div_ps(va, vb);
        _mm256_store_ps(&large_vector[i], vr);
    }
    vector_time = std::chrono::high_resolution_clock::now() - start;
    
    correct = true;
    for (size_t i = 0; i < LARGE_N; ++i) {
        if (std::fabs(large_scalar[i] - large_vector[i]) > 1e-6f) {
            correct = false;
            break;
        }
    }
    
    scalar_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(scalar_time).count();
    vector_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(vector_time).count();
    speedup = (vector_ns > 0) ? static_cast<double>(scalar_ns) / vector_ns : 0.0;
    
    std::cout << "Large Array (1024 elements)\n";
    std::cout << "Results match: " << (correct ? "YES" : "NO") << "\n";
    std::cout << "Scalar time: " << scalar_ns << " ns\n";
    std::cout << "Vector time: " << vector_ns << " ns\n";
    std::cout << "Speedup: " << std::fixed << std::setprecision(2) << speedup << "x\n";

    return 0;
}