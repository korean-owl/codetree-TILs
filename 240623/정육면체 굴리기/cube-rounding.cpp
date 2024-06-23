/*
	0부터 9까지의 임의의 숫자가 그려진 n * m 격자판에 한 면이 1 * 1 크기인 정육면체를 놓여져 있습니다. 해당 격자판에서 정육면체를 굴리려합니다.

처음 정육면체의 각 면에는 0이 쓰여져 있고, 바닥에 있는 칸의 숫자에 따라 해당 칸과 정육면체의 숫자가 변하게 됩니다. 규칙은 다음과 같습니다.

칸에 쓰여져 있는 수가 0이면, 주사위의 바닥면에 쓰여져있는 수가 칸에 복사됩니다. 이때 정육면체의 숫자는 변하지 않습니다.

칸에 쓰여져 있는 수가 0이 아니면 칸에 쓰여져있는 수가 정육면체 바닥면으로 복사되며, 해당 칸의 수는 0이 됩니다.

정육면체는 격자판 밖으로 이동할 수 없습니다. 만약 바깥으로 이동시키려고 하는 시도가 있을 때, 해당 시도를 무시하며 출력도 하지 않습니다.

아래의 그림과 같이 숫자가 주어질 때 남쪽 - 남쪽 - 남쪽 - 동쪽 - 동쪽 - 북쪽 - 서쪽 - 서쪽 - 남쪽으로 이동하면 다음과 같이 변합니다.

해석: 
1. 처음 정육면체의 각 면에는 0
2. 주사위 0 -> 바닥 ->주사위 흡수, 바닥 0
3. 바닥 0 -> 주사위 숫자가 흡수
4. 격자판 밖 x -> 무시
*/



/*
입력 예시 
3 3 0 0 9 판의 세로 크기 n, 가로 크기 m, 정육면체의 처음 위치 x, y, 그리고 굴리기 횟수 k가 공백을 사이에 두고 주어집니다.
0 1 2
3 4 5
6 7 8
4 4 4 1 1 3 2 2 4

*/
#include<iostream>
#include<vector>

using namespace std;
int n, m;
class INFO {
public:
	int x, y;
	int playNum = 0;
	// 동서 북남
	int dice[6] = { 0, };
	INFO(int ix =0, int iy=0) : x(ix),y(iy)
	{}
};
INFO cube(0,0);
int map[21][21];

void Simulate();

typedef enum {
	enumRight,
	enumLeft,
	enumUp,
	enumDown,
	enumPos,
	enumLast,
}Cube;
Cube enumCube = enumUp;
bool InRange(int x, int y)
{
	return x >= 0 and x < n and y >= 0 and y < m;
}
int main()
{
	cin >> n >> m >> cube.y >> cube.x >> cube.playNum;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	Simulate();

}
void Move(Cube dir) {
	//Pos,동,서,북,남
	int tempCube[6];
	copy(begin(cube.dice), end(cube.dice), begin(tempCube));
	
	switch (dir) {
	case enumRight:// 북,남 그대로 
		cube.dice[0] = tempCube[1];
		cube.dice[1] = tempCube[5];
		cube.dice[2] = tempCube[0];
		cube.dice[5] = tempCube[2];
		break;
	case enumLeft: // 북,남 그대로
		cube.dice[0] = tempCube[2];
		cube.dice[1] = tempCube[0];
		cube.dice[2] = tempCube[5];
		cube.dice[5] = tempCube[1];
		break;
	case enumUp://동 서 그대로
		cube.dice[0] = tempCube[4];
		cube.dice[3] = tempCube[0];
		cube.dice[4] = tempCube[5];
		cube.dice[5] = tempCube[3];
		break;
	case enumDown:
		cube.dice[0] = tempCube[3];
		cube.dice[3] = tempCube[5];
		cube.dice[4] = tempCube[0];
		cube.dice[5] = tempCube[4];
		break;
	}
}
void View()
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << map[i][j] << " ";
		}cout << endl;
	}cout << endl;
}
void Simulate()
{
	/*
	* 1. 처음 정육면체의 각 면에는 0
	2. 주사위 0 -> 바닥 ->주사위 흡수, 바닥 0
	3. 바닥 0 -> 주사위 숫자가 흡수
	4. 격자판 밖 x -> 무시
	*/

	// 동서 북남
	const int dx[4] = { 1,-1,0,0 };
	const int dy[4] = { 0,0,-1,1 };
	for (int i = 0; i < cube.playNum; i++)
	{
		int dir;
		cin >> dir;
		dir -= 1;

		int nx = cube.x + dx[dir];
		int ny = cube.y + dy[dir];
		if (InRange(ny, nx))
		{
			Move((Cube)dir);
			//1. 위치 설정
			cube.x = nx;
			cube.y = ny;
			//	2. 바닥 == 0, 주사위 숫자 복사
			if (map[cube.y][cube.x] == 0)
			{
				map[cube.y][cube.x]		= cube.dice[0];
			}
			//	3.  바닥 != 0, 주사위로 흡수
			else if (map[cube.y][cube.x] != 0)
			{
				cube.dice[0]			= map[cube.y][cube.x];
				map[cube.y][cube.x]		= 0;
			}
				
			
			cout << cube.dice[5] << endl;
		}
		//cout <<"방향: " << dir << endl;		
		//for (int i = 0; i < 6; i++) cout << cube.dice[i] << " ";
		//cout << endl;
		//View();

		
	}
	

}