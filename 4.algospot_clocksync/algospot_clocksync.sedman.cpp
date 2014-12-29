#include <memory>
#include <iostream>
#include <array>
#include <algorithm>
#include <limits>

//#define DEBUG

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

	std::size_t MAX = std::numeric_limits<std::size_t>::max();
	std::size_t minPressed = MAX;
	std::size_t pressed = 0;
	
	bool allReachAt12(void)
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

	void pressSwitch(const std::size_t switchIdx)
	{
#ifdef DEBUG
		std::cout<<"press switch : "<<switchIdx<<std::endl;
#endif
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

	std::size_t search(const std::size_t button)
	{
#ifdef DEBUG
		std::cout<<"+++++ new seach button : "<<button<<std::endl;
#endif
		if(allReachAt12() == true)
		{
			print("allReachAt12");	
			return MAX;
		}

		if(button == 10)
		{
			print("button reaches to 10");	
			return 0;
		}

		std::size_t idx = 0;
		for(; idx < 4; ++idx)
		{
			std::size_t ret = search(button + 1);

#ifdef DEBUG
			std::cout<<"minPressed : "<<minPressed<<" ret : "<<ret<<" idx :"<<idx<<"\n";
#endif
			if(ret == MAX && minPressed > (pressed + idx))
			{
				minPressed = ret + idx;
			}
			else
			{
				pressed = pressed + idx;
			}

			pressSwitch(button);
		}

		print_clocks("------");
		
#ifdef DEBUG
		std::cout<<"\n";
#endif
		return minPressed;

	}

	void print(const std::string debug) const
	{
#ifdef DEBUG
		std::cout<<debug<<std::endl;
#endif		
	}

	void print_clocks(const std::string prefix) const
	{
#ifdef DEBUG
		std::cout<<prefix<<" ";
		std::for_each(clocks.begin(), clocks.end(), [](const std::size_t item){std::cout<<item<<" ";});
		std::cout<<"\n";
#endif	
	}

public:
	clocksync()
	{
	}

	int calc(void)
	{
		pressed = 0;
		minPressed = MAX;
		for(auto &item : clocks)
		{
			std::cin>>item;
		}

#ifdef DEBUG
		for(auto item : clocks)
		{
			std::cout<<item<<" ";
		}
#endif
		if(allReachAt12() == true)
		{
			return 1;
		}

		return search(0);
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

