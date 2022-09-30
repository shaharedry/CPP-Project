// Question 3 - implementation
// 
//	without using STL containers implement the following:
//	A class for a dynamic int array, let's call it "CVectorInt" that -
//  1. doubles its size automatically when its full (allocates twice the size and moves the data),
//	2. halves its size when it is half empty (allocates half of the size and moves the data)
//  3. can be told the initial capacity (num of ints) in a constructor
//  4. have a method called "reserve" - that Requests that the vector capacity be at least enough to contain n elements.
//     If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n
//  5. have a method called "capacity" - that **returns the number of int elements allocated
//  6. have a method called "size" - that **returns the number of elements actually inserted
//  7. have a method called "empty" - that **returns true/false according to amount of actual elements in the data
//  8. have a method called "clear" - that frees all the data and resets the size
//  9. have a method called "push_back" - that adds an int elements at the end
// 10. have a method called "pop_back" - that removes an int elements at the end and **return it
// 11. have a method called "remove"  - that removes an int elements at specific index
// 12. have an interface to access the data at a specific index using subscript "[]"
//
// make sure to handle edge cases such as memory issues, size issues etc.


#include <iostream>
#include <stdexcept>

class CVectorInt
{
	// TODO: your code here
public:
	int* Array;
	int sizeOfArray = 0;
	int ElementInUse = 0;

	CVectorInt() {
		Array = new int();
		sizeOfArray = 0;
	}
	~CVectorInt() {
		std::cout << "Array is being deleted \n";
	}
	CVectorInt(int n) {
		Array = new int(n);
		sizeOfArray = n;
	}

	void reserve(int n) {
		if (n > sizeOfArray) {
			int* temp = new int[n];
			std::copy(Array, Array + sizeOfArray, temp);
			Array = new int[n];
			std::copy(temp, temp, Array);
			sizeOfArray = n;
		}
	}

	int capacity() {
		return sizeOfArray;
	}

	int size() {
		return ElementInUse;
	}

	bool empty() {
		if (ElementInUse == 0)
			return true;
		return false;
	}

	void clear() {
		Array = new int();
		sizeOfArray = 0;
		ElementInUse = 0;
	}

	void push_back(int n) {
		if (!(ElementInUse != sizeOfArray)) {
			doublesArray();
		}
		Array[ElementInUse] = n;
		ElementInUse++;
	}

	int pop_back() {
		int popNum = Array[ElementInUse - 1];
		Array[ElementInUse - 1] = NULL;
		ElementInUse--;
		if (ElementInUse <= sizeOfArray / 2) {
			halves();
		}
		return popNum;
	}

	int renove(int index) {
		int* temp = new int[sizeOfArray];
		int count = 0;
		for (int i = 0; i < sizeOfArray; i++) {
			if (i != index) {
				temp[count] = Array[i];
				count++;
			}
		}
		delete[] Array;
		Array = temp;
	}

	int& operator[](int index)
	{
		if (index >= sizeOfArray) {
			std::cout << "Array index out of bound, exiting";
			exit(0);
		}
		return Array[index];
	}

protected:


private:
	void doublesArray() {
		int* temp = new int(sizeOfArray * 2);
		size_t size = sizeOfArray * 2;
		std::copy(Array, Array + sizeOfArray, temp);
		std::copy(temp, temp, Array);
		Array = temp;
		sizeOfArray *= 2;
	}

	void halves() {
		int newSize = sizeOfArray / 2;
		if (newSize > ElementInUse) {
			int* temp = new int(newSize);
			std::copy(Array, Array - sizeOfArray, temp);
			std::copy(temp, temp, Array);
			Array = temp;
		}
		sizeOfArray = newSize;
	}
};

int main(int argc, char* argv[])
{
	// some code to use the class
	try
	{
		CVectorInt v(5);

		for (int i = 0; i < 5; i++)
		{
			v.push_back(i);
		}
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		v.push_back(1);
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		while (!v.empty())
		{
			v.pop_back();
		}
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		v.reserve(15);
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		for (int i = 0; i < 15; i++)
		{
			v.push_back(i);
		}
		v[5] = 3;
		for (int i = 0; i < v.size(); i++)
		{
			std::cout << v[i] << " ";
		}
		std::cout << std::endl;
		v.clear();
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}