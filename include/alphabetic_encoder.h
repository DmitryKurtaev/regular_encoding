// Copyright © 2016 Dmitry Kurtaev. All rights reserved.
// License: MIT License (see LICENSE)
// e-mail: dmitry.kurtaev@gmail.com

#ifndef INCLUDE_ALPHABETIC_ENCODER_H_
#define INCLUDE_ALPHABETIC_ENCODER_H_

#include <vector>
#include <string>

#include "include/state_machine.h"
#include "include/bijective_checker.h"

class AlphabeticEncoder {
 public:
  explicit AlphabeticEncoder(const std::string& config_file);

  bool CheckBijective();

  void WriteCodeStateMachine(const std::string& file_path) const;

  void WriteDeficitsStateMachine(const std::string& file_path);

  void WriteSynonymyStateMachine(const std::string& file_path);

  static void WriteCodeStateMachine(const std::string& file_path,
                                    const std::vector<std::string>& code,
                                    const StateMachine& state_machine);

  static void WriteConfigFile(const std::string& file_path,
                              const std::vector<std::string>& code,
                              const StateMachine& state_machine);

 private:
  BijectiveChecker bijective_checker;
  StateMachine state_machine_;
  std::vector<std::string> elem_codes_;
};

#endif  // INCLUDE_ALPHABETIC_ENCODER_H_
