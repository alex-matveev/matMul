#include <cstddef>

void simple_multiply(float *mat1,
              float *mat2, std::ptrdiff_t N, std::ptrdiff_t M, std::ptrdiff_t O,
              float *res) {
    for (std::ptrdiff_t i = 0; i < N; i++) {
        for (std::ptrdiff_t j = 0; j < M; j++) {
            for (std::ptrdiff_t k = 0; k < O; k++)
                res[i * M + j] += mat1[i * O + k] * mat2[k * M + j];
        }
    }
}

void multiply(float *mat1,
              float *mat2, std::ptrdiff_t N, std::ptrdiff_t M, std::ptrdiff_t O,
              float *res) {
    for (std::ptrdiff_t i = 0; i < N; i++) {
        for (std::ptrdiff_t k = 0; k < M; k++) {
            for (std::ptrdiff_t j = 0; j < O; j++)
                res[i * M + j] += mat1[i * O + k] * mat2[k * M + j];
        }
    }
}

