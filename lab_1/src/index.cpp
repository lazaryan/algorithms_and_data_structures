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

	return 0;
}
