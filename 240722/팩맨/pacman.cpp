#include<iostream>
#include<vector>
#include<queue>
#include <cstring>
using namespace std;

struct PosInfo {
	int x;
	int y;
};
struct MINFO
{
	PosInfo Pos;
	int dir;
	bool status;
	int turn = 2;
};
struct INFO {
	PosInfo pack;
	vector<MINFO>	 monster;
	queue<PosInfo>	qPackMove;

	bool visited[4][4] = { false, };
};
void View(int board[4][4])
{
	cout << "#####################" << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << board[i][j] << " ";
		}cout << endl;
	}cout << endl;
	cout << "#####################" << endl;
}
void Input(int & m, int &t , PosInfo & pack)
{
	cin >> m >> t;
	int r, c;
	cin >>r>>c;
	pack = { r-1,c-1 };
}
void MonsterCopy(vector<MINFO>& vMonster, queue<MINFO>& qEgg)
{
	for (int i = 0; i < vMonster.size(); ++i)
	{
		qEgg.push(vMonster[i]);
	}
}
bool InRange(const int x, const int y)
{
	return x >= 0 && x < 4 && y >= 0  && y < 4;
}
bool FindGhost(int x, int y, vector<MINFO>& vMonster)
{
	bool bRet = false;
	for (int i = 0; i < vMonster.size(); ++i)
	{
		bRet = ((vMonster[i].Pos.x == x) && (vMonster[i].Pos.y == y) && vMonster[i].status == false) ? true : false;
	}

	return bRet;
}
void MonsterMove(vector<MINFO>& vMonster, int(&board)[4][4], PosInfo& packMan)
{
	// ↑, ↖, ←, ↙, ↓, ↘, →, ↗ 를 의미합니다.
	int dx[8] = { -1,-1,0,1,1,1,0,-1 };
	int dy[8] = { 0,-1,-1,-1,0,1,1,1 };

	for (int i = 0; i < vMonster.size(); ++i)
	{
		bool bFlagCanGo = false;
		if (vMonster[i].status == false)
		{
			--vMonster[i].turn;
			continue;
		}
		int nx = vMonster[i].Pos.x + dx[vMonster[i].dir];
		int ny = vMonster[i].Pos.y + dx[vMonster[i].dir];
		int ndir = vMonster[i].dir;
		for (int j = 0; j < 8; ++j)
		{
			nx = vMonster[i].Pos.x + dx[ndir];
			ny = vMonster[i].Pos.y + dy[ndir];
			//몬스터 시체, 팩맨
			bool test1 = (InRange(nx, ny) == true);
			bool test2 = ((nx != packMan.x) || (ny != packMan.y));
			bool test3 = !FindGhost(nx, ny, vMonster);
				
			if (test1 && test2 && test3)
			{
				bFlagCanGo = true;
				break;
			}
			ndir = (ndir + 1) % 8;
		}
		if (bFlagCanGo == false) continue;
		--board[vMonster[i].Pos.x][vMonster[i].Pos.y];
		vMonster[i].Pos.x = nx;
		vMonster[i].Pos.y = ny; 
		vMonster[i].dir = ndir;

		
		++board[vMonster[i].Pos.x][vMonster[i].Pos.y];
	}

	return;
}
void BFS(INFO & info, int(&board)[4][4])
{	
	struct BFSINFO
	{
		PosInfo packPos;
		int point;
		queue<PosInfo>qPackMoving;
		bool visited[4][4] = { false, };
	};
	BFSINFO ret;
	ret.point = 0;
	memset(ret.visited, false, sizeof(ret.visited)); // Initialize visited array
	ret.visited[info.pack.x][info.pack.y] = true;
	ret.qPackMoving.push(info.pack);
	ret.packPos = info.pack;

	queue<BFSINFO> qInfo;
	qInfo.push(ret); // Push initial state into the queue

	//상 좌 하 우
	int dx[4] = { -1,0,1,0 };
	int dy[4] = { 0,-1,0,1 };
	while (!qInfo.empty())
	{
		BFSINFO cInfo = qInfo.front();
		qInfo.pop();
		if (cInfo.qPackMoving.size() == 4)
		{
			ret = (ret.point > cInfo.point) ? ret : cInfo;

		}
		else{

			for (int i = 0; i < 4; ++i)
			{
				BFSINFO temp;
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
						temp.visited[i][j] = cInfo.visited[i][j];

				temp.packPos = { cInfo.packPos.x + dx[i] ,cInfo.packPos.y + dy[i] };
				bool test1 = InRange(temp.packPos.x, temp.packPos.y); //== false
				if ((test1 == false)) continue;
				bool test2 = temp.visited[temp.packPos.x][temp.packPos.y]; //== false
				if ((test2 == true)) continue;
				
				if (test1 == false || test2 == true)
				{
					continue;
				}
				else {

					temp.qPackMoving = cInfo.qPackMoving;
					temp.qPackMoving.push({ temp.packPos.x, temp.packPos.y });
					temp.point = (cInfo.point + board[temp.packPos.x][temp.packPos.y]);
					temp.visited[temp.packPos.x][temp.packPos.y] = true;

					qInfo.push(temp);
				}

			}
		}
	}

	while (!ret.qPackMoving.empty())
	{
		PosInfo Posinfo = ret.qPackMoving.front();
		ret.qPackMoving.pop();

		for (int i = 0; i < info.monster.size(); ++i)
		{
			bool test1 = (info.monster[i].Pos.x == Posinfo.x) && (info.monster[i].Pos.y == Posinfo.y);
			bool test2 = info.monster[i].status;
			if ((test1) && (info.monster[i].status == true))
			{
				info.pack = Posinfo;
				info.monster[i].status = false;
				--board[Posinfo.x][Posinfo.y];
			}
		}
	}
}
void PackManMove(PosInfo& packMan, vector<MINFO>& vMonster, int(&board)[4][4])
{
	//1. Monster를 많이 만나는 순서
	//2. 이동해서 만나면 -> Monster 죽이기 
	
	INFO info = {packMan, vMonster};
	BFS(info,board);

	vMonster	= info.monster;
	packMan		= info.pack;
}
void SetBoard(int (& board)[4][4], vector<MINFO>& vMonster)
{
	for (int i = 0; i < vMonster.size(); ++i)
	{
		board[vMonster[i].Pos.x][vMonster[i].Pos.y] = (vMonster[i].status == true) ?  board[vMonster[i].Pos.x][vMonster[i].Pos.y] + 1: board[vMonster[i].Pos.x][vMonster[i].Pos.y];
	}
}
void RemoveGhost(vector<MINFO>& vMonster)
{
	for (int i = 0; i < vMonster.size(); ++i)
	{
		if (vMonster[i].turn <= 0)
		{
			vMonster.erase(vMonster.begin() + i);
		}
	}
}
void CopyComplete(queue<MINFO>qEgg, vector<MINFO>& vMonster, int(&board)[4][4])
{
	while (!qEgg.empty())
	{
		vMonster.push_back(qEgg.front());
		++board[qEgg.front().Pos.x][qEgg.front().Pos.y];
		qEgg.pop();
	}
}
void Simulate(PosInfo& packMan, vector<MINFO>& vMonster)
{
	int board[4][4] = { 0, };
	SetBoard(board, vMonster);
	//board[packMan.x][packMan.y] = -1;
	//View(board);

	//몬스터 복제 시도
	//완성
	queue<MINFO>qEgg;
	MonsterCopy(vMonster,qEgg);
	
	//몬스터 이동
	//완성
	MonsterMove(vMonster, board, packMan);
	//View(board);
	//팩맨 이동
	PackManMove(packMan, vMonster, board);

	//몬스터 시체 소멸
	RemoveGhost(vMonster);
	//몬스터 복제 완성 
	//완성
	CopyComplete(qEgg, vMonster, board);

	return;
}
void ViewData(vector<MINFO>& monster)
{
	for (int i = 0; i < monster.size(); ++i)
	{
		cout << i + 1 << "번째 몬스터 정보" << endl;
		cout << monster[i].Pos.x << ", " << monster[i].Pos.y << endl;
		cout << monster[i].dir<<endl;
		cout << monster[i].status << endl;;
	}
}
int main()
{
	int m, t;
	PosInfo packMan;
	Input(m,t, packMan);
	vector<MINFO>vMonster;

	for (int i = 0; i < m; ++i)
	{
		int direction;
		PosInfo pos;
		cin >> pos.x >> pos.y>> direction;
		vMonster.push_back({ {pos.x-1,pos.y-1}, (direction-1),true });
	}

	for (int i = 0; i < t; ++i)
	{
		//ViewData(vMonster);
		Simulate(packMan, vMonster);
	}

	int ans = 0;
	for (int i = 0; i < vMonster.size(); ++i)
	{
		ans = (vMonster[i].status == true) ? (ans + 1) : ans;
	}

	//cout <<"남은 몬스터 :" << ans<<endl;
	cout << ans;
	return 0;
}