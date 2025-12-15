cmake_minimum_required(VERSION 3.10)
project(cpp-sensor-project VERSION 1.0)

# Встановлюємо стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- 1. СТВОРЕННЯ БІБЛІОТЕКИ ОСНОВНОГО КОДУ (sensor_lib) ---
# Бібліотека містить усі класи, які ми тестуємо.
add_library(sensor_lib STATIC 
    src/Analyzer.cpp
)

# --- 2. СТВОРЕННЯ ВИКОНУВАНОГО ФАЙЛУ (app_run) ---
# Це виконуваний файл, який запускає функцію main()
add_executable(app_run main.cpp)
# Лінкуємо його з нашою бібліотекою
target_link_libraries(app_run sensor_lib)

# --- 3. СТВОРЕННЯ ВИКОНУВАНОГО ФАЙЛУ ТЕСТІВ (run_tests) ---
enable_testing()
find_package(GTest REQUIRED)

# Додаємо ціль для тестів
add_executable(run_tests 
    tests/test_analyzer.cpp
)

# Лінкуємо тести з GTest, Gmock та нашим основним кодом (бібліотекою)
target_link_libraries(run_tests 
    GTest::gtest_main 
    GTest::gmock 
    sensor_lib 
)

include(GoogleTest)
gtest_discover_tests(run_tests)

