//
//  
//  ArrayOfInt.cpp
//
//  Created by Yasmin Ali on 2/23/20.
//  Copyright © 2020 Yasmin Ali. All rights reserved.
//

#include <iostream>
#include<algorithm>
#include<vector>


using namespace std;

void print(vector<int>vec){
    for(int i : vec){
        cout << i << " ";
    }
    cout << endl;
}


vector<int> getSortedArray(int n){
    vector<int> list;
    for(int i= n; i >= 0; i--){
        list.push_back(i);
    }
    return list;
}

vector<int> getRandomArray(int n){
    vector<int> list;
    
    //filling an array of n numbers by calling getRandomArray. Each element is unique
    list= getSortedArray(n);
    
    //randomly rearrange elements in the arry.
    //the result is an array of distinct random numbers
    random_shuffle(list.begin(), list.end());
    
    return list;
}



int main() {
    
    int n;
    cout << "How many rand numbers?  " << endl;
    cin >> n;
    
    vector<int> vec1;
    vector<int> vec2;
    vec1= getRandomArray(n);
    print(vec1);
    vec2= getSortedArray(n);
    print(vec2);
    
    return 0;
}
