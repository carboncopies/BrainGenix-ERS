//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the main server-side binary of the system.
    Additonal Notes: None
    Date Created: 2021-05-30
*/


#include <iostream>


#include "Core/LocalWindowSystem/LocalWindowSystemModule.cpp"
#include "Core/Management/Logger/LoggerModule.cpp"


int main(){


    // Instantiate
    Logger TestInstance;

    TestInstance.printdummy();
    TestInstance.incrimentnum();
    TestInstance.printdummy();



    std::cout << "Test\n";
    

    std::cout << test();
    std::cout << "\n";

    return 0;
}