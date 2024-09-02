#include <iostream>
#include <algorithm>
using namespace std;

int arr[101][101];
int dp[101][101];
int main() {
    // 여기에 코드를 작성해주세요.
    int n;
    cin>>n;

    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            cin>>arr[i][j];
        }
    }

    dp[0][n - 1] = arr[0][n - 1];
    for(int i=1;i<n;++i)
    {
        dp[i][n-1] = dp[i-1][n-1] + arr[i][n-1] ;
    }
    for(int j = n - 2; j >= 0; j--)
        dp[0][j] = dp[0][j + 1] + arr[0][j];

    for(int i=1;i<n;++i)
    {
        for(int j=n-2; j>=0 ;--j)
        {
           dp[i][j] = min(dp[i-1][j],dp[i][j+1]) + arr[i][j];
        }
    }


    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
        //    cout<<dp[i][j]<<" ";
        }//cout<<endl;
    }//cout<<endl;
    
    cout<<dp[n-1][0];

        return 0;
}