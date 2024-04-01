#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

vector<pair<int, int>>block;
vector<pair<int, int>>selectBlock;
queue<tuple<int, int, int>>q1;

pair<int, int>startPoint;
pair<int, int>endPoint;


int n, k;
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
int answer = 99999;

bool arr[101][101];
bool board[101][101];
void Show() {
    cout << "Arr" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }cout << endl;

    }cout << endl;
    cout << endl;

    cout << "Board" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }cout << endl;

    }cout << endl;
    cout<<"Answer: " << answer << endl;
}
bool CanGo(int x, int y) {
    return x >= 0 && x < n&& y >= 0 && y < n&& board[x][y] == false && arr[x][y]==0;
}

void Init() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = false;
        }
    }
   
}

void BFS() {
    while (!q1.empty()) {
        int curr_x, curr_y, curr_cnt;
        tie(curr_x, curr_y, curr_cnt) = q1.front();
        q1.pop();
        if (curr_x == endPoint.first && curr_y == endPoint.second) {
            if (answer > curr_cnt)
                answer = curr_cnt;
            
        }
        for (int i = 0; i < 4; i++) {
            int nx = curr_x + dx[i], ny = curr_y + dy[i];
            if (CanGo(nx, ny)) {
                board[nx][ny] = true;
                q1.push({ nx,ny,curr_cnt + 1 });
            }
        }


    }
}
void Simaulte() {

    if (CanGo(startPoint.first, startPoint.second)) {
        board[startPoint.first][startPoint.second] = true;
        q1.push({ startPoint.first,startPoint.second,0 });
        BFS();
    }
    Init();
  //  Show();

}

void BackTraking(int cnt) {
    if (cnt == k) {
        /*for (int i = 0; i < selectBlock.size(); i++) {
            cout<<i<<"번째 좌표 : " << selectBlock[i].first << ", " << selectBlock[i].second << endl;
            arr[selectBlock[i].first][selectBlock[i].second] = 0;
        }
        */
        Simaulte();
      /*  for (int i = 0; i < selectBlock.size(); i++) {
            arr[selectBlock[i].first][selectBlock[i].second] = 1;
        }
      */  
    }
    else {
        for (int i = cnt; i < block.size(); i++) {
            //selectBlock.push_back(block[i]);
            arr[block[i].first][block[i].second] = 0;
            BackTraking(cnt + 1);
            arr[block[i].first][block[i].second] = 1;
            //selectBlock.pop_back();
        }
    }
}

int main() {
    // 여기에 코드를 작성해주세요.
    cin >> n >> k;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 1) {
                block.push_back({ i,j });
            }
        }
    cin >> startPoint.first >> startPoint.second;
    cin >> endPoint.first >> endPoint.second;
    startPoint.first = startPoint.first - 1;
    startPoint.second -= 1;
    endPoint.first -= 1;
    endPoint.second-=1;
    BackTraking(0);
    if (answer == 99999)
        cout << -1;
    else
        cout << answer;
    return 0;
}