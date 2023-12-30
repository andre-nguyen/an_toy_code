/*
 * Advent of code 2023 day 2
 *
 * --- Day 2: Cube Conundrum ---
 * You're launched high into the atmosphere! The apex of your trajectory just barely reaches the surface of a large
 * island floating in the sky. You gently land in a fluffy pile of leaves. It's quite cold, but you don't see much snow.
 * An Elf runs over to greet you.
 *
 * The Elf explains that you've arrived at Snow Island and apologizes for the lack of snow. He'll be happy to explain
 * the situation, but it's a bit of a walk, so you have some time. They don't get many visitors up here; would you like
 * to play a game in the meantime?
 *
 * As you walk, the Elf shows you a small bag and some cubes which are either red, green, or blue. Each time you play
 * this game, he will hide a secret number of cubes of each color in the bag, and your goal is to figure out information
 * about the number of cubes.
 *
 * To get information, once a bag has been loaded with cubes, the Elf will reach into the bag, grab a handful of random
 * cubes, show them to you, and then put them back in the bag. He'll do this a few times per game.
 *
 * You play several games and record the information from each game (your puzzle input). Each game is listed with its ID
 * number (like the 11 in Game 11: ...) followed by a semicolon-separated list of subsets of cubes that were revealed
 * from the bag (like 3 red, 5 green, 4 blue).
 *
 * For example, the record of a few games might look like this:
 *
 * Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
 * Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
 * Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
 * Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
 * Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
 *
 * In game 1, three sets of cubes are revealed from the bag (and then put back again). The first set is 3 blue cubes and
 * 4 red cubes; the second set is 1 red cube, 2 green cubes, and 6 blue cubes; the third set is only 2 green cubes.
 *
 * The Elf would first like to know which games would have been possible if the bag contained only 12 red cubes, 13 green
 * cubes, and 14 blue cubes?
 *
 * In the example above, games 1, 2, and 5 would have been possible if the bag had been loaded with that configuration.
 * However, game 3 would have been impossible because at one point the Elf showed you 20 red cubes at once; similarly,
 * game 4 would also have been impossible because the Elf showed you 15 blue cubes at once. If you add up the IDs of the
 * games that would have been possible, you get 8.
 *
 * Determine which games would have been possible if the bag had been loaded with only 12 red cubes, 13 green cubes, and
 * 14 blue cubes. What is the sum of the IDs of those games?
 *
*/

#include <gtest/gtest.h>
#include <fstream>
#include <absl/strings/str_split.h>
#include <absl/strings/numbers.h>
#include <absl/strings/ascii.h>

struct Bag {
  int red = 0;
  int green = 0;
  int blue = 0;
};

bool canIntersect(const Bag &bag, const Bag &other) {
  return bag.red >= other.red && bag.green >= other.green && bag.blue >= other.blue;
}

bool operator==(const Bag &lhs, const Bag &rhs) {
  return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue;
}

TEST(Day2, CanIntersect) {
  Bag bag{12, 13, 14};
  Bag other{1, 2, 3};
  ASSERT_TRUE(canIntersect(bag, other));
  ASSERT_TRUE(canIntersect(bag, {1, 2, 6}));
  ASSERT_TRUE(canIntersect(bag, {0, 2, 0}));
  ASSERT_FALSE(canIntersect(bag, {20, 8, 6}));
}

struct Game {
  int id;
  std::vector<Bag> pulls;
};

int parseGameId(const absl::string_view &input) {
  std::vector<absl::string_view> tokens = absl::StrSplit(input, ' ');
  int i;
  absl::SimpleAtoi(tokens[1], &i);
  return i;
}

Bag parsePull(const absl::string_view &input) {
  std::vector<absl::string_view> colors = absl::StrSplit(input, ", ");

  Bag bag;
  for (auto &color : colors) {
    color = absl::StripAsciiWhitespace(color);
    std::vector<absl::string_view> tokens = absl::StrSplit(color, ' ');
    if (tokens[1] == "red") {
      absl::SimpleAtoi(tokens[0], &bag.red);
    } else if (tokens[1] == "green") {
      absl::SimpleAtoi(tokens[0], &bag.green);
    } else if (tokens[1] == "blue") {
      absl::SimpleAtoi(tokens[0], &bag.blue);
    }
  }

  return bag;
}

TEST(Day2, parseGameId) {
  ASSERT_EQ(parseGameId("Game 1:"), 1);
  ASSERT_EQ(parseGameId("Game 2:"), 2);
  ASSERT_EQ(parseGameId("Game 3:"), 3);
  ASSERT_EQ(parseGameId("Game 30:"), 30);
}

TEST(Day2, parsePull) {
  Bag expected{4, 0, 3};
  ASSERT_EQ(parsePull("3 blue, 4 red"), expected);
  expected = Bag{1, 2, 6};
  ASSERT_EQ(parsePull("1 red, 2 green, 6 blue"), expected);
  expected = Bag{0, 2, 0};
  ASSERT_EQ(parsePull("2 green"), expected);
}

Game parseGame(const absl::string_view &input) {
  std::vector<absl::string_view> tokens = absl::StrSplit(input, ':');
  std::vector<absl::string_view> pulls = absl::StrSplit(tokens[1], ';');

  Game game;
  game.id = parseGameId(tokens[0]);
  for (const auto &pull : pulls) {
    game.pulls.push_back(parsePull(pull));
  }

  return game;
}

TEST(Day2, parseGame1) {
  const std::string input = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green";
  Game game = parseGame(input);

  ASSERT_EQ(game.id, 1);
  ASSERT_EQ(game.pulls.size(), 3);

  Bag expected{4, 0, 3};
  ASSERT_EQ(game.pulls[0], expected);
  expected = {1, 2, 6};
  ASSERT_EQ(game.pulls[1], expected);
  expected = {0, 2, 0};
  ASSERT_EQ(game.pulls[2], expected);
}

TEST(Day2, parseGame2) {
  const std::string input = "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue";
  Game game = parseGame(input);

  ASSERT_EQ(game.id, 2);
  ASSERT_EQ(game.pulls.size(), 3);

  Bag expected{0, 2, 1};
  ASSERT_EQ(game.pulls[0], expected);
  expected = {1, 3, 4};
  ASSERT_EQ(game.pulls[1], expected);
  expected = {0, 1, 1};
  ASSERT_EQ(game.pulls[2], expected);
}

TEST(Day2, parseGame3) {
  const std::string input = "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red";
  Game game = parseGame(input);

  ASSERT_EQ(game.id, 3);
  ASSERT_EQ(game.pulls.size(), 3);

  Bag expected{20, 8, 6};
  ASSERT_EQ(game.pulls[0], expected);
  expected = {4, 13, 5};
  ASSERT_EQ(game.pulls[1], expected);
  expected = {1, 5, 0};
  ASSERT_EQ(game.pulls[2], expected);
}

bool isGameValid(const Game &game, const Bag &bag) {
  return std::all_of(game.pulls.begin(), game.pulls.end(), [bag](const Bag &pull) {
    return canIntersect(bag, pull);
  });
}

TEST(Day2, isGameValid) {
  Game game = parseGame("Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green");
  ASSERT_TRUE(isGameValid(game, {12, 13, 14}));
  ASSERT_FALSE(isGameValid(game, {20, 8, 2}));
  game = parseGame("Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red");
  ASSERT_FALSE(isGameValid(game, {12, 13, 14}));
}

TEST(Day2, example) {
  const std::string input = R"(Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green)";

  std::vector<absl::string_view> lines = absl::StrSplit(input, '\n');
  std::vector<Game> games;
  std::transform(lines.begin(), lines.end(), std::back_inserter(games), parseGame);

  Bag bag{12, 13, 14};
  int sum = 0;
  for (const auto &game : games) {
    if (isGameValid(game, bag)) {
      sum += game.id;
    }
  }

  ASSERT_EQ(sum, 8);
}

TEST(Day2, part1) {
  std::ifstream input_file("2.txt");
  std::vector<Game> games;

  std::string line;
  while (getline(input_file, line)) {
    Game g = parseGame(line);
    games.push_back(g);
  }

  Bag bag{12, 13, 14};
  int sum = 0;
  for (const auto &game : games) {
    if (isGameValid(game, bag)) {
      sum += game.id;
    }
  }

  std::cout << "the sum is " << sum << std::endl;
}

/*
 * --- Part Two ---
 *
 * The Elf says they've stopped producing snow because they aren't getting any water! He isn't sure why the water
 * stopped; however, he can show you how to get to the water source to check it out for yourself. It's just up ahead!
 *
 * As you continue your walk, the Elf poses a second question: in each game you played, what is the fewest number of
 * cubes of each color that could have been in the bag to make the game possible?
 *
 * Again consider the example games from earlier:
 *
 * Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
 * Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
 * Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
 * Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
 * Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
 *
 *     In game 1, the game could have been played with as few as 4 red, 2 green, and 6 blue cubes. If any color had even
 *     one fewer cube, the game would have been impossible.
 *     Game 2 could have been played with a minimum of 1 red, 3 green, and 4 blue cubes.
 *     Game 3 must have been played with at least 20 red, 13 green, and 6 blue cubes.
 *     Game 4 required at least 14 red, 3 green, and 15 blue cubes.
 *     Game 5 needed no fewer than 6 red, 3 green, and 2 blue cubes in the bag.
 *
 * The power of a set of cubes is equal to the numbers of red, green, and blue cubes multiplied together. The power of
 * the minimum set of cubes in game 1 is 48. In games 2-5 it was 12, 1560, 630, and 36, respectively. Adding up these
 * five powers produces the sum 2286.
 *
 * For each game, find the minimum set of cubes that must have been present. What is the sum of the power of these sets?
 *
 */

Bag minBag(const Game &game) {
  Bag min{0, 0, 0};
  for (const auto &pull : game.pulls) {
    min.red = std::max(min.red, pull.red);
    min.green = std::max(min.green, pull.green);
    min.blue = std::max(min.blue, pull.blue);
  }
  return min;
}

TEST(Day2, part2minBag) {
  Game game = parseGame("Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green");
  Bag min = minBag(game);
  Bag expected = Bag{4, 2, 6};
  ASSERT_EQ(min, expected);

  game = parseGame("Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue");
  min = minBag(game);
  expected = Bag{1, 3, 4};
  ASSERT_EQ(min, expected);

  game = parseGame("Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red");
  min = minBag(game);
  expected = Bag{20, 13, 6};
  ASSERT_EQ(min, expected);

  game = parseGame("Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red");
  min = minBag(game);
  expected = Bag{14, 3, 15};
  ASSERT_EQ(min, expected);

  game = parseGame("Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green");
  min = minBag(game);
  expected = Bag{6, 3, 2};
  ASSERT_EQ(min, expected);
}

int power(const Bag &bag) {
  return bag.red * bag.blue * bag.green;
}

TEST(Day2, part2GamePower) {
  Bag bag{4, 2, 6};
  ASSERT_EQ(power(bag), 48);
}

TEST(Day2, part2) {
  std::ifstream input_file("2.txt");
  std::vector<Game> games;

  std::string line;
  while (getline(input_file, line)) {
    Game g = parseGame(line);
    games.push_back(g);
  }

  int sum = 0;
  for (const auto &game : games) {
    Bag min = minBag(game);
    sum += power(min);
  }

  std::cout << "the sum is " << sum << std::endl;
}