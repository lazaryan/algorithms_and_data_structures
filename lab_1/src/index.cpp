#include <iostream>

#include "Tree/Tree.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	Tree::Tree tree = Tree::Tree(
		"./database/product_types.csv",
		"./database/products.csv",
		"./database/statements.csv",
		"./database/shopping.csv"
	);

	auto a = tree.generate_random_table(50);

	return 0;
}
