/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** ArgumentParser
*/

#include "ArgumentParser/ArgumentParser.hpp"
#include "UI.hpp"

ArgumentParser::ArgumentParser(const int &argc, char **argv)
{
    if (!isValidNumberOfArguments(argc)
    || !isValidCookingTime(argv[1])
    || !isValidCooksNumber(argv[2])
    || !isValidStockTime(argv[3])
    )
    {
        throw std::invalid_argument(USAGE);
    }
    Archive::createRecord();
    UI(std::stof(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]));
}