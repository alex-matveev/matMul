#include <new>
#include <random>
#include <benchmark/benchmark.h>

#include "multiply.h"

class MatrixFixture : public ::benchmark::Fixture {
public:

	void SetUp(const ::benchmark::State& st) {
		std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(-10.0, 10.0);

		N = st.range(0);
		M = st.range(1);
		O = st.range(2);
		a = new(std::align_val_t(32)) float[N * O];
		b = new(std::align_val_t(32)) float[O * M];
		c = new(std::align_val_t(32)) float[N * M];

		for (std::ptrdiff_t i = 0; i < N; i++)
			for (std::ptrdiff_t k = 0; k < O; k++)
				a[i * O + k] = dis(gen);
		
		for (std::ptrdiff_t k = 0; k < O; k++)
			for (std::ptrdiff_t j = 0; j < M; j++)
				b[k * M + j] = dis(gen);
		 
	}

	virtual void TearDown(const ::benchmark::State&) {
		delete[] a;
		delete[] b;
		delete[] c;
	}

	float *a;
	float *b;
	float *c;
	std::ptrdiff_t N, M, O;
};

BENCHMARK_DEFINE_F(MatrixFixture, Simple)(benchmark::State& state) {
    while (state.KeepRunning()) {
       multiply(a, b, N, M, O, c);
    }
}


BENCHMARK_REGISTER_F(MatrixFixture, Simple)->ComputeStatistics("min", [](const std::vector<double>& v) -> double {
    return *(std::min_element(std::begin(v), std::end(v)));
  })->Unit(benchmark::kMillisecond)->Args({4096, 4096, 4096})->Iterations(1)->Repetitions(10);


BENCHMARK_MAIN();
