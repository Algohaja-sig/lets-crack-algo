#include <iostream>
#include <memory>
#include <vector>
#include <array>

//#define DEBUG

class wordchain
{
private:
	std::size_t nWord;
	std::vector<std::string> words;
	std::vector<std::string> result;
	//std::string result;
	typedef std::array<std::array<int, 100>, 100> arr_t;
	arr_t adj;
	std::array<bool, 100> visited;

	bool dfs(const int here)
	{
		visited[here] = true;
		//std::cout<<"#here : "<<here<<" word : "<<words[here]<<std::endl;	

		//result.append(words[here] + " ");
		result.push_back(words[here]);

		if(result.size() == nWord)
		{
			return true;
		}

		bool ret = false;
		for(int to = 0; to < words.size(); to++)
		{
			//std::cout<<"+here : "<<here<<" to : "<<to<<" word : "<<words.size()<<std::endl;
			
			if(visited[to] == false && adj[here][to] == 1)
			{
#ifdef DEBUG
				std::cout<<"@here : "<<here<<" to : "<<to<<" word : "<<words[to]<<std::endl;
#endif			
				if( dfs(to) == true)
				{
					return true;
				}
			}
		}
	
		result.pop_back();

		visited[here] = false;

		return false;
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
		
		for(from = 0; from < nWord; ++from)
		{
			if(visited[from] == false)
			{

#ifdef DEBUG
				std::cout<<"##word : "<<words[from]<<std::endl;
#endif
				if(dfs(from) == true)
				{
					break;
				}
			}
		}
		
		if(result.size() == 0)
		{
			return std::string("IMPOSSIBLE");
		}

		std::string ret;
		for(auto item : result)
		{
			ret = ret + item + " "; 
		}

		return ret;
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

