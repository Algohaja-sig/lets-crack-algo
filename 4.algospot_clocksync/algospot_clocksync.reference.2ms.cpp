#include <stdio.h>
#include <memory.h>
#include <iostream>

int clocks [16];

/* This array represents different meaning according to its order.
 * odd  : looks like it represents each index of 16 clocks. But the order is not clear to understand.
 * even : not sure what this is. 
 */
const int s[20] = {8,4, 6,3, 10,2, 11,1, 7,7, 9,9, 4,8, 1,0, 0,5, 3,6};

const char switches [160] = {
	//---------------------width---------------------//|
	1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //|
	0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0,  //|
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1,  //|
	1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,  //|
	0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0,  //|height
	1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,  //|
	0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,  //|
	0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1,  //|
	0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //|
	0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}; //|

int tune (int buttonIdx_x_2)
{
	//access to s[2 * buttonIdx + 1]
	//height : looks like the height of switches array.
	int height = s [buttonIdx_x_2 + 1] * 16;

	//what the hell is this???
	//t must be within 0,1,2,3
	int t = (4 - clocks [ s[buttonIdx_x_2] ] & 3) & 3;

	//looks like clock is updated according to ???
	for (int width = 0; width < 16; ++width) 
	{
		//switches[height + width] : 0 or 1  
		//t : 0,1,2,3
		clocks [width] += switches [height + width] * t;
	}

	return t;
}

int main ()
{
	int t, n = 0;					
	scanf ("%d", &t);
	while (t --) {
		
		//prepare
		memset (clocks, 0, 16 * sizeof(int));

		for (int z = 0; z < 16; z++) 
		{
			scanf ("%d", &n);	
			clocks [z] = n / 3; // 3,6,9,12 -> 1,2,3,4
		}

		//call tune per each button
		n = 0;
		for (int buttonIdx = 0; buttonIdx < 10; ++buttonIdx) 
			n += tune ( buttonIdx * 2 );

		//result
		for (int z = 0; z < 16; z++) 
		{
			if (clocks [z] % 4 > 0)//doesn't point to 12. so fail to find.
			{
				n = -1;		
				break;
			}

		}	
		
		printf ("%d\n", n);
	}
	return 0;
}
