/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** GiveMeAnIngredient
*/

#include "Ingredients/GiveMeAnIngredient.hpp"

std::unique_ptr<Ingredient> GiveMeAnIngredient::giveMeAnIngredient(const Ingredient::IngredientType &ingredientType)
{
    switch (ingredientType)
    {
    case Ingredient::IngredientType::Doe:
        return giveMeDoe();
    case Ingredient::IngredientType::Tomato:
        return giveMeTomato();
    case Ingredient::IngredientType::Gruyere:
        return giveMeGruyere();
    case Ingredient::IngredientType::Ham:
        return giveMeHam();
    case Ingredient::IngredientType::Mushrooms:
        return giveMeMushrooms();
    case Ingredient::IngredientType::Steak:
        return giveMeSteak();
    case Ingredient::IngredientType::Eggplant:
        return giveMeEggplant();
    case Ingredient::IngredientType::GoatCheese:
        return giveMeGoatCheese();
    default:
        return giveMeChiefLove();
    }
}