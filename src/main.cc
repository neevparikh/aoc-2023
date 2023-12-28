#include <expected>
#include <fstream>
#include <print>
#include <string>
#include <vector>

const int RED = 12;
const int GREEN = 13;
const int BLUE = 14;

enum class Error {
  InvalidInput,
};

struct Round {
  int red;
  int green;
  int blue;
};

struct Game {
  int id;
  std::vector<Round> rounds;
};

std::expected<Round, Error> parse_round(const std::string &round) {
  int start = 0;
  int end = 0;

  int red = 0;
  int green = 0;
  int blue = 0;

  while (end != std::string::npos) {
    end = round.find(",", start);
    auto draw = round.substr(start, end);
    auto space_pos = draw.find(" ");
    int num = std::stoi(draw.substr(0, space_pos));
    std::string color = draw.substr(space_pos);
    if (color == "red") {
      red += num;
    } else if (color == "green") {
      green += num;
    } else if (color == "blue") {
      blue += num;
    } else {
      return std::unexpected(Error::InvalidInput);
    }
    start = end;
  }
  return Round{red, green, blue};
};

std::expected<Game, Error> parse(const std::string &line) {
  auto colon_pos = line.find(":");
  std::string game_id = line.substr(0, colon_pos);
  int id = std::stoi(game_id.substr(5));
  std::vector<Round> rounds;

  int start = colon_pos;
  int end = colon_pos;
  while (end != std::string::npos) {
    end = line.find(";", start);
    auto round = parse_round(line.substr(start, end));
    if (round.has_value()) {
      rounds.push_back(round.value());
      start = end;
    } else {
      return std::unexpected(round.error());
    }
  }

  return Game{id, rounds};
};

int main(int argc, char **argv) {
  std::string file_name = "data/day_2.txt";
  std::ifstream input_stream(file_name);
  std::string line;
  int total = 0;
  if (input_stream.is_open()) {
    while (std::getline(input_stream, line)) {
      auto game = parse(line);
      if (game.has_value()) {
        total += game->id;
      } else {
        return 1;
      }
    }
    std::println("{} is total", total);
    input_stream.close();
    return 0;
  } else {
    return 1;
  }
}
