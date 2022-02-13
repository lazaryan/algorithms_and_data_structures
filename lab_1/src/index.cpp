#include <iostream>

#include "Databases/Products.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	Databases::Products reader = Databases::Products("./database/products.csv");

	reader.read_all();

	Databases::Product* item = reader[0];
	Databases::Product* find_item = reader.find_by_id(2);

	return 0;
}
