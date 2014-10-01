#include <stdio.h>
#include <string.h>

const int SIZE = 5;
const int PIVOT_SIZE = 9;
const int MAX_WORD_LENGTH = 11;
const int dX[PIVOT_SIZE] = { 1, 1, 0, -1, -1, -1,  0,  1 };
const int dY[PIVOT_SIZE] = { 0, 1, 1, 1, 0, -1, -1, -1 };
bool EXIST_MAP2[255][255] = {};


bool isExistsFast(char* word) {
	const int LENGTH = strlen(word);
	for (int index = 0; index < LENGTH - 1; index++) {
		const int code = word[index];
		const int nextCode = word[index + 1];
		bool* map = EXIST_MAP2[code];
		if (!map[nextCode]) {
			return false;
		}
	}
	return true;
}

int main(void) {

	int tc, T;
		
	//freopen("input.txt", "r", stdin);
	//freopen("input_small.txt", "r", stdin);
	//freopen("input_timeout.txt", "r", stdin);
	//freopen("input_timeout2.txt", "r", stdin);
	
	setbuf(stdout, NULL);

	scanf("%d", &T);
	for(tc = 0; tc < T; tc++)
	{
		
		/**********************************
		*  Implement your algorithm here. *
		***********************************/		
		int row, column;
		char table[SIZE][SIZE + 1];

		// Read table and create exist map
		for (row = 0; row < SIZE; row++) {			
			scanf("%s", table[row]);
		}
		
		// Read table and create reference between letters		
		for (int row = 0; row < SIZE; row++) {
			for (int column = 0; column < SIZE; column++) {				
				
				const int index = table[row][column];
				//EXIST_MAP[index] = true;
				bool* map = EXIST_MAP2[index];
				for (int indexForPivot = 0; indexForPivot < PIVOT_SIZE; ++indexForPivot) {
					const int newX = dX[indexForPivot] + column;
					const int newY = dY[indexForPivot] + row;

					if (newX < 0 || newX > SIZE) {
						continue;
					}

					if (newY < 0 || newY > SIZE) {
						continue;
					}

					const int token = table[newY][newX];
					map[token] = true;					
				}
			}
		}

		// Read testcase
		int totalWords;
		scanf("%d", &totalWords);
		for (int count = 0; count < totalWords; count++) {
			
			char word[MAX_WORD_LENGTH];
			scanf("%s", word);
			
			// Check existance of word in table
			if (isExistsFast(word)) {
				printf("%s YES\n", word);
			}
			else {
				printf("%s NO\n", word);
			}
		}
	}	
	
	return 0;
}
