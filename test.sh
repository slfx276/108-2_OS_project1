#!/bin/bash

#FIFO
echo 'FIFO_1'
sudo ./main < ./OS_PJ1_Test/FIFO_1.txt
echo 'FIFO_2'
sudo ./main < ./OS_PJ1_Test/FIFO_2.txt
echo 'FIFO_3'
sudo ./main < ./OS_PJ1_Test/FIFO_3.txt
echo 'FIFO_4'
sudo ./main < ./OS_PJ1_Test/FIFO_4.txt
echo 'FIFO_5'
sudo ./main < ./OS_PJ1_Test/FIFO_5.txt

#RR
echo 'RR_1'
sudo ./main < ./OS_PJ1_Test/RR_1.txt
echo 'RR_2'
sudo ./main < ./OS_PJ1_Test/RR_2.txt
echo 'RR_3'
sudo ./main < ./OS_PJ1_Test/RR_3.txt
echo 'RR_4'
sudo ./main < ./OS_PJ1_Test/RR_4.txt
echo 'RR_5'
sudo ./main < ./OS_PJ1_Test/RR_5.txt

#SJF
echo 'SJF_1'
sudo ./main < ./OS_PJ1_Test/SJF_1.txt
echo 'SJF_2'
sudo ./main < ./OS_PJ1_Test/SJF_2.txt
echo 'SJF_3'
sudo ./main < ./OS_PJ1_Test/SJF_3.txt
echo 'SJF_4'
sudo ./main < ./OS_PJ1_Test/SJF_4.txt
echo 'SJF_5'
sudo ./main < ./OS_PJ1_Test/SJF_5.txt

#PSJF
echo 'PSJF_1'
sudo ./main < ./OS_PJ1_Test/PSJF_1.txt
echo 'PSJF_2'
sudo ./main < ./OS_PJ1_Test/PSJF_2.txt
echo 'PSJF_3'
sudo ./main < ./OS_PJ1_Test/PSJF_3.txt
echo 'PSJF_4'
sudo ./main < ./OS_PJ1_Test/PSJF_4.txt
echo 'PSJF_5'
sudo ./main < ./OS_PJ1_Test/PSJF_5.txt
