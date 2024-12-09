#include <omnetpp.h>
#include <unordered_map>
#include <string>
#include <vector>

using namespace omnetpp;

struct DataItem {
    std::string id;
    std::string type;
    int size;
    int access_frequency;
};


