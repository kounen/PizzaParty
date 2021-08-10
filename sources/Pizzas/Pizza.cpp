/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Pizza
*/

#include "Pizzas/Pizza.hpp"

Pizza::Pizza(const int &orderID, const PizzaType &pizzaType, const PizzaSize &pizzaSize, const PizzaCookingTime &pizzaCookingTime)
    : _orderID{orderID}, _pizzaType{pizzaType}, _pizzaSize{pizzaSize}, _pizzaCookingTime{pizzaCookingTime}
{
}