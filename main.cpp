#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

void runOnFile(string filename);
void verifyOutput(string inputfile, string outputfile);

#define PATH "/home/jadelclemens/Downloads/"

int main() {
	/*
	 * NEW PROGRAM STRUCTURE:
	 *
	 * First, make sure PATH points to the directory where the input/output files are stored. For convenience, I've pointed this at my Downloads
	 * Put the numeric identifiers for all of the tests to run in toRun:
	 * - Put them before the runOnFile block to run the given input files and generate a (suboptimal, but hopefully valid) grouping
	 * - Put them before the verifyOutput block to check the given output files for validity against our input file
	 * The actual filenames (as downloaded from the AlgoBOWL site) will be constructed for you based on the team numbers.
	 */

	//No need to change these
	string ifbegin = "input_group";
	string ifend = ".txt";
	string filename;

	//ALGOBOWL SOLUTION
	vector<int> toRun = {};
	vector<int> runLater = {18};
	vector<int> ran = {1, 2, 4, 6, 8, 9, 10, 12, 14, 17, 21, 22, 23, 25};

	for(int num : toRun) {
		filename = ifbegin + to_string(num) + ifend;
		runOnFile(filename);
	}

	//INPUT VERIFICATION
	//No need to change these
	string ourfile = "input_group11.txt";
	ifbegin = "output_from_";
	ifend = "_to_11.txt";

	toRun = {1};

	for(int num : toRun) {
		filename = ifbegin + to_string(num) + ifend;
		verifyOutput(ourfile, filename);
	}

    return 0;
}

void runOnFile(string filename) {
	int nodes, edges;
	string outname = filename + ".out";
	ofstream outfile(outname);

	ifstream inFile(PATH + filename);

	if (!inFile) {
		cout << "Unable to open file " << PATH + filename << endl;
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

	//for (int i = 0; i < nodes/2; i++){
	/*for(int j = 0; j < N; j++){
		cout << costs[i][j] << " ";
	}*/
	//cout << group1[i]<< " " << group2[i] << endl;

	//}

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
	cout << "prevCost is " << prevCost << endl << endl;

	int nextCost = -1;
	int externalIndex;
	int internalIndex;
	int index1;
	int index2;

	//LOOP TO FIND LOWEST COST
	while (prevCost>nextCost) { //while we can still find a lower cost
		if(nextCost != -1) { //if this isn't the first loop, update cost and groups
			cout << "updating nextCost" << endl;
			prevCost = nextCost;
			cout << "prevCost is now " << prevCost << endl;
			group1[index1] = tempGroup1[index1];
			group2[index2] = tempGroup2[index2];
		}
		index1 = index2 = 0; //probably not necessary?

		int externalCosts[nodes];
		//Calculate external costs for all nodes
		for(int i = 0; i < nodes; ++i) {
			//cout << "i = " << i << endl;
			externalCosts[i] = 0;

			if(i < nodes / 2) { //we're in group 1: compare to all group 2
				//cout << "in group 1" << endl;
				for(int j = 0; j < nodes / 2; ++j) {
					externalCosts[i] += costs[group1[i] - 1][group2[j] - 1];
					//cout << "added " << costs[group1[i] - 1][group2[j] - 1]
					//	 << " to externalCosts, which is the cost from"
					//	 << group1[i] << " to " << group2[j] << endl;
				}
			} else {
				//cout << "in group 2 " << endl;
				for(int j = 0; j < nodes / 2; ++j) {
					externalCosts[i] += costs[group2[i % (nodes / 2)] - 1][group1[j] - 1];
					//cout << "added " << costs[group2[i % (nodes / 2)] - 1][group1[j] - 1]
					//	 << " to externalCosts, which is the cost from "
					//	 << group2[i % (nodes / 2)] << " to " << group1[j] << endl;
				}
			}

			/*
			for(int k = 0; k < nodes; ++k) {
				cout << "External cost for node " << k + 1 << ": " << externalCosts[k] << endl;
			}
			 */
		}

		externalIndex = 0;
		int largestExternal = INT_MIN;
		for(int i = 0; i < nodes; ++i) {
			if(externalCosts[i] > largestExternal) { //find the point with the greatest external cost
				largestExternal = externalCosts[i];
				externalIndex = i;
				//cout << "New largest external cost: " << externalIndex << " with cost " << largestExternal << endl;
			}
		}
		cout << "Overall largest external cost: " << externalIndex << " with cost " << largestExternal << endl << endl;

		bool externalGroup1 = false;
		for(int i = 0; i < nodes / 2; i++) {
			if(group1[i] == externalIndex + 1) {
				externalGroup1 = true;
				//externalIndex = i;
				//cout << "largest external found in group 1" << endl;
			}
		}
		//if(!externalGroup1) cout << "largest external found in group 2" << endl;
		cout << endl;

		int lowestInternal = INT_MAX; //we want to find something lower
		internalIndex = 0;
		int internalCosts[nodes/2];

		if(externalGroup1) {
			//cout << "summing internal costs for group 2" << endl;
			for(int i = 0; i < nodes / 2; i++) {
				int tempInternalCost = 0;
				for(int j = 0; j < nodes / 2; j++) {
					tempInternalCost += costs[group2[i] - 1][group2[j] - 1];
					//cout << "cost from node " << group2[i] << " to " << group2[j] << " is "
					//     << costs[group2[i] - 1][group2[j] - 1] << endl;
				}
				internalCosts[i] = tempInternalCost;
				if(lowestInternal > tempInternalCost) {
					//cout << "updating lowestInternal, was " << lowestInternal << " now is " << tempInternalCost << endl;
					lowestInternal = tempInternalCost;
					internalIndex = i;
				}
			}

		} else {
			//cout << "summing internal costs for group 1" << endl;
			for(int i = 0; i < nodes / 2; i++) {
				int tempInternalCost = 0;
				for(int j = 0; j < nodes / 2; j++) {
					tempInternalCost += costs[group1[i] - 1][group1[j] - 1];
					//cout << "cost from node " << group1[i] << " to " << group1[j] << " is "
					//	 << costs[group1[i] - 1][group1[j] - 1] << endl;
				}
				internalCosts[i] = tempInternalCost;
			}
		}

		/*for(int k = 0; k < nodes/2; ++k) {
			cout << "internal cost for node " << k+1 << " is " << internalCosts[k] << endl;
		}
		cout << endl << endl;*/

		vector<int> swapped; //will hold indices of the second group that have been attempted
		while(swapped.size() < nodes/2 && (nextCost > prevCost || nextCost == -1)) { //Loop through possibilities until we've tried everything (swapped holds all members of group) or we find a better cost
			for(int k = 0; k < nodes/2; ++k) { //reset temp groups if swap was not actually made
				tempGroup1[k] = group1[k];
				tempGroup2[k] = group2[k];
			}

			cout << "attempted swaps: ";
			for(int swap : swapped) cout << swap << " ";
			cout << endl;
			cout << "Before swap, nextCost was " << nextCost << endl;
			lowestInternal = INT_MAX;
			for(int j = 0; j < nodes/2; ++j) {
				if(find(swapped.begin(), swapped.end(), j) != swapped.end()) {
					//cout << "attempted to use " << j << ", which was already tried" << endl;
					continue; //we've already tried this index
				} else {
					//cout << "index " << j << " not found in swapped list " << endl;
				}
				if(lowestInternal > internalCosts[j]) {
					//cout << "updating lowestInternal, was " << lowestInternal << " now is " << internalCosts[j] << endl;
					lowestInternal = internalCosts[j];
					internalIndex = j;
				}
			}

			//cout << "adding " << internalIndex << " to list of attempted swaps " << endl;
			swapped.push_back(internalIndex);

			if(externalGroup1) { //group 1 holds the largest external point
				//cout << "swapping external from group 1 to internal from group 2" << endl;
				index1 = externalIndex;
				index2 = internalIndex;
			} else {
				//cout << "swapping external from group 2 to internal from group 1" << endl;
				index1 = internalIndex;
				index2 = externalIndex;
			}
			cout << "Swapping nodes t1: " << tempGroup1[index1] << " and 2: " << group2[index2] << endl;
			cout << "Swapping nodes t2: " << tempGroup2[index2] << " and 1: " << group1[index1] << endl;
			tempGroup1[index1] = group2[index2];
			tempGroup2[index2] = group1[index1];

			nextCost = 0;
			for(int i = 0; i < nodes / 2; i++) {
				for(int j = 0; j < nodes / 2; j++) {
					nextCost += costs[tempGroup1[i] - 1][tempGroup2[j] - 1];
					//cout << "adding cost from temp1 node " << tempGroup1[i] << " to temp2 node " << tempGroup2[j] << ", which is " << costs[tempGroup1[i] - 1][tempGroup2[j] - 1] << endl;
				}
			}
			cout << "nextCost for new group is " << nextCost << endl;
		}
	} //END LOWEST COST LOOP
	cout << endl << endl;

	int finalCost = 0;
	for (int i = 0; i<nodes/2; i++){
		for (int j = 0; j< nodes/2;j++) {
			finalCost = finalCost + costs[group1[i] - 1][group2[j] - 1];
		}
	}
	//cout << endl;

	cout << finalCost << endl;
	outfile << finalCost << endl;
	for (int i = 0; i < nodes/2; i++){
		cout << group1[i] << " ";
		outfile << group1[i] << " ";
	}
	cout << endl;
	outfile << endl;
	for(int i = 0; i < nodes/2; i++){
		cout << group2[i] << " ";
		outfile << group2[i] << " ";
	}
	cout << endl << endl;
}

void verifyOutput(string inputfile, string outputfile) {
	cout << "verifying output for input " << inputfile << " held in file " << outputfile << endl << endl;
	int nodes, edges;
	ifstream inFile(PATH + inputfile);
	ifstream oFile(PATH + outputfile);

	if (!inFile) {
		cout << "Unable to open file " << PATH + inputfile << endl;
		exit(1);   // call system to stop
	}
	if(!oFile) {
		cout << "Unable to open file " << PATH + outputfile << endl;
		exit(1);
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

	int score;
	vector<int> group1, group2;
	ostringstream next;
	string nextLine;
	oFile >> score;
	oFile.ignore();
	bool g1 = true;
	while(!oFile.eof()) {
		next.clear();
		getline(oFile, nextLine);
		if(!nextLine.empty()) {
			string::size_type spacePos = 0;
			auto lastPos = spacePos;
			while((spacePos = nextLine.find(' ', lastPos)) != nextLine.npos) {
				if(g1) {
					group1.emplace_back(stoi(nextLine.substr(lastPos, spacePos-lastPos)));
				} else {
					group2.emplace_back(stoi(nextLine.substr(lastPos, spacePos-lastPos)));
				}
				lastPos = spacePos + 1;
			}
			g1 = false;
		}
		//next << nextLine;
		//cout << next.str() << endl;
	}

	/* OUTPUT TEAM'S SCORE AND GROUPINGS
	cout << "cost: " << score << endl;
	cout << "Group 1: "<< endl;
	for(auto m : group1) {
		cout << m << " ";
	}

	cout << endl << "Group 2: " << endl;
	for(auto m : group2) {
		cout << m << " ";
	}
	cout << endl;
	*/

	int foundCost = 0;
	for(auto node1 : group1) {
		for(auto node2 : group2) {
			foundCost += costs[node1-1][node2-1];
		}
	}

	cout << "Output file " << outputfile << " is ";
	if(foundCost != score) cout << "not ";
	cout << "valid." << endl;
}