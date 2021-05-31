//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the main server-side binary of the system.
    Additonal Notes: None
    Date Created: 2021-05-30
*/

#include <iostream>


class Logger {

    private:

        int joe = 1234;

    public:

        void printdummy() {
            std::cout << "test string out";
            std::cout << joe;
        }

        void incrimentnum() {
            joe ++;
        }

};

