#include <new>
#include <random>
#include <gtest/gtest.h>

#include "multiply.h"

class MatrixFixture : public ::testing::Test {
protected:

	void SetUp() {
		std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(-10.0, 10.0);

		a = new(std::align_val_t(32)) float[N * O];
		b = new(std::align_val_t(32)) float[O * M];
		reference = new(std::align_val_t(32)) float[N * M];
                result = new(std::align_val_t(32)) float[N * M];

		for (int i = 0; i < N; i++)
			for (int k = 0; k < O; k++)
				a[i * O + k] = dis(gen);
		
		for (int k = 0; k < O; k++)
			for (int j = 0; j < M; j++)
				b[k * M + j] = dis(gen);

		simple_multiply(a, b, N, M, O, reference);
		multiply(a, b, N, M, O, result);
	}

	void TearDown() {
		delete[] a;
		delete[] b;
		delete[] reference;
		delete[] result;
	}

	int N = 1024, M = 1024, O = 1024;

	float *a;
	float *b;
	float *reference;
	float *result;
};

TEST_F(MatrixFixture, test1) {
	for (int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			EXPECT_NEAR(reference[i * M + j], result[i * M + j], 1e-6) << "Matrix differ at index [" << i << ", " << j << "]";
		}
	}
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

