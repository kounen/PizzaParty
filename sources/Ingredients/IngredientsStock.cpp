/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** IngredientsStock
*/

#include "Ingredients/IngredientsStock.hpp"

IngredientsStock::IngredientsStock()
    : _stockTimeStart{std::chrono::system_clock::now()}
{
    for (int i = 0; i < RESTOCK_NUMBER; i++)
    {
        stockUpOnIngredients();
    }
}

bool IngredientsStock::destockIngredients(Pizza::PizzaType pizzaType)
{
    std::vector<Ingredient::IngredientType> pizzaIngredients = getPizzaIngredients(pizzaType);

    if (isEnoughStock(pizzaIngredients))
    {
        for (const Ingredient::IngredientType &pizzaIngredient : pizzaIngredients)
        {
            int i = 0;
            for (const std::unique_ptr<Ingredient> &stockIngredient : _ingredientsStock)
            {
                if (pizzaIngredient == stockIngredient->_ingredientType)
                {
                    _ingredientsStock.erase(_ingredientsStock.begin() + i);
                    break;
                }
                i++;
            }
        }
        timeToStockUpIngredients();
        return true;
    }
    return false;
}

void IngredientsStock::stockUpOnIngredients()
{
    _ingredientsStock.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::Doe));
    _ingredientsStock.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::Tomato));
    _ingredientsStock.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::Gruyere));
    _ingredientsStock.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::Ham));
    _ingredientsStock.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::Mushrooms));
    _ingredientsStock.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::Steak));
    _ingredientsStock.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::Eggplant));
    _ingredientsStock.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::GoatCheese));
    _ingredientsStock.push_back(GiveMeAnIngredient::giveMeAnIngredient(Ingredient::ChiefLove));

}

void IngredientsStock::timeToStockUpIngredients()
{
    std::chrono::time_point<std::chrono::system_clock> stockTimeEnd = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = stockTimeEnd - _stockTimeStart;

    if (elapsedSeconds.count() > MILLISECONDS_TO_SECONDS(_stockTime))
    {
        stockUpOnIngredients();
        _stockTimeStart = std::chrono::system_clock::now();
    }
}

std::vector<Ingredient::IngredientType> IngredientsStock::getPizzaIngredients(Pizza::PizzaType pizzaType) const
{
    std::vector<Ingredient::IngredientType> pizzaIngredients;

    switch (pizzaType)
    {
    case Pizza::PizzaType::Margarita:
        pizzaIngredients.push_back(Ingredient::IngredientType::Doe);
        pizzaIngredients.push_back(Ingredient::IngredientType::Tomato);
        pizzaIngredients.push_back(Ingredient::IngredientType::Gruyere);
        break;
    case Pizza::PizzaType::Regina:
        pizzaIngredients.push_back(Ingredient::IngredientType::Doe);
        pizzaIngredients.push_back(Ingredient::IngredientType::Tomato);
        pizzaIngredients.push_back(Ingredient::IngredientType::Gruyere);
        pizzaIngredients.push_back(Ingredient::IngredientType::Ham);
        pizzaIngredients.push_back(Ingredient::IngredientType::Mushrooms);
        break;
    case Pizza::PizzaType::Americana:
        pizzaIngredients.push_back(Ingredient::IngredientType::Doe);
        pizzaIngredients.push_back(Ingredient::IngredientType::Tomato);
        pizzaIngredients.push_back(Ingredient::IngredientType::Gruyere);
        pizzaIngredients.push_back(Ingredient::IngredientType::Steak);
        break;
    case Pizza::PizzaType::Fantasia:
        pizzaIngredients.push_back(Ingredient::IngredientType::Doe);
        pizzaIngredients.push_back(Ingredient::IngredientType::Tomato);
        pizzaIngredients.push_back(Ingredient::IngredientType::Eggplant);
        pizzaIngredients.push_back(Ingredient::IngredientType::GoatCheese);
        pizzaIngredients.push_back(Ingredient::IngredientType::ChiefLove);
        break;
    default:
        break;
    }
    return pizzaIngredients;
}

bool IngredientsStock::isEnoughStock(std::vector<Ingredient::IngredientType> pizzaIngredients) const
{
    std::vector<int> blackList;

    for (const Ingredient::IngredientType &pizzaIngredient : pizzaIngredients)
    {
        size_t i = 0;
        for (const std::unique_ptr<Ingredient> &stockIngredient : _ingredientsStock)
        {
            if (pizzaIngredient == stockIngredient->_ingredientType && std::count(blackList.begin(), blackList.end(), i) == 0)
            {
                blackList.push_back(i);
                break;
            }
            else if (_ingredientsStock.size() == (i + 1))
            {
                return false;
            }
            i++;
        }
    }
    return true;
}
