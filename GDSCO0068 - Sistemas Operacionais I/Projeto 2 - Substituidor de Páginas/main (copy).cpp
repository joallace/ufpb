#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

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

    while (true)
    {
        file >> aux;
        if (file.eof())
            break;
        instance.page_references.push_back(aux);
    }

    return instance;
}

void print_instance(std::deque<int> const &page_refereces){
    printf("[");
    for (int i = 0; i < page_refereces.size(); i++)
        printf("%d %s", page_refereces[i], i + 1 == page_refereces.size() ? "]\n" : ", ");
}

template<typename Container, typename T>
int findElementIndex(const Container& container, const T& element) {
    int index = 0;

    for(const auto& item : container) {
        if(item == element)
            return index;
        index++;
    }

    return -1;  // Element not found
}


void FIFO(memory_instace &instance, std::deque<int> &frames, int i){
    frames.pop_front();
    frames.push_back(instance.page_references[i]);
}

void optimal(memory_instace &instance, std::deque<int> &frames, int i){
    std::vector<int> entry_order;
    bool inside;

    for(int j=i; (entry_order.size()<frames.size()) || (j<instance.page_references.size()); j++){
        inside=false;
        for(int k=0; k<entry_order.size(); k++)
            if(instance.page_references[j] == entry_order[k]){
                    inside=true;
                    break;
                }
        if(!inside)
            entry_order.push_back(instance.page_references[j]);
    }

    for(int j=0; j<frames.size(); j++)
        if(frames[j] == entry_order.back()){
            frames[j] = instance.page_references[i];
            return;
        }
}


void LRU(memory_instace &instance, std::deque<int> &frames, int i){
    std::vector<int> entry_order;
    bool inside;

    for(int j=i; (entry_order.size()<frames.size()) || (j>=0); j--){
        inside=false;
        for(int k=0; k<entry_order.size(); k++)
            if(instance.page_references[j] == entry_order[k]){
                inside=true;
                break;
            }
        if(!inside)
            entry_order.push_back(instance.page_references[j]);
    }

    for(int j=0; j<frames.size(); j++)
        if(frames[j] == entry_order.back()){
            frames[j] = instance.page_references[i];
            return;
        }
}

int getNumberOfFaults(memory_instace& instance, void (*algorithm)(memory_instace&, std::deque<int>&, int)){
    std::deque<int> frames(instance.frames);
    int faults = instance.frames;
    bool inside;

    for(int i=0; i<frames.size(); i++)
        frames[i] = instance.page_references[i];

    print_instance(frames);

    for(int i=frames.size(); i<instance.page_references.size(); i++){
        inside = false;
        for(int j=0; j<frames.size(); j++)
            if(instance.page_references[i] == frames[j]){
                inside = true;
                break;
            }

        if(!inside){
            faults++;
            algorithm(instance, frames, i);
            print_instance(frames);
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