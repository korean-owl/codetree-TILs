/*
제목 : 2개의 사탕
N×M 크기의 상자 안에 빨간색 사탕과 파란색 사탕이 각각 하나씩 들어있습니다. 이 상자 안에는 사탕이 지나가지 못하도록 하는 장애물이 여러 개 있고, 사탕이 밖으로 빠져 나올 수 있는 구멍이 딱 하나 있습니다.
이러한 상황에서 빨간색 사탕을 밖으로 빼내려고 합니다. 사탕을 밖으로 빼기 위해서는 상자를 위, 아래, 왼쪽, 오른쪽 방향으로 기울일 수 있는데, 기울어진 방향으로 사탕은 장애물 혹은 다른 사탕에 부딪히기 전 까지 미끌어지게 되며, 미끄러지는 도중에 상자를 다른 방향으로 기울일 수는 없습니다.
예를 들어 위의 예에서 상자를 아래로 기울이게 되면 다음과 같은 모양이 됩니다.
빨간색 사탕을 밖으로 빼야 하지만, 파란색 사탕이 밖으로 나와서는 안됩니다. 즉, 빨간색 사탕이 나오기 전에 파란색 사탕이 먼저 나오면 안되며, 빨간색 사탕이 나올 때 파란색 사탕이 동시에 나오는 것도 안됩니다.
예를 들어 바로 위의 상황에서 왼쪽으로 상자를 기울이게 되면 빨간색 사탕이 밖으로 나오게 되지만, 그 이후에 파란색 사탕 역시 밖으로 나오게 되므로 잘못된 경우입니다.
가장 처음 주어진 그림에서 빨간색 사탕만 밖으로 빼내기 위해서는 순서대로 오른쪽, 아래 그리고 왼쪽 방향으로 기울이면 됩니다.

이런 상황에서 빨간색 사탕을 밖으로 빼내기 위해 기울여야 하는 최소 횟수를 구하는 프로그램을 작성해보세요.


문제 해석 :
	1. 이동 : 위, 아래, 왼쪽, 오른쪽
	2.탈출 : 빨간색 사탕 O, 파란색 사탕 X
	3.
*/


/*
입력 형식
첫째 줄에는 N과 M이 공백을 사이에 두고 주어집니다.

둘째 줄 부터는 N개의 줄에 걸쳐 각 행의 상태에 해당하는 M개의 문자가 공백 없이 주어집니다. 각 문자는 '.', ‘#', ‘B’, ‘R’, 'O’ 중에 하나이며 각 위치에 빈 칸, 장애물, 파란색 사탕, 빨간색 사탕, 출구가 있음을 의미합니다. 상자의 바깥 부분은 전부 장애물로 막혀있게 주어진다 가정해도 좋습니다.

3≤N≤10

3≤M≤10


출력 형식
빨간색 사탕을 밖으로 빼내기 위해 기울여야 하는 최소 횟수를 출력합니다. 만약 10번 이내에 빨간색 사탕을 밖으로 빼내는 것이 불가능하다면, −1을 출력합니다.



*/
#include<iostream>
#include<queue>
using namespace std;
class INFO {
public:
	int rx;
	int ry;

	int bx;
	int by;

	int cnt;
	INFO(int irx = 0, int iry = 0, int ibx = 0, int iby = 0, int icnt = 0)
		:rx(irx),ry(iry),bx(ibx),by(iby),cnt(icnt)
	{}
};
int n, m;
char board[11][11];
char tempBoard[101][101];
const int dx[4] = { 0,1,0,-1 };
const int dy[4] = { 1,0,-1,0 };
int answer;
bool CanGo(int x, int y)
{
	return board[x][y] != '#' && board[x][y] != '0';
}
void InPut()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
			if (board[i][j] == 'R')
			{
				start.rx = i;
				start.ry = j;
			}
			else if (board[i][j] == 'B')
			{
				start.bx = i;
				start.by = j;
			}
		}
	start.cnt = 0;
}
INFO start;
char board[10][11];
int BFS()
{
	bool visited[11][11][11][11] = { 0, };
	queue<INFO>q ;
	q.push(start);
	visited[start.rx][start.ry][start.bx][start.by] = true;

	int ans = -1;
	while (!q.empty())
	{
		//1. 정보 받기
		INFO curr = q.front();
		q.pop();
		
		// 2. 끝나는  조건
		//View(currRed, currBlue, currCnt);
		
		if (curr.cnt > 10) break;
		if (board[curr.rx][curr.ry] == 'O' && board[curr.bx][curr.by] != 'O')
		{
			ans = curr.cnt;
				break;
		}
		
		//3. 방향을 가진 Next 생성
		for (int i = 0; i < 4; i++)// 4 방향 모두 queue에 넣어야함.
		{
			int nry = curr.ry;
			int nrx = curr.rx;
			int nby = curr.by;
			int nbx = curr.bx;
			// red 구슬 한 방향으로 이동
			while (true)
			{
				if (board[nrx][nry] != '#' && board[nrx][nry] != '0')//(CanGo(nr.x, nr.y))
				{
					nrx += dx[i];
					nry += dy[i];
				}
				else {
					nrx = (board[nrx][nry] == '#') ? (nrx -= dx[i]) : nrx;
					nry = (board[nrx][nry] == '#') ? (nry-= dy[i])  : nry;
					break;
				}
			}
			// blue 구슬 한 방향으로 이동
			while (true)
			{
				if (board[nbx][nby] != '#' && board[nbx][nby] != '0')//(CanGo(nb.x, nb.y))
				{
					nbx += dx[i];
					nby += dy[i];
				}
				else {

					nbx = (board[nbx][nby] == '#') ? (nbx -= dx[i]) : nbx;
					nby = (board[nbx][nby] == '#') ? (nby -= dy[i]) : nby;
					break;
				}
			}

			if (nry == nby && nrx == nbx)
			{
				//겹쳤지만 구멍이 아닐때 
				if (board[nrx][nry] != 'O')
				{
					int redDist = abs(nrx - curr.rx) + abs(nry - curr.ry);
					int blueDist = abs(nbx - curr.bx) + abs(nby - curr.by);
					//, 이동 거리를 기준으로 누가 앞이 였는지 정한다.
					if (blueDist > redDist)
					{
						nbx -= dx[i];
						nby -= dy[i];
					}
					else
					{
						nrx -= dx[i];
						nry -= dy[i];
					}
				}
			}
			// 4. Queue에 들어갈 수 있는 조건 
			if (visited[nrx][nry][nbx][nby] == false )
			{
				visited[nrx][nry][nbx][nby] = true;
				INFO next;
				next.ry = nrx;
				next.rx = nry;
				next.by = nby;
				next.bx = nbx;
				next.cnt = curr.cnt + 1;

				q.push(next);
			}
		}
	}
	return ans;
}
int main()
{
	InPut();
	answer = BFS();

	cout << answer << endl;
	return 0;
}