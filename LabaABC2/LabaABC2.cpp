// LabaABC2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>

std::mutex g_lock;
//int namTaskAtomic[1048576];
std::atomic<int> namTaskAtomic[1048576]{0};
int *namTaskMutex = new int[1048576];
std::atomic<int> count_atomic{0};
int count = 0;
std::vector<std::thread> mutex_th;
std::vector<std::thread> atomic_th;
void threadFunctionAtomic()
{
    while (count_atomic < 1048576) {

        int temp = count_atomic.fetch_add(1);
        std::atomic_fetch_add(&namTaskAtomic[temp], 1);
       //std::this_thread::sleep_for(std::chrono::nanoseconds(10));
    }
}
void threadFunctionMutex()
{
    while (count < 1048576) {

        g_lock.lock();
        namTaskMutex[count]++;
        count++;
        //std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        g_lock.unlock();
    }
}

int main()
{
    for (int i = 0; i < 1048576; i++) {
        namTaskMutex[i] = 0;
    }
    clock_t start = clock();
    for (int i = 0; i < 32; i++) 
        mutex_th.push_back(std::thread(threadFunctionMutex));
    for (int i = 0; i < 32; i++) {
        mutex_th[i].join();
    }
    for (int i = 0; i < 1048576; i++) {
        std::cout << namTaskMutex[i];
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLK_TCK;
    std::cout << seconds << std::endl;
    for (int i = 0; i < 32; i++)
        atomic_th.push_back(std::thread(threadFunctionAtomic));
    start = clock();
    for (int i = 0; i < 32; i++) {
        atomic_th[i].join();
    }
    end = clock();
    seconds = (double)(end - start) / CLK_TCK;
    std::cout << seconds << std::endl;
    return 0;
}