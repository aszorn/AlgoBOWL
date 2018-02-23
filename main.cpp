#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

//May not be in a working state
int main() {

    int nodes, edges;
    ifstream inFile;
    inFile.open("points.txt");

    if (!inFile) {
        cout << "Unable to open file points.txt";
        exit(1);   // call system to stop
    }

    inFile >> nodes >> edges; //stores the first row which is the number of points and edges

    int costs[nodes][nodes]; //creates a matrix of zeros
    int pt1;
    int pt2;
    int cost;

	//initialize costs to 0
    for (int i = 0; i < nodes; i++){
        for(int j = 0; j < nodes; j++){
            costs[i][j] = 0;
        }
    }

	//read in points and the edge cost
    while(inFile>>pt1>>pt2>>cost){
        pt1--; //points are 0-indexed
        pt2--;
        costs[pt1][pt2]=cost;
        costs[pt2][pt1]=cost;
    }

    inFile.close();

	//each group is exactly half the total number of nodes
    //cout << N/2 << endl << endl;
    int group1[nodes/2];
    int group2[nodes/2];

	//for comparison later
    int tempGroup1[nodes/2];
    int tempGroup2[nodes/2];


    for (int i = 0; i<nodes; ++i){
        if(i < nodes/2){
            group1[i] = i+1;
            tempGroup1[i] = i+1;
			//cout << "group1 holds node " << i+1 << " at index " << i << endl;
		}
        else{
            group2[i - nodes/2] = i+1;
            tempGroup2[i-nodes/2] = i+1;
			//cout << "group2 holds node " << i+1 << " at index " << i << endl;
        }
    }
	//cout << endl << endl;

    for (int i = 0; i < nodes/2; i++){
        /*for(int j = 0; j < N; j++){
            cout << costs[i][j] << " ";
        }*/
        //cout << group1[i]<< " " << group2[i] << endl;

    }

    //cout << endl;

    //int g1 = sizeof(group1[0]);
    //int g2 = sizeof(group2[0]);

    //cout << g1 << endl << endl;

    int prevCost = 0;
    for (int i = 0; i< nodes/2; i++){
        for (int j = 0; j< nodes/2; j++) {
            int tempG1Cost = group1[i]-1;
            int tempG2Cost = group2[j]-1;
			//cout << "adding costs from node " << group1[i]-1 << " to node " << group2[j]-1 << endl;
			//cout << tempG1Cost << " " << tempG2Cost << endl;
            prevCost = prevCost + costs[tempG1Cost][tempG2Cost];
			//cout << "that cost was " << costs[tempG1Cost][tempG2Cost] << endl;
            //cout << prevCost << endl;
        }
    }
	cout << "prevCost is now " << prevCost << endl << endl;

    int nextCost = -1;
    int externalIndex;
    int internalIndex;

	//LOOP TO FIND LOWEST COST
    while (prevCost>nextCost) { //while we can still find a lower cost
        int externalCosts[nodes];
        externalIndex = 0;
		int largestExternal = INT_MIN;

		//TODO: Consider keeping an array of external costs to consider the lowest with mutual external bonds
		//Example: swapping 5 with 2. 5 has external of 3, 2 has external of 1. 5 and 2 have shared path of 1, so 5 really only has external of 2.
		//Probably still pick the lowest internal of the other group
        for (int i = 0; i < nodes; i++) {
            externalCosts[i] = 0;
            for (int j = 0; j < nodes; j++) {
                externalCosts[i] += costs[i][j];
            }
			cout << "external cost for node " << i+1 << ": " << externalCosts[i] << endl;
			if (externalCosts[i] > largestExternal) { //find the point with the greatest external cost
                largestExternal = externalCosts[i];
                externalIndex = i;
				cout << "New largest external cost: " << externalIndex << " with cost " << largestExternal << endl;
            }
        }
		cout << "Overall largest external cost: " << externalIndex << " with cost " << largestExternal << endl << endl;

        bool externalGroup1 = false;

        for (int i = 0; i < nodes/2; i++) {
            if (group1[i] == externalIndex + 1) {
                externalGroup1 = true;
                //externalIndex = i;
				cout << "largest external found in group 1" << endl;
            }
        }
		if(!externalGroup1) cout << "largest external found in group 2" << endl;
		cout << endl;

        int internalCost = INT_MAX; //we want to find something lower
        internalIndex = 0;

        if (externalGroup1) {
			cout << "summing internal costs for group 2" << endl;
            for (int i = 0; i < nodes/2; i++) {
                int tempInternalCost = 0;
                for (int j = 0; j < nodes/2; j++) {
                    tempInternalCost += costs[group2[i]-1][group2[j]-1];
					cout << "cost from node " << group2[i] << " to " << group2[j] << " is " << costs[group2[i]-1][group2[j]-1] << endl;
                }
                if (internalCost > tempInternalCost) {
					cout << "updating internalCost, was " << internalCost << " now is " << tempInternalCost << endl;
                    internalCost = tempInternalCost;
                    internalIndex = i;
                }
            }

        } else {
			cout << "summing internal costs for group 1" << endl;
            for (int i = 0; i < nodes/2; i++) {
                int tempInternalCost = 0;
                for (int j = 0; j < nodes/2; j++) {
                    tempInternalCost += costs[group1[i]-1][group1[j]-1];
					cout << "cost from node " << group1[i] << " to " << group1[j] << " is " << costs[group1[i]-1][group1[j]-1] << endl;
                }
                if (internalCost > tempInternalCost) {
					cout << "updating internalCost, was " << internalCost << " now is " << tempInternalCost << endl;
                    internalCost = tempInternalCost;
                    internalIndex = i;
                }
            }
        }

		cout << "Before swap, nextCost was " << nextCost << endl;
		int index1, index2;
		if(externalGroup1) { //group 1 holds the largest external point
			cout << "swapping external from group 1 to internal from group 2" << endl;
			index1 = externalIndex;
			index2 = internalIndex;
		} else {
			index1 = internalIndex;
			index2 = externalIndex;
			cout << "swapping external from group 2 to internal from group 1" << endl;
		}
		cout << "Swapping nodes t1: " << tempGroup1[index1] << " and 2: " << group2[index2] << endl;
		cout << "Swapping nodes t2: " << tempGroup2[index2] << " and 1: " << group1[index1] << endl;
		tempGroup1[index1] = group2[index2];
		tempGroup2[index2] = group1[index1];

		nextCost = 0;
        for (int i = 0; i<nodes/2; i++){
            for (int j = 0; j<nodes/2;j++) {
                nextCost += costs[tempGroup1[i] - 1][tempGroup2[j] - 1];
				//cout << "adding cost from temp1 node " << tempGroup1[i] << " to temp2 node " << tempGroup2[j] << ", which is " << costs[tempGroup1[i] - 1][tempGroup2[j] - 1] << endl;
            }
        }
		cout << "nextCost for new group is " << nextCost << endl;

		if (nextCost != -1) { //if this isn't the first loop, update cost and groups
			cout << "updating nextCost" << endl;
			prevCost = nextCost;
			cout << "prevCost is now " << prevCost << endl;
			group1[index1] = tempGroup1[index1];
			group2[index2] = tempGroup2[index2];
		}
    } //END LOWEST COST LOOP

    int finalCost = 0;
    for (int i = 0; i<nodes/2; i++){
        for (int j = 0; j< nodes/2;j++) {
            finalCost = finalCost + costs[group1[i] - 1][group2[j] - 1];
        }
    }
    //cout << endl;

    cout << finalCost << endl;
    for (int i = 0; i < nodes/2; i++){
        cout << group1[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < nodes/2; i++){
        cout << group2[i] << " ";
    }
    cout << endl << endl;

    return 0;
}