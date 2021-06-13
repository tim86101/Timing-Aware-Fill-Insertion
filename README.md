
# ICCAD@2018

在我們的專題研究中，我們所面對的就是timing-aware metal insertion的問題，
目的是開發一個程式使半導體中插入的金屬滿足密度的限制，同時也最小化金屬對金屬所產生的寄生電容。

本題目來自[CAD Contest @ ICCAD 2018](http://iccad-contest.org/2018/problems.html)。


## 題目說明

&emsp;&emsp;在現代的半導體製造上，CMP是半導體製造中的一種技術，使用化學腐蝕及機械力對晶圓或其他襯底材料進行平坦化處理。若要實現更高的產量，需要使用金屬來填充empty conductor layers。

&emsp;&emsp;透過這些金屬的填充可以減小dielectric thickness的變化，增加planarity，並提供更優良的pattern density，以上對於減少過程的變化性非常重要。

&emsp;&emsp;然而填充進去的金屬之間會產生parasitic capacitance，也就是指電路中電子元件之間由於相互靠近而形成的電容，是設計時不希望得到的電容特性。

&emsp;&emsp;因此，在插入金屬時要特別去注意寄生電容對整個電路的影響，避免破壞原本所設計好的timing-closure，必須在符合最小密度的情況下，最小化寄生電容的影響。

## Data structure


![image](https://github.com/tim86101/Timing-Aware-Fill-Insertion/blob/main/code/matlab/ds1.png)

![image](https://github.com/tim86101/Timing-Aware-Fill-Insertion/blob/main/code/matlab/ds2.png)

## Algorithm

![image](https://github.com/tim86101/Timing-Aware-Fill-Insertion/blob/main/code/matlab/a1.png)

### 1.找出沒有與原始金屬(藍色格子)重疊的區塊，這些紅色格子的區域有效避免了lateral capacitance的產生。
 ![image](https://github.com/tim86101/Timing-Aware-Fill-Insertion/blob/main/code/matlab/a2.png)
 
### 2.將目前的window切割成很多grids，如果密度已符合即可換下一個window，不足的話則要往下繼續往下做。
 ![image](https://github.com/tim86101/Timing-Aware-Fill-Insertion/blob/main/code/matlab/a3.png)

### 3.檢查我們原始的金屬與我們切出來的grid是否重疊，如果重疊則標記為不可用，反之，標記為可用(如上圖綠色格子)。
![image](https://github.com/tim86101/Timing-Aware-Fill-Insertion/blob/main/code/matlab/a4.png)

### 4.標記為可用的grid我們會去做shuffle後隨機插入金屬，以達到良好的效能又可避免金屬集中在某一個區域。
 ![image](https://github.com/tim86101/Timing-Aware-Fill-Insertion/blob/main/code/matlab/a5.png)

### 5.如果塞入的金屬以達到最小密度標準則跳到下一個window繼續做檢查。



## 成果

![image](https://github.com/tim86101/Timing-Aware-Fill-Insertion/blob/main/code/matlab/0001.jpg)
