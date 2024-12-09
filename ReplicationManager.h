#ifndef REPLICATIONMANAGER_H_
#define REPLICATIONMANAGER_H_

#include <omnetpp.h>
#include "NodeData.h"

using namespace omnetpp;

// Node class
//class Node : public cSimpleModule
//{
//    protected:
//        virtual void initialize() override;
//        virtual void handleMessage(cMessage *msg) override;
//        void sendDataRequest(); // Function for edge nodes to send requests
//};

class ReplicationManager : public cSimpleModule
{
private:
    std::unordered_map<std::string, std::vector<NodeData>> m;

protected:
    int replicationThreshold = 5; // set to a low val due to limited simulation time
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void replicateData(std::string tempUserId, int edgeId, std::string dataId); // Function to manage data replication
};

#endif /* REPLICATIONMANAGER_H_ */
