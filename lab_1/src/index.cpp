#include <iostream>
#include <string>

#include "CSV/CSVReader.h"

struct Test {
	int id;
	int product_type_id;
	std::string name;
	float price;
};

int main()
{
	CSV::CSVReader<Test> reader("./database/products.csv");

	return 0;
}
