# command-encoder-decoder

Use your own commands to communicate with other hardware!.

With this library, you can use your own commands to communicate between different hardware devices in order to perform one or more operations.

To see how to use this library, refer to the test file.

I utilized this library along with pyserial to establish communication between Python and Arduino.


__Example:__


~~~


#include <iostream> 
#include <vector> 

// include cmded header file
#include "cmded.hpp"

// g++ test.cpp cmded.cpp -o cmded.exe
// ./cmded.exe

using namespace std; 
using namespace ced; 

// base commands vector
vector<vector<string> > myCommands = {{"out", "in", "pwm", "adc"}, {".0", ".1", ".2", ".3", ".4", ".5",".6",
																  ".7", ".8", ".9",".10", ".11", ".12", ".13",
																  ".14", ".15", ".16", ".17", ".18", ".19"}};

// index of commands vector used to encode
vector<int> ec = {0, 6};

// numbers vector used to encode
vector<int> en = {120, 360, 96};

// Create an object of the CED class and pass the base commands vector to it as a constructor parameter
CED test(myCommands);

int main() {

	// decode "adc .7 = 1024"
	test.decode("adc .7 = 1024  2th");

	// encode en and ec vectors, return: "out .6 = 120 360 96"
	cout << test.encode(ec, en) << endl;

	// get number of elements in first vector of the base commands, return: 4
	cout << test.getCmdSize(0) << endl;

	// get number of elements in second vector of the base commands, return: 20
	cout << test.getCmdSize(1) << endl;

	// Get the number of decoded commands, return: 2
	cout << test.cmdAvailable() << endl;

	// Get the number of given numbers, return: 2
	cout << test.numAvailable() << endl;
	
	// get the index of first given command, return: 3 
    cout << test.getCmd(0) << endl;

	// get the index of second given command, return: 7 
	cout << test.getCmd(1) << endl;

	// get the first given number, return: 1024 
	cout << test.getNum(0) << endl;

	// get the second given number, return: ced :: NAN
	cout << test.getNum(1) << endl;

	// get the third given number, return: ced :: NP
	cout << test.getNum(2);

    return 0;
}

