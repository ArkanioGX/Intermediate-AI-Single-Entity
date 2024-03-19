// A-Star.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <limits>

#define inf std::numeric_limits<float>::max()
struct Node {
public:
    float g, h, f;
    Node* Parent;
    int x, y;
};

std::vector<Node*> openList = std::vector<Node*>();
std::vector<Node*> closedList = std::vector<Node*>();

std::vector<std::vector<int>> map = {
    {0,0,0,0,0},
    {0,1,1,0,0},
    {0,0,1,1,1},
    {1,0,1,0,0},
    {0,0,0,0,0}
};

std::vector<std::vector<Node*>> nodeMap(5,std::vector<Node*>(5, new Node()));

void initNodeMap();
int getIndexFromValue(std::vector<Node*>& list, Node* v);
Node* searchMin(std::vector<Node*>& list);
std::vector<Node*> setChildren(Node* n);
int ifIsInListViaPos(Node* value, std::vector<Node*> list);
float getDist(Node* n1, Node* n2);
bool ifIsInList(Node* value, std::vector<Node*> list);

int main()
{
    initNodeMap();
    Node* startNode = nodeMap[0][4];
    startNode->f = 0;
    Node* endNode = nodeMap[4][0];

    openList.push_back(startNode);

    while (!openList.empty()) {
        Node* currentNode;
        currentNode = searchMin(openList);
        openList.erase(openList.begin() + getIndexFromValue(openList, currentNode));
        closedList.push_back(currentNode);

        if (currentNode == endNode) {
            std::cout << "GGs you won";
            return 0;
        }
        std::vector<Node*> childNodes = {};
        setChildren(currentNode);
        for (int i = 0; i < childNodes.size(); i++) {
            Node* childNode = childNodes[i];
            if (ifIsInList(childNode, closedList)) {
                continue;
            }
            childNode->g = currentNode->g + getDist(currentNode, childNode);
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
    std::vector<Node*> children = {};
    for (int x = -1; x < 2; x++) {
        if ((n->x + x > 0) && (n->x + x < nodeMap[0].size())) {
            for (int y = -1; y < 2; y++) {
                if ((n->y + y > 0) && (n->y + y < nodeMap[0].size())) {
                    nodeMap[x][y]->Parent = n;
                    children.push_back(n);
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
        if (list[i]->x == value->x && list[i]->y == value->y) {
            return i;
        }
    }
    return -1;
}


