#include <iostream>

#include "Databases/Movies.h"
#include "Databases/Views.h"
#include "Recomendation/UserRecomendation.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	CSV::item_id_t user_id_for_recomendation = 0;
	const size_t recomendet_count = 3;

	Databases::Movies movies("./database/movies.csv");
	Databases::Views views("./database/views.csv", user_id_for_recomendation);

	movies.read_all();
	views.read_all();

	Recomendation::UserRecomendation recomendations(
		&movies,
		&views,
		Recomendation::Weights {
			1.7f,
			1.9f,
			1.4f,
			1.6f
		}
	);

	Recomendation::movies_list_t recomendation_movies = recomendations.get_recomandet_movies(recomendet_count);

	std::cout << "Число рекомендуемых фильмов: " << recomendet_count << std::endl << std::endl;
	std::cout << "Рекомендуемые фильмы:" << std::endl;
	for (int i = 0; i < recomendet_count; i++)
	{
		std::cout << i + 1 << ") " << recomendation_movies[i]->name << std::endl;
	}

	return 0;
}
