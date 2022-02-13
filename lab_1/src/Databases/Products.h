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

	class Products : public CSV::CSVReader<Product>
	{
	public:
		Products(std::string path) : CSV::CSVReader<Product>(path) {};
		Products(std::string path, char c) : CSV::CSVReader<Product>(path, c) {};

		Product* find_by_id(int id)
		{
			if (this->db.empty())
			{
				return nullptr;
			}

			for (size_t i = 0; i < this->db.size(); i++)
			{
				if (this->db[i]->id == id)
				{
					auto a=  this->db[i];
				}
			}

			return nullptr;
		}

		std::vector<Product> find_by_product_type(int id)
		{
			std::vector<Product> list;

			for (size_t i = 0; i < this->db.size(); i++)
			{
				if (this->db[i]->product_type_id == id)
				{
					list.push_back(*this->db[i]);
				}
			}

			return list;
		}

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
