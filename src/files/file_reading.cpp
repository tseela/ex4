#include "file_reading.hpp"

std::string files::readFileContent(const std::string& filePath) {
  // Opens input-only file (ifstream) in binary mode.
  std::ifstream in(filePath, std::ios::binary);

  // The file is in a bad state. The error can be retrieved
  //	using the global `errno` in linux (#include <cerrno>).
  if (!in) {
    throw std::system_error(errno, std::system_category());
  }

  // Read the file to a vector. This is not the most effecient
  //	method to read a file.
  auto content = std::string{std::istreambuf_iterator<char>{in},
                             std::istreambuf_iterator<char>{}};

  // After reading the file, it should meet EOF (end of file). If
  //  it did not, it means that an error occurred.
  if (in.fail()) {
    in.close();
    throw std::system_error(errno, std::system_category());
  }

  in.close();
  return content;
}

void files::writeFileContent(const std::string& filePath, const std::string& content) {
  // Opens output-only file (ofstream) in binary mode, and truncates all
  //    existing content from the file.
  std::ofstream out(filePath, std::ios::binary | std::ios::trunc);

  // The file is in a bad state.
  if (!out) {
    throw std::system_error(errno, std::system_category());
  }

  out.write(content.data(), static_cast<std::streamsize>(content.length()));
  if (!out) {
    out.close();
    throw std::system_error(errno, std::system_category());
  }

  out.close();
}
