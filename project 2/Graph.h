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
#include<time.h>
#include<stdlib.h>

using namespace std;

struct Node{
    string value;
    //neighbors are nodes connected to current node by an edge
    vector<Node*> neighbors;
    bool visited;
    Node(string val= ""){
        value= val;
        visited= false;
    }
    
};

/******************************* Undirected Graph Class ********************************/

class Graph{
    vector<Node*> allNodes;
public:
    void addNode(string nodeVal){
        Node* temp= new Node(nodeVal);
        allNodes.push_back(temp);
    }
    
    void addUndirectedEdge(Node* first, Node* second){
        if(edgeFound(first, second) == false){
            first->neighbors.push_back(second);
            
            if(first->value != second->value){
                second->neighbors.push_back(first);
            }
            
        }
    }
    
    void removeDirectedEdge(Node* first, Node* second){
        for(Node* n : allNodes ){
            if(n->value == first->value){
                int index= 0;
                for (Node* neighbor :  n->neighbors){
                    if (neighbor->value == second->value){
                        (n->neighbors).erase((n->neighbors).begin() + index);
                    }
                    index++;
                }
            }
            
            if(n->value == second->value){
                int index= 0;
                for (Node* neighbor :  n->neighbors){
                    if (neighbor->value == first->value){
                        (n->neighbors).erase((n->neighbors).begin() + index);
                    }
                    index++;
                }
            }
        }
    }
    
    vector<Node*> getAllNodes(){
        return allNodes;
    }
    
    bool edgeFound(Node* first, Node* second){
        for(Node* n : first->neighbors ){
            if (n->value == second->value){
                return true;
            }
        }
        return false;
    }
    
    void reset(){
        vector<Node*> allNodes= getAllNodes();
        for( Node* node: allNodes){
            node->visited= false;
        }
    }
    
    
};

/******************************* Graph Search Class *******************************/
class GraphSearch{
public:
    
    void DFSHelper(vector<Node*>& output, Node* current, Node* goal, bool& found){
        if( found == false){
            current->visited= true;
            output.push_back(current);
            if(current->value == goal->value){
                found= true;
            }
            for (Node* neighbor: current->neighbors){
                if(!neighbor->visited){
                    DFSHelper(output, neighbor, goal, found);
                }
            }
        }
    }
    
    vector<Node*> DFSRec(Node* start,Node* end, Graph &g){
        //reset the visited flag of all nodes in the graph to be false before starting the search
        g.reset();
        vector<Node*> output;
        bool found= false;
        DFSHelper(output, start, end, found);
        if (found == false){
            output= {};
        }
        return output;
    }
    
    vector<Node*> DFSIter(Node* start,Node* end, Graph &g){
        //reset the visited flag of all nodes in the graph to false before starting the search
        g.reset();
        vector<Node*> output;
        stack<Node*> s;
        start->visited= true;
        s.push(start);
        while (!s.empty()){
            Node* newCurr= s.top();
            output.push_back(newCurr);
            s.pop();
            if(newCurr->value == end->value){
                return output;
            }
            for(Node* v : newCurr->neighbors){
                if(!v->visited){
                    v->visited= true;
                    s.push(v);
                }
            }
        }
        //if all nodes on the stack are popped and the element is not found, return empty vector. no path to the target node from start node, or the node does not exist.
        return {};
    }
    
    vector<Node*> BFTIter(Graph& g){
        //reset the visited flag of all nodes in the graph to false before starting the traversal
        g.reset();
        queue<Node*> q;
        vector<Node*> allNodes= g.getAllNodes();
        vector<Node*> output;
        
        for(Node* node: allNodes){
            if(!node->visited){
                q.push(node);
                node->visited= true;
                while (!q.empty()){
                    Node* newCurr= q.front();
                    output.push_back(newCurr);
                    q.pop();
                    for(Node* v : newCurr->neighbors){
                        if(!v->visited){
                            q.push(v);
                            v->visited= true;
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
            for(Node* neighbor : newCurr->neighbors){
                if(!neighbor->visited){
                    q.push(neighbor);
                    neighbor->visited= true;
                }
            }
            //call BFTHelper after inserting all neighbors to the queue.
            BFTHelper(output, q);
        }
        
    }
    
    vector<Node*> BFTRec(Graph& g){
        //reset the visited flag of all nodes in the graph to false before starting the traversal
        g.reset();
        queue<Node*> q;
        vector<Node*> allNodes= g.getAllNodes();
        vector<Node*> output;
        
        for(Node* node: allNodes){
            if(!node->visited){
                q.push(node);
                node->visited= true;
                BFTHelper(output, q);
            }
        }
        return output;
    }
};


/******************************* Undirected Graph Class ********************************/
class DirectedGraph{
    vector<Node*> allNodes;
public:
    void addNode(string nodeVal){
        Node* temp= new Node(nodeVal);
        allNodes.push_back(temp);
    }
    
    void addDirectedEdge(Node* first, Node* second){
        //no double edges && no edge to itself
        if(first->value != second->value){
            first->neighbors.push_back(second);
            //after adding an edge check if first is reachable from second; a cycle found
            if(cycleFound(second, first)){
                //if yes: remove the edge
                first->neighbors.pop_back();
            }
        }
    }
    
    //cycleFound is just a modified version of DFS.
    //it is based on the idea: if a path is found from second node to first, then there is a cycle in the graph
    bool cycleFound(Node* second, Node* first){
        //reset the visited flag of all nodes in the graph to false before starting the search
        reset();
        
        stack<Node*> s;
        second->visited= true;
        s.push(second);
        while (!s.empty()){
            Node* newCurr= s.top();
            //output.push_back(newCurr);
            s.pop();
            if(newCurr->value == first->value){
                return true;
            }
            for(Node* v : newCurr->neighbors){
                if(!v->visited){
                    v->visited= true;
                    s.push(v);
                }
            }
        }
        return false;
    }
    
    void removeDirectedEdge(Node* first, Node* second){
        for(Node* n : allNodes ){
            if(n->value == first->value){
                int index= 0;
                for (Node* neighbor :  n->neighbors){
                    if (neighbor->value == second->value){
                        (n->neighbors).erase((n->neighbors).begin() + index); //erasing element from neighbors vector at index
                    }
                    index++;
                }
            }
        }
    }
    
    vector<Node*> getAllNodes(){
        return allNodes;
    }
    
    bool edgeFound(Node* first, Node* second){
        for(Node* n : allNodes ){
            if( n->value == first->value)
                //cout << n->value << " ";
                for(Node* neighbor : n->neighbors){
                    if (neighbor->value == second->value){
                        cout << n->value << " " << neighbor->value << " " << second->value << endl;
                        return true;
                    }
                }
        }
        return false;
    }
    void reset(){
        vector<Node*> allNodes= getAllNodes();
        for( Node* node: allNodes){
            node->visited= false;
        }
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
            for(Node* neighbor : node->neighbors){
                inComingDegreeMap[neighbor]++;
            }
        }
        return inComingDegreeMap;
    }
    
    
    void addNodesWithoutDependenciesToQueue(map<Node*, int> &degreesMap, queue<Node*>& q){
        for(auto const& i : degreesMap ){
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
        addNodesWithoutDependenciesToQueue(degreesMap, q);
        
        while( !q.empty()){
            Node* temp= q.front();
            sortedOutput.push_back(temp);
            q.pop();
            
            for(Node* neighbor : temp->neighbors){
                degreesMap[neighbor]--;
            }
            addNodesWithoutDependenciesToQueue(degreesMap, q);
        }
        
        return sortedOutput;
    }
    
    void mDFSHelper(stack<Node*> &s, Node* current){
        current->visited= true;
        
        for(Node* neighbor : current->neighbors){
            if(!neighbor->visited){
                mDFSHelper(s, neighbor);
            }
        }
        s.push(current);
    }
    
    vector<Node*> mDFS(DirectedGraph graph){
        //reset visited flage of all nodes to be false
        graph.reset();
        
        stack<Node*> s;
        vector<Node*>output;
        vector<Node*> allNodes= graph.getAllNodes();
        
        for(Node* node : allNodes){
            if(!node->visited){
                mDFSHelper(s, node);
            }
            
        }
        
        while(!s.empty()){
            Node* temp= s.top();
            output.push_back(temp);
            s.pop();
        }
        
        return output;
    }
    
};


