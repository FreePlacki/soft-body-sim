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
    static const std::string SETTINGS;
public:
    /**
     * Saves the settings map to settings.txt file
     * @param settings a map<string, int> containing program settings
    */
    static void saveCurrentSettings(const std::map<std::string, int>  &settings);

    /**
     * Returns current app settings from a txt file
     * @return map<string, int> with current settings
    */
    static const std::map<std::string, int> getCurrentSettings();
};