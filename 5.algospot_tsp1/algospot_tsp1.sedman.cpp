#include <memory>
#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

/** [TODO]
 * - remove duplicate search (should approach another way)
 */

/* [History]
 * - still fail
 *   : fixed "no reset least Distance in calc" and passed
 */

/* [brief]
 * title : tsp1 
 * url : https://algospot.com/judge/problem/read/TSP1
 * performance : 35ms 
 * etc : c++11
 */
//#define DEBUG

class tsp1
{
private:
	tsp1(const tsp1 &) = delete;
	tsp1(const tsp1 &&) = delete;
	tsp1& operator=(const tsp1 &) = delete;
	tsp1& operator=(const tsp1 &&) = delete;


	void debug_print(const std::string str) const
	{
#ifdef DEBUG
		std::cout<<str<<std::endl;
#endif
	}

	void debug_print_map(const std::string prefix) const
	{
#ifdef DEBUG
		std::cout<<"["<<prefix<<"] \n";
		for(auto yitem : matrix)
		{
			for(auto xitem : yitem)
			{
				std::cout<<xitem<<" ";		
			}

			std::cout<<"\n";
		}
#endif
	}

	std::size_t cities = 0; 
	std::size_t visitedNum = 0; 
	double leastDistance = std::numeric_limits<double>::max();
	double curDistance = 0;
	typedef std::vector<double> distType;
	std::vector<distType> matrix;
	std::vector<bool> visited;

	void search(std::size_t cur_pos)
	{
		//basis
		if(visitedNum == cities)
		{
#ifdef DEBUG
			std::cout<<"arrived!!\n"<<std::endl;
#endif
			//set least distance
			if(curDistance < leastDistance)
			{
				leastDistance = curDistance;
			}

			return;
		}

		//set visited on current position
		visited[cur_pos] = true;

		//decide next pos.
		std::size_t each_idx = 0;
		for(auto each : matrix[cur_pos])
		{
			if(visited[each_idx] == true)
			{
				++each_idx;
				continue;
			}
			
			++visitedNum;
			curDistance += each;
#ifdef DEBUG
			std::cout<<"visitedNum : "<<visitedNum<<"  cur_pos:"<<cur_pos<<std::endl;
			std::cout<<"next pos : "<<each_idx<<" "<<curDistance<<std::endl;
#endif
			search(each_idx);
			
			curDistance -= each;	
			--visitedNum;

			++each_idx;
		}

		//let itself finish the visit
		visited[cur_pos] = false;
	}

public:
	tsp1()
	{
	}

	double calc(void)
	{
		std::cin>>cities;

		std::size_t i = 0, j = 0;

#ifndef DEBUG
		std::cout.setf(std::ios::fixed);
		std::cout.precision(10);
#endif
		//init
		matrix.clear();
		for(i = 0; i < cities; ++i)
		{
			distType dist;
			for(j = 0; j < cities; ++j)
			{
				double distValue;
				std::cin>>distValue;
				dist.push_back(distValue);
			}

			matrix.push_back(std::move(dist));
		}
		visited.assign(cities, false);

		debug_print_map("print all");

	
		//reset
		leastDistance = std::numeric_limits<double>::max();
		//call main
		for(i = 0; i < cities; ++i)
		{
#ifdef DEBUG
			std::cout<<"city["<<i<<"]"<<std::endl;
#endif
			visitedNum = 1;
			curDistance = 0;
			search(i);
		}

		return leastDistance;
	}
};

int main(void)
{
	unsigned int total;
	std::cin>>total;

	int i;
	unsigned int input = 0;
	std::unique_ptr<double[]> result(new double[total]);

	tsp1 bc;
	for(i = 0; i < total; i++)
	{
		result[i] = bc.calc();
	}
	
    for(i = 0; i< total; i++)
	{	
		std::cout<<result[i]<<std::endl;
	}

	return 0;
}

