// Question 5
//
//	we want to implement a logic class named MyBool to use in our logic
//	we would like to be able to use the logical and (&&) with instances of this class 
//  i.e. to be able to write in the form of myBool1 && myBool2
//	we have also implemented some function using this class
//	"notNull" checks if a pointer is null and return a corresponding MyBool
//  "greaterThanZero" checks if an int pointer points to a positive int and return a corresponding MyBool
//
//	1. Implement this addition in the MyBool class
//  2. Did it compile successfully?  Yes
//	3. Did it run successfully? No
//	4. Explain the result, explain what happened and why - 
//		The problem is in greaterThanZero function, this function doesn't check if the pointer is null before trying to check if the value is greater than zero
//		and therefore the run crashes with the error "read access violation intPtr was nullptr."
//		We can fix this issue by a simple if inside greaterThanZero function that checks if the pointer is not null before trying
//		to check if the value is greater than zero, if it's null return false.

// useful links:
// https://en.cppreference.com/w/cpp/language/operators
// https://cplusplus.com/doc/tutorial/operators/
// https://isocpp.org/wiki/faq/operator-overloading

#include <iostream>

class MyBool
{
public:
	MyBool(bool b) : m_val(b) {};

	//TODO: Your code here
	bool operator && (const MyBool& obj) {
		if (m_val == false) {
			return false;
		}
		if (obj.m_val == false) {
			return false;
		}
		return true;
	}


private:
	bool m_val;
};

MyBool notNull(int* intPtr)
{
	return intPtr != nullptr;
}

MyBool greaterThanZero(int* intPtr)
{
	return *intPtr > 0;
}

int main(int argc, char* argv[])
{
	int* a = nullptr;
	int val = 5;
	int* b = &val;


	// the long way to check
	if (a != nullptr && *a > 0)
	{
		++* a;
		std::cout << "*a is " << *a << std::endl;
	}

	// using our functions
	if (notNull(b) && greaterThanZero(b))
	{
		++* b;
		std::cout << "*b is " << *b << std::endl;
	}

	// using our functions again
	if (notNull(a) && greaterThanZero(a))
	{
		++* a;
		std::cout << "*a is " << *a << std::endl;
	}

	return 0;
}