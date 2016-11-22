//
// Created by cameronearle on 11/21/16.
//

#include "network.h"
#include "iostream"

Network::Network(int testInt_s) {
    testInt = testInt_s;
}

int Network::getTestInt() {
    return testInt;
}

void Network::run() {
    for (int i = 0; i < 10; i++) {
        std::cout << i << std::endl;
    }
}