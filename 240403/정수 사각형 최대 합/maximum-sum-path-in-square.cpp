#include <iostream>
using namespace std;
long arr[101][101]; 
long dp[101][101]; 
int n;

void Init(){
    dp[0][0]=arr[0][0];
    for(int i=1;i<n;i++){
        dp[0][i]=dp[0][i-1]+arr[0][i];
        dp[i][0]=dp[i-1][0]+arr[i][0];
    }
}
void show(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<dp[i][j]<<" ";
        }cout<<endl;
    }cout<<endl;
    cout<<endl;
}
int main() {
   
    cin>>n;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>arr[i][j];
        }
    }

    Init();

    for(int i=1; i<n; i++){
        for(int j=1; j<n; j++){
            dp[i][j] = max(dp[i-1][j],dp[i][j-1])+arr[i][j];
        }
    }
    //show();
    cout<<dp[n-1][n-1];

    // 여기에 코드를 작성해주세요.
    return 0;
}