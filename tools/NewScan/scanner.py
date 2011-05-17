import math

class Point:
    def __init__(self, x, y):
        self.x=x
        self.y=y
        
    def distance(self, other):
        return math.sqrt((self.x-other.x)**2+(self.y-other.y)**2)

class Sample:
    "Une classe qui gere une lecture du scanner"
    magicDistance = 89.3
    def __init__(self, x, y, angle, distance, floorSensor=False):
        self.x=x
        self.y=y
        self.angle=angle
        self.distance=distance
        self.floorSensor=floorSensor
        
    def getRobotPosition(self):
        return Point(self.x, self.y)
        
    def getBasePoint(self):
        return Point(self.x + self.distance*math.cos(self.angle),
                self.y + self.distance*math.sin(self.angle))
                
    def getFloorPoint(self):
        return Point(self.x + (self.distance+self.magicDistance)*math.cos(self.angle),
                self.y + (self.distance+self.magicDistance)*math.sin(self.angle))

class Scanner:
    def __init__(self, radius=150):
        self.radius = radius
        self.samples = []
        self.xMin, self.xMax = 0, 3000
        self.yMin, self.yMax = 0, 2100
        
    def addSample(self, x, y, angle, distance, floorSensor=False):
       self.samples.append(Sample(x, y, angle, distance, floorSensor))


    def findCircle(self, debug=False):
        if debug:
            try:
                import matplotlib.pyplot as plt
            except:
                print "Pas de pyplot, pas de graphe"
                return
            
            for s in self.samples:
                plt.plot(s.getBasePoint().x, s.getBasePoint().y, 'ro')
            
            
            
        
        bestPoint, bestDistance=Point(0,0),1e7
        basePoints=[a.getBasePoint() for a in self.samples]   
        for x in range(self.xMin, self.xMax, 10):
            for y in range(self.yMin, self.xMax, 10):
                currentPoint = Point(x,y)
                distance = sum([abs(currentPoint.distance(a)-self.radius) for a in basePoints])
                if distance < bestDistance:
                    bestDistance = distance
                    bestPoint = currentPoint
                 

        if debug:
            for i in range(50):
                plt.plot(self.radius*math.cos(2*3.14*i/50.)+bestPoint.x, self.radius*math.sin(2*3.14*i/50.)+bestPoint.y, 'bo')
            
        # Ici il faudrait utiliser le telemetre
        firstSeenBase = self.samples[0]
        firstSeenFloor= self.samples[-1]
        floorSeen = False
        
        for s in self.samples:
            if s.floorSensor:
                firstSeenFloor=s
                floorSeen=True
                break
                
        
        if floorSeen:
            radiusDifference = firstSeenBase.getBasePoint().distance(firstSeenFloor.getFloorPoint())
        else:
            radiusDifference = self.radius
        
        print "==== results ======="
        print radiusDifference
        print bestPoint.x
        print bestPoint.y
        print bestDistance

        if debug:
            plt.axis([0, 3000, 0, 2100])
            plt.show()

if __name__=="__main__":
    
    # (950;580)
    s = Scanner(radius=100)
    s.addSample(350, 410, angle=0.14, distance=570)
    s.addSample(360, 450, angle=0.11, distance=540)
    s.addSample(360, 480, angle=0.08, distance=520)
    s.addSample(360, 520, angle=0.17, distance=500)
    s.addSample(330, 550, angle=0.19, distance=570)
    s.findCircle(debug=False)
    
    # (670;720 r=200)
    s = Scanner(radius=200)
    s.addSample(120, 860, angle=0.07, distance=440, floorSensor=False)
    s.addSample(140, 770, angle=0.13, distance=350, floorSensor=False)
    s.addSample(210, 650, angle=0.21, distance=270, floorSensor=True)
    s.addSample(240, 550, angle=0.27, distance=260, floorSensor=True)
    s.addSample(280, 400, angle=0.37, distance=360, floorSensor=False)
    s.findCircle(debug=False)
