/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Cook
*/

#include "Cook.hpp"

std::thread Cook::hireACook(const std::pair<mqd_t, mqd_t> &receptionMessageQueueDescriptor, const float &cookingTime, const int &stockTime)
{
    std::thread newbie(handleOrder, receptionMessageQueueDescriptor, cookingTime, stockTime);
    return newbie;
}

void Cook::handleOrder(const std::pair<mqd_t, mqd_t> &receptionMessageQueueDescriptor, const float &cookingTime, const int &stockTime)
{
    std::string receiveMessage;

    ingredientsStock.setStockTime(stockTime);

    while (true)
    {
        // Lock server queue data
        receiveMutex.lock();
        try
        {
            IPCMessageQueue::receiveMessageFromReceptionInKitchen(receptionMessageQueueDescriptor.first, receiveMessage);
        }
        catch(const std::out_of_range &error)
        {
            std::cerr << error.what() << std::endl;
        }
        // Unlock server queue data
        receiveMutex.unlock();

        // Close the kitchen and then its cooks
        if (receiveMessage.compare("Close the kitchen") == 0)
        {
            sendDoneOrder(receptionMessageQueueDescriptor.second, receiveMessage);
            break;
        }

        // Pick up required ingredients and convey cooked pizza to Reception
        while (!getRequiredIngredients(getPizzaTypeFromOrder(receiveMessage)));
        cookThePizza(getPizzaTypeFromOrder(receiveMessage), cookingTime);
        sendDoneOrder(receptionMessageQueueDescriptor.second, receiveMessage);
    }
}

Pizza::PizzaType Cook::getPizzaTypeFromOrder(const std::string &order)
{
    switch (order[PIZZA_TYPE])
    {
    case CHAR(Pizza::PizzaType::Regina):
        return Pizza::PizzaType::Regina;
    case CHAR(Pizza::PizzaType::Margarita):
        return Pizza::PizzaType::Margarita;
    case CHAR(Pizza::PizzaType::Americana):
        return Pizza::PizzaType::Americana;
    case CHAR(Pizza::PizzaType::Fantasia):
        return Pizza::PizzaType::Fantasia;
    }
    return Pizza::PizzaType::UnknownType;
}

Pizza::PizzaSize Cook::getPizzaSizeFromOrder(const std::string &order)
{
    switch (order[PIZZA_SIZE])
    {
    case CHAR(Pizza::PizzaSize::S):
        return (isdigit(order[ORDER_ID])) ? Pizza::PizzaSize::XXL : Pizza::PizzaSize::S;
    case CHAR(Pizza::PizzaSize::M):
        return Pizza::PizzaSize::M;
    case CHAR(Pizza::PizzaSize::L):
        return Pizza::PizzaSize::L;
    case CHAR(Pizza::PizzaSize::XL):
        return Pizza::PizzaSize::XL;
    }
    return Pizza::PizzaSize::UnknownSize;
}

bool Cook::getRequiredIngredients(const Pizza::PizzaType &pizzaType)
{
    bool isEnoughStock = false;

    // Lock stock data
    stockMutex.lock();
    ingredientsStock.timeToStockUpIngredients();
    isEnoughStock = ingredientsStock.destockIngredients(pizzaType);
    // Unlock stock data
    stockMutex.unlock();

    return isEnoughStock;
}

void Cook::cookThePizza(const Pizza::PizzaType &pizzaType, const float &cookingTime)
{
    int milliseconds_time = 0;

    switch (pizzaType)
    {
    case Pizza::PizzaType::Margarita:
        milliseconds_time = Pizza::PizzaCookingTime::OneSecond * cookingTime;
        break;
    case Pizza::PizzaType::Regina:
        milliseconds_time = Pizza::PizzaCookingTime::TwoSeconds * cookingTime;
        break;
    case Pizza::PizzaType::Americana:
        milliseconds_time = Pizza::PizzaCookingTime::TwoSeconds * cookingTime;
        break;
    case Pizza::PizzaType::Fantasia:
        milliseconds_time = Pizza::PizzaCookingTime::FourSeconds * cookingTime;
        break;
    default:
        break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_time));
}

void Cook::sendDoneOrder(mqd_t receptionMessageQueueDescriptor, const std::string &order)
{
    // Lock client queue data
    sendMutex.lock();
    try
    {
        std::string message(order + " DONE");
        IPCMessageQueue::sendMessageFromKitchenToReception(message, receptionMessageQueueDescriptor);
    }
    catch(const std::runtime_error &error)
    {
        std::cerr << error.what() << std::endl;
    }
    // Unlock client queue data
    sendMutex.unlock();
}
