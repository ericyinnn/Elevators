/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Person.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * Final Project - Elevators
 */

#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

Person::Person(string inputString) : Person() {
    //turn = inputString.at(0);
    //currentFloor = inputString.at(2);
    //targetFloor = inputString.at(4);
    //angerLevel = inputString.at(6);
    char f;
    stringstream ss(inputString);
    ss >> turn;
    ss >> f;
    ss >> currentFloor;
    ss >> f;
    ss >> targetFloor;
    ss >> f;
    ss >> angerLevel;
}

bool Person::tick(int currentTime) {
    if (currentTime % TICKS_PER_ANGER_INCREASE == 0) {
        angerLevel += 1;
    }
    if (angerLevel == MAX_ANGER) {
        return true;
    }
    else {
        return false;
    }
}

void Person::print(ostream &outs) {    
    outs << "f" << currentFloor <<  "t" << targetFloor << "a" << angerLevel;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Person::Person() {
    turn = 0;
    currentFloor = 0;
    targetFloor = 0;
    angerLevel = 0;
}

int Person::getTurn() const {
    return turn;
}

int Person::getCurrentFloor() const {    
    return currentFloor;
}

int Person::getTargetFloor() const {    
    return targetFloor;
}

int Person::getAngerLevel() const {    
    return angerLevel;
}

ostream& operator<< (ostream& outs, Person p)
{
    p.print(outs);
    return outs;
}
