message ReplicateRequest {
    int edgeId; // ID of the edge the original request was made to
    string userId; // ID of the user that made the request
    string dataId; // ID of the requested data
    string type;
    int size;
}