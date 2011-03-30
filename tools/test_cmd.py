#!/usr/bin/python
# -*- coding: iso-8859-15 -*-

import serial
import threading
import struct

port 	= "/dev/ttyUSB0"
debit	= 115200

class test_CM:
    
    def __init__(self, port, baudrate):
        try:
            self.serial = serial.Serial(port, baudrate, bytesize=8, parity='N', stopbits=1, timeout=1)
            self.databufout = ""
            self.lastdatabufout = ""
            self.lastdatabufin = ""
            print "Connexion reussie au port " + port + " a " + str(debit)
        except serial.SerialException:
            print "Erreur lors de la connion au port " + port
        
    def start(self):
        self.alive = True
        # start serial->console thread
        self.receiver_thread = threading.Thread(target=self.reader)
        self.receiver_thread.setDaemon(1)
        self.receiver_thread.start()
        # enter console->serial loop
        self.transmitter_thread = threading.Thread(target=self.writer)
        self.transmitter_thread.setDaemon(1)
        self.transmitter_thread.start()

    def stop(self):
        self.alive = False
    
    def reader(self):
        try:
            while self.alive:
                self.databufin = self.serial.readline()
                if self.lastdatabufin != self.databufin:
                    self.traitReponse(self.lastdatabufin)
                    self.lastdatabufin = self.databufin
                #readline(size=None,eol = caractere fin de ligne)
                print self.databufin
                # traitement de la trame
                # if ... then self.receiver_thread.Event.set()
        except serial.SerialException, e:
            self.alive = False
            print "Erreur de connexion read"
        
    def writer(self):
        try:
            while self.alive:
                if self.databufout != self.lastdatabufout:
                    try:
                        self.serial.write(self.databufout)
                        self.lastdatabufout = self.databufout
                        break
                    except serial.SerialException, e:
                        print "Erreur de connexion write"
        except:
            self.alive = False
            print "connexion interrompue"
            
    # Traiemente de la réponse série
    def traitReponse(self, data):
        # trame valide ?
        if(data[0]=='A' and data[1]=='B' and data[2]=='C'):
            try:
                print "OK : "
#                result = {
#                  'a': truc1(),
#                  'b': truc2(),
#                  'c': truc3()
#                }[data](x)))
            except:
                pass
                # else
                # on bloque le thread
                #traitReponse.Lock
#        else
#            print "trame invalide ! : "
       
    # obtenir l'etat du blocage
    def  blocking_get(self):
        cmd = 3
        self.databufout = struct.pack('3sb2s','ABC', cmd,'\n')
        self.writer()
        # ajouter test de la variable (delai rcv ?)
    
    # reset du blocage
    def  blocking_reset(self):
        cmd = 4
        self.databufout = struct.pack('3sb2s','ABC',  cmd,  '\n')
        self.writer()

    # envoi position moteur forward
    def goto_direct_forward(self, pos_x, pos_y):
        cmd = 6
        self.databufout  = struct.pack('3sbhh2s','ABC', cmd,  pos_x,  pos_y,  '\n')
        self.writer()
    
    # envoi position moteur back
    def goto_direct_backward(self, pos_x, pos_y):
        cmd = 7
        self.databufout  = struct.pack('3sbhh2s','ABC', cmd,  pos_x,  pos_y,  '\n')
        self.writer()

    # envoi position moteur all
    def goto_direct_all(self, pos_x, pos_y):
        cmd = 8
        self.databufout  = struct.pack('3sbhh2s','ABC', cmd,  pos_x,  pos_y,  '\n')
        self.writer()
        
    # retourne la position du robot
    def  position_get(self):
        cmd = 12
        self.databufout = struct.pack('3sb2s','ABC', cmd ,  '\n')
        self.writer()
        self.reader()
        
    # Regle la position du robot
    def position_set(self, pos_x, pos_y, angle):
        cmd = 13
        self.databufout  = struct.pack('3sbhhh2s','ABC',cmd,  pos_x,  pos_y,  angle,  '\n')
        self.writer()
        
    # Enclenche la puissance du robot
    def  power_on(self):
        cmd = 14
        self.databufout = struct.pack('3sb2s','ABC', cmd,  '\n')
        self.writer()
        
    #  Denclenche la puissance du robot
    def  power_off(self):
        cmd = 15
        self.databufout = struct.pack('3sb2s','ABC', cmd, '\n')
        self.writer()
        
    # Fige le robot
    def hard_stop(self):
        cmd = 16
        self.databufout = struct.pack('3sb2s','ABC', cmd,  '\n')
        self.writer()
        
    # reset de la carte
    def  reset(self):
        cmd = 17
        self.databufout = struct.pack('3sb2s','ABC',  cmd,  '\n')
        self.writer()
    
    # Regle la vitesse des trajectoires
    def  speed(self, dist, angle):
        cmd = 18
        self.databufout = struct.pack('3sbhh2s','ABC', cmd,   dist,  angle,  '\n')
        self.writer()
        
    # Arrete le robot sur une distance
    def  stop(self):
        cmd = 19
        self.databufout = struct.pack('3sb2s','ABC', cmd,  '\n')
        self.writer()
       
    # Retourne si le robot est en deplacement ou non
    def  traj_finished(self):
        cmd = 20
        self.databufout = struct.pack('3sb2s','ABC', cmd,  '\n')
        self.writer()
        
    # Tourne jusqu'a un angle (absolu)
    def  turn_to(self, angle):
        cmd = 21
        self.databufout = struct.pack('3sbh2s','ABC', cmd,  angle,  '\n')
        self.writer()
        
    # Regle les seuils de fin de trajectoire
    def  windows(self, dist,  angle,  angle_start):
        cmd = 22
        self.databufout = struct.pack('3sbhhh2s','ABC', cmd,  dist,  angle,  angle_start,  '\n')
        self.writer()
        
    # PID angle
    def pid_angle(self, Kp, Ki, Kd):
        cmd = 23
        self.databufout = struct.pack('3sbhhh2s','ABC',cmd,  Kp,  Ki,  Kd,  '\n')
        self.writer()
        
    # PID distance
    def pid_distance(self, Kp, Ki, Kd):
        cmd = 24
        self.databufout = struct.pack('3sbhhh2s','ABC', cmd,  Kp,  Ki,  Kd,  '\n')
        self.writer()
        
    #wheel_corection_factor
    def wheel_corection_factor(self, factor):
        cmd = 25
        self.databufout = struct.pack('3sbi2s', 'ABC',cmd, factor,  '\n')
        self.writer()
    
    def asciiToBin(lettre): 
        lettre = ord(lettre) 
        retour =[] 
        for i in range(8,-1,-1): 
            if lettre -2**i >= 0: 
                lettre -= 2**i 
                retour.append('1') 
            else: 
                lettre.append('0') 
        return "".join(retour) 

    def binaire(chaine): 
        retour =[asciiToBin(lettre) for lettre in chaine] 
        return "".join(retour) 
        
    def strTobin(val):
        for c in val:
            print(bin(ord(c)))[2:]
        
    # renvoie une chaine en octet    
    def hexify( octets ):
        return ":".join( [ '%x'%(ord(c)) for c in octets ] )
        
test = test_CM(port, debit)
test.start()
test.position_get()
#test.writer()
#test.reader()
##print test.databufin
#test.writer()
test.stop()
print "fin"
