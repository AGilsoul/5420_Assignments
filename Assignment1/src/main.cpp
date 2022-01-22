#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <memory>
#include "alg_stopwatch.h"
#include "alg_graphs.h"
#include "alg_maxsubarraysum.h"
#include "algo4Sum.h"

using namespace std;

//reads an input file of integers
vector<int> readFile(string fileName);

//main function
int main() {
    // TODO
    //creates an algo4Sum object
    algo4Sum testAlgo;

    //creates integer vectors from input files
    vector<int> ints5H = readFile("../resources/5Hints.txt");
    vector<int> ints1K = readFile("../resources/1Kints.txt");

    //converts integer vectors to integer arrays
    int array5H[ints5H.size()];
    copy(ints5H.begin(), ints5H.end(), array5H);
    int array1K[ints1K.size()];
    copy(ints1K.begin(), ints1K.end(), array1K);

    //solves the 4-sum problem on 500 integers with both algorithms
    cout << "Solving 4-Sum problem with 500 integers..." << endl;
    StopWatch watch;
    int bruteValue500 = testAlgo.brute4Sum(array5H, ints5H.size());
    double bruteTime500 = watch.elapsed_time();
    watch.reset();
    int improvedValue500 = testAlgo.improved4Sum(array5H, ints5H.size());
    double improvedTime500 = watch.elapsed_time();
    cout << "Done!" << endl << endl;

    //solves the 4-sum problem on 1000 integers with both algorithms
    cout << "Solving 4-Sum problem with 1000 integers..." << endl;
    watch.reset();
    auto bruteValue1000 = testAlgo.brute4Sum(array1K, ints1K.size());
    auto bruteTime1000 = watch.elapsed_time();
    watch.reset();
    auto improvedValue1000 = testAlgo.improved4Sum(array1K, ints1K.size());
    auto improvedTime1000 = watch.elapsed_time();
    cout << "Done!" << endl << endl;

    //prints the results to the console in a table format
    cout << "4-Sum Problem Time Comparison" << endl;
    cout << "+--------------------+--------------------+--------------------+" << endl;
    cout << "|" << setw(21) << "|" << left << setw(20) << "Brute-Force" << "|" << left << setw(20) << "Improved Algo" << "|" << endl;
    cout << "+--------------------+--------------------+--------------------+" << endl;
    cout << "|" << left << setw(20) << "Solution (500 ints)" << "|" << left << setw(20) << bruteValue500 << "|" << left << setw(20) << improvedValue500 << "|" << endl;
    cout << "+--------------------+--------------------+--------------------+" << endl;
    cout << "|" << left << setw(20) << "Time (500 ints)" << "|" << left << setw(20) << bruteTime500 << "|" << left << setw(20) << improvedTime500 << "|" << endl;
    cout << "+--------------------+--------------------+--------------------+" << endl;
    cout << "|" << left << setw(20) << "Solution (1000 ints)" << "|" << left << setw(20) << bruteValue1000 << "|" << left << setw(20) << improvedValue1000 << "|" << endl;
    cout << "+--------------------+--------------------+--------------------+" << endl;
    cout << "|" << left << setw(20) << "Time (1000 ints)" << "|" << left << setw(20) << bruteTime1000 << "|" << left << setw(20) << improvedTime1000 << "|" << endl;
    cout << "+--------------------+--------------------+--------------------+" << endl;


    //Below is the code for testing the Max Subarray Sum Problem Algorithms
    //creates the necessary objects for random integers
    default_random_engine rng;
    mt19937 mt(rng());
    //creates a random int distribution between -1000 and 1000
    uniform_int_distribution<int> dist(-1000, 1000);
    //sets the initial array size to 10
    int sizeCount = 10;

    //creates a vector of MaxSubarraySum objects, one for each random array
    vector<MaxSubarraySum> randArrayAlgos;
    //creates a vector of random arrays, this is referenced later for console output
    vector<vector<int>> arrays;
    //for every desired array
    for (int i = 0; i < 15; i++) {
        vector<int> tempArray;
        //creates the necessary amount of random numbers
        for (int j = 0; j < sizeCount; j++) {
            tempArray.push_back(dist(mt));
        }
        MaxSubarraySum tempAlgo(tempArray);
        randArrayAlgos.push_back(tempAlgo);
        arrays.push_back(tempArray);
        //increments the random array size by 150%
        sizeCount *= 1.5;
    }

    cout << endl << endl << "Running Max Subarray Sum Problem Algorithms..." << endl;
    //vector for storing runtime results
    vector<double> allRunTimes;
    //StopWatch object for recording runtime
    StopWatch arrayWatch;
    //for every array, runs each of the four algorithms and records the time of each
    for (int i = 0; i < 15; i++) {
        arrayWatch.reset();
        randArrayAlgos[i].cubic_alg();
        allRunTimes.push_back(arrayWatch.elapsed_time());
        arrayWatch.reset();
        randArrayAlgos[i].quadratic_alg();
        allRunTimes.push_back(arrayWatch.elapsed_time());
        arrayWatch.reset();
        randArrayAlgos[i].linearithmic_alg();
        allRunTimes.push_back(arrayWatch.elapsed_time());
        arrayWatch.reset();
        randArrayAlgos[i].linear_alg();
        allRunTimes.push_back(arrayWatch.elapsed_time());
        arrayWatch.reset();
    }
    cout << "Done!" << endl << endl;

    //prints the results to the console
    cout << "Max Subarray Sum Problem Time Comparison" << endl;
    cout << "+------------------------------+--------------------+--------------------+--------------------+--------------------+" << endl;
    cout << "|" << right << setw(31) << "|" << left << setw(20) << "Cubic" << "|" << left << setw(20) << "Quadratic" << "|" << left << setw(20) << "Linearithmetic" << "|" << left << setw(20) << "Linear" << "|"<< endl;
    cout << "+------------------------------+--------------------+--------------------+--------------------+--------------------+" << endl;
    for (int i = 0; i < 60; i += 4) {
        string countString = "Array " + to_string((i+1) / 4) + " time (size: " + to_string(arrays[(i+1)/4].size()) + ")";
        cout << "|" << left << setw(30) << countString << "|" << left << setw(20) << allRunTimes[i] << "|" << left << setw(20) << allRunTimes[i+1] << "|" << left << setw(20) << allRunTimes[i+2] << "|" << left << setw(20) << allRunTimes[i+3] << "|"<< endl;
        cout << "+------------------------------+--------------------+--------------------+--------------------+--------------------+" << endl;
    }
    return 0;
}

//reads an input file of integers
vector<int> readFile(string fileName) {
    //vector of all integers being read
    vector<int> nums;
    //placeholder string for getline function
    string curLine;
    ifstream myFile(fileName);
    if (myFile.is_open()) {
        //reads every line
        while (!myFile.eof()) {
            getline(myFile, curLine);
            if (curLine != "") nums.push_back(stoi(curLine));
        }
    }
    myFile.close();
    return nums;
}
