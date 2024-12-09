#include "User.h"
#include "json.hpp"
#include "DataRequest_m.h"
#include "SendingUserData_m.h"
#include <fstream>
#include <omnetpp.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace omnetpp;

Define_Module(User);

User::User() {}

User::~User() {}

void User::initialize() {
    // Assign a unique userId from parameters
    userId = par("userId").stdstringValue();

    // Initialize available data items (you can later load these from a JSON file)
    std::ifstream fJson("synthetic_data.json");
    std::stringstream buffer;
    buffer << fJson.rdbuf();
    auto json = nlohmann::json::parse(buffer.str());

    for (auto item: json) {
        dataItems.push_back(item["id"]);
    }

    // Schedule first data request
    scheduleAt(simTime() + 0.1, new cMessage("sendRequest"));
}

void User::handleMessage(cMessage* msg) {
//    if (std::string(msg->getName()) == "sendRequest") {
//        // Send a new data request
//        sendDataRequest();
//
//        // Schedule the next request
//        // maximum time of one second between two requests
//        float random_skip = float(intuniform(0, 1000)) / 100;
//        scheduleAt(simTime() + 1, msg);
//    } else {
//        EV << "Received unknown message: " << msg->getName() << "\n";
//        delete msg;
//    }

    if (std::strcmp(msg->getName(), "sendingData") == 0) {
        SendingUserData *received = check_and_cast<SendingUserData *>(msg);
        std::string receivedData = received->getDataId();
        std::string receivedBubble = "Received " + receivedData;
        bubble(receivedBubble.c_str());
        EV << "RECEIVED DATA " << receivedData;
    } else {
        sendDataRequest();

        // Schedule the next request
        float random_skip = float(intuniform(0, 1000)) / 500;
        EV << "Random skip of : " << random_skip << "s";
        scheduleAt(simTime() + random_skip, new cMessage("sendRequest"));
    }

    delete msg;

//    if (std::strcmp(msg->getName(), "sendRequest") == 0) {
//        // This is our self-message to trigger a new request
//        sendDataRequest();
//
//        // Schedule the next request
//        float random_skip = float(intuniform(0, 1000)) / 100;
//        scheduleAt(simTime() + 1 + random_skip, new cMessage("sendRequest"));
//        delete msg;  // Delete the current message
//    }
//    else if (dynamic_cast<SendingUserData *>(msg) != nullptr) {
//        // This is the response from the EdgeNode
//        SendingUserData *received = check_and_cast<SendingUserData *>(msg);
//        std::string receivedData = received->getDataId();
//        std::string receivedBubble = "Received " + receivedData;
//        bubble(receivedBubble.c_str());
//        delete msg;  // Delete the message after processing
//    }
//    else {
//        EV << "Received unknown message: " << msg->getName() << "\n";
//        delete msg;  // Delete unknown messages
//    }
}

void User::sendDataRequest() {
    if (dataItems.empty()) {
        EV << "No data items available to request.\n";
        return;
    }

    // Randomly select a data item to request
    std::string requestedData = dataItems[intuniform(0, dataItems.size() - 1)];
    std::string dest = "u_req_" + requestedData;

    // Create and send custom defined message
    char msgname[20];
    snprintf(msgname, sizeof(msgname), dest.c_str());

    DataRequest *request = new DataRequest(msgname);
    request->setDataId(requestedData.c_str());
    request->setUserId(userId.c_str());
    send(request, "gate$o", 0);

    std::string askingFor = "Requesting " + requestedData;
    bubble(askingFor.c_str());
    EV << "User " << userId << " sent request for data: " << requestedData << "\n";
}
