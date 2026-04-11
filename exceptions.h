#pragma once

#include <stdexcept>


struct HashMustEndMessageException : std::runtime_error {
  explicit HashMustEndMessageException(std::string_view message) :
    std::runtime_error("ERROR : a command manager message must only contain a '#' at its end. Current message is '" + std::string(message) + "'") {}
};

struct InvalidOpcodeLengthException : std::runtime_error {
  InvalidOpcodeLengthException() : std::runtime_error("ERROR : invalid opcode length. The opcode length must be 10.") {}
};

struct InvalidParameterValueException : std::runtime_error {
  InvalidParameterValueException(std::string_view parameterName, std::string_view parameterValue) :
    std::runtime_error("ERROR : parameter '" + std::string(parameterName) + "' has value '" + std::string(parameterValue) + "' which is not a valid number.") {}
};

struct MissingHashException : std::runtime_error {
  explicit MissingHashException(std::string_view message) :
    std::runtime_error("ERROR : a command manager message must end with '#'. Current message is '" + std::string(message) + "'") {}
};

struct MissingParameterValueException : std::runtime_error {
  explicit MissingParameterValueException(std::string_view parameterName) :
    std::runtime_error("ERROR : parameter '" + std::string(parameterName) + "' has no value.") {}
};

struct TooLongParameterNameException : std::runtime_error {
  TooLongParameterNameException(std::string_view parameterName, size_t parameterNameLength) :
    std::runtime_error("ERROR : parameter name '" + std::string(parameterName) + "' must be lower than 15 characters."
                        "Current length is " + std::to_string(parameterNameLength) + ".") {}
};
