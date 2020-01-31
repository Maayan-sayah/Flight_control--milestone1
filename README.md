## ***milestone 2***

**<u>Description:</u>**

This program revolves around the server client structure. in general, i write a code that will solve a search problem. 
in this project the client will send n*n matrix, start point and destination point and the server will return the solution of this problem. 


in this problem i use 3 algorithms: 
BFS, BestFirst search and A star. 

i test this algorithms with 10 diffrent matrix, and i understood that a star is the algorithm that return the fastest and the cheapesst way solution.

in addition, i use a cache to store every solution in file database. 


### Running The Program:

in order to run the program, run this command in the terminal:

g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
our program requires an available port here is how to execute the program with a recommended port:

./a.out 5400
Open terminal and enter the following command :

telnet localhost 5400
Enter the matrix ,enter the start point and destination point in two different lines.

Enter "end" when you finished and wait for answer from the server.

**<u>Authors:</u>**

Maayan Sayah
my github project https://github.com/Maayan-sayah/maayan
