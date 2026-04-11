#include <iostream>
#include <stdexcept>
#include <vector>

#include "commandmanager.h"


int main() {
  std::vector<std::string> commandManagerMessages;
  commandManagerMessages.emplace_back("RUN_NO____123#");
  commandManagerMessages.emplace_back("POLAR_NO__2#");
  commandManagerMessages.emplace_back("USR_MSG___Start Tunnel#");
  commandManagerMessages.emplace_back("D_USR_FLD_Parameter1,0.004947,Parameter2,0.203044,Parameter3,-0.003805,Parameter4,0.060000,Parameter5,-0.077580,Parameter6,0.005000,#");
  commandManagerMessages.emplace_back("HISTORY___#");

  try {
    printCommandManagerMessages(commandManagerMessages);
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
