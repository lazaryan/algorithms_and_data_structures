#include <iostream>

#include "Tree/Tree.h"
#include "CSV/CSVWritter.h"

int main()
{
	Tree::Tree tree = Tree::Tree(
		"./database/product_types.csv",
		"./database/products.csv",
		"./database/statements.csv",
		"./database/shopping.csv"
	);

	CSV::CSVWriter out_writter = CSV::CSVWriter("./out.csv");

	if (!out_writter.is_open())
	{
		throw "ERROR OPEN File for saving";
	}

	const int size = 200;

	Tree::Tree::t_receipts receipts_table = tree.generate_random_receipts(size);

	std::vector<std::string> headers;
	std::vector<std::vector<std::string>> receipts(size);

	int sum_count_products = 0;
	int sum_price_receipts = 0;

	for (Tree::Tree::t_receipts::iterator it = receipts_table.begin(); it != receipts_table.end(); ++it)
	{
		headers.push_back(it->first);

		bool isPrice = it->first == "Price";

		std::vector<int> counts = it->second;

		for (int j = 0; j < size; j++)
		{
			receipts[j].push_back(std::to_string(counts[j]));

			if (isPrice)
			{
				sum_price_receipts += counts[j];
			}
			else
			{
				sum_count_products += counts[j];
			}
		}
	}

	out_writter.write_line(headers);

	for (int i = 0; i < size; i++)
	{
		out_writter.write_line(receipts[i]);
	}

	std::cout << "COUNT: " << size << std::endl;
	std::cout << "MIDDLE COUNT PRODUCTS: " << sum_count_products / size << std::endl;
	std::cout << "MIDDLE PRICE: " << (double)sum_price_receipts / size << std::endl;

	return 0;
}
