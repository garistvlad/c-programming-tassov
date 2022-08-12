# Lab-10

There is a group of students stored in a text file, containing their names and marks (marks from 2 to 5 for each of 5 subjects). Please, group students by their marks and remove all the students who has more than two `2` marks (or equal to).

**Example**<br>
Input:
```
File containing the following rows:

Vladislav Garist;5 4 5 4 5
Dmitry Ivanov;5 3 5 2 2
Gohan Saki;5 5 5 5 5
Habib Nurmagomedov;3 4 3 4 3
Leonid Kuravlev;5 5 5 2 2
Jimmy Kerry;5 3 5 3 5
Ostap Bender;3 3 3 3 2
Mark Twein;2 2 5 5 4
Luke Besson;5 4 3 2 5
Lazaros Josephides;3 5 5 4 4
Ostin Texas;5 2 2 3 3
Lesli Osborne;4 4 3 4 4
Albert Einstein;5 5 5 5 5
Strange Guy;3 3 3 3 2
Mr Blonde;2 2 2 3 2
Who Are You;3 4 5 4 5
Tomas Cat;3 2 3 3 3

```
Output:
```
File with the following rows:

Ostap Bender
Strange Guy
Tomas Cat

Habib Nurmagomedov

Lesli Osborne
Luke Besson

Lazaros Josephides
Who Are You
Jimmy Kerry

Vladislav Garist

Albert Einstein
Gohan Saki

```
