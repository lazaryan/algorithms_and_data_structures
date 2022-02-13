#ifndef __ProductType_ProductType__
#define __ProductType_ProductType__

#include <string>
#include <vector>
#include <memory>
#include <map>

#include "../Databases/ProductTypes.h"
#include "../Databases/Products.h"
#include "../Databases/Statements.h"
#include "../Random/Random.h"

namespace ProductType {
	/*
	 * Класс для получения случайного продукта по его типу и работы с типами
	 */
	class ProductType {
	public:
		ProductType(
			std::string product_type_bd,
			std::string products_bd,
			std::string statements_bd
		);

		Databases::Product* random(int product_type_id);
	private:
		typedef std::map<
			int,
			std::shared_ptr<Random::Random<Databases::Product>>
		> t_sharedRandomMap;

		t_sharedRandomMap random_map;

		std::vector<Databases::ProductType> product_types;
	};
}

#endif // !__ProductType_ProductType__
