#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

struct process{
    int arrival;
    int duration;
};

void print_process(std::vector<process> &process_entries){
    printf("[");
    for(int i = 0; i < process_entries.size(); i++)
        printf("(%d, %d)%s", process_entries[i].arrival, process_entries[i].duration, i+1 == process_entries.size()?"]\n":", ");
}

void print_queue(std::queue<int> q)
{
  while (!q.empty())
  {
    std::cout << q.front() << " ";
    q.pop();
  }
  std::cout << std::endl;
}


int main() {
    std::vector<process> p = {{0, 20}, {0, 10}, {4, 6}, {4, 8}};
    bool entered[p.size()] = {0};
    int r[p.size()];
    std::queue<int> q;
    int t, quantum = 2;

    std::sort(p.begin(), p.end(), 
        [](const process &a, const process &b) -> bool{
            return a.arrival < b.arrival;
        }
    );

    t = p[0].arrival;
    printf("(t=%d) \{P%c\} [", t, q.front()+65);
    for(int i = 0; i < p.size(); i++)
        printf("%d%s", r[i], i+1 == p.size()?"] - ":", ");
    print_queue(q);

    do{
        for(int i=0; i < p.size(); i++)
            if(!entered[i] && p[i].arrival <= t){
                entered[i] = true;
                r[i] = p[i].duration;
                q.push(i);
            }
        r[q.front()] -= quantum;

        if(r[q.front()] > 0)
            q.push(q.front());
        else
            t += r[q.front()];

        t += quantum;
        q.pop();

        printf("(t=%d) \{P%c\} [", t, q.front()+65);
        for(int i = 0; i < p.size(); i++)
            printf("%d%s", r[i], i+1 == p.size()?"] - ":", ");
        print_queue(q);

    } while (!q.empty());

//   print_process(p);

  return 0;
}
