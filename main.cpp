// Kit Pollinger
// 210 - Lab 32 | Booth Toll
#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime>
#include "Car.h"

using namespace std;

// Define constants for the simulation
const int INITIAL_QUEUE = 2;
const double CAR_LEAVES = 0.55;  // 55% chance a car leaves
const double CAR_JOINS = 0.45;   // 45% chance a car joins

int main() {
    srand(time(0)); // Seed random number generator

    // Initialize deque with a couple of cars
    deque<Car> tollBoothQue;

    // Populate the initial queue with cars
    for (int i = 0; i < INITIAL_QUEUE; i++) {
        tollBoothQue.push_back(Car());
    }

    // initial queue
    cout << "Initial queue:\n";
    for (auto& car : tollBoothQue) {
        car.print();
    }

    // Ensure we have cars in the queue
    if (tollBoothQue.empty()) {
        cout << "Error: The initial queue is empty!" << endl;
        return 1;
    }

    // Time counter
    int time = 1;

    //simulation
    while (!tollBoothQue.empty()) {
        // Displaycurrent state of the queue
        cout << "\nTime: " << time << " ";

        double randValue = static_cast<double>(rand()) / RAND_MAX;
        cout << "Operation: " << randValue << " | ";  // check random values

        // Check probabilities and display corresponding output
        if (randValue < CAR_LEAVES) {
            // A car at the front of the queue pays and leaves
            Car paidCar = tollBoothQue.front();
            tollBoothQue.pop_front();
            cout << "Operation: Car paid: ";
            paidCar.print();
        } else if (randValue < CAR_LEAVES + CAR_JOINS) {
            // A new car joins the queue
            Car newCar = Car();
            tollBoothQue.push_back(newCar);
            cout << "Operation: Joined lane: ";
            newCar.print();
        } else {
            cout << "Operation: No change (Random value doesn't meet the condition).";
        }

        // Display the updated queue after the operation
        cout << "\nQueue:\n";
        if (tollBoothQue.empty()) {
            cout << "Empty\n";
        } else {
            for (auto& car : tollBoothQue){
                car.print();
            }
        }

        time++;
    }

    //queue is empty
    cout << "\nQueue:\nEmpty\n";
    return 0;
}
