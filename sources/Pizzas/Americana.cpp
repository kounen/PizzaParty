/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Americana
*/

#include "Pizzas/Americana.hpp"

Americana::Americana(const int &orderID, const PizzaSize &pizzaSize)
    : Pizza(orderID, PizzaType::Americana, pizzaSize, PizzaCookingTime::TwoSeconds)
{
    _pizzaIngredients.reserve(PizzaIngredientsNumber::Four);
    _pizzaIngredients.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::IngredientType::Doe));
    _pizzaIngredients.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::IngredientType::Tomato));   
    _pizzaIngredients.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::IngredientType::Gruyere));
    _pizzaIngredients.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::IngredientType::Steak));
}