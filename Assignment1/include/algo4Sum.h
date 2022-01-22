//
// Created by agils on 1/18/2022.
//

#pragma once
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

class algo4Sum {
public:
    /**
     * Default Constructor
     */
    algo4Sum() {}

    /**
     * This solves the 4-sum problem via brute force
     * Cost Model: Vector/Array Accesses
     * O(n^4), contains four nested for loops, and accesses an array four times in each
     * Max Accesses: n(n-1)(n-2)(n-3)*4 = 4x^4 - 24x^3 + 44x^2 - 24x
     *
     * @param array an array of size n to be used for the 4-sum problem
     * @return int, a count of the different combinations of 4 numbers
     * in the parameter array that add to 0
     */
    int brute4Sum(int* input, int n) {
        //returns 0 if the array size is 0
        if (n == 0) {
            return 0;
        }

        //converts the array to a vector
        vector<int> array;
        for (int i = 0; i < n; i++) {
            array.push_back(input[i]);
        }

        int sumCount = 0;
        //loops through every combination of four numbers in the array
        for (int a = 0; a < n; a++) {
            for (int b = a + 1; b < n; b++) {
                for (int c = b + 1; c < n; c++) {
                    for (int d = c + 1; d < n; d++) {
                        //if all four numbers add to 0, increments sumCount
                        if (array[a] + array[b] + array[c] + array[d] == 0) {
                            sumCount++;
                        }
                    }
                }
            }
        }
        return sumCount;
    }

    /**
     * This solves the 4-sum problem via an improved method that groups vector
     * values into groups of three
     * Cost Model: Vector/Array Accesses
     *O(n^3 * log(n))
     * Max accesses: 3 * n^3 * log(n) + 2 * nlog(n) + n
     *
     * @param array an array of size n to be used for the 4-sum problem
     * @return int, a count of the different combinations of 4 numbers
     * in the parameter array that add to 0
     */
    int improved4Sum(int* input, int n) {
        //if array size is 0 returns 0
        if (n == 0) {
            return 0;
        }

        //converts the array to a vector
        vector<int> array;
        for (int i = 0; i < n; i++) {
            array.push_back(input[i]);
        }
        //sorts the array using a merge sort - O(nlog(n))
        auto sortedArray = mergeSort(array);
        int zeroSumCount = 0;
        //three for loops with a binary search at the bottom - O(n^3 * log(n))
        //(nested for loops are 3n^3, there are three array accesses,at the bottom)
        //(binary search is log(n) array accesses)
        for (int x = 0; x < n; x++) {
            for (int y = x+1; y < n; y++) {
                for (int z = y+1; z < n; z++) {
                    int threeSum = sortedArray[x] + sortedArray[y] + sortedArray[z];
                    //if the negative of threeSum is found in the binary search and is lower than z (not repeated)
                    //increments zeroSumCount
                    if (binarySearch(sortedArray, -threeSum) > z) {
                        zeroSumCount++;
                    }
                }
            }
        }
        return zeroSumCount;
    }

    /**
     * This conducts a basic binary search on a sorted vector of integers
     * Cost Model: Vector/Array Accesses
     * O(log(n))
     *
     * @param array the vector to be queried
     * @param item the value to be searched for
     * @return int index of the desired value
     */
    int binarySearch(vector<int> vec, int item) {
        int curIndex;
        //sets the lower and upper bounds of the search
        int lower = 0;
        int upper = vec.size();
        //while the upper bound is greater than or equal to the lower bound, conducts the search
        while (upper >= lower) {
            curIndex = lower + ((upper - lower) / 2);
            auto tempVal = vec[curIndex];
            if (tempVal == item) {
                return curIndex;
            }
            else if (item < tempVal) {
                upper = curIndex - 1;
            }
            else {
                lower = curIndex + 1;
            }
        }
        //if the while loop is exited without returning a value, -1 is returned
        return -1;
    }

    /**
     * This performs a recursive merge sort on a vector of integers
     * Cost Model: Vector/Array Accesses
     * O(nlog(n))
     * Max accesses: 2*nlog(n)
     *
     * @param vec vector to be sorted
     * @return vector of sorted ints
     */
    vector<int> mergeSort(vector<int> vec) {
        return mergeRecurse(vec);
    }

private:
    /**
     * This is the recursive private method for the mergeSort method
     * Cost Mode: Vector/Array Accesses
     * See above mergeSort method for Big-O
     *
     * @param vec vector/sub-vector to be sorted
     * @return vector of sorted ints
     */
    vector<int> mergeRecurse(vector<int> vec) {
        //if the size of the vector is 1 the vector is returned
        if (vec.size() == 1) {
            return vec;
        }

        //finds the midpoint of the vector
        int half = (int) (vec.size() / 2);

        //splits the vector into two vectors down the middle
        vector<int> tempBot(vec.begin(), vec.begin() + half);
        vector<int> tempTop(vec.begin() + half, vec.end());

        //performs a merge sort on the two sub-vectors
        auto botRes = mergeRecurse(tempBot);
        auto topRes = mergeRecurse(tempTop);

        vector<int> newVec;
        bool done = false;
        int bIndex = 0;
        int tIndex = 0;
        //while the current vector isn't sorted
        while (!done) {
            //special case for if one sub-vector is much larger than the other
            if (bIndex >= botRes.size() && tIndex < topRes.size()) {
                for (tIndex; tIndex < topRes.size(); tIndex++) {
                    newVec.push_back(topRes[tIndex]);
                }
                done = true;
                break;
            }
            //opposite special case
            else if (tIndex >= topRes.size() && bIndex < botRes.size()) {
                for (bIndex; bIndex < botRes.size(); bIndex++) {
                    newVec.push_back(botRes[bIndex]);
                }
                done = true;
                break;
            }
            //if both indices are greater than or equal to the vector sizes, break
            else if (tIndex >= topRes.size() && bIndex >= botRes.size()) {
                done = true;
                break;
            }
            else {
                //if the top sub-array value is lower, adds it to the new vector
                if (topRes[tIndex] < botRes[bIndex]) {
                    newVec.push_back(topRes[tIndex]);
                    tIndex++;
                }
                //if the bottom sub-array value is lower, adds it to the new vector
                else {
                    newVec.push_back(botRes[bIndex]);
                    bIndex++;
                }
            }
        }
        return newVec;
    }
};

