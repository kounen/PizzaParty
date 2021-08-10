/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** GiveMeAnIngredient
*/

inline std::unique_ptr<Ingredient> GiveMeAnIngredient::giveMeDoe()
{
    return std::make_unique<Ingredient>(Ingredient::IngredientType::Doe);
}

inline std::unique_ptr<Ingredient> GiveMeAnIngredient::giveMeTomato()
{
    return std::make_unique<Ingredient>(Ingredient::IngredientType::Tomato);
}

inline std::unique_ptr<Ingredient> GiveMeAnIngredient::giveMeGruyere()
{
    return std::make_unique<Ingredient>(Ingredient::IngredientType::Gruyere);
}

inline std::unique_ptr<Ingredient> GiveMeAnIngredient::giveMeHam()
{
    return std::make_unique<Ingredient>(Ingredient::IngredientType::Ham);
}

inline std::unique_ptr<Ingredient> GiveMeAnIngredient::giveMeMushrooms()
{
    return std::make_unique<Ingredient>(Ingredient::IngredientType::Mushrooms);
}

inline std::unique_ptr<Ingredient> GiveMeAnIngredient::giveMeSteak()
{
    return std::make_unique<Ingredient>(Ingredient::IngredientType::Steak);
}

inline std::unique_ptr<Ingredient> GiveMeAnIngredient::giveMeEggplant()
{
    return std::make_unique<Ingredient>(Ingredient::IngredientType::Eggplant);
}

inline std::unique_ptr<Ingredient> GiveMeAnIngredient::giveMeGoatCheese()
{
    return std::make_unique<Ingredient>(Ingredient::IngredientType::GoatCheese);
}

inline std::unique_ptr<Ingredient> GiveMeAnIngredient::giveMeChiefLove()
{
    return std::make_unique<Ingredient>(Ingredient::IngredientType::ChiefLove);
}