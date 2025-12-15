cmake_minimum_required(VERSION 3.10)
project(cpp-sensor-project VERSION 1.0)

# Встановлюємо стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- БЛОК ОСНОВНОГО КОДУ ---
# Створюємо статичну бібліотеку для основного коду
add_library(sensor_lib STATIC 
    # Вставте тут список усіх ваших .cpp файлів, які не є тестами!
    # Наприклад: src/Analyzer.cpp
    # Якщо у вас багато файлів, ви можете використати file(GLOB)
)

# Створюємо виконуваний файл з main.cpp
add_executable(app_run main.cpp)
target_link_libraries(app_run sensor_lib)

# --- БЛОК ТЕСТІВ ---
enable_testing()
find_package(GTest REQUIRED)

# Додаємо ціль для тестів
add_executable(run_tests 
    # Вставте тут список усіх ваших .cpp файлів, які є тестами!
    # Наприклад: tests/test_analyzer.cpp
)

# Лінкуємо тести з GTest та нашою бібліотекою
target_link_libraries(run_tests 
    GTest::gtest_main 
    GTest::gmock 
    sensor_lib 
)

include(GoogleTest)
gtest_discover_tests(run_tests)

