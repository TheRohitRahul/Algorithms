/*
Heapify is a procedure where you just take the array that you need to convert into heap and without using any additional space, you create that heap
*/
#include <iostream>
#include <vector>

using namespace std;

void print_vector(vector<int> arr){
    for (auto a = arr.begin(); a!= arr.end(); ++a){
        cout << *a << "\t";
    }
    cout << "\n";
}

// Procedure for swapping 2 elements
void swap(vector<int> &arr, int pos_1, int pos_2){
    
    int temp = arr[pos_1];
    arr[pos_1] = arr[pos_2];
    arr[pos_2] = temp;
}

void place_element_at_correct_position(vector<int> &to_be_heap, int element_position){
    bool has_reached_correct_position = false;
    int current_element_position = element_position;
    while(!has_reached_correct_position){
        
        // cout << "\nHeap at the starting of the while" << endl;
        // print_vector(to_be_heap);

        int child1, child2;
        int heap_end = to_be_heap.size();
        bool child1_valid = false;
        bool child2_valid = false;

        child1 = 2*current_element_position;
        child2 = 2*current_element_position + 1;
        

        // Child1 is valid 
        if (child1 <= heap_end){
            child1_valid = true;
        }
        // child2 is valid
        if (child2 <= heap_end){
            child2_valid = true;
        }

        if (child2_valid && child1_valid){
            
            int child1_element = to_be_heap[child1 - 1];
            int child2_element = to_be_heap[child2 - 1];

            int current_element = to_be_heap[current_element_position - 1];

            if (current_element >= child1_element && current_element >= child2_element){
                has_reached_correct_position = true;
            }
            else{
                if (child1_element > child2_element){
                    current_element_position;
                    swap(to_be_heap, child1 - 1, current_element_position - 1);
                    current_element_position = child1;
                }
                else{
                    swap(to_be_heap, child2 - 1, current_element_position - 1);
                    current_element_position = child2;
                }
            }

        }
        else if(child1_valid){
            int child1_element = to_be_heap[child1 - 1];
            int current_element = to_be_heap[current_element_position - 1];
            if (current_element_position > child1_element){
                has_reached_correct_position = true;
            }
            else{
                swap(to_be_heap, child1 - 1, current_element_position - 1);
                current_element_position = child1;
            }
        }
        else if (child2_valid){
            int child2_element = to_be_heap[child2 - 1];
            int current_element = to_be_heap[current_element_position - 1];
            if (current_element_position > child2_element){
                has_reached_correct_position = true;
            }
            else{
                swap(to_be_heap, child2 - 1, current_element_position - 1);
                current_element_position = child2;
            }
        }
        
        else{
            has_reached_correct_position = true;
        }
    }

}

void heapify(vector<int> &arr){
    
    // For computation I'm taking index from 1 but while accessing the array I will decrement 1 so that it starts from 0.
    for (int i = arr.size() ; i > 0; i--){
        place_element_at_correct_position(arr, i);
        
    }
}

int main(void){
    
    vector<int> arr = {25,20,15,40,29,50,65};
    
    cout << "Initial Vector : " << endl;
    print_vector(arr);
    
    heapify(arr);

    cout<< "\nAfter heapifying" << endl;
    print_vector(arr);

}