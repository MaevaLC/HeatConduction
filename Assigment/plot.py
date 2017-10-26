# -*- coding: utf-8 -*-
"""
Created on Mon Oct  2 10:53:48 2017

@author: m.leclech
"""

import matplotlib.pyplot as plt

fileDFF1 = open("DuFort_Frankel-0.100000.txt", 'r')
fileDFF2 = open("DuFort_Frankel-0.200000.txt", 'r')
fileDFF3 = open("DuFort_Frankel-0.300000.txt", 'r')
fileDFF4 = open("DuFort_Frankel-0.400000.txt", 'r')
fileDFF5 = open("DuFort_Frankel-0.500000.txt", 'r')

fileAN1 = open("Analytical-0.100000.txt", 'r')
fileAN2 = open("Analytical-0.200000.txt", 'r')
fileAN3 = open("Analytical-0.300000.txt", 'r')
fileAN4 = open("Analytical-0.400000.txt", 'r')
fileAN5 = open("Analytical-0.500000.txt", 'r')

fileRI1 = open("Richardson-0.100000.txt", 'r')
fileRI2 = open("Richardson-0.200000.txt", 'r')
fileRI3 = open("Richardson-0.300000.txt", 'r')
fileRI4 = open("Richardson-0.400000.txt", 'r')
fileRI5 = open("Richardson-0.500000.txt", 'r')

dataDFF1 = fileDFF1.readlines()
dataDFF2 = fileDFF2.readlines()
dataDFF3 = fileDFF3.readlines()
dataDFF4 = fileDFF4.readlines()
dataDFF5 = fileDFF5.readlines()

dataAN1 = fileAN1.readlines()
dataAN2 = fileAN2.readlines()
dataAN3 = fileAN3.readlines()
dataAN4 = fileAN4.readlines()
dataAN5 = fileAN5.readlines()

dataRI1 = fileRI1.readlines()
dataRI2 = fileRI2.readlines()
dataRI3 = fileRI3.readlines()
dataRI4 = fileRI4.readlines()
dataRI5 = fileRI5.readlines()

x = []

DFF1 = []
DFF2 = []
DFF3 = []
DFF4 = []
DFF5 = []

AN1 = []
AN2 = []
AN3 = []
AN4 = []
AN5 = []

RI1 = []
RI2 = []
RI3 = []
RI4 = []
RI5 = []

i=0

while (i<len(dataDFF1)):
    data_DFF1_splited = dataDFF1[i].split(" ")
    data_DFF2_splited = dataDFF2[i].split(" ")
    data_DFF3_splited = dataDFF3[i].split(" ")
    data_DFF4_splited = dataDFF4[i].split(" ")
    data_DFF5_splited = dataDFF5[i].split(" ")
    
    data_AN1_splited = dataAN1[i].split(" ")
    data_AN2_splited = dataAN2[i].split(" ")
    data_AN3_splited = dataAN3[i].split(" ")
    data_AN4_splited = dataAN4[i].split(" ")
    data_AN5_splited = dataAN5[i].split(" ")
    
    data_RI1_splited = dataRI1[i].split(" ")
    data_RI2_splited = dataRI2[i].split(" ")
    data_RI3_splited = dataRI3[i].split(" ")
    data_RI4_splited = dataRI4[i].split(" ")
    data_RI5_splited = dataRI5[i].split(" ")
    
    x.append(float(data_DFF1_splited[0]))
    
    DFF1.append(float(data_DFF1_splited[1]))
    DFF2.append(float(data_DFF2_splited[1]))
    DFF3.append(float(data_DFF3_splited[1]))
    DFF4.append(float(data_DFF4_splited[1]))
    DFF5.append(float(data_DFF5_splited[1]))
    
    AN1.append(float(data_AN1_splited[1]))
    AN2.append(float(data_AN2_splited[1]))
    AN3.append(float(data_AN3_splited[1]))
    AN4.append(float(data_AN4_splited[1]))
    AN5.append(float(data_AN5_splited[1]))
    
    RI1.append(float(data_RI1_splited[1]))
    RI2.append(float(data_RI2_splited[1]))
    RI3.append(float(data_RI3_splited[1]))
    RI4.append(float(data_RI4_splited[1]))
    RI5.append(float(data_RI5_splited[1]))
    
    i=i+1

plt.subplot(121)
plt.plot(x, DFF1, 'b', label='approximation')
plt.plot(x, DFF2, 'b')
plt.plot(x, DFF3, 'b')
plt.plot(x, DFF4, 'b')
plt.plot(x, DFF5, 'b')
plt.plot(x, AN1, 'r', label='analytical')
plt.plot(x, AN2, 'r')
plt.plot(x, AN3, 'r')
plt.plot(x, AN4, 'r')
plt.plot(x, AN5, 'r')
plt.title("DuFort_Frankel")
plt.xlim((0, 1))
plt.ylim((100, 300))
plt.legend(loc ='upper center')

plt.subplot(122)
plt.plot(x, RI1, 'b', label='approximation')
plt.plot(x, RI2, 'b')
plt.plot(x, RI3, 'b')
plt.plot(x, RI4, 'b')
plt.plot(x, RI5, 'b')
plt.plot(x, AN1, 'r', label='analytical')
plt.title("Richardson")
plt.xlim((0, 1))
plt.legend(loc ='upper center')

plt.show()

fileDFF1.close()
fileDFF2.close()
fileDFF3.close()
fileDFF4.close()
fileDFF5.close()

fileAN1.close()
fileAN2.close()
fileAN3.close()
fileAN4.close()
fileAN5.close()

fileRI1.close()
fileRI2.close()
fileRI3.close()
fileRI4.close()
fileRI5.close()
