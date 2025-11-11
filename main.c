#include <signal.h>
#include <stdio.h>

#define ROW(x) ((x) -1)/3
#define COL(x) ((x) -1)%3

const char *colorize(char c)
{
    switch(c) {
        case 'X': return "\x1b[31mX\x1b[0m";
        case 'O': return "\x1b[34mO\x1b[0m";
        default: 
                  if (c >= '0'  && c <= '9') {
                      static char dig[][2] = {"0","1","2","3","4","5","6","7","8","9"};
                      return dig[c - '0'];
                  }
                  return "?";
    }
}

void draw(char positons[3][3])
{
    for (int i = 0; i < 3; ++i) {
        printf("%s|%s|%s\n%s",colorize(positons[i][0]), colorize(positons[i][1]), colorize(positons[i][2]), i<2?"-|-|-\n":"");
    }
}

int checkWin(char board[3][3])
{
    for(int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return board[i][0] == 'X' ? -1 : 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return board[0][i] == 'X' ? -1 : 1;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return board[0][0] == 'X' ? -1 : 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return board[0][2] == 'X' ? -1 : 1;
    return 0;
}
int main()
{
    char positons[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
    draw(positons);
    int shouldExit = 0, isX = 1;
    for (int m = 0; m < 9; ++m) {
        int inp;
        char ply = !isX ? 'X' : 'O';
        printf("Move of %c: ", ply);
        if ((scanf("%d", &inp) != 1) || inp < 0 || inp > 9) {
            printf("Please enter valid number!\n");
            while(getchar() != '\n');
            continue;
        }
        int row = ROW(inp), col = COL(inp);
        if (positons[row][col] == 'X' || positons[row][col] == 'O') {
            printf("Please write empty slot!\n");
            continue;
        }
        positons[row][col] = ply;
        draw(positons);
        int win = checkWin(positons);
        if (win) {
            shouldExit = 1;
            printf("%c wins!\n", ply);
        }
        isX = !isX;
        if (m==8) printf("TIE\n");
    }
    return 0;
}
