//
//  BST.cpp
//  BST_Proj1_part1
//
//  Created by Yasmin Ali on 2/21/20.
//  Copyright © 2020 Yasmin Ali. All rights reserved.
//

#include <iostream>
#include<vector>
#include"BST.h"

using namespace std;

int main(int argc, const char * argv[]) {
    BST T;
    
    //using recursive and iterative insert methods interchangeably to insert nodes in tree
    T.insertRec(4);
    T.insertIter(5);
    T.insertRec(8);
    T.insertIter(7);
    T.insertRec(10);
    T.insertIter(2);
    T.insertRec(1);
    T.insertIter(12);
    T.insertRec(11);
    T.insertIter(6);
    T.insertRec(9);
    T.insertIter(3);
    T.insertRec(0);
    cout << "inOrder traversal of tree: " << endl;
    T.inOrderPrint();
    cout << endl << endl;
    //finding min and max using recursive methods
    cout << "Min is: " << T.findMinRec() << endl;
    cout << "Max is: " << T.findMaxRec() << endl << endl;
    
    
    cout << "testing deleteRec" << endl;
    //delete case1
    T.deleteRec(0);
    cout << "after removing 0: ";
    T.inOrderPrint();
    cout << endl;
    //case2
    T.deleteRec(12);
    cout << "after removing 12: ";
    T.inOrderPrint();
    cout << endl;
    //delete case3
    T.deleteRec(8);
    cout << "after removing 8: ";
    T.inOrderPrint();
    cout << endl << endl;
    
    cout << "testing deleteIter" << endl;
    T.deleteRec(3);
    cout << "after removing 3: ";
    T.inOrderPrint();
    cout << endl;
    //case2
    T.deleteRec(10);
    cout << "after removing 10: ";
    T.inOrderPrint();
    cout << endl;
    //delete case3
    T.deleteRec(4);
    cout << "after removing 4: ";
    T.inOrderPrint();
    cout << endl << endl;
    
    
    //finding min and max using iterative methods
    cout << "Min is: " << T.findMinIter() << endl;
    cout << "Max is: " << T.findMaxIter() << endl;
    cout << endl << endl;
    
    //using Iterative method to find next
    Node* nextNode= T.findNextIter(10);
    if( nextNode != NULL){
        cout << "value after 10 is: " << nextNode->data << endl;
    }
    else{
        cout << "either the value is not found or the value is the greatest in the tree " << endl;
    }
    //using recursive method to find next. Note: Value 8 was removed from tree.
    nextNode= T.findNextRec(8);
    if( nextNode != NULL){
        cout << "value after 2 is: " << nextNode->data << endl;
    }
    else{
        cout << "either the value is not found or the value is the greatest in the tree " << endl;
    }
    
    //using recursive method to find previous
    Node* prevNode= T.findPrevRec(5);
    if( prevNode != NULL){
        cout << "The value before 5 is: " << prevNode->data << endl;
    }
    else{
        cout << "either the value is not found or the value is the smallest in the tree " << endl;
    }
    //using Iterative method to find previous
    prevNode= T.findPrevIter(9);
    if( prevNode != NULL){
        cout << "The value before 9 is: " << prevNode->data << endl;
    }
    else{
        cout << "either the value is not found or the value is the smallest in the tree " << endl;
    }
    
    return 0;
}
