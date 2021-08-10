/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Order
*/

inline int Order::getPizzasNumberInOrder() const
{
    return _pizzasConveyorBelt.size();
}

inline bool Order::isDoneOrder() const
{
    return _pizzasConveyorBelt.empty();
}

inline void Order::putPizzaOnConveyorBelt(const Pizza::PizzaType &pizzaType, const Pizza::PizzaSize &pizzaSize, const int &pizzaNumber)
{
    for (int i = 0; i < pizzaNumber; i++)
    {
        _pizzasConveyorBelt.push_back(GiveMeAPizza::giveMeAPizza(_orderID, pizzaType, pizzaSize));
    }
}

inline void Order::removeFromConveyorBelt(const Pizza::PizzaType &pizzaType, const Pizza::PizzaSize &pizzaSize)
{
    int i = 0;

    for (const std::unique_ptr<Pizza> &pizza : _pizzasConveyorBelt)
    {
        if (pizza->_pizzaType == pizzaType && pizza->_pizzaSize == pizzaSize)
        {
            _pizzasConveyorBelt.erase(_pizzasConveyorBelt.begin() + i);
            break;
        }
        i++;
    }
}