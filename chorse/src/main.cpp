#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <filesystem>

#include <cstdlib>

#include "json.hpp"

#define CONFIG_FILE ".chorse"

namespace fs = std::filesystem;

void processFiles(const std::string &filePath, const std::string &buildDir, std::unordered_set<std::string> &includedFiles)
{
  std::ifstream inputFile(filePath);
  if (!inputFile)
  {
    std::cerr << "Failed to open file: " << filePath << std::endl;
    return;
  }

  std::string line;
  while (std::getline(inputFile, line))
  {
    std::cout << "Line: " << line << std::endl;
    std::istringstream iss(line);
    std::string token;
    if (iss >> token && token == "#include")
    {
      std::cout << "Found include" << line << std::endl;
      std::string includePath;
      if (iss >> includePath)
      {
        if (includePath.front() == '"' && includePath.back() == '"')
          includePath = includePath.substr(1, includePath.size() - 2);

        if (includePath.front() == '<' && includePath.back() == '>')
          continue; // Ignore system includes

        std::cout << "IS HERE " << includePath << std::endl;

        // ../App/main.cpp   util.h

        std::string absolutePath = filePath.substr(0, filePath.size() - 9) + '/' + includePath;
        // std::cout << "ABSOLUTE PATH " << absolutePath << std::endl;
        if (fs::exists(absolutePath) && includedFiles.count(absolutePath) == 0)
        {
          includedFiles.insert(absolutePath);
          processFiles(absolutePath, buildDir, includedFiles);
        }
      }
    }
  }
}

struct Configuration
{
  std::string appName;
  std::string mainFilePath;
  std::string buildDir;
  // std::string compiler;
  // std::string compilerFlags;
  // std::string linker;
  // std::string linkerFlags;
};

void getConfiguration(Configuration &configuration)
{

  std::ifstream file(CONFIG_FILE);
  if (!file.is_open())
  {
    std::cerr << "Failed to find C-Horse configuration. (.chorse filse is missing)" << std::endl;
  }

  std::string jsonString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

  nlohmann::json jsonData;
  try
  {
    jsonData = nlohmann::json::parse(jsonString);
  }
  catch (const nlohmann::json::exception &e)
  {
    std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
  }

  configuration.appName = jsonData["appName"];
  configuration.mainFilePath = jsonData["appEntry"];
  configuration.buildDir = jsonData["buildDir"];
  // configuration.compiler = jsonData["compiler"];
  // configuration.compilerFlags = jsonData["compilerFlags"];
  // configuration.linker = jsonData["linker"];
  // configuration.linkerFlags = jsonData["linkerFlags"];
}

int main(int argc, char *argv[])
{
  std::cout << "Number of arguments: " << argc << std::endl;

  for (int i = 0; i < argc; ++i)
  {
    std::cout << "Argument " << i << ": " << argv[i] << std::endl;
  }

  Configuration configuration;
  getConfiguration(configuration);

  // std::cout << "Main file path: --------------- " << configuration.mainFilePath << std::endl;

  // std::string mainFilePath;
  // std::string buildDir;

  // std::cout << "Enter the relative path to the main.cpp file: ";
  // std::cin >> mainFilePath;

  // std::cout << "Enter the build directory: ";
  // std::cin >> buildDir;

  std::unordered_set<std::string> includedFiles;

  processFiles(configuration.mainFilePath, configuration.buildDir, includedFiles);

  std::ostringstream compileCommand;
  compileCommand << "g++ -std=c++17 -Wall"
                 << " " << configuration.mainFilePath;

  std::cout << "Included files: " << includedFiles.size() << std::endl;

  for (const auto &filePath : includedFiles)
  {
    if (fs::path(filePath).extension() == ".cpp" || fs::path(filePath).extension() == ".h")
    {
      std::string formattedPath = filePath.substr(0, filePath.size() - 2);
      formattedPath += ".cpp";
      compileCommand << " " << formattedPath;
    }
  }

  compileCommand << " -o " << configuration.buildDir << "/" << configuration.appName;

  std::cout << "Compilation command: " << compileCommand.str() << std::endl;

  std::system(compileCommand.str().c_str());

  return 0;
}
