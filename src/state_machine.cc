#include "include/state_machine.h"

#include <fstream>
#include <iostream>

StateMachine::StateMachine(int n_states) {
  n_states_ = 0;
  n_transitions_ = 0;
  if (n_states != 0) {
    AddStates(n_states);
  }
}

StateMachine::~StateMachine() {
  Clear();
}

void StateMachine::Clear() {
  int n_states = states_.size();
  for (int i = 0; i < n_states; ++i) {
    delete states_[i];
  }
  states_.clear();
  n_states_ = 0;

  int n_trans = transitions_.size();
  for (int i = 0; i < n_trans; ++i) {
    delete transitions_[i];
  }
  transitions_.clear();
  n_transitions_ = 0;
}

void StateMachine::AddStates(int n_states) {
  for (int i = 0; i < n_states; ++i) {
    states_.push_back(new State(i));
  }
  n_states_ += n_states;
}

void StateMachine::AddTransition(unsigned from_id, unsigned to_id,
                                 unsigned event_id) {
  Transition* trans = new Transition(transitions_.size(),
                                     states_[from_id],
                                     states_[to_id],
                                     event_id);
  transitions_.push_back(trans);
  ++n_transitions_;
}

void StateMachine::DelTransition(unsigned id) {
  Transition* trans = transitions_[id];
  trans->from->DelTransitionFrom(id);
  trans->to->DelTransitionTo(id);
  delete trans;
  transitions_[id] = 0;
  --n_transitions_;
}

void StateMachine::DelState(unsigned id) {
  State* state = states_[id];
  std::vector<int> ids;
  for (int i = 0; i < state->transitions_from.size(); ++i) {
    ids.push_back(state->transitions_from[i]->id);
  }
  for (int i = 0; i < state->transitions_to.size(); ++i) {
    ids.push_back(state->transitions_to[i]->id);
  }
  for (int i = 0; i < ids.size(); ++i) {
    DelTransition(ids[i]);
  }
  --n_states_;
  delete state;
  states_[id] = 0;
}

State* StateMachine::GetStartState() const {
  return states_[0];
}

State* StateMachine::GetEndState() const {
  return states_.back();
}

State* StateMachine::GetState(int id) const {
  return states_[id];
}

int StateMachine::GetNumberStates() const {
  return n_states_;
}

int StateMachine::GetNumberTransitions() const {
  return n_transitions_;
}

void StateMachine::WriteDot(const std::string& file_path,
                           const std::vector<std::string>& states_names,
                           const std::vector<std::string>& events_names) const {
  std::ofstream file(file_path.c_str());
  file << "strict digraph state_machine {\n";

  const int n_states = states_.size();
  std::string edges[n_states][n_states];
  for (int i = 0; i < n_states; ++i) {
    for (int j = 0; j < n_states; ++j) {
      edges[i][j] = "";
    }
  }

  for (int i = 0; i < n_states; ++i) {
    State* state = states_[i];
    if (state != 0) {
      std::string state_from_name = states_names[i];

      const int n_trans = state->transitions_from.size();
      for (int j = 0; j < n_trans; ++j) {
        Transition* trans = state->transitions_from[j];
        const int state_to_id = trans->to->id;
        std::string state_to_name = states_names[state_to_id];
        std::string event_name = events_names[trans->event_id];

        if (edges[i][state_to_id] != "") {
          edges[i][state_to_id] += ", " + event_name;
        } else {
          edges[i][state_to_id] = event_name;
        }

        file << state_from_name << "->" << state_to_name
             << "[label=\"" <<  edges[i][state_to_id] << "\"];\n";
      }
    }
  }

  file << "}";
  file.close();
}
