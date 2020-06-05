//
//  Header.h
//  
//
//  Created by Yasmin Ali.
//

#ifndef Header_h
#define Header_h

int BST_levelCount= 1;
int AVL_levelCount= 1;

int BST_totalLevelCount= 0;
int AVL_totalLevelCount= 0;

using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
    Node* parent;
    int height;
    
    Node(){
        this->left= NULL;
        this->right= NULL;
        this->parent= NULL;
        this->height= 1;
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
    
    void preOrderPrint(){
        preOrderPrint(root);
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
            BST_totalLevelCount+= BST_levelCount;
            return;
        }
        Node* current= new Node();
        current= root;
        bool newCurrent= true;
        
        
        while((current->left != NULL || current->right != NULL) && newCurrent== true){
            if(current->left != NULL && current->data > value){
                current= current->left;
                BST_levelCount+=1;
                //if current pointer changed mark it true
                newCurrent= true;
            }
            else if(current->right != NULL && current->data < value){
                current= current->right;
                BST_levelCount+=1;
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
            BST_levelCount+=1;
        }
        else if(current->data < value){
            current->right= newNode;
            newNode->parent= current;
            BST_levelCount+=1;
        }
        
        BST_totalLevelCount+= BST_levelCount;
        BST_levelCount= 1;
        
    }
    
    void deleteIter(int value, Node* current){
        
        bool loop= true;
        while(loop == true){
            if(current == NULL){
                cout << value << " is not found in the tree" << endl;
                return;
            }
            if(current->data > value){
                current= current->left;
                loop= true;
            }
            else if(current->data < value){
                current= current->right;
                loop= true;
            }
            else if (current->data == value){
                loop= false;
                if(current->right != NULL && current->left != NULL){
                    Node* MinInRight= new Node();
                    //find the minimum value on the right subtree
                    MinInRight= findMinIter(current->right);
                    current->data= MinInRight->data;
                    value= MinInRight->data;
                    current= MinInRight;
                    loop= true;
                }
                else{
                    Node* temp= new Node();
                    
                    if(current->left == NULL && current->right == NULL){
                        //checking which pointer of parent should be set to NULL
                        temp= NULL;
                    }
                    else if(current->left != NULL && current->right == NULL){
                        temp= current->left;
                        temp->parent= current->parent;
                    }
                    else if(current->right != NULL && current->left == NULL){
                        temp= current->right;
                        temp->parent= current->parent;
                    }
                    
                    //let root pointer point to temp if the node nneded to be deleted is the root
                    Node* parent= new Node();
                    
                    if(current->parent == NULL){
                        parent= NULL;
                        root= temp;
                    }
                    else{
                        parent= current->parent;
                        //the first condition means current is on the left of its parent
                        if( current->parent->data > current->data){
                            current->parent->left= temp;
                        }
                        //the second condition means current is on the right of its parent
                        else if(current->parent->data <= current->data){
                            current->parent->right= temp;
                        }
                    }
                    
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
                value= MinInRight->data;
                
                //delete the minInRight node by calling deleteRec()
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
                
                Node* parent= new Node();
                
                if(current->parent == NULL){
                    parent= NULL;
                    root= temp;
                }
                else{
                    parent= current->parent;
                    
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
    
    void preOrderPrint(Node* parent){
        if(parent != NULL){
            cout << parent->data << " ";
            preOrderPrint(parent->left);
            preOrderPrint(parent->right);
        }
    }
};




/******************************** AVL Class *********************************/

class AVL{
    private:
    Node* root;
    
    public:
    AVL(Node* r= NULL) {
        root= r;
    }
    
    
    void inOrder(vector<Node*>& nodeVec){
        inOrder(root, nodeVec);
    }
    
    void inOrderPrint(){
        inOrderPrint(root);
    }
    
    void preOrderPrint(){
        preOrderPrint(root);
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
    
    void insertRec(int value){
        insertRec(value, root);
    }
    
    /************************ Iterative functions ************************/
    
    void insertIter(int value){
        Node* newNode= new Node();
        newNode->data= value;
        
        
        if(root == NULL){
            root= newNode;
            //cout <<  "AVL level: " << AVL_levelCount << " ";
            AVL_totalLevelCount+= AVL_levelCount;
            return;
        }
        //creating a node to go through the tree starting from root to find the right position for the new value
        Node* current= new Node();
        current= root;
        bool newCurrent= true;
        
        //keep going down (left or right) through the tree until reach NULL
        while(current != NULL && newCurrent== true){
            
            if(current->left != NULL && current->data > value){
                current= current->left;
                AVL_levelCount+= 1;
                //current pointer changed so make it true
                newCurrent= true;
            }
            else if(current->right != NULL && current->data < value){
                current= current->right;
                AVL_levelCount+= 1;
                // current pointer changed so make it true
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
            AVL_levelCount+= 1;
        }
        else if(current->data < value){
            current->right= newNode;
            newNode->parent= current;
            AVL_levelCount+= 1;
        }
        
        //updating height of tree after insertion starting from the new node
        updateHeight(newNode);
        
        Node* temp= new Node();
        temp= newNode;
        //checking balance factor starting from the new node up, and rebalance the tree when needed
        while( temp != NULL){
            int BF= getBF(temp);
            //rebalance the tree
            if(BF > 1 || BF < -1){
                rebalanceTree(temp, BF);
            }
            temp= temp->parent;
        }
        
        AVL_totalLevelCount+= AVL_levelCount;
        AVL_levelCount= 1;
        
    }
    
    void deleteIter(int value, Node* current){
        bool loop= true;
        while(loop == true){
            if(current == NULL){
                cout << value << " is not found in the tree" << endl;
                return;
            }
            if(current->data > value){
                current= current->left;
                loop= true;
            }
            else if(current->data < value){
                current= current->right;
                loop= true;
            }
            else if (current->data == value){
                loop= false;
                if(current->right != NULL && current->left != NULL){
                    Node* MinInRight= new Node();
                    //find the minimum value on the right subtree
                    MinInRight= findMinIter(current->right);
                    
                    current->data= MinInRight->data;
                    value= MinInRight->data;
                    current= MinInRight;
                    loop= true;
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
                    
                    //let root pointer point to temp if the node nneded to be deleted is the root
                    Node* parent= new Node();
                    
                    if(current->parent == NULL){
                        parent= NULL;
                        root= temp;
                    }
                    else{
                        parent= current->parent;
                        //the first condition means current is on the left of its parent
                        if( current->parent->data > current->data){
                            current->parent->left= temp;
                        }
                        //the second condition means current is on the right of its parent
                        else if(current->parent->data <= current->data){
                            current->parent->right= temp;
                        }
                    }
                    while(parent != NULL){
                        updateHeight(parent);
                        parent= parent->parent;
                    }
                    //checking balance factor starting from the parent of the deleted node, and rebalance the tree when needed
                    parent= current->parent;
                    while( parent != NULL){
                        int BF= getBF(parent);
                        //rebalance the tree
                        if(BF > 1 || BF < -1){
                            rebalanceTree(parent, BF);
                        }
                        parent= parent->parent;
                    }
                    
                }
            }
        }
    }
    
    int getHeight(Node* current){
        if(current == NULL)
        return 0;
        else
        return current->height;
    }
    
    int getBF(Node* current){
        int leftHeight= getHeight(current->left);
        int rightHeight= getHeight(current->right);
        
        return(leftHeight - rightHeight);
    }
    
    void leftRotate(Node* current){
        Node* rightOfCurrent= new Node();
        Node* newRight= new Node();
        
        
        rightOfCurrent= current->right;
        newRight= rightOfCurrent->left;
        
        //changing pointers' values to perform the rotation
        rightOfCurrent->left= current;
        rightOfCurrent->parent= current->parent;
        
        if(current->parent == NULL){
            root= rightOfCurrent;
        }
        else{
            if(current->parent->data > current->data){
                current->parent->left= rightOfCurrent;
            }
            else if(current->parent->data < current->data){
                current->parent->right= rightOfCurrent;
            }
        }
        current->parent= rightOfCurrent;
        current->right= newRight;
        
        if(newRight != NULL){
            newRight->parent= current;
        }
        
        //updateHeight after rotation
        updateHeight(current);
        updateHeight(rightOfCurrent);
        
    }
    
    void rightRotate(Node* current){
        Node* leftOfCurrent= new Node();
        Node* newleft= new Node();
        
        leftOfCurrent= current->left;        //a pointer to hold the left side of the current pointer
        newleft= leftOfCurrent->right;       //a pointer to hold address of the right of left side of current node
        
        //changing pointers' values to perform the rotation
        leftOfCurrent->parent= current->parent;
        leftOfCurrent->right= current;
        
        if(current->parent == NULL){
            root= leftOfCurrent;
        }
        else{
            if(current->parent->data > current->data){
                current->parent->left= leftOfCurrent;
            }
            else if(current->parent->data < current->data){
                current->parent->right= leftOfCurrent;
            }
        }
        
        current->left= newleft;
        current->parent= leftOfCurrent;
        
        if(newleft != NULL){
            newleft->parent= current;
        }
        //updateHeight after rotation
        updateHeight(current);
        updateHeight(leftOfCurrent);
        
    }
    
    //note: left refers to the rotation done on upper node, right is the rotation on the lower node
    //the rotation on lower node(right rotation) is performed first
    void right_leftRotate(Node* current){
        rightRotate(current->right);
        leftRotate(current);
    }
    
    //note: right refers to the rotation done on upper node, while left is the rotation on the lower node
    //the rotation on lower node(left rotation) is performed first
    void left_rightRotate(Node* current){
        leftRotate(current->left);
        rightRotate(current);
    }
    
    void updateHeight(Node *current){
        Node* temp= new Node();
        temp= current;
        while(temp != NULL){
            
            int leftH= getHeight(temp->left);
            int rightH= getHeight(temp->right);
            
            temp->height= (max(leftH, rightH)+1);
            temp= temp->parent;
        }
        
        delete temp;
        temp= NULL;
    }
    
    void rebalanceTree(Node* current, int BF){
        if(BF < -1){
            if(getBF(current->right) < 0){
                //right right case
                leftRotate(current);
            }
            else if(getBF(current->right) > 0){
                //right left case
                right_leftRotate(current);
            }
        }
        else if(BF > 1){
            if(getBF(current->left) > 0){
                //left left case
                rightRotate(current);
            }
            else if(getBF(current->left) < 0){
                //left-right imbalance case
                left_rightRotate(current);
            }
        }
        
        updateHeight(current);
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
        
        updateHeight(newNode);
        Node* temp= new Node();
        temp= newNode;
        //checking balance factor starting from the new node up, and rebalance the tree when needed
        while( temp != NULL){
            int BF= getBF(temp);
            //rebalance the tree
            if(BF > 1 || BF < -1){
                rebalanceTree(temp, BF);
            }
            temp= temp->parent;
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
    
    
    void preOrderPrint(Node* parent){
        if(parent != NULL){
            cout << parent->data << " ";
            preOrderPrint(parent->left);
            preOrderPrint(parent->right);
        }
    }
};


void print(vector<int>vec){
    for(int i : vec){
        cout << i << " ";
    }
    cout << endl;
}


vector<int> getSortedArray(int n){
    vector<int> list;
    for(int i= n; i > 0; i--){
        list.push_back(i);
    }
    return list;
}

vector<int> getRandomArray(int n){
    vector<int> list;
    //filling an array of n numbers by calling getSortedArray. Each element is unique
    list= getSortedArray(n);
    
    //randomly rearrange elements in the arry.
    //the result is an array of distinct random numbers
    random_shuffle(list.begin(), list.end());
    
    return list;
}

#endif /* Header_h */
