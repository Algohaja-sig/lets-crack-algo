#include <memory>
#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

/** TODO
 */

/* [brief]
 * tsp1 
 * https://algospot.com/judge/problem/read/TSP1
 * performance : 
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
				std::cout<<std::setprecision(20)<<xitem<<" ";		
			}

			std::cout<<"\n";
		}
#endif
	}

	std::size_t cities = 0; 
	std::size_t visitedNum = 0; 
	double leastDistance = std::numeric_limits<double>::max();
	double curDistance = -1;
	typedef std::vector<double> distType;
	std::vector<distType> matrix;
	std::vector<bool> visited;

	void search(std::size_t cur_pos)
	{
		//basis
		if(visitedNum == cities - 1)
		{
			//set least distance
			if(curDistance < leastDistance)
			{
				leastDistance = curDistance;
			}

			return;
		}

		std::size_t each_idx = 0;
		visited[cur_pos] = true;
		for(double each : matrix[cur_pos])
		{
			if(cur_pos == each_idx
			|| visited[each_idx] == true)
			{
				++each_idx;
				continue;
			}
			
			++visitedNum;
			curDistance += each;
#ifdef DEBUG
			std::cout<<"cur_pos:"<<cur_pos<<" "<<curDistance<<std::endl;
#endif
			search(each_idx);
			
			curDistance -= each;	
			--visitedNum;

			++each_idx;
		}
		visited[cur_pos] = false;
	}

public:
	tsp1()
	{
	}

	double calc(void)
	{
		std::cin>>cities;
		visitedNum = 0;

		std::size_t i = 0, j = 0;
	
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

		//call main
		for(i = 0; i < cities; ++i)
		{
			visitedNum = 0;
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
		std::cout<<std::fixed<<std::setprecision(10)<<result[i]<<std::endl;
	}

	return 0;
}

