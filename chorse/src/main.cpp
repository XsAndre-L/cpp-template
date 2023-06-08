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
    std::istringstream iss(line);
    std::string token;
    if (iss >> token && token == "#include")
    {
      std::string includePath;
      if (iss >> includePath)
      {
        if (includePath.front() == '<' && includePath.back() == '>')
          continue; // Ignore system includes

        if (includePath.front() == '"' && includePath.back() == '"')
        {
          std::cout << "Found: " << line << std::endl;
          includePath = includePath.substr(1, includePath.size() - 2);
        }

        std::string absolutePath = filePath.substr(0, filePath.size() - 9) + '/' + includePath;

        if (fs::exists(absolutePath) && includedFiles.count(absolutePath) == 0)
        {
          includedFiles.insert(absolutePath);
          processFiles(absolutePath, buildDir, includedFiles);
        }
      }
    }
  }
}

struct CHorseConfig
{
  std::string appName;
  std::string mainFilePath;
  std::string buildDir;
  std::string compiler;
  std::string cppVersion;
  std::string cVersion;
};

void getConfiguration(CHorseConfig &config)
{

  std::ifstream file(CONFIG_FILE);
  if (!file.is_open())
  {
    std::cerr << "Failed to find C-Horse config. (.chorse filse is missing)" << std::endl;
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

  config.appName = jsonData["appName"];
  config.mainFilePath = jsonData["appEntry"];
  config.buildDir = jsonData["buildDir"];
  config.compiler = jsonData["compiler"]["name"];
  config.cppVersion = jsonData["compiler"]["cppVersion"];
  config.cVersion = jsonData["compiler"]["cVersion"];
}

void buildCHorse(CHorseConfig &config)
{
  std::unordered_set<std::string> includedFiles;

  processFiles(config.mainFilePath, config.buildDir, includedFiles);

  // the compiler command gets compiler NAME and CPP version from config
  std::ostringstream compileCommand;
  compileCommand << config.compiler << " -std=" << config.cppVersion << " -Wall"
                 << " " << config.mainFilePath;

  std::cout << "Included cpp files: " << includedFiles.size() << std::endl;

  for (const auto &filePath : includedFiles)
  {
    if (fs::path(filePath).extension() == ".cpp")
    {
      compileCommand << " " << filePath;
      continue;
    }

    if (fs::path(filePath).extension() == ".hpp")
    {
      std::string formattedPath = filePath.substr(0, filePath.size() - 4);
      formattedPath += ".cpp";

      if (fs::exists(formattedPath))
        compileCommand << " " << formattedPath;

      continue;
    }

    if (fs::path(filePath).extension() == ".h")
    {
      std::string formattedPath = filePath.substr(0, filePath.size() - 2);
      formattedPath += ".cpp";

      if (fs::exists(formattedPath))
        compileCommand << " " << formattedPath;

      continue;
    }
  }

  compileCommand << " -o " << config.buildDir << "/" << config.appName;

  std::cout << "Compilation command: " << compileCommand.str() << std::endl;

  std::system(compileCommand.str().c_str());
}

// Entry point
int main(int argc, char *argv[])
{
  // std::cout << "Number of arguments: " << argc << std::endl;

  // for (int i = 0; i < argc; ++i)
  // {
  //   std::cout << "Argument " << i << ": " << argv[i] << std::endl;
  // }

  CHorseConfig config;

  if (argc > 1) // argument count greater than 1
  {
    try
    {
      getConfiguration(config);
    }
    catch (const std::exception &e) // CONFIG_FILE not found
    {
      std::cerr << e.what() << '\n';
      return 1;
    }

    if (std::string(argv[1]) == "build")
    {
      buildCHorse(config);
    }
  }

  return 0;
}
