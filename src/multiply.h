#include <cstddef>

void simple_multiply(float *mat1,
              float *mat2, std::ptrdiff_t N, std::ptrdiff_t M, std::ptrdiff_t O,
              float *res);

void multiply(float *mat1,
              float *mat2, std::ptrdiff_t N, std::ptrdiff_t M, std::ptrdiff_t O,
              float *res);
