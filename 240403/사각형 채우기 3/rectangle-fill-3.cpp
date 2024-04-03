#include <iostream>

using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int dp[1001];
    int n;
    cin>>n;

    dp[0]=0;
    dp[1]=2;
    dp[2]=6;
    for (int i=2 ; i <=n ; i++){
        dp[i] = (dp[i-1]*2 + dp[i-2] *3);
            for(int j=i-3; j>=0;j++){
                dp[i] +=dp[j] *2;
            }
        dp[i] %= 1000000007;
    }
    cout<<dp[n];

    return 0;
}