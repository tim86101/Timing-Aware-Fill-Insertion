
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


## Algorithm