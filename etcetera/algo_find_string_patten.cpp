#include <iostream>

/* 
 * abcabc : good!
 * abcdabc : no good!
 * aa : good
 * ab : no good
 * abssz : good
 * abcfdsa : no good
 */


bool check_in_substring(const std::size_t cur_idx, const std::size_t match_idx, const std::string& data)
{
	if(cur_idx - 1 == match_idx)
	{
		return (data[cur_idx] == data[match_idx]) ? true : false;
	}

	//substring_length = cur_idx - match_idx
	//the index of matched string from cur_idx  = cur_idx + substring_length - 1
	if( 2*cur_idx - match_idx > data.size())
	{
		return false;
	}

	for(std::size_t offset = 0; offset < (cur_idx - match_idx); ++offset)
	{
		if(data[cur_idx + offset] != data[match_idx + offset])
		{
			return false;
		}
	}

	return true;
}

bool check_validity(const std::string& data)
{
	if(data.size() == 1)
	{
		return false;
	}

	if(data.size() == 2)
	{
		return (data[0] == data[1]) ? true : false;
	}

	std::size_t cur_idx = 0;
	std::string queue;
	queue.push_back(data[cur_idx]);
	
	for(std::size_t cur_idx = 1; cur_idx < data.size(); ++cur_idx)
	{
		std::size_t match_idx = 0;
		for(auto s : queue)
		{
			if(s == data[cur_idx]
			&& check_in_substring(cur_idx, match_idx, data) == true)
			{
				//std::cout<<"cur_idx "<<cur_idx<<"- match_idx "<<match_idx<<std::endl;
				return true;	
			}

			++match_idx;
		}

		if(cur_idx == data.size() - 1)
		{
			break;
		}
		
		queue.push_back(data[cur_idx]);
	}

	return false;
}

int main(void)
{
	while(true)
	{
		std::string data;
		std::cin>>data;

		if(check_validity(data) == true)
		{
			std::cout<<"same pattern exists\n";			
		}
		else
		{
			std::cout<<"no exists\n";			
		}
	}
}
