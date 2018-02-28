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
typedef std::vector<std::pair<int, int>> EndPointToServers;
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

VideoSizes videoSizes;
CacheServers cacheServers;
EndPointToCentral endPointToCentral;
EndPointToServers endPointToServers;
AllEndPointToServers allEndPointToServers;
Requests requests;
EndpointRequests endpointRequests;
RemainingCapacity remainingCapacity;
AssignedServerVideos assignedServerVideos;
int video = -1; // Current video of the request
int endpoint = -1; // Current endpoint of the request
int max = -1; // Value (size * count) of the request
int test; // Temp value
int serverid; // Id du meilleur serveur pour l'ajout
int min_latency; // Meilleur latence trouvee pour un endpoint

void trouver_meilleur_request()
{
    // trouver request max (count * size)
    // We ignore values above this
    for(auto & endpoint_request : endpointRequests)
    {
        for(auto & video_count : endpoint_request.second)
        {
            if(video_count.second == -1) continue;
            test = video_count.second * videoSizes[video_count.first];
            if(test > max && test < threshold)
            {
                max = test;
                endpoint = endpoint_request.first;
                video = video_count.first;
            }
        }
    }
}

void trouver_meilleur_serveur()
{

}

void read(const std::string &filename)
{
    std::ifstream reader(filename);

    int V, E, R, C, X, numberOfCaches, currentCache, currentLatency;
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
            reader >> currentLatency;

            std::pair<int ,int> p = std::make_pair(currentCache, currentLatency);
            allEndPointToServers[e].push_back(p);
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
    read("exemple.in");

    // Fill remaining capacities
    for(auto & kv : cacheServers)
    {
        remainingCapacity[kv.first] = kv.second;
    }

    // Tant qu'il n'y plus de requests a traiter
    do
    {
        video = -1;
        endpoint = -1;

        trouver_meilleur_request();
        trouver_meilleur_serveur();

        // Modifier request pour ne plus passer dessus
        endpointRequests[endpoint][video] = -1;
    } while(video != -1);

    return 0;
}
