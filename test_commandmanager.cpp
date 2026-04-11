#include "commandmanager.h"
#include "exceptions.h"

#include <cassert>
#include <iostream>

#define RUN_TEST(test) \
  std::cout << #test << "... " << std::flush; \
  test(); \
  std::cout << "OK\n";

/*******************************************************************************************
 *                                                                                         *
 *                                                                                         *
 *                                  COMMAND MANAGER TESTS                                  *
 *                                                                                         *
 *                                                                                         *
 *******************************************************************************************/

static void test_RUN_OPCODE() {
  std::vector<std::string> commandManagerMessages;
  commandManagerMessages.emplace_back("RUN_NO____456#");
  std::string logs = processCommandManagerMessages(commandManagerMessages);

  assert(logs == "Run number: 456\n");
}

static void test_POLAR_OPCODE() {
  std::vector<std::string> commandManagerMessages;
  commandManagerMessages.emplace_back("POLAR_NO__42#");
  std::string logs = processCommandManagerMessages(commandManagerMessages);

  assert(logs == "Polar number: 42\n");
}

static void test_USR_MSG_OPCODE() {
  std::vector<std::string> commandManagerMessages;
  commandManagerMessages.emplace_back("USR_MSG___This is a test#");
  std::string logs = processCommandManagerMessages(commandManagerMessages);

  assert(logs == "This is a test\n");
}

static void test_D_USR_FLD_OPCODE() {
  std::vector<std::string> commandManagerMessages;
  commandManagerMessages.emplace_back("D_USR_FLD_Parameter1,0.123456,Parameter2,0.7645,Parameter3,-0.123456,Parameter4,42.42,Parameter5,-0.7878789,Parameter6,0.5959585858,#");
  std::string logs = processCommandManagerMessages(commandManagerMessages);

  std::string ref = "Parameters:\n"
                    "Parameter1 = 0.123456\n"
                    "Parameter2 = 0.764500\n"
                    "Parameter3 = -0.123456\n"
                    "Parameter4 = 42.420000\n"
                    "Parameter5 = -0.787879\n"
                    "Parameter6 = 0.595959\n";

  assert(logs == ref);
}

static void test_HISTORY_OPCODE() {
  std::vector<std::string> commandManagerMessages;
  commandManagerMessages.emplace_back("POLAR_NO__42#");
  commandManagerMessages.emplace_back("RUN_NO____123#");
  commandManagerMessages.emplace_back("D_USR_FLD_#");
  commandManagerMessages.emplace_back("POLAR_NO__2#");
  commandManagerMessages.emplace_back("RUN_NO____456#");
  commandManagerMessages.emplace_back("USR_MSG___This is a test#");
  commandManagerMessages.emplace_back("HISTORY___#");
  std::string logs = processCommandManagerMessages(commandManagerMessages);

  std::string ref = "Polar number: 42\n"
                    "Run number: 123\n"
                    "Parameters:\n"
                    "Polar number: 2\n"
                    "Run number: 456\n"
                    "This is a test\n"
                    "USR_MSG___\n"
                    "RUN_NO____\n"
                    "POLAR_NO__\n"
                    "D_USR_FLD_\n"
                    "RUN_NO____\n";

  assert(logs == ref);
}

static void test_unknown_OPCODE() {
  std::vector<std::string> commandManagerMessages;
  commandManagerMessages.emplace_back("Unknown_opcode#");
  std::string logs = processCommandManagerMessages(commandManagerMessages);

  assert(logs == "");
}

/*******************************************************************************************
 *                                                                                         *
 *                                                                                         *
 *                                    EXCEPTIONS TESTS                                     *
 *                                                                                         *
 *                                                                                         *
 *******************************************************************************************/

static void test_MissingHashException() {
  std::vector<std::string> commandManagerMessages;
  commandManagerMessages.emplace_back("RUN_NO____123");

  bool thrown = false;
  try {
    processCommandManagerMessages(commandManagerMessages);
  } catch (const MissingHashException&) {
    thrown = true;
  }

  assert(thrown);
}
static void test_MissingHashException_EmptyMessage() {
  std::vector<std::string> commandManagerMessages;
  commandManagerMessages.emplace_back("");

  bool thrown = false;
  try {
    processCommandManagerMessages(commandManagerMessages);
  } catch (const MissingHashException&) {
    thrown = true;
  }

  assert(thrown);
}

static void test_HashMustEndMessageException() {
  std::vector<std::string> commandManagerMessages;
  commandManagerMessages.emplace_back("RUN_NO____1#23");

  bool thrown = false;
  try {
    processCommandManagerMessages(commandManagerMessages);
  } catch (const HashMustEndMessageException&) {
    thrown = true;
  }

  assert(thrown);
}

static void test_InvalidOpcodeLengthException() {
  std::vector<std::string> commandManagerMessages;
  commandManagerMessages.emplace_back("BADOPCODE#");

  bool thrown = false;
  try {
    processCommandManagerMessages(commandManagerMessages);
  } catch (const InvalidOpcodeLengthException&) {
    thrown = true;
  }

  assert(thrown);
}

static void test_InvalidParameterValueException() {
  std::vector<std::string> commandManagerMessages;
  commandManagerMessages.emplace_back("D_USR_FLD_Parameter1,abc,#");

  bool thrown = false;
  try {
    processCommandManagerMessages(commandManagerMessages);
  } catch (const InvalidParameterValueException&) {
    thrown = true;
  }

  assert(thrown);
}

static void test_TooLongParameterNameException() {
  std::vector<std::string> commandManagerMessages;
  commandManagerMessages.emplace_back("D_USR_FLD_TooLongParameter,0.004947,#");

  bool thrown = false;
  try {
    processCommandManagerMessages(commandManagerMessages);
  } catch (const TooLongParameterNameException&) {
    thrown = true;
  }

  assert(thrown);
}

static void test_MissingParameterValueException() {
  std::vector<std::string> commandManagerMessages;
  commandManagerMessages.emplace_back("D_USR_FLD_Parameter1,#");

  bool thrown = false;
  try {
    processCommandManagerMessages(commandManagerMessages);
  } catch (const MissingParameterValueException&) {
    thrown = true;
  }

  assert(thrown);
}


int main() {
  RUN_TEST(test_RUN_OPCODE);
  RUN_TEST(test_POLAR_OPCODE);
  RUN_TEST(test_USR_MSG_OPCODE);
  RUN_TEST(test_D_USR_FLD_OPCODE);
  RUN_TEST(test_HISTORY_OPCODE);
  RUN_TEST(test_unknown_OPCODE);

  RUN_TEST(test_MissingHashException);
  RUN_TEST(test_MissingHashException_EmptyMessage);
  RUN_TEST(test_HashMustEndMessageException);
  RUN_TEST(test_InvalidOpcodeLengthException);
  RUN_TEST(test_InvalidParameterValueException);
  RUN_TEST(test_TooLongParameterNameException);
  RUN_TEST(test_MissingParameterValueException);
}