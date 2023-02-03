#include "MarkovChain.h"
#include <iostream>

int main()
{
	MarkovChain chain;
	for (int i = 0; i < 30; i++)
	{
		std::cout << chain.GenerateSentence() << std::endl;
	}
	return 0;
}