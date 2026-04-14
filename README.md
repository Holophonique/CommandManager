# CommandManager

## To run on Windows

- Install Visual Studio
- Open 'Developer Command Prompt for VS' in this repository
- Execute these commands :

To run the project :
```
cl /std:c++17 commandmanager.cpp main.cpp /Fe: commandmanager
commandmanager
```

To run unit tests :
```
cl /std:c++17 commandmanager.cpp test_commandmanager.cpp /Fe: commandmanagertest
commandmanagertest
```

## To run on Linux/MacOS

- Install gcc or clang
- Execute these commands :

To run the project :
```
g++ -std=c++17 commandmanager.cpp main.cpp -o commandmanager
./commandmanager
```

To run unit tests :
```
g++ -std=c++17 commandmanager.cpp test_commandmanager.cpp -o commandmanagertest
./commandmanagertest
```