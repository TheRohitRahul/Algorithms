#include <iostream>
#include <vector>

using namespace std;

int randint(int low, int high){
    double rand_num = (double) rand() / (RAND_MAX);
    int r = int(((rand_num)*(high - low)) + low);
    return r;
}

// Procedure for swapping 2 elements
void insert_element(vector<int> &arr, int pos_insert, int pos_to_insert){
    // cout << "\ninserting element " << pos_to_insert << " at " << pos_insert;
    int temp = arr[pos_to_insert];
    for ( int k = pos_to_insert - 1; k >= pos_insert; k--){
        arr[k + 1] = arr[k];
    }
    arr[pos_insert] = temp;
}

void print_vector(vector<int> arr){
    for (auto a = arr.begin(); a!= arr.end(); ++a){
        cout << *a << "\t";
    }
    cout << "\n";
}

void insertion_sort(vector<int> &array){

    for (int i = 1; i < array.size(); i++){
        
        int pos_insert = i;
        int pos_to_insert = i;
        int j = i - 1;
        while(array[j] > array[i]){
            pos_insert = j;
            j--; 
         }
        if (pos_insert != pos_to_insert){
            insert_element(array, pos_insert, pos_to_insert);
        }
        /*
        Uncomment this if you want to see the output at every pass
        */
        // cout << "\nOutput at pass "<< i << " is " <<endl;
        // print_vector(array);

    }
    
}

int main(void){
    vector<int> array;

    for (int i = 0; i < 10 ; i++){
        array.push_back(randint(2, 70));
    }

    cout << "\nInitial Vector : "<< endl;
    print_vector(array);
    insertion_sort(array);
    cout << "\nAfter sorting : " << endl;
    print_vector(array);


}