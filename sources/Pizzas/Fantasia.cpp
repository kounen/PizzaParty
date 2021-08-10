/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Fantasia
*/

#include "Pizzas/Fantasia.hpp"

Fantasia::Fantasia(const int &orderID, const PizzaSize &pizzaSize)
    : Pizza(orderID, PizzaType::Fantasia, pizzaSize, PizzaCookingTime::FourSeconds)
{
    _pizzaIngredients.reserve(PizzaIngredientsNumber::Five);
    _pizzaIngredients.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::IngredientType::Doe));
    _pizzaIngredients.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::IngredientType::Tomato));   
    _pizzaIngredients.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::IngredientType::Eggplant));
    _pizzaIngredients.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::IngredientType::GoatCheese));
    _pizzaIngredients.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::IngredientType::ChiefLove));
}