/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** GiveMeAnIngredient
*/

#ifndef GIVEMEANINGREDIENT_HPP_
#define GIVEMEANINGREDIENT_HPP_

#include <memory>

#include "Ingredients/Ingredient.hpp"

class GiveMeAnIngredient {
    public:
        GiveMeAnIngredient() = delete;
        GiveMeAnIngredient(const GiveMeAnIngredient &) = delete;
        GiveMeAnIngredient(GiveMeAnIngredient &&) = delete;
        GiveMeAnIngredient &operator=(GiveMeAnIngredient &&) = delete;
        GiveMeAnIngredient &operator=(const GiveMeAnIngredient &) = delete;
        ~GiveMeAnIngredient() = delete;
        static std::unique_ptr<Ingredient> giveMeAnIngredient(const Ingredient::IngredientType &ingredientType);

    private:
        static std::unique_ptr<Ingredient> giveMeDoe();
        static std::unique_ptr<Ingredient> giveMeTomato();
        static std::unique_ptr<Ingredient> giveMeGruyere();
        static std::unique_ptr<Ingredient> giveMeHam();
        static std::unique_ptr<Ingredient> giveMeMushrooms();
        static std::unique_ptr<Ingredient> giveMeSteak();
        static std::unique_ptr<Ingredient> giveMeEggplant();
        static std::unique_ptr<Ingredient> giveMeGoatCheese();
        static std::unique_ptr<Ingredient> giveMeChiefLove();
};

#include "Ingredients/GiveMeAnIngredient.inl"

#endif /* !GIVEMEANINGREDIENT_HPP_ */
