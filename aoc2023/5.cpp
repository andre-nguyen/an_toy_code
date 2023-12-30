/**
 * --- Day 5: If You Give A Seed A Fertilizer ---

You take the boat and find the gardener right where you were told he would be: managing a giant "garden" that looks more to you like a farm.

"A water source? Island Island is the water source!" You point out that Snow Island isn't receiving any water.

"Oh, we had to stop the water because we ran out of sand to filter it with! Can't make snow with dirty water. Don't worry, I'm sure we'll get more sand soon; we only turned off the water a few days... weeks... oh no." His face sinks into a look of horrified realization.

"I've been so busy making sure everyone here has food that I completely forgot to check why we stopped getting more sand! There's a ferry leaving soon that is headed over in that direction - it's much faster than your boat. Could you please go check it out?"

You barely have time to agree to this request when he brings up another. "While you wait for the ferry, maybe you can help us with our food production problem. The latest Island Island Almanac just arrived and we're having trouble making sense of it."

The almanac (your puzzle input) lists all of the seeds that need to be planted. It also lists what type of soil to use with each kind of seed, what type of fertilizer to use with each kind of soil, what type of water to use with each kind of fertilizer, and so on. Every type of seed, soil, fertilizer and so on is identified with a number, but numbers are reused by each category - that is, soil 123 and fertilizer 123 aren't necessarily related to each other.

For example:

seeds: 79 14 55 13

seed-to-soil map:
50 98 2
52 50 48

soil-to-fertilizer map:
0 15 37
37 52 2
39 0 15

fertilizer-to-water map:
49 53 8
0 11 42
42 0 7
57 7 4

water-to-light map:
88 18 7
18 25 70

light-to-temperature map:
45 77 23
81 45 19
68 64 13

temperature-to-humidity map:
0 69 1
1 0 69

humidity-to-location map:
60 56 37
56 93 4

The almanac starts by listing which seeds need to be planted: seeds 79, 14, 55, and 13.

The rest of the almanac contains a list of maps which describe how to convert numbers from a source category into numbers in a destination category. That is, the section that starts with seed-to-soil map: describes how to convert a seed number (the source) to a soil number (the destination). This lets the gardener and his team know which soil to use with which seeds, which water to use with which fertilizer, and so on.

Rather than list every source number and its corresponding destination number one by one, the maps describe entire ranges of numbers that can be converted. Each line within a map contains three numbers: the destination range start, the source range start, and the range length.

Consider again the example seed-to-soil map:

50 98 2
52 50 48

The first line has a destination range start of 50, a source range start of 98, and a range length of 2. This line means that the source range starts at 98 and contains two values: 98 and 99. The destination range is the same length, but it starts at 50, so its two values are 50 and 51. With this information, you know that seed number 98 corresponds to soil number 50 and that seed number 99 corresponds to soil number 51.

The second line means that the source range starts at 50 and contains 48 values: 50, 51, ..., 96, 97. This corresponds to a destination range starting at 52 and also containing 48 values: 52, 53, ..., 98, 99. So, seed number 53 corresponds to soil number 55.

Any source numbers that aren't mapped correspond to the same destination number. So, seed number 10 corresponds to soil number 10.

So, the entire list of seed numbers and their corresponding soil numbers looks like this:

seed  soil
0     0
1     1
...   ...
48    48
49    49
50    52
51    53
...   ...
96    98
97    99
98    50
99    51

With this map, you can look up the soil number required for each initial seed number:

    Seed number 79 corresponds to soil number 81.
    Seed number 14 corresponds to soil number 14.
    Seed number 55 corresponds to soil number 57.
    Seed number 13 corresponds to soil number 13.

The gardener and his team want to get started as soon as possible, so they'd like to know the closest location that needs a seed. Using these maps, find the lowest location number that corresponds to any of the initial seeds. To do this, you'll need to convert each seed number through other categories until you can find its corresponding location number. In this example, the corresponding types are:

    Seed 79, soil 81, fertilizer 81, water 81, light 74, temperature 78, humidity 78, location 82.
    Seed 14, soil 14, fertilizer 53, water 49, light 42, temperature 42, humidity 43, location 43.
    Seed 55, soil 57, fertilizer 57, water 53, light 46, temperature 82, humidity 82, location 86.
    Seed 13, soil 13, fertilizer 52, water 41, light 34, temperature 34, humidity 35, location 35.

So, the lowest location number in this example is 35.

What is the lowest location number that corresponds to any of the initial seed numbers?

*/

#include <gtest/gtest.h>
#include <fstream>
#include <gmock/gmock.h>
#include <absl/strings/str_split.h>
#include <absl/strings/numbers.h>

namespace day5 {

struct Mapping {
  uint64_t dest_start;
  uint64_t src_start;
  uint64_t length;

  [[nodiscard]] bool isIn(uint64_t value) const {
    return value >= src_start && value < src_start + length;
  }

  [[nodiscard]] std::optional<uint64_t> map(uint64_t value) const {
    if (!isIn(value)) {
      return std::nullopt;
    }
    return dest_start + (value - src_start);
  }
};

bool operator==(const Mapping &lhs, const Mapping &rhs) {
  return lhs.dest_start == rhs.dest_start &&
      lhs.src_start == rhs.src_start &&
      lhs.length == rhs.length;
}

uint64_t map(const std::vector<Mapping> &mappings, uint64_t value) {
  for (const auto &mapping : mappings) {
    auto mapped = mapping.map(value);
    if (mapped.has_value()) {
      return mapped.value();
    }
  }
  return value;
}

struct Puzzle {
  std::vector<uint64_t> seeds;
  std::vector<Mapping> seed_to_soil;
  std::vector<Mapping> soil_to_fertilizer;
  std::vector<Mapping> fertilizer_to_water;
  std::vector<Mapping> water_to_light;
  std::vector<Mapping> light_to_temperature;
  std::vector<Mapping> temperature_to_humidity;
  std::vector<Mapping> humidity_to_location;
};

std::vector<uint64_t> parseSeeds(std::ifstream &file) {
  std::string line;
  std::getline(file, line);
  std::vector<absl::string_view> seeds = absl::StrSplit(line, ' ');
  std::vector<uint64_t> seeds_int;
  assert(seeds[0] == "seeds:");
  for (int i = 1; i < seeds.size(); ++i) {
    uint64_t seed;
    if (!absl::SimpleAtoi(seeds[i], &seed)) {
      throw std::runtime_error("Could not parse seed");
    }
    seeds_int.push_back(seed);
  }
  std::getline(file, line); // skip empty line
  return seeds_int;
}

Mapping parseMapping(const std::string &line) {
  std::vector<absl::string_view> mapping = absl::StrSplit(line, ' ');
  assert(mapping.size() == 3);

  Mapping m;
  if (!absl::SimpleAtoi(mapping[0], &m.dest_start)) {
    throw std::runtime_error("Could not parse dest_start");
  }
  if (!absl::SimpleAtoi(mapping[1], &m.src_start)) {
    throw std::runtime_error("Could not parse src_start");
  }
  if (!absl::SimpleAtoi(mapping[2], &m.length)) {
    throw std::runtime_error("Could not parse length");
  }
  return m;
}

std::vector<Mapping> parseMappings(std::ifstream &file) {
  std::string line;
  std::getline(file, line); // skip the header
  std::vector<Mapping> mappings;
  for (std::getline(file, line); !line.empty(); std::getline(file, line)) {
    mappings.push_back(parseMapping(line));
  }

  return mappings;
}

Puzzle parseInput(const std::string &filename) {
  std::ifstream file(filename);
  if (!file) {
    throw std::runtime_error("Could not open file");
  }

  Puzzle puzzle;
  puzzle.seeds = parseSeeds(file);
  puzzle.seed_to_soil = parseMappings(file);
  puzzle.soil_to_fertilizer = parseMappings(file);
  puzzle.fertilizer_to_water = parseMappings(file);
  puzzle.water_to_light = parseMappings(file);
  puzzle.light_to_temperature = parseMappings(file);
  puzzle.temperature_to_humidity = parseMappings(file);
  puzzle.humidity_to_location = parseMappings(file);

  return puzzle;
}

std::vector<uint64_t> getSeedLocations(const Puzzle &p) {
  std::vector<uint64_t> locations;
  locations.reserve(p.seeds.size());
  for (const auto &seed : p.seeds) {
    uint64_t soil = map(p.seed_to_soil, seed);
    uint64_t fertilizer = map(p.soil_to_fertilizer, soil);
    uint64_t water = map(p.fertilizer_to_water, fertilizer);
    uint64_t light = map(p.water_to_light, water);
    uint64_t temperature = map(p.light_to_temperature, light);
    uint64_t humidity = map(p.temperature_to_humidity, temperature);
    uint64_t location = map(p.humidity_to_location, humidity);
    locations.push_back(location);
  }
  return locations;
}

TEST(Day5, parseInput) {
  Puzzle puzzle = parseInput("5_sample.txt");
  EXPECT_THAT(puzzle.seeds, ::testing::ElementsAre(79, 14, 55, 13));
  EXPECT_EQ(puzzle.seed_to_soil.size(), 2);
  EXPECT_THAT(puzzle.seed_to_soil,
              ::testing::ElementsAre(
                  Mapping{50, 98, 2},
                  Mapping{52, 50, 48}));
  EXPECT_EQ(puzzle.soil_to_fertilizer.size(), 3);
  EXPECT_THAT(puzzle.soil_to_fertilizer,
              ::testing::ElementsAre(
                  Mapping{0, 15, 37},
                  Mapping{37, 52, 2},
                  Mapping{39, 0, 15}));
  EXPECT_EQ(puzzle.fertilizer_to_water.size(), 4);
  EXPECT_THAT(puzzle.fertilizer_to_water,
              ::testing::ElementsAre(
                  Mapping{49, 53, 8},
                  Mapping{0, 11, 42},
                  Mapping{42, 0, 7},
                  Mapping{57, 7, 4}));
  EXPECT_EQ(puzzle.water_to_light.size(), 2);
  EXPECT_THAT(puzzle.water_to_light,
              ::testing::ElementsAre(
                  Mapping{88, 18, 7},
                  Mapping{18, 25, 70}));
  EXPECT_EQ(puzzle.light_to_temperature.size(), 3);
  EXPECT_THAT(puzzle.light_to_temperature,
              ::testing::ElementsAre(
                  Mapping{45, 77, 23},
                  Mapping{81, 45, 19},
                  Mapping{68, 64, 13}));
  EXPECT_EQ(puzzle.temperature_to_humidity.size(), 2);
  EXPECT_THAT(puzzle.temperature_to_humidity,
              ::testing::ElementsAre(
                  Mapping{0, 69, 1},
                  Mapping{1, 0, 69}));
  EXPECT_EQ(puzzle.humidity_to_location.size(), 2);
  EXPECT_THAT(puzzle.humidity_to_location,
              ::testing::ElementsAre(
                  Mapping{60, 56, 37},
                  Mapping{56, 93, 4}));
}

TEST(Day5, mapping) {
  //  Seed number 79 corresponds to soil number 81.
  //  Seed number 14 corresponds to soil number 14.
  //  Seed number 55 corresponds to soil number 57.
  //  Seed number 13 corresponds to soil number 13.
  std::vector<Mapping> mappings = {Mapping{50, 98, 2},
                                   Mapping{52, 50, 48}};

  EXPECT_EQ(map(mappings, 79), 81);
  EXPECT_EQ(map(mappings, 14), 14);
  EXPECT_EQ(map(mappings, 55), 57);
  EXPECT_EQ(map(mappings, 13), 13);
}

TEST(Day5, puzzleMapping) {
  //  Seed 79, soil 81, fertilizer 81, water 81, light 74, temperature 78, humidity 78, location 82.
  //  Seed 14, soil 14, fertilizer 53, water 49, light 42, temperature 42, humidity 43, location 43.
  //  Seed 55, soil 57, fertilizer 57, water 53, light 46, temperature 82, humidity 82, location 86.
  //  Seed 13, soil 13, fertilizer 52, water 41, light 34, temperature 34, humidity 35, location 35.
  Puzzle puzzle = parseInput("5_sample.txt");
  auto locations = getSeedLocations(puzzle);
  EXPECT_THAT(locations, ::testing::ElementsAre(82, 43, 86, 35));
}

TEST(Day5, part1) {
  Puzzle puzzle = parseInput("5.txt");
  auto locations = getSeedLocations(puzzle);
  std::cout << "min location: " << *std::min_element(locations.begin(), locations.end()) << std::endl;
}

/*
--- Part Two ---

Everyone will starve if you only plant such a small number of seeds. Re-reading the almanac, it looks like the seeds: line actually describes ranges of seed numbers.

The values on the initial seeds: line come in pairs. Within each pair, the first value is the start of the range and the second value is the length of the range. So, in the first line of the example above:

seeds: 79 14 55 13

This line describes two ranges of seed numbers to be planted in the garden. The first range starts with seed number 79 and contains 14 values: 79, 80, ..., 91, 92. The second range starts with seed number 55 and contains 13 values: 55, 56, ..., 66, 67.

Now, rather than considering four seed numbers, you need to consider a total of 27 seed numbers.

In the above example, the lowest location number can be obtained from seed number 82, which corresponds to soil 84, fertilizer 84, water 84, light 77, temperature 45, humidity 46, and location 46. So, the lowest location number is 46.

Consider all of the initial seed numbers listed in the ranges on the first line of the almanac. What is the lowest location number that corresponds to any of the initial seed numbers?
*/

struct Range {
  uint64_t start;
  uint64_t length;
  class Iterator {
   public:
    Iterator(uint64_t start, uint64_t length) : current_(start), length_(length) {}

    uint64_t operator*() const {
      return current_;
    }

    Iterator &operator++() {
      ++current_;
      return *this;
    }

    bool operator==(const Iterator &rhs) const {
      return current_ == rhs.current_;
    }

    bool operator!=(const Iterator &rhs) const {
      return !(rhs == *this);
    }

    using difference_type = uint64_t;
    using value_type = uint64_t;
    using pointer = const uint64_t *;
    using reference = const uint64_t &;
    using iterator_category = std::forward_iterator_tag;
   private:
    uint64_t current_;
    uint64_t length_;
  };

  [[nodiscard]] Iterator begin() const {
    return {start, length};
  };
  [[nodiscard]] Iterator end() const {
    return {start + length, length};
  };
};

TEST(Day5, range) {
  Range r{50, 20};
  EXPECT_THAT(std::vector<uint64_t>(r.begin(), r.end()),
              ::testing::ElementsAre(50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61,
                                     62, 63, 64, 65, 66, 67, 68, 69));
}

std::vector<Range> toSeedRange(const std::vector<uint64_t> &seeds) {
  std::vector<Range> ranges;
  for (int i = 0; i < seeds.size(); i += 2) {
    ranges.push_back(Range{seeds[i], seeds[i + 1]});
  }
  return ranges;
}

TEST(Day5, toSeedRange) {
  std::vector<uint64_t> seeds = {79, 14, 55, 13};
  std::vector<Range> ranges = toSeedRange(seeds);
  EXPECT_EQ(ranges.size(), 2);
  EXPECT_EQ(ranges[0].start, 79);
  EXPECT_EQ(ranges[0].length, 14);
  EXPECT_EQ(ranges[1].start, 55);
  EXPECT_EQ(ranges[1].length, 13);
}

uint64_t getMinimumSeedLocation(const Puzzle &p) {
  uint64_t min = std::numeric_limits<uint64_t>::max();
  auto ranges = toSeedRange(p.seeds);

  for (const auto &range : ranges) {
    for (const auto &seed : range) {
      uint64_t soil = map(p.seed_to_soil, seed);
      uint64_t fertilizer = map(p.soil_to_fertilizer, soil);
      uint64_t water = map(p.fertilizer_to_water, fertilizer);
      uint64_t light = map(p.water_to_light, water);
      uint64_t temperature = map(p.light_to_temperature, light);
      uint64_t humidity = map(p.temperature_to_humidity, temperature);
      uint64_t location = map(p.humidity_to_location, humidity);
      min = std::min(min, location);
    }
  }

  return min;
}

TEST(Day5, part2Sample) {
  Puzzle puzzle = parseInput("5_sample.txt");
  EXPECT_EQ(getMinimumSeedLocation(puzzle), 46);
}

TEST(Day5, part2) {
  Puzzle puzzle = parseInput("5.txt");
  std::cout << "min location: " << getMinimumSeedLocation(puzzle) << std::endl;
}

}  // day5