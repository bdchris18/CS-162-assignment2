#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string>
#include <fstream>
#include "menu.h"
#include "emp_hours.h"

class Restaurant {
  private:
    Menu menu_;
    employee* employees_;
    Hours* week_;
    std::string name_;
    std::string phone_;
    std::string address_;
  public:
    Restaurant();
    Restaurant(const Restaurant& old_res);
    ~Restaurant();
    Restaurant& operator=(const Restaurant& old_res);
    //need to include accessor functions and mutator functions for each private member
    std::string get_restaurant_name();
    void set_restaurant_name(std::string& name);
    std::string get_restaurant_phone();
    void set_restaurant_phone(std::string& phone);
    std::string get_restaurant_address();
    void set_restaurant_address(std::string& address);
    Hours* get_restaurant_hours(const int i) const;
    void set_restaurant_hours(std::ifstream& r_file, const int num_hours);
    //need to include constructors, copy constructors, assignment operator overload,
    //and destructors where appropriate
    void load_data(int& num_employees); //reads from files to correctly populate menu, employees, hours, etc.
    void load_basic_info(std::ifstream& r_file);
    void load_hours(std::ifstream& r_file);
    void fill_employees(int& num_employees);
    void main_login(bool& valid, const int num_employees);
    bool login(int entered_id, std::string& entered_password, const int num_employees);
    void view_menu();
    void view_hours();
    void view_address();
    void view_phone();
    void search_menu_by_price();
    void search_by_ingredients();
    
    // Only one of the following two prototypes should be used:
    // selection is a dynamically allocated array of Pizza objects that are being ordered
    // selection_size indicates the number of Pizza objects in the array
    // num_ordered is a dynamically allocated array that indicates how many pizzas of each type were ordered
    void place_order(Pizza* selection, const int selection_price, const int num_ordered, const int selected_pizza);
    // you may also choose to use this prototype:
    //void place_order(Pizza* selection);
    
    void change_hours();
    void set_hours(Hours* week_, const std::string edited_day, const std::string new_open_hour, const std::string new_close_hour);
    void add_to_menu();
    void remove_from_menu();
    void view_orders();
};

#endif