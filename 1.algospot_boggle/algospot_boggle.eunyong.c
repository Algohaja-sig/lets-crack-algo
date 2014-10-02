#include <stdio.h>

#define MAX 5
//#define DEBUG

char data[MAX+1][MAX+1];
char ans[30][128];
int result[30];

char cache[MAX+1][MAX+1]={
".....",
".....",
".....",
".....",
".....",
	};

static int hasWord(int y, int x, int cur_position, int ans_n)
{
	int find=0;
	
	if(cache[y][x]==ans[ans_n][cur_position])
		return 1;

	if(ans[ans_n][cur_position]==0){
#ifdef DEBUG
		printf("success\n");
#endif
		return 0;
	}
	
	if(x>0){
		if(ans[ans_n][cur_position]==data[y][x-1]){
			find=1;
#ifdef DEBUG
			printf("left : %c\n",data[y][x-1]);
#endif
			if(!hasWord(y,x-1,cur_position+1, ans_n))
				return 0;
		}
	}
	if(y>0 && x>0){
		if(ans[ans_n][cur_position]==data[y-1][x-1]){
			find=1;
#ifdef DEBUG
			printf("left-up : %c\n",data[y-1][x-1]);
#endif
			if(!hasWord(y-1,x-1,cur_position+1, ans_n))
				return 0;
		}
	}
	if(y>0){
		if(ans[ans_n][cur_position]==data[y-1][x]){
			find=1;
#ifdef DEBUG
			printf("up : %c\n",data[y-1][x]);
#endif
			if(!hasWord(y-1,x,cur_position+1, ans_n))
				return 0;
		}
	}
	if(y>0 && x<MAX){
		if(ans[ans_n][cur_position]==data[y-1][x+1]){
			find=1;
#ifdef DEBUG
			printf("right-up : %c\n",data[y-1][x+1]);
#endif
			if(!hasWord(y-1,x+1,cur_position+1, ans_n))
				return 0;
		}
	}
	if(x<MAX){
		if(ans[ans_n][cur_position]==data[y][x+1]){
			find=1;
#ifdef DEBUG
			printf("right : %c\n",data[y][x+1]);
#endif
			if(!hasWord(y,x+1,cur_position+1, ans_n))
				return 0;
		}
	}
	if(y<MAX && x<MAX){
		if(ans[ans_n][cur_position]==data[y+1][x+1]){
			find=1;
#ifdef DEBUG
			printf("right-down : %c\n",data[y+1][x+1]);
#endif
			if(!hasWord(y+1,x+1,cur_position+1, ans_n))
				return 0;
		}
	}
	if(y<MAX){
		if(ans[ans_n][cur_position]==data[y+1][x]){
			find=1;
#ifdef DEBUG
			printf("down : %c\n",data[y+1][x]);
#endif
			if(!hasWord(y+1,x,cur_position+1, ans_n))
				return 0;
		}
	}
	if(y<MAX && x>0){
		if(ans[ans_n][cur_position]==data[y+1][x-1]){
			find=1;
#ifdef DEBUG
			printf("left-down : %c\n",data[y+1][x-1]);
#endif
			if(!hasWord(y+1,x-1,cur_position+1, ans_n))
				return 0;
		}
	}

	if(!find)
		cache[y][x]=ans[ans_n][cur_position];
				
#ifdef DEBUG
		printf("fail\n");
#endif

	return 1;
}

int main(void)
{
	int i,j,k;
	int ans_num, cases;

	scanf("%d",&cases);

	while(cases--) {

		for(i=0;i<5;i++)
			scanf("%s",data[i]);

		scanf("%d",&ans_num);

		for(i=0;i<ans_num;i++){
			scanf("%s",ans[i]);
		}
		
		for(k=0;k<ans_num;k++){
			
			//initialize cache
			for(i=0;i<MAX;i++){
				for(j=0;j<MAX;j++){
					cache[i][j]='.';
				}
			}
												
			for(i=0;i<MAX;i++){
				for(j=0;j<MAX;j++){
					if(data[i][j] == ans[k][0]){
						if(!hasWord(i,j,1,k)){
							result[k]=1;
							goto success;
						}
					}
				}
			}
			result[k]=0; //fail
success:;
		}
		
		for(i=0;i<ans_num;i++){
			if(result[i])
				printf("%s YES\n",ans[i]);
			else
				printf("%s NO\n",ans[i]);
		}
		
	}

#ifdef DEBUG
		for(i=0;i<MAX;i++)
			printf("%s\n",cache[i]);
#endif
	
	return 0;
}
