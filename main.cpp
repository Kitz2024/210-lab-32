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

    // Populate the initial queue with cars
    for (int i = 0; i < NUM_LANES; i++)
    {
        int initialCars = rand() % (MAX_CARS - MIN_CARS + 1) + MIN_CARS;
        for (int j = 0; j < initialCars; j++)
        {
            tollBoothQue[i].push_back(Car());
        }
    }

    // initial queue
    cout << "Initial queue:\n";
    for (int i = 0; i < NUM_LANES; i++)
    {
        cout << "Lane " << i + 1 << ":\n";
        if (tollBoothQue[i].empty())
        {
            cout << "    empty\n";
        }
        else
        {
            for (auto &car : tollBoothQue[i])
            {
                car.print();
            }
        }
        cout << "\n";
    }

    // Time counter
    int time = 1;

    // Simulation loop for 20 time periods
    while (time <= SIMULATION_PERIODS)
    {
        cout << "\nTime: " << time << "\n";

        // Initialize a string to capture the operation message for each lane
        string operations[NUM_LANES];

        // For each lane, perform one operation
        for (int i = 0; i < NUM_LANES; i++)
        {
            if (!tollBoothQue[i].empty())
            {
                double randValue = static_cast<double>(rand()) / RAND_MAX;

                // Check operation type based on random value
                if (randValue < CAR_LEAVES)
                {
                    // Car at the front of the queue pays and leaves
                    Car paidCar = tollBoothQue[i].front();
                    tollBoothQue[i].pop_front();
                    operations[i] = "Paid: ";
                    paidCar.print(); // Print the paid car's details directly
                }
                else if (randValue < CAR_LEAVES + CAR_JOINS)
                {
                    // A new car joins the queue
                    Car newCar = Car();
                    tollBoothQue[i].push_back(newCar);
                    operations[i] = "Joined: ";
                    newCar.print(); // Print the new car's details directly
                }
                else if (randValue < CAR_LEAVES + CAR_JOINS + CAR_SWITCHES)
                {
                    // A car switches lanes
                    if (tollBoothQue[i].size() > 0)
                    {
                        // Randomly pick a lane that is not the current one
                        int newLane = rand() % NUM_LANES;
                        while (newLane == i)
                        {
                            newLane = rand() % NUM_LANES;
                        }

                        // Move the car from the rear of the current lane to the new lane
                        Car carToMove = tollBoothQue[i].back();
                        tollBoothQue[i].pop_back();
                        tollBoothQue[newLane].push_back(carToMove);
                        operations[i] = "Switched: ";
                        carToMove.print(); // Print the switched car's details directly
                    }
                }
                else
                {
                    operations[i] = "No change.";
                }
            }
        }
        for (int i = 0; i < NUM_LANES; i++)
        {
            cout << "Lane " << i + 1 << ": " << operations[i] << "\n";
        }

        // Print the updated queue status for each lane
        for (int i = 0; i < NUM_LANES; i++)
        {
            cout << "Lane " << i + 1 << " Queue: ";
            if (tollBoothQue[i].empty())
            {
                cout << "empty\n";
            }
            else
            {
                cout << "\n";
                for (auto &car : tollBoothQue[i])
                {
                    // Use print() to display each car's details
                    car.print(); 
                }
            }
        }
        time++;
    }

    // queue is empty
    cout << "\nQueue:\nEmpty\n";
    return 0;
}
