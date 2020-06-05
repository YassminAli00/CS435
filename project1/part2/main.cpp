//  Name: Yasmin Ali.
//  CS435-006
//  Project1_part2
//  Includes: test cases in main
//  Created by Yasmin Ali on 03/04/20.
//

#include <iostream>
#include<algorithm>
#include<vector>
#include <chrono>
#include "BST_AVL.h"



/*********************************** main(testing BST and AVL)************************************/
int main() {
    
    int n= 10000;
    
    vector<int> randomList;
    vector<int> sortedList;
    
    randomList= getRandomArray(n);
    sortedList= getSortedArray(n);
    
    
    
    AVL AVLRandomIter;
    BST BSTRandomRec;
    
    //Answer for Question 5(b).
    for(int i=0; i < randomList.size(); i++){
        AVLRandomIter.insertIter(randomList[i]);
        BSTRandomRec.insertRec(randomList[i]);
    }
    
    AVL_totalLevelCount = BST_totalLevelCount= 0;
    
    BST BSTRandom;
    AVL AVLRandom;
    
    //Answer for Question 5(c).
    for(int i=0; i < randomList.size(); i++){
        AVLRandom.insertIter(randomList[i]);
        BSTRandom.insertIter(randomList[i]);
    }
    
    //Answer for Question 6(b).
    cout << "Total levels using getRandomArray() and iterative insert" << endl;
    cout << "Total iterative AVL level: " <<  AVL_totalLevelCount << endl;
    cout << "Total iterative BST level: " <<  BST_totalLevelCount << endl;
    cout << endl;
    
    //zero out the counter to do the following test
    AVL_totalLevelCount = BST_totalLevelCount= 0;
    
    
    BST BSTSorted;
    AVL AVLSorted;
    
    //Answer for Question 6(c).
    for(int i=0; i < sortedList.size(); i++){
        AVLSorted.insertIter(sortedList[i]);
        BSTSorted.insertIter(sortedList[i]);
    }
    cout << "Total levels using getSortedArray() and iterative insert" << endl;
    cout << "Total iterative AVL level: " <<  AVL_totalLevelCount << endl;
    cout << "Total iterative BST level: " <<  BST_totalLevelCount << endl;
    cout << endl;
    
    //zero out the counter to do the following test
    AVL_totalLevelCount = BST_totalLevelCount= 0;
    
    
    
    //***************************** tests for Question 7(a) (measuring time) ******************************************//
    
    
    
    BST BSTRec;
    
    //testing time for BST.insertRec.
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0; i < randomList.size(); i++){
        BSTRec.insertRec(randomList[i]);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    cout << "Time of recersive BST insertion using random list: " << duration.count() << endl << endl;
    
    
    //testing time for BST.insertIter and AVL.insertIter on random input.
    BST TRandom;
    AVL VRandom;
    
    auto start1 = std::chrono::high_resolution_clock::now();
    for(int i=0; i < randomList.size(); i++){
        //cout << "inserting(" << randomList[i] << "): " << endl;
        VRandom.insertIter(randomList[i]);
    }
    auto stop1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop1 - start1);
    cout << "Time of iterative AVL insertion using random list: " << duration1.count() << endl;
    
    auto start2 = std::chrono::high_resolution_clock::now();
    for(int i=0; i < randomList.size(); i++){
        //cout << "inserting(" << randomList[i] << "): " << endl;
        TRandom.insertIter(randomList[i]);
    }
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(stop2 - start2);
    cout << "Time of iterative BST insertion using random list: " << duration2.count() << endl;
    
    cout << endl;
    
    
    //testing time for BST.insertIter and AVL.insertIter on sorted input.
    BST TSorted;
    AVL VSorted;
    
    auto start3 = std::chrono::high_resolution_clock::now();
    for(int i=0; i < sortedList.size(); i++){
        VSorted.insertIter(sortedList[i]);
    }
    auto stop3 = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(stop3 - start3);
    cout << "Time of iterative AVL insertion using sorted list: " << duration3.count() << endl;
    
    auto start4 = std::chrono::high_resolution_clock::now();
    for(int i=0; i < sortedList.size(); i++){
        TSorted.insertIter(sortedList[i]);
    }
    auto stop4 = std::chrono::high_resolution_clock::now();
    auto duration4 = std::chrono::duration_cast<std::chrono::milliseconds>(stop4 - start4);
    cout << "Time of iterative BST insertion using sorted list: " << duration4.count() << endl;
    
    cout << endl;
    
    
    //testing time for BST.deleteIter and AVL.deleteIter on random input.
    auto start5 = std::chrono::high_resolution_clock::now();
    for(int i=0; i < randomList.size(); i++){
        VRandom.deleteIter(randomList[i]);
    }
    auto stop5 = std::chrono::high_resolution_clock::now();
    auto duration5 = std::chrono::duration_cast<std::chrono::milliseconds>(stop5 - start5);
    cout << "Time of iterative AVL delete using random list: " << duration5.count() << endl;
    
    auto start6 = std::chrono::high_resolution_clock::now();
    for(int i=0; i < randomList.size(); i++){
        TRandom.deleteIter(randomList[i]);
    }
    auto stop6 = std::chrono::high_resolution_clock::now();
    auto duration6 = std::chrono::duration_cast<std::chrono::milliseconds>(stop6 - start6);
    cout << "Time of iterative BST delete using random list " << duration6.count() << endl;
    
    cout << endl;
    
    
    //testing time for BST.deleteIter and AVL.deleteIter on sorted input.
    auto start7 = std::chrono::high_resolution_clock::now();
    for(int i= sortedList.size()-1; i >= 0; i--){
        VSorted.deleteIter(sortedList[i]);
    }
    auto stop7 = std::chrono::high_resolution_clock::now();
    auto duration7 = std::chrono::duration_cast<std::chrono::milliseconds>(stop7 - start7);
    cout << "Time of iterative AVL delete using sorted list: " << duration7.count() << endl;
    
    
    auto start8 = std::chrono::high_resolution_clock::now();
    for(int i= sortedList.size()-1; i >= 0; i--){
        TSorted.deleteIter(sortedList[i]);
    }
    auto stop8 = std::chrono::high_resolution_clock::now();
    auto duration8 = std::chrono::duration_cast<std::chrono::milliseconds>(stop8 - start8);
    cout << "Time of iterative BST delete using sorted list: " << duration8.count() << endl;
    
    cout << endl;
    
    
    return 0;
}
