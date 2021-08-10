/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** GiveMeAPizza
*/

inline std::unique_ptr<Regina> GiveMeAPizza::giveMeARegina(const int &orderID, const Pizza::PizzaSize &pizzaSize)
{
    return std::make_unique<Regina>(orderID, pizzaSize);
}

inline std::unique_ptr<Margarita> GiveMeAPizza::giveMeAMargarita(const int &orderID, const Pizza::PizzaSize &pizzaSize)
{
    return std::make_unique<Margarita>(orderID, pizzaSize);
}

inline std::unique_ptr<Americana> GiveMeAPizza::giveMeAnAmericana(const int &orderID, const Pizza::PizzaSize &pizzaSize)
{
    return std::make_unique<Americana>(orderID, pizzaSize);
}

inline std::unique_ptr<Fantasia> GiveMeAPizza::giveMeAFantasia(const int &orderID, const Pizza::PizzaSize &pizzaSize)
{
    return std::make_unique<Fantasia>(orderID, pizzaSize);
}