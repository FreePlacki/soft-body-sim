/**
 * Reads and writes to files for app storage.
 * @file fileManager.h
*/

#pragma once

#include <string>
#include <map>
#include <fstream>
#include <iostream>


class FileManager {
private:
    std::string SETTINGS = "data/settings.txt";
public:
    /**
     * Saves the settings map to settings.txt file
     * @param settings a map<string, int> containing program settings
    */
    void saveCurrentSettings(const std::map<std::string, int>  &settings) const;

    /**
     * Returns current app settings from a txt file
     * @return map<string, int> with current settings
    */
    const std::map<std::string, int> getCurrentSettings() const;
};