#include <stdio.h>
#include <string.h>

const int SIZE = 5;
const int PIVOT_SIZE = 9;
const int dX[PIVOT_SIZE] = { 1, 1, 0, -1, -1, -1,  0,  1 };
const int dY[PIVOT_SIZE] = { 0, 1, 1, 1, 0, -1, -1, -1 };

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
		
	// Check every tokens in words exist in table
	
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
		
	//freopen("input_timeout.txt", "r", stdin);
	
	//setbuf(stdout, NULL);

	scanf("%d", &T);
	for(tc = 0; tc < T; tc++)
	{
		
		/**********************************
		*  Implement your algorithm here. *
		***********************************/		
		int row, column;
		char table[SIZE][SIZE + 1];
		
		for (row = 0; row < SIZE; row++) {			
			scanf("%s", table[row]);
			char* str = table[row];
			for (column = 0; column < SIZE; column++) {
				str[column];
			}
		}

		int count, totalWords;
		scanf("%d", &totalWords);
		for (count = 0; count < totalWords; count++) {

			char word[11];

			scanf("%s", word);
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
