#include "Tree.h"

namespace Tree {
	Tree::Tree(
		std::string product_type_bd,
		std::string products_bd,
		std::string statements_bd,
		std::string shopping_bd
	)
	{
		this->product_types = new ProductType::ProductType(
			product_type_bd,
			products_bd,
			statements_bd
		);

		this->all_product_types = this->product_types->get_product_types();

		this->randomize_in_the_basket = Random::Random<InTheBasket>(
			std::vector<InTheBasket> { InTheBasket::Yeas, InTheBasket::No },
			std::vector<double> { Tree::probability_of_adding, 1 - Tree::probability_of_adding }
		);

		this->init(shopping_bd);
	}

	void Tree::init(std::string shopping_bd)
	{
		Databases::Shopping shopping = Databases::Shopping(shopping_bd);
		shopping.read_all();

		size_t shopping_count = shopping.size();

		size_t product_types_count = this->all_product_types.size();

		for (size_t i = 0; i < product_types_count; i++)
		{
			this->nodes.emplace(
				this->all_product_types[i].id,
				new TreeNode{ this->all_product_types[i] }
			);
		}

		for (size_t i = 0; i < shopping_count; i++)
		{
			std::vector<int> shopping_list = *shopping[i];

			for (std::vector<int>::iterator iter = shopping_list.begin(); iter != shopping_list.end(); iter++)
			{
				if (*iter == -1) {
					continue;
				}

				t_listNodes::iterator it = this->nodes.find(*iter);

				if (it == this->nodes.end())
				{
					continue;
				}

				for (std::vector<int>::iterator next_iter = ++iter; next_iter != shopping_list.end(); next_iter++)
				{
					if (*next_iter == -1)
					{
						// FIX
						continue;
					}

					t_listNodes::iterator addon_iter = this->nodes.find(*next_iter);

					if (addon_iter != this->nodes.end())
					{
						std::vector<TreeNode*>::iterator if_found_1 = std::find(
							it->second->next.begin(),
							it->second->next.end(),
							addon_iter->second
						);

						if (if_found_1 == it->second->next.end())
						{
							it->second->next.push_back(addon_iter->second);
						}

						std::vector<TreeNode*>::iterator if_found_2 = std::find(
							addon_iter->second->next.begin(),
							addon_iter->second->next.end(),
							it->second
						);

						if (if_found_2 == addon_iter->second->next.end())
						{
							addon_iter->second->next.push_back(it->second);
						}
					}
				}
			}
		}
	}
}
