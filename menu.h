#ifndef MENU_H
#define MENU_H 

#include <string>
#include <fstream>
#include "pizza.h"

class Menu {
  private:
    int num_pizzas_;
    Pizza* pizzas;
  public:
    Menu();
    Menu(int new_num_pizzas);
    ~Menu();
    Menu(const Menu& old_menu);
    Menu& operator=(const Menu& old_menu);
    void print_menu();
    //need to include accessor functions and mutator functions for each private member
    void set_num_pizzas(const int num_pizzas);
    int get_num_pizzas();
    Pizza* get_pizzas();
    //need to include constructors, copy constructors, assignment operator overload,
    //and destructors where appropriate
    Menu* create_menu();
    // Only one of the following two prototypes should be used:
    Menu search_pizza_by_cost(int upper_bound);
    //Menu search_pizza_by_cost(int upper_bound, string size);

    Menu search_pizza_by_ingredients_to_include(std::string* ingredients, int num_search_ingredients);
    Menu search_pizza_by_ingredients_to_exclude(std::string* ingredients, int num_search_ingredients);
    void add_to_menu();
    void remove_from_menu(int index_of_pizza_on_menu);
};

#endif