WebSocketEndpoint is a "cmake" sample code project to demonstrate how to create a WebSocket service on a Unix/Linux system.

This project was just a starting point before moving to Vala for creating a WebSocket endpoint demonstration project.

For MacOS:

    brew install cmake
    brew install glib
    brew install json-glib
    pkg-config --cflags glib-2.0
    pkg-config --libs glib-2.0

    NOTE: This cmake project needs to know where the homebrew repo resides because homebrew installs librarys inside the repo. Read the comments for MacOS setup in the CMakeLists.txt file. 

For Linux

    sudo apt-get update
    sudo apt-get install cmake
    sudo apt-get install libglib2.0-dev
    sudo apt-get install libjson-glib-dev
    sudo apt install libssl-dev

For Windows

    git clone https://github.com/microsoft/vcpkg.git C:/Dev/vcpkg
    cd C:/Dev/vcpkg
    ./bootstrap-vcpkg.bat
    Update your "Git Bash" setup to include /c/DIRECTORY/WHERE/YOU/CLONED/VCPKG 

        # my .bashrc PATH additions
        export PATH="$PATH:/c/PATH/ADDITION1:/c/PATH/ADDITION2:/c/DIRECTORY/WHERE/YOU/CLONED/VCPKG/vcpkg


To build a cmake project, first create a directory named "build" inside the "WebSocketEndpoint" folder if one does not already exist (mkdir build). If a build folder already exists (e.g. if you copied this repo from another machine) delete the "build" folder and create a new one. Now run the following commands to build the project.

    cd build    
    cmake ..
    make

This project will build an executable that demonstrates how to embed a web server in any application/tool/service. The product named "endpoint" can be used to create multiple endpoints on a machine. There are two run scripts (buildrun.sh and run_second_endpoint.sh) that launch two endpoints. Each endpoint listens on a unique port number. 

Use "buildrun.sh" to build and test changes. 

    