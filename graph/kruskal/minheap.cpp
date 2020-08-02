#include <iostream>
// #include "edge.cpp"
#include <vector>

class MinHeap{
    private:
        std::vector<Edge> m_heap;
        
        void populate_heap(std::vector<Edge> edge_list){
            for (auto i : edge_list){
                this->insert_element(i);
                }
        }
        

    public:
        MinHeap(){ }

        MinHeap(std::vector<Edge> edge_list){
            this->populate_heap(edge_list); }
        
        void print_heap(){
            for (auto i = this->m_heap.begin(); i != this->m_heap.end(); i++){
                std::cout << (*i).get_vertice1() << "\t" << (*i).get_vertice2() << "\t" << (*i).get_edge_weight() << std::endl;
            }
        }
       
        /*
        Swapping two elements from the heap
        */
       void swap(int i, int j){
           Edge temp = this->m_heap[i];
           this->m_heap[i] = this->m_heap[j];
           this->m_heap[j] = temp;
       }

        /*
        The 1st element is always sorted that is , an array with a single element in it will always be a heap
        This method returns the id of the element that is just inserted
        */
        void insert_element(Edge element){
            
            
            this->m_heap.push_back(element);
            
            // This will be true when the element finally reaches its designated position in the heap and the loop would then break
            bool has_reached_its_position = false;
            
            /*
            Do note that here I'm using indices from 1 to calculate the positions but later while actually accessing the position 
            in the heap I will subtract 1 so that the indices start from 0.
            */
            int current_position = this->m_heap.size();
            int parent_position = int(current_position / 2);

            while(!has_reached_its_position && current_position > 1){
                
                if ( this->m_heap[parent_position - 1].get_edge_weight() > this->m_heap[current_position - 1].get_edge_weight() ){

                    this->swap(parent_position-1, current_position -1);
                    current_position = parent_position;
                    parent_position = int(current_position/2);

                }
                else{
                    has_reached_its_position = true;
                }            
            }            
        }
        /*
        Implementation of pop from the heap 
        This will further call the delete min function
        */
        Edge pop(){
            if (this->m_heap.size() == 0){
                Edge temp(-1,-1,-1);
                return temp;
            }
            
            Edge min_element = this->m_heap[0];
            this->delete_min();
            return min_element;

        }
        void delete_min(){
            /*
            We need to delete the first element 
            but we will first swap the first and last element
            Otherwise we would have to shift each element if we choose to delete first and swap later
            */
            int position_to_delete = this->m_heap.size() -1 ;
            this -> swap(this->m_heap.size()-1, 0);

            this->m_heap.erase(this->m_heap.begin() + position_to_delete);
            this->rebalance_heap();
            
        }
        void rebalance_heap(){
            int current_pos = 1;
            int child1_pos = current_pos*2;
            int child2_pos = (current_pos*2) + 1;
            bool has_reached_its_place = false;

            while(!has_reached_its_place && current_pos < this->m_heap.size() + 1 ){
                bool child1_valid = false;
                bool child2_valid = false;

                if (child1_pos < this->m_heap.size() + 1){
                    child1_valid = true;
                }
                if (child2_pos < this->m_heap.size() + 1){
                    child2_valid = true;
                }

                if (child1_valid && child2_valid){
                    if (this->m_heap[child1_pos -1 ].get_edge_weight() <= this->m_heap[child2_pos - 1].get_edge_weight()){
                        if (this->m_heap[child1_pos - 1].get_edge_weight() < this->m_heap[current_pos - 1].get_edge_weight()){
                            this->swap(child1_pos - 1, current_pos -1 );
                            current_pos = child1_pos;
                            child1_pos = int(2*current_pos);
                            child2_pos = int(2*current_pos) + 1;
                        }
                        else{
                            has_reached_its_place = true;
                        }
                        
                    }
                    else{
                        if (this->m_heap[child2_pos - 1].get_edge_weight() < this->m_heap[current_pos - 1].get_edge_weight()){
                            this->swap(child2_pos - 1, current_pos -1 );
                            current_pos = child2_pos;
                            child1_pos = int(2*current_pos);
                            child2_pos = int(2*current_pos) + 1;
                        }
                        else{
                            has_reached_its_place = true;
                        }

                    }

                }
                else if (child1_valid){
                    if (this->m_heap[current_pos - 1].get_edge_weight() > this->m_heap[child1_pos - 1].get_edge_weight() ){
                        this->swap( current_pos - 1, child1_pos - 1 );
                        current_pos = child1_pos;
                        child1_pos = 2*child1_pos;
                        child2_pos = 2*child1_pos + 1;
                    }
                    else{
                        has_reached_its_place = true;
                    }
                }
                else if (child2_valid){
                    if (this->m_heap[current_pos - 1].get_edge_weight() > this->m_heap[child2_pos - 1].get_edge_weight() ){
                        this->swap( current_pos - 1, child2_pos - 1 );
                        current_pos = child2_pos;
                        child1_pos = 2*child2_pos;
                        child2_pos = 2*child2_pos + 1;
                    }
                    else{
                        has_reached_its_place = true;
                    }}
                // We have reached the max depth of the heap
                else{
                    has_reached_its_place = true;
                }
            }


        }
        int size(){
            return this->m_heap.size();
        }
};