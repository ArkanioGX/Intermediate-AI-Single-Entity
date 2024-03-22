// A-Star.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <limits>

enum NodeType {Ground = 0, Wall = 1, Challenging = 2, Dangerous = 3};

#define inf std::numeric_limits<float>::max()
struct Node {
public:
    float g, h, f;
    Node* Parent;
    int x, y;
    NodeType type;
};

std::vector<Node*> openList = std::vector<Node*>();
std::vector<Node*> closedList = std::vector<Node*>();

std::vector<std::vector<int>> map = {
    {0,0,0,0,0},
    {0,1,1,1,3},
    {0,0,1,1,3},
    {1,3,1,3,3},
    {1,3,3,3,3}
};

std::vector<std::vector<Node*>> nodeMap(5,std::vector<Node*>(5, new Node()));

void initNodeMap();
int getIndexFromValue(std::vector<Node*>& list, Node* v);
Node* searchMin(std::vector<Node*>& list);
std::vector<Node*> setChildren(Node* n);
int ifIsInListViaPos(Node* value, std::vector<Node*> list);
bool hasSamePos(Node* n1, Node* n2);
float getDist(Node* n1, Node* n2);
bool ifIsInList(Node* value, std::vector<Node*> list);
float getNodeTypeMultiplier(NodeType t);
void showPath(Node* start, Node* end, std::vector<std::vector<Node*>> list);

int main()
{
    initNodeMap();
    Node* startNode = nodeMap[1][2];
    startNode->f = 0;
    Node* endNode = nodeMap[4][0];

    openList.push_back(startNode);

    while (!openList.empty()) {
        Node* currentNode;
        currentNode = searchMin(openList);
        openList.erase(openList.begin() + getIndexFromValue(openList, currentNode));
        closedList.push_back(currentNode);

        if (currentNode == endNode) {
            std::cout << "GGs you won" << std::endl;
            showPath(startNode, endNode, nodeMap);
            return 0;
        }
        std::vector<Node*> childNodes = setChildren(currentNode);
        for (int i = 0; i < childNodes.size(); i++) {
            Node* childNode = childNodes[i];
            if (ifIsInList(childNode, closedList)) {
                continue;
            }
            childNode->g = currentNode->g + getDist(currentNode, childNode) * getNodeTypeMultiplier(childNode->type);
            childNode->h = getDist(childNode, endNode);
            childNode->f = childNode->g + childNode->h;

            int listPos = ifIsInListViaPos(childNode, openList);
            if (listPos != -1) {
                if (openList[listPos]->g < childNode->g) {
                    continue;
                }
            }
            openList.push_back(childNode);
        }
    }
    
}

void initNodeMap() {
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size(); x++) {
            Node* n = new Node();
            n->x = x;
            n->y = y;
            n->g = 0;
            n->h = 0;
            n->f = n->g + n->h;
            n->Parent = nullptr;

            n->type = static_cast<NodeType>(map[y][x]);
            nodeMap[x][y] = n;
        }
    }
}

float getDist(Node* n1, Node* n2) {
    return sqrt(pow((n1->x - n2->x), 2) + pow((n1->x - n2->x), 2));
}

int getIndexFromValue(std::vector<Node*>& list, Node* v) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i] == v) {
            return  i;
        }
    }
    return 0;
}

Node* searchMin(std::vector<Node*>& list) {
    int fMin = 0;

    for (int j = 0; j < list.size(); j++) {
        if (list[j]->f < list[fMin]->f)
        {
            fMin = j;
        }
    }
    return list[fMin];
}

std::vector<Node*> setChildren(Node* n) {
    std::vector<Node*> children = std::vector<Node*>();
    for (int x = -1; x < 2; x++) {
        if ((n->x + x >= 0) && (n->x + x < nodeMap[0].size())) {
            for (int y = -1; y < 2; y++) {
                if ((n->y + y >= 0) && (n->y + y < nodeMap[0].size())) {
                    int xP = n->x + x;
                    int yP = n->y + y;
                    if (!(x == 0 && y == 0) && nodeMap[xP][yP]->type != NodeType::Wall && (ifIsInListViaPos(nodeMap[xP][yP],closedList)==-1)) {
                        nodeMap[xP][yP]->Parent = n;
                        children.push_back(nodeMap[xP][yP]);
                    }
                }
            }
        }
    }
    return children;
}

bool ifIsInList(Node* value, std::vector<Node*> list) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i] == value) {
            return true;
        }
    }
    return false;
}

int ifIsInListViaPos(Node* value, std::vector<Node*> list) {
    for (int i = 0; i < list.size(); i++) {
        if (hasSamePos(list[i],value)) {
            return i;
        }
    }
    return -1;
}

bool hasSamePos(Node* n1, Node* n2)
{
    return n1->x == n2->x && n1->y == n2->y;
}

void showPath(Node* start, Node* end, std::vector<std::vector<Node*>> list) {
    Node* n = list[end->x][end->y];
    std::cout << "Path : " << std::endl;
    while (!hasSamePos(n,start)) {
        std::cout << "Position : x =" << n->x << " | y = " << n->y << std::endl;
        Node* p = n->Parent;
        n = list[p->x][p->y];
    }
    std::cout << "Position : x =" << n->x << " | y = " << n->y << std::endl;
}

float getNodeTypeMultiplier( NodeType t ){
    switch (t) {
    case NodeType::Ground:
        return 1;
    case NodeType::Wall:
        return inf;
    case NodeType::Challenging:
        return 1.5;
    case NodeType::Dangerous:
        return 2;
    }
}


