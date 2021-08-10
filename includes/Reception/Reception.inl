/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Reception
*/

inline int Reception::getNewOrderID()
{
    return _ordersNumber++;
}

inline void Reception::removeNewOrder()
{
    _ordersNumber -= 1;
}