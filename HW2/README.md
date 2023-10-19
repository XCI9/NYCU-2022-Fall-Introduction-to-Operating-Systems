# HW2 Multi-Threading Programming

- Use multithreading to do matrix calculation problems
- Find the best thread quantity between 2 ~ 20
- Output the sum of every element of your matrices

- You should implement:
  1. STDIN(e.g. scanf, cin)
  2. Multiplication/addition function
  3. Thread management
  4. STDOUT(e.g. printf, cout)

- **DO NOT USE FILE I/O !**

### Compile & Run Commands
- Compile
  - (single-thread)  $ g++ -o filename filename.cpp
  - (multi-thread) $ g++ -o filename filename.cpp -lpthread
- Run
  - $ ./filename < input.txt
- Environment
  - You should run your code on the multiple CPU
- Performance between single-thread and multi-thread:
  - use $ time ./filename” to check the execution time
  - ![image](https://github.com/XCI9/NYCU-2022-Fall-Introduction-to-Operating-Systems/assets/71249961/8024b334-9154-402d-9a46-34ff909e501f)
  - ![image](https://github.com/XCI9/NYCU-2022-Fall-Introduction-to-Operating-Systems/assets/71249961/dde2ef81-30a7-429b-8237-238a9118e726)
 
### Speed up
- Compare the real time between single thread and the multi thread
- Speedup = real time of multiple threads / real time of single thread
- Compare with your classmates (bigger speed-up gets higher score)
  - Top 1/5 get 20 points, second 1/5 get 16 points, etc.
 
### Input format
- Input size : 500 * 500 matrix
- All elements are seperated by space (without newline)
- Matrix A start from line1, matrix B start from line 2 
- Integer value random from 0~9

### Output format
- Output the sum of every element of the Addition matrix FIRST
- Then output the sum of the Multiplication matrix NEXT LINE
(Hint: If the sum is too big, try use long long int)

### Requirements
- Multi-threading method should be much faster than Single-threading, and their results must be exactly the same.
- Write yout codes in **C/C++**
- You need to hand in one multi_thread versions and a report. Put **studentID.cpp and studentID_report.pdf** into the same compressed file without input, output data or any folder
- The type of compressed file must be “studentID_HW2.zip”
- **Use Ubuntu or NYCU work station as your environment.**
- The compressed file needs to be as follow:
![image](https://github.com/XCI9/NYCU-2022-Fall-Introduction-to-Operating-Systems/assets/71249961/70929703-18a2-4474-ba3a-e61008f19a5f)

### Grading
- Total score : 100 pts. **COPY WILL GET 0 POINT!**
- Speedup : 20 pts  
- Multi-thread programs : 50 pts (correctness)
- Report : 30 pts
- Incorrect file format : -10 pts
- Use FILE I/O : -5 pts
- Deadline : 2022/10/30 (SUN) 23:59
- **Late submission will get a -20% point per day.**










