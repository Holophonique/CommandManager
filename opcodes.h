#pragma once

#include <string_view>


constexpr size_t OPCODE_LENGTH = 10;
constexpr std::string_view RUN_OPCODE = "RUN_NO____";
constexpr std::string_view POLAR_OPCODE = "POLAR_NO__";
constexpr std::string_view USR_MSG_OPCODE = "USR_MSG___";
constexpr std::string_view D_USR_FLD_OPCODE = "D_USR_FLD_";
constexpr std::string_view HISTORY_OPCODE = "HISTORY___";