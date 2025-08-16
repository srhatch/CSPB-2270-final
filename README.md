# CSPB-2270-final
An implementation of a Rope data structure

What is it, and why do we care?<br>
The data structure I implemented for this project is called a Rope. A Rope is a binary tree that is used to represent string data. String data is typically represented in a monolithic, contiguous block of memory. This is effective for small strings, or for larger strings that don’t need to be manipulated frequently, but when the string needs to be edited (as would be the case in text processing applications), a Rope becomes more appealing. The main reason for this is that a Rope has O(log n) time complexity for most of its operations. For operations like concatenation or insertion, this complexity is better than a contiguous data structure’s complexity, which would be O(n).

What is the context?<br>
I was interested in using a Rope to represent something other than text data. I decided to build my demo to provide a limited model of how a Rope could be used for CRISPR gene editing. In short, this is a technique that is used to edit genetic material. Genetic material is composed of long strands of base pairs of molecules (a combination of A and T, or a combination of C and G). These strands can easily be represented as a string, and when using a Rope each leaf node can be used to represent one base pair. Performing common text editing operations in a word processing application is a common analogy for the kinds of editing performed in CRISPR gene editing. This makes it a perfect conceptual example for how a Rope can be used to represent and perform operations on long sequences of ordered data.

How will it be demonstrated?<br>
My demonstration consists of a simple command line program that can be used to create and edit a string of genetic material.

First clone the repository.

Compile the program to make sure it will run properly:<br>
g++ -o main ./code/rope.cpp ./app/main.cpp

Then start the program:<br>
./main

This is the main menu:<br>
1: Create new Rope<br>
2: Display existing Ropes<br>
3: Concatenate two Ropes<br>
4: Insert new data into a Rope<br>
5: Insert a subtree (Rope) into a Rope<br>
6: Search by index<br>
7: Split a Rope<br>
8: Print Rope string

Each command will contain instructions for how to enter information correctly. There are validation checks on input, but keep in mind the purpose of this is for editing genetic base pairs, so strings of base pairs, as well as indexes for various functions, will need to be divisible by 2. Usefully, option 8 can be used to check the contents of a rope to verify that edits worked properly.


Challenges: I unfortunately ran out of time and wasn’t able to implement the delete function. The split function can effectively be used as a delete, because the delete algorithm just calls split twice, once for each index bound, and then concatenates the two outer trees. The split function in general was very difficult to implement and I wasn’t able to exhaustively test all cases. As such it may still be a little buggy. The command line program is also still a little buggy, and problems start to occur when performing multiple operations in sequence. If this happens, restarting the program will help. To the extent that I tested it, all of the operations seem to work when performed individually from the start of the program running. The issue is likely in the way that I’m storing the Ropes in the “front-end”, as opposed to issues with the algorithms themselves.
