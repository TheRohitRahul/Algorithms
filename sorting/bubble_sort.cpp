#include <iostream>
#include <vector>

using namespace std;

int randint(int low, int high){
    double rand_num = (double) rand() / (RAND_MAX);
    int r = int(((rand_num)*(high - low)) + low);
    return r;
}

// Procedure for swapping 2 elements
void swap(vector<int> &arr, int pos_1, int pos_2){
    
    int temp = arr[pos_1];
    arr[pos_1] = arr[pos_2];
    arr[pos_2] = temp;
}

void print_vector(vector<int> arr){
    for (auto a = arr.begin(); a!= arr.end(); ++a){
        cout << *a << "\t";
    }
    cout << "\n";
}


void bubble_sort(vector<int> &array){

    for (int i = 0; i < array.size(); i++){
        
        for (int j = 0; j < array.size()-i-1; j++){
            if (array[j] > array[j+1]){
                swap(array, j, j+1);
            }
        }
        /*
        Uncomment this if you want to print per pass output
        */
        // cout << "\nAfter pass : " << i << endl;
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
    bubble_sort(array);
    cout << "\nAfter sorting : " << endl;
    print_vector(array);


}