# Структура баз данных

## movies.csv

Таблица всех фильмов в системе

| FieldName   | Type   | Desription                      |
| ----------- | :----: | ------------------------------: |
| id          | int    | -                               |
| name        | string | название фильма                 |
| genre_id    | int    | -> genre.csv[id]                |
| count_views | int    | количество просмотров           |
| count_likes | int    | количество лайков у фильма      |
| raiting     | float  | рейтинг на кинопоиске от 0 до 5 |

## views.csv

Таблицпа просмотров в системе

| FieldName   | Type   | Desription                      |
| ----------- | :----: | ------------------------------: |
| id          | int    | -                               |
| user_id     | int    | -> users.csv[id]                |
| movie_id    | int    | -> movies.csv[id]               |

## genre.csv

Таблица со всеми жанрами фильмов в системе

| FieldName   | Type   | Desription                      |
| ----------- | :----: | ------------------------------: |
| id          | int    | -                               |
| name        | string | название жанра                  |

## users.csv

Таблица со всеми пользователями в системе

| FieldName   | Type   | Desription                      |
| ----------- | :----: | ------------------------------: |
| id          | int    | -                               |
| name        | string | полное имя пользователя         |
