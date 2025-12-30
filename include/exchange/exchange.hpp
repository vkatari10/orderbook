#pragma once 

#include <vector>
#include <moodycamel/concurrentqueue.h>

#include "gateway/gateway.hpp"
#include "matching-engine/matching_engine.hpp"  

class Exchange { 
public:

    // creates object 
    Exchange();

    // setup exchange
    void init(); 

    // runs the exchange (event loop)
    void run(); 

private:

    // vector of matching engines 
    // main exchange sequencer 
    // fix gateway 
};