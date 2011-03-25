from math import *
import psyco
psyco.full()

class ObjectDetector:
    def __init__(self, radius=150):
        self.radius=radius
        self.samples=[]
        self.sampleCounter=0
        
    def addSample(self, x, y, midSensor=False, topSensor=False):
        self.samples.append((x,y,midSensor, topSensor, self.sampleCounter))
        self.sampleCounter=self.sampleCounter+1
        
    def setDetectionZone(self, xMin=0, xMax=10, yMin=0, yMax=10):
        self.xMin=xMin
        self.xMax=xMax
        self.yMin=yMin
        self.yMax=yMax
        
    def findCircle(self):
        bestY, bestX, bestDistance=0,0,1e6
        # We init the Acumulation Array with 0s
        a=[0]*self.yMax
        AccumulationArray=[a*self.xMax]
    
        # Detection du cercle de base
        for x in range(self.xMin, self.xMax):
            for y in range(self.yMin, self.yMax):
                # Distance from each sample to the circle (x;y;radius)
                w=[abs(sqrt((x-s[0])**2 + (y-s[1])**2)-self.radius) for s in self.samples]
                distance=sum(w)
                if distance < bestDistance:
                    bestX, bestY, bestDistance=x,y,distance


        # Detection d'un eventuel roi
        firstSeen=self.sampleCounter
        lastSeen=0
        for s in self.samples:
            
            # Detection du front montant
            if(s[2] and s[4] < firstSeen):
                firstSeen=s[4]
                
            # Detection du front descendant
            if(s[2] and s[4] > lastSeen):
                lastSeen=s[4]
            
            
        # Si on a vu un mid on calcule son diametre sinon on fait rien
        if(lastSeen>=firstSeen):
            midRadius=(self.samples[lastSeen][0]-self.samples[firstSeen][0])**2 + (self.samples[lastSeen][1]-self.samples[firstSeen][1])**2
            midRadius=sqrt(midRadius)
            midRadius = midRadius/2
        else:
            midRadius=-1
            

                
        print firstSeen, lastSeen
        
        return (bestX, bestY, bestDistance, midRadius)
    
    
if __name__=="__main__":
    print "CVRA Scanner 1.0"
    scan=ObjectDetector(radius=1)
    scan.setDetectionZone()
    # Les points correspondent a un C(1,0) et r=1
    scan.addSample(0.03, 0.23)
    scan.addSample(0.23, 0.64)
    scan.addSample(0.83,1)
    scan.addSample(0.5,1)
    print scan.findCircle()
    
    # Maintenant on teste le detecteur de tours
    # Ici on a un roi en C(0,1)
    scan=ObjectDetector(radius=1)
    scan.setDetectionZone()
    scan.addSample(0.,   0.,    midSensor=False)
    scan.addSample(0.2, -0.6,   midSensor=False)
    #scan.addSample(0.04, 0.28,  midSensor=True)
    scan.addSample(0.1,  0.5,   midSensor=True)
    scan.addSample(0.2,  0.6,   midSensor=True)
    scan.addSample(0.6,  0.9,   midSensor=True)
    scan.addSample(0.8,  1.,    midSensor=True)
    #scan.addSample(0.77, 0.97,  midSensor=True)
    scan.addSample(1.3,  1.0,   midSensor=False)
    scan.addSample(1.5,  0.8,   midSensor=False)
    print scan.findCircle()
    
    # Maintenant on teste avec des points sur une droite
    scan=ObjectDetector(radius=1)
    scan.setDetectionZone()
    scan.addSample(0., 0.)
    scan.addSample(0., 0.1)
    scan.addSample(0., 0.2)
    scan.addSample(0., 0.3)
    scan.addSample(0., 0.4)
    scan.addSample(0., 0.5)
    scan.addSample(0., 0.6)
    scan.addSample(0., 0.7)
    scan.addSample(0., 0.8)
    scan.addSample(0., 0.9)
    print scan.findCircle()
    
    
    
    
    
    
    
    
    
