/*#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>
#include <deque>
std::condition_variable con_var;
std::vector<std::thread> producer;
std::vector<std::thread> consumer;
std::vector<std::thread> producerConst;
std::vector<std::thread> consumerConst;
std::mutex mutex_thread;
const int queueSize =4;
int count = 0, prodcount = 0;
int summ = 0;
int TaskNum = 4 * 1024 * 1024;

class Queue {
	std::deque<uint8_t> que;
public:
	void push(uint8_t val)
	{
		que.push_back(val);
	}
	bool pop(uint8_t& val)
	{
		if (que.size() == 0)
		{
			return false;
		}
		else
		{
			que.pop_back();
			return true;
		}
	}
};
Queue q;
void Producer()
{
	int localcount = 0;
	while (localcount < TaskNum)
	{
		int value = 1;
		mutex_thread.lock();
		q.push(value);
		
		localcount++;
		count++;
		prodcount++;
		mutex_thread.unlock();

	}

}
void Consumer()
{

	bool a = true;
	while (a)
	{
		uint8_t id = 0;
		mutex_thread.lock();
		bool temp = q.pop(id);
		mutex_thread.unlock();
		if (!temp && (prodcount == TaskNum)) {
			std::cout << "Empty";
			a = false;
		}
		else {
			summ++;
			count--;
		}
		
	}
}
void ProducerConst()
{
	int localcount = 0;
	while (count < queueSize)
	{
		int value = 1;
		std::unique_lock<std::mutex> locker(mutex_thread);
		q.push(value);
		localcount++;
		count++;
		prodcount++;
		con_var.notify_one();

	}

}
void ConsumerConst()
{

	bool a = true;
	while (a)
	{
		uint8_t id = 0;
		std::unique_lock<std::mutex> locker(mutex_thread);
		bool temp = q.pop(id);
		if (!temp && (prodcount == queueSize)) {
			std::cout << "Empty";

			a = false;
		}
		else {
			summ++;
			count--;
		}
		con_var.notify_one();
	}
}
void main() {
	clock_t start = clock();
	for (int i = 0; i < 1; i++)
		producer.push_back(std::thread(Producer));
	for (int i = 0; i < 1; i++) {
		producer[i].join();
	}
	clock_t end = clock();
	double seconds = (double)(end - start) / CLK_TCK;
	std::cout <<"Producer: " << seconds<< std::endl << prodcount << std::endl;
	start = clock();
	for (int i = 0; i < 1; i++)
		consumer.push_back(std::thread(Consumer));
	for (int i = 0; i < 1; i++) {
		consumer[i].join();
	}
	end = clock();
	seconds = (double)(end - start) / CLK_TCK;
	std::cout << std::endl << "Consumer: " << seconds << std::endl;
	std::cout<<std::endl <<"Sum:" <<summ;
	summ = 0;
	prodcount = 0;
	start = clock();
	for (int i = 0; i < 1; i++)
		producerConst.push_back(std::thread(ProducerConst));
	for (int i = 0; i < 1; i++) {
		producerConst[i].join();
	}
	end = clock();
	seconds = (double)(end - start) / CLK_TCK;
	std::cout << std::endl << "ProducerConst: " << seconds << std::endl;
	start = clock();
	for (int i = 0; i < 1; i++)
		consumerConst.push_back(std::thread(ConsumerConst));
	for (int i = 0; i < 1; i++) {
		consumerConst[i].join();
	}
	end = clock();
	seconds = (double)(end - start) / CLK_TCK;
	std::cout << std::endl << "ConsumerConst: " << seconds << std::endl;
	std::cout << std::endl << "Sum:" << summ;
}*/

