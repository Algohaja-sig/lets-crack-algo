#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <algorithm>

//mostly from textbook

#define DEBUG

class wordchain
{
private:
	std::size_t nWord;
	std::vector<std::string> words;
	std::string result;

	static const int nAlpha = 26;
	std::array<std::array<std::vector<std::string>, nAlpha>, nAlpha> graph;
	std::array<std::array<int, nAlpha>, nAlpha> adj;
	std::array<int, nAlpha> indegree;
	std::array<int, nAlpha> outdegree;

	void getCircuit(int here, std::vector<int>& circuit)
	{
		for(int there = 0; there < adj.size(); ++there)
		{
			while(adj[here][there] > 0)
			{
#ifdef DEBUG
				std::cout<<"here : "<<static_cast<char>(here + 'a')<<" there : "<<static_cast<char>(there + 'a')<<std::endl;
#endif
				--adj[here][there];
				getCircuit(there, circuit);

			}
		}

		circuit.push_back(here);
	}

	std::vector<int> getTrailOrCircuit(void)
	{
		std::vector<int> circuit;

		int i = 0;
		//first, check trail.
		for(; i < indegree.size(); ++i)
		{
			if(outdegree[i] == indegree[i] + 1)
			{
				getCircuit(i, circuit);
				return circuit;
			}
		}

		//last check circuit
		for(i = 0; i < indegree.size(); ++i)
		{
			if(outdegree[i])
			{
				getCircuit(i, circuit);
				return circuit;
			}
		}

		return circuit;
	}

	bool checkEuler(void)
	{
		int plus1 = 0, minus1 = 0;
		for(int i = 0; i < nAlpha; ++i)
		{
			int delta = outdegree[i] - indegree[i];

			if(delta < -1 || 1 < delta) return false;

			if(delta == 1) plus1++;
			if(delta == -1) minus1++;
		}

		return (plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0);
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

		if(nWord == 1)
		{
			return words[0];
		}
		
		int idx = 0;
		indegree.fill(0);
		outdegree.fill(0);

		for(auto &grp : adj)
		{
			grp.fill(0);
		}

		for(; idx < nWord; ++idx)
		{
			char from = words[idx][0] - 'a';
			char to = words[idx][words[idx].length() - 1] - 'a';
#ifdef DEBUG	
			std::cout<<"from : "<<words[idx][0]<<" to : "<<words[idx][words[idx].length() - 1]<<" word1 : "<<words[idx]<<std::endl;
#endif
			graph[from][to].push_back(words[idx]);			

			adj[from][to]++;
			outdegree[from]++;
			indegree[to]++;
		}

		//check circuit or trail
		if(checkEuler() == false)
		{
			return std::string("IMPOSSIBLE");
		}

#ifdef DEBUG
		for(const auto grp : adj)
		{
			for(const auto item : grp)
			{
				std::cout<<item<<" ";
			}
			std::cout<<"\n";
		}
#endif
		
		result.clear();
		auto ret = getTrailOrCircuit();

		//if not equal, this means there is a seperate one.
		if(ret.size() != words.size() + 1)
		{
			return std::string("IMPOSSIBLE");
		}

		std::reverse(ret.begin(), ret.end());
	
		//auto successCnt = nWord;
		for(idx = 1; idx < ret.size(); ++idx)
		{
			char first = static_cast<char>(ret[idx - 1]);	
			char second = static_cast<char>(ret[idx]);
		
			result.append(graph[first][second].back() + " ");
			graph[first][second].pop_back();

			//--successCnt;
		}

		//if(successCnt > 0)
		//{
		//	return std::string("IMPOSSIBLE");
		//}

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

