#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

uint8_t calculate_digits_of_line(const std::string &line) {
  uint8_t first = 0;
  uint8_t last = 0;
  for (const char &c : line) {
    if (isdigit(c)) {
      if (first == 0) {
        first = c;
        last = c;
      } else {
        last = c;
      }
    }
  }
  std::cout << first << " " << last << std::endl;
  return (first * static_cast<uint8_t>(10)) + last;
}

int main(int argc, char **argv) {
  std::string file_name = "data/day_1/input.txt";
  std::ifstream input_stream(file_name);
  std::string line;
  uint64_t result = 0;
  if (input_stream.is_open()) {
    while (std::getline(input_stream, line)) {
      result += calculate_digits_of_line(line);
    }
    input_stream.close();
    std::cout << "Answer is " << result << std::endl;
    return 0;
  } else {
    return 1;
  }
}
