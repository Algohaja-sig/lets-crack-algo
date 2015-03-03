#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>

/* TODO : 
 */

/* [brief]
 * gallery  
 * https://algospot.com/judge/problem/read/GALLERY
 * performance : adjacency matrix : O(V * E) 131ms 
 *				 adjacency list : O(V + E) 18ms
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

###4
1
19 13
11 9 
13 16 
7 4 
18 0 
10 3 
16 8 
2 9 
3 5 
17 5 
10 2 
10 14 
10 4 
2 13

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

		status dfs(const int here, const bool root)
		{
			visited[here] = true;
#ifdef DEBUG
			std::cout<<">>>here : "<<here<<std::endl;
#endif
			status here_status = status::Unwatched;
			for(int idx = 0; idx < adj[here].size(); ++idx)
			{
				int there = adj[here][idx];
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
#ifdef DEBUG
							std::cout<<"installed "<<here<<"\n";
#endif
							here_status = status::Installed;
							++nInstalled;
						}
						else if(child_ret == status::Installed)
						{
							here_status = status::Watched;	
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

			adj = std::vector<std::vector<int>>(nVertex);

			int i = 0, end1,end2;
			for(i = 0; i < nLink; ++i)
			{
				std::cin>>end1;					
				std::cin>>end2;	

				adj[end1].push_back(end2);
				adj[end2].push_back(end1);
			}

			visited = std::vector<bool>(nVertex, false);
			nInstalled = 0;

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

