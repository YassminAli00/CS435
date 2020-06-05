//  BST.h
//  BST_Proj1_part1
//
//  Created by Yasmin Ali on 2/23/20.
//  Copyright © 2020 Yasmin Ali. All rights reserved.
//

#include<vector>
#include<iostream>

using namespace std;
struct Node{
    int data;
    Node* left;
    Node* right;
    Node* parent;
    
    Node(){
        this->left= NULL;
        this->right= NULL;
        this->parent= NULL;
    }
};

class BST{
private:
    Node* root;
    
public:
    BST(Node* r= NULL) {
        root= r;
    }
    
    /*********************** Recursive functions ***********************/
    void insertRec(int value){
        insertRec(value, root);
    }

    void inOrder(vector<Node*>& nodeVec){
        inOrder(root, nodeVec);
    }
    
    void inOrderPrint(){
        inOrderPrint(root);
    }
    int findMinRec(){
        Node* minNode= findMinRec(root);
        return (minNode->data);
    }
    int findMaxRec(){
        Node* maxNode= findMaxRec(root);
        return (maxNode->data);
    }
    void deleteRec(int value){
        deleteRec(value, root);
    }
    
    int findMinIter(){
        return((findMinIter(root))->data);
    }
    
    int findMaxIter(){
        return((findMaxIter(root))->data);
    }
    void deleteIter(int value){
        deleteIter(value, root);
    }
    
    Node* findNextRec(int value){
        //this function returns a node with the next largest value
        vector<Node*> nodesList;
        inOrder(root, nodesList);
        
        int currentIndex= findNextRec(value, nodesList, 0);
        if(currentIndex+1 >=  nodesList.size()){
            return NULL;
        }
        //return the next node
        return(nodesList[currentIndex+1]);
    }
    
    Node* findPrevRec(int value){
        //this function returns a node with the previous largest value
        vector<Node*> nodesList;
        inOrder(root, nodesList);
        
        int currentIndex= findNextRec(value, nodesList, 0);   //an overload version of findNextRec that can be found in private functions
        if(currentIndex-1 <  0){
            return NULL;
        }
        //return the next node
        return(nodesList[currentIndex-1]);
    }
    
    
    /************************ Iterative functions ************************/
    
    void insertIter(int value){
        Node* newNode= new Node();
        newNode->data= value;
        
        if(root == NULL){
            root= newNode;
            return;
        }
        Node* current= new Node();
        current= root;
        bool newCurrent= true;
        
        while((current->left != NULL || current->right != NULL) && newCurrent== true){
            if(current->left != NULL && current->data > value){
                current= current->left;
                //if current pointer changed mark it true
                newCurrent= true;
            }
            else if(current->right != NULL && current->data < value){
                current= current->right;
                //if current pointer changed mark it true
                newCurrent= true;
            }
            else{
                //if current pointer didn't chang mark it false to stop the loop
                newCurrent= false;
            }
        }
        if(current->data > value){
            current->left= newNode;
            newNode->parent= current;
        }
        else if(current->data < value){
            current->right= newNode;
            newNode->parent= current;
        }
    }
    
    void deleteIter(int value, Node* current){
        if(current == NULL){
            cout << value << " is not found in the tree" << endl;
            return;
        }
        if(current->data > value){
            deleteRec(value, current->left);
        }
        else if(current->data < value){
            deleteRec(value, current->right);
        }
        else if (current->data == value){
            
            bool deleteNeeded = true;
            while( deleteNeeded == true){
                deleteNeeded= false;
                if(current->right != NULL && current->left != NULL){
                    Node* MinInRight= new Node();
                    //find the minimum value on the right subtree
                    MinInRight= findMinIter(current->right);
                    current->data= MinInRight->data;
                    //delete the minInright node by calling deleteRec()
                    value= MinInRight->data;
                    deleteNeeded = true;
                    current= MinInRight;
                }
                else{
                    Node* temp= new Node();
                    
                    if(current->left == NULL && current->right == NULL){
                        //checking which pointer of parent should be set to NULL
                        temp= NULL;
                    }
                    else if(current->left != NULL && current->right == NULL){
                        //temp= current;
                        temp= current->left;
                        temp->parent= current->parent;
                    }
                    else if(current->right != NULL && current->left == NULL){
                        temp= current->right;
                        temp->parent= current->parent;
                    }
                    
                    //the first condition means current is on the left of its parent
                    if( current->parent->data > current->data){
                        current->parent->left= temp;
                    }
                    //the second condition means current is on the right of its parent
                    else if(current->parent->data <= current->data){
                        current->parent->right= temp;
                    }
                    delete current;
                    current= NULL;
                }
            }
        }
    }
    
    Node* findNextIter(int value){
        //this function returns a node with the next largest value
        vector<Node*> nodesList;
        inOrder(root, nodesList);
        
        int found= -1;
        
        for(int i= 0; i < nodesList.size(); i++){
            if(nodesList[i]->data == value){
                found= i;
                break;
            }
        }
        if(found == -1){
            return NULL;
        }
        if(found+1 >=  nodesList.size()){
            return NULL;
        }
        //return the next node
        return(nodesList[found+1]);
    }
    
    Node* findPrevIter(int value){
        //traversing the tree in in-order travesal and save nodes in a vector
        vector<Node*> nodesList;
        inOrder(root, nodesList);
        
        //index is the index of the node value in the tree
        int index=findValue(value, nodesList);
        //if index= 0 then it is the smallest in the tree and there is no previous
        if(index <= 0){
            return NULL;
        }
        //return the previous node
        return(nodesList[index-1]);
    }
    
    int findValue(int value, vector<Node*> nodesList){
        //this function finds the node in the node's vector that holds the required value
        int index= -1;
        for(int i= 0; i < nodesList.size(); i++){
            if(nodesList[i]->data == value){
                index= i;
                break;
            }
        }
        return index;
    }
    
    Node* findMinIter(Node* current){
        if(current == NULL){
            return NULL;
        }
        
        while(current->left != NULL){
            current= current->left;
        }
        return (current);
    }
    
    Node* findMaxIter(Node* current){
        if(current == NULL){
            return NULL;
        }
        
        while(current->right != NULL){
            current= current->right;
        }
        return (current);
    }
    
    /**************************** Private functions ***************************/
private:
    void insertRec(int value, Node* node){
        Node* newNode= new Node();
        newNode->data= value;
        
        //insert to the root if tree is empty
        if(root == NULL){
            root= newNode;
            return;
        }
        //go right if value > current node value
        if(value > node->data){
            if(node->right== NULL){
                node->right= newNode;
                newNode->parent= node;
            }
            else{
                insertRec(value, node->right);
            }
        }
        //go left if value < current node value
        else if(value < node->data){
            if(node->left== NULL){
                node->left= newNode;
                newNode->parent= node;
            }
            else{
                insertRec(value, node->left);
            }
        }
    }
    
    Node* findMinRec(Node* node){
        if (node == NULL){
            return NULL;
        }
        Node* minNode= node;
        if(node->left != NULL){
            minNode= findMinRec(node->left);
        }
        return minNode;
    }
    
    Node* findMaxRec(Node* node){
        if (node == NULL){
            return NULL;
        }
        Node* maxNode= node;
        if(node->right != NULL){
            maxNode= findMaxRec(node->right);
        }
        return maxNode;
    }
    
    void deleteRec(int value, Node* current){
        if(current == NULL){
            cout << value << " is not found in the tree" << endl;
            return;
        }
        if(current->data > value){
            deleteRec(value, current->left);
        }
        else if(current->data < value){
            deleteRec(value, current->right);
        }
        else if (current->data == value){
            if(current->right != NULL && current->left != NULL){
                Node* MinInRight= new Node();
                //find the minimum value on the right subtree
                MinInRight= findMinRec(current->right);
                current->data= MinInRight->data;
                //delete the minInright node by calling deleteRec()
                value= MinInRight->data;
                deleteRec(value, MinInRight);
            }
            else{
                Node* temp= new Node();
                
                if(current->left == NULL && current->right == NULL){
                    //checking which pointer of parent should be set to NULL
                    temp= NULL;
                }
                else if(current->left != NULL && current->right == NULL){
                    //temp= current;
                    temp= current->left;
                    temp->parent= current->parent;
                }
                else if(current->right != NULL && current->left == NULL){
                    temp= current->right;
                    temp->parent= current->parent;
                }
                
                //the first condition means current is on the left of its parent
                if( current->parent->data > current->data){
                    current->parent->left= temp;
                }
                //the second condition means current is on the right of its parent
                else if(current->parent->data <= current->data){
                    current->parent->right= temp;
                }
                delete current;
                current= NULL;
            }
        }
    }
    
    int findNextRec(int value, vector<Node*> nodesList, int index){
        if( index < nodesList.size() ){
            if(nodesList[index]->data != value){
                index= findNextRec(value, nodesList, index+1);
            }
        }
        //when the value is found return its index in the list
        return index;
    }
    
    int findPrevRec(int value, vector<Node*> nodesList, int index){
        if(index < nodesList.size() ){
            if(nodesList[index]->data != value){
                index= findPrevRec(value, nodesList, index+1);
            }
        }
        //when the value is found return its index in the list
        return index;
    }
    
    void inOrderPrint(Node* parent){
        if(parent != NULL){
            inOrderPrint(parent->left);
            cout << parent->data << " ";
            inOrderPrint(parent->right);
        }
    }
    
    void inOrder(Node* parent, vector<Node*>& nodeVec){
        if(parent != NULL){
            inOrder(parent->left, nodeVec);
            nodeVec.push_back(parent);
            inOrder(parent->right, nodeVec);
        }
    }
};
