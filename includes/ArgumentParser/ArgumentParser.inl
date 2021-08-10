/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** ArgumentParser
*/

inline bool ArgumentParser::isValidNumberOfArguments(const int &argc) const
{
    return (argc == 4) ? true : false;
}

inline bool ArgumentParser::isValidCookingTime(const std::string &cookingTime) const
{
    if (((isFloat(cookingTime) && isBetween(std::stof(cookingTime), 0, 1)) || isInteger(cookingTime)) 
    && !isZero(cookingTime))
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline bool ArgumentParser::isValidCooksNumber(const std::string &cooksNumber) const
{
    return (isZero(cooksNumber) || !isInteger(cooksNumber)) ? false : true;
}

inline bool ArgumentParser::isValidStockTime(const std::string &stockTime) const
{
    return (isZero(stockTime) || !isInteger(stockTime)) ? false : true;
}

inline bool ArgumentParser::isInteger(const std::string &number) const
{
    for (char const &c : number)
    {
        if (!std::isdigit(c))
        {
            return false;
        }
    }
    return true;
}

inline bool ArgumentParser::isZero(const std::string &number) const
{
    return (number.compare("0") == 0) ? true : false;
}

inline bool ArgumentParser::isFloat(const std::string &number) const
{
    try
    {
        std::stof(number);
        for (char const &c : number)
        {
            if (!std::isdigit(c) && c != '.')
            {
                throw std::invalid_argument("Error: number is not a float");
            }
        }
        return true;
    }
    catch(const std::invalid_argument &error)
    {
        return false;
    }
}

inline bool ArgumentParser::isBetween(const float &number, const int &start, const int &end) const
{
    return (start < number && number < end) ? true : false;
}