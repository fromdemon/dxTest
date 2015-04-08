#include "utility.hpp"
#include <algorithm>
#include <exception>
#include <Shlwapi.h>
#include <fstream>

namespace Library {

  std::string Utility::CurrentDirectory() {
    WCHAR buffer[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, buffer);
    std::wstring dir(buffer);

    return std::string(dir.begin(), dir.end());
  }

  std::wstring Utility::ExecutableDirectory() {
    WCHAR buffer[MAX_PATH];
    GetModuleFileName(nullptr, buffer, MAX_PATH);
    PathRemoveFileSpec(buffer);
    
    return std::wstring(buffer);
  }

  void Utility::GetFile(const std::string& inputFile, std::string& filename) {
    std::string fullPath(inputFile);
    std::replace(fullPath.begin(), fullPath.end(), '\\', '/');

    std::string::size_type lastPosition = fullPath.find_last_of('/');
    if (lastPosition != std::string::npos)
      filename = fullPath.substr(lastPosition + 1, fullPath.size() - lastPosition - 1);
    else
      filename = fullPath;
  }

  void Utility::GetDirectory(const std::string& inputFile, std::string& directoryname) {
    std::string fullPath(inputFile);
    std::replace(fullPath.begin(), fullPath.end(), '\\', '/');

    std::string::size_type lastPosition = fullPath.find_last_of('/');
    if (lastPosition != std::string::npos)
      directoryname = fullPath.substr(0, lastPosition + 1);
    else
      directoryname = "";
  }

  void Utility::GetFileAndDirectory(const std::string& inputFile, std::string& filename, std::string& directoryname) {
    std::string fullPath(inputFile);
    std::replace(fullPath.begin(), fullPath.end(), '\\', '/');

    std::string::size_type lastPosition = fullPath.find_last_of('/');
    if (lastPosition != std::string::npos) {
      filename = fullPath.substr(lastPosition+1, fullPath.size() - lastPosition - 1);
      directoryname = fullPath.substr(0, lastPosition + 1);
    }
    else {
      filename = inputFile;
      directoryname = "";
    }
  }

  void Utility::LoadBinaryFile(const std::wstring& filename, std::vector<char>& data) {
    std::ifstream file(filename.c_str(), std::ios::binary);
    if (file.bad())
      throw std::exception("Could not open file");

    file.seekg(0, std::ios::end);
    unsigned int size = (unsigned int)file.tellg();

    if (size > 0){
      data.resize(size);
      file.seekg(0, std::ios::beg);
      file.read(&data.front(), size);
    }

    file.close();
  }

  void Utility::ToWideString(const std::string& source, std::wstring& destination) {
    destination.assign(source.begin(), source.end());
  }

  std::wstring Utility::ToWideString(const std::string& source) {
    std::wstring tmpString;
    return tmpString.assign(source.begin(), source.end());
  }

  void Utility::PathJoin(std::wstring& destination, const std::wstring& directoryname, const std::wstring& filename) {
    WCHAR buffer[MAX_PATH];

    PathCombine(buffer, directoryname.c_str(), filename.c_str());
    destination = buffer;
  }

  void Utility::GetPathExtension(const std::wstring& source, std::wstring& destination) {
    destination = PathFindExtension(source.c_str());
  }

} // namespace Library