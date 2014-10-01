#include <stdio.h>
#include <string.h>

const int SIZE = 5;
const int PIVOT_SIZE = 9;
const int dX[PIVOT_SIZE] = { 1, 1, 0, -1, -1, -1,  0,  1 };
const int dY[PIVOT_SIZE] = { 0, 1, 1, 1, 0, -1, -1, -1 };
bool EXIST_MAP[255] = {};
bool EXIST_MAP2[255][255] = {};

bool digg(int startX, int startY, char table[][6], char* word, int indexForFind) {
	const int x = startX;
	const int y = startY;

	if (indexForFind > strlen(word) - 1) {
		return true;
	}

	for (int indexForPivot = 0; indexForPivot < PIVOT_SIZE; ++indexForPivot) {
		const int newX = dX[indexForPivot] + x;
		const int newY = dY[indexForPivot] + y;

		if (newX < 0 || newX > SIZE) {
			continue;
		}

		if (newY < 0 || newY > SIZE) {
			continue;
		}
		
		const char token = table[newY][newX];		
		if (token == word[indexForFind]) {
			if (digg(newX, newY, table, word, indexForFind + 1)) {
				return true;
			}
		}
	}
	return false;
}

bool isExists(char table[][6], char* word) {
		
	for (int row = 0; row < SIZE; row++) {
		for (int column = 0; column < SIZE; column++) {
			const char token = table[row][column];
			if (token == word[0]) {
				if (digg(column, row, table, word, 1)) {
					return true;
				}
			}
		}
	}
	return false;
}

int main(void) {

	int tc, T;
		
	//freopen("input_small.txt", "r", stdin);
	
	//setbuf(stdout, NULL);

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
			const char* str = table[row];
			for (column = 0; column < SIZE; column++) {
				const int code = str[column];
				EXIST_MAP[code] = true;
			}
		}
		
		// Read table and create reference between letters		
		for (int row = 0; row < SIZE; row++) {
			for (int column = 0; column < SIZE; column++) {
				const int index = table[row][column];
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
			
			char word[11];
			scanf("%s", word);

			// Filter out invalid testcase
			bool skip = false;
			const int TOTAL = strlen(word);
			for (int index = 0; index < TOTAL; index++) {
				int code = word[index];
				if (!EXIST_MAP[code]) {
					skip = true;
					break;
				}
				if (index < TOTAL - 1) {
					bool* map = EXIST_MAP2[code];
					code = word[index + 1];
					if (!map[code]) {
						skip = true;
						break;
					}
				}				
			}
			if (skip) {
				printf("%s NO\n", word);
				continue;
			}

			// Check existance of word in table
			if (isExists(table, word)) {
				printf("%s YES\n", word);
			}
			else {
				printf("%s NO\n", word);
			}
		}
	}	
	
	return 0;
}

