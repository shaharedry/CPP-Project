//Question 2 - threads & synchronization

//Task: Improve execution time by using multi-threading instead of calling operation1 and operation2 serially, make sure that sum=EXPECTED_SUM after using threads
// please explain the changes you made and what new aspects you had to deal with when shifting from serial execution to parallel execution 

// Make sure you compile the code in "Release" configuration (e.g O2 optimization level).
// Do not modify the constexpr variables

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>

constexpr size_t ITERATIONS = 1000 * 1000ULL;
constexpr size_t OP1_PARAM = 2ULL;
constexpr size_t OP2_PARAM = 1ULL;
constexpr size_t EXPECTED_SUM = 1000001000000ULL;

size_t gSum1 = 0;
size_t gSum2 = 0;

void operation1(size_t arg) {
	std::cout << "Performing operation1\n" << std::endl;
	for (size_t i = 0; i < ITERATIONS; i++) {
		gSum1 += (arg + i);
	}
	std::this_thread::sleep_for(std::chrono::seconds(5)); //Simulate some heavy work
	std::cout << "Operation1 Performed" << std::endl;
}


void operation2(size_t arg) {
	std::cout << "Performing operation2\n" << std::endl;
	for (size_t i = 0; i < ITERATIONS; i++) {
		gSum2 += (arg * i);
	}
	std::this_thread::sleep_for(std::chrono::seconds(10));  //Simulate some heavy work
	std::cout << "Operation2 Performed" << std::endl;
}


int main(int argc, char** argv)
{
	auto start = std::chrono::steady_clock::now();
	std::thread t1(operation1, OP1_PARAM); //Start a new thread that will handle operation1
	//operation1(OP1_PARAM);
	std::thread t2(operation2, OP2_PARAM); //Start a new thread that will handle operation1
	//operation2(OP2_PARAM);
	t1.join(); // Wait for operation1 thread to finish
	t2.join(); // Wait for operation1 thread to finish
	auto end = std::chrono::steady_clock::now();

	size_t Sum = gSum1 + gSum2;

	std::cout << "Total execution duration in milliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
	std::cout << "Result:  " << Sum << ", " << (Sum == EXPECTED_SUM ? "success" : "failure!") << std::endl;
	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}