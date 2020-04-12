//
//  Project2_question 5
//  weightedGraph-Dijkstra's
//
//  Created by Yasmin Ali on 3/30/20.


#include <iostream>
#include<vector>
#include<string>
#include<stack>
#include<queue>
#include<map>
#include<time.h>
#include<stdlib.h>
#include <climits>
#include<unordered_set>
#include<algorithm>

using namespace std;

struct WNode {
    string value;
    bool visited;
    map<WNode*, int> neighbors; //int holds the weight of the edge between the node and the neighboring node
public:
    WNode(string val= "") {
        value = val;
        visited= false;
        neighbors = {};
    }
};

/************************** Weighted Graph Class ***********************/
class WeightedGraph{
    vector<WNode*> allNodes;
public:
    void addNode(string nodeVal){
        WNode* temp= new WNode(nodeVal);
        allNodes.push_back(temp);
    }
    
    void addDirectedEdge(WNode* first, WNode* second, int weight){
        //no edge to itself
        if(first->value != second->value){
            first->neighbors[second]= weight;
        }
    }
    
    void removeDirectedEdge(WNode* first, WNode* second){
        for(WNode* n : allNodes ){
            if(n->value == first->value){
                for (auto const& neighbor :  n->neighbors){
                    if (neighbor.first->value == second->value){
                        n->neighbors.erase(neighbor.first);
                    }
                }
            }
        }
    }
    
    vector<WNode*> getAllNodes(){
        return allNodes;
    }
    
    void reset(){
        vector<WNode*> allNodes= getAllNodes();
        for( WNode* node: allNodes){
            node->visited= false;
        }
    }
};


/************************** Dijkstra's and its helper functions ***********************/
//This function finds the node with minimum distance
WNode* minDist(map<WNode*, int> distances, unordered_set<WNode*> visited){
    WNode* temp= nullptr;
    int minDist= INT_MAX;
    for(auto const& i: distances){
        if(!visited.count(i.first) && i.second <= minDist){
            minDist= i.second;
            temp= i.first;
        }
    }
    return temp;
}

map<WNode*, int> dijkstras(WNode* start){
    unordered_set<WNode*>visited;
    map<WNode*, int>distances;
    
    distances[start]= 0;
    WNode* current= start;
    
    while (current != NULL){
        
        visited.insert(current);
        // Iterate over its neighbors, “relax” each neighbor:
        //neighbors here is a map<WNode*, int> where WNode* is the neighbor, and int is the edge weight
        for(const auto& neighbor : current->neighbors){
            if(!visited.count(neighbor.first)){
                //the distance is infinity if it is first time to be added to the map
                if(!distances.count(neighbor.first)){
                    distances[neighbor.first]= INT_MAX;
                }
                int newDistance= min(distances[current] + neighbor.second, distances[neighbor.first]);
                distances[neighbor.first]= newDistance;
            }
        }
        current= minDist(distances, visited);
    }
    return distances;
    
}

/*************************** Functions to create weighted graphs ***************************/
WeightedGraph createRandomCompleteWeightedGraph(int n){
    WeightedGraph g;
    //creating nodes, and adding them to the graph
    for(int i=0; i < n; i++){
        g.addNode(to_string(i));
    }
    
    vector<WNode*> graphNodes= g.getAllNodes();
    //creating random edges between nodes
    srand(time(0));
    for(int i=0; i < n; i++){
        for(int j= 0; j < n; j++){
            //weight is a random number from 1 to 10
            int weight= rand() % 10 + 1;
            g.addDirectedEdge(graphNodes[i], graphNodes[j], weight);
        }
    }
    return g;
}


WeightedGraph createLinkedList(int n){
    WeightedGraph g;
    
    //creating nodes, and adding them to the LL
    for(int i=0; i < n; i++){
        g.addNode(to_string(i));
    }
    vector<WNode*> graphNodes= g.getAllNodes();
    WNode* current= new WNode();
    
    for(int n=0; n < graphNodes.size(); n++){
        current= graphNodes[n];
        if( n+1 < graphNodes.size()){
            int weight= 1;
            g.addDirectedEdge(current, graphNodes[n+1], weight);
        }
    }
    return g;
}

void print(WeightedGraph g){
    vector <WNode*> allNodes= g.getAllNodes();
    
    for (WNode* n : allNodes){
        cout<< n->value << " :{";
        for(auto const& i : n->neighbors){
            cout << "(" << i.first->value << ",";
            cout << i.second << "), ";
        }
        cout << "}" << endl;
    }
}

/******************************* main and test cases*********************************/

int main() {
    /********** testing creating random weighted graph and running Dijakstra's on it ***********/
    WeightedGraph g2= createRandomCompleteWeightedGraph(10);
    cout << "Random weighted Graph: " << endl ;
    print(g2);
    
    vector <WNode*> allNodes;
    allNodes= g2.getAllNodes();
    WNode* start= allNodes[0];
    map<WNode*, int>djPath= dijkstras( start);
    
    cout << endl << "Minimum distance from start to each node using Dijkstra's Alg. : " << endl;
    for(const auto& i : djPath){
        cout << i.first->value << ": " << i.second << endl;
    }
    
    cout << endl;
    
    /**************** creating linked list and running Dijkstra's on it ***************/
    WeightedGraph g1= createLinkedList(10);
    cout << "Linked List: " << endl;
    print(g1);
    
    allNodes= g1.getAllNodes();
    start= allNodes[0];
    
    cout << "Minimum distance from start to each node using Dijkstra's Alg. : " << endl;
    map<WNode*, int>djPath_LL= dijkstras(start);
    for(const auto& i : djPath_LL){
        cout << i.first->value << ": " << i.second << endl;
    }
    
    return 0;
}
