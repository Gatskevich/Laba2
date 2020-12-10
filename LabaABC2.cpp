#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>

std::mutex th;
const int  numTasks = 1048576;
int *namTaskAtomic=new int[numTasks];
//std::atomic<int> namTaskAtomic[1048576]{0};
int *namTaskMutex = new int[numTasks];
std::atomic<int> count_atomic{0};
int count = 0;
std::vector<std::thread> mutex_th;
std::vector<std::thread> atomic_th;
void threadFunctionAtomic()
{
    while (count_atomic < numTasks) {

        int temp = count_atomic.fetch_add(1);
        namTaskAtomic[temp]++;
        //std::atomic_fetch_add(&namTaskAtomic[temp], 1);
       //std::this_thread::sleep_for(std::chrono::nanoseconds(10));
    }
}
void threadFunctionMutex()
{
    while (count < numTasks) {

        th.lock();
        namTaskMutex[count]++;
        count++;
        //std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        th.unlock();
    }
}

int main()
{
    for (int i = 0; i < numTasks; i++) {
        namTaskMutex[i] = 0;
    }
    clock_t start = clock();
    for (int i = 0; i < 32; i++) 
        mutex_th.push_back(std::thread(threadFunctionMutex));
    for (int i = 0; i < 32; i++) {
        mutex_th[i].join();
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLK_TCK;
    std::cout <<"Mutex: "<< seconds << std::endl;
    for (int i = 0; i < 32; i++)
        atomic_th.push_back(std::thread(threadFunctionAtomic));
    start = clock();
    for (int i = 0; i < 32; i++) {
        atomic_th[i].join();
    }
    end = clock();
    seconds = (double)(end - start) / CLK_TCK;
    std::cout<<"Atomic: "<< seconds << std::endl;

    return 0;
}