//
//  main.cpp
//  project2_Q6_GridGraph_A*
//
//  Created by Yasmin Ali on 4/1/20.
//

#include <iostream>
#include<vector>
#include<string>
#include<map>
#include<unordered_map>
#include<time.h>
#include<stdlib.h>
#include <climits>
#include<unordered_set>
#include <math.h>

using namespace std;

struct GridNode{
protected:
    //neighbors are nodes connected to current node by an edge
    vector<GridNode*> neighbors;
    string value;
    int x;
    int y;
public:
    GridNode(int X= 0, int Y= 0, string v=""){
        value= v;
        x= X;
        y= Y;
        neighbors= {};
    }
    string getValue(){
        return value;
    }
    vector<GridNode*> getNeighbors(){
        return neighbors;
    }
    void addNeighbor(GridNode* node){
        this->neighbors.push_back(node);
    }
    void removeNeighbor(int index){
        neighbors.erase(neighbors.begin() + index);
    }
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
    void setX(int X){
        x= X;
    }
    void setY(int Y){
        y= Y;
    }
};

class GridGraph{
    vector<GridNode*> allNodes;
public:
    void addGridNode(int x, int y, string nodeVal){
        GridNode* newNode= new GridNode(x, y, nodeVal);
        allNodes.push_back(newNode);
    }
    
    void addUndirectedEdge(GridNode* first, GridNode* second){
        if(first == NULL || second == NULL)
            return;
        
        if(!edgeFound(first, second)){
            first->addNeighbor(second);
            second->addNeighbor(first);
        }
    }
    
    void removeUnDirectedEdge(GridNode* first, GridNode* second){
        for(GridNode* current : allNodes ){
            //when first is found in the graph remove second from first
            if(current->getValue() == first->getValue()){
                checkAndRemove(current, second);
            }
            //when second is found in the graph remove first from second
            if(current->getValue() == second->getValue()){
                checkAndRemove(current, first);
            }
        }
    }
    
    void checkAndRemove(GridNode* current, GridNode* needsRemoval){
        vector<GridNode*> neighbors= current->getNeighbors();
        if(neighbors.size() < 1)
            return;
        
        int index= 0;
        for (GridNode* neighbor : neighbors){
            //when needsRemoval is found, remove it
            if (neighbor->getValue() == needsRemoval->getValue()){
                //removes neighbor when located at index (index)
                current->removeNeighbor(index);
                break;
            }
            index++;
        }
    }
    
    vector<GridNode*> getAllNodes(){
        return allNodes;
    }
    
    bool edgeFound(GridNode* first, GridNode* second){
        for(GridNode* n : first->getNeighbors() ){
            if (n->getValue() == second->getValue()){
                return true;
            }
        }
        return false;
    }
};

GridGraph createRandomGridGraph(int n){
    GridGraph g;
    //creating nodes
    int nodeVal= 0;
    for(int x=0; x < n; x++){
        for(int y=0; y < n; y++){
            g.addGridNode(x, y, to_string(nodeVal));
            nodeVal++;
        }
    }
    
    vector<GridNode*> graphNodes= g.getAllNodes();
    //creating random edges
    srand(time(0));
    
    //genrating random edges with the four nodes surrounding the current node
    for(int i=0; i < graphNodes.size(); i++){
        if (i+1 < n){
            int makeRightEdge= rand() % 2;
            if (makeRightEdge){
                g.addUndirectedEdge(graphNodes[i], graphNodes[i+1]);
            }
        }
        if( i+n < pow(n,2)-1){
            int makeDownEdge= rand() % 2;
            if (makeDownEdge){
                g.addUndirectedEdge(graphNodes[i], graphNodes[i+n]);
            }
        }
        if( i-n > 0){
            int makeUpperEdge= rand() % 2;
            if (makeUpperEdge){
                g.addUndirectedEdge(graphNodes[i], graphNodes[i-n]);
            }
        }
        if( i % n != 0){
            int makeLeftEdge= rand() % 2;
            if (makeLeftEdge){
                g.addUndirectedEdge(graphNodes[i], graphNodes[i-1]);
            }
        }
    }
    return g;
}

int heuristic(GridNode* curr, GridNode* dest) {
    // using manhattan distance since we're allowed to move up, down, left and right only
    int h= abs(curr->getX() - dest->getX()) + abs(curr->getY() - dest->getY());
    return h;
}

//this function finds the neighbor node with minimum d(v)= h(v) + g(v)
GridNode* aStarHelper(map<GridNode*, pair<int, int>>& distances, unordered_set<GridNode*>& finalized) {
    GridNode* ans = nullptr;
    int minDist= INT_MAX;
    for (auto p : distances) {
        GridNode* node = p.first;
        int shortestToNode = p.second.first;
        int heuristic = p.second.second;
        
        if (!finalized.count(node) && shortestToNode + heuristic <= minDist){
            minDist= shortestToNode + heuristic;
            ans= node;
        }
    }
    return ans;
}

vector<GridNode*> astar(GridNode* origin, GridNode* dest){
    map<GridNode*, pair<int, int>> distances;
    unordered_set<GridNode*> finalized;
    vector<GridNode*> output;
    
    GridNode* current= origin;
    distances[origin]= make_pair(0, heuristic(current, dest));
    bool found= false;
    output.push_back(origin);
    
    while (current != dest && current != NULL){
        finalized.insert(current);
        // Iterate over its neighbors, “relax” each neighbor:
        //neighbors here is a vector<GridNode*> where GridNode* is the neighbor
        for(auto neighbor : current->getNeighbors()){
            //checking if neighbor was visited already
            if(!finalized.count(neighbor)){
                //adding the node and its distance to distances map if it is not already saved there
                if(!distances.count(neighbor)){
                    //if it is the first time to add i to distance map, make its distance g[v] infinity or INT_MAX
                    distances[neighbor]= make_pair(INT_MAX, heuristic(neighbor, dest));
                }
                //we consider all edges to have a weight of 1 since it is unweighted graph
                int dist_from_curr_to_neighbor= 1;
                int newDistance= min(distances[current].first + dist_from_curr_to_neighbor, distances[neighbor].first);
                
                distances[neighbor].first= newDistance;
            }
        }
        current= aStarHelper(distances, finalized);
        output.push_back(current);
        if(current==dest){
            found= true;
        }
    }
    if(!found)
        return {};
    
    return output;
}

/******************************* main and testing *****************************************/
int main() {
    
    /************** Creating a random Grid Graph ******************/
    cout << "GridGraph of size 100 * 100: " << endl;
    GridGraph g= createRandomGridGraph(100);
    vector<GridNode*>allNodes= g.getAllNodes();
    
    for(GridNode* node: allNodes){
        cout<< node->getValue() << " :{";
        for(auto i : node->getNeighbors()){
            cout << i->getValue() << ",";
        }
        cout << "}" << endl;
    }
    cout << endl;
    /******************* running Astar on unweighted graph ***********************/
    cout << "Minimum distance from start node using A* Algorithm to find minimum path from node (0,0), to (99,99): " << endl;
    int lastIndex= allNodes.size()-1;
    GridNode* origin= allNodes[0];
    GridNode* dest= allNodes[lastIndex];
    
    vector<GridNode*> AStar_result= astar(origin, dest);
    if (AStar_result.size() == 0)
        cout << "No path available. " << endl;
    for(auto i : AStar_result){
        cout << i->getValue() << endl;
    }
    return 0;
}
