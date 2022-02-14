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

		std::vector<double> product_type_statements(this->all_product_types.size());
		const double middle_statement = 1.0f / this->all_product_types.size();
		std::fill(product_type_statements.begin(), product_type_statements.end(), middle_statement);

		this->randomize_product_type = Random::Random<Databases::ProductType>(
			this->all_product_types,
			product_type_statements
		);

		this->randomize_in_the_basket = Random::Random<InTheBasket>(
			std::vector<InTheBasket> { InTheBasket::Yeas, InTheBasket::No },
			std::vector<double> { Tree::probability_of_adding, 1 - Tree::probability_of_adding }
		);

		this->randomize_in_the_add_abstract = Random::Random<InTheBasket>(
			std::vector<InTheBasket> { InTheBasket::Yeas, InTheBasket::No },
			std::vector<double> { Tree::probability_of_abstract_product, 1 - Tree::probability_of_abstract_product }
		);

		this->randomize_count_add_abstract = Random::Random<int>(
			std::vector<int> { 1, 2 },
			std::vector<double> { 0.5f, 0.5f }
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

			int count_abstract_products = 0;

			bool add_abstract_products = false;

			for (std::vector<int>::iterator iter = shopping_list.begin(); iter != shopping_list.end(); iter++)
			{
				if (*iter == -1) {
					add_abstract_products = true;
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

			t_listNodes::iterator first_iter = this->nodes.find(*shopping_list.begin());

			if (first_iter != this->nodes.end())
			{
				first_iter->second->add_abstract_products = add_abstract_products;
			}
		}
	}

	std::vector<Databases::Product> Tree::generate_random_line()
	{
		Databases::ProductType start_product = *this->randomize_product_type.random();
		std::vector<Databases::Product> basket;

		basket.push_back(*this->product_types->random(start_product.id));

		t_listNodes::iterator it_first_node = this->nodes.find(start_product.id);

		if (it_first_node == this->nodes.end())
		{
			return basket;
		}

		TreeNode node = *it_first_node->second;

		this->recursive_generate_basket(&basket, node);

		if (node.add_abstract_products)
		{
			int count_random = *this->randomize_count_add_abstract.random();

			for (int i = 0; i < count_random; i++)
			{
				if (*this->randomize_in_the_add_abstract.random() == InTheBasket::Yeas)
				{
					Databases::ProductType random_product_type = *this->randomize_product_type.random();
					Databases::Product random_product = *this->product_types->random(random_product_type.id);

					basket.push_back(random_product);
				}
			}
		}

		return basket;
	}

	std::vector<std::vector<Databases::Product>> Tree::generate_random_table(int count)
	{
		std::vector<std::vector<Databases::Product>> table;

		for (int i = 0; i < count; i++)
		{
			table.push_back(this->generate_random_line());
		}

		return table;
	}

	void Tree::recursive_generate_basket(std::vector<Databases::Product>* calculate, TreeNode node)
	{
		for (size_t i = 0; i < node.next.size(); i++)
		{
			InTheBasket is_generate = *this->randomize_in_the_basket.random();

			if (is_generate == InTheBasket::No)
			{
				continue;
			}

			Databases::Product random_product = *this->product_types->random(node.next[i]->product.id);

			bool find = false;
			for (int j = 0; j < calculate->size(); j++)
			{
				Databases::Product item = (*calculate)[j];
				if (item.product_type_id == random_product.product_type_id && item.id == random_product.id)
				{
					find = true;
					break;
				}
			}

			if (!find)
			{
				calculate->push_back(random_product);

				this->recursive_generate_basket(calculate, *node.next[i]);
			}
		}
	}
}
