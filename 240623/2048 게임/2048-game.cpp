#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n = 4;

typedef enum {
    enumRight,
    enumDown,
    enumLeft,
    enumUp,
} enumDir;

class INFO {
public:
    int cnt = 0;
    enumDir dir = enumRight;
    int map[4][4] = { 0 };
    INFO() {}
    INFO(enumDir idir) : dir(idir) {}
};

INFO start;
queue<INFO> q1;

int CheckMaxNum(INFO& info, int answer) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            answer = max(answer, info.map[i][j]);
        }
    }
    return answer;
}

void Move(INFO& info) {
    switch (info.dir) {
    case enumRight:
        for (int i = 0; i < n; i++) {
            int last_merge_pos = n;
            for (int j = n - 2; j >= 0; j--) {
                if (info.map[i][j] == 0) continue;
                int k = j;
                while (k + 1 < n && info.map[i][k + 1] == 0) {
                    info.map[i][k + 1] = info.map[i][k];
                    info.map[i][k] = 0;
                    k++;
                }
                if (k + 1 < n && info.map[i][k + 1] == info.map[i][k] && k + 1 < last_merge_pos) {
                    info.map[i][k + 1] *= 2;
                    info.map[i][k] = 0;
                    last_merge_pos = k + 1;
                }
            }
        }
        break;
    case enumDown:
        for (int i = 0; i < n; i++) {
            int last_merge_pos = n;
            for (int j = n - 2; j >= 0; j--) {
                if (info.map[j][i] == 0) continue;
                int k = j;
                while (k + 1 < n && info.map[k + 1][i] == 0) {
                    info.map[k + 1][i] = info.map[k][i];
                    info.map[k][i] = 0;
                    k++;
                }
                if (k + 1 < n && info.map[k + 1][i] == info.map[k][i] && k + 1 < last_merge_pos) {
                    info.map[k + 1][i] *= 2;
                    info.map[k][i] = 0;
                    last_merge_pos = k + 1;
                }
            }
        }
        break;
    case enumLeft:
        for (int i = 0; i < n; i++) {
            int last_merge_pos = -1;
            for (int j = 1; j < n; j++) {
                if (info.map[i][j] == 0) continue;
                int k = j;
                while (k - 1 >= 0 && info.map[i][k - 1] == 0) {
                    info.map[i][k - 1] = info.map[i][k];
                    info.map[i][k] = 0;
                    k--;
                }
                if (k - 1 >= 0 && info.map[i][k - 1] == info.map[i][k] && k - 1 > last_merge_pos) {
                    info.map[i][k - 1] *= 2;
                    info.map[i][k] = 0;
                    last_merge_pos = k - 1;
                }
            }
        }
        break;
    case enumUp:
        for (int i = 0; i < n; i++) {
            int last_merge_pos = -1;
            for (int j = 1; j < n; j++) {
                if (info.map[j][i] == 0) continue;
                int k = j;
                while (k - 1 >= 0 && info.map[k - 1][i] == 0) {
                    info.map[k - 1][i] = info.map[k][i];
                    info.map[k][i] = 0;
                    k--;
                }
                if (k - 1 >= 0 && info.map[k - 1][i] == info.map[k][i] && k - 1 > last_merge_pos) {
                    info.map[k - 1][i] *= 2;
                    info.map[k][i] = 0;
                    last_merge_pos = k - 1;
                }
            }
        }
        break;
    }
}

int BFS() {
    int ret = 0;
    while (!q1.empty()) {
        INFO curr = q1.front();
        q1.pop();

        if (curr.cnt == 5) {
            ret = max(ret, CheckMaxNum(curr, ret));
            continue;
        }

        for (int i = 0; i < 4; i++) {
            INFO Next(curr);
            Next.dir = (enumDir)i;
            Next.cnt = curr.cnt + 1;
            Move(Next);
            q1.push(Next);
        }
    }
    return ret;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> start.map[i][j];

    int answer = 0;
    for (int i = 0; i < 4; i++) {
        start.dir = (enumDir)i;
        start.cnt = 0;
        q1.push(start);
        answer = max(answer, BFS());
    }

    cout << answer;
    return 0;
}