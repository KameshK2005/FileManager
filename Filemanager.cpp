#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void listDirectory(const fs::path& path) {
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            std::cout << entry.path().filename().string() << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void changeDirectory(fs::path& currentPath, const std::string& newPath) {
    try {
        fs::current_path(newPath);
        currentPath = fs::current_path();
        std::cout << "Changed directory to: " << currentPath.string() << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void viewFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }
}

void createDirectory(const std::string& dirPath) {
    try {
        if (fs::create_directory(dirPath)) {
            std::cout << "Directory created: " << dirPath << std::endl;
        } else {
            std::cerr << "Directory not created. It may already exist." << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void copyFile(const std::string& sourcePath, const std::string& destinationPath) {
    try {
        fs::copy(sourcePath, destinationPath);
        std::cout << "File copied to: " << destinationPath << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void moveFile(const std::string& sourcePath, const std::string& destinationPath) {
    try {
        fs::rename(sourcePath, destinationPath);
        std::cout << "File moved to: " << destinationPath << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    fs::path currentPath = fs::current_path();
    std::string command;
    std::cout << "Basic File Manager\nType 'help' for a list of commands.\n";

    while (true) {
        std::cout << currentPath.string() << "> ";
        std::cin >> command;

        if (command == "list") {
            listDirectory(currentPath);
        } else if (command == "cd") {
            std::string newPath;
            std::cin >> newPath;
            changeDirectory(currentPath, newPath);
        } else if (command == "view") {
            std::string filePath;
            std::cin >> filePath;
            viewFile(filePath);
        } else if (command == "mkdir") {
            std::string dirPath;
            std::cin >> dirPath;
            createDirectory(dirPath);
        } else if (command == "copy") {
            std::string sourcePath, destinationPath;
            std::cin >> sourcePath >> destinationPath;
            copyFile(sourcePath, destinationPath);
        } else if (command == "move") {
            std::string sourcePath, destinationPath;
            std::cin >> sourcePath >> destinationPath;
            moveFile(sourcePath, destinationPath);
        } else if (command == "exit") {
            break;
        } else if (command == "help") {
            std::cout << "Commands:\n"
                      << "  list            - List the contents of the current directory\n"
                      << "  cd <path>       - Change the current directory\n"
                      << "  view <file>     - View the contents of a file\n"
                      << "  mkdir <dir>     - Create a new directory\n"
                      << "  copy <src> <dst> - Copy a file\n"
                      << "  move <src> <dst> - Move a file\n"
                      << "  exit            - Exit the file manager\n";
        } else {
            std::cerr << "Unknown command: " << command << std::endl;
        }
    }

    return 0;
}
