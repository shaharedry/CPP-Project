//Question 4 - pointers

// There is a memory leak in the code below, where is it?, what class/solution can you use to fix it while ensuring that the object will be deleted only once and only when it's not used by any consumer
// Task: Modify the code to address the issues above. Please explain the changes you made and how they solve the memory allocation/deletion issue  

// The memory leak happends because the program doesn't release the memory at the end of the threads, both threads use the same Payload struct 
// and therefore it was impossible to release the memory at the end of the function without checking if the other thread has finished using 
// the Payload struct.
// I created a new boolean variable for each thread, that when the thread is done changes to true.
// At the end of each thread, check if the other thread has finished via checking the boolean, 
// if the other thread has finished,we can safely delete the Payload struct.

// Do not remove any function or change threads dispatching order - you can(and should) change the functions body/signature

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <mutex>
#include <condition_variable>


struct Payload {

	Payload(uint64_t id_) :
		id(id_),
		veryLargeVector(1000 * 1000)
	{}

	uint64_t id;
	std::vector<int> veryLargeVector;
};

bool Op1Finished = false;
bool Op2Finished = false;

void operation1(Payload* payload) {
	std::cout << "Performing operation1 on payload " << payload->id << "\n" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1))));  //Simulate some heavy work
	std::cout << "Operation1 Performed" << std::endl;
	Op1Finished = true;
	if (Op2Finished == true)
		delete(payload);
}

void operation2(Payload* payload) {
	std::cout << "Performing operation2 on payload " << payload->id << "\n" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1)))));  //Simulate some heavy work
	std::cout << "Operation2 Performed" << std::endl;
	Op2Finished = true;
	if (Op1Finished == true)
		delete(payload);
}

void dispacher_thread() {
	Payload* payload = new Payload(1);
	std::this_thread::sleep_for(std::chrono::seconds(2));  //Simulate some heavy work
	std::thread wt1(&operation1, payload);
	std::thread wt2(&operation2, payload);
	//Waiting for wt1 & wt2 to finish is not allowed, dispacher_thread should exit after creating wt1 and wt2
	wt1.detach();
	wt2.detach();
}

int main(int argc, char** argv)
{
	std::cout << "Calling dispatcher thread" << std::endl;
	std::thread t(&dispacher_thread);
	t.join();
	while (!Op1Finished || !Op2Finished) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}