#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
using namespace std;

// 2272027 전자전기공학 심희윤

const int WIDTH = 20;
const int HEIGHT = 17;

// 미로 정의 (0: 길, 1: 벽)
int maze[HEIGHT][WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1},
    {1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// 시작점과 종료점
pair<int, int> start_point = {1, 1};
pair<int, int> end_point = {15, 18}; 

bool visited[HEIGHT][WIDTH] = {false};


// DFS 재귀 함수
bool dfs_recursive(int x, int y, vector<pair<int, int>>& path) {

    // 미로 범위 체크 및 방문 체크
    if(x < 0 || x >= HEIGHT || y < 0 || y >= WIDTH || maze[x][y] == 1 || visited[x][y]){
        return false;
    }

    // 현재 위치를 경로에 추가하고 방문 표시
    path.push_back(make_pair(x, y));
    visited[x][y] = true;

    // 도착 지점에 도달한 경우
    if(end_point.first == x && end_point.second == y){
        return true;
    }

    // 동서남북 순서로 이동할 좌표 설정 및 재귀 호출
    int dir[2][4] = {{0, 0, 1, -1}, {1, -1, 0, 0}}; // EAST -> WEST -> SOUTH -> NORTH 순으로 순회
    
    for(int i = 0; i < 4; i++){
        int dx = x + dir[0][i];
        int dy = y + dir[1][i];

        if(dfs_recursive(dx, dy, path))
            return true;
        
    }

    // 경로가 아니면 되돌아가면서 제거
    path.pop_back();
    return false;
}


// visited 배열 초기화 함수
void reset_visited() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            visited[i][j] = false;
        }
    }
}

int main() { 

    // 재귀를 이용한 DFS 경로 탐색
    vector<pair<int, int>> path_recursive;
    reset_visited();
    
    if (dfs_recursive(start_point.first, start_point.second, path_recursive)) {
        cout << "\n재귀를 이용한 DFS 경로를 찾았습니다! 경로는 다음과 같습니다:\n";
        for (const auto& [x, y] : path_recursive) {
            cout << "(" << x << ", " << y << ") ";
        }
        cout << endl;
        
        // 경로 txt 파일로 저장
        ofstream path_file("path_recursive.txt");
        for (const auto& [x, y] : path_recursive) {
            path_file << x << " " << y << endl;
        }
        path_file.close();
        
    } else {
        cout << "재귀를 이용한 DFS 경로가 없습니다." << endl;
    }

    return 0;
}
