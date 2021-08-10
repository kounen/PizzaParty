/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Regina
*/

#ifndef REGINA_HPP_
#define REGINA_HPP_

#include "Pizzas/Pizza.hpp"

class Regina : public Pizza {
    public:
        Regina(const int &orderID, const PizzaSize &pizzaSize);
        ~Regina() = default;

        Regina() = delete;
        Regina(Regina &&) = delete;
        Regina &operator=(Regina &&) = delete;
        Regina &operator=(const Regina &) = delete;
};

#endif /* !REGINA_HPP_ */
