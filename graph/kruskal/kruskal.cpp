#include <iostream>
#include <vector>

#include "edge.cpp"
#include "find_cycles.cpp"
#include "minheap.cpp"

class Kruskal{
    private:
        std::vector<Edge> m_edge_list;
        int m_num_vertices;
       
        // This is what will be finally formed
        std::vector<Edge> m_mst;

        CycleDetector m_cycle_detector;
        MinHeap m_min_heap;        

    public:
        Kruskal(std::vector<Edge> edge_list, int num_vertices): m_edge_list(edge_list), m_num_vertices(num_vertices){
            
            CycleDetector temp_cycle_detector(num_vertices);
            this->m_cycle_detector = temp_cycle_detector;
            
            MinHeap temp_heap(edge_list);
            this->m_min_heap = temp_heap;
            // this->m_cycle_detector.update_edge_list(m_edge_list);
        }

        void print_edge_vector(std::vector<Edge> edge_vector){
            for (auto i = edge_vector.begin(); i != edge_vector.end(); i++){
                std::cout << (*i).get_vertice1() << "\t" << (*i).get_vertice2() << "\t" << (*i).get_edge_weight() << std::endl;
            }
        }

        std::vector<Edge> create_mst(){
            for (int i = 0 ; i < ( this->m_num_vertices - 1 ); i++){
                bool cycle_present = true;
                while(cycle_present){
                    Edge current_edge = this->m_min_heap.pop();
                    this->m_mst.push_back(current_edge);
                    this->m_cycle_detector.update_edge_list(this->m_mst);
                    cycle_present = this->m_cycle_detector.detect_cycles();
                    
                    // if (cycle_present){
                    //     std::cout << "Cycle Present is : " << cycle_present << std::endl;
                    //     print_edge_vector(this->m_mst);
                    //     std::cout << std::endl;
                    // }
                    
                    // If a cycle is present then we will remove the last element that we inserted
                    if (cycle_present){
                        this->m_mst.erase(this->m_mst.begin() + (this->m_mst.size()-1));
                    }

                    // if (cycle_present){
                    //     print_edge_vector(this->m_mst);
                    //     std::cout << std::endl;
                    //     exit(0);
                    // }
                }
            }
            return this->m_mst;
        }


        
};

void print_edge_vector(std::vector<Edge> edge_vector){
    int total_cost = 0;
    for (auto i = edge_vector.begin(); i != edge_vector.end(); i++){
        std::cout << (*i).get_vertice1() << "\t" << (*i).get_vertice2() << "\t" << (*i).get_edge_weight() << std::endl;
        total_cost += (*i).get_edge_weight();
    }
    std::cout << "Cost of minimum spanning tree is : " << total_cost << std::endl;
}


/*
Always start the vertice number from zero otherwise the result will not be correct
*/
void fill_edges(std::vector<Edge> &edge_list_initial){
    edge_list_initial.push_back(Edge(0, 1, 28));
    edge_list_initial.push_back(Edge(1, 2, 16));
    edge_list_initial.push_back(Edge(2, 3, 12));
    edge_list_initial.push_back(Edge(3, 6, 18));
    edge_list_initial.push_back(Edge(6, 1, 14));
    edge_list_initial.push_back(Edge(3, 4, 22));
    edge_list_initial.push_back(Edge(4, 6, 24));
    edge_list_initial.push_back(Edge(4, 5, 25));
    edge_list_initial.push_back(Edge(5, 0, 10));
}
int main(){
    std::vector<Edge> edge_list_initial;
    fill_edges(edge_list_initial);
    Kruskal kruskal(edge_list_initial, 7);
    std::vector<Edge> mst = kruskal.create_mst();
    std::cout << "This output is finally created" << std::endl;
    print_edge_vector(mst);
    

}