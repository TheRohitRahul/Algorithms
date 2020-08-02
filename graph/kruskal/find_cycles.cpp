#include <iostream>
// #include "edge.cpp"
#include <vector>
#include <cstring>

class CycleDetector{

    private:
        std::vector<Edge> m_edge_list;
        std::vector<int> m_parent_list;
        int m_num_vertices;
    public:
        CycleDetector(){}
        CycleDetector(int num_vertices) : m_num_vertices(num_vertices){}

        void initialize_parent_list(){
            if (this->m_parent_list.size() == 0){
                this->m_parent_list.insert(this->m_parent_list.end(), this->m_num_vertices, -1 );
            }
            else{
                std::fill(this->m_parent_list.begin(), this->m_parent_list.end(), -1);
            }
        }
        void update_edge_list( std::vector<Edge> edge_list ){
            this->m_edge_list = edge_list;

        }

        int find_parent(int vertice){
            int parent = vertice;
            while(this->m_parent_list[parent] >= 0){
                parent = this->m_parent_list[parent];
            }

            return parent;

        }
        void print_parent_list(){
            for (auto i = this->m_parent_list.begin(); i != this->m_parent_list.end(); i++){
                std::cout<< *i << "\t";
            }
            std::cout << std::endl;
        }
        bool detect_cycles(){
            // std::cout << "Total vertices are : " << m_num_vertices;
            // exit(0);
            this->initialize_parent_list();

            // this->print_parent_list();
            for (int i = 0; i < this->m_edge_list.size(); i++){

                int vertice1 = this->m_edge_list[i].get_vertice1();
                int vertice2 = this->m_edge_list[i].get_vertice2();

                int parent1 = this->find_parent(vertice1);
                int parent2 = this->find_parent(vertice2);

                

                if (parent1 == parent2){
                    // std::cout << "vertice 1 : " << vertice1 << " vertice 2 : " << vertice2 << std::endl;
                    // std::cout << "parent 1 : " << parent1 << " parent 2 : " << parent2 << std::endl;
                    // this->print_parent_list();
                    // std:: cout << parent1 << "\t" << parent2 << std::endl;
                    return true;
                }
                if (parent2 >= parent1){
                    this->m_parent_list[parent2] = parent1;
                    this->m_parent_list[parent1]--;
                }
                else{
                    this->m_parent_list[parent1] = parent2;
                    this->m_parent_list[parent2]--;
                }
            }
            
            return false;
        }
};