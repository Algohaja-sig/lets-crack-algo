#include <memory>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <limits>

/* TODO : 
*/

/* [brief]
 * gallery  
 * https://algospot.com/judge/problem/read/GALLERY
 * performance : timeout (1000ms)
 * etc : c++11
 */

class gallery
{
private:
	class data
	{
	public:
		bool visited = false; 
		std::list<int> adjacent;
	};

	std::vector<data> vertexs;

public:
	gallery()
	{
		vertexs.clear();
	}

	int calc(void)
	{
		int nVertex;
		int nLink;
		
		std::cin>>nVertex;
		std::cin>>nLink;

		int i = 0, end1,end2;
		for(i = 0; i < nVertex; ++i)
		{
			data tmp;
			vertexs.push_back(tmp);
		}

		for(i = 0; i < nLink; ++i)
		{
			std::cin>>end1;					
			std::cin>>end2;	

			vertexs[end1].adjacent.push_back(end2);
			vertexs[end2].adjacent.push_back(end1);
		}

		int minLinks = std::numeric_limits<int>::max();
		int result = 0;
		int j = 0;
		for(i = 0; i < vertexs.size(); ++i)
		{
			result = 0;
				
			std::for_each(vertexs.begin(), vertexs.end(), [](data &arg) { arg.visited = false; });

			for(j = 0; j < vertexs.size(); ++j)
			{
				int idx = (i +j) % (vertexs.size());	
				auto v = vertexs[idx];
				if(v.visited == false)
				{
					v.visited = true;
					for(auto idx : v.adjacent)
					{
						vertexs[idx].visited = true;
					}

					++result;
				}
			}

			if(minLinks > result)
			{
				minLinks = result;
			}
		}

		return minLinks;
	}
};

int main(void)
{
	unsigned int total;
	std::cin>>total;

	int i;
	unsigned int input = 0;
	std::unique_ptr<int[]> result(new int[total]);

	for(i = 0; i < total; i++)
	{
		gallery g;
		result[i] = g.calc();
	}

    for(i = 0; i< total; i++)
	{	
		std::cout<<result[i]<<std::endl;
	}

	return 0;
}


