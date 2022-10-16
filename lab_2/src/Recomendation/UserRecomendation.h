#ifndef __RECOMENDATION__USER_RECOMENDATION__
#define __RECOMENDATION__USER_RECOMENDATION__

#include <vector>
#include <map>

#include "../Databases/Movies.h"
#include "../Databases/Views.h"

namespace Recomendation
{
	struct Weights {
		float likes;
		float rating;
		float views;
		float genre;
	};

	typedef std::vector<Databases::Movie*> movies_list_t;

	class UserRecomendation
	{
	public:
		UserRecomendation(
			Databases::Movies* movies,
			Databases::Views* views,
			Weights fields_weights
		);

		movies_list_t get_recomandet_movies(size_t count);
	private:
		movies_list_t sorted_movies;
		std::map<CSV::item_id_t, size_t> genres_views_map;

		size_t max_genre_rate = 0;
		size_t max_likes = 0;
		size_t max_views = 0;

		Weights fields_weights { 1.0f, 1.0f, 1.0f, 1.0f };

		movies_list_t sorting_movies(
			CSV::db_map_t<Databases::Movie*> movies
		);

		float get_movie_weight(Databases::Movie item);
	};
}

#endif // !__RECOMENDATION__USER_RECOMENDATION__
