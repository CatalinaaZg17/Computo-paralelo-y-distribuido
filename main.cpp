#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <mutex>

// 10 threads,  cada uno sumará 100 números aleatorios entre 1 y 1000.
//  Mostrar el resultado de cada thread. Enunciar el thread con puntuación más alta
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

    // Mostrar resultados y el thread con mayor puntuación
    int maxSum = 0;
    int maxId = 0;

    std::cout << "\n\033[1;34m=== Resultados  ===\033[0m\n";

    for (auto& w : workers) {
        std::cout << "Thread " << w.getId() << " sum: " << w.getSum() << std::endl;
        if (w.getSum() > maxSum) {
            maxSum = w.getSum();
            maxId = w.getId();
        }
    }

    std::cout << "\n\033[1;32m Thread con puntuación más alta: Thread "
              << maxId << " con suma " << maxSum << " \033[0m\n";

    return 0;
}
