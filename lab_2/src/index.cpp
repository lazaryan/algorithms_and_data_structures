#include "Databases/Movies.h"
#include "Databases/Views.h"

int main()
{
	CSV::item_id_t user_id_for_recomendation = 0;

	Databases::Movies movies("./database/movies.csv");
	Databases::Views views("./database/views.csv", user_id_for_recomendation);

	movies.read_all();
	views.read_all();

	auto a = movies[0];

	return 0;
}
