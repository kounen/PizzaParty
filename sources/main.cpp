/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** main
*/

#include "ArgumentParser/ArgumentParser.hpp"

int main(int argc, char **argv)
{
    try
    {
        ArgumentParser(argc, argv);
    }
    catch(const std::invalid_argument &error)
    {
        std::cerr << error.what() << std::endl;
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}