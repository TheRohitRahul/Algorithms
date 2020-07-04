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

void find_longest_equal_or_increasing_subsequence(vector<int> &arr){

    vector<int> longest_vec;
    for (int i = 0; i < arr.size(); i++){
        longest_vec.push_back(1);
    }

    for (int j = 1; j < arr.size(); j++){
        for (int i = 0; i < j; i++){
            if (arr[i] <= arr[j]){
                longest_vec[j] = longest_vec[i] + 1;
            }
            
        }

    }
    print_vector(longest_vec);
    // return longest_vec;

}

int main(void){
    // vector<int> arr = {1,2,3,4,5,1,2,2,2,2,2};
    vector<int> arr = {8,2,3,4,5,1,2,2,2,2,2};
    cout << "\nInitial vector : "<< endl;
    print_vector(arr);
    find_longest_equal_or_increasing_subsequence(arr);
    cout << "\nLongest increasing or equal subsequence : "<< endl;    
}