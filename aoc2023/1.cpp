#include <algorithm>
#include <cctype>
#include <iostream>
#include <exception>
#include <string>
#include <regex>

int getCalibration(const std::string &s)
{
    auto it = std::find_if(s.cbegin(), s.cend(), [](char c) -> bool
                           { return std::isdigit(c); });

    auto it2 = std::find_if(s.crbegin(), s.crend(), [](char c) -> bool
                            { return std::isdigit(c); });

    char num[3];
    num[0] = *it;
    num[1] = *it2;
    num[2] = 0;

    return std::atoi(num);
}

char word2num(const std::string &s)
{
    using namespace std::string_literals;
    if (s == "one")
    {
        return '1';
    }
    else if (s == "two")
    {
        return '2';
    }
    else if (s == "three")
    {
        return '3';
    }
    else if (s == "four")
    {
        return '4';
    }
    else if (s == "five")
    {
        return '5';
    }
    else if (s == "six")
    {
        return '6';
    }
    else if (s == "seven")
    {
        return '7';
    }
    else if (s == "eight")
    {
        return '8';
    }
    else if (s == "nine")
    {
        return '9';
    }
    throw std::runtime_error("invalid input");
}

int getCalibration2(const std::string &s)
{
    std::regex regex("(one|two|three|four|five|six|seven|eight|nine)",
                     std::regex_constants::ECMAScript);

    auto matches_begin = std::sregex_iterator(s.begin(), s.end(), regex);
    auto matches_end = std::sregex_iterator();

    auto it = std::find_if(s.cbegin(), s.cend(), [](char c) -> bool
                           { return std::isdigit(c); });

    auto it2 = std::find_if(s.crbegin(), s.crend(), [](char c) -> bool
                            { return std::isdigit(c); });

    char num[3];
    num[2] = 0;

    // Compare head
    if (matches_begin == matches_end ||
        std::distance(s.begin(), it) < matches_begin->position())
    {
        // digit is first
        num[0] = *it;
        // std::cout << *it << " ";
    }
    else
    {
        num[0] = word2num(matches_begin->str());
        // std::cout << num[0] << " ";
    }

    // Advance iterator to last valid element
    auto i = matches_begin;
    auto last_match = matches_begin;
    for (; i != matches_end; ++i)
    {
        last_match = i;
    }

    // Compare tail
    if (last_match == matches_end ||
        std::distance(s.begin(), it2.base()) > last_match->position())
    {
        num[1] = *it2;
        // std::cout << *it2 << "\n";
    }
    else
    {
        num[1] = word2num(last_match->str());
        // std::cout << num[1] << "\n";
    }
    // std::cout << "\t" << num << "\n";
    return std::atoi(num);
}
//
//int main()
//{
//    std::string s;
//    int sum = 0;
//
//    while (!std::cin.eof())
//    {
//        std::getline(std::cin, s);
//        if (s.empty())
//        {
//            break;
//        }
//
//        int calibration = getCalibration2(s);
//        sum += calibration;
//        std::cout << "input: " << s << " " << calibration << "\n";
//    }
//    std::cout << "sum: " << sum << "\n";
//    return 0;
//}