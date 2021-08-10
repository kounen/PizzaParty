/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** ArgumentParser
*/

#ifndef ArgumentParser_HPP_
#define ArgumentParser_HPP_

#include <string>
#include <iostream>
#include <cstdlib>
#include <stdexcept>

#include "Archive.hpp"

#define USAGE \
"Usage: ./plazza [cooking time] [number of cooks] [stock time]\n\
    [cooking time]      Multiplier for the cooking time of the pizzas. Either a float with a value between 0 to 1 to obtain a divisior, or a positive integer\n\
    [number of cooks]   Positive integer representing the number of cooks per kitchen\n\
    [stock time]        Positive integer representing the time in milliseconds, used by the kitchen stock to replace ingredients\n\n\
Interactive shell builtins:\n\
    <menu>              Displays the plazza menu\n\
    <status>            Displays the kitchens status, including the current occupancy of the cooks, as well as theirs stocks of ingredients"
#define EXIT_ERROR 84

class ArgumentParser {
    public:
        ArgumentParser(const int &argc, char **argv);
        ~ArgumentParser() = default;

        ArgumentParser() = delete;
        ArgumentParser(ArgumentParser &&) = delete;
        ArgumentParser &operator=(ArgumentParser &&) = delete;
        ArgumentParser &operator=(const ArgumentParser &) = delete;

    private:
        bool isValidNumberOfArguments(const int &argc) const;
        bool isValidCookingTime(const std::string &cookingTime) const;
        bool isValidCooksNumber(const std::string &cooksNumber) const;
        bool isValidStockTime(const std::string &stockTime) const;
        bool isInteger(const std::string &number) const;
        bool isZero(const std::string &number) const;
        bool isFloat(const std::string &number) const;
        bool isBetween(const float &number, const int &start, const int &end) const;
};

#include "ArgumentParser/ArgumentParser.inl"

#endif /* !ArgumentParser_HPP_ */
