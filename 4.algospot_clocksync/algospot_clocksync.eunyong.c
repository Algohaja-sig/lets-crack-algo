#include <stdio.h>

#define CLOCKS_NUM 16
#define BUTTON_NUM 10
//#define DEBUG 1

int clock[32][CLOCKS_NUM];
int cur_clock[CLOCKS_NUM];
int button[10][6]={
	{3,0,1,2,0,0},
	{4,3,7,9,11,0},
	{4,4,10,14,15,0},
	{5,0,4,5,6,7},
	{5,6,7,8,10,12},
	{4,0,2,14,15,0},
	{3,3,14,15,0,0},
	{5,4,5,7,14,15},
	{5,1,2,3,4,5},
	{5,3,4,5,9,13}
};

int pressed_button[10];

int END = 0;
int CUR_I = 0;

void print_clocks()
{
	int i, j;

	for(i=0; i < CLOCKS_NUM ;i++){
		printf("%d ",cur_clock[i]);
	}
	printf("\n");
}

void press_slected_button(int num)
{
	int i;
	for(i=0; i < button[num][0]; i++){
		cur_clock[button[num][i+1]] += 3;
		if(cur_clock[button[num][i+1]] > 12)
			cur_clock[button[num][i+1]] -= 12;
	}
}

int check_cur_clock()
{
	int i;

	for(i=0; i < CLOCKS_NUM; i++){
		if(cur_clock[i] != 12)
			return 0;
	}

	return 1;
}

int print_pressed_button()
{
	int i, j, result=0;
#ifdef DEBUG
	for(i=0; i < 10; i++){
		printf("%d ", pressed_button[i]);
	}
	printf("\n");
#endif

	for(i=0; i < 10; i++){
		for(j=0; j < pressed_button[i]; j++){
			press_slected_button(i);
		}
		result += pressed_button[i];
	}
#ifdef DEBUG
	print_clocks();
#endif
	if(check_cur_clock() == 1){
		printf("%d\n", result);
		return result;
	}

	return 0;
}


int init_specific_pressed_button(int num)
{
	int i, result;

	if(num == BUTTON_NUM-1){
		for(i=0; i<CLOCKS_NUM; i++){
			cur_clock[i] = clock[CUR_I][i];
		}
		
		result = print_pressed_button();
		if(result > 0){
			return result;
		}
	}
	pressed_button[num] = 0;

	return 0;
}


void press_button(int num)
{
	pressed_button[num]++;
}


int join(int num)
{
	int i, j, result;
	if(num >= BUTTON_NUM || END == 1)
		return 0;

	for(i=0; i < 4; i++){
		for(j=0; j < i; j++){
			press_button(num);
		}
		join(num+1);
		result = init_specific_pressed_button(num);
		if(result > 0){
			END = 1;
			return result;
		}
	}

	return 0;
}


int main(void)
{
	int i, j;
	int cases;

	scanf("%d",&cases);

	for(i=0; i < cases; i++){
		for(j=0; j < CLOCKS_NUM; j++){
			scanf("%d",&clock[i][j]);
		}
	}
	for(i=0; i < cases; i++){
		CUR_I = i;
		join(0);
		if(END == 0)
			printf("-1\n");
		else
			END = 0;
	}
	
	return 0;
}
