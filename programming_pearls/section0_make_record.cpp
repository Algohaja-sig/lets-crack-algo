#include <array>
#include <fstream>
#include <random>
#include <algorithm>
#include <iostream>

static const std::size_t nWord = 10000000;
static std::array<int, nWord> map;

std::size_t getRandom(int from, int to)
{
	std::random_device rd;
    std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(from, to);

	return dis(gen);
}

int main(void)
{
	int data = 0;
	for(auto &item : map)
	{
		item = data++; 
	}

	std::size_t cnt = 0;
	while(cnt < (nWord))
	{
		std::size_t idx1 = getRandom(0, nWord - 1);
		std::size_t idx2 = getRandom(0, nWord - 1);
		
		if(idx1 != idx2)
		{
			std::swap(map[idx1], map[idx2]);	
			cnt++;
		}
	}

	std::ofstream file("file.txt");
	for(const auto item : map)
	{
		//std::cout<<item<<std::endl;
		file<<item<<"\n";
	}

	file.close();
	return 0;
}
