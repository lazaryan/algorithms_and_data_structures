#ifndef __TREE_TREE__
#define __TREE_TREE__

#include <string>
#include <vector>
#include <map>

#include "../Databases/ProductTypes.h"
#include "../Databases/Shopping.h"
#include "../ProductType/ProductType.h"
#include "../Random/Random.h"

namespace Tree {
	enum class InTheBasket {
		Yeas,
		No
	};

	struct TreeNode {
		Databases::ProductType product;
		std::vector<TreeNode*> next;
		bool add_abstract_products = false;
	};

	class Tree {
	public:
		static constexpr const double probability_of_adding = 0.8f;
		static constexpr const double probability_of_abstract_product = 0.4f;

		Tree(
			std::string product_type_bd,
			std::string products_bd,
			std::string statements_bd,
			std::string shopping_bd
		);

		void init(std::string shopping_bd);

		std::vector<Databases::Product> generate_random_line();

		std::vector<std::vector<Databases::Product>> generate_random_table(int count);
	private:
		typedef std::map<
			int,
			TreeNode*
		> t_listNodes;

		ProductType::ProductType* product_types;

		std::vector<Databases::ProductType> all_product_types;

		Random::Random<Databases::ProductType> randomize_product_type;
		Random::Random<InTheBasket> randomize_in_the_basket;
		Random::Random<InTheBasket> randomize_in_the_add_abstract;
		Random::Random<int> randomize_count_add_abstract;

		t_listNodes nodes;

		void recursive_generate_basket(std::vector<Databases::Product>* calculate, TreeNode node);
	};
}


#endif // !__TREE_TREE__
