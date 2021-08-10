/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Ingredient
*/

#ifndef INGREDIENT_HPP_
#define INGREDIENT_HPP_

class Ingredient {
    public:
        typedef enum {
            Doe,
            Tomato,
            Gruyere,
            Ham,
            Mushrooms,
            Steak,
            Eggplant,
            GoatCheese,
            ChiefLove
        } IngredientType;

        Ingredient(const IngredientType &ingredientType);
        ~Ingredient() = default;

        Ingredient() = delete;
        Ingredient(Ingredient &&) = delete;
        Ingredient &operator=(Ingredient &&) = delete;
        Ingredient &operator=(const Ingredient &) = delete;

        const IngredientType _ingredientType;
};

#endif /* !INGREDIENT_HPP_ */
