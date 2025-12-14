#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <sstream>

// Функція для генерації випадкових значень (імітація роботи датчика)
double get_sensor_value(double base, double variance) {
    // Проста імітація коливань
    return base + ((rand() % 100) / 100.0 * variance - (variance / 2));
}

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, 1024);

    // Генеруємо свіжі дані датчиків
    double temp = get_sensor_value(22.0, 2.0); // Температура ~22C
    double humidity = get_sensor_value(45.0, 5.0); // Вологість ~45%
    double pressure = get_sensor_value(1013.0, 10.0); // Тиск ~1013 hPa

    // Формуємо JSON вручну
    std::stringstream json_ss;
    json_ss << "["
            << "{\"id\": \"SENS-01\", \"type\": \"Temperature\", \"value\": " << temp << ", \"unit\": \"°C\", \"status\": \"OK\"},"
            << "{\"id\": \"SENS-02\", \"type\": \"Humidity\", \"value\": " << humidity << ", \"unit\": \"%\", \"status\": \"OK\"},"
            << "{\"id\": \"SENS-03\", \"type\": \"Pressure\", \"value\": " << pressure << ", \"unit\": \"hPa\", \"status\": \"Active\"},"
            << "{\"id\": \"SENS-04\", \"type\": \"Vibration\", \"value\": 0.05, \"unit\": \"g\", \"status\": \"Stable\"}"
            << "]";
    
    std::string json_response = json_ss.str();

    // Заголовки HTTP
    std::string http_response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json; charset=utf-8\r\n"
        "Connection: close\r\n"
        "\r\n" + json_response;

    send(client_socket, http_response.c_str(), http_response.length(), 0);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Створення сокету
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        return 1;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        return 1;
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        return 1;
    }

    std::cout << "IoT Sensor Service started on port 8080..." << std::endl;

    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept");
            continue;
        }
        std::thread(handle_client, new_socket).detach();
    }
    
    return 0;
}
