#include <queue>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> vStudent;
int board[51][51];
int idxArr[51][51];
int dx[4] = { 0, 1, -1, 0 };
int dy[4] = { 1, 0, 0, -1 };

bool InRange(const int x, const int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

vector<pair<int, int>> FindMaxFriend(vector<int> const& student) {
    vector<pair<int, int>> vPos;
    int maxNum = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int num = 0;
            if (board[i][j] != 0) continue;
            for (int m = 0; m < 4; ++m) {
                int nx = i + dx[m];
                int ny = j + dy[m];

                if ((InRange(nx, ny) == false)) continue;
                for (int k = 1; k < 5; ++k) {
                    if (student[k] == board[nx][ny]) ++num;
                }
            }
            if (num == maxNum) {
                vPos.push_back({ i, j });
            }
            else if (num > maxNum) {
                maxNum = num;
                vPos.clear();
                vPos.push_back({ i, j });
            }
        }
    }

    return vPos;
}

vector<pair<int, int>> FindSeatClean(const vector<pair<int, int>>& Pos) {
    vector<pair<int, int>> vRet;
    int cnt = 0;

    for (int i = 0; i < Pos.size(); ++i) {
        int iTemp = 0;
        for (int j = 0; j < 4; ++j) {
            int nx = Pos[i].first + dx[j];
            int ny = Pos[i].second + dy[j];

            if ((InRange(nx, ny) == false) || (board[nx][ny] != 0)) continue;
            ++iTemp;
        }
        if (iTemp == cnt) {
            vRet.push_back(Pos[i]);
        }
        else if (iTemp > cnt) {
            vRet.clear();
            vRet.push_back(Pos[i]);
            cnt = iTemp;
        }
    }

    return vRet;
}

pair<int, int> SelectSeat(const vector<pair<int, int>>& Pos) {
    pair<int, int> pRet = Pos[0];

    // 우선순위 : 행 , 열 -> 가로, 세로
    for (int i = 0; i < Pos.size(); ++i) {
        if ((Pos[i].first < pRet.first) ||
            ((Pos[i].second == pRet.second) && (Pos[i].first < pRet.second))) {
            pRet = Pos[i];
        }
    }

    return pRet;
}

void Simulate(vector<int>& student, const int idx) {
    // 격자를 벗어나지 않는 4방향으로 인접한 칸 중 앉아있는 좋아하는 친구의 수가 가장 많은 위치로 갑니다.
    vector<pair<int, int>> vPos = FindMaxFriend(student);

    // 만약 1번 조건을 만족하는 칸의 위치가 여러 곳이라면, 그 중 인접한 칸 중 비어있는 칸의 수가 가장 많은 위치로 갑니다.
    if (vPos.size() > 1) {
        vector<pair<int, int>> vTemp = FindSeatClean(vPos);
        vPos.clear();
        vPos.assign(vTemp.begin(), vTemp.end());
    }

    // 만약 2번 조건까지 동일한 위치가 여러 곳이라면, 그 중 행 번호가 가장 작은 위치로 갑니다.
    // 만약 3번 조건까지 동일한 위치가 여러 곳이라면, 그 중 열 번호가 가장 작은 위치로 갑니다.
    if (vPos.size() > 1) {
        pair<int, int> pRet = SelectSeat(vPos);
        board[pRet.first][pRet.second] = student[0];
        idxArr[pRet.first][pRet.second] = idx;
    }
    else {
        board[vPos[0].first][vPos[0].second] = student[0];
        idxArr[vPos[0].first][vPos[0].second] = idx;
    }
}

int main() {
    cin >> n;

    for (int i = 0; i < n * n; ++i) {
        vector<int> vTemp;

        for (int m = 0; m < 5; ++m) {
            int iTemp;
            cin >> iTemp;
            vTemp.push_back(iTemp);
        }
        vStudent.push_back(vTemp);
    }

    for (int i = 0; i < n * n; ++i) {
        Simulate(vStudent[i], i);
    }

    int iAns = 0;
  

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int cnt = 0;
            for (int m = 0; m < 4; ++m) {
                int nx = i + dx[m];
                int ny = j + dy[m];

                if (InRange(nx, ny) == false) continue;
                for (int k = 1; k < 5; ++k) {
                    if (board[nx][ny] == vStudent[idxArr[i][j]][k]) ++cnt;
                }
            }
            switch (cnt) {
            case 0: iAns += 0; break;
            case 1: iAns += 1; break;
            case 2: iAns += 10; break;
            case 3: iAns += 100; break;
            case 4: iAns += 1000; break;
            }
        }
    }

    cout << iAns;

    return 0;
}