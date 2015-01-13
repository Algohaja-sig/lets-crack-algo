#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <cstdio>

/* TODO : 
*/

/* [brief]
 * dictionary
 * https://algospot.com/judge/problem/read/DICTIONARY
 * performance : 41ms 
 * etc : c++11
 */

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
				//printf("++1(%c)(%c)\n", (here + 'a'), (to + 'a'));
				if(visited[to] == false)
				{		
					//printf("++2(%c)(%c)\n", (here + 'a'), (to + 'a'));
					dfs(to);		
				}
			}
		}

		order.push_back(here);
		//printf("--(%c)\n", (here + 'a'));
	}

	void makeGraph(const std::vector<std::string> &words)
	{
		for(auto &item : adj)
		{
			item.fill(0);
		}

		int cur = 1,prev = 0;
		for(; cur < words.size(); ++cur)
		{
			prev = cur - 1;	
			int minlength = std::min(words[prev].length(), words[cur].length());

			for(int i = 0; i < minlength; ++i)
			{
				if(words[prev][i] != words[cur][i])
				{
					int from = words[prev][i] - 'a';
					int to = words[cur][i] - 'a';
					adj[to][from] = 1;			
					break;
				}
			}
		}
	}

	void calldfs(void)
	{
		//call dfs
		visited.fill(false);
		order.clear();
		for(int i = 0; i < adj.size(); ++i)
		{
			if(visited[i] == false)
			{
				dfs(i);
			}
		}
	}

	bool findInvalid(void)
	{
		int i = 0, j = 0;
		for(i = 0; i < adj.size(); ++i)
		{
			for(j = i + 1; j < adj.size(); ++j)
			{
				if(adj[order[i]][order[j]])
				{
					return true;
				}
			}
		}

		return false;
	}

public:
	std::string calc(void)
	{
		//prepare input
		int nWord;
		std::cin>>nWord;

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

		makeGraph(words);
		
#ifdef DEBUG
		std::cout<<"\n";
		for(const auto item : adj)
		{
			for(const auto flag : item)
			{
				std::cout<<flag<<" ";
			}
			std::cout<<"\n";
		}
#endif	
		
		calldfs();	
		
		if(findInvalid() == true)
		{
			return std::string("INVALID HYPOTHESIS");
		}

		//make one string
		std::string result;
		std::for_each(order.begin(), order.end(), [&result](const int data) 
		{
			char ch = static_cast<char>(data + 'a');
			result.push_back(ch);
		});

		return result;
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


