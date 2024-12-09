#include <omnetpp.h>
#include "ReplicationManager.h"
#include "ManagerMessage_m.h"

using namespace omnetpp;

Define_Module(ReplicationManager);

void ReplicationManager::initialize() {}

void ReplicationManager::handleMessage(cMessage *msg) {
    ManagerMessage *request = check_and_cast<ManagerMessage *>(msg);
    std::string requestedData = request->getDataId();
    int edgeId = request->getEdgeId();
    std::string tempUserId = request->getUserId();

    // check if it's there in the manager files
    if (strcmp(request->getName(), "inform") == 0) // core node informing
    {
        if (m.find(requestedData) != m.end()) {
            EV << "REQUESTED DATA IS FOUND\n";
            // it's there
            bool found = false;

            for (auto i: m[requestedData])
            {
                if (i.getEdgeId() == edgeId) [[unlikely]]
                {
                    found = true;
                    i.incrementTimesCalled();

                    // this is the auto-replication
                    if (i.getTimesCalled() >= replicationThreshold && \
                            i.getReplicated() == false)
                    {
                        EV << "ENTERED THE REPLICATE IF STATEMENT IN THE REP_MAN\n";
                        replicateData(tempUserId, edgeId, requestedData);
                        i.setReplicated(true);
                    }
                }
            }

            if (!found)
            {
                NodeData n(edgeId, 1, false);
                m[requestedData].push_back(n);
            }

        } else {
            // it's not there in the manager files
            NodeData n(edgeId, 1, false);
            m[requestedData] = {n};
        }
    }
    else
    {
        // the request sent is because the edge node is deleting this from its cache
        for (auto i: m[requestedData]) {
            if (i.getEdgeId() == edgeId) {
                i.setReplicated(false);
                i.setTimesCalled(0);
            }
        }
    }

    // TODO: do i have to delete the message too...?
    delete msg;
}

void ReplicationManager::replicateData(std::string tempUserId, int edgeId, std::string dataId) {
    // Add logic to replicate data to edge nodes based on access patterns
    // Here we’d calculate access latency and select nodes for replication
    EV << "Replicating data to optimize latency\n";

    std::string dest = "replicate";
    char msgname[20];
    snprintf(msgname, sizeof(msgname), dest.c_str());

    ManagerMessage *rep_req = new ManagerMessage(msgname);
    rep_req->setUserId(tempUserId.c_str());
    rep_req->setEdgeId(edgeId);
    rep_req->setDataId(dataId.c_str());
    send(rep_req, "gate$o", 0);

    std::string coreReplicateBubble = "Replicate " + dataId + " at " + std::to_string(edgeId);
    bubble(coreReplicateBubble.c_str());
}
