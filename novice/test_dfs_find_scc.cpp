#include <stack>
#include <vector>
#include <iostream>

std::vector<std::vector<int>> adj;

std::vector<int> sccId, discovered, finished;

std::stack<int> st;

int sccGroup, vertexCounter;

/*
the reason why checking if finished is not 1 (&& finished[there] != 1)
see e.g.
0 -----> 1 -----> 2
		   -----> 3 -----> 2

2 is finished first, then when going to 3, 
3 checks 2 if direction is reverse and 2 is not finished.
Since  2 is already finished, it just goes out of interation then make 3 a scc root.
*/


int scc(int here)
{
	std::cout<<"here : "<<here<<"\n";
	//record visit order
	int ret = discovered[here] = vertexCounter++;

	st.push(here);

	for(int there = 0; there < adj[here].size(); ++there)
	{
		
		if(adj[here][there] == 1)
		{
			std::cout<<"there : "<<there<<" discovered : "<<discovered[there]<<"\n";
			if(discovered[there] == -1)
			{
				ret = std::min(ret, scc(there));
			}
			//reverse direction && it's not finished
			else if(discovered[there] < discovered[here] 
			&& finished[there] != 1)
			{
				ret = std::min(ret, discovered[there]);
			}
		}
	}

	std::cout<<"min : "<<ret<<"\n";

	//is this scc root?
	if(ret == discovered[here])
	{
		std::cout<<"##scc root: "<<here<<"\n";

		//here is scc root, get vertex in the same scc
		while(true)
		{
			int t = st.top();
			st.pop();
			sccId[t] = sccGroup;
		
			std::cout<<"t: "<<t<<" scc group : "<<sccGroup<<"\n";
			if(t == here)
			{
				break;
			}

		}
		++sccGroup;
	}

	finished[here] = 1;

	return ret;
}

std::vector<int> tajanSCC(void)
{
	sccId = discovered = finished = std::vector<int>(adj.size(), -1);
	sccGroup = vertexCounter = 0;

	for(int i = 0; i < adj.size(); ++i)
	{
		if(discovered[i] == -1)
		{
			std::cout<<"start!\n";
			scc(i);
		}
	}

	return sccId;
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

		//because this is a directed graph
		adj[v1][v2] = 1;
	}

	for(const auto grp : adj)
	{
		for(const auto item : grp)
		{
			std::cout<<item<<" ";
		}

		std::cout<<"\n";
	}

	for(const auto item : tajanSCC())
	{
		std::cout<<item<<" ";
	}

	std::cout<<"\n";

	return 0;
}

