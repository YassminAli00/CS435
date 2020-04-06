//
//  TreeSort.cpp
//  TreeSort_proj1
//
//  Created by Yasmin Ali on 2/21/20.
//  Copyright © 2020 Yasmin Ali. All rights reserved.
//

#include <iostream>
#include"BST.h"
#include<vector>

using namespace std;


 void print(vector<Node*> vec){
     for( Node* i : vec){
         cout << i->data << " ";
     }
 }


vector<Node*> sort(vector <int> list){
    BST T;
    vector<Node*>sortedList;
    
    for(int j=0; j < list.size(); j++){
        T.insertRec(list[j]);
    }
    
    T.inOrder(sortedList);
    cout << endl;
    
    return sortedList;
}

int main() {
    
    int numbers;
    cout << "how many numbers? ";
    cin >> numbers;
    
    cout << "numbers: ";
    vector<int>list;
    int num;
    
    for(int i=0; i < numbers; i++){
        cin >> num;
        list.push_back(num);
    }
    
    vector<Node*>sortedList;
    sortedList= sort(list);
    print(sortedList);
    
    return 0;
}
