/**
 * Reads and writes to files for app storage.
*/

#pragma once

#include <string>
#include <map>
#include <fstream>
#include <iostream>


class FileManager {
public:
    static void saveCurrentSettings(const std::map<std::string, int>  &settings);
    static const std::map<std::string, int> getCurrentSettings();

private:
    static const std::string SETTINGS_PATH;
};