#include <iostream>
#include <vector>
#include<unordered_map>

#include "edge.cpp"

class Prims{
    private:
        std::vector<bool> m_tree_not_tree_vertex;
        int m_num_vertices;
        std::unordered_map< int, std::vector<Edge> > adjecency_list;
        std::vector<Edge> m_mst;

        void create_adjecency_list(std::vector<Edge> edge_list){
            
            for (auto i = edge_list.begin(); i != edge_list.end(); i++){
                int vertice1 = (*i).get_vertice1();
                this -> add_vertice_to_adjecency_list(vertice1, (*i));
                
                int vertice2 = (*i).get_vertice2();
                this -> add_vertice_to_adjecency_list(vertice2, (*i));
                
            }
        }

        void print_adjecency_list(){
            std::cout << "\nAdjecency List created is : " <<std::endl;
            for (auto& it: this->adjecency_list){
                std::cout <<"\n" << it.first <<" : | ";
                std::vector<Edge> show_vec = it.second;

                for (auto i = show_vec.begin(); i != show_vec.end(); i++){
                    std::cout << (*i).get_vertice1() << " -- " << (*i).get_edge_weight() << " --> " << (*i).get_vertice2() << " | ";
                }
                std::cout << std::endl;

            }
            std::cout<< "\n\n";
        }

        void add_vertice_to_adjecency_list(int vertice, Edge edge){
            //Inserting edge under vertice1
            if (this->adjecency_list.find(vertice) == this->adjecency_list.end()){
                // Key for vertice1 not found
                std::vector<Edge> temp_vec;
                temp_vec.push_back(edge);
                this->adjecency_list[vertice] = temp_vec;
            }
            else{
                //Key was present
                this->adjecency_list[vertice].push_back(edge);
            }
        }

        void init_tree_not_tree(){
            if (this->m_tree_not_tree_vertex.size() == 0){
                this->m_tree_not_tree_vertex.insert(this->m_tree_not_tree_vertex.end(), this->m_num_vertices, false );
            }
            else{
                std::fill(this->m_tree_not_tree_vertex.begin(), this->m_tree_not_tree_vertex.end(), false);
            }
        }

        // This function will keep a track of duplicates
        bool should_keep(int verticea, int verticeb, std::unordered_map<int, std::vector<int>> &seen_so_far){
            
            if (seen_so_far.find(verticea) != seen_so_far.end()){
                std::vector<int> all_seen_vertices = seen_so_far[verticea];
                for (int j = 0; j < all_seen_vertices.size(); j++){
                    //We have already seen this edge
                    if (all_seen_vertices[j] == verticeb){
                        return false;
                    }
                    else{
                        seen_so_far[verticea].push_back(verticeb);
                        return true;
                    }
                }

            }
            else{
                std::vector<int> temp_edge;
                temp_edge.push_back(verticeb);
                seen_so_far[verticea] = temp_edge;
                return true;
            }
        }

        std::vector<Edge> remove_invalid_candidates(std::vector<Edge> &interim_candidates){
            //This will contain the smaller vertice as key and larger vertice as value
            std::vector<Edge> filtered_candidates;
            std::unordered_map<int, std::vector<int>> seen_so_far;

            for (auto i = interim_candidates.begin(); i!= interim_candidates.end(); i++){
                int vertice1 = (*i).get_vertice1();
                int vertice2 = (*i).get_vertice2();
                
                // We have to select one edge that is not in the tree and one that is
                if (this->m_tree_not_tree_vertex[vertice1] ^ this->m_tree_not_tree_vertex[vertice2]){
                        if (vertice1 < vertice2){
                            if (should_keep(vertice1, vertice2, seen_so_far)){
                                filtered_candidates.push_back((*i));
                            }
                        }
                        else{
                            if (should_keep(vertice2, vertice1, seen_so_far)){
                                filtered_candidates.push_back((*i));
                            }
                        }
                    }
                
                //We hit this case when either both are tree vertex or both are non tree vertex
                else{continue;}
            }
            return filtered_candidates;
        }

        std::vector<Edge> find_all_candidate_edges(){
            
            std::vector<int> all_tree_vertices;
            for(int i = 0; i < m_tree_not_tree_vertex.size(); i++){
                if (m_tree_not_tree_vertex[i]){
                    all_tree_vertices.push_back(i);
                }
            }
            
            
            std::vector<Edge> interim_candidates;
            for(int i = 0; i < all_tree_vertices.size(); i++){
                int single_vertex = all_tree_vertices[i];
                std::vector<Edge> all_edges = this->adjecency_list[single_vertex];
                
                for (auto j = all_edges.begin(); j != all_edges.end(); j++){
                    interim_candidates.push_back((*j));
                }
            }
            

            std::vector<Edge> valid_candidates = remove_invalid_candidates(interim_candidates);
            
            return valid_candidates;
        }

        Edge get_next_min_edge(std::vector<Edge> candidate_edges){
            int min_weight = 99999;
            Edge min_edge;
            for (int i = 0; i < candidate_edges.size(); i++){
                if (candidate_edges[i].get_edge_weight() < min_weight){
                    min_weight = candidate_edges[i].get_edge_weight();
                    min_edge = candidate_edges[i];
                }
            }
            return min_edge;
        }

    public:
        Prims(std::vector<Edge> edge_list, int num_vertices) : m_num_vertices(num_vertices){
            this->create_adjecency_list(edge_list);
            this->print_adjecency_list();

        }

        
        std::vector<Edge> create_mst(){
            
            this->init_tree_not_tree();
            
            //will make 0 vertice as tree vertice
            this->m_tree_not_tree_vertex[0] = true;
            
            for (int i = 0; i < m_num_vertices -1 ; i++){
                std::vector<Edge> candidate_edges = this->find_all_candidate_edges();
                Edge next_min = this->get_next_min_edge(candidate_edges);
                this->m_mst.push_back(next_min);
                
                if ( !(this->m_tree_not_tree_vertex[ next_min.get_vertice1() ]) ){
                    this->m_tree_not_tree_vertex[ next_min.get_vertice1() ] = true;
                }
                if ( !(this->m_tree_not_tree_vertex[ next_min.get_vertice2() ]) ){
                    this->m_tree_not_tree_vertex[ next_min.get_vertice2() ] = true;
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
    Prims prims_obj(edge_list_initial, 7);
    std::vector<Edge> mst = prims_obj.create_mst();
    std::cout << "This output is finally created" << std::endl;
    print_edge_vector(mst);
    

}