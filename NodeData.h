#include <omnetpp.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>

using namespace omnetpp;

class NodeData {
private:
    int edgeId;
    int timesCalled = 0;
    bool replicated = false;

public:
    NodeData(int eId, int timesCalled, bool replicated) {
        edgeId = eId;
        this->timesCalled = timesCalled;
        this->replicated = replicated;
    }

    int getEdgeId() {
        return this->edgeId;
    }

    int getTimesCalled() {
        return this->timesCalled;
    }

    bool getReplicated() {
        return this->replicated;
    }

    void setReplicated(bool value) {
        this->replicated = value;
    }

    void setTimesCalled(int value) {
        this->timesCalled = value;
    }

    void incrementTimesCalled() {
        this->timesCalled += 1;
    }
};


