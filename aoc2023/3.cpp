/**
* You and the Elf eventually reach a gondola lift station; he says the gondola lift will take you up to the water
 * source, but this is as far as he can bring you. You go inside.
 *
 * It doesn't take long to find the gondolas, but there seems to be a problem: they're not moving.
 *
 * "Aaah!"
 *
 * You turn around to see a slightly-greasy Elf with a wrench and a look of surprise. "Sorry, I wasn't expecting anyone!
 * The gondola lift isn't working right now; it'll still be a while before I can fix it." You offer to help.
 *
 * The engineer explains that an engine part seems to be missing from the engine, but nobody can figure out which one.
 * If you can add up all the part numbers in the engine schematic, it should be easy to work out which part is missing.
 *
 * The engine schematic (your puzzle input) consists of a visual representation of the engine. There are lots of numbers
 * and symbols you don't really understand, but apparently any number adjacent to a symbol, even diagonally, is a "part
 * number" and should be included in your sum. (Periods (.) do not count as a symbol.)
 *
 * Here is an example engine schematic:
 *
 * 467..114..
 * ...*......
 * ..35..633.
 * ......#...
 * 617*......
 * .....+.58.
 * ..592.....
 * ......755.
 * ...$.*....
 * .664.598..
 *
 * In this schematic, two numbers are not part numbers because they are not adjacent to a symbol: 114 (top right) and 58
 * (middle right). Every other number is adjacent to a symbol and so is a part number; their sum is 4361.
 *
 * Of course, the actual engine schematic is much larger. What is the sum of all of the part numbers in the engine
 * schematic?
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <absl/strings/str_split.h>
#include <absl/strings/numbers.h>
#include <absl/strings/ascii.h>
#include <tuple>

const std::vector<std::string> example = {
    "467..114..",
    "...*......",
    "..35..633.",
    "......#...",
    "617*......",
    ".....+.58.",
    "..592.....",
    "......755.",
    "...$.*....",
    ".664.598.."
};

struct Number {
  int row;
  int col;
  int size;
  int num;
};

struct Symbol {
  int row;
  int col;
};

bool isSymbol(char c) {
  return c != '.' && std::ispunct(c);
}

std::vector<Symbol> findSymbols(const absl::string_view &input, int row = 0) {
  std::size_t col = 0;
  std::vector<Symbol> symbols;
  absl::string_view::iterator next_it;
  for (auto it = std::find_if(input.begin(), input.end(), [](const char c) { return isSymbol(c); });
       it != input.end();
       it = std::find_if(next_it, input.end(), [](const char c) { return isSymbol(c); })) {
    Symbol s;
    s.row = row;
    col = std::distance(input.begin(), it);
    s.col = col;
    symbols.push_back(s);
    next_it = it + 1;
  }
  return symbols;
}

TEST(Day3, findSymbols) {
  {
    const std::string input = "467..114..";
    auto symbols = findSymbols(input);
    ASSERT_EQ(symbols.size(), 0);
  }
  {
    const std::string input = "...*......";
    auto symbols = findSymbols(input);
    ASSERT_EQ(symbols.size(), 1);
    ASSERT_EQ(symbols[0].row, 0);
    ASSERT_EQ(symbols[0].col, 3);
  }
  {
    const std::string input = ".*.*./.#.%";
    auto symbols = findSymbols(input);
    ASSERT_EQ(symbols.size(), 5);
    ASSERT_EQ(symbols[0].col, 1);
    ASSERT_EQ(symbols[1].col, 3);
    ASSERT_EQ(symbols[2].col, 5);
    ASSERT_EQ(symbols[3].col, 7);
    ASSERT_EQ(symbols[4].col, 9);
  }
  {
    const std::string input =
        "....+..........259....698..373.992.52.674.........................781...22........130.584.....-...%399.......777.................266........";
    auto symbols = findSymbols(input);
    ASSERT_EQ(symbols.size(), 3);
    ASSERT_EQ(symbols[0].col, 4);
    ASSERT_EQ(symbols[1].col, 94);
    ASSERT_EQ(symbols[2].col, 98);
  }
}

std::tuple<std::vector<Number>, std::vector<Symbol>> findNumbers(const absl::string_view &input) {
  std::vector<Number> numbers;
  std::vector<Symbol> symbols = findSymbols(input);
  std::vector<absl::string_view>
      tokens = absl::StrSplit(input, absl::ByAnyChar("./!@#$%&*()-_=+`~"), absl::SkipEmpty());
  for (const auto &token : tokens) {
    if (token.empty()) continue;
    if (token.size() == 1 && isSymbol(token[0])) {
      continue;
    }
    Number n;

    bool result = absl::SimpleAtoi(token, &n.num);
    if (result) {
      n.col = input.find(token);
      n.size = token.size();
      numbers.push_back(n);
    }
  }
  return {numbers, symbols};
}

TEST(Day3, findNumbers) {
  {
    const std::string input = "467..114..";
    auto [numbers, symbols] = findNumbers(input);
    ASSERT_EQ(numbers.size(), 2);
    ASSERT_EQ(numbers[0].num, 467);
    ASSERT_EQ(numbers[0].size, 3);
    ASSERT_EQ(numbers[0].col, 0);
    ASSERT_EQ(numbers[1].num, 114);
    ASSERT_EQ(numbers[1].size, 3);
    ASSERT_EQ(numbers[1].col, 5);
  }
  {
    const std::string input = "617*........";
    auto [numbers, symbols] = findNumbers(input);
    ASSERT_EQ(numbers.size(), 1);
  }

}

std::tuple<std::vector<Number>, std::vector<Symbol>> parseRow(const absl::string_view &input, int row_num) {
  auto [numbers, symbols] = findNumbers(input);
  for (auto &number : numbers) {
    number.row = row_num;
  }
  for (auto &symbol : symbols) {
    symbol.row = row_num;
  }
  return {numbers, symbols};
}

struct Puzzle {
  std::vector<std::vector<Number>> numbers;
  std::vector<std::vector<Symbol>> symbols;
  std::vector<std::string> rows;
};

bool checkRowForSymbol(const std::string_view &row, int col, int size) {
  int start_col = col - 1 < 0 ? 0 : col - 1;
  int end_col = col + size + 1 > row.size() ? row.size() : col + size + 1;
  absl::string_view row_view = absl::string_view(row).substr(start_col, end_col - start_col);
  return std::any_of(row_view.begin(), row_view.end(), [](const char c) { return isSymbol(c); });
}

bool hasSymbolAbove(const Puzzle &puzzle, const Number &number) {
  if (number.row == 0) return false;
  const std::string &row_above = puzzle.rows[number.row - 1];

  return checkRowForSymbol(row_above, number.col, number.size);
}

bool hasSymbolBelow(const Puzzle &puzzle, const Number &number) {
  if (number.row == puzzle.rows.size() - 1) return false;
  const std::string &row_below = puzzle.rows[number.row + 1];

  return checkRowForSymbol(row_below, number.col, number.size);
}

bool hasSymbolLeft(const Puzzle &puzzle, const Number &number) {
  if (number.col == 0) return false;
  return isSymbol(puzzle.rows[number.row][number.col - 1]);
}

bool hasSymbolRight(const Puzzle &puzzle, const Number &number) {
  if (number.col == puzzle.rows[number.row].size() - 1) return false;
  return isSymbol(puzzle.rows[number.row][number.col + number.size]);
}

int sumOfParts(const Puzzle &p) {
  int sum = 0;
  for (const auto &row : p.numbers) {
    bool something_printed = false;
    for (const auto &number : row) {
      bool no_symbol_near =
          hasSymbolAbove(p, number) ||
              hasSymbolBelow(p, number) ||
              hasSymbolLeft(p, number) ||
              hasSymbolRight(p, number);
      if (no_symbol_near) {
        sum += number.num;
        std::cout << number.num << " ";
        something_printed = true;
      }
    }
    if (something_printed) std::cout << std::endl;
  }
  return sum;
}

TEST(Day3, sample) {
  std::vector<std::vector<Number>> numbers;
  std::vector<std::vector<Symbol>> symbols;
  std::vector<std::string> rows;
  int row = 0;
  for (auto &line : example) {
    auto [row_numbers, row_symbols] = parseRow(line, row++);
    numbers.push_back(row_numbers);
    symbols.push_back(row_symbols);
    rows.push_back(line);
  }
  Puzzle puzzle{numbers, symbols, rows};

  EXPECT_FALSE(hasSymbolAbove(puzzle, puzzle.numbers[0][0]));
  EXPECT_FALSE(hasSymbolAbove(puzzle, puzzle.numbers[0][1]));
  EXPECT_TRUE(hasSymbolAbove(puzzle, puzzle.numbers[2][0]));
  EXPECT_FALSE(hasSymbolAbove(puzzle, puzzle.numbers[2][1]));
  EXPECT_FALSE(hasSymbolAbove(puzzle, puzzle.numbers[4][0]));
  EXPECT_FALSE(hasSymbolAbove(puzzle, puzzle.numbers[5][0]));
  EXPECT_TRUE(hasSymbolAbove(puzzle, puzzle.numbers[6][0]));
  EXPECT_FALSE(hasSymbolAbove(puzzle, puzzle.numbers[7][0]));
  EXPECT_TRUE(hasSymbolAbove(puzzle, puzzle.numbers[9][0]));
  EXPECT_TRUE(hasSymbolAbove(puzzle, puzzle.numbers[9][1]));

  EXPECT_TRUE(hasSymbolBelow(puzzle, puzzle.numbers[0][0]));
  EXPECT_FALSE(hasSymbolBelow(puzzle, puzzle.numbers[0][1]));
  EXPECT_FALSE(hasSymbolBelow(puzzle, puzzle.numbers[2][0]));
  EXPECT_TRUE(hasSymbolBelow(puzzle, puzzle.numbers[2][1]));
  EXPECT_FALSE(hasSymbolBelow(puzzle, puzzle.numbers[4][0]));
  EXPECT_FALSE(hasSymbolBelow(puzzle, puzzle.numbers[5][0]));
  EXPECT_FALSE(hasSymbolBelow(puzzle, puzzle.numbers[6][0]));
  EXPECT_TRUE(hasSymbolBelow(puzzle, puzzle.numbers[7][0]));
  EXPECT_FALSE(hasSymbolBelow(puzzle, puzzle.numbers[9][0]));
  EXPECT_FALSE(hasSymbolBelow(puzzle, puzzle.numbers[9][1]));

  EXPECT_FALSE(hasSymbolLeft(puzzle, puzzle.numbers[0][0]));
  EXPECT_FALSE(hasSymbolLeft(puzzle, puzzle.numbers[0][1]));
  EXPECT_FALSE(hasSymbolLeft(puzzle, puzzle.numbers[2][0]));
  EXPECT_FALSE(hasSymbolLeft(puzzle, puzzle.numbers[2][1]));
  EXPECT_FALSE(hasSymbolLeft(puzzle, puzzle.numbers[4][0]));
  EXPECT_FALSE(hasSymbolLeft(puzzle, puzzle.numbers[5][0]));
  EXPECT_FALSE(hasSymbolLeft(puzzle, puzzle.numbers[6][0]));
  EXPECT_FALSE(hasSymbolLeft(puzzle, puzzle.numbers[7][0]));
  EXPECT_FALSE(hasSymbolLeft(puzzle, puzzle.numbers[9][0]));
  EXPECT_FALSE(hasSymbolLeft(puzzle, puzzle.numbers[9][1]));

  EXPECT_FALSE(hasSymbolRight(puzzle, puzzle.numbers[0][0]));
  EXPECT_FALSE(hasSymbolRight(puzzle, puzzle.numbers[0][1]));
  EXPECT_FALSE(hasSymbolRight(puzzle, puzzle.numbers[2][0]));
  EXPECT_FALSE(hasSymbolRight(puzzle, puzzle.numbers[2][1]));
  EXPECT_TRUE(hasSymbolRight(puzzle, puzzle.numbers[4][0]));
  EXPECT_FALSE(hasSymbolRight(puzzle, puzzle.numbers[5][0]));
  EXPECT_FALSE(hasSymbolRight(puzzle, puzzle.numbers[6][0]));
  EXPECT_FALSE(hasSymbolRight(puzzle, puzzle.numbers[7][0]));
  EXPECT_FALSE(hasSymbolRight(puzzle, puzzle.numbers[9][0]));
  EXPECT_FALSE(hasSymbolRight(puzzle, puzzle.numbers[9][1]));

  EXPECT_EQ(sumOfParts(puzzle), 4361);
}

Puzzle parsePuzzleInput() {
  std::vector<std::vector<Number>> numbers;
  std::vector<std::vector<Symbol>> symbols;
  std::vector<std::string> rows;
  std::ifstream input("3.txt");
  std::string line;
  int row_num = 0;
  while (std::getline(input, line)) {
    auto [row_numbers, row_symbols] = parseRow(line, row_num);
    numbers.push_back(row_numbers);
    symbols.push_back(row_symbols);
    rows.push_back(line);
    row_num++;
  }
  return {numbers, symbols, rows};
}

TEST(Day3, part1) {
  Puzzle p = parsePuzzleInput();
  std::cout << "Part 1: sum " << sumOfParts(p);
}