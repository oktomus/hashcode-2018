#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <cassert>
#include <limits>
#include <algorithm>
#include <sstream>

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
AllEndPointToServers allEndPointToServers;
Requests requests;
EndpointRequests endpointRequests;
RemainingCapacity remainingCapacity;
AssignedServerVideos assignedServerVideos;
int video = -1; // Current video of the request
int video_size; // Current video size
int endpoint = -1; // Current endpoint of the request
int max = -1; // Value (size * count) of the request
int test; // Temp value
int serverid = -1; // Id du meilleur serveur pour l'ajout

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
            if(test > max)
            {
                max = test;
                endpoint = endpoint_request.first;
                video = video_count.first;
            }
        }
    }
    video_size = videoSizes[video];
}

void trouver_meilleur_serveur()
{
    EndPointToServers & endpointsServers = allEndPointToServers[endpoint];
    for(int i = 0, n = endpointsServers.size(); i < n; i++)
    {
        serverid = endpointsServers[i].first;
        if (remainingCapacity[serverid] >= video_size)
            break;
        serverid = -1;
    }

    if (serverid != -1)
    {
        remainingCapacity[serverid] -= video_size;
        endpointRequests[endpoint][video] = -1;
        assignedServerVideos[serverid].push_back(video);
    }
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

    for(int c = 0; c < C; ++c)
    {
        cacheServers[c] = X;
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

    reader.close();
}

bool pairCompare(const std::pair<int, int>& firstElem, const std::pair<int, int>& secondElem)
{
  return firstElem.second > secondElem.second;
}

int eval()
{
    int score = 0;
    // pour chaque endpoint, on calcul le gain pour chaque request.
    for(auto & epr : endpointRequests)
    {
        for(auto & r : epr)
        {
            // si la vidéo r.first est dans un cache alors on ajoute aux gains
        }
    }

    return score;
}

int main()
{
    std::vector<std::string> fichiers = {
        "exemple.in"
    };

    for(std::size_t i = 0; i < fichiers.size(); i++)
    {
        read(fichiers[i]);

        // Fill remaining capacities
        for(auto & kv : cacheServers)
        {
            remainingCapacity[kv.first] = kv.second;
        }

        // Trier EndpointsToServers Latencies
        for(auto & ep : allEndPointToServers)
        {
            std::sort(ep.second.begin(), ep.second.end(), pairCompare);
        }

        // Tant qu'il n'y plus de requests a traiter
        do
        {
            video = -1;
            video_size = -1;
            endpoint = -1;
            serverid = -1;
            max = -1;

            trouver_meilleur_request();

            if (video == -1) break;

            trouver_meilleur_serveur();

            // Modifier request pour ne plus passer dessus
            endpointRequests[endpoint][video] = -1;
        } while(video != -1);

        std::cout << "Score : " << eval() << std::endl;

        // Export

        std::string output_path = fichiers[i].substr(0, fichiers[i].find_last_of('.')) + ".out";

        std::ofstream writer(output_path);
        assert(writer.is_open());

        writer << assignedServerVideos.size() << "\n";
        for(auto & server_video : assignedServerVideos)
        {
            writer << server_video.first;
            for(std::size_t v = 0; v < server_video.second.size(); v++)
            {
                writer << " " << server_video.second[v];
            }
            writer << "\n";
        }

        writer.close();
    }
    return 0;
}
