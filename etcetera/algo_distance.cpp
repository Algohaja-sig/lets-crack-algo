#include <iostream>
#include <memory>
#include <unordered_map>

namespace util
{
	std::size_t abs(int data)
	{
		return ((data < 0)? -data : data);
	}
}

class distance
{
private:
	std::size_t get_distance(std::size_t chosen_idx, std::unique_ptr<int[]> &&data, std::size_t num)
	{
		std::size_t sum = 0;
		auto chosen_data = data[chosen_idx];
		for(auto i = 0; i < num; ++i)
		{
			if(i != chosen_idx)
			{
				sum += util::abs(data[i] - chosen_data);	
			}
		}

		return sum;
	}

public:
	std::size_t calc(void)
	{
		std::size_t num;
		std::cin>>num;

		std::unique_ptr<int[]> data(new int[num]);

		std::size_t idx;
		for(idx = 0; idx < num; ++idx)
		{
			std::cin>>data[idx];
		}

		std::size_t sum = 0;
		std::unordered_map<int, std::size_t> cache;
		for(idx = 0; idx < num; ++idx)
		{
			//lookup the cache
			//if exists, plus cached value to sum
			auto found = cache.find(data[idx]); 
			if(found != cache.end())
			{
				//std::cout<<"cached data : "<<found->first<<std::endl;
				sum += found->second;		
			}
			//otherwise, calculate distance then put into hashtable.
			else
			{
				auto dist = get_distance(idx, std::move(data), num);

				cache.insert({data[idx], dist});

				sum += dist;
			}
		}

		return sum;
	}

};

int main(void)
{
	unsigned int total;
	std::cin>>total;//the number of test case

	std::unique_ptr<std::size_t[]> result(new std::size_t[total]);
	
	std::unique_ptr<distance> dist(new distance);
	for(int i = 0; i < total; i++)
	{
		result[i] = dist->calc();
	}
	
	//std::cout<<"\n result \n";
	
  for(int i = 0; i< total; i++)
	{
		std::cout<<result[i]<<std::endl; 
	}

	return 0;
}	

