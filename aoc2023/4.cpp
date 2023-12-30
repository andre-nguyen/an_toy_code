/**
* The gondola takes you up. Strangely, though, the ground doesn't seem to be coming with you; you're not climbing a
 * mountain. As the circle of Snow Island recedes below you, an entire new landmass suddenly appears above you! The
 * gondola carries you to the surface of the new island and lurches into the station.

As you exit the gondola, the first thing you notice is that the air here is much warmer than it was on Snow Island. It's
 also quite humid. Is this where the water source is?

The next thing you notice is an Elf sitting on the floor across the station in what seems to be a pile of colorful
 square cards.

"Oh! Hello!" The Elf excitedly runs over to you. "How may I be of service?" You ask about water sources.

"I'm not sure; I just operate the gondola lift. That does sound like something we'd have, though - this is Island
 Island, after all! I bet the gardener would know. He's on a different island, though - er, the small kind surrounded by
 water, not the floating kind. We really need to come up with a better naming scheme. Tell you what: if you can help me
 with something quick, I'll let you borrow my boat and you can go visit the gardener. I got all these scratchcards as a
 gift, but I can't figure out what I've won."

The Elf leads you over to the pile of colorful cards. There, you discover dozens of scratchcards, all with their opaque
 covering already scratched off. Picking one up, it looks like each card has two lists of numbers separated by a
 vertical bar (|): a list of winning numbers and then a list of numbers you have. You organize the information into a
 table (your puzzle input).

As far as the Elf has been able to figure out, you have to figure out which of the numbers you have appear in the list
 of winning numbers. The first match makes the card worth one point and each match after the first doubles the point
 value of that card.

For example:

Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11

In the above example, card 1 has five winning numbers (41, 48, 83, 86, and 17) and eight numbers you have (83, 86, 6,
 31, 17, 9, 48, and 53). Of the numbers you have, four of them (48, 83, 17, and 86) are winning numbers! That means
 card 1 is worth 8 points (1 for the first match, then doubled three times for each of the three matches after the
 first).

    Card 2 has two winning numbers (32 and 61), so it is worth 2 points.
    Card 3 has two winning numbers (1 and 21), so it is worth 2 points.
    Card 4 has one winning number (84), so it is worth 1 point.
    Card 5 has no winning numbers, so it is worth no points.
    Card 6 has no winning numbers, so it is worth no points.

So, in this example, the Elf's pile of scratchcards is worth 13 points.

Take a seat in the large pile of colorful cards. How many points are they worth in total?
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <absl/strings/str_split.h>
#include <absl/strings/numbers.h>
#include <unordered_set>
#include <algorithm>
#include <fstream>

namespace day4 {

struct Ticket {
  int id;
  std::vector<int> winning_numbers;
  std::vector<int> numbers;
  std::vector<int> intersection;
};

std::vector<int> getNumbers(const absl::string_view &input) {
  std::vector<int> numbers;
  std::vector<absl::string_view> tokens = absl::StrSplit(input, ' ', absl::SkipEmpty());

  for (const auto &token : tokens) {
    int number = 0;
    bool result = absl::SimpleAtoi(token, &number);
    if (result) {
      numbers.push_back(number);
    }
  }

  return numbers;
}

TEST(Day4, getNumbers) {
  {
    auto numbers = getNumbers("41 48 83 86 17");
    EXPECT_EQ(numbers.size(), 5);
    EXPECT_EQ(numbers[0], (41));
    EXPECT_EQ(numbers[1], (48));
    EXPECT_EQ(numbers[2], (83));
    EXPECT_EQ(numbers[3], (86));
    EXPECT_EQ(numbers[4], (17));
  }
  {
    auto numbers = getNumbers("83 86  6 31 17  9 48 53");
    EXPECT_EQ(numbers.size(), 8);
    EXPECT_EQ(numbers[0], 83);
    EXPECT_EQ(numbers[1], 86);
    EXPECT_EQ(numbers[2], 6);
    EXPECT_EQ(numbers[3], 31);
    EXPECT_EQ(numbers[4], 17);
    EXPECT_EQ(numbers[5], 9);
    EXPECT_EQ(numbers[6], 48);
    EXPECT_EQ(numbers[7], 53);
  }
}

int parseGameId(const absl::string_view &input) {
  std::vector<absl::string_view> tokens = absl::StrSplit(input, ' ', absl::SkipEmpty());
  int id = 0;
  bool result = absl::SimpleAtoi(tokens[1], &id);
  if (result) {
    return id;
  }
  throw std::runtime_error("invalid input");
}

TEST(Day4, parseGameId) {
  EXPECT_EQ(parseGameId("card 1:"), 1);
  EXPECT_EQ(parseGameId("card 12:"), 12);
  EXPECT_EQ(parseGameId("card 5:"), 5);
  EXPECT_EQ(parseGameId("card 1235:"), 1235);
}

Ticket parseTicket(const absl::string_view &input) {
  std::vector<absl::string_view> tokens = absl::StrSplit(input, absl::ByAnyChar(":|"), absl::SkipEmpty());

  assert(tokens.size() == 3);

  Ticket ticket;
  ticket.id = parseGameId(tokens[0]);
  ticket.winning_numbers = getNumbers(tokens[1]);
  ticket.numbers = getNumbers(tokens[2]);

  return ticket;
}

TEST(Day4, parseTicket) {
  {
    auto ticket = parseTicket("card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53");
    EXPECT_EQ(ticket.id, 1);
    EXPECT_EQ(ticket.winning_numbers.size(), 5);
    EXPECT_EQ(ticket.numbers.size(), 8);
    EXPECT_THAT(ticket.winning_numbers, testing::UnorderedElementsAre(41, 48, 83, 86, 17));
    EXPECT_THAT(ticket.numbers, testing::UnorderedElementsAre(83, 86, 6, 31, 17, 9, 48, 53));
  }
  {
    auto ticket = parseTicket("card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19");
    EXPECT_EQ(ticket.id, 2);
    EXPECT_EQ(ticket.winning_numbers.size(), 5);
    EXPECT_EQ(ticket.numbers.size(), 8);
    EXPECT_THAT(ticket.winning_numbers, testing::UnorderedElementsAre(13, 32, 20, 16, 61));
    EXPECT_THAT(ticket.numbers, testing::UnorderedElementsAre(61, 30, 68, 82, 17, 32, 24, 19));
  }
  {
    auto ticket = parseTicket("card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1");
    EXPECT_EQ(ticket.id, 3);
    EXPECT_EQ(ticket.winning_numbers.size(), 5);
    EXPECT_EQ(ticket.numbers.size(), 8);
    EXPECT_THAT(ticket.winning_numbers, testing::UnorderedElementsAre(1, 21, 53, 59, 44));
    EXPECT_THAT(ticket.numbers, testing::UnorderedElementsAre(69, 82, 63, 72, 16, 21, 14, 1));
  }
  {
    auto ticket = parseTicket("card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83");
    EXPECT_EQ(ticket.id, 4);
    EXPECT_EQ(ticket.winning_numbers.size(), 5);
    EXPECT_EQ(ticket.numbers.size(), 8);
    EXPECT_THAT(ticket.winning_numbers, testing::UnorderedElementsAre(41, 92, 73, 84, 69));
    EXPECT_THAT(ticket.numbers, testing::UnorderedElementsAre(59, 84, 76, 51, 58, 5, 54, 83));
  }
  {
    auto ticket = parseTicket("card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36");
    EXPECT_EQ(ticket.id, 5);
    EXPECT_EQ(ticket.winning_numbers.size(), 5);
    EXPECT_EQ(ticket.numbers.size(), 8);
    EXPECT_THAT(ticket.winning_numbers, testing::UnorderedElementsAre(87, 83, 26, 28, 32));
    EXPECT_THAT(ticket.numbers, testing::UnorderedElementsAre(88, 30, 70, 12, 93, 22, 82, 36));
  }
  {
    auto ticket = parseTicket("card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11");
    EXPECT_EQ(ticket.id, 6);
    EXPECT_EQ(ticket.winning_numbers.size(), 5);
    EXPECT_EQ(ticket.numbers.size(), 8);
    EXPECT_THAT(ticket.winning_numbers, testing::UnorderedElementsAre(31, 18, 13, 56, 72));
    EXPECT_THAT(ticket.numbers, testing::UnorderedElementsAre(74, 77, 10, 23, 35, 67, 36, 11));
  }
}

int getPoints(Ticket &ticket) {
  int points = 0;
  std::sort(ticket.winning_numbers.begin(), ticket.winning_numbers.end());
  std::sort(ticket.numbers.begin(), ticket.numbers.end());
  std::set_intersection(ticket.winning_numbers.begin(), ticket.winning_numbers.end(),
                        ticket.numbers.begin(), ticket.numbers.end(),
                        std::back_inserter(ticket.intersection));
  if (ticket.intersection.empty()) {
    return 0;
  }

  points = std::pow(2, ticket.intersection.size() - 1);
  return points;
}

TEST(Day4, getPoints) {
  {
    Ticket ticket;
    ticket.winning_numbers = {41, 48, 83, 86, 17};
    ticket.numbers = {83, 86, 6, 31, 17, 9, 48, 53};
    EXPECT_EQ(getPoints(ticket), 8);
  }
  {
    Ticket ticket;
    ticket.winning_numbers = {13, 32, 20, 16, 61};
    ticket.numbers = {61, 30, 68, 82, 17, 32, 24, 19};
    EXPECT_EQ(getPoints(ticket), 2);
  }
  {
    Ticket ticket;
    ticket.winning_numbers = {1, 21, 53, 59, 44};
    ticket.numbers = {69, 82, 63, 72, 16, 21, 14, 1};
    EXPECT_EQ(getPoints(ticket), 2);
  }
  {
    Ticket ticket;
    ticket.winning_numbers = {41, 92, 73, 84, 69};
    ticket.numbers = {59, 84, 76, 51, 58, 5, 54, 83};
    EXPECT_EQ(getPoints(ticket), 1);
  }
  {
    Ticket ticket;
    ticket.winning_numbers = {87, 83, 26, 28, 32};
    ticket.numbers = {88, 30, 70, 12, 93, 22, 82, 36};
    EXPECT_EQ(getPoints(ticket), 0);
  }
  {
    Ticket ticket;
    ticket.winning_numbers = {31, 18, 13, 56, 72};
    ticket.numbers = {74, 77, 10, 23, 35, 67, 36, 11};
    EXPECT_EQ(getPoints(ticket), 0);
  }
}

using PileOfTickets = std::vector<Ticket>;

int sumPoints(PileOfTickets &pile) {
  int sum = 0;
  for (auto &ticket : pile) {
    sum += getPoints(ticket);
  }
  return sum;
}

TEST(Day4, pileOfTickets) {
  PileOfTickets pile;
  pile.push_back(parseTicket("Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53"));
  pile.push_back(parseTicket("Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19"));
  pile.push_back(parseTicket("Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1"));
  pile.push_back(parseTicket("Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83"));
  pile.push_back(parseTicket("Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36"));
  pile.push_back(parseTicket("Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11"));

  EXPECT_EQ(pile.size(), 6);
  EXPECT_EQ(pile[0].id, 1);
  EXPECT_EQ(pile[1].id, 2);
  EXPECT_EQ(pile[2].id, 3);
  EXPECT_EQ(pile[3].id, 4);
  EXPECT_EQ(pile[4].id, 5);
  EXPECT_EQ(pile[5].id, 6);

  EXPECT_EQ(sumPoints(pile), 13);
}

TEST(Day4, part1) {
  std::ifstream input("4.txt");
  std::string line;
  PileOfTickets pile;
  while (std::getline(input, line)) {
    pile.push_back(parseTicket(line));
  }

  std::cout << "Sum points: " << sumPoints(pile) << "\n";
}

/**
 * --- Part Two ---

Just as you're about to report your findings to the Elf, one of you realizes that the rules have actually been printed
 on the back of every card this whole time.

There's no such thing as "points". Instead, scratchcards only cause you to win more scratchcards equal to the number of
 winning numbers you have.

Specifically, you win copies of the scratchcards below the winning card equal to the number of matches. So, if card 10
 were to have 5 matching numbers, you would win one copy each of cards 11, 12, 13, 14, and 15.

Copies of scratchcards are scored like normal scratchcards and have the same card number as the card they copied. So,
 if you win a copy of card 10 and it has 5 matching numbers, it would then win a copy of the same cards that the
 original card 10 won: cards 11, 12, 13, 14, and 15. This process repeats until none of the copies cause you to win any
 more cards. (Cards will never make you copy a card past the end of the table.)

This time, the above example goes differently:

Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11

    Card 1 has four matching numbers, so you win one copy each of the next four cards: cards 2, 3, 4, and 5.
    Your original card 2 has two matching numbers, so you win one copy each of cards 3 and 4.
    Your copy of card 2 also wins one copy each of cards 3 and 4.
    Your four instances of card 3 (one original and three copies) have two matching numbers, so you win four copies each of cards 4 and 5.
    Your eight instances of card 4 (one original and seven copies) have one matching number, so you win eight copies of card 5.
    Your fourteen instances of card 5 (one original and thirteen copies) have no matching numbers and win no more cards.
    Your one instance of card 6 (one original) has no matching numbers and wins no more cards.

Once all of the originals and copies have been processed, you end up with 1 instance of card 1, 2 instances of card 2,
 4 instances of card 3, 8 instances of card 4, 14 instances of card 5, and 1 instance of card 6. In total, this example
 pile of scratchcards causes you to ultimately have 30 scratchcards!

Process all of the original and copied scratchcards until no more scratchcards are won. Including the original set of
 scratchcards, how many total scratchcards do you end up with?

 */

int getNumCopies(Ticket &ticket) {
  int copies = 0;
  std::sort(ticket.winning_numbers.begin(), ticket.winning_numbers.end());
  std::sort(ticket.numbers.begin(), ticket.numbers.end());
  std::set_intersection(ticket.winning_numbers.begin(), ticket.winning_numbers.end(),
                        ticket.numbers.begin(), ticket.numbers.end(),
                        std::back_inserter(ticket.intersection));
  if (ticket.intersection.empty()) {
    return 0;
  }

  copies = ticket.intersection.size();
  return copies;
}

TEST(Day4, part2GetNumCopies) {
  {
    Ticket ticket;
    ticket.winning_numbers = {41, 48, 83, 86, 17};
    ticket.numbers = {83, 86, 6, 31, 17, 9, 48, 53};
    EXPECT_EQ(getNumCopies(ticket), 4);
  }
  {
    Ticket ticket;
    ticket.winning_numbers = {13, 32, 20, 16, 61};
    ticket.numbers = {61, 30, 68, 82, 17, 32, 24, 19};
    EXPECT_EQ(getNumCopies(ticket), 2);
  }
  {
    Ticket ticket;
    ticket.winning_numbers = {1, 21, 53, 59, 44};
    ticket.numbers = {69, 82, 63, 72, 16, 21, 14, 1};
    EXPECT_EQ(getNumCopies(ticket), 2);
  }
  {
    Ticket ticket;
    ticket.winning_numbers = {41, 92, 73, 84, 69};
    ticket.numbers = {59, 84, 76, 51, 58, 5, 54, 83};
    EXPECT_EQ(getNumCopies(ticket), 1);
  }
  {
    Ticket ticket;
    ticket.winning_numbers = {87, 83, 26, 28, 32};
    ticket.numbers = {88, 30, 70, 12, 93, 22, 82, 36};
    EXPECT_EQ(getNumCopies(ticket), 0);
  }
  {
    Ticket ticket;
    ticket.winning_numbers = {31, 18, 13, 56, 72};
    ticket.numbers = {74, 77, 10, 23, 35, 67, 36, 11};
    EXPECT_EQ(getNumCopies(ticket), 0);
  }
}

void updatePileOfTicketsWithCopies(PileOfTickets &pile) {
  std::vector<int> ticket_count(pile.size(), 1);
  for (int i = 0; i < pile.size(); ++i) {
    int num_new_tickets = getNumCopies(pile[i]);
    for (int j = 0; j < num_new_tickets && j + i < pile.size(); ++j) {
      ticket_count[j + i + 1] += ticket_count[i];
    }
  }

  PileOfTickets new_pile;
  for (auto count : ticket_count) {
    new_pile.insert(new_pile.end(), count, pile.back());
  }
  pile = new_pile;
  std::sort(pile.begin(), pile.end(), [](const Ticket &a, const Ticket &b) { return a.id < b.id; });
}

TEST(Day4, part2PileOfTickets) {
  PileOfTickets pile;
  pile.push_back(parseTicket("Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53"));
  pile.push_back(parseTicket("Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19"));
  pile.push_back(parseTicket("Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1"));
  pile.push_back(parseTicket("Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83"));
  pile.push_back(parseTicket("Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36"));
  pile.push_back(parseTicket("Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11"));

  EXPECT_EQ(pile.size(), 6);
  updatePileOfTicketsWithCopies(pile);
  EXPECT_EQ(pile.size(), 30);
}

TEST(Day4, part2) {
  std::ifstream input("4.txt");
  std::string line;
  PileOfTickets pile;
  while (std::getline(input, line)) {
    pile.push_back(parseTicket(line));
  }

  updatePileOfTicketsWithCopies(pile);
  std::cout << "Num cards: " << pile.size() << "\n";
}

}  /// namespace day4