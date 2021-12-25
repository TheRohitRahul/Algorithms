#include <iostream>
#include <vector>

// Simple node of a linked list
struct Node{
    int data;
    Node* next_node;
};

Node* reverse_it(Node* head_ptr){

    /*
    We will initialize 3 pointers. One will stay behind One which will point to the 
    head of the linked list and another which will be a step ahead
    */
    
   // This pointer would stay 1 step behind 
    Node* ptr1 = NULL;

    // the mid of the pointer set 
    Node* ptr2 = head_ptr;

    // This pointer will move a step ahead
    Node* ptr3 = head_ptr->next_node;

    while(ptr2 != NULL){
        ptr2->next_node = ptr1;
        ptr1 = ptr2;
        ptr2 = ptr3;
        if (ptr3 != NULL){
            ptr3 = ptr3->next_node;
        }
    }
    head_ptr = ptr1;
    return head_ptr;
}


/*
This function is for printing the linked list
*/
void print_linked_list( Node* head_ptr ){
    Node* current_ptr = head_ptr;

    std::cout << std::endl;

    while(current_ptr != NULL){
        std::cout << " -- | " << current_ptr->data << " | --> "; 
        current_ptr = current_ptr -> next_node;

    }
    std::cout<<std::endl;
    std::cout << std::endl;
}

/*
A function for creating the linked list
*/
Node* create_linked_list(){

    std::vector<int> all_data = {1,2,3,4,5,6,7,8,9};

    Node* head_ptr = (Node*) malloc(sizeof(Node));
    head_ptr->data = all_data[0];
    head_ptr->next_node = NULL;
    Node* current_ptr = head_ptr;



    for (int i = 1; i < all_data.size(); i++){
        int val = all_data[i];

        Node* new_ptr = (Node*) malloc(sizeof(Node));
        (*new_ptr).data = val;
        (*new_ptr).next_node = NULL;
        
        current_ptr->next_node = new_ptr;
        current_ptr = new_ptr;
    }
    return head_ptr;

}

int main(){

    Node* head_ptr = create_linked_list();
    
    std::cout << "Original linked list : " << std::endl;
    print_linked_list(head_ptr);
    
    std::cout << "Reversed linked list : " << std::endl;
    Node* reversed_head_ptr = reverse_it(head_ptr);
    print_linked_list(reversed_head_ptr);    
    

}

