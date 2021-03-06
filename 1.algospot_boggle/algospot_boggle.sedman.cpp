#include <iostream>
//#include <unordered_map>
//#include <map>
#include <vector>
#include <memory>
#include <array>
#include <algorithm>

//g++ -o algo_boggle algo_boggle.cpp -std=c++11

class boggle
{
public:
	//typedef std::unique_ptr<std::string> str_type;
	typedef std::string str_type;
	//typedef std::unordered_map<str_type, str_type> hash_map; 
	//typedef std::map<str_type, str_type> hash_map; 
	//typedef sequencial_map<str_type, str_type> hash_map; 

	//hash_map calc(void)
	std::vector<std::string> calc(void)
	//void calc(void)
	{
		//get ready
		int i,j;
		
		for(i = 0; i < nBlocks; ++i)
		{
			for(j = 0; j < nBlocks; ++j)
			{
				std::cin>>blocks[i][j];	
			}
		}

		//iterate over finding_str to get matched.
		int n;
		std::cin>>n;
		std::string str;
		while(n >= 1)
		{
			std::cin>>str;
			if(run(str) == true)
			{
				//std::cout<<"TRUE"<<std::endl;
				//map.insert(std::make_pair(std::move(str), std::move(std::string("YES"))));
				result.push_back(str + " YES");
			}
			else
			{
				//map.insert(std::make_pair(std::move(str), std::move(std::string("NO"))));
				//std::cout<<"FALSE"<<std::endl;
				result.push_back(str + " NO");
			}
			//std::cout<<"-----------------------\n";
			--n;
		}

		return std::move(result);
	}

protected:
	static const std::size_t nBlocks = 5;
	char blocks[nBlocks][nBlocks];
	//hash_map map;	
	std::string matched_str;

	char getBlock(const int cur_pos) const
	{
		return blocks[cur_pos / nBlocks][cur_pos % nBlocks];
	}

private:
	std::vector<std::string> result;
	
	bool run(const std::string &given_str)
	{
		int cur_pos = 0; 
		char temp_char;
		bool found = false;
		for(auto byte_char : given_str)
		{
			for(cur_pos = 0; cur_pos < nBlocks*nBlocks; ++cur_pos)
			{
				if(getBlock(cur_pos) == byte_char)
				{
					found = true;
				}
			}

			if(found == false)
			{
				return false;
			}

			found = false;
		}

		for(cur_pos = 0; cur_pos < nBlocks*nBlocks; ++cur_pos)
		{
			matched_str.clear();
			if(getBlock(cur_pos) == given_str[0])
			{
				if(given_str.length() == 1)
				{
					return true;
				}
		
				//init 
				matched_str.push_back(given_str[0]);

				if(searchWord(given_str, cur_pos, matched_str) == true)
				{
					return true;
				}
			}
		}

		return false;
	}
	
	bool getMatchedChar(const int pos, const char next_char) const
	{
		return (getBlock(pos) == next_char) ? true : false;
	}

	std::array<int, 8> getNextWord(const int cur_pos, const char next_char)
	{
		std::array<int, 8> adjacent {-1, -1, -1, -1, -1, -1, -1, -1}; 
		
		//std::cerr<<"cur_pos : "<<cur_pos<<" next_char : "<<next_char<<std::endl;
		
		int matched_pos;
		int idx = 0;
		//cur_pos - 6
		if(cur_pos % nBlocks != 0 || cur_pos > nBlocks)
		{
			matched_pos = cur_pos - nBlocks - 1;
			if(getMatchedChar(matched_pos, next_char))
			{
				adjacent[idx++] = matched_pos;
			}
		}
		//cur_pos - 5
		if(cur_pos >= nBlocks)
		{
			matched_pos = cur_pos - nBlocks;
			if(getMatchedChar(matched_pos, next_char))
			{
				adjacent[idx++] = matched_pos;
			}
		}
		//cur_pos - 4 
		if((cur_pos % nBlocks != nBlocks - 1) || (cur_pos > nBlocks))
		{
			matched_pos = cur_pos - nBlocks + 1;
			if(getMatchedChar(matched_pos, next_char))
			{
				adjacent[idx++] = matched_pos;
			}

		}
		//cur_pos + 1
		if(cur_pos % nBlocks != nBlocks - 1)
		{
			matched_pos = cur_pos + 1;
			if(getMatchedChar(matched_pos, next_char))
			{
				adjacent[idx++] = matched_pos;
			}
		}
		//cur_pos + 6
		if((cur_pos % nBlocks != nBlocks - 1) || (cur_pos / nBlocks < nBlocks - 1))
		{
			matched_pos = cur_pos + nBlocks + 1;
			if(getMatchedChar(matched_pos, next_char))
			{
				adjacent[idx++] = matched_pos;
			}
		}
		//cur_pos + 5
		if(cur_pos / nBlocks < nBlocks - 1)
		{
			matched_pos = cur_pos + nBlocks;
			if(getMatchedChar(matched_pos, next_char))
			{
				adjacent[idx++] = matched_pos;
			}
		}
		//cur_pos + 4
		if((cur_pos % nBlocks != 0) || (cur_pos / nBlocks < nBlocks - 1))
		{
			//std::cout<<"inside\n";
			matched_pos = cur_pos + nBlocks - 1;
			if(getMatchedChar(matched_pos, next_char))
			{
				adjacent[idx++] = matched_pos;
			}
		}
		//cur_pos - 1
		if(cur_pos % nBlocks != 0)
		{
			matched_pos = cur_pos - 1;
			if(getMatchedChar(matched_pos, next_char))
			{
				adjacent[idx++] = matched_pos;
			}
		}

		return std::move(adjacent);
	}

	virtual bool searchWord(const std::string &given_str
	, const int cur_pos_on_blocks
	, std::string &matched_str)
	{
		//basis
		if(given_str.size() == matched_str.size())
		{
			return true;	
		}
		
		//std::cout<<"matched str size : "<<matched_str.size()<<std::endl;
		//get next char
		char next_char = given_str[matched_str.size()];
		
		//search next matched blocks.
		for(auto found_idx : getNextWord(cur_pos_on_blocks, next_char))
		{
			if(found_idx == -1)
			{
				//std::cerr<<"no found"<<std::endl;
				continue;
			}

			matched_str.push_back(getBlock(found_idx));
			
			if(searchWord(given_str, found_idx, matched_str) == true)
			{
				return true;
			}

			matched_str.pop_back();
		}
		
		return false;
	}
};


/* BUG (FIXME)
 * it can't check boundary.
 * e.g.) if current position is 20 then checks  
 * current position + (1*5 + -1*1) results in 24 which crosses boundary.
 */
class boggleTextbook : public boggle
{
private:
	const int dx[8] = { -1, -1, -1,  1, 1, 1,  0, 0 };
	const int dy[8] = { -1,  0,  1, -1, 0, 1, -1, 1 };//*5

	bool inRange(const int pos)
	{
		return (pos <= 24) ? true : false;
	}

	//role as adapter
	bool searchWord(const std::string &given_str
	, const int cur_pos
	, std::string &not_used)
	{
		std::string word = given_str;//const_cast<std::string>(given_str);
		//word = word.substr(1);
		
		std::cout<<"\n word : "<<word<<std::endl;

		for(int direction = 0; direction < 8; ++direction)
		{
			int next_pos = cur_pos + dy[direction] * 5 + dx[direction];
			std::string nextword = word.substr(1);
			if(hasWord(next_pos, nextword) == true)
			{
				return true;
			}
		}
	}

	bool hasWord(const int cur_pos
	, std::string &word)
	{
		//std::cout<<"cur_pos : "<<cur_pos<<std::endl;
		if(inRange(cur_pos) == false)
		{
			return false;
		}

		if(getBlock(cur_pos) != word[0])
		{
			return false;
		}

		if(word.length() == 1)
		{
			std::cout<<"hit!! pos : "<<cur_pos<<std::endl;
			return true;
		}

		for(int direction = 0; direction < 8; ++direction)
		{
			int next_pos = cur_pos + dy[direction] * 5 + dx[direction];

			std::string nextword = word.substr(1);
			if(hasWord(next_pos, nextword) == true)
			{
				std::cout<<"pos : "<<cur_pos<<std::endl;
				return true;
			}
		}

		return false;
	}
};

int main(void)
{
	unsigned int total;
	std::cin>>total;//the number of test case

	int i;
	unsigned int input = 0;
	//std::unique_ptr<boggle::hash_map[]> result(new boggle::hash_map[total]);
	std::unique_ptr<std::vector<std::string>[]> result(new std::vector<std::string>[total]);
	
	std::unique_ptr<boggle> bog(new boggle);
	for(i = 0; i < total; i++)
	{
		result[i] = bog->calc();
	}
	
	//std::cout<<"\n result \n";
	
    for(i = 0; i< total; i++)
	{
		//std::for_each(result[i].begin(), result[i].end(), [](const boggle::hash_map::value_type& item) 
		//{ std::cout<<item.first<<" "<<item.second<<std::endl; });
		std::for_each(result[i].begin(), result[i].end(), [](const std::string &item)
		{ std::cout<<item<<std::endl; });
	}

	return 0;
}	

