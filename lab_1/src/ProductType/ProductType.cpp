#include "ProductType.h"

namespace ProductType {
	ProductType::ProductType(
		std::string product_type_bd_path,
		std::string products_bd_path,
		std::string statements_bd_path
	)
	{
		Databases::ProductTypes product_types_bd = Databases::ProductTypes(product_type_bd_path);
		Databases::Products products_bd = Databases::Products(products_bd_path);
		Databases::Statements statements_bd = Databases::Statements(statements_bd_path);

		product_types_bd.read_all();
		products_bd.read_all();
		statements_bd.read_all();

		size_t cout_types = product_types_bd.size();

		for (size_t i = 0; i < cout_types; i++)
		{
			Databases::ProductType product_type = *product_types_bd[i];

			this->product_types.push_back(product_type);

			std::vector<Databases::Product> products = products_bd.find_by_product_type(product_type.id);
			std::vector<double> products_statements;

			for (size_t j = 0; j < products.size(); j++)
			{
				Databases::Statement* item = statements_bd.find_by_id(products[j].statement_id);

				if (item)
				{
					products_statements.push_back(item->probability);
				}
			}

			this->random_map.emplace(
				product_type.id,
				std::make_shared<Random::Random<Databases::Product>>(products, products_statements)
			);
		}
	}

	Databases::Product* ProductType::random(int product_type_id)
	{
		t_sharedRandomMap::iterator it = this->random_map.find(product_type_id);

		if (it == this->random_map.end())
		{
			return nullptr;
		}

		std::shared_ptr<Random::Random<Databases::Product>> item = it->second;

		if (!item)
		{
			return nullptr;
		}

		return item->random();
	}
}