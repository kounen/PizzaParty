/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Pizza
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_

#include <vector>
#include <memory>

#include "Ingredients/Ingredient.hpp"
#include "Ingredients/GiveMeAnIngredient.hpp"

class Pizza {
    public:
        typedef enum {
            UnknownType = 0,
            Regina = 1,
            Margarita = 2,
            Americana = 4,
            Fantasia = 8
        } PizzaType;

        typedef enum {
            UnknownSize = 0,
            S = 1,
            M = 2,
            L = 4,
            XL = 8,
            XXL = 16
        } PizzaSize;

        typedef enum {
            OneSecond = 1000,
            TwoSeconds = 2000,
            FourSeconds = 4000
        } PizzaCookingTime;

        typedef enum {
            Three = 3,
            Four = 4,
            Five = 5
        } PizzaIngredientsNumber;

        Pizza(const int &orderID, const PizzaType &pizzaType, const PizzaSize &pizzaSize, const PizzaCookingTime &pizzaCookingTime);
        ~Pizza() = default;

        Pizza() = delete;
        Pizza(Pizza &&) = delete;
        Pizza &operator=(Pizza &&) = delete;
        Pizza &operator=(const Pizza &) = delete;

        const int _orderID;
        const PizzaType _pizzaType;
        const PizzaSize _pizzaSize;
        const PizzaCookingTime _pizzaCookingTime;

    protected:
        std::vector<std::unique_ptr<Ingredient>> _pizzaIngredients;
};

#endif /* !PIZZA_HPP_ */
