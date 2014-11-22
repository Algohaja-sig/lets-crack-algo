#include <memory>
#include <iostream>
#include <vector>

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

	class pos
	{
	public:
		pos(int x_, int y_)
		:x(x_), y(y_)
		{
		}

		int x,y;
	};

	class block
	{
	private:
		char type;

	public:
		void setType(const char type_) { type = type_; }
		char getType(void) const { return type; }

		bool operator==(const char rhs)
		{
			return (type == rhs) ? true:false;
		}

		block(const char& type_)
		:type(type_)
		{
				
		}
	};
	std::vector<std::vector<block>> matrix;
	
	std::size_t height, width, blocks, result;

	const char BLACK = '#';
	const char WHITE = '.';
	const pos coverType[4][3] = {
	{{0, 0}, {0, 1}, {1, 1}},
	{{0, 0}, {0, 1}, {-1, 1}},
	{{0, 0}, {1, 0}, {0, 1}},
	{{0, 0}, {1, 0}, {1, 1}}
	};
	const pos temp_block[2] = {{0, 0}, {0, 0}};
	
	bool checkCover(const pos& cur_pos, const pos *rel_pos)
	{
		int i = 1;
		bool found = true;

		for(; i < 3; ++i)
		{
			if(cur_pos.x + rel_pos[i].x < 0 
			|| cur_pos.x + rel_pos[i].x >= width
		    || cur_pos.y + rel_pos[i].y < 0
		    || cur_pos.y + rel_pos[i].y >= height
			|| matrix[cur_pos.x + rel_pos[i].x][cur_pos.y + rel_pos[i].y] == BLACK)
			{
				found = false;		
				break;
			}
		}

		if(found == true)
		{
			matrix[cur_pos.x][cur_pos.y].setType(WHITE);	
			matrix[cur_pos.x + rel_pos[1].x][cur_pos.y + rel_pos[1].y].setType(WHITE);	
			matrix[cur_pos.x + rel_pos[2].x][cur_pos.y + rel_pos[2].y].setType(WHITE);

			return true;
		}

		return false;
	}

	void restoreCover(const pos& cur_pos, const pos *rel_pos)
	{		
		matrix[cur_pos.x + rel_pos[1].x][cur_pos.y + rel_pos[1].y].setType(BLACK);	
		matrix[cur_pos.x + rel_pos[2].x][cur_pos.y + rel_pos[2].y].setType(BLACK);
	}

	//search all.
	bool search(const pos& cur_pos, std::size_t num)
	{
		//basis
		if(num == blocks)
		{
			result++;
			return true;		
		}		

		int i,j,k;
		for(i = 0; i < 4; ++i)
		{
			//check to find block that covers.
			if( checkCover(cur_pos, coverType[i]) == true )
			{
				//FIXME : need better way.
				for(j = 0; j < height; ++j)
				{
					for(k = 0; k < width; ++k)
					{
						if(matrix[j][k].getType() == WHITE)
						{
							//recursive
							pos p(j, k);
							search(p, ++num);
			
							//restore for next try
							--num;
							restoreCover(cur_pos, coverType[i]);
						}
					}
				}
			}
		}
		
		//restore
		matrix[cur_pos.x][cur_pos.y].setType(BLACK);	
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

		std::size_t i = 0, j = 0;
		
		char type;
		std::size_t white_num = 0;
		for(; i < height; ++i)
		{
			for(j = 0; j < width; ++j)
			{

				std::cin>>type; 
				matrix[i][j] = type;
				if(type == WHITE)
				{
					white_num++;
				}
			}
		}

		//exception.
		if(white_num == 0 || white_num % 3 != 0)
		{
			return 0;
		}
	
		//the number of blocks that covers
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
		for(i = 0; i < height; ++i)
		{
			for(j = 0; j < width; ++j)
			{
				if(matrix[i][j].getType() == WHITE)
				{
					pos p(i,j);
					search(p, 0);
				}
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

