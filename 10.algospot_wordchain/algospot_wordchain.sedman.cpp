#include <iostream>
#include <memory>
#include <vector>
#include <array>

#define DEBUG

class wordchain
{
private:
	std::size_t nWord;
	std::vector<std::string> words;
	std::string result;
	typedef std::array<std::array<int, 100>, 100> arr_t;
	arr_t adj;
	std::array<bool, 100> visited;

	void dfs(const int here)
	{
		visited[here] = true;
		std::cout<<"*here : "<<here<<" nWord : "<<nWord<<std::endl;	

		result.append(words[here] + " ");
		
		int to = 0;
		for(; to < words.size(); ++to)
		{
			std::cout<<"+here : "<<here<<" to : "<<to<<" word : "<<words.size()<<std::endl;
			
			if(visited[to] == false && adj[here][to] == 1)
			{
#ifdef DEBUG
				std::cout<<"@here : "<<here<<" to : "<<to<<" word : "<<words[to]<<std::endl;
#endif
				dfs(to);
			}
		}
	}

public:
	std::string calc(void)
	{
		std::cin>>nWord;

		int i = 0;
		std::string input;
		words.clear();
		for(; i < nWord; ++i)
		{
			std::cin>>input;
			words.push_back(std::move(input));
		}
		
		for(auto &item : adj)
		{
			item.fill(0);
		}

		int from = 0, to = 0;
		for(; from < nWord; ++from)
		{
			for(to = 0; to < nWord; ++to)
			{
				if(from != to)
				{
					std::string word1 = words[from];
					std::string word2 = words[to];
					if(word1[word1.length() - 1] == word2[0])
					{
						adj[from][to] = 1;					
					}
				}
			}
		}
		
#ifdef DEBUG
		for(from = 0; from < nWord; ++from)
		{
			for(to = 0; to < nWord; ++to)
			{
				std::cout<<adj[from][to]<<" ";
			}
			std::cout<<"\n";
		}
#endif
		
		visited.fill(false);
		
		bool first = false;
		for(from = 0; from < nWord; ++from)
		{
			if(visited[from] == false)
			{
				if(first == true)
				{
					return std::string("IMPOSSIBLE");
				}

				first = true;
#ifdef DEBUG
				std::cout<<"##word : "<<words[from]<<std::endl;
#endif
				dfs(from);
			}
		}
		
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
		wordchain wc;
		result[i] = wc.calc();
	}

	for(i = 0; i< total; i++)
	{	
		std::cout<<result[i]<<std::endl;
	}

	return 0;
}

