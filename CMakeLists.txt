cmake_minimum_required(VERSION 3.10)
project(CppSonarProject)

set(CMAKE_CXX_STANDARD 17)

# Важливо: ім'я файлу має бути app_run, бо так прописано в Dockerfile
add_executable(app_run main.cpp)
