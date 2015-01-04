#include <memory>
#include <iostream>
#include <array>
#include <algorithm>
#include <limits>


/* TODO : no need to use TEXTBOOK define
*/

/* [brief]
 * clocksync 
 * https://algospot.com/judge/problem/read/CLOCKSYNC
 * performance : 2877ms
 * etc : c++11
 */

//#define DEBUG
//#define TEXTBOOK

class clocksync
{
private:
	clocksync(const clocksync&) = delete;
	clocksync& operator=(const clocksync& ) = delete;

protected:
	typedef std::array<std::size_t, 16> clocks_t;
	clocks_t clocks;
	typedef std::array<int, 5> clocksPerSwitch_t;
	
	static const std::size_t nSwitch = 10;
	std::array<clocksPerSwitch_t, nSwitch> switches = {{
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
	std::size_t pressed = 0;
	std::size_t minPressed = MAX;
	static const int HIT = 0;

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

	virtual std::size_t search(const std::size_t cur_switch)
	{
#ifdef DEBUG
		std::cout<<"\n+++++ new seach cur_switch : "<<cur_switch<<" pressed : "<<pressed<<std::endl;
#endif
		//hit!!!
		if(allReachAt12() == true)
		{
			print("******allReachAt12");	
			return HIT;
		}

		//Can't go further.
		if(cur_switch == nSwitch)
		{
			print("------cur_switch reaches to max. nSwitch");	
			return MAX;
		}

		//0 ~ 2 : press
		//3 : no press 
		std::size_t idx = 0;
		for(; idx < 4; ++idx)
		{
			std::size_t ret = search(cur_switch + 1);
#ifdef DEBUG
			std::cout<<"minPressed : "<<minPressed<<" ret : "<<ret<<" idx :"<<idx<<"\n";
#endif
			if(ret == HIT && minPressed > pressed)
			{
				minPressed = pressed;
			}

			++pressed;

			pressSwitch(cur_switch);
			print_clocks("");
		}

		//restore, bacause clock returns to its original point.
		pressed -= 4;
		
		return minPressed;
	}

	void print(const std::string& debug) const
	{
#ifdef DEBUG
		std::cout<<debug<<std::endl;
#endif		
	}

	void print_clocks(const std::string& prefix) const
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
		//init
		pressed = 0;
		minPressed = MAX;
		
		//prepare input
		for(auto &item : clocks)
		{
			std::cin>>item;
		}

		print_clocks("");
	
		//exception case
		if(allReachAt12() == true)
		{
			return 1;
		}
		
#ifdef TEXTBOOK
		return search(0);
#else
		search(0);
		return (minPressed == MAX) ? -1 : minPressed;
#endif
	}
};

#ifdef TEXTBOOK 
/*
 * It always returns 0 because std::min always gets 0 when it finds "all 12s",
 * which is the least value. This is wrong
 */
class clocksync_textbook : public clocksync
{
private:
	std::size_t search(const std::size_t cur_switch)
	{
		//basis
		//what if cur_switch is less than nSwitch but alreay HIT!
		if(cur_switch == nSwitch)
		{
			return allReachAt12() ? HIT : MAX;
		}
		
		std::size_t ret = MAX;

		//recursive
		for(int cnt = 0; cnt < 4; ++cnt)
		{
			ret = std::min(ret, cnt + search(cur_switch + 1));
			pressSwitch(cur_switch);
		}

		//if any "HIT" is not found, ret returns MAX
		return ret;
	}
};
#endif

int main(void)
{
	unsigned int total;
	std::cin>>total;

	int i;
	unsigned int input = 0;
	std::unique_ptr<int[]> result(new int[total]);

#ifdef TEXTBOOK
	std::unique_ptr<clocksync> cs(new clocksync_textbook);
#else
	std::unique_ptr<clocksync> cs(new clocksync);
#endif	
	for(i = 0; i < total; i++)
	{
		result[i] = cs->calc();
	}

    for(i = 0; i< total; i++)
	{	
		std::cout<<result[i]<<std::endl;
	}

	return 0;
}

