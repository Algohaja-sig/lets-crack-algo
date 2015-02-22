#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

std::vector<std::vector<int>> adj;

void bfs2(const int start, std::vector<int> &distance, std::vector<int>& parent)
{
	distance = std::vector<int>(adj.size(), -1);
	parent = std::vector<int>(adj.size(), -1);

	std::queue<int> q;

	distance[start] = 0;
	parent[start] = start;//it's a root
	q.push(start);

	while(q.empty() == false)
	{
		int here = q.front();
		q.pop();

		//adjacency
		for(int i = 0; i< adj[here].size(); ++i)
		{
			int there = i;//FIXME : because adj is adjacency matrix

			if(adj[here][there] == 1
			&& distance[there] == -1)
			{
				q.push(there);
				distance[there] = distance[here] + 1;
				parent[there] = here;

				std::cout<<"here : "<<here<<" there : "<<there<<" distance : "<<distance[there]<<" parent : "<<parent[there]<<std::endl;
			}
		}
	}
}

std::vector<int> shortestPath(int v, const std::vector<int> &parent)
{
	std::vector<int> path(1, v);

	while(parent[v] != v)
	{
		v = parent[v];
		path.push_back(v);
	}

	std::reverse(path.begin(), path.end());
	return path;
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

	std::vector<int> distance;
	std::vector<int> parent;

	bfs2(0, distance, parent);

	int v;
	std::cin>>v;

	std::cout<<"result\n";
	for(const auto item : shortestPath(v, parent))
	{
		std::cout<<item<<" ";
	}

	std::cout<<"\n";

	return 0;
}

