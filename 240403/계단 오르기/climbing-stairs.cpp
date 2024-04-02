#include <iostream>

using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int dp[1001];
    int n;
    cin>>n;
    dp[0]=1;
    dp[1]=0;
    dp[2]=1;
    dp[3]=1;


    for(int i=4;i<=n;i++){
    //dp[i]로 올 수 있는 경우는 2계단 아래와 3계단 아래일때만 가능하다.
        dp[i]=(dp[i-2]+dp[i-3])% 10007;
    }


    cout<<dp[n];

    return 0;
}