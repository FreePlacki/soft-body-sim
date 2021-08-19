/**
 * Implements methods from the fileManager class.
 * @file fileManager.cpp
*/

#include "fileManager.h"


void FileManager::saveCurrentSettings(const std::map<std::string, int>  &settings) const {
    std::fstream file(SETTINGS, std::ios::out);
    if (file.is_open()) {
        for (const auto &x : settings) {
            std::string line = x.first + "=" + std::to_string(x.second);
            file << line << std::endl;
        }

        std::cout << "Settings saved successfully\n";
        file.close();
    } else {
        std::cout << "Error opening a file: " << SETTINGS << std::endl;
    }
}

const std::map<std::string, int> FileManager::getCurrentSettings() const {
    std::fstream file1(SETTINGS, std::ios::in);
    if (file1.is_open()) {
        std::map<std::string, int> settings;
        std::string line;
        while (std::getline(file1, line)) {
            settings.insert(
                std::make_pair<std::string, int>(
                    line.substr(0, line.find("=")),
                    std::stoi(line.substr(line.find("=")+1, line.size()))));
        }
        
        file1.close();
        return settings;
    } else {
        std::cout << "Error opening a file: " << SETTINGS << std::endl;
        return std::map<std::string, int> {};
    }
}