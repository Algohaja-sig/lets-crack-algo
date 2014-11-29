#include <memory>
#include <iostream>
#include <vector>

/** TODO
 */

/* [brief]
 * boardcover 
 * https://algospot.com/user/profile/9001
 * performance : 10ms
 * etc : c++11
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
		
		void print(const std::string debug = "") const
		{
#ifdef DEBUG
			std::cout<<debug<<"[x : "<<x<<" y : "<<y<<"]"<<std::endl;
#endif		
		}

		int x,y;
	};

	std::size_t height, width, blocks, result;
	
	typedef char block;
	typedef std::vector<std::vector<block>> matrix_type;
	matrix_type matrix;
	
	const block BLACK = '#';
	const block WHITE = '.';
	const block COVERED = '@';
    const static int NUM_CANDIDATE_COVER = 4;
	/*
	 4 candidates for each try.
	  _
	 | |_
	 |_ _|
        _
	  _| |
     |___|
      ___
     |  _|
	 |_|
	  ___
	 |_  |
	   |_|
	 */
	const pos coverType[NUM_CANDIDATE_COVER][2] = {
	{/*{0, 0},*/{1, 0}, {1, 1}},
	{/*{0, 0},*/{1, 0}, {1, -1}},
	{/*{0, 0},*/{0, 1}, {1, 0}},
	{/*{0, 0},*/{0, 1}, {1, 1}}
	};
	
	bool checkCover(const pos& cur_pos, const pos *rel_pos)
	{
		for(int i = 0; i < 2; ++i)
		{
#ifdef DEBUG
			std::cout<<"idx "<<cur_pos.x + rel_pos[i].x<<" "<<cur_pos.y + rel_pos[i].y<<" ";
#endif
			if(cur_pos.x + rel_pos[i].x < 0 
			|| cur_pos.x + rel_pos[i].x >= height
		    || cur_pos.y + rel_pos[i].y < 0
		    || cur_pos.y + rel_pos[i].y >= width
			|| matrix[cur_pos.x + rel_pos[i].x][cur_pos.y + rel_pos[i].y] == BLACK
			|| matrix[cur_pos.x + rel_pos[i].x][cur_pos.y + rel_pos[i].y] == COVERED)
			{
				//no found!
				debug_print("no found");
				return false;
			}
		}

		setCover(cur_pos, rel_pos, COVERED);
	
		debug_print_map("covered");
		return true;
	}

	void setCover(const pos& cur_pos, const pos *rel_pos, const block b)
	{		
		matrix[cur_pos.x][cur_pos.y] = b;	
		matrix[cur_pos.x + rel_pos[0].x][cur_pos.y + rel_pos[0].y] = b;	
		matrix[cur_pos.x + rel_pos[1].x][cur_pos.y + rel_pos[1].y] = b;
	}

	/* search all
	 * 1. search white position
	 * 2. try to fit 4 candidate blocks into the position.
	 *	  - see checkCover
	 * 3. if one fits, go for another search(recursive)
	 */
	bool search(std::size_t foundBlocks)
	{
		debug_print("\n+++ new search");
		
		//basis
		if(foundBlocks == blocks)
		{
			result++;
#ifdef DEBUG
			std::cout<<"result : "<<result<<std::endl;
#endif
			return true;		
		}		

		debug_print("search cover");
		int i,j,k;
		bool found = false;
		//TODO : need better way.
		for(j = 0; j < height; ++j)
		{
			for(k = 0; k < width; ++k)
			{
				if(matrix[j][k] == WHITE)
				{
					found = true;
					break;
				}
			}

			if(found == true)
			{
				break;
			}
		}
		
		if( found == false )
		{
			debug_print("not found at all!!");
			return false;
		}

		pos cur_pos(j, k);
		cur_pos.print();

		for(i = 0; i < NUM_CANDIDATE_COVER; ++i)
		{
			//check to find block that covers on cur_pos
			if( checkCover(cur_pos, coverType[i]) == true )
			{
				//recursive
				search(++foundBlocks);

				//restore for next try
				--foundBlocks;
				setCover(cur_pos, coverType[i], WHITE);
				debug_print_map("restore");
			}
		}		
		
		debug_print("--- return\n");
		return false;
	}

	void debug_print_map(const std::string prefix) const
	{
#ifdef DEBUG
		std::cout<<"["<<prefix<<"] \n";
		for(auto yitem : matrix)
		{
			for(auto xitem : yitem)
			{
				std::cout<<xitem;		
			}

			std::cout<<"\n";
		}
#endif
	}

	void debug_print(const std::string str) const
	{
#ifdef DEBUG
		std::cout<<str<<std::endl;
#endif
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
		std::size_t white_foundBlocks = 0;

		result = 0;
		matrix.clear();
		for(i = 0; i < height; ++i)
		{
			std::vector<block> w;
			for(j = 0; j < width; ++j)
			{
				std::cin>>type;
				w.push_back(type);
				if(type == WHITE)
				{
					white_foundBlocks++;
				}
			}

			matrix.push_back(std::move(w));
		}

		//exception.
		if(white_foundBlocks == 0 || white_foundBlocks % 3 != 0)
		{
			return 0;
		}
	
		//the foundBlocksber of blocks that cover
		blocks = white_foundBlocks / 3;

#ifdef DEBUG
		std::cout<<"blocks : "<<blocks<<" white_foundBlocks : "<<white_foundBlocks<<std::endl;
#endif

		//call main	
		search(0);
		return result;
	}
};

int main(void)
{
	unsigned int total;
	std::cin>>total;//the foundBlocksber of test case

	int i;
	unsigned int input = 0;
	std::unique_ptr<double[]> result(new double[total]);

	boardcover bc;
	for(i = 0; i < total; i++)
	{
		result[i] = bc.calc();
	}
	
    for(i = 0; i< total; i++)
	{	
		std::cout<<result[i]<<std::endl;
	}

	return 0;
}

