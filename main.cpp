#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <mutex>


class RandomSumThread {
private:
    int id;
    int sum;
public:
    RandomSumThread(int thread_id) : id(thread_id), sum(0) {}

    void run() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000);

        for (int i = 0; i < 100; i++) {
            sum += dis(gen);
        }
    }

    int getSum() const {
        return sum;
    }

    int getId() const {
        return id;
    }
};

int main() {
    const int NUM_THREADS = 10;
    std::vector<RandomSumThread> workers;
    std::vector<std::thread> threads;

    // Crear los objetos
    for (int i = 0; i < NUM_THREADS; i++) {
        workers.emplace_back(i+1);
    }

    // Lanzar los threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threads.emplace_back(&RandomSumThread::run, &workers[i]);
    }

    // Esperar que todos terminen
    for (auto& t : threads) {
        t.join();
    }

    // Mostrar resultados y determinar el thread con mayor puntuación
    int maxSum = 0;
    int maxId = 0;

    for (auto& w : workers) {
        std::cout << "Thread " << w.getId() << " sum: " << w.getSum() << std::endl;
        if (w.getSum() > maxSum) {
            maxSum = w.getSum();
            maxId = w.getId();
        }
    }

    std::cout << "Thread con puntuación más alta: Thread " << maxId
              << " con suma " << maxSum << std::endl;

    return 0;
}
