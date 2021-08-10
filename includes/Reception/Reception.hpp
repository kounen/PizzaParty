/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <iomanip>
#include <unistd.h>
#include <signal.h>

#include "Order/Order.hpp"
#include "IPCMessageQueue.hpp"
#include "Kitchen.hpp"
#include "Archive.hpp"
#include "Colours.h"

#define MAX_ORDER_NUMBER(x) (x * 2) - 1
#define ELAPSED_SECONDS(first, last) last - first
#define CLOSING_TIME 5
#define LAST_KITCHEN(x) x - 1

class Reception {
    public:
        Reception(const float &cookingTime, const int &cooksNumber, const int &stockTime);
        ~Reception() = default;
        Reception() = delete;
        Reception(Reception &&) = delete;
        Reception &operator=(Reception &&) = delete;
        Reception &operator=(const Reception &) = delete;

        void handleNewOrder(std::shared_ptr<Order> newOrder);
        void dumpStatus() const;
        void handleCookedPizzas();

        // Inline functions
        int getNewOrderID();
        void removeNewOrder();

    private:
        // Constructor properties
        std::unique_ptr<IPCMessageQueue> _IPCSystem;
        float _cookingTime;
        int _cooksNumber;
        int _stockTime;

        // Order properties
        int _ordersNumber;
        std::vector<std::shared_ptr<Order>> _orders;

        // Kitchen properties
        std::vector<kitchen_t> _kitchens;
        int _kitchensNumber;

        // Order methods
        int getOrderFromID(const int &orderID) const;
        void handleDoneOrder(const int &orderID);

        // Kitchen methods
        void openAKitchen();
        void closeUnusedKitchens();
        int getMostAvailableKitchen();
};

#include "Reception/Reception.inl"

#endif /* !RECEPTION_HPP_ */
