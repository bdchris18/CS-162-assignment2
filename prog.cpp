#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "restaurant.h"

int main(int argc, char *argv[]){
	int choice = 0;
	bool valid = true;
	int status = 0;
	int num_employees = 0;
	int num_ordered = 0;
	int old_num = 0;
	Restaurant r1;
	Menu* orders;
	Pizza* selection;
	r1.load_data(num_employees);
	while (valid){
		std::cout << "Are you a 1) employee or 2) customer?" << std::endl;
		std::cin >> status;
		if (status == 1){
			r1.main_login(valid, num_employees);
			valid = false;	
		}
		else if (status == 2){
			valid = false;
		}
		else{
			valid = true;
		}
	}
	valid = true;
	while (valid){
		std::cout << "what would you like to do?" << std::endl;
		std::cout << "1) View menu" << std::endl;
		if (status == 1){
			std::cout << "2) View orders" << std::endl;
			std::cout << "3) Change hours" << std::endl;
			std::cout << "4) Remove order" << std::endl;
			std::cout << "5) Add item to menu" << std::endl;
			std::cout << "6) Remove item from menu" << std::endl;
			std::cout << "7) View hours" << std::endl;
			std::cout << "8) View address" << std::endl;
			std::cout << "9) View phone" << std::endl;
			std::cout << "10) Quit" << std::endl;
		}
		else if (status == 2){
			std::cout << "2) Search menu by price" << std::endl;
			std::cout << "3) Search menu by ingredients" << std::endl;
			std::cout << "4) Place order" << std::endl;
			std::cout << "5) View hours" << std::endl;
			std::cout << "6) View address" << std::endl;
			std::cout << "7) View phone" << std::endl;
			std::cout << "8) Quit" << std::endl;

		}
		std::cin >> choice;
		if (choice == 1){
			r1.view_menu();
		}
		else if (choice == 2 && status == 1){
			r1.view_orders();
		}
		else if (choice == 3 && status == 1){
			r1.change_hours();
		}
		else if (choice == 2 && status == 2){
			r1.search_menu_by_price();
		}
		else if (choice == 3 && status == 2){
			r1.search_by_ingredients();
		}
		else if (choice == 4 && status == 1){
			r1.add_to_menu();
		}
		else if (choice == 4 && status == 2){
			int selected_pizza = 0;
			int selection_price = 0;
			std::cout << "Enter the index of the pizza you want" << std::endl;
			std::cin >> selected_pizza;
			std::cout << "Enter the size of the pizza 1) small 2) medium 3) large" << std::endl;
			std::cin >> selection_price;
			std::cout << "How many of the selected pizza do you want" << std::endl;
			std::cin >> num_ordered;
			orders = new Menu[old_num + num_ordered];
			old_num = num_ordered + old_num;
			std::cout << "ready to call place order function" << std::endl;
			selection = new Pizza[num_ordered];
			r1.place_order(selection, selection_price, num_ordered, selected_pizza);
			std::ofstream o_file("orders.txt");
			for (int i = 0; i < num_ordered; ++i){
				std::cout << i << std::endl;
				o_file << selection[i].get_name() << " ";
				o_file << selection[i].get_small_cost() << " ";
				o_file << selection[i].get_medium_cost() << " ";
				o_file << selection[i].get_large_cost() << std::endl;
			}
			o_file.close();
			std::cout << "done placing order" << std::endl;
		}
		else if (choice == 5 && status == 1){
			r1.remove_from_menu();
		}
		else if ((choice == 5 && status == 2) || (choice == 6 && status == 1)){
			r1.view_hours();
		}
		else if ((choice == 6 && status == 2) || (choice == 7 && status == 1)){
			r1.view_address();
		}
		else if ((choice == 7 && status == 2) || (choice == 8 && status == 1)){
			r1.view_phone();
		}
		else if ((choice == 8 && status == 2) || (choice == 9 && status == 1)){
			valid = false;
		}
		else{
			std::cout << "Invalid input" << std::endl;
		}
	}
	return 0;
}