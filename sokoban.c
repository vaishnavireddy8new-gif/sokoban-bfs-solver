#include <stdio.h>
#include <string.h>

int dr[4]={-1,0,1,0}; //wasd uldr
int dc[4]={0,-1,0,+1};

char mv[4]={'W','A','S','D'};

typedef struct {
    char board[100][100];
    int pr, pc;
    char path[1000];
} GameState;

GameState queue[10000];
int front = 0, rear = 0;

char visited[10000][10000]; // visited array for BFS
int vis_count = 0;

void flatten(char board[100][100], int r, int n, char out[]) {
    int k = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < n; j++) {
            out[k++] = board[i][j];
        }
    }
    out[k] = '\0';
}

int is_visited(char key[]) {
    for (int i = 0; i < vis_count; i++) {
        if (strcmp(visited[i], key) == 0)
            return 1;
    }
    return 0;
}

int solved(char board[100][100], int r, int n) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == '$')
                return 0;
        }
    }
    return 1;
}


int makemove(char a[100][100], int pi, int pj,int r,int n,int dir){
    int dr[4]={-1,0,1,0}; //wasd uldr
    int dc[4]={0,-1,0,+1};

    int ni=pi+dr[dir];
    int nj=pj+dc[dir];

    int bi=pi+(2*dr[dir]);
    int bj=pj+(2*dc[dir]);

    char current=a[pi][pj];
    char next=a[ni][nj];

    if(ni<0 || ni>=r || nj<0 || nj>=n || next=='#') return 0;

    if (next == ' ') {
    if (current == '@') {
        a[ni][nj] = '@';
        a[pi][pj] = ' ';
    } 
    else if (current == '+') {
        a[ni][nj] = '@';
        a[pi][pj] = '.';
    }
    return 1;
    }

     if (next == '.') {
    if (current == '@') {
        a[ni][nj] = '+';
        a[pi][pj] = ' ';
    } 
    else if (current == '+') {
        a[ni][nj] = '+';
        a[pi][pj] = '.';
    }
    return 1;
    }

    if (next == '$' || next == '*') {
        if (bi < 0 || bi >= r || bj < 0 || bj >= n)
            return 0;

        if (current == '@'){
            if (next == '$') {
                if (a[bi][bj] == ' ' ) {
                    a[bi][bj] = '$';
                    a[ni][nj] = '@';
                    a[pi][pj] = ' ';
                }
                if(a[bi][bj] == '.'){
                    a[bi][bj] = '*';
                    a[ni][nj] = '@';
                    a[pi][pj] = ' ';
                }
            } 
            else if (next == '*') {
                 if (a[bi][bj] == ' ') {
                    a[bi][bj] = '$';
                    a[ni][nj] = '+';
                    a[pi][pj] = ' ';
                }
                if (a[bi][bj] == '.'){
                    a[bi][bj] = '*';
                    a[ni][nj] = '+';
                    a[pi][pj] = ' ';
                }
            }
        }
        else if (current == '+'){
             if (next == '$') {
                if (a[bi][bj] == ' ') {
                    a[bi][bj] = '$';
                    a[ni][nj] = '@';
                    a[pi][pj] = '.';
                }
                if (a[bi][bj] == '.'){
                    a[bi][bj] = '*';
                    a[ni][nj] = '@';
                    a[pi][pj] = '.';
                }
            } 
            else if (next == '*') {
                 if (a[bi][bj] == ' ' ) {
                    a[bi][bj] = '$';
                    a[ni][nj] = '+';
                    a[pi][pj] = '.';
                }
                if (a[bi][bj] == '.'){
                    a[bi][bj] = '*';
                    a[ni][nj] = '+';
                    a[pi][pj] = '.';
                }
            }
        }   
        
        
           
        return 1;
    }

    return 0;


    }

void bfs(char a[100][100], int pi, int pj, int r, int n) {
    GameState start;
    memcpy(start.board, a, sizeof(start.board));
    start.pr = pi;
    start.pc = pj;
    start.path[0] = '\0';

    queue[rear++] = start;

    char key[10000];
    flatten(start.board, r, n, key);

    strcpy(visited[vis_count++], key);

    while (front < rear) {
        GameState cur = queue[front++];

        if (solved(cur.board, r, n)) {
            printf("Solution found: %s\n", cur.path);
            return;
        }

        for (int dir = 0; dir < 4; dir++) {
            GameState next = cur;

            if (makemove(next.board, next.pr, next.pc, r, n, dir)==1) {
                next.pr += dr[dir];
                next.pc += dc[dir];

                int len = strlen(next.path);
                next.path[len] = mv[dir];
                next.path[len + 1] = '\0';

                flatten(next.board, r, n, key);

                if (is_visited(key)==0) {
                    strcpy(visited[vis_count++], key);
                    queue[rear++] = next;
                }
            }
        }
    }

    printf("No solution exists\n");
}


int main(){

int n,l,r,boxes=0,goals=0,boxes_on_goals=0,o,pi,pj;
char m,k,str[100];


scanf("%d %c",&n,&k);
if(k==':'){
    scanf(" %[^\n]", str);
}

l=strlen(str);
r=(l/n);

char a[100][100];
for(int i=0;i<r;i++){
    for(int j=0;j<n;j++){
        a[i][j]=str[(i*n)+j];
    }
}

for(int i=0;i<r;i++){
    for(int j=0;j<n;j++){
       if (a[i][j]=='$') boxes++;
       if (a[i][j]=='.') goals++;
    }
}

if (boxes>goals){o=goals;}
else{o=boxes;}

printf("Boxes: %d, Goals: %d\n", boxes, goals);

for(int i=0;i<r;i++){
    for(int j=0;j<n;j++){
        if (a[i][j]=='@' || a[i][j]=='+'){
         pi=i;
         pj=j;
        }
    }
}
printf("Solving using BFS: \n");
bfs(a, pi, pj, r, n);

do {
    printf("Current state:\n");
for(int i=0;i<r;i++){
    for(int j=0;j<n;j++){
        printf("%c",a[i][j]);
    }
    printf("\n");
}
//taking input for move
    do {printf("Make your move: ");
     scanf(" %c",&m);} while((m!='W') && (m!='A') && (m!='S') && (m!='D'));

     //updating the state of the game based on the move
for(int i=0;i<r;i++){
    for(int j=0;j<n;j++){
        if (a[i][j]=='@' || a[i][j]=='+'){
         pi=i;
         pj=j;
        }
    }
}
    if (m=='W'){
        makemove(a,pi,pj,r,n,0);      
           }
    else if (m=='A'){
        makemove(a,pi,pj,r,n,1);
           }
    else if (m=='S'){
          makemove (a,pi,pj,r,n,2);  
            }
    else if (m=='D'){
          makemove(a,pi,pj,r,n,3);   
           }
    


boxes_on_goals=0;
for(int i=0;i<r;i++){
    for(int j=0;j<n;j++){
       if (a[i][j]=='*') boxes_on_goals++;
    }
}

if (boxes_on_goals==o){
    printf("Congratulations! You've won the game!\n");
      break;
    }
}
while(boxes_on_goals<o);

return 0;
}