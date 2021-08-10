/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Order
*/

#ifndef ORDER_HPP_
#define ORDER_HPP_

#include <string>

#include "Pizzas/GiveMeAPizza.hpp"
#include "Cook.hpp"

#define DONE_LENGTH 5
#define INFOS_NBR 3
#define XXL_INDEX 5
#define NORMAL_INDEX 4

enum DoneOrder { TYPE, SIZE, ID };

class Order {
    public:
        Order(const int &orderID, const std::string &orderContent);
        ~Order() = default;
        Order() = delete;
        Order(Order &&) = delete;
        Order &operator=(Order &&) = delete;
        Order &operator=(const Order &) = delete;

        // Inline functions
        int getPizzasNumberInOrder() const;
        bool isDoneOrder() const;
        void putPizzaOnConveyorBelt(const Pizza::PizzaType &pizzaType, const Pizza::PizzaSize &pizzaSize, const int &pizzaNumber);
        void removeFromConveyorBelt(const Pizza::PizzaType &pizzaType, const Pizza::PizzaSize &pizzaSize);

        std::string pack(const size_t &pizzaIndex) const;
        static std::vector<int> unpack(std::string &receiveMessage);

        const int _orderID;
        const std::string _orderContent;

    private:
        std::vector<std::unique_ptr<Pizza>> _pizzasConveyorBelt;
};

#include "Order/Order.inl"

#endif /* !ORDER_HPP_ */
