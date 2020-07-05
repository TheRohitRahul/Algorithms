#include <iostream>
#include <vector>

using namespace std;

struct job{
    double profit, max_wait_time;
};

struct return_type{
    int max_index, max_element;
};

void print_jobs(vector<job> jobs){
    cout << "profit   : ";
    for (int i = 0; i < jobs.size(); i++){
        cout << jobs[i].profit << "\t";
    }
    cout << endl;

    cout << "max wait : ";
    for (int i = 0; i < jobs.size(); i++){
        cout << jobs[i].max_wait_time << "\t";
    }
    cout << endl;
}

int randint(int low, int high){
    double rand_num = (double) rand() / (RAND_MAX);
    int r = int(((rand_num)*(high - low)) + low);
    return r;
}


return_type find_max(vector<job> jobs){

    return_type ret;
    ret.max_element = -1;
    ret.max_index = -1;

    for (int i = 0; i < jobs.size(); i++){
        if (jobs[i].profit > ret.max_element){
            ret.max_element = jobs[i].profit;
            ret.max_index = i;
        }

    }

    return ret;
}

vector<job> schedule_jobs(vector<job> jobs){
    vector<job> scheduled_jobs;
    vector<int> num_slots;

    int max_wait_time = 0;
    for (int i = 0; i < jobs.size(); i++){
        if (jobs[i].max_wait_time > max_wait_time){
            max_wait_time = jobs[i].max_wait_time;

        }
    }
    // cout << "\nmaximum time a person is ready to wait is : "<< max_wait_time;

    /*
    -1 means unassigned slot
    Here we are initializing both num_slots and scheduled jobs
    */
    for (int i = 0; i < max_wait_time; i++){
        num_slots.push_back(-1);
        job dummy_job;
        scheduled_jobs.push_back(dummy_job);
    }

    for(int i = 0; i < num_slots.size(); i++){
        return_type ret = find_max(jobs);
        int j = jobs[ret.max_index].max_wait_time;
        
        while(num_slots[j] != -1 && j >= 0){
            j--;
        }
        if (j >= 0 && num_slots[j] == -1){
            num_slots[j] = jobs[ret.max_index].profit;
            scheduled_jobs[j] = jobs[ret.max_index];
        }
        jobs.erase(jobs.begin() + ret.max_index);
        // cout << "At iteration "<< i << endl;
        // print_jobs(jobs);

    }

    return scheduled_jobs;
}

int main(void){
    vector<job> jobs;

    for (int i = 0; i < 10; i++){
        job temp_job;
        temp_job.profit = randint(2, 30);
        temp_job.max_wait_time = randint(1,5);
        jobs.push_back(temp_job);
    }

    cout << "\nIncoming Jobs are : " << endl;
    print_jobs(jobs);

    vector<job> scheduled_jobs = schedule_jobs(jobs);

    cout << "\nJobs after they are scheduled : " << endl;
    print_jobs(scheduled_jobs);


}