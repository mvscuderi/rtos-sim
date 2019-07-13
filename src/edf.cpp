#include <bits/stdc++.h>
#include <queue>

using namespace std;

#define BUFFER 100

typedef struct context{
    public:
        int time;
        int task_id;
        int execution_time;
        int deadline;
        int identifier;
        int frequency;
} context; 

typedef struct Comparator{
    bool operator()(context const& p1, context const& p2){
        return p1.deadline > p2.deadline ||
                (p1.deadline == p2.deadline && p1.task_id > p2.task_id);
    }
} Comparator;

int main(int argc, char** argv){
    int n_tasks = -1;
    int n_events = -1;
    int overhead=0;
    FILE* setup_file = NULL;
    FILE* arrivals_file = NULL;

     /* Open the input and output file(s). */
    int i = 1;
    setup_file = fopen(argv[i++],"r");
    arrivals_file = fopen(argv[i++],"r");
    
    fscanf(setup_file,"%d", &n_tasks);
    int* task_id = (int*)malloc(sizeof(int)*(n_tasks+4));
    int* frequency = (int*)malloc(sizeof(int)*n_tasks+4);
    int task_counter[BUFFER] = {0};


    for (int j=1; j<=n_tasks; j++){
        fscanf(setup_file,"%d", &task_id[j]);
        fscanf(setup_file,"%d", &frequency[j]);
    }

    fscanf(setup_file,"%d", &overhead);

    fclose(setup_file);

    fscanf(arrivals_file,"%d", &n_events);

    int time_buffer;
    int task_id_buffer;
    int execution_time_buffer;
    int deadline_buffer;
    float utilization=0;
    int execute[BUFFER] = {0}; 
    int visited[BUFFER] = {0};
    int task_num[BUFFER] = {0};
    int preempted[BUFFER] = {0};
    int instance[BUFFER] = {0};
    int ident = 1;

    queue<context> q;
    priority_queue<context, vector<context>, Comparator> pq;

    for (int j=0; j<n_events; j++){
        fscanf(arrivals_file,"%d", &time_buffer);
        fscanf(arrivals_file,"%d", &task_id_buffer);
        fscanf(arrivals_file,"%d", &execution_time_buffer);
        fscanf(arrivals_file,"%d", &deadline_buffer);
        q.push({time_buffer, task_id_buffer, execution_time_buffer, deadline_buffer,j+1,frequency[task_id_buffer]});
        execute[ident] = execution_time_buffer;
        task_num[ident] = 1;
        ident++;
        utilization += (float)execution_time_buffer/deadline_buffer;
    }
    fclose(arrivals_file);

    /**************************EDF SCHEDULER**************************/
    
    int clk=0;
    int idle=1;
    int preemption_instance=1;
    int prev_task = -1; //identifier of task run on previous clk tick
    
    while (!q.empty() || !pq.empty()){
            while (q.front().time <= clk && !q.empty()){
                pq.push(q.front());
                q.pop();
            }

        if (!pq.empty()){
            if (prev_task == -1){
                prev_task = pq.top().identifier;
            }

            if (preempted[pq.top().identifier] == 1){
                printf("%d %d.%d\n", clk, pq.top().task_id, instance[pq.top().identifier]);
                preempted[pq.top().identifier] = 0;
            }

            if ((prev_task != pq.top().identifier) && (execute[prev_task] > 0)){
                if (overhead != 0){
                    printf("%d %d.%d\n", clk, 0, preemption_instance);
                    clk += overhead;
                }
                preemption_instance++;
                preempted[prev_task] = 1;
                prev_task = pq.top().identifier;
                continue;
            }

            if (visited[pq.top().identifier] == 0){ 
                printf("%d %d.%d\n", clk, pq.top().task_id, task_num[pq.top().task_id]);
                instance[pq.top().identifier] = task_num[pq.top().task_id];
                task_num[pq.top().task_id]++;
                visited[pq.top().identifier] = 1;
            }
            execute[pq.top().identifier] -=1;
            if (execute[pq.top().identifier] <=0){
                pq.pop();
                if (pq.empty() && q.front().time != clk+1){
                    printf("%d %d.%d\n", clk+1, -1, idle);
                    idle++;
                }
            }
         } 
        prev_task = pq.top().identifier;
        clk++;
    }
    return 0;
}
