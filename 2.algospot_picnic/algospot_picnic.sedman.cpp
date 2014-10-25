#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>


//#define DEBUG

class picnic
{
private:
	std::size_t numOfStudent;
	std::size_t numOfPair;
	std::size_t numOfPairInOne;
	std::size_t total = 0;

	class pair
	{
	public:
		int x = 0,y = 0;
		bool valid = false; 

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

		void print(const std::string &prefix) const
		{
#ifdef DEBUG
			std::cout<<"[ "<<prefix<<" ] x : "<<x<<" y : "<<y<<std::endl;
#endif
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

	bool getPair(std::vector<pair> &remain, std::vector<pair> &paired)
	{
#ifdef DEBUG
		std::cout<<"------in\n";
#endif	
		if(paired.size() == numOfPairInOne)
		{
			total++;
#ifdef DEBUG			
			std::for_each(paired.begin(), paired.end(), [](const pair& item) { item.print("pair:");});
			std::cout<<"++++++++++++hit!\n\n";
#endif	
			return true;
		}

		if(remain.size() == 0)
		{
#ifdef DEBUG
			std::cout<<"remain becomes zero\n";
#endif			
			return false;
		}

		std::vector<pair>::iterator pos = remain.begin();
		while(pos != remain.end())
		{
			if(duplicateInGroup(paired, *pos) == true)
			{
				pos->print("duplicated!");
				remain.erase(pos);
			}
			else
			{
				++pos;
			}
		}

		std::vector<pair> remainHere;
		remainHere.assign(remain.begin(), remain.end());
		
		pos = remainHere.begin();
		while(pos != remainHere.end())
		{
#ifdef DEBUG 
			pos->print("#####no duplicated");
#endif			
			paired.push_back(*pos);	

#ifdef DEBUG
			std::cout<<"[before]remain size : "<<remainHere.size()<<" paired size : "<<paired.size()<<std::endl;
#endif

			bool ret = getPair(remain, paired);

#ifdef DEBUG
			std::cout<<"[after]remain size : "<<remainHere.size()<<" paired size : "<<paired.size()<<std::endl;
#endif
	
			if(ret == false)
			{
				remain.assign(remainHere.begin(), remainHere.end());
			}

			paired.pop_back();

			++pos;
		}

		return false;
	}

	std::size_t getDuplicate(std::size_t pairs)                                                                                         
	{                                                                                                                                   
		std::size_t cases = pairs;                                                                                                      
		while((--pairs) > 1)                                                                                                            
		{                                                                                                                               
			cases *= pairs;                                                                                                             
		}                                                                                                                               

		return cases;                                                                                                                   
	}

public:
	picnic()
	{
	}

	std::size_t calc(void)
	{
		total = 0;
		std::cin>>numOfStudent;
		std::cin>>numOfPair;
		//numOfPair = numOfStudent*(numOfStudent - 1) / 2;
		numOfPairInOne = numOfStudent / 2;

		int i = 0;
		std::vector<pair> friend_pair;
		pair pair_item;
		for(; i < numOfPair; ++i)
		{
			std::cin>>pair_item.x;
			std::cin>>pair_item.y;

			friend_pair.push_back(pair_item);
		}

#ifdef DEBUG
		for(auto item:friend_pair)
		{
			std::cout<<"("<<item.x<<" "<<item.y<<")"<<std::endl;
		}
#endif

		if(friend_pair.size() < (numOfStudent/2))
		{
			return 0;
		}
		
		if(numOfPair == 1 && numOfStudent == 2)
		{
			return 1;
		}
		
		std::vector<pair> paired;
		std::vector<pair> remain;
		
		for(auto item : friend_pair)
		{
			paired.clear();
			paired.push_back(item);
			remain.assign(friend_pair.begin(), friend_pair.end());
			item.print("\nstart!");
			getPair(remain, paired);
		}

		return (total / getDuplicate(numOfPairInOne));
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

