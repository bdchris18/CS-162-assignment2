#include <iostream>
#include <fstream>
#include <stdio.h>
#include "pizza.h"

Pizza::Pizza(){
    this->name = "";
    this->small_cost = 0;
    this->medium_cost = 0;
    this->large_cost = 0;
    this->num_ingredients = 0;
    this->ingredients = NULL;
}

Pizza::~Pizza(){
    delete [] ingredients;
}

const std::string& Pizza::get_name() const{
    return this->name;
}

void Pizza::set_name(const std::string name){
    this->name = name;
}

int Pizza::get_small_cost() const{
    return this->small_cost;
}

void Pizza::set_small_cost(const int small_cost){
    this->small_cost = small_cost;
}

int Pizza::get_medium_cost() const{
    return this->medium_cost;
}

void Pizza::set_medium_cost(const int medium_cost){
    this->medium_cost = medium_cost;
}

int Pizza::get_large_cost() const{
    return this->large_cost;
}

void Pizza::set_large_cost(const int large_cost){
    this->large_cost = large_cost;
}

int Pizza::get_num_ingredients() const{
    return this->num_ingredients;
}

void Pizza::set_num_ingredients(const int num_ingredients){
    this->num_ingredients = num_ingredients;
}

const std::string* Pizza::get_ingredients() const{
    return this->ingredients;
}

void Pizza::populate_pizza_from_input(){
    std::string name;
    int small = 0;
    int medium = 0;
    int large = 0;
    int num_ingredients = 0;
    std::cout << "Enter pizza name" << std::endl;
    std::cin >> name;
    set_name(name);
    std::cout << "Enter cost of small" << std::endl;
    std::cin >> small;
    set_small_cost(small);
    std::cout << "Enter cost of medium" << std::endl;
    std::cin >> medium;
    set_medium_cost(medium);
    std::cout << "Enter cost of large" << std::endl;
    std::cin >> large;
    set_large_cost(large);
    std::cout << "Enter number of ingredients" << std::endl;
    std::cin >> num_ingredients;
    set_num_ingredients(num_ingredients);
    ingredients = new std::string[num_ingredients];
    for (int i = 0; i < num_ingredients; ++i){
        std::string ingredient;
        std::cout << "Enter ingredient name" << std::endl;
        std::cin >> ingredient;
        ingredients[i] = ingredient;
    }
}

void Pizza::populate_pizza(std::ifstream& p_file){
    std::string name;
    int small = 0;
    int medium = 0;
    int large = 0;
    int num_ingredients = 0;
    p_file >> name;
    set_name(name);
    p_file >> small;
    set_small_cost(small);
    p_file >> medium;
    set_medium_cost(medium);
    p_file >> large;
    set_large_cost(large);
    p_file >> num_ingredients;
    set_num_ingredients(num_ingredients);
    ingredients = new std::string[num_ingredients];
    for (int i = 0; i < num_ingredients; ++i){
        std::string ingredient;
        p_file >> ingredient;
        ingredients[i] = ingredient;
    }
    std::cout << "Finished populating pizza named " << get_name() << " With " << num_ingredients << " ingredients" << std::endl;
}

std::ostream& operator << (std::ostream& o, const Pizza& p){
    o << p.get_name() << " " << p.get_small_cost() << " " << p.get_medium_cost() << " " << p.get_large_cost() << " ";
    for (int n = 0; n < p.get_num_ingredients(); ++n){
        o << p.get_ingredients()[n] << " ";
        if (n != p.get_num_ingredients()-1){
            o << " ";
        }
    };
    return o;
}