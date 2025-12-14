FROM gcc:latest as builder
# Виправлення 1: Безпечне встановлення пакетів та очищення кешу
RUN apt-get update && apt-get install -y --no-install-recommends cmake \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .
RUN mkdir build && cd build && cmake .. && make

FROM debian:stable-slim
# Виправлення 2: Створення не-root користувача для безпеки
RUN useradd -m appuser

WORKDIR /app
COPY --from=builder /app/build/app_run .

# Перемикаємося на безпечного користувача
USER appuser

CMD ["./app_run"]
