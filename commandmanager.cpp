#include "commandmanager.h"
#include "exceptions.h"
#include "opcodes.h"

#include <deque>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>


static std::string formatDouble(double x) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(6) << x;
  return oss.str();
}


void printCommandManagerMessages(const std::vector<std::string>& commandManagerMessages) {
  std::string logs = processCommandManagerMessages(commandManagerMessages);
  std::cout << logs << std::flush;
}

std::string processCommandManagerMessages(const std::vector<std::string>& commandManagerMessages) {
  std::string logs;

  std::deque<std::string> opcodeHistory;

  for (const std::string& commandManagerMessage : commandManagerMessages) {
    std::string_view messageView(commandManagerMessage);

    size_t hashPosition = messageView.find('#');
    if (hashPosition == std::string::npos) {
      throw MissingHashException(messageView);
    }

    if (messageView.back() != '#') {
      throw HashMustEndMessageException(messageView);
    }

    // The '#' marks the end of the message.
    // Since the opcode must be exactly OPCODE_LENGTH characters,
    // the '#' must appear at an index >= OPCODE_LENGTH.
    // Otherwise, the message is malformed (opcode too short or missing data).
    if (hashPosition < OPCODE_LENGTH) {
      throw InvalidOpcodeLengthException();
    }

    const size_t commandArgumentLength = hashPosition - OPCODE_LENGTH;
    std::string_view runCommandArgument = messageView.substr(OPCODE_LENGTH, commandArgumentLength);

    std::string_view opcode = messageView.substr(0, OPCODE_LENGTH);

    if (opcode != HISTORY_OPCODE) {
      constexpr size_t MAX_HISTORY_LENGTH = 5;
      if (opcodeHistory.size() == MAX_HISTORY_LENGTH) {
        opcodeHistory.pop_front();
      }
      opcodeHistory.emplace_back(opcode);
    }

    if (opcode == RUN_OPCODE) {
      logs += "Run number: " + std::string(runCommandArgument) + "\n";
    } else if (opcode == POLAR_OPCODE) {
      logs += "Polar number: " + std::string(runCommandArgument) + "\n";
    } else if (opcode == USR_MSG_OPCODE) {
      logs += std::string(runCommandArgument) + "\n";
    } else if (opcode == D_USR_FLD_OPCODE) {
      logs += process_D_USR_FLD_opcode(runCommandArgument);
    } else if (opcode == HISTORY_OPCODE) {
      logs += process_HISTORY_opcode(opcodeHistory);
    } else {
      // Unrecognised opcode // nothing to do
    }
  }

  return logs;
}

std::string process_D_USR_FLD_opcode(std::string_view runCommandArgument) {
  std::string D_USR_FLD_logs;

  std::vector<std::string> tokens;

  size_t start = 0;
  while (start < runCommandArgument.size()) {
    size_t comma = runCommandArgument.find(',', start);
    if (comma == std::string_view::npos) break;

    std::string_view token = runCommandArgument.substr(start, comma - start);
    tokens.emplace_back(token);
    start = comma + 1;
  }

  if (tokens.size() % 2 != 0) {
    throw MissingParameterValueException(tokens.back());
  }

  D_USR_FLD_logs += "Parameters:\n";

  for (size_t i = 0; i < tokens.size(); i += 2) {
    std::string_view parameterName = tokens[i];
    const std::string& parameterValueString = tokens[i + 1];

    const size_t parameterNameLength = parameterName.size();
    if (parameterNameLength > 15u) {
      throw TooLongParameterNameException(parameterName, parameterNameLength);
    }

    double parameterValue = 0.0;
    try {
      parameterValue = std::stod(parameterValueString);
    } catch(const std::exception& e) {
      throw InvalidParameterValueException(parameterName, parameterValueString);
    }
    std::string roundedParameterValue = formatDouble(parameterValue);
    D_USR_FLD_logs += std::string(parameterName) + " = " + roundedParameterValue + "\n";
  }

  return D_USR_FLD_logs;
}


std::string process_HISTORY_opcode(const std::deque<std::string>& opcodeHistory) {
  std::string historyLogs;
  for (auto opcodeIt = opcodeHistory.rbegin(); opcodeIt != opcodeHistory.rend(); ++opcodeIt) {
    historyLogs += *opcodeIt + "\n";;
  }
  return historyLogs;
}
