/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Americana
*/

#ifndef AMERICANA_HPP_
#define AMERICANA_HPP_

#include "Pizzas/Pizza.hpp"

class Americana : public Pizza {
    public:
        Americana(const int &orderID, const PizzaSize &pizzaSize);
        ~Americana() = default;

        Americana() = delete;
        Americana(Americana &&) = delete;
        Americana &operator=(Americana &&) = delete;
        Americana &operator=(const Americana &) = delete;
};

#endif /* !AMERICANA_HPP_ */
