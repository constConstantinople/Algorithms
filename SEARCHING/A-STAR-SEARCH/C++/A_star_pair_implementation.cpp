#include <iostream>
#include <queue>
#include <vector>
#include <numeric>
#include <limits>
#include <utility>
#include <cmath>
using namespace std;
void AstarSearch(int start_row, int start_col, int end_row, int end_col, vector<vector<int>>& visited){
    int row=visited.size(), col=visited[0].size();
	std::vector<std::vector<pair<int,int>>> parent(row, std::vector<pair<int, int>>(col, {-1,-1}));
	std::vector<std::vector<double>> global_val(row, std::vector<double>(col, numeric_limits<double>::infinity()));
	std::vector<std::vector<double>> local_val(row, std::vector<double>(col, numeric_limits<double>::infinity()));
	auto comp = [&, global_val](pair<int, int>& a, pair<int,int>& b){
		return global_val[a.first][a.second] > global_val[b.first][b.second];
	};
	auto distance = [](pair<int, int> a, pair<int, int> b){
		return sqrt((double)(a.first-b.first)*(a.first-b.first) + (double)(a.second-b.second)*(a.second-b.second));
	};
	priority_queue<pair<int, int>, std::vector<pair<int, int>>, decltype(comp)> q(comp);
	if(!visited[start_row][start_col]){
		q.push({start_row, start_col});
		global_val[start_row][start_col]=distance({start_row, start_col}, {end_row, end_col});
		local_val[start_row][start_col]=0;
	}
	while(!q.empty()){
		auto curr=q.top();
		q.pop();
		visited[curr.first][curr.second]=true;
		if(curr.first > 0 && !visited[curr.first-1][curr.second]){
			q.push({curr.first-1, curr.second});
			auto newLocal = local_val[curr.first][curr.second] + distance(curr, {curr.first-1, curr.second});
			if(newLocal < local_val[curr.first-1][curr.second]){
				local_val[curr.first-1][curr.second]=newLocal;
				parent[curr.first-1][curr.second]=curr;
				global_val[curr.first-1][curr.second]=newLocal + distance({curr.first-1, curr.second}, {end_row, end_col});
			}
		}if(curr.first < row-1 && !visited[curr.first+1][curr.second]){
			q.push({curr.first+1, curr.second});
			auto newLocal = local_val[curr.first][curr.second] + distance(curr, {curr.first+1, curr.second});
			if(newLocal < local_val[curr.first+1][curr.second]){
				local_val[curr.first+1][curr.second]=newLocal;
				parent[curr.first+1][curr.second]=curr;
				global_val[curr.first+1][curr.second]=newLocal + distance({curr.first+1, curr.second}, {end_row, end_col});
			}
		}if(curr.second > 0 && !visited[curr.first][curr.second-1]){
			q.push({curr.first, curr.second-1});
			auto newLocal = local_val[curr.first][curr.second] + distance(curr, {curr.first, curr.second-1});
			if(newLocal < local_val[curr.first][curr.second-1]){
				local_val[curr.first][curr.second-1]=newLocal;
				parent[curr.first][curr.second-1]=curr;
				global_val[curr.first][curr.second-1]=newLocal + distance({curr.first, curr.second-1}, {end_row, end_col});
			}
		}
		if(curr.second < col-1 && !visited[curr.first][curr.second+1]){
			q.push({curr.first, curr.second+1});
			auto newLocal = local_val[curr.first][curr.second] + distance(curr, {curr.first, curr.second+1});
			if(newLocal < local_val[curr.first][curr.second+1]){
				local_val[curr.first][curr.second+1]=newLocal;
				parent[curr.first][curr.second+1]=curr;
				global_val[curr.first][curr.second+1]=newLocal + distance({curr.first, curr.second+1}, {end_row, end_col});
			}
		}
	}
	if(!visited[end_row][end_col] || parent[end_row][end_col]==make_pair(-1,-1)){
		cout<<"Unable to reach target"<<endl;
	}else{
		cout<<"path: "<<endl;
		pair<int,int> temp={end_row, end_col};
		while(temp!=make_pair(-1,-1)){
			cout<<"("<<temp.first<<", "<<temp.second<<")"<<endl;
			temp=parent[temp.first][temp.second];
		}
	}
}
void initialization(int row, int col, int start_row, int start_col, int end_row, int end_col, int numObstacle){
	vector<vector<int>> visited(row, vector<int>(col, false));
    cout<<"Chosen obstacles: "<<endl;
	for(int i=0;i<numObstacle;i++){
		int rand_row=rand()%row, rand_col=rand()%col;
		visited[rand_row][rand_col]=true;
        cout<<"("<<rand_row<<", "<<rand_col<<")"<<endl;
	}
	AstarSearch(start_row, start_col, end_row, end_col,visited);
}
int main(){
	int row=15, col=15;
	int numObstacle=5;
	int start_row=0, start_col=0;
	int end_row=row-1, end_col=col-1;
	initialization(row, col, start_row, start_col, end_row, end_col, numObstacle);
}