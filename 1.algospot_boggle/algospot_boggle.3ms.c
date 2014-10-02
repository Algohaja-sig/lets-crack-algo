#include <stdio.h>
#include <string.h>

int N;

char A[5][6];
char str[11];
int len;
char idx[256][25][2];
int count[256];

bool isConnected(char a, int count_a, char b, int count_b)
{
    int i, j;

    if(a == b)
    {
        if(count_a < 2) return false;
        for(i=0;i<count_a;i++)
        {
            for(j=i+1;j<count_a;j++)
            {
                if((idx[a][i][0] - idx[b][j][0] <= 1) && (idx[a][i][0] - idx[b][j][0] >= -1) && (idx[a][i][1] - idx[b][j][1] <= 1) && (idx[a][i][1] - idx[b][j][1] >= -1)) return true;
            }
        }
        return false;
    }

    for(i=0;i<count_a;i++)
    {
        for(j=0;j<count_b;j++)
        {
            if((idx[a][i][0] - idx[b][j][0] <= 1) && (idx[a][i][0] - idx[b][j][0] >= -1) && (idx[a][i][1] - idx[b][j][1] <= 1) && (idx[a][i][1] - idx[b][j][1] >= -1)) return true;
        }
    }
    return false;
}

bool find(int a, int x, int y)
{
    if(x < 0 || x >= 5 || y < 0 || y >= 5) return false;
    if(a >= len) return true;

    if(A[x-1][y-1] == str[a]) if(find(a+1, x-1, y-1)) return true;
    if(A[x-1][y] == str[a]) if(find(a+1, x-1, y)) return true;
    if(A[x-1][y+1] == str[a]) if(find(a+1, x-1, y+1)) return true;
    if(A[x][y-1] == str[a]) if(find(a+1, x, y-1)) return true;
    if(A[x][y+1] == str[a]) if(find(a+1, x, y+1)) return true;
    if(A[x+1][y-1] == str[a]) if(find(a+1, x+1, y-1)) return true;
    if(A[x+1][y] == str[a]) if(find(a+1, x+1, y)) return true;
    if(A[x+1][y+1] == str[a]) if(find(a+1, x+1, y+1)) return true;
    return false;
}

int main()
{
    //freopen("test.txt", "rt", stdin);

    int T, i, j;
    scanf("%d", &T);

    while(T--)
    {
        scanf("%s %s %s %s %s", A[0], A[1], A[2], A[3], A[4]);
        scanf("%d", &N);

        for(i='A';i<='Z';i++) count[i] = 0;
        for(i=0;i<5;i++)
        {
            for(j=0;j<5;j++)
            {
                idx[A[i][j]][count[A[i][j]]][0] = i;
                idx[A[i][j]][count[A[i][j]]][1] = j;
                count[A[i][j]]++;
            }
        }

        for(i=0;i<N;i++)
        {
            scanf("%s", str);
            len = strlen(str);

            for(j=0;j<len;j++) if(count[str[j]] == 0) break;
            if(j != len) { printf("%s NO\n", str); continue; }

            for(j=0;j<len-1;j++) if(!isConnected(str[j], count[str[j]], str[j+1], count[str[j+1]])) break;
            if(j != len - 1) { printf("%s NO\n", str); continue; }

            for(j=0;j<count[str[0]];j++)
            {
                if(find(1, idx[str[0]][j][0], idx[str[0]][j][1])) break;
            }

            if(j == count[str[0]]) { printf("%s NO\n", str); continue; }
            printf("%s YES\n", str);
        }
    }

    return 0;
}
