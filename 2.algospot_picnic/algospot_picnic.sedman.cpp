#include <memory>
#include <vector>
#include <iostream>

class picnic
{
private:
	bool pairDone;

	class pair
	{
	public:
		int x,y;

		bool operator!=(const pair &rhs)
		{
			if(this == &rhs)
			{
				return false;
			}

			if(x == rhs.x || y == rhs.y
			|| x == rhs.y || y == rhs.x)
			{
				return false;
			}

			return true;
		}

		bool operator==(const pair &rhs)
		{
			return !operator!=(rhs);
		}

	};

	bool duplicateInGroup(const std::vector<pair> &group, const pair& p)
	{
		
		for(auto item : group)
		{
			if(item == p)
			{
				return true;
			}
		}

		return false;
	}

public:
	picnic()
	:pairDone(false)
	{
	}

	std::size_t calc(void)
	{
		std::size_t numOfStudent;
		std::size_t numOfPair;

		std::cin>>numOfStudent;
		std::cin>>numOfPair;
		//numOfPair = numOfStudent*(numOfStudent - 1) / 2;

		int i = 0;
		std::vector<pair> vec_pair;
		pair pair_item;
		for(; i < numOfPair; ++i)
		{
			std::cin>>pair_item.x;
			std::cin>>pair_item.y;

			vec_pair.push_back(pair_item);
		}

#ifdef DEBUG
		for(auto item:vec_pair)
		{
			std::cout<<"("<<item.x<<" "<<item.y<<")"<<std::endl;
		}
#endif

		if(vec_pair.size() == 1)
		{
			return 1;
		}
		
		std::list<int> students;
		stsudents.reserve(numOfStudent);
	
		std::size_t current = 0;
		for(auto item : students)
		{
			
			getPair(current, 	

			current++;
		}
		
		return numOfCase;
	}
};

int main(void)
{
	unsigned int total;
	std::cin>>total;//the number of test case

	int i;
	unsigned int input = 0;
	std::unique_ptr<double[]> result(new double[total]);

	picnic pic;
	for(i = 0; i < total; i++)
	{
		result[i] = pic.calc();
	}
	
	//std::cout<<"\n result \n";
	
    for(i = 0; i< total; i++)
	{	
		std::cout<<result[i]<<std::endl;
		//std::cout<<std::fixed;
		//std::cout<<std::setprecision(7)<<result[i]<<std::endl;
	}

	return 0;
}

