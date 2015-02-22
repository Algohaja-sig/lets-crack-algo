#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>

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

/*
Coner cases
### 1
1 
7 6
0 1
1 2
1 3
3 4
3 5
5 6

### 2
1
4 3
0 1
1 2
2 3

### 3
1
13 11
0 1
1 2
2 3
3 4
2 6
6 5
6 7
1 8
9 10 
10 11
11 12
5


*/
//#define DEBUG

class gallery
{
private:
	enum class status {
		Installed,
		Watched,
		Unwatched,
	};

	std::vector<std::vector<int>> adj;
	std::vector<bool> visited;
	std::size_t nInstalled = 0;
	std::vector<int> c;

	void installCamera(const int here)
	{	
#ifdef DEBUG
		std::cout<<"installed "<<here<<"\n";
#endif
		++nInstalled;
		c.push_back(here);
	}

	status dfs(const int here, const bool root)
	{
		visited[here] = true;
#ifdef DEBUG
		std::cout<<">>>here : "<<here<<std::endl;
#endif
		status here_status = status::Unwatched;
		for(int there = 0; there < adj.size(); ++there)
		{
			if(adj[here][there] == 1)
			{
				if(visited[there] == false)				
				{
						status child_ret = dfs(there, false);
	#ifdef DEBUG
						std::cout<<" here : "<<here<<" here_status : "<<static_cast<int>(here_status)<<" child ret : "<<static_cast<int>(child_ret)<<" there : "<<there<<std::endl;
	#endif
						if(here_status != status::Installed)
						{
							if(child_ret == status::Unwatched)
							{
								installCamera(here);
								here_status = status::Installed;
								return here_status; //to let parent know who I am
							}
							else if(child_ret == status::Installed)
							{
								here_status = status::Watched;	
							}
							else//child_ret must be "watched"
							{
								here_status = status::Unwatched;
							}
						}
				}
			}
		}

		if(root == true)
		{
			if(here_status == status::Unwatched)
			{
				++nInstalled;
			}
		}

		return here_status; //to let parent know who I am

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
		nInstalled = 0;


		c.clear();
		for(i = 0; i < nVertex; ++i)
		{
			if(visited[i] == false)
			{
				dfs(i, true);
#ifdef DEBUG 
				std::cout<<"##nInstalled : "<<nInstalled<<std::endl;
#endif
			}
		}
#ifdef DEBUG
		std::for_each(c.begin(), c.end(), [](const int item){std::cout<<item<<" ";});
#endif
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


