/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** IngredientsStock
*/

#ifndef INGREDIENTSSTOCK_HPP_
#define INGREDIENTSSTOCK_HPP_

#include <chrono>
#include <algorithm>

#include "Ingredients/Ingredient.hpp"
#include "Pizzas/Pizza.hpp"

#define RESTOCK_NUMBER 5
#define MILLISECONDS_TO_SECONDS(time_in_milliseconds) time_in_milliseconds / 1000

class IngredientsStock {
    public:
        IngredientsStock();
        ~IngredientsStock() = default;
        IngredientsStock(const IngredientsStock &) = delete;
        IngredientsStock(IngredientsStock &&) = delete;
        IngredientsStock &operator=(IngredientsStock &&) = delete;
        IngredientsStock &operator=(const IngredientsStock &) = delete;

        // Inline stock time setter
        void setStockTime(const int &stockTime) {
            _stockTime = stockTime;
        }

        bool destockIngredients(Pizza::PizzaType pizzaType);
        void timeToStockUpIngredients();

    private:
        void stockUpOnIngredients();
        std::vector<Ingredient::IngredientType> getPizzaIngredients(Pizza::PizzaType pizzaType) const;
        bool isEnoughStock(std::vector<Ingredient::IngredientType> pizzaType) const;

        int _stockTime;
        std::chrono::time_point<std::chrono::system_clock> _stockTimeStart;
        std::vector<std::unique_ptr<Ingredient>> _ingredientsStock;
};

#endif /* !INGREDIENTSSTOCK_HPP_ */
