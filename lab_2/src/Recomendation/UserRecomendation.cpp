#include "./UserRecomendation.h"

Recomendation::UserRecomendation::UserRecomendation(
	Databases::Movies* movies,
	Databases::Views* views,
	Weights fields_weights
)
{
	CSV::db_map_t<Databases::Movie*> movies_map = movies->get_data();
	CSV::db_map_t<Databases::View*> views_map = views->get_data();

	this->fields_weights = fields_weights;

	for (const auto& [key, value] : views_map)
	{
		CSV::item_id_t movie_id = value->movie_id;
		if (!movies_map.count(movie_id)) continue;

		Databases::Movie* movie = movies_map.at(movie_id);
		CSV::item_id_t genre_id = movie->genre_id;

		if (!this->genres_views_map.count(genre_id))
		{
			this->genres_views_map.emplace(genre_id, 1);

			if (this->max_genre_rate < 1) this->max_genre_rate = 1;
		}
		else
		{
			size_t count_genre_views = this->genres_views_map.at(genre_id);
			if (this->max_genre_rate < count_genre_views + 1) this->max_genre_rate = count_genre_views + 1;
			this->genres_views_map.at(genre_id)++;
		}

		if (this->max_likes < movie->count_likes) this->max_likes = movie->count_likes;
		if (this->max_views < movie->count_views) this->max_views = movie->count_views;

		movies_map.erase(key);
	}

	this->sorted_movies = this->sorting_movies(movies_map);
}

Recomendation::movies_list_t Recomendation::UserRecomendation::get_recomandet_movies(size_t count)
{
	size_t count_movies = this->sorted_movies.size();
	size_t slised_count = std::min(count, count_movies);

	auto link_1 = this->sorted_movies.cbegin();
	auto link_2 = this->sorted_movies.cbegin() + slised_count;

	Recomendation::movies_list_t slised_list(link_1, link_2);
	return slised_list;
}

float Recomendation::UserRecomendation::get_movie_weight(Databases::Movie movie)
{
	float weight = 0.0f;

	weight += ((float)movie.count_likes / this->max_likes) * this->fields_weights.likes;
	weight += ((float)movie.raiting / 5) * this->fields_weights.rating;
	weight += ((float)movie.count_views / this->max_views) * this->fields_weights.views;
	weight += (
		(this->genres_views_map.count(movie.genre_id) ? this->genres_views_map.at(movie.genre_id) : 0) / this->max_genre_rate
	) * this->fields_weights.genre;

	return weight;
}

Recomendation::movies_list_t Recomendation::UserRecomendation::sorting_movies(
	CSV::db_map_t<Databases::Movie*> movies
)
{
	std::vector<Databases::Movie*> sorted_movies;
	std::transform(
		movies.begin(), movies.end(),
		std::back_inserter(sorted_movies),
		[](const std::pair<CSV::item_id_t, Databases::Movie*>& p) { return p.second; }
	);
	std::sort(
		sorted_movies.begin(),
		sorted_movies.end(),
		[this](Databases::Movie* item1, Databases::Movie* item2) {
			float weight_item_1 = this->get_movie_weight(*item1);
			float weight_item_2 = this->get_movie_weight(*item2);

			return weight_item_1 > weight_item_2;
		}
	);

	return sorted_movies;
}
