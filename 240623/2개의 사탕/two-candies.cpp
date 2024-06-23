#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

struct INFO {
    int rx, ry, bx, by, count;
};
INFO start; // 시작 위치
char map[10][11]; // 맨 끝 개행 문자 포함
int n, m;
int answer;

bool CanGo(int x, int y) {
    return map[x][y] != '#' && map[x][y] != '0';
}

void InPut() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
            if (map[i][j] == 'R') {
                start.ry = i;
                start.rx = j;
            } else if (map[i][j] == 'B') {
                start.bx = i;
                start.by = j;
            }
        }
    }
    start.count = 0;
}

int BFS() {
    const int dy[] = {-1, 1, 0, 0};
    const int dx[] = {0, 0, -1, 1};

    bool visited[10][10][10][10] = {false};
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
            int next_ry = cur.ry;
            int next_rx = cur.rx;
            int next_by = cur.by;
            int next_bx = cur.bx;

            // red 구슬 한 방향으로 이동
            while (true) {
                if (map[next_ry][next_rx] != '#' && map[next_ry][next_rx] != 'O') {
                    next_ry += dy[i];
                    next_rx += dx[i];
                } else {
                    if (map[next_ry][next_rx] == '#') {
                        next_ry -= dy[i];
                        next_rx -= dx[i];
                    }
                    break;
                }
            }

            // blue 구슬 한 방향으로 이동
            while (true) {
                if (map[next_by][next_bx] != '#' && map[next_by][next_bx] != 'O') {
                    next_by += dy[i];
                    next_bx += dx[i];
                } else {
                    if (map[next_by][next_bx] == '#') {
                        next_by -= dy[i];
                        next_bx -= dx[i];
                    }
                    break;
                }
            }

            // red와 blue가 겹칠 경우
            if (next_ry == next_by && next_rx == next_bx) {
                if (map[next_ry][next_rx] != 'O') {
                    int red_dist = abs(next_ry - cur.ry) + abs(next_rx - cur.rx);
                    int blue_dist = abs(next_by - cur.by) + abs(next_bx - cur.bx);

                    if (blue_dist > red_dist) {
                        next_by -= dy[i];
                        next_bx -= dx[i];
                    } else {
                        next_ry -= dy[i];
                        next_rx -= dx[i];
                    }
                }
            }

            if (!visited[next_ry][next_rx][next_by][next_bx]) {
                visited[next_ry][next_rx][next_by][next_bx] = true;
                INFO next = {next_rx, next_ry, next_bx, next_by, cur.count + 1};
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