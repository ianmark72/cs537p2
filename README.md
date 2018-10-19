# cs537p2

In a 10,000 foot summary, this program reads in strings and performs various mutations to the capitatlization and spacing of the strings. 

More technically, the program takes in input from stdin and parses it string by string. Then it passes these strings through various threads using a queue. The queue uses a monitor as a syncronization mechanism to ensure queue integrity when passing threads between proccesses. Once the strings have been passed through all the threads, they are printed out along with queue statistics. 