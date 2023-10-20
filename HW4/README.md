# Page replacement algorithm
- FIFO (First In First Out)
  - 先進先出，先進frame中的page會先被替換掉
- LRU (Least Recently Used)
  - LRU演算法，全稱Least recently used，即最近最少使用。LRU演算法的思想是如果資料最近被訪問過，那麼將來被訪問的概率也會很高。
- LFU (Least Frequently Used)
  - LFU演算法，全稱Least frequently used，即最不經常使用。LFU演算法的想法是一定時間內被訪問最少次的 page ，在將來被訪問到的機率也是最小的。
  - 當一個page被替換掉後又重新進入frame，此frame的frequency須重新計算。如果frequency相同，則用FIFO（越早被放入frame的越優先）。
 
# Input format
- 一共會有五筆測資（兩筆公開測資，三筆不公開測資）
- 每筆測資包含三行：
  - Frame 個數（10以內）
  - Reference string 長度（100以內）
  - Reference string（20以內）
- **請使用STDIN / STDOUT！**
- 範例：![image](https://github.com/XCI9/NYCU-2022-Fall-Introduction-to-Operating-Systems/assets/71249961/bcd684e0-a6cf-411a-9cd9-cf79bc25e1a2)

# Output format
- 僅需要Output出針對該筆測資，各Algorithm的Page Fault次數
- 順序：1. FIFO 2. LRU 3. LFU （需要換行）
- 範例:![image](https://github.com/XCI9/NYCU-2022-Fall-Introduction-to-Operating-Systems/assets/71249961/e33707e7-047a-4e63-bf98-eced400fcb9f)
- 注意:
  1. 順序錯誤
  2. 多輸出其他東西
  3. 各次數間沒有換行
  - 以上狀況皆會斟酌扣分，請多加留意！

# Compile & Run Commands
- 助教會使用以下Command編譯與執行：
  ```shell
  g++ hw4.cpp -o hw4
  ./hw4 < input1.txt > hw4_ans.txt #（再與正解比對）
  ```
- **請使用STDIN / STDOUT！**

# Requirements
- 使用 C/C++ 撰寫
- 程式碼檔名必須為hw4.c 或 hw4.cpp
- 壓縮檔命名必須為StudentID_hw4.zip
- 繳交多餘的檔案、程式碼檔名錯誤、壓縮檔檔名錯誤，皆會-5分

# Grading
- 滿分 100 分，抄襲一律 0 分
- 分數佔比：FIFO 30% / LRU 40% / LFU 30%
- 各筆測資：FIFO 6分 / LRU 8分 / LFU 6分

- 截止時間 : 2023/01/06 (FRI) 23:59
- 遲交一天 -20% 計算
