//
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
    vector<GridNode*>neighbors;
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
};

class GridGraph{
    vector<GridNode*> allNodes;
public:
    void addGridNode(int x, int y, string nodeVal){
        GridNode* newNode= new GridNode(x, y, nodeVal);
        allNodes.push_back(newNode);
    }
    
    void addUndirectedEdge(GridNode* first, GridNode* second){
        
        if(!edgeFound(first, second)){
            first->neighbors.push_back(second);
            second->neighbors.push_back(first);
        }
    }
    
    void removeUndirectedEdge(GridNode* first, GridNode* second){
        for(GridNode* n : allNodes ){
            if(n->value == first->value){
                int index= 0;
                for (GridNode* neighbor :  n->neighbors){
                    if (neighbor->value == second->value){
                        (n->neighbors).erase((n->neighbors).begin() + index);
                    }
                    index++;
                }
            }
            
            if(n->value == second->value){
                int index= 0;
                for (GridNode* neighbor :  n->neighbors){
                    if (neighbor->value == first->value){
                        (n->neighbors).erase((n->neighbors).begin() + index);
                    }
                    index++;
                }
            }
        }
    }
    
    vector<GridNode*> getAllNodes(){
        return allNodes;
    }
    
    bool edgeFound(GridNode* first, GridNode* second){
        for(GridNode* n : first->neighbors ){
            if (n == second){
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
    //consider only the right and down nodes
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
        
    }
    return g;
}

int heuristic(GridNode* curr, GridNode* dest) {
    // using manhattan distance:
    int h= abs(curr->x - dest->x) + abs(curr->y - dest->y);
    return h;
}

//this function finds the neighbor node with minimum d(v)= h(v) + g(v)
GridNode* mostPromisingAStar(map<GridNode*, pair<int, int>>& distances, unordered_set<GridNode*>& finalized) {
    GridNode* ans = nullptr;
    int minDist= INT_MAX;
    for (auto p : distances) {
        GridNode* node = p.first;
        int shortest_to_node = p.second.first;
        int heuristic = p.second.second;
        
        if (!finalized.count(node) && shortest_to_node + heuristic <= minDist){
            minDist= shortest_to_node + heuristic;
            ans= node;
        }
    }
    return ans;
}


map<GridNode*, pair<int, int>> astar(GridNode* origin, GridNode* dest){
    map<GridNode*, pair<int, int>> distances;
    unordered_set<GridNode*> finalized;
    
    GridNode* current= origin;
    distances[origin]= make_pair(0, heuristic(current, dest));
    bool found= false;
    
    while (current != dest && current != NULL){
        finalized.insert(current);
        // Iterate over its neighbors, “relax” each neighbor:
        //neighbors here is a vector<GridNode*> where GridNode* is the neighbor
        for(auto neighbor : current->neighbors){
            if(!finalized.count(neighbor)){
                //adding the node and its distance to distances map if it is not already saved there
                if(!distances.count(neighbor)){
                
                    distances[neighbor]= make_pair(INT_MAX, heuristic(neighbor, dest));
                }
                //we consider all edges to have a weight of 1 since it is unweighted graph
                int dist_from_curr_to_neighbor= 1;
                int newDistance= min(distances[current].first + dist_from_curr_to_neighbor, distances[neighbor].first);
                
                distances[neighbor].first= newDistance;
            }
        }
        current= mostPromisingAStar(distances, finalized);
        if(current==dest){
            found= true;
        }
    }
    
    if(!found)
        return {};
    
    return distances;
}




int main() {
    
    /************** Creating a random Grid Graph ******************/
    cout << "GridGraph of size 5 * 5: " << endl;
    GridGraph g= createRandomGridGraph(5);
    vector<GridNode*>allNodes= g.getAllNodes();
    
    for(GridNode* node: allNodes){
        //cout << node->value << ": ";
        cout<< node->value << " :{";
        for(auto i : node->neighbors){
            cout << i->value << ",";
        }
        cout << "}" << endl;
    }
    cout << endl;
    /******************* running Astar on unweighted graph ***********************/
    
    cout << "Minimum distance from start node using A* Algorithm to find minimum path from node (0,0), to (24,24): " << endl;
    int lastIndex= allNodes.size()-1;
    GridNode* origin= allNodes[0];
    GridNode* dest= allNodes[lastIndex];
    
    map<GridNode*, pair<int, int>> AStar_result= astar(origin, dest);
    for(auto i : AStar_result){
        cout << i.first->value << ": " << "   d[v]:" << i.second.first << endl;
    }
    return 0;
}
