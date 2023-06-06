// // #include <iostream>
// // #include <fstream>
// // #include <sstream>
// // #include <vector>
// // #include <unordered_set>

// // void processFile(const std::string &mainFilePath, const std::string &buildDir, std::unordered_set<std::string> &includedFiles)
// // {
// //   std::ifstream inputFile(mainFilePath);
// //   if (!inputFile)
// //   {
// //     std::cerr << "Failed to open file: " << mainFilePath << std::endl;
// //     return;
// //   }

// //   std::string line;
// //   while (std::getline(inputFile, line))
// //   {
// //     std::istringstream iss(line);
// //     std::string token;
// //     if (iss >> token && token == "#include")
// //     {
// //       std::string includePath;
// //       if (iss >> includePath)
// //       {
// //         if (includePath.front() == '"' && includePath.back() == '"')
// //         {
// //           includePath = includePath.substr(1, includePath.size() - 2);
// //         }
// //         else if (includePath.front() == '<' && includePath.back() == '>')
// //         {
// //           continue; // Ignore system includes
// //         }

// //         std::string absolutePath = buildDir + '/' + includePath;
// //         if (includedFiles.count(absolutePath) == 0)
// //         {
// //           includedFiles.insert(absolutePath);
// //           processFile(absolutePath, buildDir, includedFiles);
// //         }
// //       }
// //     }
// //   }
// // }

// // int main()
// // {
// //   std::string mainFilePath;
// //   std::string buildDir;

// //   std::cout << "Enter the relative path to the main.cpp file: ";
// //   std::cin >> mainFilePath;

// //   std::cout << "Enter the build directory: ";
// //   std::cin >> buildDir;

// //   std::unordered_set<std::string> includedFiles;
// //   processFile(mainFilePath, buildDir, includedFiles);

// //   std::ostringstream compileCommand;
// //   compileCommand << "g++ -std=c++11 -Wall";

// //   for (const auto &filePath : includedFiles)
// //   {
// //     compileCommand << " " << filePath;
// //   }

// //   std::cout << "Compilation command: " << compileCommand.str() << std::endl;

// //   return 0;
// // }

// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <vector>
// #include <unordered_set>
// #include <filesystem>

// namespace fs = std::filesystem;

// void processFile(const std::string &filePath, const std::string &buildDir, std::unordered_set<std::string> &includedFiles)
// {
//   std::ifstream inputFile(filePath);
//   if (!inputFile)
//   {
//     std::cerr << "Failed to open file: " << filePath << std::endl;
//     return;
//   }

//   std::string line;
//   while (std::getline(inputFile, line))
//   {
//     std::istringstream iss(line);
//     std::string token;
//     if (iss >> token && token == "#include")
//     {
//       std::string includePath;
//       if (iss >> includePath)
//       {
//         if (includePath.front() == '"' && includePath.back() == '"')
//         {
//           includePath = includePath.substr(1, includePath.size() - 2);
//         }
//         else if (includePath.front() == '<' && includePath.back() == '>')
//         {
//           continue; // Ignore system includes
//         }

//         std::string absolutePath = buildDir + '/' + includePath;
//         if (includedFiles.count(absolutePath) == 0)
//         {
//           includedFiles.insert(absolutePath);
//           processFile(absolutePath, buildDir, includedFiles);
//         }
//       }
//     }
//   }
// }

// int main()
// {
//   std::string mainFilePath;
//   std::string buildDir;

//   std::cout << "Enter the relative path to the main.cpp file: ";
//   std::cin >> mainFilePath;

//   std::cout << "Enter the build directory: ";
//   std::cin >> buildDir;

//   std::unordered_set<std::string> includedFiles;
//   processFile(mainFilePath, buildDir, includedFiles);

//   std::ostringstream compileCommand;
//   compileCommand << "g++ -std=c++11 -Wall";

//   for (const auto &filePath : includedFiles)
//   {
//     if (fs::path(filePath).extension() == ".cpp" || fs::path(filePath).extension() == ".h")
//     {
//       compileCommand << " " << filePath;
//     }
//   }

//   std::cout << "Compilation command: " << compileCommand.str() << std::endl;

//   return 0;
// }

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <filesystem>

#include <cstdlib>

#include "json.hpp"

namespace fs = std::filesystem;

void processFiles(const std::string &mainFilePath, const std::string &buildDir, std::unordered_set<std::string> &includedFiles)
{
  std::ifstream inputFile(mainFilePath);
  if (!inputFile)
  {
    std::cerr << "Failed to open file: " << mainFilePath << std::endl;
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
        {
          includePath = includePath.substr(1, includePath.size() - 2);
        }
        else if (includePath.front() == '<' && includePath.back() == '>')
        {
          continue; // Ignore system includes
        }

        std::cout << "IS HERE " << includePath << std::endl;

        // ../App/main.cpp   util.h

        std::string absolutePath = mainFilePath.substr(0, mainFilePath.size() - 9) + '/' + includePath;
        std::cout << "ABSOLUTE PATH " << absolutePath << std::endl;
        if (fs::exists(absolutePath) && includedFiles.count(absolutePath) == 0)
        {
          std::cout << "Found file: " << absolutePath << std::endl;
          includedFiles.insert(absolutePath);
          std::cout << "INSERTED " << includedFiles.size() << std::endl;
          processFiles(absolutePath, buildDir, includedFiles);
        }
      }
    }
  }
}

struct Configuration
{
  std::string mainFilePath;
  std::string buildDir;
  // std::string compiler;
  // std::string compilerFlags;
  // std::string linker;
  // std::string linkerFlags;
};

void getConfiguration(Configuration &configuration)
{

  std::ifstream file("ft.conf");
  if (!file.is_open())
  {
    std::cerr << "Failed to find FT configuration." << std::endl;
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

  configuration.mainFilePath = jsonData["appRoot"];
  configuration.buildDir = jsonData["buildDir"];
  // configuration.compiler = jsonData["compiler"];
  // configuration.compilerFlags = jsonData["compilerFlags"];
  // configuration.linker = jsonData["linker"];
  // configuration.linkerFlags = jsonData["linkerFlags"];
}

int main()
{
  Configuration configuration;
  getConfiguration(configuration);

  std::cout << "Main file path: --------------- " << configuration.mainFilePath << std::endl;

  std::string mainFilePath;
  std::string buildDir;

  std::cout << "Enter the relative path to the main.cpp file: ";
  std::cin >> mainFilePath;

  std::cout << "Enter the build directory: ";
  std::cin >> buildDir;

  std::unordered_set<std::string> includedFiles;

  processFiles(mainFilePath, buildDir, includedFiles);

  std::ostringstream compileCommand;
  compileCommand << "g++ -std=c++17 -Wall"
                 << " " << mainFilePath;

  std::cout << "Included files: " << includedFiles.size() << std::endl;

  for (const auto &filePath : includedFiles)
  {
    std::cout << "File path: BEFORE " << filePath << std::endl;
    if (fs::path(filePath).extension() == ".cpp" || fs::path(filePath).extension() == ".h")
    {
      std::string formattedPath = filePath.substr(0, filePath.size() - 2);
      formattedPath += ".cpp";

      std::cout << "Adding file to compilation: " << formattedPath << std::endl;
      compileCommand << " " << formattedPath;
    }
  }

  compileCommand << " -o " << buildDir << "/main";

  std::cout << "Compilation command: " << compileCommand.str() << std::endl;

  int result = std::system(compileCommand.str().c_str());

  return 0;
}
