# HW 1-1
- Please draw the tree format according the code on the report ( OS_report.pdf ). <br>
  ![image](https://github.com/XCI9/NYCU-2022-Fall-Introduction-to-Operating-Systems/assets/71249961/37a7d50d-7b5e-4bdc-90de-c65aa2888ae2)
- Need to clarify which fork ( fork0, fork1, fork2, fork3 and fork4 ) the process been made by.
- For example:
  ![image](https://github.com/XCI9/NYCU-2022-Fall-Introduction-to-Operating-Systems/assets/71249961/ec6fb004-1c4f-4e7f-9af8-43ac94ec3d12)
> Hint:
> - System Call:
>   - getpid() : Get the process ID of the current process.
>   - getppid() : Get process ID of parent process.
> - Additions
>   - You can use above system calls to help you complete this part.
>   - Draw which fork ( fork0, fork1, fork2, fork3, fork4 ) the process been made by after the code is executed. 

# HW 1-2
- Write a program which uses fork() to produce the tree format on below.
  Please note that **the format** and **the order of fork()** of your output should be the same as the following.
- output sample:
  ![image](https://github.com/XCI9/NYCU-2022-Fall-Introduction-to-Operating-Systems/assets/71249961/3100b0bf-8c6f-41db-ad9b-323e60c0b8b5)
- structure:
  ![image](https://github.com/XCI9/NYCU-2022-Fall-Introduction-to-Operating-Systems/assets/71249961/a4deb996-1d64-4eaa-b226-4265cbe3e861)

> Hint:
> To maintain the order of the fork(), parent processes have to **wait()** until child processes finish.

# HW 1-3
- Finish “hw1_3.c” or “hw1_3.cpp” in order to design a C/C++ program to serve as a shell interface that accepts user commands then execute each command in a separate process.
-  User can keep entering the command until he/she enters “exit”. (a command include the command itself and its parameters).
- Your shell needs to support following commands: cat, ls, date, ps(ps –f), pwd, exit
- Some important System Call :
  - read ( STDIN_FILENO, inputBuﬀer, MAX_LINE ) : read command line
  - fork() : Create child process
  - execvp ( char *command, char *params[] ) : Execute system calls
  - waitpid ( pid )
  - wait ()
- Example output:
  ![image](https://github.com/XCI9/NYCU-2022-Fall-Introduction-to-Operating-Systems/assets/71249961/6c44a913-8459-4a6e-8539-8879658415d4)


# Submission and Grade
- Score
  - Total score : 100pts.
  - **Copy will get 0 point.**
  - 1-1 score : Report Q1 30pts
  - 1-2 score : Code 25pts / Report Q2 10pts
  - 1-3 score : Code 25pts / Report Q3 10pts
  - Incorrect output format will get -5 pts
  - Report : Format is in OS_report.pdf.
-  Use **only C/C++**, other language will get 0 point. 
- Filename format please according to : **hw1_2.c (or .cpp), hw1_3.c (or .cpp), OS_report.pdf**
- Incorrect filename format will get -5 pts
- Put **all** *.c (or *.cpp) ﬁles and *.pdf reports into same compressed ﬁle named **Student ID_hw1.zip**. (ex : 0000000_hw1.zip)
- Deadline: **2022/10/12 11:59 p.m**
- Delayed submission will get -20% point a day. 
- If you have any question, just send email to TAs by E3.
