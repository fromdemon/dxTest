#pragma once

#include "common.hpp"

namespace Library {

  class Utility {
  public:
    Utility() = delete;
    Utility(const Utility&) = delete;
    Utility operator=(const Utility&) = delete;

    static std::string CurrentDirectory();
    static std::wstring ExecutableDirectory();
    static void GetFile(const std::string& inputFile, std::string& filename);
    static void GetDirectory(const std::string& inputFile, std::string& directoryname);
    static void GetFileAndDirectory(const std::string& inputFile, std::string& filename, std::string& directoryname);
    static void LoadBinaryFile(const std::wstring& filename, std::vector<char>& data);
    static void ToWideString(const std::string& source, std::wstring& destination);
    static std::wstring ToWideString(const std::string& source);
    static void PathJoin(std::wstring& destination, const std::wstring& directoryname, const std::wstring& filename);
    static void GetPathExtension(const std::wstring& source, std::wstring& destination);
  }; // class Utility

} // namespace Library