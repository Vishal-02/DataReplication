#include <omnetpp.h>
#include <string>
#include <vector>

using namespace omnetpp;

class User : public cSimpleModule {
private:
    std::string userId;            // Unique ID for the user
    std::vector<std::string> dataItems; // List of available data items to request

protected:
    virtual void initialize() override;   // Initialization logic
    virtual void handleMessage(cMessage* msg) override; // Handle incoming messages
    void sendDataRequest();       // Send a data request to the connected EdgeNode

public:
    User();  // Constructor
    virtual ~User(); // Destructor
};
