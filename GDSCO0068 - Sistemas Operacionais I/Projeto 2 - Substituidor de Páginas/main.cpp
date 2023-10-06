#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

struct memory_instace{
    std::vector<int> page_references;
    int frames;
};

memory_instace read_file(char *path){
    std::ifstream file(path);
    memory_instace instance;
    int aux;

    if (!file.is_open())
        return {{}, NULL};

    file >> instance.frames;

    while (true){
        file >> aux;
        if (file.eof())
            break;
        instance.page_references.push_back(aux);
    }

    return instance;
}

template<typename Container>
void print_container(Container const &arr){
    printf("[");
    for (int i = 0; i < arr.size(); i++)
        printf("%d%s", arr[i], i + 1 == arr.size() ? "]\n" : ", ");
}

template<typename Container>
int getIndex(const Container& container, int element, int startIndex = 0, bool reverse = false){
    if(startIndex < 0 || startIndex >= container.size())
        return -1;
  
    for(int i=startIndex; reverse? (i>=0) : (i<container.size()); reverse? i-- : i++)
        if(container[i] == element)
            return i;
  
    return -1;
}

void FIFO(memory_instace &instance, std::deque<int> &frames, int next_idx){
    frames.pop_front();
    frames.push_back(instance.page_references[next_idx]);
}

void optimal(memory_instace &instance, std::deque<int> &frames, int next_idx){
    int max_idx = -1;
    int current_idx;
    int replace_idx;

    for(int i=0; i<frames.size(); i++){
        current_idx = getIndex(instance.page_references, frames[i], next_idx);

        if(current_idx == -1){
            frames[i] = instance.page_references[next_idx];
            return;
        }

        if(current_idx > max_idx){
            replace_idx = i;
            max_idx = current_idx;
        }
    }

    frames[replace_idx] = instance.page_references[next_idx];
}

void LRU(memory_instace &instance, std::deque<int> &frames, int next_idx){
    int min_idx = std::numeric_limits<int>::max();
    int current_idx;
    int replace_idx;

    for(int i=0; i<frames.size(); i++){
        current_idx = getIndex(instance.page_references, frames[i], next_idx, true);
        
        if(current_idx < min_idx){
            replace_idx = i;
            min_idx = current_idx;
        }
    }

    frames[replace_idx] = instance.page_references[next_idx];
}

int getNumberOfFaults(memory_instace& instance, void (*replacement_algorithm)(memory_instace&, std::deque<int>&, int)){
    std::deque<int> frames;
    int faults = 0;

    for(int i=0; i<instance.page_references.size(); i++){
        if(getIndex(frames, instance.page_references[i]) == -1){
            faults++;
            if(frames.size() == instance.frames)
                replacement_algorithm(instance, frames, i);
            else
                frames.push_back(instance.page_references[i]);
        }
    }

    return faults;
}


int main(int argc, char *argv[]){
    memory_instace i = read_file(argv[1]);

    printf("FIFO: %d\n",  getNumberOfFaults(i, &FIFO));
    printf("OTM: %d\n",  getNumberOfFaults(i, &optimal));
    printf("LRU: %d\n", getNumberOfFaults(i, &LRU));

    return 0;
}