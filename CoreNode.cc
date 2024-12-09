#include <fstream>
#include <omnetpp/cpacket.h>
#include "json.hpp"
#include "CoreNode.h"
#include "DataRequest_m.h"
#include "CoreRequest_m.h"
#include "ManagerMessage_m.h"
#include "ReplicateRequest_m.h"

using namespace omnetpp;

Define_Module(CoreNode);

void CoreNode::initialize() {
    // Load data from the file
    loadDataFromFile("synthetic_data.json");
    EV << "Core Node initialized with " << dataStore.size() << " data items.\n";
}

void CoreNode::handleMessage(cMessage *msg) {
    // convert the received message to the right data type
    if (strcmp(msg->getName(), "edge_request") == 0)
    {
        CoreRequest *edge_msg = check_and_cast<CoreRequest *>(msg);
        std::string requestedData = edge_msg->getDataId();
        int edgeId = edge_msg->getEdgeId();
        int size = dataStore[requestedData].size;
        std::string tempUserId = edge_msg->getUserId();
        int userId = std::stoi(tempUserId.substr(1, 1));

        // check if it's worth replicating
        // TODO: find a formula for this
        bool worthIt = true; // placeholder

        // if it's worth replicating, then replicate it to the edge node directly
        if (worthIt) {
            std::string dest = "replicate";
            float time = float(size) / 2000; // random number chosen here
            char msgname[20];
            snprintf(msgname, sizeof(msgname), dest.c_str());

            ReplicateRequest *replicate = new ReplicateRequest(msgname);
            replicate->setEdgeId(edgeId);
            replicate->setUserId(tempUserId.c_str());
            replicate->setDataId(edge_msg->getDataId());
            replicate->setType(dataStore[requestedData].type.c_str());
            replicate->setSize(dataStore[requestedData].size);
            sendDelayed(replicate, time, "gate$o", edgeId - 1);

            std::string sendingEdgeBubble = "Sending " + requestedData + " to edge " \
                    + std::to_string(edgeId) + " in " + std::to_string(time) + "s";
            bubble(sendingEdgeBubble.c_str());

//            ManagerMessage *replicate = new ManagerMessage(msgname);
//            replicate->setEdgeId(edge_msg->getEdgeId());
//            replicate->setDataId(requestedData.c_str());
//            replicate->setUserId(tempUserId.c_str());
//            send(replicate, "gate$o", 5); // to the replication manager
        } else {
            // send data directly to connected user
            std::string tempUserId = edge_msg->getUserId();
            int userId = std::stoi(tempUserId.substr(1, 1));
            float time = float(size) / 2000; // random number chosen
            cMessage *user_msg = new cMessage("sendRequest");
            sendDelayed(user_msg, time, "gate$o", userId + 5);
        }

        // inform the replication manager
        std::string dest = "inform";
        char msgname[20];
        snprintf(msgname, sizeof(msgname), dest.c_str());

        ManagerMessage *inform = new ManagerMessage(msgname);
        inform->setEdgeId(edge_msg->getEdgeId());
        inform->setDataId(requestedData.c_str());
        inform->setUserId(tempUserId.c_str());
        send(inform, "gate$o", 5);
    }

    // TODO: Do I even need this anymore?
//    else
//    {
//        ManagerMessage *rep_man_msg = check_and_cast<ManagerMessage *>(msg);
//        int edgeId = rep_man_msg->getEdgeId();
//        std::string requestedData = rep_man_msg->getDataId();
//        float time = float(dataStore[requestedData].size) / 500; // random number chosen
//
//        std::string dest = "replicate";
//        char msgname[20];
//        snprintf(msgname, sizeof(msgname), dest.c_str());
//
//
//        ReplicateRequest *rep_req = new ReplicateRequest(dest.c_str());
//        rep_req->setEdgeId(edgeId);
//        rep_req->setUserId(rep_man_msg->getUserId());
//        rep_req->setDataId(rep_man_msg->getDataId());
//
//        sendDelayed(rep_req, time, "gate$o", edgeId - 1);
//    }

    /*
    I need to get the data and see if it's worth sending back to the edge node
    i need some estimate for calculating the time required to send from the core node
    and to replicate to edge node.
    this would depend on the size of the program
    */



    delete msg;
}

void CoreNode::loadDataFromFile(const std::string &filename) {
    std::ifstream fJson(filename);
    std::stringstream buffer;
    buffer << fJson.rdbuf();
    auto json = nlohmann::json::parse(buffer.str());

    for (auto item: json) {
        DataItem data;
        data.id = item["id"];
        data.type = item["type"];
        data.size = item["size"];
        data.access_frequency = item["access_frequency"];

        dataStore[item["id"]] = data;
    }

    EV << "Loaded " << dataStore.size() << " data items.\n";
}
