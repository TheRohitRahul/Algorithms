#include <iostream>
#include <vector>

using namespace std;


void apply_dijkstra(vector <vector<int>> graph){
    vector<int> seen_vertex;
    for (int i = 0 ; i < graph.size(); i++){
        
    }

}

void print_graph(vector<vector<int>> graph){
    for (int i = 0; i < graph.size(); i++){
        cout << "\n";
        for (int j = 0 ; j < graph.size(); j++){
            cout << graph[i][j] << "\t";
        }
    }
    cout << "\n";
}

int randint(int low, int high){
    double rand_num = (double) rand() / (RAND_MAX);
    int r = int(((rand_num)*(high - low)) + low);
    return r;
}

void create_graph(vector<vector<int>> &graph, int num_vertices){
    for(int i = 0; i < num_vertices; i++){
        vector<int> temp ;
        for (int j = 0 ; j < num_vertices; j++){
            temp.push_back(randint(0, 3));
        }
        graph.push_back(temp);
    }
}

int main(void){
    
    vector<vector<int>> graph;
    int num_vertices = 5;
    create_graph(graph, num_vertices);
    print_graph(graph);
    apply_dijkstra(graph);

}