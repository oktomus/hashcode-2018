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

void read(const std::string &filename, VideoSizes &videoSizes,
          EndPointToCentral &endPointToCentral, AllEndPointToServers &allEndPointToServers,
          EndpointRequests &endpointRequests)
{
    std::ifstream reader(filename);

    std::size_t V, E, R, C, X, numberOfCaches, currentCache;
    reader >> V >> E >> R >> C >> X;

    for(size_t v = 0; v < V; ++v)
    {
        reader >> videoSizes[v];
    }

    for(size_t e = 0; e < E; ++e)
    {
        reader >> endPointToCentral[e];

        reader >> numberOfCaches;
        for(size_t c = 0; c < numberOfCaches; ++c)
        {
            reader >> currentCache;

            if(allEndPointToServers.count(e) < 1)
                allEndPointToServers[e];

            reader >> allEndPointToServers[e][currentCache];
        }
    }

    std::size_t video, endpoint, requests;

    for(size_t r = 0; r < R; ++r)
    {
        reader >> video;
        reader >> endpoint;
        reader >> requests;

        if(endpointRequests.count(endpoint) < 1)
            endpointRequests[endpoint];

        endpointRequests[endpoint][video] = requests;
    }
}

int main()
{
    VideoSizes videoSizes;
    CacheServers cacheServers;
    EndPointToCentral endPointToCentral;
    EndPointToServers endPointToServers;
    AllEndPointToServers allEndPointToServers;
    Requests requests;
    EndpointRequests endpointRequests;
    RemainingCapacity remainingCapacity;
    AssignedServerVideos assignedServerVideos;

    read("me_at_the_zoo.in", videoSizes, endPointToCentral, allEndPointToServers, endpointRequests);

    // Fill remaining capacities
    for(auto & kv : cacheServers)
    {
        remainingCapacity[kv.first] = kv.second;
    }
    return 0;
}
