#include <iostream>
#include "pizza.h"
#include "menu.h"

Menu::Menu(){
    std::cout << "menu default constructor called" << std::endl;
    this->num_pizzas_ = 0;
    this->pizzas = NULL;
}

Menu::Menu(int new_num_pizzas){
    std::cout << "non default constructor called" << std::endl;
    this->num_pizzas_ = new_num_pizzas;
    this->pizzas = NULL;
}

Menu::~Menu(){
    delete [] pizzas;
}

Menu::Menu(const Menu& old_menu){
    this->num_pizzas_ = old_menu.num_pizzas_;
    this->pizzas = new Pizza[old_menu.num_pizzas_];
    for (int i = 0; i < this->num_pizzas_; ++i){
        this->pizzas[i] = old_menu.pizzas[i];
    }
}

Menu& Menu::operator=(const Menu& old_menu){
    if(this != &old_menu){
        this->num_pizzas_ = old_menu.num_pizzas_;

        if (this->pizzas != NULL){
            for (int i = 0; i < pizzas->get_num_ingredients(); ++i){
                delete [] this->pizzas[i].get_ingredients();
            }
            delete [] this->pizzas;
        }

        this->pizzas = new Pizza[old_menu.num_pizzas_];
        for (int i = 0; i < this->num_pizzas_; ++i){
            this->pizzas[i] = old_menu.pizzas[i];
        }
    }
}

void Menu::print_menu(){
    std::cout << num_pizzas_ << " " << get_num_pizzas() << std::endl;
    for (int i = 0; i < num_pizzas_; ++i){
        std::cout << i << std::endl;
        std::cout << pizzas[i].get_name() << " " << pizzas[i].get_small_cost() << " " << pizzas[i].get_medium_cost() << " " << pizzas[i].get_large_cost() << " ";
        for (int n = 0; n < pizzas[i].get_num_ingredients(); ++n){
            std::cout << pizzas[i].get_ingredients()[n] << " " << std::endl;
        }
    }
}

void Menu::set_num_pizzas(const int num_pizzas){
    this->num_pizzas_ = num_pizzas;
}

int Menu::get_num_pizzas(){
    return this->num_pizzas_;
}

Pizza* Menu::get_pizzas(){
    return this->pizzas;
}

Menu* Menu::create_menu(){
    int count = 0;
    std::string f;
    std::ifstream p_file("menu.txt");
    while(!p_file.eof()){
        std::getline(p_file, f);
        count++;
    }
    set_num_pizzas(count);
    p_file.close();
    p_file.open("menu.txt");
    pizzas = new Pizza[count];
    for (int i = 0; i < get_num_pizzas(); ++i){
        pizzas[i].populate_pizza(p_file);
    }
}

Menu Menu::search_pizza_by_cost(int upper_bound){
    for (int i = 0; i < get_num_pizzas(); ++i){
        if (pizzas[i].get_large_cost() < upper_bound){
            std::cout << pizzas[i].get_name() << " " << pizzas[i].get_small_cost() << " " << pizzas[i].get_medium_cost() << " " << pizzas[i].get_large_cost() << " ";
            for (int n = 0; n < pizzas[i].get_num_ingredients(); ++n){
                std::cout << pizzas[i].get_ingredients()[n] << " ";
            }
        }
        else if (pizzas[i].get_medium_cost() < upper_bound){
            std::cout << pizzas[i].get_name() << " " << pizzas[i].get_small_cost() << " " << pizzas[i].get_medium_cost() << " ";
            for (int n = 0; n < pizzas[i].get_num_ingredients(); ++n){
                std::cout << pizzas[i].get_ingredients()[n] << " ";
            }
        }
        else if (pizzas[i].get_small_cost() < upper_bound){
            std::cout << pizzas[i].get_name() << " " << pizzas[i].get_small_cost() << " ";
            for (int n = 0; n < pizzas[i].get_num_ingredients(); ++n){
                std::cout << pizzas[i].get_ingredients()[n] << " ";
            }
        }
        std::cout << std::endl;
    }
}

Menu Menu::search_pizza_by_ingredients_to_exclude(std::string* search_ingredients, int num_search_ingredients){
    Menu new_menu;
    int new_pizza_index = 0;
    new_menu.set_num_pizzas(num_pizzas_);
    new_menu.pizzas = new Pizza[num_pizzas_];
    for (int i = 0; i < num_pizzas_; ++i){
        int num_excluded = 0; 
        for (int j = 0; j < pizzas[i].get_num_ingredients(); ++j){
            for (int k = 0; k < num_search_ingredients; ++k){
                if (search_ingredients[k] == pizzas[i].get_ingredients()[j]){
                    num_excluded++;
                    break;
                }
                if(num_excluded > 0) break;
            }
            if(num_excluded > 0) break;
        }
        if (num_excluded > 0) continue;
        new_menu.pizzas[new_pizza_index] = pizzas[new_pizza_index];
        ++new_pizza_index;
        
        std::cout << std::endl;
    }
    for (int i = 0; i < new_pizza_index; ++i){
        std::cout << "Pizza " << i << " " << new_menu.pizzas[i] << std::endl;
    }
    return new_menu;
}

Menu Menu::search_pizza_by_ingredients_to_include(std::string* search_ingredients, int num_search_ingredients){
    Menu new_menu;
    int new_pizza_index = 0;
    new_menu.set_num_pizzas(num_pizzas_);
    new_menu.pizzas = new Pizza[num_pizzas_];
    for (int i = 0; i < num_pizzas_; ++i){
        int num_included = 0; 
        for (int j = 0; j < pizzas[i].get_num_ingredients(); ++j){
            for (int k = 0; k < num_search_ingredients; ++k){
                if (search_ingredients[k] == pizzas[i].get_ingredients()[j]){
                    num_included++;
                    break;
                }
                if(num_included > 0) break;
            }
            if(num_included > 0) break;
        }
        if (num_included == 0) continue;
        new_menu.pizzas[new_pizza_index] = pizzas[new_pizza_index];
        ++new_pizza_index;
        std::cout << std::endl;
    }
    for (int i = 0; i < new_pizza_index; ++i){
        std::cout << "Pizza " << i << " " << new_menu.pizzas[i] << std::endl;
    }
    return new_menu;
}

void Menu::add_to_menu(){
    Pizza* new_pizzas = new Pizza[get_num_pizzas()+1];
    for (int i = 0; i < get_num_pizzas(); ++i){
        new_pizzas[i] = pizzas[i];
    }
    delete [] pizzas;
    pizzas = new_pizzas;
    set_num_pizzas(get_num_pizzas()+1);

    Pizza& new_pizza = pizzas[get_num_pizzas()-1];
    new_pizza.populate_pizza_from_input();
}

void Menu::remove_from_menu(int index_of_pizza_on_menu){
    Pizza* new_pizzas = new Pizza[get_num_pizzas()-1];
    for (int i = 0; i < index_of_pizza_on_menu; ++i){
        new_pizzas[i] = pizzas[i];
    }
    for (int i = index_of_pizza_on_menu; i < get_num_pizzas()-1; ++i){
        new_pizzas[i] = pizzas[i+1];
    }
    delete [] pizzas;
    pizzas = new_pizzas;
    set_num_pizzas(get_num_pizzas()-1);

    Pizza& new_pizza = pizzas[get_num_pizzas()-1];
}