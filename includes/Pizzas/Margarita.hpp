/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Margarita
*/

#ifndef MARGARITA_HPP_
#define MARGARITA_HPP_

#include "Pizzas/Pizza.hpp"

class Margarita : public Pizza {
    public:
        Margarita(const int &orderID, const PizzaSize &pizzaSize);
        ~Margarita() = default;

        Margarita() = delete;
        Margarita(Margarita &&) = delete;
        Margarita &operator=(Margarita &&) = delete;
        Margarita &operator=(const Margarita &) = delete;
};

#endif /* !MARGARITA_HPP_ */
