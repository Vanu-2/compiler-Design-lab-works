#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

using namespace std;

// Global variables to represent the states of locations and the current location of the vacuum cleaner
int states[2];  // Array to store states of locations A (index 0) and B (index 1)
char location;  // Current location ('A' or 'B')

// Function to initialize the environment
void initialize() {
    // Seed the random number generator
    srand(time(0));

    // Randomly initialize the states (0: clean, 1: dirty)
    states[0] = rand() % 2;  // State of location A
    states[1] = rand() % 2;  // State of location B
    location = 'A';  // Start at location A
}

// Function to print the current state of the environment
void printState() {
    cout << "Current Location: " << location << ", State: A=" << states[0] << ", B=" << states[1] << endl;
}

// Function to clean the current location
void suck() {
    cout << "Sucking at " << location << endl;
    if (location == 'A') {
        states[0] = 0;  // Clean location A
    } else {
        states[1] = 0;  // Clean location B
    }
}

// Function to move the vacuum cleaner to location A
void moveLeft() {
    cout << "Moving Left to A" << endl;
    location = 'A';
}

// Function to move the vacuum cleaner to location B
void moveRight() {
    cout << "Moving Right to B" << endl;
    location = 'B';
}

// Function to run the vacuum cleaner simulation
void run() {
    printState();  // Print the initial state

    // Keep running until both locations are clean
    while (states[0] == 1 || states[1] == 1) {
        if (location == 'A') {
            if (states[0] == 1) {
                suck();
            } else {
                moveRight();
            }
        } else if (location == 'B') {
            if (states[1] == 1) {
                suck();
            } else {
                moveLeft();
            }
        }
        printState();  // Print the state after every action
    }

    cout << "Both locations are clean!" << endl;
}

int main() {
    initialize();  // Initialize the environment
    run();         // Run the vacuum cleaner simulation
    return 0;
}
