/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** GiveMeAPizza
*/

#include "Pizzas/GiveMeAPizza.hpp"

std::unique_ptr<Pizza> GiveMeAPizza::giveMeAPizza(const int &orderID, const Pizza::PizzaType &pizzaType, const Pizza::PizzaSize &pizzaSize)
{
    switch (pizzaType)
    {
    case Pizza::PizzaType::Regina:
        return giveMeARegina(orderID, pizzaSize);
    case Pizza::PizzaType::Margarita:
        return giveMeAMargarita(orderID, pizzaSize);
    case Pizza::PizzaType::Americana:
        return giveMeAnAmericana(orderID, pizzaSize);
    default:
        return giveMeAFantasia(orderID, pizzaSize);
    }
}