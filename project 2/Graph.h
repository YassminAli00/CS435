//
//  Graph.h
//  CS435-006
//  project2
//  Created by: Yassmin Ali
//

#include <iostream>
#include<vector>
#include<string>
#include<stack>
#include<queue>
#include<map>
#include<stdlib.h>

using namespace std;


struct Node{
protected:
    //neighbors are nodes connected to current node by an edge
    vector<Node*> neighbors;
    string value;
    bool visited;
public:
    Node(string val= ""){
        value= val;
        visited= false;
        neighbors= {};
    }
    string getValue(){
        return value;
    }
    vector<Node*> getNeighbors(){
        return neighbors;
    }
    void addNeighbor(Node* node){
        this->neighbors.push_back(node);
    }
    void removeNeighbor(int index){
        neighbors.erase(neighbors.begin() + index);
    }
    void removeLastNeighbor(){
        neighbors.pop_back();
    }
    bool getVisited(){
        return visited;
    }
    void setVisited(bool v){
        visited= v;
    }
};

/******************* Graph class ****************************/
class Graph{
protected:
    vector<Node*> allNodes;
public:
    void addNode(string nodeVal){
        Node* temp= new Node(nodeVal);
        allNodes.push_back(temp);
    }
    
    void addUndirectedEdge(Node* first, Node* second){
        if(first == NULL || second == NULL)
            return;
        if(edgeFound(first, second) == false){
            first->addNeighbor(second);
            if(first->getValue() != second->getValue()){
                second->addNeighbor(first);
            }
        }
    }
    
    void removeUnDirectedEdge(Node* first, Node* second){
        if (allNodes.size() < 1)
            return;
        
        for(Node* current : allNodes ){
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
    
    void checkAndRemove(Node* current, Node* needsRemoval){
        vector<Node*> neighbors= current->getNeighbors();
        if(neighbors.size() < 1)
            return;
        
        int index= 0;
        for (Node* neighbor : neighbors){
            //when needsRemoval is found, remove it
            if (neighbor->getValue() == needsRemoval->getValue()){
                //removes neighbor when located at index (index)
                current->removeNeighbor(index);
                break;
            }
            index++;
        }
    }
    
    vector<Node*> getAllNodes(){
        return allNodes;
    }
    
    bool edgeFound(Node* first, Node* second){
        for(Node* n : first->getNeighbors() ){
            if (n->getValue() == second->getValue()){
                return true;
            }
        }
        return false;
    }
    
    void resetVisited(){
        vector<Node*> allNodes= getAllNodes();
        for( Node* node: allNodes){
            node->setVisited(false);
        }
    }
};

/******************************* UndirectedGraph Class ********************************/
//child of Graph
class UndirectedGraph : public Graph{
};

/******************************* Directed Graph Class ********************************/
//child of Graph
class DirectedGraph : public Graph{
public:
    void addDirectedEdge(Node* first, Node* second){
        //no edge to itself
        if(first->getValue() != second->getValue() && !edgeFound(first, second)){
            first->addNeighbor(second);
            //after adding an edge check if first is reachable from second; a cycle found
            if(cycleFound(second, first)){
                //if yes: remove the edge
                first->removeLastNeighbor();
            }
        }
    }
    //cycleFound is just a modified version of DFS.
    //it is based on the idea: if a path is found from second node to first, then there is a cycle in the graph
    bool cycleFound(Node* second, Node* first){
        //reset the visited flag of all nodes in the graph to false before starting the search
        resetVisited();
        stack<Node*> nodeStack;
        second->setVisited(true);
        nodeStack.push(second);
        while (!nodeStack.empty()){
            Node* newCurr= nodeStack.top();
            nodeStack.pop();
            if(newCurr->getValue() == first->getValue()){
                return true;
            }
            for(Node* v : newCurr->getNeighbors()){
                if(!v->getVisited()){
                    v->setVisited(true);
                    nodeStack.push(v);
                }
            }
        }
        return false;
    }
    
    void removeDirectedEdge(Node* first, Node* second){
        if(first == NULL || second == NULL)
            return;
        
        if (allNodes.size() < 1)
            return;
        for(Node* current : allNodes ){
            //when first is found in the graph remove second from first
            if(current->getValue() == first->getValue()){
                checkAndRemove(current, second);
            }
        }
    }
};

/******************************* Graph Search Class *******************************/
class GraphSearch{
public:
    void DFSHelper(vector<Node*>& output, Node* current, Node* end, bool &found){
        if( found == false){
            current->setVisited(true);
            output.push_back(current);
            if(current->getValue() == end->getValue()){
                found= true;
            }
            for (Node* neighbor: current->getNeighbors()){
                if(!neighbor->getVisited()){
                    DFSHelper(output, neighbor, end, found);
                }
            }
        }
    }
    
    vector<Node*> DFSRec(Node* start,Node* end, UndirectedGraph &g){
        //reset the visited flag of all nodes in the graph to be false before starting the search
        g.resetVisited();
        vector<Node*> output;
        bool found= false;
        DFSHelper(output, start, end, found);
        if (found == false){
            output= {};
        }
        return output;
    }
    
    vector<Node*> DFSIter(Node* start,Node* end, UndirectedGraph &g){
        //reset the visited flag of all nodes in the graph to false before starting the search
        g.resetVisited();
        vector<Node*> output;
        stack<Node*> nodeStack;
        start->setVisited(true);
        nodeStack.push(start);
        while (!nodeStack.empty()){
            Node* newCurr= nodeStack.top();
            output.push_back(newCurr);
            nodeStack.pop();
            if(newCurr->getValue() == end->getValue()){
                return output;
            }
            for(Node* v : newCurr->getNeighbors()){
                if(!v->getVisited()){
                    v->setVisited(true);
                    nodeStack.push(v);
                }
            }
        }
        //if all nodes on the stack are popped and the element is not found, return empty vector. no path to the target node from start node, or the node does not exist.
        return {};
    }
    
    vector<Node*> BFTIter(UndirectedGraph& g){
        //reset the visited flag of all nodes in the graph to false before starting the traversal
        g.resetVisited();
        queue<Node*> q;
        vector<Node*> allNodes= g.getAllNodes();
        vector<Node*> output;
        
        for(Node* node: allNodes){
            if(!node->getVisited()){
                q.push(node);
                node->setVisited(true);
                while (!q.empty()){
                    Node* newCurr= q.front();
                    output.push_back(newCurr);
                    q.pop();
                    for(Node* v : newCurr->getNeighbors()){
                        if(!v->getVisited()){
                            q.push(v);
                            v->setVisited(true);
                        }
                    }
                }
            }
        }
        return output;
    }
    
    void BFTHelper(vector<Node*>& output, queue<Node*>& q){
        if (!q.empty()){
            Node* newCurr= q.front();
            output.push_back(newCurr);
            q.pop();
            for(Node* neighbor : newCurr->getNeighbors()){
                if(!neighbor->getVisited()){
                    q.push(neighbor);
                    neighbor->setVisited(true);
                }
            }
            //call BFTHelper after inserting all neighbors to the queue.
            BFTHelper(output, q);
        }
    }
    
    vector<Node*> BFTRec(UndirectedGraph& g){
        //reset the visited flag of all nodes in the graph to false before starting the traversal
        g.resetVisited();
        queue<Node*> q;
        vector<Node*> allNodes= g.getAllNodes();
        vector<Node*> output;
        
        for(Node* node: allNodes){
            if(!node->getVisited()){
                q.push(node);
                node->setVisited(true);
                BFTHelper(output, q);
            }
        }
        return output;
    }
};
/******************************* TopSort Class *******************************/
class TopSort{
public:
    map<Node*,int> getNodesDegrees(DirectedGraph g){
        vector<Node*> allNodes= g.getAllNodes();
        map<Node*, int> inComingDegreeMap;
        
        for (Node* node : allNodes){
            inComingDegreeMap[node]= 0;
        }
        for( Node* node:  allNodes){
            for(Node* neighbor : node->getNeighbors()){
                inComingDegreeMap[neighbor]++;
            }
        }
        return inComingDegreeMap;
    }
    
    void addNodesWithoutDependencies(map<Node*, int> &degreesMap, queue<Node*>& q){
        for(auto& i : degreesMap ){
            if(i.second == 0){
                q.push(i.first);
                //set the current value's in-degree to be -1 so that we don't add it back to the queue.
                degreesMap[i.first]--;
            }
        }
    }
    
    vector<Node*> Kahns(DirectedGraph graph){
        queue<Node*> q;
        vector<Node*> sortedOutput;
        map<Node*, int> degreesMap= getNodesDegrees(graph);
        addNodesWithoutDependencies(degreesMap, q);
        
        while( !q.empty()){
            Node* temp= q.front();
            sortedOutput.push_back(temp);
            q.pop();
            
            for(Node* neighbor : temp->getNeighbors()){
                degreesMap[neighbor]--;
            }
            addNodesWithoutDependencies(degreesMap, q);
        }
        return sortedOutput;
    }
    
    void mDFSHelper(stack<Node*> &nodeStack, Node* current){
        current->setVisited(true);
        
        for(Node* neighbor : current->getNeighbors()){
            if(!neighbor->getVisited()){
                mDFSHelper(nodeStack, neighbor);
            }
        }
        nodeStack.push(current);
    }
    
    vector<Node*> mDFS(DirectedGraph graph){
        
        stack<Node*> nodeStack;
        vector<Node*>output;
        vector<Node*> allNodes= graph.getAllNodes();
        for(Node* node : allNodes){
            if(!node->getVisited()){
                mDFSHelper(nodeStack, node);
            }
        }
        while(!nodeStack.empty()){
            Node* temp= nodeStack.top();
            output.push_back(temp);
            nodeStack.pop();
        }
        return output;
    }
};
