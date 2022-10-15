# ��������� ��� ������

## movies.csv

������� ���� ������� � �������

| FieldName   | Type   | Desription                      |
| ----------- | :----: | ------------------------------: |
| id          | int    | -                               |
| name        | string | �������� ������                 |
| genre_id    | int    | -> genre.csv[id]                |
| count_views | int    | ���������� ����������           |
| count_likes | int    | ���������� ������ � ������      |
| raiting     | float  | ������� �� ���������� �� 0 �� 5 |

## views.csv

�������� ���������� � �������

| FieldName   | Type   | Desription                      |
| ----------- | :----: | ------------------------------: |
| id          | int    | -                               |
| user_id     | int    | -> users.csv[id]                |
| movie_id    | int    | -> movies.csv[id]               |

## genre.csv

������� �� ����� ������� ������� � �������

| FieldName   | Type   | Desription                      |
| ----------- | :----: | ------------------------------: |
| id          | int    | -                               |
| name        | string | �������� �����                  |

## users.csv

������� �� ����� �������������� � �������

| FieldName   | Type   | Desription                      |
| ----------- | :----: | ------------------------------: |
| id          | int    | -                               |
| name        | string | ������ ��� ������������         |
