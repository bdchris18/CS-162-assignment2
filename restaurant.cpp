#include <iostream>
#include <cstdlib>
#include "restaurant.h"
#include "emp_hours.h"

Restaurant::Restaurant(){
    std::cout << "restaurant default constructor called" << std::endl;
    this->employees_ = NULL;
    this->week_ = NULL;
    this->name_ = "";
    this->phone_ = "";
    this->address_ = "";
}

Restaurant::~Restaurant(){
    std::cout << "deconstructor called" << std::endl;
    delete [] week_; 
    delete [] employees_; 
}

Restaurant::Restaurant(const Restaurant& old_res){
    std::cout << "copy constructor called" << std::endl;
    this->name_ = old_res.name_;
    this->phone_ = old_res.phone_;
    this->address_ = old_res.address_;
    this->week_ = new Hours[7];
    for (int i = 0; i < 7; ++i){
        this->week_[i] = old_res.week_[i];
    }
}

Restaurant& Restaurant::operator=(const Restaurant& old_res){
    std::cout << "operator overload called" << std::endl;
    if (this != &old_res){
        this->name_ = old_res.name_;
        this->phone_ = old_res.phone_;
        this->address_ = old_res.address_;

        if (this->week_ != NULL){
            delete [] this->week_;
        }
        this->week_ = new Hours[7];
        for (int i = 0; i < 7; ++i){
            this->week_[i] = old_res.week_[i];
        }
    }
    return *this;
}

void Restaurant::load_data(int& num_employees){
    std::ifstream r_file;
    r_file.open("restaurant_info.txt");
    load_basic_info(r_file);
    load_hours(r_file);
    fill_employees(num_employees);
    r_file.close();
    menu_.create_menu();
}

void Restaurant::load_basic_info(std::ifstream& r_file){
    std::string r_name;
    std::string r_phone;
    std::string r_address;

	std::getline(r_file, r_name);
    std::getline(r_file, r_phone);
    std::getline(r_file, r_address);

    set_restaurant_name(r_name);
    set_restaurant_phone(r_phone);
    set_restaurant_address(r_address);
}

void Restaurant::load_hours(std::ifstream& r_file){
    int num_days = 0;
    std::string temp;
    int line = r_file.tellg();
    Hours* week;
    while(!r_file.eof()){
        std::getline(r_file, temp);
        num_days++;
    }
    r_file.seekg(line);
    set_restaurant_hours(r_file, num_days);
}

std::string Restaurant::get_restaurant_name(){
    return this->name_;
}

void Restaurant::set_restaurant_name(std::string& name){
    this->name_ = name;
}

std::string Restaurant::get_restaurant_phone(){
    return this->phone_;
}

void Restaurant::set_restaurant_phone(std::string& phone){
    this->phone_ = phone;
}

std::string Restaurant::get_restaurant_address(){
    return this->address_;
}

void Restaurant::set_restaurant_address(std::string& address){
    this->address_ = address;
}

Hours* Restaurant::get_restaurant_hours(const int i) const{
    return &(week_[i]);
}

void Restaurant::set_restaurant_hours(std::ifstream& r_file, const int num_days){
    week_ = new Hours[num_days];
    for (int i = 0; i < num_days; ++i){
        r_file >> week_[i].day;
        r_file >> week_[i].open_hour;
        r_file >> week_[i].close_hour;
    }
}

void Restaurant::fill_employees(int& num_employees){
    std::string temp;
    std::string temp2;
    std::ifstream e_file;
    e_file.open("employee.txt");
    while(!e_file.eof()){
        std::getline(e_file, temp);
        num_employees++;
    }
    employees_ = new employee[num_employees];
    e_file.seekg(0);
    for (int i = 0; i < num_employees; ++i){
        e_file >> employees_[i].id;
        e_file >> employees_[i].password;
        e_file >> employees_[i].first_name;
        e_file >> employees_[i].last_name;
    }
}

void Restaurant::main_login(bool& valid,const int num_employees){
    int id = 0;
	valid = true;
	std::string password;
    while(valid){
		std::cout << "Please enter id:" << std::endl;
		std::cin >> id;
		std::cout << "Please enter password:" << std::endl;
		std::cin >> password; 
		valid = login(id, password, num_employees);
	}
    
}

bool Restaurant::login(int entered_id, std::string& entered_password, const int num_employees){
    for (int i = 0; i < num_employees; ++i){
        if (employees_[i].id == entered_id && employees_[i].password == entered_password){
            return false;
        }
    }
    return true;
}

void Restaurant::view_menu(){
    menu_.print_menu();
}

void Restaurant::view_hours(){
    for (int i = 0; i < 7; ++i){
        std::cout << week_[i].day << " " << week_[i].open_hour << " " << week_[i].close_hour << std::endl;
    }
}

void Restaurant::view_address(){
    std::cout << get_restaurant_address() << std::endl;
}

void Restaurant::view_phone(){
    std::cout << get_restaurant_phone() << std::endl;
}

void Restaurant::search_menu_by_price(){
    int upper_bound = 0;
    std::cout << "Enter your budget" << std::endl;
    std::cin >> upper_bound;
    menu_.search_pizza_by_cost(upper_bound);
}

void Restaurant::search_by_ingredients(){
    int choice = 0;
    int index = 0;
    int num_search_ingredients = 1;
    bool valid = true;
    std::string* search_ingredients = new std::string[num_search_ingredients];
    std::cout << "would you like to search by 1) excluding ingredients or 2) including?" << std::endl;
    std::cin >> choice;
    if (choice == 1){
        while(valid){
            if (index >= 1){
                const int previous_num_search_ingredients = num_search_ingredients;
                ++num_search_ingredients;
                std::string* new_search_ingredients = new std::string[num_search_ingredients];
                for (int i = 0; i < previous_num_search_ingredients; ++i){
                    new_search_ingredients[i] = search_ingredients[i];
                }
                delete [] search_ingredients;
                search_ingredients = new_search_ingredients;
            }
            std::cout << "Enter an ingredient to exclude" << std::endl;
            std::cin >> search_ingredients[index];
            std::cout << "Would you like to exclude another? 1) yes, 2) no" << std::endl;
            int more_ingredients = 0;
            std::cin >> more_ingredients;
            if (more_ingredients == 2){
                break;
            }
            else{
                ++index;
            }
        }
        menu_.search_pizza_by_ingredients_to_exclude(search_ingredients, num_search_ingredients);
        delete [] search_ingredients;
        
    }
    else if (choice == 2){
        while(valid){
            if (index >= 1){
                const int previous_num_search_ingredients = num_search_ingredients;
                ++num_search_ingredients;
                std::string* new_search_ingredients = new std::string[num_search_ingredients];
                for (int i = 0; i < previous_num_search_ingredients; ++i){
                    new_search_ingredients[i] = search_ingredients[i];
                }
                delete [] search_ingredients;
                search_ingredients = new_search_ingredients;
            }
            std::cout << "Enter an ingredient to include" << std::endl;
            std::cin >> search_ingredients[index];
            std::cout << "Would you like to include another? 1) yes, 2) no" << std::endl;
            int more_ingredients = 0;
            std::cin >> more_ingredients;
            if (more_ingredients == 2){
                break;
            }
            else{
                ++index;
            }
        }
        menu_.search_pizza_by_ingredients_to_include(search_ingredients, num_search_ingredients);
        delete [] search_ingredients;
    }
}

void Restaurant::place_order(Pizza* selection, const int selection_price, const int num_ordered, const int selected_pizza){
    for (int pizza_index = 0; pizza_index < menu_.get_num_pizzas(); ++pizza_index){
        if (pizza_index == selected_pizza){
            for (int n = 0; n < num_ordered; ++n){
                selection[n] = menu_.get_pizzas()[pizza_index];
                if(selection_price == 1){
                    selection[n].set_medium_cost(0);
                    selection[n].set_large_cost(0);
                }
                else if (selection_price == 2){
                    selection[n].set_small_cost(0);
                    selection[n].set_large_cost(0);
                }
                else if (selection_price == 3){
                    selection[n].set_small_cost(0);
                    selection[n].set_medium_cost(0);
                }
            }
        }
    }
}

void Restaurant::change_hours(){
    std::string edited_day;
    std::string new_open_hour;
    std::string new_close_hour;
    std::cout << "Enter the day to edit" << std::endl;
    std::cin >> edited_day;
    std::cout << "Enter a new opening hour" << std::endl;
    std::cin >> new_open_hour;
    std::cout << "Enter a new closing hour" << std::endl;
    std::cin >> new_close_hour;
    set_hours(week_, edited_day, new_open_hour, new_close_hour);
}

void Restaurant::set_hours(Hours* week_, const std::string edited_day, const std::string new_open_hour, const std::string new_close_hour){
    for (int i = 0; i < 7; ++i){
        std::cout << "no seg" << std::endl;
        if (edited_day == this->week_[i].day){
            this->week_[i].open_hour = new_open_hour;
            this->week_[i].close_hour = new_close_hour;
        }
    }
}

void Restaurant::add_to_menu(){
    menu_.add_to_menu();
}

void Restaurant::remove_from_menu(){
    int index_of_pizza_on_menu = 0;
    std::cout << "What pizza would you like to remove?" << std::endl;
    std::cin >> index_of_pizza_on_menu;
    menu_.remove_from_menu(index_of_pizza_on_menu);
}

void Restaurant::view_orders(){
    std::string name;
    int small = 0;
    int medium = 0;
    int large = 0;
    int count = 0;
    std::string temp;
    std::ifstream o_file("orders.txt");
    while(!o_file.eof()){
        std::getline(o_file, temp);
        count++;
    }
    for (int i = 0; i < count; ++i){
        o_file >> name;
        std::cout << name << " ";
        o_file >> small;
        std::cout << small << " ";
        o_file >> medium;
        std::cout << medium << " ";
        o_file >> large;
        std::cout << large << " ";
    }
    o_file.close();
}