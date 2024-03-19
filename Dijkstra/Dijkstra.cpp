// Dijkstra.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include <vector>

#define inf std::numeric_limits<int>::max()
const int nodeNumber = 7;

void Dikjstra(int g[nodeNumber][nodeNumber], int origin);
int searchMin(int dist[], std::vector<int>& list);
int getIndexFromValue(std::vector<int>& list, int v);

int main()
{
    int graph[nodeNumber][nodeNumber] = {
    0, 10, 15, inf, 30, inf, inf,
    inf, 0, inf, inf, inf, 57, inf,
    15, inf, 0, 16, inf, inf, 52,
    inf, inf, 13, 0, inf, inf, inf,
    30, inf, inf, inf, 0, 11, 34,
    inf, 49, inf, inf, 12, 0, inf,
    inf, inf, 63, inf, 35, inf, 0 };

    Dikjstra(graph,0);
}



void Dikjstra(int g[nodeNumber][nodeNumber], int origin) {
    int dist[nodeNumber];
    int prev[nodeNumber];

    std::vector<int> nodeList;

    for (int i = 0; i < nodeNumber; i++) {
        dist[i] = inf;
        prev[i] = -1;
        nodeList.push_back(i);
    }
    dist[origin] = 0;

    while (!nodeList.empty()) {
        int min = searchMin(dist,nodeList);
        nodeList.erase(nodeList.begin()+ getIndexFromValue(nodeList,min));

        for (int i = 0; i < nodeList.size(); i++) {
            int id = nodeList[i];
            if (g[min][id] != inf) {
                int distAlt = dist[min] + g[min][id];
                if (distAlt < dist[id]) {
                    dist[id] = distAlt;
                    prev[id] = id;
                }
            }
        }
    }

    std::cout << "Distance from point " << origin << std::endl;
    for (int i = 0; i < nodeNumber; i++) {
        
        std::cout << "ID : " << i << " | Distance : " << dist[i] << " | Previous : " << prev[i] << std::endl;
    }
}

int searchMin(int dist[], std::vector<int>& list) {
    int minID = list[0];

    for (int j = 0; j < list.size(); j++) {
        int id = list[j];
        if (dist[id] < dist[minID]) 
        { 
            minID = id; 
        }
    }
    std::cout << minID << std::endl;
    return minID;
}

int getIndexFromValue(std::vector<int> &list,int v) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i] == v) {
            return  i;
        }
    }
    return 0;
}

