/*
A program to find the solution to the knapsack problem using greedy method
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct object{
    double weight, price;
};

void print_objects(vector<object> objects){
    cout << "price   : ";
    for (int i = 0; i < objects.size(); i++){
        cout << objects[i].price << "\t";
    }
    cout << endl;

    cout << "weights : ";
    for (int i = 0; i < objects.size(); i++){
        cout << objects[i].weight << "\t";
    }
    cout << endl;
}

int randint(int low, int high){
    double rand_num = (double) rand() / (RAND_MAX);
    int r = int(((rand_num)*(high - low)) + low);
    return r;
}

vector <object> knapsack(vector<object> objects, int knapsack_size){
    vector<double> price_to_weight_ratio;
    int weight_taken_thus_far = 0;
    vector <object> objects_in_sack;


    for (int i = 0 ; i < objects.size(); i++){
        double price = objects[i].price;
        double weight = objects[i].weight;
        price_to_weight_ratio.push_back(price/weight);
    }

    while(price_to_weight_ratio.size() > 0 && weight_taken_thus_far < knapsack_size){
        int index = distance(price_to_weight_ratio.begin(), max_element(price_to_weight_ratio.begin(), price_to_weight_ratio.end()));

        
        double object_weight = objects[index].weight;
        double object_price = objects[index].price;

        if (object_weight <= knapsack_size - weight_taken_thus_far){
            object item;
            item.weight = object_weight;
            item.price = object_price;
            weight_taken_thus_far += item.weight;

            objects_in_sack.push_back(item);
            
        }
        else if (knapsack_size - weight_taken_thus_far > 0){
            object item;
            
            double unit_price = price_to_weight_ratio[index];
            item.weight = knapsack_size - weight_taken_thus_far;
            item.price = unit_price*item.weight;
            
            weight_taken_thus_far += item.weight;

            objects_in_sack.push_back(item);
        }

        price_to_weight_ratio.erase(price_to_weight_ratio.begin() + index);


    }
    return objects_in_sack;
}

int main(void){
    vector<object> objects;

    for (int i = 0; i < 10; i++){
        object temp_obj ;
        temp_obj.price = double(randint(1, 20));
        temp_obj.weight = double(randint(1, 20));      
        objects.push_back(temp_obj);
    }
    
    print_objects(objects);
    vector <object> objects_in_sack = knapsack(objects, 25);
    cout << "Objects in sack : " << endl;
    print_objects(objects_in_sack);

    
}