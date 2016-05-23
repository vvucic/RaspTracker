
#include <iostream>

#include "WQueue.hpp"
#include "CameraHandler.hpp"

int main(int argc, const char* argv[]) {
    
    CameraHandler camHandler;
    
    if (!camHandler.openCamera(1)) {
        std::cerr << "Could not open camera\n";
    }
    
    return 0;
}