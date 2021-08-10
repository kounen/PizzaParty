/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** GiveMeAPizza
*/

#ifndef GIVEMEAPIZZA_HPP_
#define GIVEMEAPIZZA_HPP_

#include <memory>

#include "Pizzas/Regina.hpp"
#include "Pizzas/Margarita.hpp"
#include "Pizzas/Americana.hpp"
#include "Pizzas/Fantasia.hpp"

class GiveMeAPizza {
    public:
        GiveMeAPizza() = delete;
        GiveMeAPizza(const GiveMeAPizza &) = delete;
        GiveMeAPizza(GiveMeAPizza &&) = delete;
        GiveMeAPizza &operator=(GiveMeAPizza &&) = delete;
        GiveMeAPizza &operator=(const GiveMeAPizza &) = delete;
        ~GiveMeAPizza() = delete;
        static std::unique_ptr<Pizza> giveMeAPizza(const int &orderID, const Pizza::PizzaType &pizzaType, const Pizza::PizzaSize &pizzaSize);

    private:
        static std::unique_ptr<Regina> giveMeARegina(const int &orderID, const Pizza::PizzaSize &pizzaSize);
        static std::unique_ptr<Margarita> giveMeAMargarita(const int &orderID, const Pizza::PizzaSize &pizzaSize);
        static std::unique_ptr<Americana> giveMeAnAmericana(const int &orderID, const Pizza::PizzaSize &pizzaSize);
        static std::unique_ptr<Fantasia> giveMeAFantasia(const int &orderID, const Pizza::PizzaSize &pizzaSize);
};

#include "Pizzas/GiveMeAPizza.inl"

#endif /* !GIVEMEAPIZZA_HPP_ */
