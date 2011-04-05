import matplotlib.pyplot as plt
import sys

if(len(sys.argv) < 2):
    print "Error too few argument"
    quit()
    
f=open(sys.argv[1])

time=[]
distance=[]
angle=[]

for line in f:
    dat = line.split(" ")
    print dat
    time.append(int(dat[0]))
    distance.append(int(dat[1]))
    angle.append(int(dat[2]))

    
plt.plot(time, distance, "r-")
plt.plot(time, angle, "g-")
    
plt.show()
