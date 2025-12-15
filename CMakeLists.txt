cmake_minimum_required(VERSION 3.10)
project(cpp-sensor-project VERSION 1.0)

# Встановлюємо стандарт C++17 (як і в CI/CD)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Явно включаємо файли з SRC (основний код)
file(GLOB SOURCE_FILES
    "src/*.cpp"
    "src/*.h"
    "main.cpp"
)

# 1. Основна ціль (executable)
add_executable(app_run ${SOURCE_FILES})

# 2. Цілі для тестів
enable_testing()

# Явно включаємо файли з TESTS
file(GLOB TEST_FILES
    "tests/*.cpp"
)

# Обов'язково знаходимо GTest
find_package(GTest REQUIRED)

# Додаємо ціль для тестів
add_executable(run_tests ${TEST_FILES})

# Лінкуємо тести з GTest, Gmock та основним кодом
target_link_libraries(run_tests 
    GTest::gtest_main 
    GTest::gmock 
    app_run
)

# Додаємо тести в CMake
include(GoogleTest)
gtest_discover_tests(run_tests)

