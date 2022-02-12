# formats

## products.csv

������� ���� ���������

StatementId -> statements.csv[RowId]
ProductTypeId -> product_types.csv[RowId]

| RowId | ProductTypeId | ProductName | StatementId | Price  |
| ----- | :-----------: | :----------:| :---------: | ------:|
|  int  |     int       |   string    |    int      | double |

## statements.csv

������� ���� ����������� �������� � �� ���������� �������

`� ����� ��� ������ ������ 1`

| RowId | title  | Probability |
| ----- | :----: | ----------: |
|  int  | string |   double    |

## product_types.csv

������� ����� �������

| RowId | title  |
| ----- | -----: |
|  int  | string |
