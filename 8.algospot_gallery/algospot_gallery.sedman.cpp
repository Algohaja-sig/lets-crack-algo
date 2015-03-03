#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>

//#define RANDOM_TEST

#ifdef RANDOM_TEST
#include <random>
#endif


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

fail case
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

#ifdef RANDOM_TEST
int getRandom(const int from, const int to)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(from, to);

	return dis(gen);
}
#endif

class gallery
{
private:
	enum status {
		Installed,
		Watched,
		Unwatched,
	};

	std::vector<std::vector<int>> adj;
	std::vector<bool> visited;
	std::size_t nInstalled = 0;
	std::size_t nInstalled2 = 0;
	
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

	int dfs_textbook(const int here)
	{
		visited[here] = true;

		std::array<int, 3> children = {0, 0, 0};

		for(int i = 0; i < adj[here].size(); ++i)
		{
			int there = i;//adj[here][i];

			if(adj[here][i] == 1 && visited[there] == false)
			{
				++children[dfs_textbook(there)];
			}
		}

		if(children[status::Unwatched])
		{
			++nInstalled2;
			return status::Installed;
		}

		if(children[status::Installed])
		{
			return status::Watched;
		}

		return status::Unwatched;
	}

public:
	gallery()
	{
	}

	int calc(void)
	{
		int nVertex;
		int nLink;
		
#ifdef RANDOM_TEST
		nVertex = getRandom(1, 20);
		nLink = getRandom(0, nVertex - 1);

		std::cout<<"vextex :"<<nVertex<<std::endl;
		std::cout<<"link : "<<nLink<<std::endl;
#else
		std::cin>>nVertex;
		std::cin>>nLink;
#endif
		int i = 0, end1 = -1,end2 = -1;
		for(i = 0; i < nVertex; ++i)
		{
			adj.push_back(std::vector<int>(nVertex, 0));
		}

		std::vector<std::vector<int>> ends;
		for(i = 0; i < nLink; ++i)
		{
#ifdef RANDOM_TEST
			end1 = getRandom(0, nVertex - 1);
			do
			{
				end2 = getRandom(0, nVertex - 1);
			}
			while(end1 == end2);

			std::vector<int> pair = {end1, end2};
			ends.push_back(pair);
			//std::cout<<end1<<std::endl;
			//std::cout<<end2<<std::endl;
#else
			std::cin>>end1;					
			std::cin>>end2;	
#endif
			adj[end1][end2] = 1;
			adj[end2][end1] = 1;
		}

		//mine
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
		
#ifdef RANDOM_TEST
		//from textbook
		visited = std::vector<bool>(nVertex, false);
		nInstalled2 = 0;
		for(int u = 0; u < nVertex; ++u)
		{
			if(visited[u] == false
			&& dfs_textbook(u) == status::Unwatched)
			{
				++nInstalled2;
			}
		}
	
		std::cout<<"#1 : "<<nInstalled<<" #2 :"<<nInstalled2<<std::endl;
		if(nInstalled != nInstalled2)
		{
			for(auto cols : ends)
			{
				for(int item : cols)
				{	
					std::cout<<item<<" ";
				}
				std::cout<<"\n";
			}

			return 0;
		}

		return 1;
#else
		return nInstalled;
#endif
	}
};

int main(void)
{
	unsigned int total = 5;
#ifndef RANDOM_TEST
	std::cin>>total;
#endif
	int i;
	unsigned int input = 0;
	std::unique_ptr<int[]> result(new int[total]);

	for(i = 0; i < total; i++)
	{
		gallery g;
		result[i] = g.calc();
	}

	std::cout<<"result\n";
    for(i = 0; i< total; i++)
	{	
		std::cout<<result[i]<<std::endl;
	}

	return 0;
}


