#ifndef INCLUDE_STATE_MACHINE_H_
#define INCLUDE_STATE_MACHINE_H_

#include <vector>
#include <string>

#include "include/structures.h"
#include "include/contexts_factory.h"

class StateMachine {
 public:
  StateMachine(int n_states = 0);

  ~StateMachine();

  void Init(int n_states);

  void InitContexts();

  void Clear();

  void AddTransition(unsigned from_id, unsigned to_id, int event_id);

  void DelTransition(unsigned id);

  void DelState(unsigned id);

  State* GetState(int id) const;

  int GetNumberStates() const;

  int GetNumberTransitions() const;

  bool IsRecognized(const std::vector<int>& word) const;

  bool FindContext(std::vector<int>& first_substr,
                   std::vector<int>& second_substr, bool& has_kernels) const;

  void WriteDot(const std::string& file_path,
                const std::vector<std::string>& states_names,
                const std::vector<std::string>& events_names) const;

  void WriteConfig(std::ofstream& s) const;

 private:
  std::vector<State*> states_;
  std::vector<Transition*> transitions_;
  ContextsFactory* contexts_factory_;
};

#endif  // INCLUDE_STATE_MACHINE_H_
