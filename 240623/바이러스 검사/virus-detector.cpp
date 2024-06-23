/*
  2015년 상반기 삼성전자 기출

  바이러스의 확산을 막기 위해 총 n개의 식당에 있는 고객들의 체온을 측정하고자 합니다. 체온을 측정하는 검사자는 검사팀장과 검사팀원으로 나뉘어집니다. 팀장과 팀원이 검사할 수 있는 고객의 수가 다르며, 한 가게당 팀장은 오직 한 명, 팀원은 여러명 있을 수 있습니다. 하지만 가게당 팀장 한 명은 무조건 필요합니다. 가게에 검사팀원만 존재하는 경우는 있을 수 없습니다. 팀장이든 팀원이든 담당한 가게에 대해서만 검사합니다.

n개의 식당 고객들의 체온을 측정하기 위해 필요한 검사자 수의 최솟값을 구하는 프로그램을 작성해주세요.

해석:
  1. 검사자는 팀장,팀원
  2. 가게당 팀장은 Only 1명
  3. 가게당 필수 팀장 1명 이후 팀원 존재 
  4. 담당한 가게에서만 검사 진행

입력 형식
첫째 줄에는 식당의 수 n이 주어집니다.

둘째 줄에는 각 식당에 있는 고객의 수가 공백을 사이에 두고 주어집니다.

셋째줄에는 검사팀장이 검사할 수 있는 최대 고객 수와 검사팀원이 검사할 수 있는 최대 고객 수가 공백을 사이에 두고 주어집니다.

1 ≤ n ≤ 1,000,000

1 ≤ (각 식당에 있는 고객의 수) ≤ 1,000,000

1 ≤ (팀장 혹은 팀원 한 명이 검사 가능한 최대 고객의 수) ≤ 1,000,000

출력 형식
n개의 식당의 고객들을 모두 검사하기 위한 검사자의 최소의 수를 출력하세요
*/
#include<iostream>
#include<vector>

using namespace std;
int storeNum;
int leaderScanNum, followerScanNum;
vector<int>store;
int answer;
void Input()
{
  cin>>storeNum;
  for(int i=0; i < storeNum; i++)
  {
    int client;
    cin>>client;
    store.push_back(client);
  }

  cin>>leaderScanNum >> followerScanNum;
}

void Simulate()
{
  for(int i=0; i < store.size(); i++)
  {
    if(store[i] > leaderScanNum)
    {
      answer++;
      store[i]-=leaderScanNum;
      while(true)
      {
        if(store[i] < 0)
        {
          break;
        }

        store[i] -= followerScanNum;
        answer++;
      }
    }
    else
    {
      answer++;
    }
  }


}


int main()
{
	Input();
	Simulate();

	cout << answer;

	return 0;
}