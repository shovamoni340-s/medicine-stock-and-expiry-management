# Medicine Stock Management

hello this is my c project.
this program is for keeping medicine stock in a shop.
it tell which medicine is low and which one going to expire soon.

## what it can do

- show all medicine in a table
- search one medicine by code
- add stock or issue stock
- sort by priority
- save the report in a file

## how to run

open the code in code blocks and press build and run.

or in linux you type:

```
gcc medicine.c -o medicine
./medicine
```

## menu

1. show report
2. search
3. update stock (add or remove)
4. sort priority
5. save file
6. exit

## about priority

if stock is less than minimum then it is low stock.
if expiry is 30 days or less then it is expiry risk.
then program give a condition and a number.
big number = more important.

## what i used

- array
- for loop
- if else
- switch case
- bubble sort
- function pointer

## note

medicine data is already in the program.
when you save it make a file report.txt in same folder.

thank you.
i am first year student i made this for learning c.