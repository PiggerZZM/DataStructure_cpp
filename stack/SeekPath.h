#include <iostream>
using namespace std;
const int m = 3, n = 3;
int Maze[m+2][n+2] = {0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0};
int mark[m+2][m+2] = {0};
struct offsets
{
    // ǰ�������
    int x,y;    // x����λ�ƺ�y����λ��
    char *dir;  // ����
};

int SeekPath(int x, int y, int m, int n)
{
    // ��(x,y)λ�ó���Ѱ�ҳ���(m,n)���ҵ�����1���Ҳ�������0
    offsets move[8] = {{-1,0,"N"},{-1,1,"NE"},{0,1,"E"},{1,1,"SE"},{1,0,"S"},{1,-1,"SW"},{0,1,"W"},{-1,-1,"NW"}};
    
    int next_x, next_y;
    char *direction;
    if(x == m && y == n)
        return 1;
    for(int i=0;i<8;i++)
    {
        // ��8��������̽
        next_x = x + move[i].x;
        next_y = y + move[i].y;
        direction = move[i].dir;
        if(Maze[next_x][next_y] && !mark[next_x][next_y])
        {
            mark[next_x][next_y] = 1;
            if(SeekPath(next_x,next_y,m,n))
            {
                cout << direction << ",(" << next_x << "," << next_y << ")" << endl;
                return 1;
            }
        }
    }
    if(x == 1 && y == 1)
        cout << "no path in Maze" << endl;
    return 0;
}