# PizzaParty

![alt text](http://miam-images.m.i.pic.centerblog.net/f050dae0.png)

Realize a simulation of a pizzeria, which is composed of the reception that accepts new commands, of several kitchens, themselves with several cooks, themselves cooking several pizzas.
The following tools were used :
* Processes (man fork, man exit, man wait...).
* Inter-process communication (IPC).
* STL threads.
* POSIX mutex.


<h3>Usage</h3>
<strong>./plazza 2 5 2000</strong>

<h3>Description</h3>
- <em>The first parameter</em> is a multiplier for the cooking time of the pizzas. Moreover this parameter accepts numbers with value in between 0 to 1 to obtain adivisor of the pizzas cooking time.<br>
- <em>The second parameter</em> is the number of cooks per kitchen.<br>
- <em>The third parameter</em> is the time in milliseconds, used by the kitchen stock to replace ingredients.<br>

<h3>Option</h3>
"-h" to display the help page.<br>

##Authors

- [@kounen](https://www.github.com/kounen)
- [@Mehdz](https://www.github.com/Mehdz)
