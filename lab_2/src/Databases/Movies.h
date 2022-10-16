#ifndef __DATABASES_MOVIES__
#define __DATABASES_MOVIES__

#include <string>
#include <algorithm>

#include "../CSV/CSVReader.h"

namespace Databases
{
	struct Movie
	{
		CSV::item_id_t id;
		std::string name;
		CSV::item_id_t genre_id;
		int count_views;
		int count_likes;
		float raiting;
	};

	class Movies : public CSV::CSVReader<Movie>
	{
	public:
		Movies(std::string path) : CSV::CSVReader<Movie>(path) {};
		Movies(std::string path, char separator) : CSV::CSVReader<Movie>(path, separator) {};
	private:
		Movie* line_reader(std::vector<std::string> item)
		{
			if (item.size() != 6)
			{
				return nullptr;
			}

			Movie* new_item = new Movie
			{
				std::stoi(item[0]),
				item[1],
				std::stoi(item[2]),
				std::stoi(item[3]),
				std::stoi(item[4]),
				std::stof(item[5]),
			};

			return new_item;
		}

		CSV::item_id_t get_item_id(Movie item) { return item.id; }
	};
}

#endif // !__DATABASES_MOVIES__
