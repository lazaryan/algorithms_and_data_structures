# formats

## products.csv

Таблица всех продуктов

StatementId -> statements.csv\[RowId\]
ProductTypeId -> product_types.csv\[RowId\]

| RowId | ProductTypeId | ProductName | StatementId | Price  |
| ----- | :-----------: | :----------:| :---------: | ------:|
|  int  |     int       |   string    |    int      | double |

## statements.csv

Таблица всех утверждений кассиров и их вроятности встречи

`В сумме они должны давать 1`

| RowId | title  | Probability |
| ----- | :----: | ----------: |
|  int  | string |   double    |

## product_types.csv

Таблица типов товаров

| RowId | title  |
| ----- | -----: |
|  int  | string |

## shopping.csv

Список высказываний, какие продукты обычно с чем-то берут
-1 означает, что берут "еще что-то"
Все элементы идут через точку с запятой

listProductTypeIds -> product_types.csv\[RowId\]\[\]

| listProductTypeIds |
| ------------------ |
|      int[]         |
