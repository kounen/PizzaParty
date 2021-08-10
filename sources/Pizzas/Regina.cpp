/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Regina
*/

#include "Pizzas/Regina.hpp"

Regina::Regina(const int &orderID, const PizzaSize &pizzaSize)
    : Pizza(orderID, PizzaType::Regina, pizzaSize, PizzaCookingTime::TwoSeconds)
{
    _pizzaIngredients.reserve(PizzaIngredientsNumber::Five);
    _pizzaIngredients.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::IngredientType::Doe));
    _pizzaIngredients.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::IngredientType::Tomato));   
    _pizzaIngredients.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::IngredientType::Gruyere));
    _pizzaIngredients.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::IngredientType::Ham));
    _pizzaIngredients.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::IngredientType::Mushrooms));
}