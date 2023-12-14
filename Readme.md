Name: Inioluwa Adeniyi
Student ID: 1629052
CMPUT 379, Fall 2022
Assignment 2: Producer-Consumer problem
Included files: # Readme.md # main.cpp # main.hpp # prodcon.cpp # summary_details.cpp # summary_details.hpp # Makefile # buffer.cpp # buffer.hpp # tands.cpp

Wiring Instructions: None

Running Instructions:

    1. Navigate to the directory containing the files

    2. Type "make" into the terminal to create the shell379 executable

    3. To run the executable:
        1. Type "./prodcon x y < inputfile" or "./prodcon x inputfile" into the terminal to run the executable and redirect input from  a file. Make sure to prepare the file before doing this.

        2. Type "./prodcon x y" or "./prodcon x" into the terminal to run the executable and enter commands throught the keyboard. Use ctrl+d to pass in EOF which is required to bring the program to an end.

        NOTE:
        x - is the number of threads. Must be passed.
        y - is the id of the file. If given, output goes to "prodcon.y.log" file. If not passed, output goes to "prodcon.log" file.

    4. type in "make clean" to remove the object files and executable. the txt and log files are left for the user if    they want to check.

Notes and Assumptions:
For this assignment, i used a circular queue to implement the bounded buffer. The idea and implementation of thte circular queue was gotten from:

    1. youtube video that helped with implementing the queue: https://www.youtube.com/watch?v=oyX30WVuEos

    2. // linear vs circular queue: https://www.geeksforgeeks.org/difference-between-linear-queue-and-circular-queue/

For passing the thread id into the consumer function, i used:

    https://www.unix.com/programming/81931-creating-array-hold-posix-thread-ids-only-dynamic-array-works.html

To synchronize the producer and consumer(s), I used a mutex lock for the output file and buffer, as they were the criticlal sections: writing into files, enqueing and dequeueing. I used these locks to make the operations atomic; hence, preventing garbled file output and incosistencies when reading or writing into the buffer.

I also used conditional variables to wait/alert when the the buffer was full and empty. I finally used a conditonal variable broadcast to free any stuck threads when the end of file was reached and the buffer empty.
Program was tested extensively and seems to work very well. Hoepfully, it maintains that while you test.
# Message-Passing
# Message-Passing
