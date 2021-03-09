#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
//Moroti Iulia 1231A ADC HW3
using namespace std;

void printPath(pair<int,int> source, pair<int, int> dest, int **distMatrix, stack<pair<int, int> > *Path, int N, int M, bool **visited){
    pair<int, int> node;
    queue<pair<int,int > > Q;
    Q.push(dest);
    int distS = distMatrix[dest.first][dest.second];
    short dx[4] = {0, 0, 1, -1};
    short dy[4] = {1, -1, 0, 0};

    for( int i = 0; i < N; i++)
        for(int j = 0; j < M; j ++)
            visited[i][j] = false;

    while( !Q.empty()){
        node = Q.front();
        Q.pop();
        for(int i = 0; i < 4; i++){
            pair<int, int> neigh;
            neigh.first = node.first + dx[i];
            neigh.second = node.second + dy[i];

            if(neigh.first >= N || neigh.first < 0)
                continue;
            if(neigh.second >= M|| neigh.second < 0)
                continue;
            if (distMatrix[neigh.first][neigh.second] == -1)
                continue;
            if(neigh.first == source.first && neigh.second==source.second){
                Path->push(node);
                break;
            }
            if(distMatrix[neigh.first][neigh.second] < distS && (visited[neigh.first][neigh.second] == false)){
                Q.push(neigh);
                if (distMatrix[neigh.first][neigh.second] == (distS - 1)){
                    Path->push(node);
                    visited[neigh.first][neigh.second] = true;
                }
                distS--;
            }
        }
    }
}
void bfsDistance(pair<int,int> source, int** dist, char** citymap, int N, int M){
    for (int i = 0; i < N ; i++)
        for(int j = 0; j < M; j++)
            dist[i][j] = {2147483647};

    queue<pair<int,int > > Q;

    short dx[4] = {0, 0, 1, -1};
    short dy[4] = {1, -1, 0, 0};

    Q.push(source);
    dist[source.first][source.second] = 0;

    while(!Q.empty()){
        pair<int, int> node;
        node = Q.front();
        Q.pop();
        pair<int, int> neigh;

        for(int i = 0; i < 4; i++){
            neigh.first = node.first + dx[i];
            neigh.second = node.second + dy[i];

            if(neigh.first >= N || neigh.first < 0)
                continue;

            if(neigh.second >= M || neigh.second < 0)
                continue;

             if(citymap[neigh.first][neigh.second] == 'X'){
                dist[neigh.first][neigh.second] = -1;
                continue;
            }

            if(dist[neigh.first][neigh.second] > (dist[node.first][node.second] + 1)){
                dist[neigh.first][neigh.second] = dist[node.first][node.second] + 1;
                Q.push(neigh);
            }
        }
    }
}

int main(){
    ifstream workin("workcommute.in");
    ofstream workout("workcommute.out");
    if (!workin){
        cerr << "No such file found.";
        return -1;
    }
    int N, M;
    workin >> N >> M;
    char **citymap;
    citymap = new char *[N];
    for(int i = 0; i < N; i++)
        citymap[i] = new char[M];
    char c;
    pair<int, int> source;
    pair<int, int> offices[3];
    int contor = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            workin >> c;
            citymap[i][j] = c;
            if( c == 'H')
                source = {i, j};
            if (c == 'O'){
                offices[contor] = {i, j};
                contor++;
            }
        }
    }

    workin.close();
    bool **visited;
    int **distH, **distO1, **distO2, **distO3;
    distH = new int *[N];
    distO1 = new int*[N];
    distO2 = new int*[N];
    distO3 = new int*[N];
    visited = new bool*[N];
    for(int i = 0; i < N; i++){
        distH[i] = new int[M];
        distO1[i] = new int[M];
        distO2[i] = new int[M];
        distO3[i] = new int[M];
        visited[i] = new bool[M];
    }
    bfsDistance(source, distH , citymap, N, M);
    bfsDistance(offices[0], distO1 , citymap, N, M);
    bfsDistance(offices[1], distO2 , citymap, N, M);
    bfsDistance(offices[2], distO3 , citymap, N, M);

    stack<pair<int, int> > *Path;
    Path = new stack<pair<int, int> >();

    int sumH123 = distH[offices[0].first][offices[0].second] + distO1[offices[1].first][offices[1].second] + distO2[offices[2].first][offices[2].second];
    int sumH132 = distH[offices[0].first][offices[0].second] + distO1[offices[2].first][offices[2].second] + distO3[offices[1].first][offices[1].second];
    int sumH213 = distH[offices[1].first][offices[1].second] + distO2[offices[0].first][offices[0].second] + distO1[offices[2].first][offices[2].second];
    int sumH231 = distH[offices[1].first][offices[1].second] + distO2[offices[2].first][offices[2].second] + distO3[offices[0].first][offices[0].second];
    int sumH312 = distH[offices[2].first][offices[2].second] + distO3[offices[0].first][offices[0].second] + distO1[offices[1].first][offices[1].second];
    int sumH321 = distH[offices[2].first][offices[2].second] + distO3[offices[1].first][offices[1].second] + distO2[offices[0].first][offices[0].second];

    int sum = min(sumH123, min(sumH132, min(sumH213, min(sumH231, min(sumH312,sumH321)))));

    if (sum < 0)
        workout << "-1\n";
    else if (sum == sumH123){
        workout << sumH123 << endl;
        printPath(offices[1], offices[2], distO2, Path, N, M, visited);
        printPath(offices[0], offices[1], distO1, Path, N, M, visited);
        printPath(source, offices[0], distH, Path, N, M, visited);

    }
    else if (sum == sumH132){
        workout << sumH132 << endl;
        printPath(offices[2], offices[1], distO3, Path, N, M, visited);
        printPath(offices[0], offices[2], distO1, Path, N, M, visited);
        printPath(source, offices[0], distH, Path, N, M, visited);

    }
    else if (sum == sumH213){
        workout << sumH213 << endl;
        printPath(offices[0], offices[2], distO1, Path, N, M, visited);
        printPath(offices[1], offices[0], distO2, Path, N, M, visited);
        printPath(source, offices[1], distH, Path, N, M, visited);
    }
    else if (sum == sumH231){
        workout << sumH231 << endl;
        printPath(offices[2], offices[0], distO3, Path, N, M, visited);
        printPath(offices[1], offices[2], distO2, Path, N, M, visited);
        printPath(source, offices[1], distH, Path, N, M, visited);

    }
    else if (sum == sumH312){
        workout << sumH312 << endl;
        printPath(offices[0], offices[1], distO1, Path, N, M, visited);
        printPath(offices[2], offices[0], distO3, Path, N, M, visited);
        printPath(source, offices[2], distH, Path, N, M, visited);

    }
    else if (sum == sumH321){
        workout << sumH321 << endl;
        printPath(offices[1], offices[0], distO2, Path, N, M, visited);
        printPath(offices[2], offices[1], distO3, Path, N, M, visited);
        printPath(source, offices[2], distH, Path, N, M, visited);

    }
    else workout << "-1\n";

    Path->push(source);
    while (!Path->empty()){
        pair<int, int> node = Path->top();
        workout << node.first + 1 << ' '<< node.second + 1 <<endl;
        Path->pop();
    }
    workout.close();
    return 0;
}
