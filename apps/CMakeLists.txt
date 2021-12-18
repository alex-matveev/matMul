FIND_PACKAGE(GTest REQUIRED)
FIND_PACKAGE(benchmark REQUIRED)

ADD_EXECUTABLE(matMulBench
               $<TARGET_OBJECTS:mult>
               matMulBench.cpp)
TARGET_LINK_LIBRARIES(matMulBench benchmark::benchmark)

ADD_EXECUTABLE(matMulTest
               $<TARGET_OBJECTS:mult>
               matMulTest.cpp)
TARGET_LINK_LIBRARIES(matMulTest GTest::GTest)

