/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Archive
*/

#include "Archive.hpp"

void Archive::createRecord()
{
    std::ofstream myfile("record.txt", std::ios::trunc);

    if (myfile.is_open())
    {
        myfile << ARCHIVE_HEADER << std::endl;
        myfile.close();
    }
}

void Archive::logInRecord(const std::string &data)
{
    std::ofstream myfile("record.txt", std::ios::app);

    if (myfile.is_open())
    {
        myfile << getCurrentDateTime() << "\t" << data << std::endl;
        myfile.close();
    }
}

std::string Archive::getCurrentDateTime()
{
    std::time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    std::string currentDateTime = asctime(timeinfo);
    currentDateTime.erase(std::prev(currentDateTime.end()));
    return currentDateTime;
}