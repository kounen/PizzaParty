/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Fantasia
*/

#ifndef FANTASIA_HPP_
#define FANTASIA_HPP_

#include "Pizzas/Pizza.hpp"

class Fantasia : public Pizza {
    public:
        Fantasia(const int &orderID, const PizzaSize &pizzaSize);
        ~Fantasia() = default;

        Fantasia() = delete;
        Fantasia(Fantasia &&) = delete;
        Fantasia &operator=(Fantasia &&) = delete;
        Fantasia &operator=(const Fantasia &) = delete;
};

#endif /* !FANTASIA_HPP_ */
