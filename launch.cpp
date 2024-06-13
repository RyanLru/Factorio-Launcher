// Fichier pour gérer et parser les dossiers à déplacer

#include "launch.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>


namespace fs = std::filesystem;

// Fonction pour regarder quel modpack est présent dans le répertoire de l'utilisateur
// Exemple de répertoire: /home/username/.factorio/mods
// Le fichier est un fichier texte qui a pour nom le nom du modpack
// Le fichier contient le nom du modpack et le chemin du modpack pour le déplacer
// Exemple de contenu du fichier:
// Modpack.txt
// Exotic Industries
// /home/username/Bureau/Projet/Factorio-Launcher/ModPacks/Exotic Industries

bool checkModpacks(std::string& modpackName, std::string& modpackPath) {
    // Récupérer le nom d'utilisateur
    const char* username = getenv("USER");
    if (!username) {
        std::cerr << "Erreur: impossible de récupérer le nom d'utilisateur." << std::endl;
        return false;
    }

    // Chemin du répertoire des mods
    std::string modDirPath = std::string("/home/") + username + "/.factorio/mods";

    // Vérifier si le répertoire existe
    if (!fs::exists(modDirPath) || !fs::is_directory(modDirPath)) {
        std::cerr << "Erreur: le répertoire des mods n'existe pas ou n'est pas un répertoire." << std::endl;
        return false;
    }

    // On ouvert le fichier Modpack.txt
    std::ifstream file(modDirPath + "/Modpack.txt");
    if (!file.is_open()) {
        std::cerr << "Erreur: impossible d'ouvrir le fichier Modpack.txt." << std::endl;
        return false;
    }

    // On récupère le nom du modpack
    std::getline(file, modpackName);

    // On récupère le chemin du modpack
    std::getline(file, modpackPath);

    // On ferme le fichier
    file.close();

    // Remplacer username par le nom d'utilisateur
    size_t pos = modpackPath.find("username");
    if (pos != std::string::npos) {
        modpackPath.replace(pos, 8, username);
    }

    // On Affiche le nom du modpack et le chemin du modpack
    std::cout << "Nom du modpack: " << modpackName << std::endl;
    std::cout << "Chemin du modpack: " << modpackPath << std::endl;


    // On vérifie si le dossier du modpack existe
    if (!fs::exists(modpackPath) || !fs::is_directory(modpackPath)) {
        std::cerr << "Erreur: le répertoire du modpack n'existe pas ou n'est pas un répertoire." << std::endl;
        return false;
    }

    return true;

}

// Fonction pour déplacer les mods du répertoire des mods vers le répertoire du modpack
// Exemple de répertoire des mods: /home/username/.factorio/mods
// Exemple de répertoire du modpack: /home/username/Bureau/Projet/Factorio-Launcher/ModPacks/Exotic Industries
// On déplace les mods du répertoire des mods vers le répertoire du modpack

bool moveModstoFolder() {
    // Récupère le nom et le chemin du modpack
    std::string modpackName;
    std::string modpackPath;
    if (!checkModpacks(modpackName, modpackPath)) {
        return false;
    }

    // Récupérer le nom d'utilisateur
    const char* username = getenv("USER");

    // Chemin du répertoire des mods
    std::string modDirPath = std::string("/home/") + username + "/.factorio/mods";

    // Vérifier si le répertoire existe
    if (!fs::exists(modDirPath) || !fs::is_directory(modDirPath)) {
        std::cerr << "Erreur: le répertoire des mods n'existe pas ou n'est pas un répertoire." << std::endl;
        return false;
    }

    // Chemin du répertoire du modpack
    std::string modpackDirPath = modpackPath;

    // Vérifier si le répertoire existe
    if (!fs::exists(modpackDirPath) || !fs::is_directory(modpackDirPath)) {
        std::cerr << "Erreur: le répertoire du modpack n'existe pas ou n'est pas un répertoire." << std::endl;
        return false;
    }

    // On Déplace les mods du répertoire des mods vers le répertoire du modpack
    for (const auto& entry : fs::directory_iterator(modDirPath)) {
        fs::copy(entry.path(), modpackDirPath / entry.path().filename(), fs::copy_options::recursive);
    }

    // On supprime les mods du répertoire des mods
    for (const auto& entry : fs::directory_iterator(modDirPath)) {
        fs::remove_all(entry.path());
    }

    return true;

    
}

// Fonction pour déplacer les mods du répertoire du modpack vers le répertoire des mods
// Arguments : Chemin du répertoire du modpack
// Exemple de répertoire des mods: /home/username/.factorio/mods
// Exemple de répertoire du modpack: /home/username/Bureau/Projet/Factorio-Launcher/ModPacks/Exotic Industries
// On déplace les mods du répertoire du modpack vers le répertoire des mods

bool moveModsfromFolder(std::string modpackPath) {
    // Récupérer le nom d'utilisateur
    const char* username = getenv("USER");

    // Chemin du répertoire des mods
    std::string modDirPath = std::string("/home/") + username + "/.factorio/mods";

    // Vérifier si le répertoire existe
    if (!fs::exists(modDirPath) || !fs::is_directory(modDirPath)) {
        std::cerr << "Erreur: le répertoire des mods n'existe pas ou n'est pas un répertoire." << std::endl;
        return false;
    }

    // Vérifier si le répertoire du modpack existe
    if (!fs::exists(modpackPath) || !fs::is_directory(modpackPath)) {
        std::cerr << "Erreur: le répertoire du modpack n'existe pas ou n'est pas un répertoire." << std::endl;
        return false;
    }

    // On Déplace les mods du répertoire du modpack vers le répertoire des mods
    for (const auto& entry : fs::directory_iterator(modpackPath)) {
        fs::copy(entry.path(), modDirPath / entry.path().filename(), fs::copy_options::recursive);
    }

    // On supprime les mods du répertoire du modpack
    for (const auto& entry : fs::directory_iterator(modpackPath)) {
        fs::remove_all(entry.path());
    }

    return true;

    
}

// Fonction pour lancer un transfert : Argument : Selection
void Transfert(int selection){
    // Si on a sélectionné un modpack

    // Vérifier si factorio est lancé
    if (checkFactorio()) {
        std::cout << "Factorio est déjà lancé." << std::endl;
        return;
    }

    if(selection != 0){
        // On Déplace les mods du répertoire des mods vers le répertoire du modpack
        moveModstoFolder();

        // Chemin du répertoire du modpack
        std::string modpackPath = std::string("/home/") + getenv("USER") + "/Bureau/Projet/Factorio-Launcher/ModPacks/";

        // On ajoute le nom du modpack
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
        }

        // On déplace les mods du répertoire du modpack vers le répertoire des mods
        moveModsfromFolder(modpackPath);

    }

    // On lance factorio
    launchFactorio();
}


// On vérifie si factorio est lancé, si non return false
bool checkFactorio() {
    // On vérifie si factorio est lancé
    if (system("pgrep factorio") == 0) {
        return true;
    }

    return false;
}

// On Lance factorio avec la commande
/*
#!/bin/bash
__NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia steam steam://rungameid/427520 &
*/
void launchFactorio() {
    if (checkFactorio()) {
        std::cout << "Factorio est déjà lancé." << std::endl;
        return;
    }
    // On lance factorio en arrière-plan
    system("__NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia steam steam://rungameid/427520 &");
    return;
}
