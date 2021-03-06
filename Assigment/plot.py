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

fileLA1 = open("Laasonen-0.100000.txt", 'r')
fileLA2 = open("Laasonen-0.200000.txt", 'r')
fileLA3 = open("Laasonen-0.300000.txt", 'r')
fileLA4 = open("Laasonen-0.400000.txt", 'r')
fileLA5 = open("Laasonen-0.500000.txt", 'r')

fileCN1 = open("CrankNicholson-0.100000.txt", 'r')
fileCN2 = open("CrankNicholson-0.200000.txt", 'r')
fileCN3 = open("CrankNicholson-0.300000.txt", 'r')
fileCN4 = open("CrankNicholson-0.400000.txt", 'r')
fileCN5 = open("CrankNicholson-0.500000.txt", 'r')

filedtLA1 = open("dt_Laasonen-0.010000.txt", 'r')
filedtLA2 = open("dt_Laasonen-0.025000.txt", 'r')
filedtLA3 = open("dt_Laasonen-0.050000.txt", 'r')
filedtLA4 = open("dt_Laasonen-0.100000.txt", 'r')

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

dataLA1 = fileLA1.readlines()
dataLA2 = fileLA2.readlines()
dataLA3 = fileLA3.readlines()
dataLA4 = fileLA4.readlines()
dataLA5 = fileLA5.readlines()

dataCN1 = fileCN1.readlines()
dataCN2 = fileCN2.readlines()
dataCN3 = fileCN3.readlines()
dataCN4 = fileCN4.readlines()
dataCN5 = fileCN5.readlines()

datadtLA1 = filedtLA1.readlines()
datadtLA2 = filedtLA2.readlines()
datadtLA3 = filedtLA3.readlines()
datadtLA4 = filedtLA4.readlines()

x = []

DFF1 = []
DFF2 = []
DFF3 = []
DFF4 = []
DFF5 = []

eDFF1 = []
eDFF2 = []
eDFF3 = []
eDFF4 = []
eDFF5 = []

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

eRI1 = []
eRI2 = []
eRI3 = []
eRI4 = []
eRI5 = []

LA1 = []
LA2 = []
LA3 = []
LA4 = []
LA5 = []

eLA1 = []
eLA2 = []
eLA3 = []
eLA4 = []
eLA5 = []

CN1 = []
CN2 = []
CN3 = []
CN4 = []
CN5 = []

eCN1 = []
eCN2 = []
eCN3 = []
eCN4 = []
eCN5 = []

dtLA1 = []
dtLA2 = []
dtLA3 = []
dtLA4 = []

dteLA1 = []
dteLA2 = []
dteLA3 = []
dteLA4 = []
dteLA5 = []

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
    
    data_LA1_splited = dataLA1[i].split(" ")
    data_LA2_splited = dataLA2[i].split(" ")
    data_LA3_splited = dataLA3[i].split(" ")
    data_LA4_splited = dataLA4[i].split(" ")
    data_LA5_splited = dataLA5[i].split(" ")
    
    data_CN1_splited = dataCN1[i].split(" ")
    data_CN2_splited = dataCN2[i].split(" ")
    data_CN3_splited = dataCN3[i].split(" ")
    data_CN4_splited = dataCN4[i].split(" ")
    data_CN5_splited = dataCN5[i].split(" ")
    
    data_dtLA1_splited = datadtLA1[i].split(" ")
    data_dtLA2_splited = datadtLA2[i].split(" ")
    data_dtLA3_splited = datadtLA3[i].split(" ")
    data_dtLA4_splited = datadtLA4[i].split(" ")
    
    x.append(float(data_DFF1_splited[0]))
    
    DFF1.append(float(data_DFF1_splited[1]))
    DFF2.append(float(data_DFF2_splited[1]))
    DFF3.append(float(data_DFF3_splited[1]))
    DFF4.append(float(data_DFF4_splited[1]))
    DFF5.append(float(data_DFF5_splited[1]))
    
    eDFF1.append(float(data_DFF1_splited[2]))
    eDFF2.append(float(data_DFF2_splited[2]))
    eDFF3.append(float(data_DFF3_splited[2]))
    eDFF4.append(float(data_DFF4_splited[2]))
    eDFF5.append(float(data_DFF5_splited[2]))
    
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

    eRI1.append(float(data_RI1_splited[2]))
    eRI2.append(float(data_RI2_splited[2]))
    eRI3.append(float(data_RI3_splited[2]))
    eRI4.append(float(data_RI4_splited[2]))
    eRI5.append(float(data_RI5_splited[2]))
    
    LA1.append(float(data_LA1_splited[1])) 
    LA2.append(float(data_LA2_splited[1])) 
    LA3.append(float(data_LA3_splited[1])) 
    LA4.append(float(data_LA4_splited[1])) 
    LA5.append(float(data_LA5_splited[1]))
    
    eLA1.append(float(data_LA1_splited[2])) 
    eLA2.append(float(data_LA2_splited[2])) 
    eLA3.append(float(data_LA3_splited[2])) 
    eLA4.append(float(data_LA4_splited[2])) 
    eLA5.append(float(data_LA5_splited[2])) 
    
    CN1.append(float(data_CN1_splited[1]))
    CN2.append(float(data_CN2_splited[1])) 
    CN3.append(float(data_CN3_splited[1])) 
    CN4.append(float(data_CN4_splited[1])) 
    CN5.append(float(data_CN5_splited[1])) 
    
    eCN1.append(float(data_CN1_splited[2]))
    eCN2.append(float(data_CN2_splited[2])) 
    eCN3.append(float(data_CN3_splited[2])) 
    eCN4.append(float(data_CN4_splited[2])) 
    eCN5.append(float(data_CN5_splited[2])) 
    
    dtLA1.append(float(data_dtLA1_splited[1])) 
    dtLA2.append(float(data_dtLA2_splited[1])) 
    dtLA3.append(float(data_dtLA3_splited[1])) 
    dtLA4.append(float(data_dtLA4_splited[1])) 
    
    dteLA1.append(float(data_dtLA1_splited[2])) 
    dteLA2.append(float(data_dtLA2_splited[2])) 
    dteLA3.append(float(data_dtLA3_splited[2])) 
    dteLA4.append(float(data_dtLA4_splited[2])) 
    
    i=i+1

plt.subplot(221)
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
plt.title("DuFort Frankel")
plt.xlim((0, 1))
plt.ylim((100, 300))
plt.legend(loc ='upper center')

plt.subplot(222)
plt.plot(x, RI1, 'b', label='approximation')
plt.plot(x, RI2, 'b')
plt.plot(x, RI3, 'b')
plt.plot(x, RI4, 'b')
plt.plot(x, RI5, 'b')
plt.plot(x, AN1, 'r', label='analytical')
plt.title("Richardson")
plt.xlim((0, 1))
plt.legend(loc ='upper right')

plt.subplot(223)
plt.plot(x, LA1, 'b', label='approximation')
plt.plot(x, LA2, 'b')
plt.plot(x, LA3, 'b')
plt.plot(x, LA4, 'b')
plt.plot(x, LA5, 'b')
plt.plot(x, AN1, 'r', label='analytical')
plt.plot(x, AN2, 'r')
plt.plot(x, AN3, 'r')
plt.plot(x, AN4, 'r')
plt.plot(x, AN5, 'r')
plt.title("Laasonen")
plt.xlim((0, 1))
plt.ylim((100, 300))
plt.legend(loc ='upper center')

plt.subplot(224)
plt.plot(x, CN1, 'b', label='approximation')
plt.plot(x, CN2, 'b')
plt.plot(x, CN3, 'b')
plt.plot(x, CN4, 'b')
plt.plot(x, CN5, 'b')
plt.plot(x, AN1, 'r', label='analytical')
plt.plot(x, AN2, 'r')
plt.plot(x, AN3, 'r')
plt.plot(x, AN4, 'r')
plt.plot(x, AN5, 'r')
plt.title("Crank Nicholson")
plt.xlim((0, 1))
plt.ylim((100, 300))
plt.legend(loc ='upper center')

plt.show()

plt.subplot(221)
plt.plot(x, eDFF1, 'red', label='T = 0.1h')
plt.plot(x, eDFF2, 'magenta', label='T = 0.2h')
plt.plot(x, eDFF3, 'green', label='T = 0.3h')
plt.plot(x, eDFF4, 'blue', label='T = 0.4h')
plt.plot(x, eDFF5, 'brown', label='T = 0.5h')
plt.title("DuFort Frankel Error")
plt.xlim((0, 1))
plt.ylim((-1, 5))
plt.legend(loc ='upper center')

plt.subplot(222)
plt.plot(x, eRI1, 'red', label='T = 0.1h')
plt.plot(x, eRI2, 'magenta', label='T = 0.2h')
plt.plot(x, eRI3, 'green', label='T = 0.3h')
plt.plot(x, eRI4, 'blue', label='T = 0.4h')
plt.plot(x, eRI5, 'brown', label='T = 0.5h')
plt.title("Richardson Error")
plt.xlim((0, 1))
plt.legend(loc ='lower left')

plt.subplot(223)
plt.plot(x, eLA1, 'red', label='T = 0.1h')
plt.plot(x, eLA2, 'magenta', label='T = 0.2h')
plt.plot(x, eLA3, 'green', label='T = 0.3h')
plt.plot(x, eLA4, 'blue', label='T = 0.4h')
plt.plot(x, eLA5, 'brown', label='T = 0.5h')
plt.title("Laasonen Error")
plt.xlim((0, 1))
plt.ylim((-3, 1.5))
plt.legend(loc ='lower center')

plt.subplot(224)
plt.plot(x, eCN1, 'red', label='T = 0.1h')
plt.plot(x, eCN2, 'magenta', label='T = 0.2h')
plt.plot(x, eCN3, 'green', label='T = 0.3h')
plt.plot(x, eCN4, 'blue', label='T = 0.4h')
plt.plot(x, eCN5, 'brown', label='T = 0.5h')
plt.title("Crank Nicholson Error")
plt.xlim((0, 1))
plt.ylim((-0.3, 1))
plt.legend(loc ='upper center')

plt.show()

plt.subplot(211)
plt.plot(x, dtLA1, 'red', label='dt = 0.01')
plt.plot(x, dtLA2, 'magenta', label='dt = 0.025')
plt.plot(x, dtLA3, 'green', label='dt = 0.05')
plt.plot(x, dtLA4, 'blue', label='dt = 0.1')
plt.title("Laasonen")
#plt.xlim((0, 1))
#plt.ylim((-3, 1.5))
plt.legend(loc ='upper center')

plt.subplot(212)
plt.plot(x, dteLA1, 'red', label='dt = 0.01')
plt.plot(x, dteLA2, 'magenta', label='dt = 0.025')
plt.plot(x, dteLA3, 'green', label='dt = 0.05')
plt.plot(x, dteLA4, 'blue', label='dt = 0.1')
plt.title("Laasonen Error")
#plt.xlim((0, 1))
#plt.ylim((-0.3, 1))
plt.legend(loc ='lower center')

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

fileLA1.close()
fileLA2.close()
fileLA3.close()
fileLA4.close()
fileLA5.close()

fileCN1.close()
fileCN2.close()
fileCN3.close()
fileCN4.close()
fileCN5.close()

filedtLA1.close()
filedtLA2.close()
filedtLA3.close()
filedtLA4.close()