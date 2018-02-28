#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <limits>

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

    int V, E, R, C, X, numberOfCaches, currentCache;
    reader >> V >> E >> R >> C >> X;

    for(int v = 0; v < V; ++v)
    {
        reader >> videoSizes[v];
    }

    for(int e = 0; e < E; ++e)
    {
        reader >> endPointToCentral[e];

        reader >> numberOfCaches;
        for(int c = 0; c < numberOfCaches; ++c)
        {
            reader >> currentCache;

            if(allEndPointToServers.count(e) < 1)
                allEndPointToServers[e];

            reader >> allEndPointToServers[e][currentCache];
        }
    }

    int video, endpoint, requests;

    for(int r = 0; r < R; ++r)
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

    read("exemple.in", videoSizes, endPointToCentral, allEndPointToServers, endpointRequests);

    // Fill remaining capacities
    for(auto & kv : cacheServers)
    {
        remainingCapacity[kv.first] = kv.second;
    }

    // Do algo

    // trouver request max (count * size)
    int video = 0;
    int endpoint = 0;
    int max = 0;
    // We ignore values above this
    int threshold = std::numeric_limits<int>::max();
    int test;
    for(auto & endpoint_request : endpointRequests)
    {
        for(auto & video_count : endpoint_request.second)
        {
            test = video_count.second * videoSizes[video_count.first];
            if(test > max && test < threshold)
            {
                max = test;
                endpoint = endpoint_request.first;
                video = video_count.first;
            }
        }
    }
    threshold = max;

    return 0;
}
