## 1. Design:
在 scheduling() function裡面每一個current time單位會進行以下動作：

    a.  更新已經使用cpu執行完畢的process

    b.  尋找有沒有這個時間點ready的process

    c.  選擇下一個可以得到cpu的process，如果是preemptive的方法就會進行context switch。


因為在進行排程的時候最主要的不同之處就是在於選擇下一個可以進入cpu的process的時間以及選擇哪一個 processs。

##### FIFO_next_process():

>我們純粹以ready time的排序選擇下一個可以進入的process而且因為不可插隊，所以只要被選到就可以直接執行到結束，非常簡單就能進排程。

##### RR_next_process():
>預設RR每個process的time quantum = 500，如果距離上一次context switch是500的倍數就會再切換成下一個process，切換的方式就是傳給下一個號碼的process(如果它需要CPU)。 

##### SJF_next_process():
>包含了SJF跟PSJF的選擇方式，SJF一樣是不可插隊，所以選到的process可以一直執行直到結束，只要確認每個時間點如果cpu是idle的就選shortest job來執行。PSJF的話不論有沒有process正在執行都要選這個時間點的shortest job並且回傳，在scheduling function中如果PSJF回傳的不是正在執行的process就會進行插隊，把正在執行的process "block"掉，"wakeup"可以插隊的process。



## 2. Contribution:

R07922099 - main. scheuler.  
T07505201 - process. system call processing

## 3. Results:
------------------------------------FIFO-----------------------------------  
### FIFO_1  
Process id:  
P1 13706  
P2 13707  
P3 13708  
P4 13709  
P5 13710  

result:  
    start    end  
P1      0    500  
P2    500   1000  
P3   1000   1500  
P4   1500   2000  
P5   2000   2500  
  
### FIFO_2  
Process id:  
P1 13715  
P2 13716  
P3 13728  
P4 13731  

result:  
    start    end  
P1      0  80000  
P2  80000  85000  
P3  85000  86000  
P4  86000  87000  
  
### FIFO_3  
Process id:  
P1 13742  
P2 13743  
P3 13744  
P4 13745  
P5 13746  
P6 13747  
P7 13748  

result:  
    start    end  
P1      0   8000  
P2   8000  13000  
P3  13000  16000  
P4  16000  17000  
P5  17000  18000  
P6  18000  19000  
P7  19000  23000  
  
### FIFO_4  
Process id:  
P1 13780  
P2 13781  
P3 13782  
P4 13783  
  
result:  
    start    end  
P1      0   2000  
P2   2000   2500  
P3   2500   2700  
P4   2700   3200  
  
### FIFO_5  
Process id:  
P1 13786  
P2 13787  
P3 13788  
P4 13789  
P5 13790  
P6 13791  
P7 13792  
  
result:  
    start    end  
P1      0   8000  
P2   8000  13000  
P3  13000  16000  
P4  16000  17000  
P5  17000  18000  
P6  18000  19000  
P7  19000  23000  

------------------------------------RR-----------------------------------    

### RR_1  
Process id:  
P1 14855  
P2 14856  
P3 14857  
P4 14858  
P5 14859  
  
result:  
    start    end  
P1      0    500  
P2    500   1000  
P3   1000   1500  
P4   1500   2000  
P5   2000   2500  
  
### RR_2  
Process id:  
P1 14862  
P2 14874  

result:  
    start    end  
P1    600   8100  
P2   1100   9600  

### RR_3  
Process id:  
P3 14917  
P1 14915  
P2 14916  
P6 14920  
P5 14919  
P4 14918  

result:  
    start    end  
P1   1200  18700  
P2   2700  19200  
P3   4200  18200  
P4   6200  31200  
P5   6700  30200  
P6   7200  28200  

### RR_4  
Process id:  
P4 14940  
P5 14941  
P6 14942  
P3 14939  
P2 14938  
P7 14943  
P1 14937  
  
result:  
    start    end  
P1      0  23000  
P2    500  18500  
P3   1000  13000  
P4   1500   5500  
P5   2000   7500  
P6   2500   9500  
P7   3000  21500  

### RR_5  
Process id:  
P4 14994   
P5 14995   
P6 14996   
P3 14992  
P2 14991  
P7 14997  
P1 14990  

result:  
    start    end  
P1      0  23000  
P2    500  18500  
P3   1000  13000  
P4   1500   5500  
P5   2000   7500  
P6   2500   9500  
P7   3000  21500  

------------------------------------SJF-----------------------------------  

### SJF_1  
Process id:  
P2 15016  
P3 15017  
P4 15018  
P1 15015  

result:  
    start    end  
P1   7000  14000  
P2      0   2000  
P3   2000   3000  
P4   3000   7000  

### SJF_2  
Process id:  
P1 15039  
P3 15041  
P2 15040  
P4 15042  
P5 15043  

result:  
    start    end  
P1    100    200  
P2    400   4400  
P3    200    400  
P4   4400   8400  
P5   8400  15400  
  
### SJF_3  
Process id:  
P1 15052  
P4 15055  
P5 15056  
P6 15057  
P7 15058  
P2 15053  
P3 15054  
P8 15059  

result:  
    start    end  
P1    100   3100  
P2  11120  16120  
P3  16120  23120  
P4   3100   3110  
P5   3110   3120  
P6   3120   7120  
P7   7120  11120  
P8  23120  32120  

### SJF_4 
Process id:  
P1 15070  
P2 15071  
P3 15072  
P5 15074  
P4 15073  
  
result:  
    start    end  
P1      0   3000  
P2   3000   4000  
P3   4000   8000  
P4   9000  11000  
P5   8000   9000  

### SJF_5 
Process id:  
P1 15078  
P2 15079  
P3 15080  
P4 15082  

result:  
    start    end  
P1      0   2000  
P2   2000   2500  
P3   2500   3000  
P4   3000   3500  

------------------------------------PSJF-----------------------------------  

### PSJF_1  
Process id:  
P4 15088  
P3 15087  
P2 15086  
P1 15085  

result:  
    start    end  
P1      0  25000  
P2   1000  16000  
P3   2000  10000  
P4   3000   6000  

### PSJF_2  
Process id:  
P2 15096  
P1 15095  
P4 15098  
P5 15099  
P3 15097  

result:  
    start    end  
P1      0   4000  
P2   1000   2000  
P3   4000  11000  
P4   5000   7000  
P5   7000   8000  

### PSJF_3  
Process id:  
P2 15120  
P3 15121  
P4 15123  
P1 15119  

result:  
    start    end  
P1      0   3500  
P2    500   1000  
P3   1000   1500  
P4   1500   2000  

### PSJF_4  
Process id:  
P3 15128  
P2 15127  
P4 15129  
P1 15126  

result:  
    start    end  
P1   7000  14000  
P2      0   3000  
P3    100   1100  
P4   3000   7000  

### PSJF_5  
Process id:  
P1 15158  
P3 15160  
P2 15159  
P4 15161  
P5 15162  

result:  
    start    end  
P1    100    200  
P2    400   4400  
P3    200    400  
P4   4400   8400  
P5   8400  15400  
