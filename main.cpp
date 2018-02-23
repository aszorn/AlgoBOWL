#include <iostream>
#include <fstream>

using namespace std;

int main() {

    int N,V;
    ifstream inFile;
    inFile.open("points.txt");

    if (!inFile) {
        cout << "Unable to open file points.txt";
        exit(1);   // call system to stop
    }

    inFile >> N >> V; //stores the first row which is the number of points and edges

    int costs[N][N]; //creates a matrix of zeros
    int pt1;
    int pt2;
    int cost;

    for (int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            costs[i][j] = 0;
        }
    }

    while(inFile>>pt1>>pt2>>cost){
        pt1--;
        pt2--;
        costs[pt1][pt2]=cost;
        costs[pt2][pt1]=cost;
    }

    inFile.close();

    //cout << N/2 << endl << endl;
    int group1[N/2];
    int group2[N/2];

    int tempGroup1[N/2];
    int tempGroup2[N/2];


    for (int i = 0; i<N;i++){
        if(i < N/2){
            group1[i] = i+1;
            tempGroup1[i] = i+1;
        }
        else{
            group2[i - N/2] = i+1;
            tempGroup2[i-N/2] = i+1;
        }
    }

    for (int i = 0; i < N/2; i++){
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
    for (int i = 0; i< N/2; i++){
        for (int j = 0; j< N/2; j++) {
            int tempG1Cost = group1[i]-1;
            int tempG2Cost = group2[j]-1;
            //cout << tempG1Cost << " " << tempG2Cost << endl;
            prevCost = prevCost + costs[tempG1Cost][tempG2Cost];
            //cout << prevCost << endl;
        }
    }


    int nextCost = -1;
    int externalPoint;
    int internalPoint;

    while (prevCost>nextCost) {
        if (nextCost != -1){
            prevCost = nextCost;
            group1[externalPoint] = tempGroup1[externalPoint];
            group2[internalPoint] = tempGroup2[internalPoint];
        }

        int externalCost = 0;
        externalPoint = 0;

        for (int i = 0; i < N; i++) {
            int tempCost = 0;
            for (int j = 0; j < N; j++) {
                tempCost = tempCost + costs[i][j];
            }
            if (externalCost < tempCost) {
                externalCost = tempCost;
                externalPoint = i+1;
            }
        }

        bool externalGroup1 = false;

        for (int i = 0; i < N/2; i++) {
            if (group1[i] == externalPoint) {
                externalGroup1 = true;
                externalPoint = i;
            }
        }

        int internalCost = -1;
        internalPoint = 0;

        if (externalGroup1) {
            for (int i = 0; i < N/2; i++) {
                int tempCost = 0;
                for (int j = 0; j < N/2; j++) {
                    tempCost = tempCost + costs[group2[i]-1][group2[j]-1];
                }
                if (internalCost > tempCost || internalCost == -1) {
                    internalCost = tempCost;
                    internalPoint = i;
                }
            }

        } else {
            for (int i = 0; i < N/2; i++) {
                int tempCost = 0;
                for (int j = 0; j < N/2; j++) {
                    tempCost = tempCost + costs[group1[i]-1][group1[j]-1];
                }
                if (internalCost > tempCost || internalCost == -1) {
                    internalCost = tempCost;
                    internalPoint = i + 1;
                }
            }

            for (int i = 0; i < N/2; i++) {
                if (group2[i] == externalPoint) {
                    externalPoint = i;
                }
            }
        }
        tempGroup1[externalPoint] = group2[internalPoint];
        tempGroup2[internalPoint] = group1[externalPoint];

        for (int i = 0; i<N/2; i++){
            for (int j = 0; j<N/2;j++) {
                nextCost = nextCost + costs[tempGroup1[i] - 1][tempGroup2[j] - 1];
            }
        }
    }

    int finalCost;

    for (int i = 0; i<N/2; i++){
        for (int j = 0; j< N/2;j++) {
            finalCost = finalCost + costs[group1[i] - 1][group2[j] - 1];
        }
    }
    //cout << endl;

    cout << finalCost << endl;
    for (int i = 0; i < N/2; i++){
        cout << group1[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < N/2; i++){
        cout << group2[i] << " ";
    }
    cout << endl << endl;

    return 0;
}