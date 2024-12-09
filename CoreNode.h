#include <omnetpp.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "DataItem.h"

using namespace omnetpp;

class CoreNode : public cSimpleModule {
private:
    std::unordered_map<std::string, DataItem> dataStore; // Keyed by data ID

    void loadDataFromFile(const std::string &filename);

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};
