#include "DataRequest_m.h"
#include "CoreRequest_m.h"
#include "ReplicateRequest_m.h"
#include "ManagerMessage_m.h"
#include "SendingUserData_m.h"
#include "DataItem.h"
#include "json.hpp"
#include <fstream>
#include <map>
#include <omnetpp.h>
#include <string>
#include <climits>

using namespace omnetpp;

class EdgeNode : public cSimpleModule {
  private:
    std::map<std::string, DataItem> cachedData; // Data items stored locally
    int edgeId;
    int cacheLimit = 20;

  protected:
    virtual void initialize() override {
        // get the edge id
        edgeId = par("nodeId");

        // Caching some data in this edge node
        std::ifstream fJson("synthetic_data.json");
        std::stringstream buffer;
        buffer << fJson.rdbuf();
        auto json = nlohmann::json::parse(buffer.str());

        // a poor attempt to randomly store some data into each edge node
        int num_items = 0;
        int random_skip = intuniform(0, 70);
        int i = 0;
        for (auto item: json) {
            while (i++ < random_skip)
                continue;
            if (num_items >= cacheLimit || i >= 100)
                break;

            DataItem data;
            data.id = item["id"];
            data.type = item["type"];
            data.size = item["size"];
            data.access_frequency = 0;

            cachedData[data.id] = data;
            ++num_items;
        }

        return;
    }

    virtual void handleMessage(cMessage *msg) override {
        // TODO: Auto delete items

        if (strcmp(msg->getName(), "replicate") == 0)
        {
            // deletes the item with the lowest frequency to make room
            // for the new item to be replicated
            std::string test = "Sending replicated data";
            bubble(test.c_str());

            ReplicateRequest *rep_req = check_and_cast<ReplicateRequest *>(msg);
            std::string dataId = rep_req->getDataId();

            int min = INT_MAX;
            std::string min_data = "";

            for(auto i: cachedData) {
                if (i.second.access_frequency < min) {
                    min = i.second.access_frequency;
                    min_data = i.first;
                }

                if (min == 0)
                    break;
            }

            // this is the auto delete
            cachedData.erase(min_data);
            std::string deletingBubble = "Deleting " + min_data;
            bubble(deletingBubble.c_str());

            // send a message to the replication manager telling it that you're deleting some data off of your cache
            DataItem data;
            data.id = dataId;
            data.type = rep_req->getType();
            data.size = rep_req->getSize();
            data.access_frequency = 1;

            cachedData[dataId] = data;

            SendingUserData *msg = new SendingUserData("sendingData");
            msg->setDataId(rep_req->getDataId());
            int data_size = data.size;
            float time = float(data_size) / 2000; // random number chosen
            // gate 1, because only one user is connected
            // this will get more complicated once multiple users connect to one edge
            sendDelayed(msg, time, "gate$o", 1);
        }
        else
        {
            DataRequest *ttmsg = check_and_cast<DataRequest *>(msg);
            std::string requestedData = ttmsg->getDataId();

            // if the edge node has the data
            if (cachedData.find(requestedData) != cachedData.end()) {

                // TODO: Respond to user (create and send a response message)
                // DataItem data = cachedData[requestedData];
                cachedData[requestedData].access_frequency += 1;
                int data_size = cachedData[requestedData].size;
                float time = float(data_size) / 2000; // random number chosen
                EV << "size is " << data_size << ", so should take " << time << "s.\n";

                // this is the data we need to send back
                SendingUserData *msg = new SendingUserData("sendingData");
                msg->setDataId(requestedData.c_str());

                // this will get more complicated once multiple users connect to one edge
                sendDelayed(msg, time, "gate$o", 1); // gate 1, because only one user is connected
                EV << "Edge node has data " << requestedData << ", serving directly.\n";
                std::string sendingUserBubble = requestedData + " found. Sending in " \
                        + std::to_string(time) + "s";
                bubble(sendingUserBubble.c_str());

                std::string dest = "inform";
                char msgname[20];
                snprintf(msgname, sizeof(msgname), dest.c_str());

                // send a message to the replication manager for informing it
                ManagerMessage *inform = new ManagerMessage(msgname);
                inform->setEdgeId(edgeId);
                inform->setDataId(requestedData.c_str());
                inform->setUserId(ttmsg->getUserId());
                send(inform, "gate$o", 2); // gate 2 is the replication manager

            } else { // the edge node doesn't have the data
                EV << "Data " << requestedData << " not found at edge node, forwarding to core node.\n";
                std::string askingCoreBubble = requestedData + " not found. Requesting Core...";
                bubble(askingCoreBubble.c_str());

                std::string dest = "edge_request";
                char msgname[20];
                snprintf(msgname, sizeof(msgname), dest.c_str());

                CoreRequest *c_req = new CoreRequest(msgname);
                c_req->setEdgeId(edgeId);
                c_req->setUserId(ttmsg->getUserId());
                c_req->setDataId(requestedData.c_str());

                send(c_req, "gate$o", 0); // gate 0 is core node
            }
        }



    }
};

Define_Module(EdgeNode);
