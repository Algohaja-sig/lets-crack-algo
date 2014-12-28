#include <memory>
#include <iostream>
#include <array>
#include <algorithm>

class clocksync
{
private:
	typedef std::array<std::size_t, 16> clocks_t;
	clocks_t clocks;
	typedef std::array<int, 5> clocksPerSwitch_t;
	std::array<clocksPerSwitch_t, 10> switches = {{
	{{0,  1,  2, -1, -1}},
	{{3,  7,  9, 11, -1}},
	{{4, 10, 14, 15, -1}},
	{{0,  4,  5,  6,  7}},
	{{6,  7,  8, 10, 12}},
	{{0,  2, 14, 15, -1}},
	{{3, 14, 15, -1, -1}},
	{{4,  5,  7, 14, 15}},
	{{1,  2,  3,  4,  5}},
	{{3,  4,  5,  9, 13}}
	}};

	std::size_t pressed = 0;
	
	bool allReachTo12(void)
	{
		for(auto clock : clocks)
		{
			if(clock != 12)
			{
				return false;
			}
		}

		return true;
	}

	void updateClocks(const std::size_t switchIdx)
	{
		for(auto idx : switches[switchIdx])
		{
			if(idx == -1)
			{
				break;
			}
			
			std::size_t tmp = clocks[idx] + 3;
			clocks[idx] = ((tmp == 15)?3:tmp);

		}
	}

	int search(const std::size_t button)
	{
		if(allReachTo12() == true)
		{
			return 0;
		}

		if(button == 10)
		{
			return -1;
		}

		std::size_t idx = 0;
		for(; idx < 4; ++idx)
		{
			int ret = search(button + 1);

			++pressed;
			if(ret == 0)
			{
				return pressed;
			}

			updateClocks(button);
		}

	}

public:
	clocksync()
	{
	}

	int calc(void)
	{
		int tmp;
		for(auto &item : clocks)
		{
			std::cin>>item;
		}

		for(auto item : clocks)
		{
			std::cout<<item<<" ";
		}

		if(allReachTo12() == true)
		{
			return 1;
		}

		pressed = 0;
		search(0);

		return pressed;
	}
};


int main(void)
{
	unsigned int total;
	std::cin>>total;

	int i;
	unsigned int input = 0;
	std::unique_ptr<std::size_t[]> result(new std::size_t[total]);

	clocksync cs;
	for(i = 0; i < total; i++)
	{
		result[i] = cs.calc();
	}

    for(i = 0; i< total; i++)
	{	
		std::cout<<"\n---"<<result[i]<<std::endl;
	}

	return 0;
}

