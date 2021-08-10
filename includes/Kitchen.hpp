/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include "Cook.hpp"

typedef struct kitchen_s
{
    int ID;
    int busyCooks;
    int availableCooks;
    time_t noOccupancyTime;
    bool alreadyClosed;
} kitchen_t;

class Kitchen {
    public:
        Kitchen(const int &kitchenID, const float &cookingTime, const int &cooksNumber, const int &stockTime);
        ~Kitchen();
        Kitchen() = delete;
        Kitchen(Kitchen &&) = delete;
        Kitchen &operator=(Kitchen &&) = delete;
        Kitchen &operator=(const Kitchen &) = delete;

    private:
        void createMessageQueue();
        void createThreadPool();

        int _kitchenID;
        float _cookingTime;
        int _cooksNumber;
        int _stockTime;

        std::vector<std::thread> _threadPool;
        std::pair<mqd_t, mqd_t> _messageQueueDescriptor;
};

#endif /* !KITCHEN_HPP_ */
