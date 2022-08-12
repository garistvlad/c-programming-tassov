# Lab-11

## Lab-11.1


**Example**<br>
Delete empty strings from a given text file. At the beginning of each row you need to add:
- String number
- Number of words (in this string)
- Number of vovels
- Number of conconants
Input. Text file with the following content:
```
It's my life

It's my life
My heart is like an open highway
Like Frankie said:
"I did it my way".
...

… It's now or never.
But I ain't gonna live forever 
I just want to live while I'm alive 
(It's my life)
```
Output. Text file with the following content:
```
1. [3, 4, 5]. It's my life
2. [3, 4, 5]. It's my life
3. [7, 12, 14]. My heart is like an open highway
4. [3, 7, 8]. Like Frankie said:
5. [5, 6, 5]. "I did it my way".
6. [1, 0, 0]. ...
7. [5, 5, 8]. … It's now or never.
8. [6, 11, 13]. But I ain't gonna live forever 
9. [8, 12, 15]. I just want to live while I'm alive 
10. [3, 4, 5]. (It's   my life)
```

## Lab-11.2


**Example**<br>
Implement a program to work with a text file, containing information about Cars, with the following set of commands:
- add new Car
- delete an existing Car
- find a Car by brand name and/or year of production
- sorting Cars by brand name, engine power, engine capacity
Please, use the `Car` structure with the following set of fields:
- brand name
- model name
- car's category
- year of production
- engine power (HP)
- engine capacity (L)
