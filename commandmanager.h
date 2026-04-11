#pragma once

#include <deque>
#include <string>
#include <string_view>
#include <vector>


void printCommandManagerMessages(const std::vector<std::string>& commandManagerMessages);
std::string processCommandManagerMessages(const std::vector<std::string>& commandManagerMessages);
std::string process_D_USR_FLD_opcode(std::string_view runCommandArgument);
std::string process_HISTORY_opcode(const std::deque<std::string>& opcodeHistory);
