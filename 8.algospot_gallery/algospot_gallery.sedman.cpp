#include <memory>
#include <iostream>
#include <vector>

/* TODO : 
*/

/* [brief]
 * gallery  
 * https://algospot.com/judge/problem/read/GALLERY
 * performance : timeout (1000ms)
 * etc : c++11
 */

/*
3 Status of vertex
1. subtree returns Un-Watched.
2. subtree returns Watched.
3. subtree returns Leaf.
*/

class gallery
{
private:
	enum class status {
		Installed,
		Watched,
		Leaf
	};

	std::vector<std::vector<int>> adj;
	std::vector<bool> visited;
	std::size_t nInstalled = 0;
	std::vector<bool> installed;

	status dfs(const int here)
	{
		visited[here] = true;

		status child_ret = status::Leaf;
		status result = child_ret;
		for(int there = 0; there < adj.size(); ++there)
		{
			if(visited[there] == false)//here is not a leaf
			{
				status child_ret = dfs(there);

				if((child_ret == status::Leaf || child_ret == status::Watched)
				&& installed[here] == false)
				{
					++nInstalled;
					installed[here] = true;
					
					result = status::Installed;
				}
				else
				{
					if(child_ret == status::Installed
					&& result != status::Installed)
					{
						result = status::Watched;		
					}
				}
			}
		}

		return result; //to let parent know who I am

	}

public:
	gallery()
	{
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
			adj.push_back(std::vector<int>(nVertex, 0));
		}

		for(i = 0; i < nLink; ++i)
		{
			std::cin>>end1;					
			std::cin>>end2;	

			adj[end1][end2] = 1;
			adj[end2][end1] = 1;
		}

		visited = std::vector<bool>(nVertex, false);
		installed = std::vector<bool>(nVertex, false);
		nInstalled = 0;

		for(i = 0; i < nVertex; ++i)
		{
			if(visited[i] == false)
			{
				dfs(i);
			}
		}


		return nInstalled;
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


