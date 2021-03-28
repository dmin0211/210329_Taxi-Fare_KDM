#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

int edgePriority[301][301];

void swap(int &node1, int &node2){
  if(node1>node2){
    int temp=node1;
    node1=node2;
    node2=temp;
  }
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
  int answer = 0;
  int node1, node2;
  set<int> nodeExist;
  fill(&edgePriority[0][0],&edgePriority[300][300]+1,1000001);
  for(int i=0;i<fares.size();i++){
    node1=fares[i][0];
    node2=fares[i][1];
    nodeExist.insert(node1);
    nodeExist.insert(node2);
    edgePriority[node1][node2]=fares[i][2];
    edgePriority[node2][node1]=fares[i][2];
  }
  for(auto iterCenter=nodeExist.begin();iterCenter!=nodeExist.end();iterCenter++){
    for(auto iterFirst=nodeExist.begin();iterFirst!=nodeExist.end();iterFirst++){
      for(auto iterEnd=iterFirst;iterEnd!=nodeExist.end();iterEnd++){
        node1=*iterFirst;
        node2=*iterEnd;
        int center=*iterCenter;
        if(edgePriority[node1][center]+edgePriority[center][node2]<edgePriority[node1][node2]&&node1!=node2){
          edgePriority[node1][node2]=edgePriority[node1][center]+edgePriority[center][node2];
          edgePriority[node2][node1]=edgePriority[node1][center]+edgePriority[center][node2];
        }
      }
    }
  }
  answer=edgePriority[s][a]+edgePriority[s][b];
//  for(int i=1;i<=6;i++){
//    for(int j=1;j<=6;j++){
//      cout<<edgePriority[i][j]<<"\t";
//    }cout<<endl;
//  }
  int temp;
  for(auto iter=nodeExist.begin();iter!=nodeExist.end();iter++){
    node1=*iter;
    if(node1==a){
      temp=edgePriority[a][s]+edgePriority[a][b];
    }else if(node1==b){
      temp=edgePriority[b][s]+edgePriority[b][a];
    }else{
      temp=edgePriority[s][node1]+edgePriority[node1][a]+edgePriority[node1][b];
    }
    answer=min(answer,temp);
  }
  return answer;
}

int main(){
  vector<vector<int>> inputV={{2, 6, 6}, {6, 3, 7}, {4, 6, 7}, {6, 5, 11}, {2, 5, 12}, {5, 3, 20}, {2, 4, 8}, {4, 3, 9}};
  solution(6,4,5,6,inputV);

}