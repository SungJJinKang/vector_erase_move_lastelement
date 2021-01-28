#include <iostream>
#include <vector>
#include "../vector_swap_erase.h"

class A
{
public:
	int value;

	A(int k) : value{ k }
	{
		std::cout << "default contructor" << std::endl;

	}
	A(const A& a)
	{
	}
	A(A&& a) noexcept
	{
		value = a.value;
		std::cout << "move contructor" << std::endl;
	}

	~A()
	{
	}

	A& operator=(A&& a) noexcept
	{
		value = a.value;
		std::cout << "move assignmnet" << std::endl;
		return *this;
	}
};
int main()
{
	std::vector<A> a{};
	a.emplace_back(1);
	a.emplace_back(2);
	a.emplace_back(3);

	std::vector<int> b{ 1,5,3,2,4,5,6 };

	for (auto& aa : a)
	{
		std::cout << aa.value << " ";
	}
	std::cout << std::endl;

	for (auto& bb : b)
	{
		std::cout << bb << " ";
	}
	std::cout << std::endl;

	std::vector_swap_erase(a, 0);
	std::vector_swap_erase(b, 1);

	std::cout << std::endl;
	for (auto& aa : a)
	{
		std::cout << aa.value << " ";
	}
	std::cout << std::endl;

	for (auto& bb : b)
	{
		std::cout << bb << " ";
	}
	std::cout << std::endl;

}