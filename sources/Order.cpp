/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Order
*/

#include "Order/Order.hpp"

Order::Order(const int &orderID, const std::string &orderContent)
    : _orderID{orderID}, _orderContent{orderContent}
{
}

std::string Order::pack(const size_t &pizzaIndex) const
{
    if (pizzaIndex >= _pizzasConveyorBelt.size())
    {
        return nullptr;
    }
    else
    {
        return 
            std::to_string(_pizzasConveyorBelt[pizzaIndex]->_pizzaType) 
            + "-"
            + std::to_string(_pizzasConveyorBelt[pizzaIndex]->_pizzaSize)
            + "-"
            + std::to_string(_orderID);
    }
}

std::vector<int> Order::unpack(std::string &receiveMessage)
{
    // Remove " DONE" characters in receiveMessage
    receiveMessage.erase(receiveMessage.begin() + (receiveMessage.size() - DONE_LENGTH), receiveMessage.end());

    // Create container with unpacked informations from receiveMessage and return it
    std::vector<int> unpackedMessage;

    unpackedMessage.reserve(INFOS_NBR);
    unpackedMessage.push_back(Cook::getPizzaTypeFromOrder(receiveMessage));
    unpackedMessage.push_back(Cook::getPizzaSizeFromOrder(receiveMessage));
    unpackedMessage.push_back(isdigit(receiveMessage[ORDER_ID]) 
                                ? std::atoi(receiveMessage.c_str() + XXL_INDEX) 
                                : std::atoi(receiveMessage.c_str() + NORMAL_INDEX));
    return unpackedMessage;
}
