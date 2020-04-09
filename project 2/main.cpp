//
//  main.cpp
//  CS435-006
//  project2_part1
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
#include"Graph.h"

using namespace std;

/*************************** functions for Creating Graphs ******************************/

Graph createRandomUnweightedGraphIter(int n){
    Graph g;
    //creating nodes
    for(int i=0; i < n; i++){
        g.addNode(to_string(i));
    }
    
    vector<Node*> graphNodes= g.getAllNodes();
    //creating random edges
    srand(time(0));
    for(int i=0; i < n-1; i++){
        for(int j= i+1; j < n; j++){
            //generating random number between 0,false, and 1,true.
            int makeEdge= rand() % 2;
            if (makeEdge){
                g.addUndirectedEdge(graphNodes[i], graphNodes[j]);
            }
        }
    }
    return g;
}

Graph createLinkedList(int n){
    Graph g;
    
    //creating and adding nodes to LL
    for(int i=0; i < n; i++){
        g.addNode(to_string(i));
    }
    
    vector<Node*> graphNodes= g.getAllNodes();
    Node* current= new Node();
    
    for(int n=0; n < graphNodes.size(); n++){
        current= graphNodes[n];
        if( n+1 < graphNodes.size()){
            g.addUndirectedEdge(current, graphNodes[n+1]);
        }
    }
    return g;
}

DirectedGraph createRandomDAGIter(int n){
    DirectedGraph g;
    //creating nodes
    for(int i=0; i < n; i++){
        g.addNode(to_string(i));
    }
    
    vector<Node*> graphNodes= g.getAllNodes();
    //creating random edges
    srand(time(0));
    for(int i=0; i < n; i++){
        for(int j= 0; j < n; j++){
            //generating random number between 0,false, and 1,true.
            int makeEdge= rand() % 2;
            
            if (makeEdge){
                g.addDirectedEdge(graphNodes[i], graphNodes[j]);
            }
        }
    }
    return g;
}

/************************ printing functions for testing ***************************/

void printAdjLists(vector<Node*> allNodes){
    for (Node* n : allNodes){
        cout<< n->value << " :{";
        for(Node* neighbor : n->neighbors){
            cout << neighbor->value << ",";
        }
        cout << "}" << endl;
    }
    cout << endl;
}

void printTraversalResult(vector<Node*> traversalOutput){
    for (Node* no : traversalOutput){
        cout<< no->value << ", ";
    }
    cout << endl;
}

void print(vector<Node*> vec){
    for (Node* n : vec){
        cout<< n->value << " ";
    }
    cout << endl;
}

void printGraph(DirectedGraph g){
    vector <Node*> allNodes= g.getAllNodes();
    for (Node* n : allNodes){
        cout<< n->value << " :{";
        for(Node* neighbor : n->neighbors){
            cout << neighbor->value << ",";
        }
        cout << "}" << endl;
    }
}


/************************ linked list testing functions ************************/
void BFTRecLinkedList(Graph graph){
    GraphSearch S;
    vector<Node*> output=S.BFTRec(graph);
    printTraversalResult(output);
}


void BFTIterLinkedList(Graph graph){
    GraphSearch S;
    vector<Node*> output=S.BFTIter(graph);
    printTraversalResult(output);
}



/************************************ main and test cases *************************************/
int main() {
    
    /******************** Question 3 testing **********************/
    /********** testing creating the undirected Graphs **************/
    Graph g1= createRandomUnweightedGraphIter(7);
    
    Graph g2= createLinkedList(10);
    
    cout << "Adj lists of random unweighted graph of size 7 nodes: " << endl;
    vector <Node*> allNodes1= g1.getAllNodes();
    printAdjLists(allNodes1);
    
    cout << "Adj lists of linked list graph of size 10 nodes: " << endl;
    vector <Node*> allNodes2= g2.getAllNodes();
    printAdjLists(allNodes2);
    
    /********testing removal of an edge*************/
    Node* first= new Node("5");
    Node* second= new Node("0");
    
    g1.removeDirectedEdge(first, second);
    allNodes1= g1.getAllNodes();
    cout << "Removing edge between 0 and 5" << endl;
    cout << "Adj lists after removal: " << endl;
    printAdjLists(allNodes1);
    
    
    /*************** testing graph Search **************/
    GraphSearch S;
    Node* target= new Node("6");
    
    /*** testing DFSRec and DFSIter ***/
    vector<Node*> DFSOutput;
    
    DFSOutput= S.DFSRec(allNodes1[0], target, g1);
    cout << "DFS Rec from 0 to 6 output: " << endl;
    printTraversalResult(DFSOutput);
    
    DFSOutput= S.DFSIter(allNodes1[0], target, g1);
    cout << "DFS Iter from 0 to 6 output: " << endl;
    printTraversalResult(DFSOutput);
    
    
    /*** tsting BFTRec and BFTIter ***/
    vector<Node*> BFTOutput;
    
    BFTOutput= S.BFTRec(g1);
    cout << "BFT Rec output: " << endl;
    printTraversalResult(BFTOutput);
    
    BFTOutput= S.BFTIter(g1);
    cout << "BFT Iter output: " << endl;
    printTraversalResult(BFTOutput);
    
    /********** testing linked list graph *************/
    
    Graph LinkedList= createLinkedList(10000);
    cout << "BFT Iter on 10,000 size graph: " << endl;
    BFTIterLinkedList(LinkedList);
    cout << endl;
    cout << "BFT Rec on 10,000 size graph: " << endl;
    BFTRecLinkedList(LinkedList);
    
    
    /******************** Question 4 testing **********************/
    /********** testing creating the Directed Graphs **************/
    DirectedGraph g= createRandomDAGIter(1000);
    printGraph(g);
    cout << endl;
    
    TopSort T;
    vector<Node*>Result1= T.Kahns(g);
    cout << "Result of running Khans sort on Directed Graph: " << endl;
    print(Result1);
    
    cout << endl;
    vector<Node*>Result2= T.mDFS(g);
    cout << "Result of running mDFS sort on Directed Graph: " << endl;
    print(Result2);
    
    return 0;
}
