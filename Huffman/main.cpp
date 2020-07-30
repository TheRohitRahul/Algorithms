#include <iostream>
#include<bits/stdc++.h>
#include <string>

#define SIZE 10

class Node{

    Node* m_parent;
    Node* m_left;
    Node* m_right;
    bool m_is_leaf;
    int m_count;
    char m_alphabet;
    int m_id;

    public:
        Node(Node* left, Node* right, bool is_leaf, char alphabet, int count): m_right(right), m_left(left), m_is_leaf(is_leaf), m_alphabet(alphabet), m_count(count){

        }
        int get_id(){
            return this->m_id;
        }
        void set_id(int id){
            this->m_id = id;
        }
        int get_count(){
            return this->m_count;
        }
        void set_count(int count){
            this->m_count = count;
        }
        bool get_is_leaf(){
            return this->m_is_leaf;
        }
        char get_character(){
            return this->m_alphabet;
        }
        Node* get_right(){
            return this->m_right;
        }
        Node* get_left(){
            return this->m_left;
        }
};

struct CharCount{
    char character;
    int count;
    bool is_leaf;
    int id;
};

struct CharAndEncoding{
    char character;
    std::vector<char> encoding;
    int frequency;
};

class MinHeap{
    private:
        std::vector<CharCount> m_heap;
        //This is maintained to provide id to elements
        int m_counter = 0;

        void populate_heap(std::unordered_map<char, int> frequency){
            for (auto i : frequency){
                
                CharCount temp;
                temp.character = i.first;
                temp.count = i.second;
                temp.is_leaf = true;
                this->insert_element(temp);
                
            }
        }
        

    public:
        MinHeap(){

        }

        MinHeap(std::unordered_map<char, int> frequency){
            this->populate_heap(frequency);
            
        }
        void print_heap(){
            for (auto i = this->m_heap.begin(); i != this->m_heap.end(); i++){
                std::cout << (*i).character << "\t" << (*i).count << std::endl;
            }
        }
        CharCount get_next(){}

        /*
        Swapping two elements from the heap
        */
       void swap(int i, int j){
           CharCount temp = this->m_heap[i];
           this->m_heap[i] = this->m_heap[j];
           this->m_heap[j] = temp;
       }

        /*
        The 1st element is always sorted that is , an array with a single element in it will always be a heap
        This method returns the id of the element that is just inserted
        */
        int insert_element(CharCount element){
            
            //Assigning ids to elements for later use
            element.id = this->m_counter;
            this->m_counter++;

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
                
                if ( this->m_heap[parent_position - 1].count > this->m_heap[current_position - 1].count ){

                    this->swap(parent_position-1, current_position -1);
                    current_position = parent_position;
                    parent_position = int(current_position/2);

                }
                else{
                    has_reached_its_position = true;
                }
            
            }

            return element.id;
        }
        /*
        Implementation of pop from the heap 
        This will further call the delete min function
        */
        CharCount pop(){
            if (this->m_heap.size() == 0){
                CharCount temp ;
                temp.count = -1;
                temp.is_leaf = false;
                temp.character = ' ';
                return temp;
            }
            CharCount min_element = this->m_heap[0];
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
                    if (this->m_heap[child1_pos -1 ].count <= this->m_heap[child2_pos - 1].count){
                        if (this->m_heap[child1_pos - 1].count < this->m_heap[current_pos - 1].count){
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
                        if (this->m_heap[child2_pos - 1].count < this->m_heap[current_pos - 1].count){
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
                    if (this->m_heap[current_pos - 1].count > this->m_heap[child1_pos - 1].count ){
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
                    if (this->m_heap[current_pos - 1].count > this->m_heap[child2_pos - 1].count ){
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

class Huffman{

    private:
        std::unordered_map<char, int> m_frequency;
        std::string m_message;
        MinHeap minheap;
        std::vector<Node*> top_nodes;
        std::vector<CharAndEncoding> all_chars_and_encodings;
    
        void print_frequency(const std::unordered_map<char, int>& frequency){

        for (auto i : frequency){
            std::cout << i.first << " --> "  << i.second << std::endl;
        }

    }
        void print_tree(Node* to_print){

            std::cout << "Alphabet : " << (*to_print).get_character() << std::endl;;
            std::cout << "Is Leaf : "<< (*to_print).get_is_leaf() << std::endl;;
            std::cout << "Count : " << (*to_print).get_count() << std::endl;;
            
            Node* right_tree = (*to_print).get_right();
            
            if (right_tree != NULL){
                std::cout << "Right" << std::endl;
                print_tree(right_tree);
            }
            else{
                std::cout << "Leaf ending \n" << std::endl;
            }
            
            
            
            Node* left_tree = (*to_print).get_left();
            if (left_tree != NULL){
                std::cout << "Left" << std::endl;
                print_tree(left_tree);
            }
            else{
                std::cout << "Leaf ending \n" << std::endl;
            }


        }

        void count_frequency(std::string& message,std::unordered_map<char, int>& frequency){
            for (int i = 0; i < message.length(); i++){

            frequency[message[i]]++;

            // std::cout << (int) message[i] << "  " << std::bitset<8>((int)message[i]).to_string() << std:: endl;
            }
        }

        /*
        Fetches a node if already present otherwise creates a new one
        */
        Node* fetch_node(CharCount element){
            int id = element.id;
            int index_found = -1;
            for (int i = 0; i < this->top_nodes.size(); i++){
                if ((*top_nodes[i]).get_id() == id){
                    index_found = i;
                }
            }
            if (index_found != -1){
                Node* ret_element = this->top_nodes[index_found];
                this->top_nodes.erase(this->top_nodes.begin() + index_found);
                return ret_element;
            }
            /*
            If something is not already present in the nodelist then it is a leaf node
            */
            else{
                return new Node(NULL, NULL, element.is_leaf,  element.character, element.count);

            }

        }
        void create_tree(){

            while(this->minheap.size() > 1){
                CharCount min_element1 = this->minheap.pop();
                CharCount min_element2 = this->minheap.pop();
                Node* minnode1 = fetch_node(min_element1);
                Node* minnode2 = fetch_node(min_element2);
                // std::cout << "Popped out : " << (*minnode1).get_character() << " and " << (*minnode2).get_character() << std::endl;
                
                // std::cout << "Minnode 1 right : "<< (*minnode1).get_right() << std::endl;
                // std::cout << "Minnode 1 left : "<< (*minnode1).get_left() << std::endl;
                
                // std::cout << "Minnode 1 right : "<< (*minnode1).get_right() << std::endl;
                // std::cout << "Minnode 2 left : "<< (*minnode1).get_left() << std::endl;
                
                int combined_count = (*minnode1).get_count() + (*minnode2).get_count();
                //Joining these two nodes
                Node* joint_node = new Node(minnode1, minnode2, false, ' ', combined_count);
                
                // std::cout << "Minnode 1 is : "<< minnode1 << std::endl;
                // std::cout << "Minnode 2 is : "<< minnode2 << std::endl;

                // std::cout << "Assigned " << (*joint_node).get_left() << " to minnode 1" << std::endl;
                // std::cout << "Assigned " << (*joint_node).get_right() << " to minnode 2" << std::endl;

                CharCount joint_struct;
                joint_struct.character = (*joint_node).get_character();
                joint_struct.count = (*joint_node).get_count();
                joint_struct.is_leaf = (*joint_node).get_is_leaf();

                int new_id = this->minheap.insert_element(joint_struct);
                (*joint_node).set_id(new_id);
                this->top_nodes.push_back(joint_node);

            }
            /*
            At this point our tree is built we can use it to assign 
            */
            // Printing to check if the tree has been formed correctly
            // this->print_tree(this->top_nodes[0]);
           
        }
        std::vector<CharAndEncoding> recursive_fill(Node* single_node){
            std::vector<CharAndEncoding> to_return;

            //Handling base case
            if ((*single_node).get_is_leaf()){
                CharAndEncoding to_add;
                to_add.character = (*single_node).get_character();
                to_add.frequency = (*single_node).get_count();
                to_return.push_back(to_add);        
            }

            else{
                std::vector<CharAndEncoding> left_data =  recursive_fill((*single_node).get_left());
                std::vector<CharAndEncoding> right_data = recursive_fill((*single_node).get_right());

                for (auto i = left_data.begin(); i != left_data.end(); i++){
                    (*i).encoding.insert((*i).encoding.begin(), '1');
                    to_return.push_back((*i));
                }
                for (auto i = right_data.begin(); i != right_data.end(); i++){
                    (*i).encoding.insert((*i).encoding.begin(), '0');
                    to_return.push_back((*i));
                }
            }
            return to_return;
        }
        void fill_chars_and_encodings(){
            this->all_chars_and_encodings = recursive_fill(this->top_nodes[0]);
        }
    public:
        Huffman(std::string message): m_message(message){
            count_frequency(this->m_message, this->m_frequency);
            // print_frequency(this-> m_frequency);
            MinHeap temp(this->m_frequency);
            this->minheap = temp;
            this->create_tree();
            this->fill_chars_and_encodings();
            // std::cout << "printing for second time " << std::endl;
            // this->minheap.print_heap();
        } 
        std::vector<CharAndEncoding> get_chars_and_encodings(){
            return this->all_chars_and_encodings;
        }
        Node* get_tree(){
            return this->top_nodes[0];
        }

};


void print_chars_and_encodings(std::vector<CharAndEncoding> all_chars_and_encodings){
    std:: cout << "\nCharacters in the original message and their new encodings" << std::endl;
    for (auto i = all_chars_and_encodings.begin(); i != all_chars_and_encodings.end(); i++){
        std::cout << (*i).character << "\t";
        for (auto j = (*i).encoding.begin(); j != (*i).encoding.end(); j++){
            std::cout << (*j);
        }
        std::cout << std::endl;            
    }
    std::cout << "encodings end here \n"<< std::endl;
}

int main(void){

    std::string message = "HELLOTHERE";
    
    std::cout << "Total length of original message is : " << message.length()*8 << std::endl;
    Huffman encoder(message);
    
    std::vector<CharAndEncoding> chars_and_encoding = encoder.get_chars_and_encodings();
    
    print_chars_and_encodings(chars_and_encoding);

    int compressed_message_count = 0;
    for (auto i = chars_and_encoding.begin(); i != chars_and_encoding.end(); i++){
        // std::cout << (*i).frequency << "  " << (*i).encoding.size() << std::endl;
        compressed_message_count += ( (*i).frequency * (*i).encoding.size() );
    }

    std::cout << "After compression the length of the message would be : " << compressed_message_count << std::endl;

 
}