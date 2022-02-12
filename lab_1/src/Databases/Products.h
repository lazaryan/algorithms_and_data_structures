#ifndef __DATABASES_PRODUCTS__
#define __DATABASES_PRODUCTS__

#include <string>

#include "../CSV/CSVReader.h"

namespace Databases {
	struct Product {
		int id;
		int product_type_id;
		std::string name;
		int statement_id;
		double price;
	};

	typedef CSV::CSVReader<Product> BaseClass;

	class Products : public BaseClass
	{
	public:
		Products(std::string path) : BaseClass(path) {};
		Products(std::string path, char c) : BaseClass(path, c) {};

	private:
		Product* line_reader(std::vector<std::string> item)
		{
			if (item.size() != 5) {
				return nullptr;
			}

			Product *new_item = new Product {
				std::stoi(item[0]),
				std::stoi(item[1]),
				item[2],
				std::stoi(item[3]),
				std::atof(item[4].c_str()),
			};

			return new_item;
		}
	};
}

#endif // !__DATABASES_PRODUCTS__
