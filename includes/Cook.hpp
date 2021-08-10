/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Cook
*/

#ifndef COOK_HPP_
#define COOK_HPP_

#include <thread>
#include <mutex>

#include "Ingredients/IngredientsStock.hpp"
#include "Pizzas/Pizza.hpp"
#include "IPCMessageQueue.hpp"

#define PIZZA_TYPE 0
#define PIZZA_SIZE 2
#define ORDER_ID 3

#define CHAR(x) x + 48

// Mutex
static std::mutex sendMutex;
static std::mutex receiveMutex;
static std::mutex stockMutex;

// Ingredient stock
static IngredientsStock ingredientsStock;

class Cook {
    public:
        Cook() = delete;
        Cook(const Cook &) = delete;
        Cook(Cook &&) = delete;
        Cook &operator=(Cook &&) = delete;
        Cook &operator=(const Cook &) = delete;
        ~Cook() = delete;

        static std::thread hireACook(const std::pair<mqd_t, mqd_t> &receptionMessageQueueDescriptor, const float &cookingTime, const int &stockTime);
        static Pizza::PizzaType getPizzaTypeFromOrder(const std::string &order);
        static Pizza::PizzaSize getPizzaSizeFromOrder(const std::string &order);

    private:
        static void handleOrder(const std::pair<mqd_t, mqd_t> &receptionMessageQueueDescriptor, const float &cookingTime, const int &stockTime);
        static bool getRequiredIngredients(const Pizza::PizzaType &pizzaType);
        static void cookThePizza(const Pizza::PizzaType &pizzaType, const float &cookingTime);
        static void sendDoneOrder(mqd_t receptionMessageQueueDescriptor, const std::string &order);
};

#endif /* !COOK_HPP_ */
