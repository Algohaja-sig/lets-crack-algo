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

	std::size_t height, width;
	std::unique_ptr<char[]> matrix;

public:
	boardcover()
	{
	}

	std::size_t calc(void)
	{
		std::cin>>height;
		std::cin>>width;

		int i = 0, j = 0;

		matrix.reset(new char[width * height]);

		for(; i < height; ++i)
		{
			for(j = 0; j < width; ++j)
			{
				std::cin>>matrix[i * width + j]; 
			}
		}

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


		return 0;
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

