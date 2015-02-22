#include <vector>
#include <queue>
#include <iostream>

std::vector<std::vector<int>> adj;

std::vector<int> bfs(const int start)
{
	std::vector<bool> discovered(adj.size(), false);

	std::queue<int> q;

	std::vector<int> order;

	discovered[start] = true;

	q.push(start);

	while(q.empty() == false)
	{
		int here = q.front();
		q.pop();

		order.push_back(here);

		for(int i = 0; i < adj[here].size(); ++i)
		{
			int there = i;

			if(adj[here][there] == 1 
			&& discovered[there] == false)
			{
				q.push(there);
				discovered[there] = true;
			}
		}
	}

	return order;
}

int main(void)
{
	//prepare
	int nVertex;
	std::cin>>nVertex;

	int i = 0;
	for(; i < nVertex; ++i)
	{
		adj.push_back(std::vector<int>(nVertex, 0));			
	}

	//set adjacency
	int nAdj;
	std::cin>>nAdj;
	int v1, v2;
	for(i = 0; i < nAdj; ++i)
	{
		std::cin>>v1;
		std::cin>>v2;

		if(v1 >= nVertex || v2 >= nVertex)
		{
			return -1;
		}

		//because this is an undirected graph
		adj[v1][v2] = 1;
		adj[v2][v1] = 1;
	}

	for(const auto grp : adj)
	{
		for(const auto item : grp)
		{
			std::cout<<item<<" ";
		}

		std::cout<<"\n";
	}

	std::cout<<"result\n";
	for(const auto item : bfs(0))
	{
		std::cout<<item<<" ";
	}

	std::cout<<"\n";

	return 0;
}

