Author: Marcin 'Icewall' Noga

Description
============
Hanoi.exe is an application solving ["Hanoi problem"](http://en.wikipedia.org/wiki/Hanoi_towers) ( [planning problem](http://en.wikipedia.org/wiki/Automated_planning_and_scheduling)) using **Forward State Propagation (FSP)** algorith
and [STRIPS](http://en.wikipedia.org/wiki/STRIPS) notation.

How does it works?
===================
1. Generate problem
2. Click Solve and wait for solution(s).
3. Simulate the solution by click simulate button.

Important info
===============
###1. World/problem definition
World/problem and also operators and other elements are described in **problem.xml** file. This file needs to be always in the same directory as executable file.
Because of task requirements I did not put full problem description into **problem.xml** (but there is that possibility) instead, application automaticly generate full problem(beg state, end state,etc)
based on parameter "Amount of elements". If You want manualy describe entire problem, set "Amount of elements" to 0 and make proper changes in **problem.xml** file.
Information about required xml format you will find reading Parser.cpp file.

###2. Solutions
The best solution is saved into bestmoves.txt. It is done in that way because as You can notice there is possibility to set more than 3 elements (Piles) and if you set so,
generation of all possible results will take so much time that the best way is to:
- add solution finding limit ( you can treat it as an exercise and modify properly **CPlanner::solve_inter** method in planner.cpp file)
- choose manually on of them and remove rest from bestmoves.txt file.
After that procedure you are ready to click simulate.

