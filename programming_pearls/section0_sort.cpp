#include <iostream>
#include <array>
#include <fstream>
/*
>>> 1.2*1024*1024*8
10066329.6

>>> 1024 * 1024 * 1.2 / 4(byte, int)
 = 314572.8

>>> 9999999%32
31
>>> 9999999/32
312499
>>> 
 */
static std::array<int, 312500> map;

bool checkDuplicate(const std::size_t input )
{
	std::size_t groupIdx = input/32; 
	std::size_t bitIdx = input%32; 

	//std::cout<<"groupIdx :"<<groupIdx<<" bitIdx : "<<bitIdx<<std::endl;

	int data = map[groupIdx];

	int cmpbit = 0x1<<bitIdx;

	//std::cout<<"data :"<<data<<" cmpbit : "<<cmpbit<<" result : "<<(data&cmpbit)<<std::endl;
	
	if((data & cmpbit) == cmpbit)
	{
		return true;
	}
	else
	{
		map[groupIdx] = (data | cmpbit);
		return false;
	}
}

int main(void)
{
	for(auto &item : map)
	{
		item = 0x00000000;
	}

	std::ifstream file("file.txt");

	std::string str_number;	
	if(file.is_open() == true)
	{
		while(file.eof() == false)
		{
			std::getline(file, str_number);
		
			if(str_number.empty() == true)
			{
				break;
			}

			if(checkDuplicate(std::stoi(str_number)) == true)
			{
				std::cout<<std::string(str_number)<<std::endl;
				std::cerr<<"error duplicate!!"<<std::endl;	
				exit(0);
			}
		}
	}

	std::ofstream file_w("result.txt");
	
	std::size_t cnt = 0;
	for(const auto item : map)
	{
		int mask;
		for(int shift = 0; shift < 32; ++shift)
		{
			mask = 0x1<<shift;
			if(item & mask == mask)
			{
				std::size_t data = (cnt * 32) + shift;
				file_w<<data<<"\n";
			}
		}

		++cnt;
	}

	std::cout<<cnt<<std::endl;

	file_w.close();
	file.close();


	return 0;
}
