#include <vector>
#include <iostream>

std::vector<std::vector<int>> adj;
std::vector<int> discovered;
int counter;
std::vector<bool> isCutVertex;

int findCutVertex(int here, bool isRoot)
{
	//record visit order
	discovered[here] = counter++;

	int ret = discovered[here];

	std::cout<<"##visit here : "<<here<<" order : "<<ret<<"\n";
	
	int children = 0;

	for(int there= 0; there < adj[here].size(); ++there)
	{
		std::cout<<"there "<<there<<" discovered order: "<<discovered[there]<<"\n";
		
		if(adj[here][there] == 1)
		{
			if(discovered[there] == -1)// no visit
			{
				++children;

				std::cout<<"**child there : "<<there<<" children : "<<children<<"\n";
				int subtree = findCutVertex(there, false);

				if(isRoot == false && subtree >= discovered[here])
				{
					std::cout<<"$$$cutVertex is "<<here<<"\n";
					isCutVertex[here] = true;
				}

				ret = std::min(ret, subtree);
			}
			else// already visit
			{
				ret = std::min(ret, discovered[there]);
			}
		}
	}

	if(isRoot == true)
	{
		isCutVertex[here] = (children >= 2);
	}
	
	std::cout<<"return : "<<ret<<"\n";

	return ret;
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

	discovered = std::vector<int>(nVertex, -1);
	isCutVertex = std::vector<bool>(nVertex, false);

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
	//find cut vertex
	findCutVertex(0, true);
	
	return 0;
}
