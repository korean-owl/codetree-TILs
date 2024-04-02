#include <iostream>

using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int dp[1001];
    int n;
    cin>>n;

    dp[1]=0;
    dp[2]=1;
    dp[3]=1;
    for(int i=4;i<n;i++){
        dp[i]=dp[i-1]+dp[i-2];
    }

    cout<<dp[n];

    return 0;
}