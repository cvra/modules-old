from math import *
import psyco
psyco.full()

def findCircle(samples, radius):
    xMax=300
    yMax=300
    bestY, bestX, bestDistance=0,0,1e6
    # We init the Acumulation Array with 0s
    a=[0]*yMax
    AccumulationArray=[a*xMax]
    
    
    for x in range(xMax):
        for y in range(yMax):
            # Distance from each sample to the circle (x;y;radius)
            w=[abs(sqrt((x-s[0])**2 + (y-s[1])**2)-radius) for s in samples]
            distance=sum(w)
            if distance < bestDistance:
                bestX, bestY, bestDistance=x,y,distance

    return (bestX, bestY, bestDistance)
    
    
print findCircle([(3,4.1),(5,1.9), (2.5,2.8)], 2)
