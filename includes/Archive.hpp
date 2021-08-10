/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Archive
*/

#ifndef ARCHIVE_HPP_
#define ARCHIVE_HPP_

#include <fstream>
#include <ctime>

#define ARCHIVE_HEADER \
"PLAZZA RECORD FILE\n\
Authors: Mohamed Mrabet, Mehdi Zehri and Lucas Guichard (Year 2024, Lyon)\n\n\
DETAILS OF OPERATIONS\n\n"

class Archive {
    public:
        Archive() = delete;
        Archive(const Archive &) = delete;
        Archive(Archive &&) = delete;
        Archive &operator=(Archive &&) = delete;
        Archive &operator=(const Archive &) = delete;
        ~Archive() = delete;

        static void createRecord();
        static void logInRecord(const std::string &data);

    private:
        static std::string getCurrentDateTime();
};

#endif /* !ARCHIVE_HPP_ */
