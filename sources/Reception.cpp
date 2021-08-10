/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Reception
*/

#include "Reception/Reception.hpp"

Reception::Reception(const float &cookingTime, const int &cooksNumber, const int &stockTime)
    : _cookingTime{cookingTime}, _cooksNumber{cooksNumber}, _stockTime{stockTime}, _ordersNumber{0}, _kitchensNumber{0}
{
    std::unique_ptr<IPCMessageQueue> IPCSystem = std::make_unique<IPCMessageQueue>();
    _IPCSystem = std::move(IPCSystem);
}

void Reception::handleNewOrder(std::shared_ptr<Order> newOrder)
{
    // Log in file the new order
    Archive::logInRecord(newOrder->_orderContent);

    // Put the new order in its respective container
    _orders.push_back(newOrder);

    // Fair distribution of each pizza in the most available kitchen
    int mostAvailableKitchen = 0;

    for (int i = 0; i < newOrder->getPizzasNumberInOrder(); i++)
    {
        mostAvailableKitchen = getMostAvailableKitchen();
        // Set number of busy cooks
        _kitchens[mostAvailableKitchen].busyCooks += 1;
        // Send the order to the appropriate kitchen
        try
        {
            _IPCSystem->sendMessageFromReceptionToKitchen(newOrder->pack(i), _kitchens[mostAvailableKitchen].ID);
        }
        catch(const std::exception &error)
        {
            std::cerr << error.what() << std::endl;
        }   
    }
}

void Reception::dumpStatus() const
{
    if (_kitchens.empty())
    {
        std::cout << B_PURPLE "No open kitchen..." DEFAULT << std::endl << std::endl;
    }
    else
    {
        for (const kitchen_t &kitchen : _kitchens)
        {
            std::cout   << B_PURPLE "Kitchen of ID " << kitchen.ID << DEFAULT << std::endl
                        << "\tCurrently " R_PURPLE << kitchen.busyCooks << " pizzas" DEFAULT " are cooking in the kitchen" << std::endl
                        << "\tSo " R_PURPLE << ((kitchen.busyCooks >= _cooksNumber) ? _cooksNumber : kitchen.busyCooks) << " cooks" DEFAULT " out of " << _cooksNumber << " are cooking" << std::endl << std::endl;
        }
    }
}

void Reception::handleCookedPizzas()
{
    int orderID, availableCooks = 0;
    std::string receiveMessage;
    std::vector<int> unpackedMessage;

    closeUnusedKitchens();

    for (kitchen_t &kitchen : _kitchens)
    {
        for (int i = 0; i < kitchen.busyCooks; i++)
        {
            if (_IPCSystem->receiveMessageFromKitchenInReception(kitchen.ID, receiveMessage) > 0)
            {
                unpackedMessage = Order::unpack(receiveMessage);
                orderID = getOrderFromID(unpackedMessage[DoneOrder::ID]);
                _orders[orderID]->removeFromConveyorBelt(static_cast<Pizza::PizzaType> (unpackedMessage[DoneOrder::TYPE]), 
                                                        static_cast<Pizza::PizzaSize> (unpackedMessage[DoneOrder::SIZE]));
                handleDoneOrder(orderID);
                availableCooks += 1;
            }
            receiveMessage.clear();
        }
        // Set kitchen informations 
        if (availableCooks && !(kitchen.busyCooks -= availableCooks))
        {
            kitchen.noOccupancyTime = std::time(0);
        }
        availableCooks = 0;
    }
}

int Reception::getOrderFromID(const int &orderID) const
{
    int orderIndex = 0;

    for (const std::shared_ptr<Order> &order : _orders)
    {
        if (order->_orderID == orderID)
        {
            break;
        }
        orderIndex++;
    }
    return orderIndex;
}

void Reception::handleDoneOrder(const int &orderID)
{
    if (_orders[orderID]->isDoneOrder())
    {
        // Log in file the cooked order
        Archive::logInRecord(_orders[orderID]->_orderContent + " COOKED !");
        // Print the cooked order in the interactive shell
        std::cout   << B_CYAN "Hey, the order number " << _orders[orderID]->_orderID << " "
                    << std::quoted(_orders[orderID]->_orderContent)
                    << " is cooked !" DEFAULT << std::endl;
        _orders.erase(_orders.begin() + orderID);
    }
}

void Reception::openAKitchen()
{
    // Set number of active kitchens
    _kitchensNumber += 1;

    // Initialize kitchen_t structure and put it in its respective container
    kitchen_t newKitchenStructure = {_kitchensNumber, 0, 0, std::time(0), false};
    _kitchens.push_back(newKitchenStructure);

    // Set its IPC MessageQueue
    try
    {
        _IPCSystem->createAKitchenMessageQueue(_kitchensNumber);
    }
    catch(const std::runtime_error &error)
    {
        std::cerr << error.what() << std::endl;
    }

    // Create a child process and instantiating a Kitchen object
    if (fork() == 0)
    {
        Archive::logInRecord("Kitchen number " + std::to_string(_kitchensNumber) + " opens its doors");
        Kitchen newKitchenProcess(_kitchensNumber, _cookingTime, _cooksNumber, _stockTime);
        exit(EXIT_SUCCESS);
    }
    else
    {
        // To ignore the SIGCHLD signal
        signal(SIGCHLD, SIG_IGN);
    }
}

void Reception::closeUnusedKitchens()
{
    // Send closed message to specific kitchens
    for (kitchen_t &kitchen : _kitchens)
    {
        std::time_t rawtime = std::time(0);
        if (ELAPSED_SECONDS(kitchen.noOccupancyTime, rawtime) > CLOSING_TIME 
        && !kitchen.busyCooks 
        && !kitchen.alreadyClosed)
        {
            for (int i = 0; i < _cooksNumber; i++)
            {
                try
                {
                    _IPCSystem->sendMessageFromReceptionToKitchen("Close the kitchen", kitchen.ID);
                }
                catch(const std::exception &error)
                {
                    std::cerr << error.what() << std::endl;
                }
                kitchen.alreadyClosed = true;
            }
        }
    }

    // Receive closed confirmation from specific cooks kitchen
    std::string receiveMessage;

    for (kitchen_t &kitchen : _kitchens)
    {
        if (!kitchen.busyCooks)
        {
            if (_IPCSystem->receiveMessageFromKitchenInReception(kitchen.ID, receiveMessage) > 0 && receiveMessage.compare("Close the kitchen DONE") == 0)
            {
                kitchen.availableCooks += 1;
                receiveMessage.clear();
                continue;
            }
        }
    }

    // Closed confirmed kitchens
    auto i = _kitchens.begin();

    while (i != _kitchens.end())
    {
        if ((*i).availableCooks == _cooksNumber)
        {
            Archive::logInRecord("Kitchen number " + std::to_string((*i).ID) + " closes its doors");
            i = _kitchens.erase(i);
        }
        else
        {
            i++;
        }
    }
}

int Reception::getMostAvailableKitchen()
{
    // Get the the smallest number of busy cooks
    int smallestWorkerNumber = MAX_ORDER_NUMBER(_cooksNumber);

    for (const kitchen_t &kitchen : _kitchens)
    {
        if (!kitchen.alreadyClosed && kitchen.busyCooks < smallestWorkerNumber)
        {
            smallestWorkerNumber = kitchen.busyCooks;
        }
    }

    // Get index of the most available kitchen
    bool mustOpenAKitchen = true;
    int i = 0;

    for (const kitchen_t &kitchen : _kitchens)
    {
        if (kitchen.busyCooks == smallestWorkerNumber)
        {
            smallestWorkerNumber = i;
            mustOpenAKitchen = false;
            break;
        }
        i++;
    }

    return (mustOpenAKitchen) ? openAKitchen(), LAST_KITCHEN(_kitchens.size()) : smallestWorkerNumber;
}
