#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <cstdio>

class dictionary
{
private:	
	typedef std::array<std::array<int, 26>, 26> alpha_t;
	alpha_t adj;

	std::array<bool, 26> visited;
	std::vector<int> order;

	void dfs(int here)
	{
		visited[here] = true;

		//printf("++(%c)\n", (here + 'a'));
		for(int to = 0; to < 26; ++to)
		{
			if(adj[here][to] == 1)
			{
				if(visited[to] == false)
				{		
					dfs(to);		
				}
			}
		}

		order.push_back(here);
		printf("--(%c)\n", (here + 'a'));
	}

public:
	std::string calc(void)
	{
		int nWord;
		std::cin>>nWord;

		for(auto &item : adj)
		{
			item.fill(0);
		}

		std::vector<std::string> words;
		int maxlength = 0;
		int i = 0;
		for(i = 0; i < nWord; ++i)
		{
			std::string input;
			std::cin>>input;
			
			if(input.length() > maxlength)
			{
				maxlength = input.length();
			}

			words.push_back(std::move(input));
				
		}

/*
		std::cout<<"\n\nmax len : "<<maxlength<<"\n";

		std::for_each(words.begin(), words.end(), [](const std::string &str) 
		{
			std::cout<<str<<" ";
		});
*/
		//make graph
		int cur = 1,prev = 0;
		for(; cur < nWord; ++cur)
		{
			prev = cur - 1;	
			int minlength = std::min(words[prev].length(), words[cur].length());

			for(int i = 0; i < minlength; ++i)
			{
				if(words[prev][i] != words[cur][i])
				{
					int from = words[prev][i] - 'a';
					int to = words[cur][i] - 'a';
					adj[from][to] = 1;			
					break;
				}
			}
		}
/*
		std::cout<<"\n";
		for(const auto item : adj)
		{
			for(const auto flag : item)
			{
				std::cout<<flag<<" ";
			}
			std::cout<<"\n";
		}
*/
		//
		visited.fill(false);
		order.clear();
		int j = 0;
		for(i = 0; i < adj.size(); ++i)
		{
			//for(; j < adj.size(); ++j)
			{
				//if(adj[i][j] == 1 && 
				if(visited[i] == false)
				{
					dfs(i);
				}
			}

			std::cout<<"**";
		}
	
		std::reverse(order.begin(), order.end());

		//
		for(i = 0; i < adj.size(); ++i)
		{
			for(j = i + 1; j < adj.size(); ++j)
			{
				if(adj[order[j]][order[i]])
				{
					return std::string("INVALID HYPOTHESIS");
				}
			}
		}

		return std::string("");
	}
};

int main(void)
{
	unsigned int total;
	std::cin>>total;

	int i;
	unsigned int input = 0;
	std::unique_ptr<std::string[]> result(new std::string[total]);

	for(i = 0; i < total; i++)
	{
		dictionary dic;
		result[i] = dic.calc();
	}

    for(i = 0; i< total; i++)
	{	
		std::cout<<result[i]<<std::endl;
	}

	return 0;
}


