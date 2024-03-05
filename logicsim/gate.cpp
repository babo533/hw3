#include <vector>
#include <random>
#include <iostream>

#include "gate.h"
#include "wire.h"

Gate::Gate(int num_inputs, Wire* output) 
	: m_output(output), m_inputs(num_inputs), m_delay(0), m_current_state('X')
{
    
}

Gate::~Gate(){}

void Gate::wireInput(unsigned int id, Wire* in)
{
    if(id < m_inputs.size())
    {
        m_inputs[id] = in;
    }
}

And2Gate::And2Gate(Wire* a, Wire* b, Wire* o) : Gate(2,o)
{
    wireInput(0,a);
    wireInput(1,b);
}

Event* And2Gate::update(uint64_t current_time)
{
    
  char state = '1';
  Event* e = nullptr;
	for(auto w : m_inputs)
	{
		char in = w->getState();
		if(in == '0')
		{
			state = '0';
			break;
		}
		else if(in == 'X')
		{
			state = 'X';
		}
	}
    if(state != m_current_state)
	{
    m_current_state = state;
    uint64_t next = current_time + m_delay;
		e = new Event {next,m_output,state};
         
	}
    return e;
}

Or2Gate::Or2Gate(Wire* a, Wire* b, Wire* o) : Gate(2,o)
{
    wireInput(0,a);
    wireInput(1,b);
}

Event* Or2Gate::update(uint64_t current_time)
{
    
  char state = '0';
  Event* e = nullptr;
	for(auto w : m_inputs)
	{
		char in = w->getState();
		if(in == '1')
		{
			state = '1';
			break;
		}
		else if(in == 'X')
		{
			state = 'X';
		}
	}
  if(state != m_current_state)
	{
    m_current_state = state;
		uint64_t next = current_time + m_delay;
		e = new Event {next,m_output,state};
         
	}
  return e;
}

  NotGate::NotGate(Wire* input, Wire* output) : Gate(1, output) {
    wireInput(0, input); // Wiring the input wire
  }

  Event* NotGate::update(uint64_t current_time) {
    char state = 'X'; // Default to 'X' to represent an unknown state
    Event* e = nullptr;

    for(auto w : m_inputs) {
        char in = w->getState();

        // Implementing NOT logic 
        if(in == '0') {
            state = '1'; // Invert 0 to 1
            break; // Since there's only one input, we can break after processing
        } else if (in == '1') {
            state = '0'; // Invert 1 to 0
            break; // Since there's only one input, we can break after processing
        } else if(in == 'X') {
            state = 'X'; // If input is 'X', output remains 'X'
            break;
        }
    }

    // Check if the state has changed and create an event if so
    if (state != m_current_state) {
        m_current_state = state;
        uint64_t next = current_time + m_delay; // Calculate the time for the next event
        e = new Event{next, m_output, state};
    }

    return e; // Return the event
}

