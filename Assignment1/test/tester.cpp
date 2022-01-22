#define CATCH_CONFIG_MAIN
#include "catch2.h"
#include "algo4Sum.h"

using namespace std;

//creates an algo4Sum object
algo4Sum testAlgo;

//test arrays with known 4-sum answers, along with their corresponding element counts
int testArray1[] = {-20, -14, -13, -12, -11, -6, -4, -3, -2, -1, 0, 1, 6, 7, 11, 13, 14, 18, 19, 20};
int n1 = 20;
int testArray2[] = {-28, -27, -24, -23, -22, -20, -19, -18, -17, -12, -9, -5, -2, 1, 3, 5, 7, 11, 12, 13, 14, 15, 16, 17, 19, 20, 21, 23, 26, 29};
int n2 = 30;
int testArray3[] = {};
int n3 = 0;
int testArray4[] = {1, 2, 3, 4, 5, 6, 7, 8};
int n4 = 8;
int testArray5[] = {-1, -2, -3, -4, -5, -6, -7, -8};
int n5 = 8;

//BRUTE FORCE TEST CASE
TEST_CASE("Brute Force 4-Sum Tests") {
	SECTION("Brute Force Array 1") {
		CHECK(testAlgo.brute4Sum(testArray1, n1) == 91);
	}
	SECTION("Brute Force Array 2") {
		CHECK(testAlgo.brute4Sum(testArray2, n2) == 306);
	}
    SECTION("Brute Force Empty Array") {
        CHECK(testAlgo.brute4Sum(testArray3, n3) == 0);
    }
    SECTION("Brute Force Positive Array") {
        CHECK(testAlgo.brute4Sum(testArray4, n4) == 0);
    }
    SECTION("Brute Force Negative Array") {
        CHECK(testAlgo.brute4Sum(testArray5, n5) == 0);
    }


}

//IMPROVED ALGORITHM TEST CASE
TEST_CASE("Improved Algorithm 4-Sum Tests") {
    //Improved Algorithm tests
    SECTION("Improved Algorithm Array 1") {
        CHECK(testAlgo.improved4Sum(testArray1, n1) == 91);
    }
    SECTION("Improved Algorithm Array 2") {
        CHECK(testAlgo.improved4Sum(testArray2, n2) == 306);
    }
    SECTION("Improved Algorithm Emtpy Array") {
        CHECK(testAlgo.improved4Sum(testArray3, n3) == 0);
    }
    SECTION("Improved Algorithm Positive Array") {
        CHECK(testAlgo.improved4Sum(testArray4, n4) == 0);
    }
    SECTION("Improved Algorithm Negative Array") {
        CHECK(testAlgo.improved4Sum(testArray5, n5) == 0);
    }
}