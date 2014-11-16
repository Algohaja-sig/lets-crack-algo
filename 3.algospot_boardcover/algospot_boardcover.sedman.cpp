#include <memory>
#include <iostream>

/** TODO
 */

/* [brief]
 *
 *
 *
 *
 */
//#define DEBUG

class boardcover
{
private:
	boardcover(const boardcover &) = delete;
	boardcover& operator=(const boardcover &) = delete;

	std::size_t height, width, blocks, result;
	std::unique_ptr<char[]> matrix;

	const char black = '#';
	const char white = '.';
	const int coverType[4][3][2] = {
	{{0, 0}, {0, 1}, {1, 1}},
	{{0, 0}, {0, 1}, {-1, 1}},
	{{0, 0}, {0, 1}, {1, 0}},
	{{0, 0}, {1, 0}, {1, 1}}
	};

	bool search(const std::size_t pos , const std::size_t num)
	{ 
		if(num == blocks)
		{
			result++;
			return true;		
		}

		
	}

	bool getBlock(const std::size_t pos)
	{
		return false;
	}

public:
	boardcover()
	:result(0)
	{
	}

	std::size_t calc(void)
	{
		std::cin>>height;
		std::cin>>width;

		int i = 0, j = 0;

		std::size_t area = width * height;
		matrix.reset(new char[area]);
		
		std::size_t white_num = 0;
		for(; i < height; ++i)
		{
			for(j = 0; j < width; ++j)
			{
				std::cin>>matrix[i * width + j]; 

				if(matrix[i * width + j] == white)
				{
					white_num++;
				}
			}
		}

		//exception.
		if(white_num % 3 != 0)
		{
			return 0;
		}
		
		blocks = white_num / 3;

#ifdef DEBUG
		for(i = 0; i < height; ++i)
		{
			for(j = 0; j < width; ++j)
			{
				std::cout<<matrix[i * width + j];
			}

			std::cout<<"\n";
		}
#endif

		//call main	
		std::size_t tmp = area;
		while(tmp--)
		{	
			if(getBlock(tmp) == true)
			{
				search(tmp, 0);
			}
		}

		return result;
	}
};

int main(void)
{
	unsigned int total;
	std::cin>>total;//the number of test case

	int i;
	unsigned int input = 0;
	std::unique_ptr<double[]> result(new double[total]);

	boardcover bc;
	for(i = 0; i < total; i++)
	{
		result[i] = bc.calc();
	}
	
	//std::cout<<"\n result \n";
	
    for(i = 0; i< total; i++)
	{	
		std::cout<<result[i]<<std::endl;
		//std::cout<<std::fixed;
		//std::cout<<std::setprecision(7)<<result[i]<<std::endl;
	}

	return 0;
}

