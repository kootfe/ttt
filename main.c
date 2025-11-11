#include <stdio.h>

const char *colorize(char c) {
    if (c == 'X') return "\x1b[31mX\x1b[0m";
    if (c == 'O') return "\x1b[34mO\x1b[0m";
    if (c >= '0' && c <= '9') {
        static const char digits[][2] = {"0","1","2","3","4","5","6","7","8","9"};
        return digits[c - '0'];
    }
    return "?";
}

void draw(char positons[3][3])
{
    for (int i = 0; i < 3; ++i) {
        printf("%s|%s|%s\n%s",colorize(positons[i][0]), colorize(positons[i][1]), colorize(positons[i][2]), i<2?"-|-|-\n":"");
    }
}

int checkWin(char b[3][3], int r, int c)
{
    char player = b[r][c];
    if (b[r][0]==player && b[r][1]==player && b[r][2]==player) return player=='X'?-1:1;
    if (b[0][c]==player && b[1][c]==player && b[2][c]==player) return player=='X'?-1:1;
    if (r==c && b[0][0]==player && b[1][1]==player && b[2][2]==player) return player=='X'?-1:1;
    if (r+c==2 && b[0][2]==player && b[1][1]==player && b[2][0]==player) return player=='X'?-1:1;
    return 0;
}

int main()
{
    char positons[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
    draw(positons);
    int isX = 1;
    for (int m = 0; m < 9; ++m) {
        int inp;
        char ply = !isX ? 'X' : 'O';
        printf("Move of %c: ", ply);
        if ((scanf("%d", &inp) != 1) || inp < 0 || inp > 9) {
            printf("Please enter valid number!\n");
            while(getchar() != '\n');
            continue;
        }
        int row = (inp - 1) /3, col = (inp - 1) % 3;
        if (positons[row][col] == 'X' || positons[row][col] == 'O') {
            printf("Please write empty slot!\n");
            continue;
        }
        positons[row][col] = ply;
        draw(positons);
        int win = checkWin(positons, row, col);
        if (win) {
            printf("%c wins!\n", ply);
            break;
        }
        isX = !isX;
        if (m==8) printf("TIE\n");
    }
    return 0;
}
