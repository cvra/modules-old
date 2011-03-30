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
        self.kingRadius=8
        self.pawnRadius=15
        self.kingMargin=2
        
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
            
        
        # On recommence pour le 2eme etage
        firstSeen=self.sampleCounter
        lastSeen=0
        for s in self.samples:
            # Detection du front montant
            if(s[3] and s[4] < firstSeen):
                firstSeen=s[4]
                
            # Detection du front descendant
            if(s[3] and s[4] > lastSeen):
                lastSeen=s[4]
                
        # Si on a vu un mid on calcule son diametre sinon on fait rien
        if(lastSeen>=firstSeen):
            topRadius=(self.samples[lastSeen][0]-self.samples[firstSeen][0])**2 + (self.samples[lastSeen][1]-self.samples[firstSeen][1])**2
            topRadius=sqrt(topRadius)
            topRadius = topRadius/2
        else:
            topRadius=-1

        
        return (bestX, bestY, bestDistance, midRadius, topRadius)
    
    
    # Cette fonction ne marche que si c'est au dimensions coupe en cm
    def analyze(self):
        tower = self.findCircle()
        
        print "Result of algorithm : "+repr(tower)
        
        towerType="pawn"
        # On a vu de la merde. A calibrer
        if(tower[2] > self.sampleCounter*5):
            towerType="not tower"
        # On vu un roi
        else:
            if (tower[3] > 0 and tower[3] < self.kingRadius and tower[4]==-1):
                towerType="king"
            # On a vu un roi et un pion
            elif(tower[3] > 0 and tower[3] > (self.kingRadius) and \
               tower[4] > 0 and tower[4] < self.kingMargin):
                   towerType="pawn+king"
            elif(tower[3] > 0 and tower[3] > (self.kingRadius) and \
               tower[4] > 0 and tower[4] > (self.kingRadius)):
                towerType="pawn+pawn+king"
        
        return (tower[0], tower[1], towerType)
                
    
    # Affiche les points. Requiert pyplot.
    def show(self):
        try:
            import matplotlib.pyplot as plt
        except:
            print "Pas de pyplot, pas de graphe"
            return
        
        x = []
        y = []
        
        for s in self.samples:
            plt.plot(s[0], s[1], 'ro')
        
        
        plt.axis([0, 300, 0, 210])
        
        plt.show()
    
if __name__=="__main__":
    print "CVRA Scanner 1.0"
    scan=ObjectDetector(radius=1)
    scan.setDetectionZone()
    
    print "====== Cercle C(1,0) r=1 ======"
    # Les points correspondent a un C(1,0) et r=1
    scan.addSample(0.03, 0.23)
    scan.addSample(0.23, 0.64)
    scan.addSample(0.83,1)
    scan.addSample(0.5,1)
    print scan.findCircle()
    
    
    print "====== Droite ======"
    scan=ObjectDetector(radius=15)
    scan.setDetectionZone(xMax=300, yMax=210)
    scan.addSample(0., 0.)
    scan.addSample(0., 10)
    scan.addSample(0., 15)
    scan.addSample(0., 20)
    scan.addSample(0., 25)
    scan.addSample(0., 30)
    scan.addSample(0., 35)
    scan.addSample(0., 40)
    scan.addSample(0., 45)
    scan.addSample(0., 50)
    scan.addSample(0., 55)
    scan.addSample(0., 60)
    scan.addSample(0., 65)  
    scan.addSample(0., 70)
    scan.addSample(0., 75)
    scan.addSample(0., 80)
    scan.addSample(0., 85)
    scan.addSample(0., 90)
    print scan.analyze()
    
    
    print "====== Roi en (120, 103) ======"
    
    # Simulation de la table
    # Le pion est en (120, 103) et c'est un roi
    # Il y a en moyenne un centimetre de bruit
    scan=ObjectDetector(radius=15)
    scan.setDetectionZone(xMax=300, yMax=210)
    scan.addSample(105, 107, False)
    scan.addSample(105, 100, False)
    scan.addSample(110, 115, True)
    scan.addSample(105, 100, True)
    scan.addSample(115, 118, True)
    scan.addSample(118, 118, True)
    scan.addSample(122, 118, False)
    scan.addSample(105, 100, False)
    scan.addSample(129, 116, False)
    print scan.analyze()
    
    print "====== Pion+Roi (120, 103) ======"
    # Pion plus roi pos (120, 103)
    scan=ObjectDetector(radius=15)
    scan.setDetectionZone(xMax=300, yMax=210)
    scan.addSample(105, 107, True, False)
    scan.addSample(105, 100, True, False)
    scan.addSample(110, 115, True, True)
    scan.addSample(105, 100, True, True)
    scan.addSample(115, 118, True, True)
    scan.addSample(118, 118, True, True)
    scan.addSample(122, 118, True, False)
    scan.addSample(105, 100, True, False)
    scan.addSample(129, 116, True, False)
    print scan.analyze()
    
    print "====== Robot carre ======"
    scan=ObjectDetector(radius=15)
    scan.setDetectionZone(xMax=300, yMax=210)
    scan.addSample(71, 105)
    scan.addSample(65, 107)
    scan.addSample(58, 108)
    scan.addSample(57, 103)
    scan.addSample(53, 87)
    scan.addSample(52, 82)
    print scan.analyze()
    
    print "====== Rotation avec un roi en (147, 85) ======"
    scan=ObjectDetector(radius=15)
    scan.setDetectionZone(xMax=300, yMax=210)
    scan.addSample(133, 80, midSensor=False, topSensor=False)
    scan.addSample(132, 85, midSensor=False, topSensor=False)
    scan.addSample(133, 90, midSensor=True, topSensor=False)
    scan.addSample(136, 94, midSensor=True, topSensor=False)
    scan.addSample(137, 96, midSensor=True, topSensor=False)
    scan.addSample(132, 85, midSensor=False, topSensor=False)
    scan.addSample(136, 95, midSensor=True, topSensor=False)
    scan.addSample(133, 80, midSensor=True, topSensor=False)
    scan.addSample(141, 98, midSensor=True, topSensor=False)
    scan.addSample(150, 100, midSensor=True, topSensor=False)
    scan.addSample(158, 95, midSensor=False, topSensor=False)
    scan.addSample(160, 91, midSensor=False, topSensor=False)
    print scan.analyze()
    
    scan.show()
    
    
    
    
    
    
    
    
    
    
    
