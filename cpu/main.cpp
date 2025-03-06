#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <cmath>
#include <atomic>
#include <iomanip>

// 计算密集型任务
void calculate(double duration, std::atomic<bool>& running, double& progress) {
    auto start = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed;
    while (running && elapsed.count() < duration) {
        // 执行一些计算密集型操作
        double result = 0;
        for (int i = 0; i < 100000; ++i) {
            result += std::sin(i) * std::cos(i);
        }
        auto now = std::chrono::high_resolution_clock::now();
        elapsed = now - start;
        progress = elapsed.count() / duration;
    }
}

void printProgressBar(double progress) {
    int barWidth = 50;
    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << std::fixed << std::setprecision(1) << progress * 100.0 << "%";
    std::cout << "\r"; // 回车，覆盖上一行
    std::cout.flush(); // 强制刷新输出
}

int main() {
    // 获取 CPU 核心数
    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) {
        numThreads = 4;
    }
    std::cout << "CPU Cores: " << numThreads << std::endl;

    // 设置运行时间（10 分钟）
    double duration = 10 * 60;

    // 创建线程和进度变量
    std::vector<std::thread> threads;
    std::atomic<bool> running(true);
    std::vector<double> progresses(numThreads, 0.0);
    for (unsigned int i = 0; i < numThreads; ++i) {
        threads.emplace_back(calculate, duration, std::ref(running), std::ref(progresses[i]));
    }

    // 显示进度条
    auto startTime = std::chrono::high_resolution_clock::now();
    while (running) {
        double totalProgress = 0.0;
        for (double progress : progresses) {
            totalProgress += progress;
        }
        totalProgress /= numThreads;
        printProgressBar(totalProgress);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 每 100 毫秒更新一次
        auto now = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::minutes>(now - startTime).count() >= 10) {
            break;
        }
    }
    std::cout << std::endl; // 换行

    // 停止线程
    running = false;
    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "CPU usage decreased." << std::endl;

    return 0;
}