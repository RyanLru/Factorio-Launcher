// File to manage and parse directories to be moved

#include "launch.h"
#include "librairies.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

/**
 * @brief Checks which modpack is present in the user's directory.
 * The directory is typically: /home/username/.factorio/mods.
 * The file is a text file named after the modpack.
 * The file contains the name of the modpack and the path to the modpack to be moved.
 * Example file content:
 * Modpack.txt
 * Exotic Industries
 * /home/username/Desktop/Project/Factorio-Launcher/ModPacks/Exotic Industries
 *
 * @param modpackName The name of the modpack.
 * @param modpackPath The path to the modpack.
 * @return True if the modpack and its path are successfully retrieved, otherwise false.
 */
bool checkModpacks(std::string& modpackName, std::string& modpackPath) {
    // Retrieve the username
    const char* username = getenv("USER");
    std::string usernameStr(username);
    if (!username) {
        std::cerr << "Error: unable to retrieve the username." << std::endl;
        return false;
    }

    // Path to the mods directory
    std::string modDirPath = std::string("/home/") + username + "/.factorio/mods";

    // Check if the directory exists
    if (!fs::exists(modDirPath) || !fs::is_directory(modDirPath)) {
        std::cerr << "Error: the mods directory does not exist or is not a directory." << std::endl;
        return false;
    }

    // Open the Modpack.txt file
    std::ifstream file(modDirPath + "/Modpack.txt");
    if (!file.is_open()) {
        std::cerr << "Error: unable to open Modpack.txt file." << std::endl;
        return false;
    }

    // Retrieve the modpack name
    std::getline(file, modpackName);

    // Retrieve the modpack path
    std::getline(file, modpackPath);

    // Close the file
    file.close();

    // Replace 'username' with the actual username
    size_t pos = modpackPath.find("username");
    if (pos != std::string::npos) {
        modpackPath.replace(pos, 8, username);
    }

    // Display the modpack name and path
    std::cout << "Modpack name: " << modpackName << std::endl;
    std::cout << "Modpack path: " << modpackPath << std::endl;

    // Check if the modpack directory exists
    if (!fs::exists(modpackPath) || !fs::is_directory(modpackPath)) {
        std::cerr << "Error: the modpack directory does not exist or is not a directory." << std::endl;
        return false;
    }

    return true;
}

/**
 * @brief Moves mods from the mods directory to the modpack directory.
 * Example mods directory: /home/username/.factorio/mods
 * Example modpack directory: /home/username/Desktop/Project/Factorio-Launcher/ModPacks/Exotic Industries
 *
 * @return True if the mods are successfully moved, otherwise false.
 */
bool moveModstoFolder() {
    // Retrieve the modpack name and path
    std::string modpackName;
    std::string modpackPath;
    if (!checkModpacks(modpackName, modpackPath)) {
        return false;
    }

    // Retrieve the username
    const char* username = getenv("USER");

    // Path to the mods directory
    std::string modDirPath = std::string("/home/") + username + "/.factorio/mods";

    // Check if the directory exists
    if (!fs::exists(modDirPath) || !fs::is_directory(modDirPath)) {
        std::cerr << "Error: the mods directory does not exist or is not a directory." << std::endl;
        return false;
    }

    // Path to the modpack directory
    std::string modpackDirPath = modpackPath;

    // Check if the directory exists
    if (!fs::exists(modpackDirPath) || !fs::is_directory(modpackDirPath)) {
        std::cerr << "Error: the modpack directory does not exist or is not a directory." << std::endl;
        return false;
    }

    // Move mods from the mods directory to the modpack directory
    for (const auto& entry : fs::directory_iterator(modDirPath)) {
        fs::copy(entry.path(), modpackDirPath / entry.path().filename(), fs::copy_options::recursive);
    }

    // Delete mods from the mods directory
    for (const auto& entry : fs::directory_iterator(modDirPath)) {
        fs::remove_all(entry.path());
    }

    return true;
}

/**
 * @brief Moves mods from the modpack directory to the mods directory.
 * Example mods directory: /home/username/.factorio/mods
 * Example modpack directory: /home/username/Desktop/Project/Factorio-Launcher/ModPacks/Exotic Industries
 *
 * @param modpackPath The path to the modpack directory.
 * @return True if the mods are successfully moved, otherwise false.
 */
bool moveModsfromFolder(std::string modpackPath) {
    // Retrieve the username
    const char* username = getenv("USER");

    // Path to the mods directory
    std::string modDirPath = std::string("/home/") + username + "/.factorio/mods";

    // Check if the directory exists
    if (!fs::exists(modDirPath) || !fs::is_directory(modDirPath)) {
        std::cerr << "Error: the mods directory does not exist or is not a directory." << std::endl;
        return false;
    }

    // Check if the modpack directory exists
    if (!fs::exists(modpackPath) || !fs::is_directory(modpackPath)) {
        std::cerr << "Error: the modpack directory does not exist or is not a directory." << std::endl;
        return false;
    }

    // Move mods from the modpack directory to the mods directory
    for (const auto& entry : fs::directory_iterator(modpackPath)) {
        fs::copy(entry.path(), modDirPath / entry.path().filename(), fs::copy_options::recursive);
    }

    // Delete mods from the modpack directory
    for (const auto& entry : fs::directory_iterator(modpackPath)) {
        fs::remove_all(entry.path());
    }

    return true;
}

/**
 * @brief Transfers mods based on the selected modpack.
 * 
 * @param selection The selected modpack.
 * @param QOL Indicates whether QOL mods should be included.
 */
void Transfer(int selection, bool QOL){
    // If a modpack is selected

    // Check if Factorio is running
    if (checkFactorio()) {
        std::cout << "Factorio is already running." << std::endl;
        return;
    }

    if(selection != 0){
        // Before moving, delete common files in the mods directory
        deleteCommonFiles(std::string("/home/") + getenv("USER") + "/.factorio/mods");

        // Move mods from the mods directory to the modpack directory
        moveModstoFolder();

        // Path to the modpack directory
        std::string modpackPath = std::string("/home/") + getenv("USER") + "/Bureau/Projet/Factorio-Launcher/ModPacks/";

        // Append the modpack name
        switch (selection) {
            case 1:
                modpackPath += "All-The-Overhaul";
                break;
            case 2:
                modpackPath += "Exotic-Industries";
                break;
            case 3:
                modpackPath += "Pyanodons";
                break;
            case 4:
                modpackPath += "Vanilla";
                break;
            case 5:
                modpackPath += "Angel-Bob";
                break;
        }

        // Move mods from the modpack directory to the mods directory
        moveModsfromFolder(modpackPath);

        // Add QOL mods
        if(QOL){
            moveQOLtoFolder();
        }
    }

    // Launch Factorio
    launchFactorio();
}

/**
 * @brief Checks if Factorio is currently running.
 *
 * @return True if Factorio is running, otherwise false.
 */
bool checkFactorio() {
    // Check if Factorio is running
    if (system("pgrep factorio") == 0) {
        return true;
    }

    return false;
}

/**
 * @brief Launches Factorio using a system command.
 * Uses specific environment variables for rendering settings.
 */
void launchFactorio() {
    if (checkFactorio()) {
        std::cout << "Factorio is already running." << std::endl;
        return;
    }
    // Launch Factorio in the background
    system("__NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia steam steam://rungameid/427520 &");
}
