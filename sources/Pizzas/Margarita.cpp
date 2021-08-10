/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Margarita
*/

#include "Pizzas/Margarita.hpp"

Margarita::Margarita(const int &orderID, const PizzaSize &pizzaSize)
    : Pizza(orderID, PizzaType::Margarita, pizzaSize, PizzaCookingTime::OneSecond)
{
    _pizzaIngredients.reserve(PizzaIngredientsNumber::Three);
    _pizzaIngredients.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::IngredientType::Doe));
    _pizzaIngredients.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::IngredientType::Tomato));   
    _pizzaIngredients.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::IngredientType::Gruyere));
}