#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// ------======Estruturas======------

template <typename T> struct execution_measures {
    T t_ret; // Tempo de Retorno
    T t_ans; // Tempo de Resposta
    T t_wtn; // Tempo de Espera

    execution_measures& operator +=(const execution_measures& other){
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

void update_measures(std::vector<process> &process_queue, execution_measures<float> &means, int &t, int i){
    int t_ans = std::max(process_queue[i].arrival, t - process_queue[i].arrival);
    int t_ret = t + process_queue[i].duration - process_queue[i].arrival;
    int t_wtn = t - process_queue[i].arrival;

    process_queue[i].measures = {t_ret, t_ans, t_wtn};
    std::cout << "(t=" << t << ") P"<< i << ": " << process_queue[i].arrival  << " " << process_queue[i].duration << "  " << process_queue[i].measures.t_ret << " " << process_queue[i].measures.t_ans << " " << process_queue[i].measures.t_wtn << "\n";

    means += execution_measures<float>{
        (float) t_ret/process_queue.size(),
        (float) t_ans/process_queue.size(),
        (float) t_wtn/process_queue.size()
    };

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
    bool finished = false;
    int i;
    int t;

    for(i = 0; i < process_queue.size(); i++)
        remaining_time[i] = process_queue[i].duration;

    std::sort(process_queue.begin(), process_queue.end(), 
        [](const process &a, const process &b) -> bool{
            return a.arrival < b.arrival;
        }
    );

    t = process_queue[0].arrival;
    while(!finished){
        finished = true;
        i = 0;

        for(int i=0; i < process_queue.size(); i++){
            if(remaining_time[i] == 0 || process_queue[i].arrival > t)
                continue;

            remaining_time[i] -= quantum;

            if(remaining_time[i] <= 0){
                t += quantum + remaining_time[i];
                remaining_time[i] = 0;
                update_measures(process_queue, averages, t, i);
            } else{
                finished = false;
                t += quantum;
            }

            printf("(t=%d) [", t);
            for(int i = 0; i < process_queue.size(); i++)
                printf("%d%s", remaining_time[i], i+1 == process_queue.size()?"]\n":", ");
        }
        i++;
    }
    
    return averages;
}



int main(int argc, char *argv[]){
    std::vector<process> process_entries = read_file(argv[1]);
    execution_measures result = FCFS(process_entries);

    std::cout << "FCFS: " << result.t_ret << " " << result.t_ans << " " << result.t_wtn << "\n";

    result = SJF(process_entries);
    std::cout << "SJF: " << result.t_ret << " " << result.t_ans << " " << result.t_wtn << "\n";

    result = RR(process_entries, 2);
    std::cout << "RR: " << result.t_ret << " " << result.t_ans << " " << result.t_wtn << "\n";

    return 0;
}