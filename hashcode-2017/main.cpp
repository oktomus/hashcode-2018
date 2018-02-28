#include <iostream>
#include <vector>
#include <map>
#include <fstream>

// Size for each video
typedef std::map<int, int> VideoSizes;

// Capacity for each server
typedef std::map<int, int> CacheServers;

// Latency from endpoint to central
typedef std::map<int, int> EndPointToCentral;

// Lantency from 1 endpoint to servers
// First: ServerId, Second: Latency
typedef std::map<int, int> EndPointToServers;
// Lantency from all endpoint to servers
typedef std::map<int, EndPointToServers> AllEndPointToServers;

// Request is video -> count
// First: Video Id, Second: count
typedef std::map<int, int> Requests;

// Endpoints Request
// First id endpoint, Second: Requests
typedef std::map<int, Requests> EndpointRequests;


// Algo structs

// Tell for [A Server Id] [Capcaity Left]
typedef std::map<int, int> RemainingCapacity;

// Out structs
// [Server ID] [VideoId, VideoID....]
typedef std::map<int, std::vector<int>> AssignedServerVideos;

int main()
{
    VideoSizes videoSizes;
    CacheServers cacheServers;
    EndPointToCentral endPointToCentral;
    EndPointToServers endPointToServers;
    AllEndPointToServers allEndPointToServers;
    Requests requests;
    EndpointRequests endpointRequests;

    return 0;
}
