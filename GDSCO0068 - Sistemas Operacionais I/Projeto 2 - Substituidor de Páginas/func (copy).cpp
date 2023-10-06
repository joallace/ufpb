#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <set>

struct memory_instace
{
    std::vector<int> page_references;
    int frames;
};

memory_instace read_file(char *path)
{
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

void print_instance(std::vector<int> const &page_refereces)
{
    printf("[");
    for (int i = 0; i < page_refereces.size(); i++)
        printf("%d %s", page_refereces[i], i + 1 == page_refereces.size() ? "]\n" : ", ");
}

void print_instance(std::deque<int> const &page_refereces)
{
    printf("[");
    for (int i = 0; i < page_refereces.size(); i++)
        printf("%d %s", page_refereces[i], i + 1 == page_refereces.size() ? "]\n" : ", ");
}

int FIFO(memory_instace instance){
    std::deque<int> frames;
    int faults = instance.frames;
    bool inside;

    for(int i=0; i<instance.frames; i++)
        frames.push_back(instance.page_references[i]);

    for(int i=instance.frames; i<instance.page_references.size(); i++){
        print_instance(frames);
        inside = false;
        for(int j=0; j<instance.frames; j++)
            if(instance.page_references[i] == frames[j]){
                inside = true;
                break;
            }

        if(!inside){
            faults++;
            frames.pop_front();
            frames.push_back(instance.page_references[i]);
        }
    }

    return faults;
}

int optimal(memory_instace instance){
    std::deque<int> frames(instance.frames);
    std::set<int> entry_order;
    int faults = instance.frames;
    bool inside;

    for(int i=0; i<frames.size(); i++)
        frames[i] = instance.page_references[i];

    for(int i=frames.size(); i<instance.page_references.size(); i++){
        print_instance(frames);
        inside = false;
        for(int j=0; j<frames.size(); j++)
            if(instance.page_references[i] == frames[j]){
                inside = true;
                break;
            }

        if(!inside){
            faults++;

            entry_order.clear();
            for(int j=i; (entry_order.size()<frames.size()) || (j<instance.page_references.size()); j++)
                entry_order.insert(instance.page_references[j]);
            for(int j=0; j<frames.size(); j++)
                if(frames[j] == *entry_order.rbegin())
                    frames[j] = instance.page_references[i];
        }
    }

    return faults;
}

int LRU(memory_instace instance){
    std::deque<int> frames(instance.frames);
    std::vector<int> entry_order;
    int faults = instance.frames;
    bool inside;
    print_instance(instance.page_references);

    for(int i=0; i<frames.size(); i++)
        frames[i] = instance.page_references[i];

    for(int i=frames.size(); i<instance.page_references.size(); i++){
        print_instance(frames);
        inside = false;
        for(int j=0; j<frames.size(); j++)
            if(instance.page_references[i] == frames[j]){
                inside = true;
                break;
            }

        if(!inside){
            faults++;

            entry_order.clear();
            for(int j=i; (entry_order.size()<frames.size()) || (j>=0); j--){
                // printf("%d\n", instance.page_references[j]);
                inside=false;
                for(int k=0; k<entry_order.size(); k++)
                    if(instance.page_references[j] == entry_order[k]){
                        inside=true;
                        break;
                    }
                if(!inside)
                    entry_order.push_back(instance.page_references[j]);
            }

            for (auto it = entry_order.begin(); it != entry_order.end(); ++it)
                std::cout << ' ' << *it;
            for(int j=0; j<frames.size(); j++)
                if(frames[j] == *entry_order.rbegin()){
                    printf("UEPA\n");
                    frames[j] = instance.page_references[i];
                }
        }
    }

    return faults;
}


int main()
{
    memory_instace i = read_file("inputs/especificação.txt");

    printf("Frames: %d\n", i.frames);
    print_instance(i.page_references);
    printf("\nFIFO: %d\n", FIFO(i));
    printf("OTM: %d\n", optimal(i));
    printf("LRU: %d\n", LRU(i));
    return 0;
}