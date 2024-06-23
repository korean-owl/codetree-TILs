#include<iostream>
#include<queue>
using namespace std;

struct INFO {
	int rx, ry, bx, by, count;
};
INFO start; //시작 위치
char map[12][12]; //맨끝개행문자
int n, m;
int answer;
bool CanGo(int x, int y) {
	return map[x][y] != '#' && map[x][y] != 'O';
}

void InPut() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'R') {
				start.rx = j;
				start.ry = i;
			}
			else if (map[i][j] == 'B') {
				start.bx = j;
				start.by = i;
			}
		}
	start.count = 0;
}

int BFS() {
	const int dy[] = { -1, 1, 0, 0 };
	const int dx[] = { 0, 0, -1, 1 };

	int visited[10][10][10][10] = { 0, };
	queue<INFO> q;
	q.push(start);
	visited[start.ry][start.rx][start.by][start.bx] = true;

	int ans = -1;
	while (!q.empty()) {
		INFO cur = q.front();
		q.pop();

		if (cur.count > 10) break;
		if (map[cur.ry][cur.rx] == 'O' && map[cur.by][cur.bx] != 'O') {
			ans = cur.count;
			break;
		}

		for (int i = 0; i < 4; i++) {
			int nry = cur.ry;
			int nrx = cur.rx;
			int nby = cur.by;
			int nbx = cur.bx;

			while (true) {
				if (CanGo(nry + dy[i], nrx + dx[i])) {
					nry += dy[i];
					nrx += dx[i];
				}
				else {
					if (map[nry + dy[i]][nrx + dx[i]] == '#') {
						nry -= dy[i];
						nrx -= dx[i];
					}
					break;
				}
			}

			while (true) {
				if (CanGo(nby + dy[i], nbx + dx[i])) {
					nby += dy[i];
					nbx += dx[i];
				}
				else {
					if (map[nby + dy[i]][nbx + dx[i]] == '#') {
						nby -= dy[i];
						nbx -= dx[i];
					}
					break;
				}
			}

			if (nry == nby && nrx == nbx) {
				if (map[nry][nrx] != 'O') {
					int redDist = abs(nrx - cur.rx) + abs(nry - cur.ry);
					int blueDist = abs(nbx - cur.bx) + abs(nby - cur.by);
					if (blueDist > redDist) {
						nby -= dy[i];
						nbx -= dx[i];
					}
					else {
						nrx -= dy[i];
						nry -= dx[i];
					}
				}
			}

			if (!visited[nry][nrx][nby][nbx]) {
				visited[nry][nrx][nby][nbx] = true;
				INFO next;
				next.ry = nry;
				next.rx = nrx;
				next.by = nby;
				next.bx = nbx;
				next.count = cur.count + 1;
				q.push(next);
			}
		}
	}
	return ans;
}

int main() {
	InPut();
	answer = BFS();
	cout << answer << endl;
	return 0;
}