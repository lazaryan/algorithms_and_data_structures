#include <iostream>

#include "ProductType/ProductType.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	ProductType::ProductType type = ProductType::ProductType(
		"./database/product_types.csv",
		"./database/products.csv",
		"./database/statements.csv"
	);

	for (int i = 0; i < 10; i++)
	{
		auto item = type.random(1);

		if (item)
		{
			std::cout << "RANDOM: " << item->name << std::endl;
		}
	}

	return 0;
}
