# -*- coding: utf-8 -*-
"""
Created on Mon Oct  2 10:53:48 2017

@author: m.leclech
"""

import matplotlib.pyplot as plt

fileDFF = open("DuFort_Frankel.txt", 'r')
fileAN = open("Analytical.txt", 'r')
fileRI = open("Richardson.txt", 'r')
dataDFF = fileDFF.readlines()
dataAN = fileAN.readlines()
dataRI = fileRI.readlines()

x = []
DFF = []
AN = []
RI = []

i=0
while (i<len(dataDFF)):
    data_DFF_splited = dataDFF[i].split(" ")
    data_AN_splited = dataAN[i].split(" ")
    data_RI_splited = dataRI[i].split(" ")
    x.append(float(data_DFF_splited[0]))
    DFF.append(float(data_DFF_splited[1]))
    AN.append(float(data_AN_splited[1]))
    RI.append(float(data_RI_splited[1]))
    i=i+1

plt.subplot(121)
plt.plot(x, DFF, 'b', label='approximation')
plt.plot(x, AN, 'r', label='analytical')
plt.title("DuFort_Frankel")
plt.xlim((0, 1))
plt.ylim((100, 300))
plt.legend(loc ='upper center')

plt.subplot(122)
plt.plot(x, RI, 'b', label='approximation')
plt.plot(x, AN, 'r', label='analytical')
plt.title("Richardson")
plt.xlim((0, 1))
#plt.ylim((100, 300))
plt.legend(loc ='upper center')

plt.show()

fileDFF.close()
