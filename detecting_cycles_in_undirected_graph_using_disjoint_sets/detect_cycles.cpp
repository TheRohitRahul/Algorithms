#include <iostream>
#define VERTICE_COUNT 8
#define EDGE_COUNT 9
#define NUM_POINTS 2

using namespace std;

void print_working_list(int working_list[]){
    cout << "WORKING LIST : ";
    cout <<"\n";
    for (int i = 0; i < VERTICE_COUNT; i++){
        cout << "\t" << working_list[i];
    }
    cout << "\n";
}

void print_edge_list(int edge_list[EDGE_COUNT][NUM_POINTS]){
    cout << "EDGE LIST : ";
    cout <<"\n";
    for (int i = 0; i < EDGE_COUNT; i++){
        cout << '\n';
        for( int j = 0; j < NUM_POINTS; j++){
            cout << "\t" << edge_list[i][j];
        }        
    }
    cout << "\n";
}

void initialize_working_list(int working_list[]){
    for (int i = 0; i < VERTICE_COUNT; i++){
        working_list[i] = -1;
    }
}

int find_parent(int working_list[], int vertice){
    int parent = vertice;
    // cout << "value in working list for parent is " << working_list[vertice] << endl;
    while(working_list[parent] >= 0){
        // cout  << "\n" << parent << endl;
        parent = working_list[parent];
    }
    // cout << "Returning parent for "<< vertice << " as " << parent << endl;
    return parent;
}

void remove_cycles(int edge_list[EDGE_COUNT][NUM_POINTS]){

    int working_list[VERTICE_COUNT];
    initialize_working_list(working_list);
    print_working_list(working_list);
    print_edge_list(edge_list);
    
    int vertice_1 = 0;
    int vertice_2 = 0;
    int parent_v1 = 0;
    int parent_v2 = 0;

    for (int i = 0; i < EDGE_COUNT; i++){
        vertice_1 = edge_list[i][0];
        vertice_2 = edge_list[i][1];

        parent_v1 = find_parent(working_list, vertice_1);
        parent_v2 = find_parent(working_list, vertice_2);
        
        if (parent_v2 == parent_v1){
            cout << "There is cycle in the graph" << endl;
            cout << "leaving edge " << vertice_1 <<"--" << vertice_2 << endl;
            continue;
        }
        // cout << "vertices are " << vertice_1 << " and " << vertice_2 << endl;
        // cout << "Trying to join "<< parent_v1 <<" and "<< parent_v2<< endl;
        // Do union of the sets
        if (working_list[parent_v2] >= working_list[parent_v1]){
            working_list[parent_v2] = parent_v1;
            working_list[parent_v1]--;
        }
        else{
            working_list[parent_v1] = parent_v2;
            working_list[parent_v2]--;
        }
        // print_working_list(working_list);
    }
    cout << "final working list is : " << endl;
    print_working_list(working_list);
}



int main(void){

    int edge_list[EDGE_COUNT][NUM_POINTS] = {{0,2}, {0,1}, {2,3}, {1,3}, {1,4}, {4, 6}, {6, 7}, {7, 5}, {5, 4}};
    remove_cycles(edge_list);
   

}