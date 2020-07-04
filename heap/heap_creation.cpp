#include <iostream>
#include <vector>

using namespace std;

// Printing a vector
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

int delete_from_heap(vector<int> &heap, int &heap_end){
    int deleted_element = heap[0];
    swap(heap, 0, heap_end - 1);
    heap.erase(heap.begin() + (heap_end -1));
    heap.push_back(deleted_element);
    heap_end-- ;

    //At this point heap is still a complete binary tree but the order is all wrong so we would need to correct for the order
    bool has_reached_its_place = false;
    int current_position = 1;

    // cout << "\nbefore begining of while loop" << endl;
    // print_vector(heap);
    // cout <<"\n going into while"<< endl;
    while(!has_reached_its_place){
        // cout << "\nprinting heap"<< endl;
        // print_vector(heap);
        int child1 = 2*current_position;
        int child2 = 2*current_position + 1;
        bool child1valid = false;
        bool child2valid = false;

        if (child1 <= heap_end){
            child1valid = true; 
            // cout << "\n child 1 is " << child1 << " heap end is  " << heap_end << " and it is " << child1valid << endl;
        }
        if (child2 <= heap_end){
            child2valid = true; 
            // cout << "\n child 2 is " << child2 << " heap end is  " << heap_end << " and it is " << child2valid << endl;
        }

        // Both the childs are in the bounds of the heap
        if (child1valid && child2valid){
            if (heap[child1 - 1] <= heap[current_position - 1] && heap[child2 - 1] <= heap[current_position - 1]){
                
                has_reached_its_place = true;
            }
            else{
                if (heap[child1 - 1] > heap[child2 - 1]){
                    swap(heap, child1 -1 , current_position - 1);
                    current_position = child1;
                }
                else{
                    swap(heap, child2 - 1, current_position -1 );
                    current_position = child2;

                }
            }
        }
        else{
            if (child1valid){
                if (heap[child1 - 1] > heap[current_position -1 ]){
                    swap(heap, child1 -1 , current_position -1);
                    current_position = child1;
                }
                else{
                    has_reached_its_place = true;
                }
            }
            else if (child2valid) {
                if (heap[child2 -1 ] > heap[current_position - 1]){
                    swap(heap, child2 -1 , current_position - 1);
                    current_position = child2;
                }
                else{
                    has_reached_its_place = true;
                }
            
            }
            else{
                has_reached_its_place = true;
            }
        }

       }
    cout <<"__________________________________________________";
    return deleted_element;    
}
    
        
// I'm sorting using heap
void heap_sort(vector<int> &heap){
    int heap_end = heap.size();
    
    if (heap_end == 1){
        return;
    }
    int deleted_element;
    while(heap_end > 0){
        // cout << "\n heap end before is "<< heap_end;
        // cout << "\n array before is ";
        // print_vector(heap);
        deleted_element = delete_from_heap(heap, heap_end);
        // cout << "\n array after is ";
        // print_vector(heap);
        // cout << "\n heap end after is "<< heap_end;
        cout <<"\ndeleted "<< deleted_element << endl;
    }
 
   
}

//We are taking an array and creating a heap from it
void insert_into_heap(vector<int> &heap, int element_to_insert){
    
    cout << "\nInserting "<< element_to_insert << " into "<< endl;
    print_vector(heap);
    
    heap.push_back(element_to_insert);
    if (heap.size() == 1){
        return;
    }
    
    bool has_reached_its_place = false;
    int current_position = heap.size();


    while(!has_reached_its_place && current_position > 1 ){
        int parent_position = int(current_position /2) ;
        // cout << "Parent of " << current_position  << " is " << parent_position << endl;
        if (heap[parent_position - 1] < heap[current_position - 1]){
            swap(heap, parent_position - 1, current_position - 1);
        }
        else{
            has_reached_its_place = true;
            // cout << "\nnext iteration" << endl;
            // print_vector(heap);
        }
        current_position = parent_position;

    }
}

vector<int> convert_to_heap(vector<int> arr){
    //Creating a new vector we can use the same vector but then we would need to use heapify
    vector<int> heap;

    //inserting_elements
    for (int i = 0; i < arr.size(); i++){
        insert_into_heap(heap, arr[i]);
    }

    return heap;
}


int main(void){
    vector<int> arr = {25,20,15,40,29,50,65};
    cout << "Initial Vector : " << endl;
    print_vector(arr);

    // here we are making a max heap
    vector<int> ret_heap = convert_to_heap(arr);
    
    cout << "\nheap created : " << endl;
    print_vector(ret_heap);
    cout << "\nRunning inverse heap sort"<< endl;
    heap_sort(ret_heap);
    cout << "\nFinal array: " << endl;
    print_vector(ret_heap);

}