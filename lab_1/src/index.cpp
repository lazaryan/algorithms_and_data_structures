#include <iostream>

#include "Databases/Products.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	Databases::Products reader = Databases::Products("./database/products.csv");

	reader.read_all();

	Databases::Product* item = reader[0];

	return 0;
}
