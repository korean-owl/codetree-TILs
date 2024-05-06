#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

/*
문제 설명

1. 검사 가능 인원
팀장은 오직 한명
팀원은 여러명 

2. 가게에 팀장은 필수

3. 담당한 가게에서만 검사 가능


---------------------
입출력
1. 식당 수 
2. 고객의 수
3. 검색 가능 팀장 최대, 팀원 최대
*/
long storeNum;
long leader, follwer;
vector<int>store;
long answer;
void Input()
{
	cin >> storeNum;
	for (int i = 0; i < storeNum; i++)
	{
		long people;
		cin >> people;
		store.push_back(people);
	}
	cin >> leader >> follwer;
}

void Simulate()
{
	for (int i = 0; i < storeNum; i++) {
		if (store[i] == 0)
		{
			continue;
		}
		else // people in store > 0
		{
			answer++;
			store[i] -= leader;
			if (store[i] > 0)
			{
				int plusPeople = store[i] / follwer;

				if (store[i] > plusPeople * follwer)
				{
					answer += (plusPeople + 1);
				}
				else
				{
					answer += plusPeople;
				}
			}
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