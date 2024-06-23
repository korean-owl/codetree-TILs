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
class Marker {
public:
	int x;
	int y;
	Marker(int ix = 0, int iy = 0) :x(ix), y(iy)
	{}
};
int n, m;
char board[11][11];
char tempBoard[101][101];
queue<pair<pair<Marker, Marker>, int>>q1;
Marker red;
Marker blue;
Marker Goal;
typedef enum {
	enumRight,
	enumDown,
	enumLeft,
	enumUp,
}enumDir;
const int dx[4] = { 0,1,0,-1 };
const int dy[4] = { 1,0,-1,0 };
int answer;
bool InRange(int x, int y)
{
	return x >= 0 && x < n&& y >= 0 && y <= m;
}
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
				red.x = i;
				red.y = j;
				board[i][j] = '.';
			}
			else if (board[i][j] == 'B')
			{
				blue.x = i;
				blue.y = j;
				board[i][j] = '.';
			}
			else if (board[i][j] == 'O')
			{
				Goal.x = i;
				Goal.y = j;
			}
		}

	answer = -1;
}
void View(Marker m1, Marker m2 , int cnt)
{
	cout << cnt<<"번째 "<<endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (m1.x == i && m1.y == j)
			{
				cout << "R";
			}
			else if(m2.x == i && m2.y == j)
			{
				cout << "B";
			}
			else
			{
				cout << board[i][j];
			}
		}cout << endl;
	}
	cout << endl;
}
int BFS()
{
	bool visited[11][11][11][11] = { 0, };
	visited[red.x][red.y][blue.x][blue.y] = true;
	q1.push({ {red,blue},0 });
	int ans = -1;
	while (!q1.empty())
	{
		//1. 정보 받기
		Marker currRed, currBlue;
		currRed = q1.front().first.first;
		currBlue = q1.front().first.second;
		int currCnt = q1.front().second;
		q1.pop();
		
		// 2. 끝나는  조건
		//View(currRed, currBlue, currCnt);
		if (currCnt >= 10) break;
		if (board[currRed.x][currRed.y] == 'O' && board[currBlue.x][currBlue.y] != 'O')
		{
			ans = currCnt;
				break;
		}
		
		//3. 방향을 가진 Next 생성
		for (int i = 0; i < 4; i++)// 4 방향 모두 queue에 넣어야함.
		{
			Marker nr(currRed.x, currRed.y);
			Marker nb(currBlue.x, currBlue.y);
			// red 구슬 한 방향으로 이동
			while (true)
			{
				if (board[nr.x][nr.y] != '#' && board[nr.x][nr.y] != '0')//(CanGo(nr.x, nr.y))
				{
					nr.x+= dx[i];
					nr.y += dy[i];
				}
				else {
					nr.x = (board[nr.x][nr.y] == '#') ? (nr.x -= dx[i]) : nr.x;
					nr.y = (board[nr.x][nr.y] == '#') ? (nr.y-= dy[i]) : nr.y;
					break;
				}
			}

			// blue 구슬 한 방향으로 이동
			while (true)
			{
				if (board[nb.x][nb.y] != '#' && board[nb.x][nb.y] != '0')//(CanGo(nb.x, nb.y))
				{
					nb.x += dx[i];
					nb.y += dy[i];
				}
				else {

					nb.x = (board[nb.x][nb.y] == '#') ? (nb.x -= dx[i]) : nb.x;
					nb.y = (board[nb.x][nb.y] == '#') ? (nb.y -= dy[i]) : nb.y;
					break;
				}
			}

			if (nr.y == nb.y && nr.x == nb.x)
			{
				//겹쳤지만 구멍이 아닐때 
				if (board[nr.x][nr.y] != 'O')
				{
					int redDist = abs(nr.x - currRed.x) + abs(nr.y - currRed.y);
					int blueDist = abs(nb.x - currBlue.x) + abs(nb.y - currBlue.y);
					//, 이동 거리를 기준으로 누가 앞이 였는지 정한다.
					if (blueDist > redDist)
					{
						nb.x -= dx[i];
						nb.y -= dy[i];
					}
					else
					{
						nr.x -= dx[i];
						nr.y -= dy[i];
					}
				}
			}
			// 4. Queue에 들어갈 수 있는 조건 
			if (visited[nr.x][nr.y][nb.x][nb.y] == false && board[nb.x][nb.y] != 'O')
			{
				visited[nr.x][nr.y][nb.x][nb.y] = true;
				q1.push({ { nr,nb }, currCnt + 1 });
			}


		}
	}
	return ans;
}
int main()
{
	//cout << answer << endl;
	InPut();

	//cout << answer << endl;
	answer = BFS();

	cout << answer << endl;
	return 0;
}