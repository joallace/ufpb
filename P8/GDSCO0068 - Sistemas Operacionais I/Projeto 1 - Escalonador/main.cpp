#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

// ------======Estruturas======------

template <typename T> struct execution_measures {
    T t_ret; // Tempo de Retorno
    T t_ans; // Tempo de Resposta
    T t_wtn; // Tempo de Espera

    execution_measures& operator +=(const execution_measures &other){
        t_ret += other.t_ret;
        t_ans += other.t_ans;
        t_wtn += other.t_wtn;

        return *this;
    }
};

struct process{
    int arrival;
    int duration;
    execution_measures<int> measures;
};



//------======Funções Auxiliares======------

void print_process(std::vector<process> &process_entries){
    printf("[");
    for(int i = 0; i < process_entries.size(); i++)
        printf("(%d %d)%s", process_entries[i].arrival, process_entries[i].duration, i+1 == process_entries.size()?"]\n":", ");
}

void print_queue(std::queue<int> q){
  while (!q.empty())
  {
    std::cout << q.front() << " ";
    q.pop();
  }
  std::cout << std::endl;
}

std::vector<process> read_file(char *path){
    std::ifstream file(path);
    std::vector<process> process_entries;

    if(file.is_open()){
        int arrival;
        int duration;

        while(true){
            file >> arrival;
            file >> duration;

            if(file.eof()) break;

            process_entries.push_back({arrival, duration});
        }
    }
    
    return process_entries;
}

void update_measures(std::vector<process> &process_queue, execution_measures<float> &averages, int &t, int i){
    int t_ans = std::max(process_queue[i].arrival, t - process_queue[i].arrival);
    int t_ret = t + process_queue[i].duration - process_queue[i].arrival;
    int t_wtn = t - process_queue[i].arrival;

    process_queue[i].measures = {t_ret, t_ans, t_wtn};

    averages += execution_measures<float>{
        (float) t_ret/process_queue.size(),
        (float) t_ans/process_queue.size(),
        (float) t_wtn/process_queue.size()
    };

    std::cout << "(t=" << t << ") P"<< i << ": " << process_queue[i].arrival  << " " << process_queue[i].duration << "  " << process_queue[i].measures.t_ret << " " << process_queue[i].measures.t_ans << " " << process_queue[i].measures.t_wtn << "\n";

    t += process_queue[i].duration;
}



//------======Métodos======------

execution_measures<float> FCFS(std::vector<process> process_queue){
    execution_measures<float> averages = {0.0, 0.0, 0.0};
    int t;

    std::sort(process_queue.begin(), process_queue.end(), 
        [](const process &a, const process &b) -> bool{
            return a.arrival < b.arrival;
        }
    );

    t = process_queue[0].arrival;
    for(int i=0; i < process_queue.size(); i++){
        update_measures(process_queue, averages, t, i);
    }

    return averages;
}

execution_measures<float> SJF(std::vector<process> process_queue){
    execution_measures<float> averages = {0.0, 0.0, 0.0};  // Médias 
    int current = 0;
    int t;

    auto first = std::min_element(process_queue.begin(), process_queue.end(),
                    [](const process &a, const process &b) -> bool{
                        return a.arrival < b.arrival;
                    }
                );
    
    t = first->arrival;
    for(int i = 0; i < process_queue.size(); i++){
        for(int j = i; j < process_queue.size(); j++)
            if(process_queue[j].arrival <= t && process_queue[j].duration < process_queue[current].duration)
                current = j;

        if(i+1 != process_queue.size())
            std::swap(process_queue[i], process_queue[current]);
        update_measures(process_queue, averages, t, i);
        print_process(process_queue);
    }

    // std::cout << "(t=" << t << ")\n";
    return averages;
}

execution_measures<float> RR(std::vector<process> process_queue, int quantum){
    execution_measures<float> averages = {0.0, 0.0, 0.0};
    int remaining_time[process_queue.size()];
    bool entered[process_queue.size()] = {0};
    std::queue<int> q;
    int t, done = 0;

    for(int i = 0; i < process_queue.size(); i++)
        remaining_time[i] = process_queue[i].duration;

    std::sort(process_queue.begin(), process_queue.end(), 
        [](const process &a, const process &b) -> bool{
            return a.arrival < b.arrival;
        }
    );

    q.push(0);
    t = process_queue[0].arrival;
    entered[0] = true;
    while (done != process_queue.size()){
        if(remaining_time[q.front()] == process_queue[q.front()].duration){
            process_queue[q.front()].measures.t_ans = t - process_queue[q.front()].arrival;
            if(q.front() != 0)
                process_queue[q.front()].measures.t_ans -= quantum;
        }

        remaining_time[q.front()] -= quantum;

        if(remaining_time[q.front()] > 0)
            q.push(q.front());
        else{
            done++;
            t += remaining_time[q.front()];

            if(done == process_queue.size())
                t += quantum;

            process_queue[q.front()].measures.t_ret = t - process_queue[q.front()].arrival;
            process_queue[q.front()].measures.t_wtn = t - process_queue[q.front()].arrival - process_queue[q.front()].duration;

            std::cout << "(t=" << t << ") P"<< q.front() << ": " << process_queue[q.front()].arrival  << " " << process_queue[q.front()].duration << "  " << process_queue[q.front()].measures.t_ret << " " << process_queue[q.front()].measures.t_ans << " " << process_queue[q.front()].measures.t_wtn << "\n";

            averages += execution_measures<float>{
                (float) process_queue[q.front()].measures.t_ret/process_queue.size(),
                (float) process_queue[q.front()].measures.t_ans/process_queue.size(),
                (float) process_queue[q.front()].measures.t_wtn/process_queue.size()
            };

        }

        t += quantum;

        for(int i=1; i < process_queue.size(); i++){
            if(!entered[i] && q.empty())
                t = process_queue[i].arrival;
            if(!entered[i] && process_queue[i].arrival <= t){
                entered[i] = true;
                q.push(i);
            }
        }
        
        q.pop();

        printf("(t=%d) \{P%c\} [", t, q.front()+65);
        for(int i = 0; i < process_queue.size(); i++)
            printf("%d%s", remaining_time[i], i+1 == process_queue.size()?"] - ":", ");
        print_queue(q);
    };
    
    return averages;
}



int main(int argc, char *argv[]){
    std::vector<process> process_entries = read_file(argv[1]);
    execution_measures result = FCFS(process_entries);

    printf("FCFS: %.1f %.1f %.1f\n", result.t_ret, result.t_ans, result.t_wtn);

    result = SJF(process_entries);
    printf("SJF: %.1f %.1f %.1f\n", result.t_ret, result.t_ans, result.t_wtn);

    result = RR(process_entries, 2);
    printf("RR: %.1f %.1f %.1f\n", result.t_ret, result.t_ans, result.t_wtn);

    return 0;
}