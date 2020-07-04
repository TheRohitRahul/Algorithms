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

struct return_struct{
    int low, high;
};

// Assumption is ret1 would be lower than ret2 in position
void merge(vector<int> &arr, return_struct ret1, return_struct ret2){
    int l1_high = ret1.high;
    int l2_high = ret2.high;

    int l1_pointer = ret1.low;
    int l2_pointer = ret2.low;


    vector <int> temp_list ;
    while (l1_pointer <= l1_high && l2_pointer <= l2_high){
       if (arr[l1_pointer] < arr[l2_pointer]){
           temp_list.push_back(arr[l1_pointer]);
           l1_pointer++;
       
       }
       else{
           temp_list.push_back(arr[l2_pointer]);
           l2_pointer++; 
       }
       
    }

    if (l1_pointer <= l1_high){
        for (int i = l1_pointer; i <= l1_high; i++){
            temp_list.push_back(arr[i]);
        }
    }
    else if (l2_pointer <= l2_high){
        for (int i = l2_pointer; i <= l2_high; i++){
            temp_list.push_back(arr[i]);
        }
    }
    // At this point the length of temp_list should be equal to length of list1 + length of list2. Therefore we would just copy the temp list

    int counter_list = 0;
    for (int i = ret1.low; i <= ret1.high; i++){
        arr[i] = temp_list[counter_list];
        counter_list++;
    }

    for (int i = ret2.low; i <= ret2.high; i++){
        arr[i] = temp_list[counter_list];
        counter_list++;
    }


}

return_struct merge_sort(vector<int> &arr, int low, int high){
    return_struct ret;

    if (low < high){
        int mid = int((low + high) / 2);
        return_struct ret1, ret2;
        ret1 = merge_sort(arr, low, mid);
        ret2 = merge_sort(arr, mid + 1, high);
        merge(arr, ret1, ret2);
        ret.low = ret1.low;
        ret.high = ret2.high;
        return ret;

    }
    // The base case
    else{
        // cout << "\nlow is "<< low << " high is "<< high << endl;
        ret.low = low;
        ret.high = high;
        return ret;
    }
}

int main(void){

    vector<int> arr = {9,3,7,5,6,4,8,2};
    cout << "\nInitial vector " << endl;
    print_vector(arr);
    merge_sort(arr, 0, arr.size() - 1);
    cout << "\nafter running merge sort "<< endl;
    print_vector(arr);
}