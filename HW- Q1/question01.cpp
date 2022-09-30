#include <functional>
// Question 1 - functions
// 
//	you are given the following missing implementation:
//	float applyF(float a, float b, ??????)
//	{
//		return f(a, b);
//	}
//	
//	1) list at least 3 different ways to replace the qustion marks (??????)
//		1. std::function<float(float, float)>f
//		2. float(*f)(float, float)
//		3. float f(float, float)
//	
//	2) replace the qustion marks in the following implementations with the solutions you listed
//
//	3) using one of those options create an add operation and a multiply operation and implement the following computation:
//		(2 * 3) + (4 * 5) + 6
//
//	you may not change the functions' implementation, only complete the signature


float applyF1(float a, float b, std::function<float(float, float)>f)
{
	return f(a, b);
}

float applyF2(float a, float b, float(*f)(float, float))
{
	return f(a, b);
}

float applyF3(float a, float b, float f(float, float))
{
	return f(a, b);
}


int main(int argc, char* argv[])
{
	float fNum = 0;
	//calculate fNum = (2 * 3) + (4 * 5) + 6

	//TODO: Your code here
	auto add = [](float a, float b)-> float { return a + b; };
	auto mul = [](float a, float b)-> float { return a * b; };

	fNum = applyF3(applyF2(applyF1(2, 3, mul), applyF1(4, 5, mul), add), 6, add);

	return 0;
}

