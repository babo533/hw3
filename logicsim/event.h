#ifndef EVENT_H
#define EVENT_H
#include "wire.h"

struct Event
{
    uint64_t time;
    Wire* wire;
    char state;
};

typedef struct EventLess {
        //write the operator() required to make this a functor that compares Events by time
    bool operator() (Event* eventInputOne, Event* eventInputTwo) const {
        // Compare the time of two events pointed to by the input pointers.
        if ((eventInputOne->time) < (eventInputTwo->time)) {
            return true;
        } 
        else {
            return false;
        }
    }
} EventLess;
	
#endif
