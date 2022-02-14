#ifndef __DATABASES_SHOPPING__
#define __DATABASES_SHOPPING__

#include <string>
#include <vector>
#include <algorithm>

#include "../CSV/CSVReader.h"

namespace Databases {
	typedef std::vector<int> ShoppingList;

	class Shopping : public CSV::CSVReader<ShoppingList>
	{
	public:
		Shopping(std::string path) : CSV::CSVReader<ShoppingList>(path) {};
		Shopping(std::string path, char c) : CSV::CSVReader<ShoppingList>(path, c) {};

		ShoppingList* find_by_id(int id)
		{
			if (this->db.empty())
			{
				return nullptr;
			}

			return this->db[id];
		}

	private:
		ShoppingList* line_reader(std::vector<std::string> item_1)
		{
			if (item_1.size() != 1) {
				return nullptr;
			}

			size_t position_separator = 0;
			std::string item;
			std::vector<int>* list = new std::vector<int>;

			while ((position_separator = item_1[0].find(';')) != std::string::npos) {
				item = item_1[0].substr(0, position_separator);
				list->push_back(std::stoi(item));
				item_1[0].erase(0, position_separator + 1);
			}

			if (item_1[0].length() > 0)
			{
				list->push_back(std::stoi(item_1[0]));
			}

			return list;
		}
	};
}

#endif // !__DATABASES_SHOPPING__
