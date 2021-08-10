/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** UI
*/

#ifndef UI_HPP_
#define UI_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <memory>

#include "Colours.h"
#include "Reception/Reception.hpp"

#define WELCOME "Welcome to plazza restaurant !"
#define GOODBYE "See you soon in our plazza restaurant !"
#define PROMPT "Enter your order below"
#define INVALID_ORDER \
"Error: Wrong grammar for pizza ordering\n\
        S := TYPE SIZE NUMBER [; TYPE SIZE NUMBER]*\n\
        TYPE := [a..zA..Z]+\n\
        SIZE := S|M|L|XL|XXL\n\
        NUMBER := x[1..9][0..9]*\n\
example: 'regina XXL x2; fantasia M x3; margarita S x1; americana L x6'"
#define MENU \
" ------------------------------MENU------------------------------\n\
|               Margarita: doe, tomato and gruyere.              |\n\
|         Regina: doe, tomato, gruyere, ham, mushrooms.          |\n\
|             Americana: doe, tomato, gruyere, steak.            |\n\
|  Fantasia: doe, tomato, eggplant, goat cheese and chief love.  |\n\
 ----------------------------------------------------------------"
#define NEW_ORDER(id) "Your order has the number " << id << ", you will be informed once it is ready"

class UI {
    public:
        UI(const float &cookingTime, const int &cooksNumber, const int &stockTime);
        ~UI() = default;
        UI() = delete;
        UI(UI &&) = delete;
        UI &operator=(UI &&) = delete;
        UI &operator=(const UI &) = delete;

    private:
        void interactiveShell();
        std::shared_ptr<Order> getValidOrder(const std::string &order, const int &orderID) const;
        std::vector<std::string> getSubOrderContents(std::string &subOrder) const;
        Pizza::PizzaType getValidPizzaType(const std::string &pizzaType) const;
        Pizza::PizzaSize getValidPizzaSize(const std::string &pizzaSize) const;
        int getValidPizzaNumber(std::string &pizzaNumber) const;
        bool inputIsAvailable();
        void handleInput();

        float _cookingTime;
        int _cooksNumber;
        int _stockTime;
        std::string _input;
        std::unique_ptr<Reception> _reception;
};

#endif /* !UI_HPP_ */
