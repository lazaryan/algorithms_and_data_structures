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
	enum InTheBasket {
		Yeas,
		No
	};

	struct TreeNode {
		Databases::ProductType product;
		std::vector<TreeNode*> next;
	};

	class Tree {
	public:
		static constexpr const double probability_of_adding = 0.8f;

		Tree(
			std::string product_type_bd,
			std::string products_bd,
			std::string statements_bd,
			std::string shopping_bd
		);

		void init(std::string shopping_bd);
	private:
		typedef std::map<
			int,
			TreeNode*
		> t_listNodes;

		ProductType::ProductType* product_types;

		std::vector<Databases::ProductType> all_product_types;

		Random::Random<InTheBasket> randomize_in_the_basket;

		t_listNodes nodes;
	};
}


#endif // !__TREE_TREE__
