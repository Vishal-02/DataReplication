simple CoreNode
{
    parameters:
        string type = "core";
        int nodeId = 0;
    gates:
        inout gate[];
}

simple EdgeNode
{
    parameters:
        string type = "edge";
        int nodeId; // 0 is for Core Node
    gates:
        inout gate[];
}

simple User
{
    parameters:
        string userId;
        int requestInterval = 1; // Time between requests
    gates:
        inout gate[];
}

simple ReplicationManager
{
    gates:
        inout gate[];
}

network DataReplicationNetwork
{
    parameters:
        int edgeNodeCount = default(5);
        int userCount = default(5);
        @display("bgb=496,467");
    submodules:
        replicationManager: ReplicationManager {
            @display("p=249,53");
        }

        // Define Edge Nodes
        edgeNode1: EdgeNode {
            @display("p=31,293");
            nodeId = 1;
        }
        edgeNode2: EdgeNode {
            @display("p=119,293");
            nodeId = 2;
        }
        edgeNode3: EdgeNode {
            @display("p=221,293");
            nodeId = 3;
        }
        edgeNode4: EdgeNode {
            @display("p=320,293");
            nodeId = 4;
        }
        edgeNode5: EdgeNode {
            @display("p=428,293");
            nodeId = 5;
        }

        // Define Core Node
        coreNode1: CoreNode {
            @display("p=249,166");
        }

        // Define Users
        user1: User {
            userId = "u1"; // Assign unique IDs to users
            @display("p=44,407");
        }

        user2: User {
            userId = "u2"; // Assign unique IDs to users
            @display("p=150,407");
        }

        user3: User {
            userId = "u3"; // Assign unique IDs to users
            @display("p=241,407");
        }

        user4: User {
            userId = "u4"; // Assign unique IDs to users
            @display("p=338,407");
        }

        user5: User {
            userId = "u5"; // Assign unique IDs to users
            @display("p=434,407");
        }

    connections allowunconnected:
        // Connect each edge node to the core node
        edgeNode1.gate++ <--> coreNode1.gate++;
        edgeNode2.gate++ <--> coreNode1.gate++;
        edgeNode3.gate++ <--> coreNode1.gate++;
        edgeNode4.gate++ <--> coreNode1.gate++;
        edgeNode5.gate++ <--> coreNode1.gate++;

        // Connect the replication manager to the core node
        replicationManager.gate++ <--> coreNode1.gate++;

        // Connect each user to an edge node
        user1.gate++ <--> edgeNode1.gate++;
        user2.gate++ <--> edgeNode2.gate++;
        user3.gate++ <--> edgeNode3.gate++;
        user4.gate++ <--> edgeNode4.gate++;
        user5.gate++ <--> edgeNode5.gate++;
        
        // Connect each edge node to the replication manager
        edgeNode1.gate++ <--> replicationManager.gate++;
        edgeNode2.gate++ <--> replicationManager.gate++;
        edgeNode3.gate++ <--> replicationManager.gate++;
        edgeNode4.gate++ <--> replicationManager.gate++;
        edgeNode5.gate++ <--> replicationManager.gate++;

        // Connect the users to the core node(s)
        user1.gate++ <--> coreNode1.gate++;
        user2.gate++ <--> coreNode1.gate++;
        user3.gate++ <--> coreNode1.gate++;
        user4.gate++ <--> coreNode1.gate++;
        user5.gate++ <--> coreNode1.gate++;

}
