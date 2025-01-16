/*
 * Copyright 2023 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * Ray Lee
 * hsiangrl
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>
#include <math.h>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core

string getAIMoveString(const BuildingState& buildingState) {
    string moveString = "";
    bool isGood = true;
    
    if (buildingState.elevators[0].isServicing && buildingState.elevators[1].isServicing &&
        buildingState.elevators[2].isServicing) {
        return moveString;
    }
    
    int numPeople[NUM_FLOORS] = {0};
    for (int j = 0; j < NUM_FLOORS; j++) {
        numPeople[j] = buildingState.floors[j].numPeople;
    }
    if (numPeople[0] == 0 && numPeople[1] == 0 && numPeople[2] == 0 && numPeople[3] == 0 && numPeople[4] == 0 && numPeople[5] == 0 &&
        numPeople[6] == 0 && numPeople[7] == 0 && numPeople[8] == 0 && numPeople[9] == 0) {
        return moveString;
    }
    
    int maxPeople = numPeople[0];
    int maxPeopleFloor = 0;
    for (int i = 0; i < NUM_FLOORS; i++) {
        for (int j = 0; j < NUM_ELEVATORS; ++j) {
            if (buildingState.elevators[j].targetFloor == i) {
                isGood = false;
            }
        }
        if ((maxPeople < numPeople[i]) && isGood) {
            maxPeople = numPeople[i];
            maxPeopleFloor = i;
        }
        isGood = true;
    }
    
    if (maxPeople == 0){
        return moveString;
    }
    
    int floorNum[NUM_ELEVATORS] = {0, 0, 0};
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        floorNum[i] = abs(maxPeopleFloor - buildingState.elevators[i].currentFloor);
    }
    int minFloorNum = 10;
    int optimaizeElev = 0;
    for (int i = 0; i < NUM_ELEVATORS ; i++) {
        if (minFloorNum > floorNum[i] && !buildingState.elevators[i].isServicing) {
            minFloorNum = floorNum[i];
            optimaizeElev = i;
        }
    }
    
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        if (buildingState.elevators[i].currentFloor == buildingState.elevators[i].targetFloor && buildingState.floors[buildingState.elevators[i].targetFloor].numPeople >= maxPeople && !buildingState.elevators[i].isServicing) {
            moveString = "e" + to_string(i) + "p";
            return moveString;
        }
    }
    
    if ((maxPeopleFloor - buildingState.elevators[optimaizeElev].currentFloor) != 0 && !buildingState.elevators[optimaizeElev].isServicing) {
        moveString = "e" + to_string(optimaizeElev) + "f" + to_string(maxPeopleFloor);
       return moveString;
    }
    return moveString;
}

string getAIPickupList(const Move& move, const BuildingState& buildingState, 
                       const Floor& floorToPickup) {
    string upresult = "";
    string downresult = "";
    int upanger = 0;
    int downanger = 0;
    
    for (int i = 0; i < floorToPickup.getNumPeople(); i++) {
        if (floorToPickup.getPersonByIndex(i).getTargetFloor() > floorToPickup.getPersonByIndex(i).getCurrentFloor()) {
            upanger += floorToPickup.getPersonByIndex(i).getAngerLevel();
            upresult += to_string(i);
        }
    }
    
    for (int i = 0; i < floorToPickup.getNumPeople(); i++) {
        if (floorToPickup.getPersonByIndex(i).getTargetFloor() < floorToPickup.getPersonByIndex(i).getCurrentFloor()) {
            downanger += floorToPickup.getPersonByIndex(i).getAngerLevel();
            downresult += to_string(i);
        }
    }
    
    if (upanger >= downanger) {
        return upresult;
    }
    else {
        return downresult;
    }
}
