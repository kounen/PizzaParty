/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** UI
*/

#include "UI.hpp"

UI::UI(const float &cookingTime, const int &cooksNumber, const int &stockTime)
    : _cookingTime{cookingTime}, _cooksNumber{cooksNumber}, _stockTime{stockTime}
{
    std::unique_ptr<Reception> reception = std::make_unique<Reception>(cookingTime, cooksNumber, stockTime);
    _reception = std::move(reception);

    interactiveShell();
}

bool UI::inputIsAvailable()
{
    struct timeval timeout {0, 0};
    fd_set readfds;
    int readyFD;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    readyFD = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);
    switch (readyFD)
    {
    case -1:
        std::cerr << "Error: select" << std::endl;
        return false;
    case 0:
        return false;
    default:
        return (FD_ISSET(STDIN_FILENO, &readfds));
    }
}

void UI::interactiveShell()
{
    std::cout << B_GREEN WELCOME DEFAULT << std::endl << std::endl;
    std::cout << R_BLUE PROMPT DEFAULT << std::endl;
    while (true)
    {
        if (inputIsAvailable())
        {
            getline(std::cin, _input);
            handleInput();
            std::cout << R_BLUE PROMPT DEFAULT << std::endl;
        }
        else
        {
            _reception->handleCookedPizzas();
        }
    }
}

void UI::handleInput()
{
    std::shared_ptr<Order> validOrder;

    if (_input.compare("exit") == 0)
    {
        std::cout << B_GREEN GOODBYE DEFAULT << std::endl;
        exit(EXIT_SUCCESS);
    }
    else if (_input.compare("menu") == 0)
    {
        std::cout << R_YELLOW MENU << std::endl << std::endl;
    }
    else if (_input.compare("status") == 0)
    {
        _reception->dumpStatus();
    }
    else if (_input.empty() || !(validOrder = getValidOrder(_input, _reception->getNewOrderID())))
    {
        std::cerr << R_RED INVALID_ORDER << std::endl << std::endl;
        _reception->removeNewOrder();
    }
    else
    {
        std::cout << R_CYAN NEW_ORDER(validOrder->_orderID) DEFAULT << std::endl << std::endl;
        _reception->handleNewOrder(validOrder);
    }
}

std::shared_ptr<Order> UI::getValidOrder(const std::string &order, const int &orderID) const
{
    std::istringstream subOrderStream(order);
    std::string subOrder;
    std::vector<std::string> subOrderContents;

    auto currentOrder = std::make_shared<Order>(orderID, order);

    Pizza::PizzaType pizzaType = Pizza::PizzaType::UnknownType;
    Pizza::PizzaSize pizzaSize = Pizza::PizzaSize::UnknownSize;
    int pizzaNumber = 0;

    while (std::getline(subOrderStream, subOrder, ';'))
    {
        subOrderContents = getSubOrderContents(subOrder);
        if (subOrderContents.size() != 3
        || !(pizzaType = getValidPizzaType(subOrderContents.at(0)))
        || !(pizzaSize = getValidPizzaSize(subOrderContents.at(1)))
        || !(pizzaNumber = getValidPizzaNumber(subOrderContents.at(2))))
        {
            return nullptr;
        }
        else
        {
            currentOrder->putPizzaOnConveyorBelt(pizzaType, pizzaSize, pizzaNumber);
        }
    }
    return currentOrder;
}

std::vector<std::string> UI::getSubOrderContents(std::string &subOrder) const
{
    std::vector<std::string> subOrderContents;
    std::string content;
    std::istringstream contentStream((subOrder.front() == ' ') ? subOrder.erase(0, 1) : subOrder);

    while (std::getline(contentStream, content, ' '))
    {
        subOrderContents.push_back(content);
    }
    return subOrderContents;
}

Pizza::PizzaType UI::getValidPizzaType(const std::string &pizzaType) const
{
    if (pizzaType.compare("margarita") == 0)
    {
        return Pizza::PizzaType::Margarita;
    }
    else if (pizzaType.compare("regina") == 0)
    {
        return Pizza::PizzaType::Regina;
    }
    else if (pizzaType.compare("americana") == 0)
    {
        return Pizza::PizzaType::Americana;
    }
    else if (pizzaType.compare("fantasia") == 0)
    {
        return Pizza::PizzaType::Fantasia;
    }
    else
    {
        return Pizza::PizzaType::UnknownType;
    }
}

Pizza::PizzaSize UI::getValidPizzaSize(const std::string &pizzaSize) const
{
    if (pizzaSize.compare("S") == 0)
    {
        return Pizza::PizzaSize::S;
    }
    else if (pizzaSize.compare("M") == 0)
    {
        return Pizza::PizzaSize::M;
    }
    else if (pizzaSize.compare("L") == 0)
    {
        return Pizza::PizzaSize::L;
    }
    else if (pizzaSize.compare("XL") == 0)
    {
        return Pizza::PizzaSize::XL;
    }
    else if (pizzaSize.compare("XXL") == 0)
    {
        return Pizza::PizzaSize::XXL;
    }
    else
    {
        return Pizza::PizzaSize::UnknownSize;
    }
}

int UI::getValidPizzaNumber(std::string &pizzaNumber) const
{
    if (pizzaNumber.front() != 'x' || pizzaNumber.length() < 2)
    {
        return false;
    }
    pizzaNumber.erase(0, 1);
    if (pizzaNumber.front() == '0')
    {
        return false;
    }
    for (char const &c : pizzaNumber)
    {
        if (!std::isdigit(c))
        {
            return false;
        }
    }
    return std::stoi(pizzaNumber);
}