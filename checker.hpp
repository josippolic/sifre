#pragma once
#include <string>
#include <fstream>
#include <unordered_set>
#include <iostream>

bool isPasswordBlacklisted(const std::string& password, const std::string& pathToWordlist) {
    std::ifstream file(pathToWordlist);
    if (!file.is_open()) {
        std::cerr << "Ne mogu otvoriti wordlist: " << pathToWordlist << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line == password) {
            return true;
        }
    }
    return false;
}
