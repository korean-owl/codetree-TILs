#include <iostream>
#include <queue>
#include <vector>
using namespace std;


int arr[101][101];
bool board[101][101];
vector<pair<int,int>>wall;
vector<pair<int,int>>v1;

//bool 
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
pair<int,int> position[2];
int n, k;
int answer=100001;
bool InRange(int x, int y){
    return x>=0 && x<n && y>= 0 &&y<n  && board[x][y]==false ;
}
void ShowArr(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<arr[i][j]<<" ";
        }cout<<endl;
    }cout<<endl;
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<board[i][j]<<" ";
        }cout<<endl;
    }cout<<endl;
}
int Simualte(){
    int sum=0;
    //ShowArr();
    
    queue<pair<int,int>>q1;

    if(board[position[0].first][position[0].second] ==0 ){
        board[position[0].first][position[0].second] =true;
        q1.push({position[0].first,position[0].second});

        while(!q1.empty()){
            int curr_x= q1.front().first, curr_y = q1.front().second;
            

            q1.pop();
            
            for(int i=0;i<4;i++){
                int nx=curr_x+dx[i], ny=curr_y+dy[i];
                if(InRange(nx,ny) &&arr[nx][ny] !=1){
                    board[nx][ny]=true;
                    sum++;
                    q1.push({nx,ny});
                }
            }
            
            
        }
        //cout<<sum<<endl;
      
        return sum+1;
        
        
       

    }
    return 0;
}

void Set(){
    for(int i=0;i<n;i++)
        for(int j=0; j<n;j++)
            board[i][j]=false;
}
void BackTracking(int num, int curr){
    if(curr == num){
        Set();
        
        int sum=Simualte();
        
        //cout<<sum<<endl;
        //ShowArr();
       
        if(sum!=0 && answer>sum  && board[position[1].first][position[1].second] == true ){
            cout<<"%%%%%%%%%%%%%%%"<<endl<<sum<<endl;
            //ShowArr();
            answer=sum;
        }
            
            
    }
    else{
        for(int i=curr;i<wall.size();i++){
            //v1.push_back({wall[i].first,wall[i].second});
            arr[wall[i].first][wall[i].second]=0;
            BackTracking(n,curr+1);
            arr[wall[i].first][wall[i].second]=1;
            //v1.pop_back();
        }
    }
}

int main() {

    cin>>n>>k;

    for(int i=0; i<n;i++)
        for(int j=0;j<n;j++){
            cin>>arr[i][j];
            if(arr[i][j]==1){
                wall.push_back({i,j});
            }
        }

    cin>>position[0].first>>position[0].second >> position[1].first>>position[1].second;
    //cout<<"#####"<<endl;
    for(int i=0;i<wall.size();i++){
        //cout<<"wall "<<i+1<<": "<<wall[i].first<<","<<wall[i].second<<endl;;
    }//cout<<endl;
    //cout<<wall.size()<<"@@@"<<endl;
    BackTracking(k,0);

    if(answer ==10001 )
        cout<<-1;
    else
        cout<<answer;

    return 0;
}