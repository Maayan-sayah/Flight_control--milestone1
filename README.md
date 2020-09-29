## ***milestone 2***

**<u>Description:</u>**
In computer science, a search algorithm is any algorithm which is used to search requested information within a data structure. Searching is a basic operation in Software Development and therefor efforts have been made to develop efficient algorithms for this.

This program revolves around the server-client structure and in general, the code that I wrote will solve a search problem. 

The client will send: 
 n*n matrix
start point 
destination point 
The server will return: solution of this problem- the solution will be the shorteset route between the points.

To resolve this is problem I use 3 algorithms: BFS, BestFirst search and A star.
I were test this algorithms with 10 diffrent matrix. the result was:

![Capture](https://user-images.githubusercontent.com/60346583/94564495-b6b77080-0270-11eb-85d3-ea241bc644be.PNG)


according to the result of the following graphs, a star is the algorithm that return the fastest and the cheapesst way solution. so the program use this algorithm, but it's modifiable.

in addition, i use a cache to store every solution in file database. 


### Running The Program:

in order to run the program, run this command in the terminal:

**<u>g++ -std=c++11 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread</u>**

our program requires an available port here is how to execute the program with a recommended port:

**<u>./a.out 5400</u>**
Open terminal and enter the following command :

**<u>telnet localhost 5400</u>**
Enter the matrix ,enter the start point and destination point in two different lines.

Enter "end" when you finished and wait for answer from the server.

**<u>Authors:</u>**

Maayan Sayah

my github project https://github.com/Maayan-sayah/maayan
