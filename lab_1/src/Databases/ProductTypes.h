#ifndef __DATABASES_PRODUCT_TYPES__
#define __DATABASES_PRODUCT_TYPES__

#include <string>

#include "../CSV/CSVReader.h"

namespace Databases {
	struct ProductType {
		int id;
		std::string title;
	};

	typedef CSV::CSVReader<ProductType> BaseClass;

	class ProductTypes : public BaseClass
	{
	public:
		ProductTypes(std::string path) : BaseClass(path) {};
		ProductTypes(std::string path, char c) : BaseClass(path, c) {};

		ProductType* find_by_id(int id)
		{
			if (this->db.size() == 0)
			{
				return nullptr;
			}

			for (size_t i = 0; i < this->db.size(); i++)
			{
				if (this->db[i]->id == id)
				{
					return this->db[i];
				}
			}

			return nullptr;
		}

	private:
		ProductType* line_reader(std::vector<std::string> item)
		{
			if (item.size() != 2) {
				return nullptr;
			}

			ProductType* new_item = new ProductType {
				std::stoi(item[0]),
				item[1],
			};

			return new_item;
		}
	};
}

#endif // !__DATABASES_PRODUCT_TYPES__
