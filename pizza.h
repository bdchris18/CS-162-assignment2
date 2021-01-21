#ifndef PIZZA_H
#define PIZZA_H

#include <string>
#include <fstream>

class Pizza {
  private:
    std::string name;
    int small_cost;
    int medium_cost;
    int large_cost;
    int num_ingredients;
    std::string* ingredients;
  public:
    //need to include accessor functions and mutator functions for each private member
    //need to include constructors, copy constructors, assignment operator overload,
    //and destructors where appropriate
    Pizza();
    ~Pizza();
    Pizza* create_pizza(int num_pizzas);
    const std::string& get_name() const;
    void set_name(const std::string name);
    int get_small_cost() const;
    void set_small_cost(const int small_cost);
    int get_medium_cost() const;
    void set_medium_cost(const int medium_cost);
    int get_large_cost() const;
    void set_large_cost(const int large_cost);
    int get_num_ingredients() const;
    void set_num_ingredients(const int num_ingredients);
    void set_ingredients(const std::string ingredient);
    const std::string* get_ingredients() const;
    void create_pizzas();
    //update: you may also name the function like this:
    void populate_pizza_from_input();
    void populate_pizza (std::ifstream& ); // populate date for one pizza
};

std::ostream& operator << (std::ostream& o, const Pizza& p);

#endif