# Process Scheduling
1. Shortest Remaining Time First Scheduling (SRTF, Preemptive SJF)
2. Round-Robin(RR)
3. Multilevel Feedback Queue
   - 1<sup>st</sup> Level : Round-Robin
   - 2<sup>nd</sup> Level : First Come First Serve(FCFS)
  
# Scheduling Criteria
- Throughput: Number of completed processes per time unit.
- Turnaround Time:  The amount of time taken to complete a process.
- Waiting Time: Total time spent by the process in the ready queue.
- Response Time: The time spent when the process is being submission and gets the CPU for the first time.

# The Format of Input & Output
- Input
```
3 # Total Number of Processes
0 2 4 # Arrival Time of Each Process
6 3 1 # Burst Time of Each Process
```
- Output: You should output **four things**
1. Waiting time for each process
2. Turnaround time for each process
3. Total waiting time
4. Total turnaround time
  - example output:
  - ![image](https://github.com/XCI9/NYCU-2022-Fall-Introduction-to-Operating-Systems/assets/71249961/fbbdd0cf-df28-4b18-bee2-0bd4bd3bcd0f)
  - **You just need to print the format as above**
  - detail explain:
  - ![image](https://github.com/XCI9/NYCU-2022-Fall-Introduction-to-Operating-Systems/assets/71249961/7c03998a-e977-4695-8579-97f3757ce831)

# Notes
- TAs will use “g++  hw3_1.cpp -o hw3_1 ” to compile.
- In Linux, after saving the test case in testcase.txt, we can use “./hw3_1 < testcase.txt > student_ans.txt” to test, and compare it to answer.txt.
- So, please use std::cin to get user input in your homework!

# Grades
- Total score : 100pts. Copy will get 0 point!
1. hw3-1, hw3-2, hw3-3 : 30 pts for each question.
2. There will be three test cases for each scheduling algorithm, one is visible, and the others are hidden. You will get 10 pts, if you pass one case.
3. Report : 10 pts
4. The format of Report is in hw3_report.docx. Please export it to PDF ( hw3_report.pdf ) before submitting.
5. If you just use { printf ( "0 7\n5 9\n7 8\n12\n24“ ) ; }, you will get 0 pts.
6. Deadline : 2022/11/30 (Wes) 23:59. Late submission will get a -20% point per day.

# Requirements
1. You should write codes in c/c++.
2. The name of .cpp file must in the form of “hw3_1.cpp” & “hw3_2.cpp” & “hw3_3.cpp”.
3. Put all *.cpp source files and report(*.pdf) into same compressed file. The type of compressed file must be “zip”.
   ![image](https://github.com/XCI9/NYCU-2022-Fall-Introduction-to-Operating-Systems/assets/71249961/318298d3-01ad-44d6-8f48-3f4d177d972d)
4. The name of your compressed file must have the form of “studentID_hw3.zip” and without any folder.
5. Incorrect file form : -20 pts ( Including the names of compressed file, .cpp files, report file )
   ![image](https://github.com/XCI9/NYCU-2022-Fall-Introduction-to-Operating-Systems/assets/71249961/8cb9e4d9-985b-47f0-b7f1-f583238ae91d)



