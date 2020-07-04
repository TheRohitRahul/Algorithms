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

int partition(vector<int> &array, int low, int high){

    int pivot = array[low];
    int i = low;
    int j = high;
    
    while(i < j){
        while(array[j] > pivot){
            j--;
        }
        while(array[i] <= pivot){
            i++;
        }
        if (i < j){
            swap(array, j, i);

        }
        
    }
    swap(array, low, j);

    return j;

}

void quicksort(vector<int> &array, int low , int high){

    if (low < high){
        int j = partition(array, low, high);
        // cout << "\n After partition" << endl;
        // cout << "\n j is " << j << endl;
        // cout << "\nlow is " << low << " High is " << high << endl;
        // cout << "\nArray is "<< endl;
        // print_vector(array);
        // getchar();
        quicksort(array, low, j);
        quicksort(array, j + 1, high);
    }
    return;

}

int main(void){

    vector<int> array = {9,3,7,5,6,4,8,2};
    array.push_back(9999);

    cout << "Initial Array : " << endl;
    print_vector(array);
    
    
    quicksort(array, 0, array.size() - 1);
    
    cout << "After Sorting : " << endl;
    print_vector(array);


}