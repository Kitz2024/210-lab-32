// Kit Pollinger
// 210 - Lab 32 | Booth Toll
#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime> //Random Number Generator
#include "Car.h"

using namespace std;

// New Constants
const int NUM_LANES = 4;           // Number of toll lanes
const int MIN_CARS = 1;            // Minimum cars to populate the initial queue in each lane
const int MAX_CARS = 3;            // Maximum cars to populate the initial queue in each lane
const double CAR_LEAVES = 0.46;    // 46% chance a car leaves
const double CAR_JOINS = 0.39;     // 39% chance a car joins
const double CAR_SWITCHES = 0.15;  // 15% chance a car switches lanes
const int SIMULATION_PERIODS = 20; // Number of time periods for the simulation

/*// Define constants for the simulation
const int INITIAL_QUEUE = 2;
const double CAR_LEAVES = 0.55;  // 55% chance a car leaves
const double CAR_JOINS = 0.45;   // 45% chance a car joins
*/

int main()
{
    srand(time(0)); // Seed random number generator

    // Initialize deque with a couple of cars
    deque<Car> tollBoothQue[NUM_LANES];

    // Populate the lanes with 1-3 cars each
    for (int i = 0; i < NUM_LANES; i++) {
        int initialCars = rand() % (MAX_CARS - MIN_CARS + 1) + MIN_CARS;
        for (int j = 0; j < initialCars; j++) {
            tollBoothQue[i].push_back(Car());
        }
    }

    // Print initial queue state
    cout << "Initial queue:\n";
    for (int i = 0; i < NUM_LANES; ++i) {
        cout << "Lane " << i + 1 << ":\n";
        for (auto& car : tollBoothQue[i]) {
             cout << "\t";
            car.print();
        }
    }

    // Simulation loop
    for (int time = 1; time <= SIMULATION_PERIODS; ++time) {
        cout << "Time: " << time << "\n";

        // Process each lane
        for (int i = 0; i < NUM_LANES; ++i) {
            if (!tollBoothQue[i].empty()) {
                double randValue = static_cast<double>(rand()) / RAND_MAX;

                // Process operations based on random value
                if (randValue < CAR_LEAVES) {
                    Car paidCar = tollBoothQue[i].front();
                    tollBoothQue[i].pop_front();
                    cout << "Lane " << i + 1 << ": Paid: ";
                    paidCar.print();
                } else if (randValue < CAR_LEAVES + CAR_JOINS) {
                    Car newCar = Car();
                    tollBoothQue[i].push_back(newCar);
                    cout << "Lane " << i + 1 << ": Joined: ";
                    newCar.print();
                } else if (randValue < CAR_LEAVES + CAR_JOINS + CAR_SWITCHES) {
                    if (tollBoothQue[i].size() > 0) {
                        int newLane = rand() % NUM_LANES;
                        while (newLane == i) {
                            newLane = rand() % NUM_LANES;
                        }
                        Car carToMove = tollBoothQue[i].back();
                        tollBoothQue[i].pop_back();
                        tollBoothQue[newLane].push_back(carToMove);
                        cout << "Lane " << i + 1 << ": Switched: ";
                        carToMove.print();
                    }
                } else {
                    cout << "Lane " << i + 1 << ": No change.\n";
                }
            }
        }
        // Print Next queue state
        for (int i = 0; i < NUM_LANES; ++i) {
            cout << "Lane " << i + 1 << " Queue:\n";
            for (auto& car : tollBoothQue[i]) {
                cout << "\t";
                car.print();
            }
        }
    }
    cout << "\nFinal queue:\n";
    for (int i = 0; i < NUM_LANES; ++i) {
        cout << "Lane " << i + 1 << " Queue:\n";
        if (tollBoothQue[i].empty()) {
            cout << "Empty\n";
        } else {
            for (auto& car : tollBoothQue[i]) {
                cout << "\t";
                car.print();
            }
        }
    }
    return 0;
}
