#ifndef __DATABASES_VIEWS__
#define __DATABASES_VIEWS__

#include <string>
#include <algorithm>

#include "../CSV/CSVReader.h"


namespace Databases
{
	struct View
	{
		CSV::item_id_t id;
		CSV::item_id_t user_id;
		CSV::item_id_t movie_id;
	};

	class Views : public CSV::CSVReader<View>
	{
	public:
		Views(std::string path) : CSV::CSVReader<View>(path) {};
		Views(std::string path, CSV::item_id_t user_id) : CSV::CSVReader<View>(path) { this->user_id = user_id; };
		Views(std::string path, char separator) : CSV::CSVReader<View>(path, separator) {};
		Views(std::string path, char separator, CSV::item_id_t user_id) : CSV::CSVReader<View>(path, separator) { this->user_id = user_id; };
	private:
		CSV::item_id_t user_id = INT_MIN;

		View* line_reader(std::vector<std::string> item)
		{
			if (item.size() != 3)
			{
				return nullptr;
			}

			View* new_item = new View
			{
				std::stoi(item[0]),
				std::stoi(item[1]),
				std::stoi(item[2]),
			};

			return new_item;
		}

		CSV::item_id_t get_item_id(View item) { return item.id; }

		bool filter_saving(View item)
		{
			if (this->user_id == INT_MIN) return true;

			return item.user_id == this->user_id;
		}
	};
}

#endif // !__DATABASES_VIEWS__
