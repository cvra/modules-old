#!/usr/bin/python
# -*- coding: iso-8859-15 -*-

# Classe test pour la communication PC <-> Carte moteur
# Olivier Wenger coupe 2011 CVRA

import serial
import threading
import struct

port     = "/dev/ttyUSB0"
debit    = 115200

class test_CM:
    
    def __init__(self, port, baudrate):
        try:
            self.serial = serial.Serial(port, baudrate, bytesize=8, parity='N', stopbits=1, timeout=1)
            self.databufout = ""
            self.lastdatabufout = ""
            self.lastdatabufin = ""
            print "Connexion reussie au port " + port + " a " + str(debit)
        except serial.SerialException:
            print "Erreur lors de la connexion au port " + port
        
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

    def stopThread(self):
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
            
    # Traitement de la reponse a blocking_get
    def ret_blocking_get(self, trame):
        blocage, fin_Trame =  struct.unpack_from('B2s', trame,  offset=4)
        print "Etat blocage : " + blocage
        
    # Traitement de la reponse a goto_next_forward (fin etape)
    def ret_goto_next_forward(self):
        print "fin etape goto_next_forward"
        
    # Traitement de la reponse a position_get
    def ret_position_get(self, trame):
        get_pos_X, get_pos_Y, get_angle, fin_Trame = struct.unpack_from('3sBhhh2s', trame,  offset=4)
        print "get position X :" + get_pos_X + " Y : " + get_pos_Y + " angle : " + get_angle
        
    # Traitement de la reponse a trajet_finished
    def ret_trajet_finished(self):
        print "Trajet finished"
        
    # Traiemente de la réponse série
    def traitReponse(self, data):
        # trame valide ?
        if(data[0]=='A' and data[1]=='B' and data[2]=='C'):
            try:
                print "OK : "
                try:
                    {3: self.ret_blocking_get(data),
                     9: self.ret_goto_next_forward(),
                     12: self.ret_position_get(data),
                     20: self.ret_trajet_finished(data)}[data[3]]()
                except:
                    print "Valeur retour invalide !!"
            except:
                print "Trame invalide (ABC) !!"
                # else
                # on bloque le thread
                #traitReponse.Lock
       
    # obtenir l'etat du blocage
    def  blocking_get(self):
        cmd = 3
        self.databufout = struct.pack('3sB2s','ABC', cmd,'\n')
        self.writer()
        # ajouter test de la variable (delai rcv ?)
    
    # reset du blocage
    def  blocking_reset(self):
        cmd = 4
        self.databufout = struct.pack('3sB2s','ABC',  cmd,  '\n')
        self.writer()

    # envoi position moteur forward
    def goto_direct_forward(self, pos_x, pos_y):
        cmd = 6
        self.databufout  = struct.pack('3sBhh2s','ABC', cmd,  pos_x,  pos_y,  '\n')
        self.writer()
    
    # envoi position moteur back
    def goto_direct_backward(self, pos_x, pos_y):
        cmd = 7
        self.databufout  = struct.pack('3sBhh2s','ABC', cmd,  pos_x,  pos_y,  '\n')
        self.writer()

    # envoi position moteur all
    def goto_direct_all(self, pos_x, pos_y):
        cmd = 8
        self.databufout  = struct.pack('3sBhh2s','ABC', cmd,  pos_x,  pos_y,  '\n')
        self.writer()
        
    # retourne la position du robot
    def  position_get(self):
        cmd = 12
        self.databufout = struct.pack('3sB2s','ABC', cmd ,  '\n')
        self.writer()
        self.reader()
        
    # Regle la position du robot
    def position_set(self, pos_x, pos_y, angle):
        cmd = 13
        self.databufout  = struct.pack('3sBhhh2s','ABC',cmd,  pos_x,  pos_y,  angle,  '\n')
        self.writer()
        
    # Enclenche la puissance du robot
    def  power(self,  etat):
        cmd = 14
        self.databufout = struct.pack('3sBB2s','ABC', cmd, etat,  '\n')
        self.writer()
        
    # Fige le robot
    def hard_stop(self):
        cmd = 16
        self.databufout = struct.pack('3sB2s','ABC', cmd,  '\n')
        self.writer()
        
    # reset de la carte
    def  reset(self):
        cmd = 17
        self.databufout = struct.pack('3sB2s','ABC',  cmd,  '\n')
        self.writer()
    
    # Regle la vitesse des trajectoires
    def  speed(self, dist, angle):
        cmd = 18
        self.databufout = struct.pack('3sBhh2s','ABC', cmd,   dist,  angle,  '\n')
        self.writer()
        
    # Arrete le robot sur une distance
    def  stop(self):
        cmd = 19
        self.databufout = struct.pack('3sB2s','ABC', cmd,  '\n')
        self.writer()
       
    # Retourne si le robot est en deplacement ou non
    def  traj_finished(self):
        cmd = 20
        self.databufout = struct.pack('3sB2s','ABC', cmd,  '\n')
        self.writer()
        
    # Tourne jusqu'a un angle (absolu)
    def  turn_to(self, angle):
        cmd = 21
        self.databufout = struct.pack('3sBh2s','ABC', cmd,  angle,  '\n')
        self.writer()
        
    # Regle les seuils de fin de trajectoire
    def  windows(self, dist,  angle,  angle_start):
        cmd = 22
        self.databufout = struct.pack('3sBhhh2s','ABC', cmd,  dist,  angle,  angle_start,  '\n')
        self.writer()
        
    # Aimant avant
    def magnet_front(self, etat):
        cmd = 50
        self.databufout = struct.pack('3sBB2s',  'ABC', cmd,  etat,  '\n')
        self.writer()
        
    # Aimant avant
    def magnet_back(self, etat):
        cmd = 51
        self.databufout = struct.pack('3sBB2s',  'ABC', cmd,  etat,  '\n')
        self.writer()
        
    # Mode des bras
    # 0=desactive, 1=automatique, 2=pousser, 3=tirer (non implemente), 4=scan bordure, 5=prise de pion bordure, 6=prise de figures bordure
    def arm_mode(self, gauche,  droit):
        cmd = 100
        self.databufout = struct.pack('3sBBB2s',  'ABC', cmd,  gauche, droit,  '\n')
        self.writer()
        
    # drop : depose la tour
    def drop(self,  cote, pos_X, pos_Y),  :
        cmd = 101
        self.databufout = struct.pack('3sBhhh2s',  'ABC', cmd,  gauche, droit,  '\n')
        self.writer()
    
    # Calibration des bras A NE PAS UTILISER EN MATCH !!!!!!!
    def  arm_calibration(self):
        cmd = 102
        self.databufout = struct.pack('3sB2s',  'ABC', cmd,  '\n')
        self.writer()  
    
    # Anciennes commandes
        
    # PID angle
    def pid_angle(self, Kp, Ki, Kd):
        cmd = 23
        self.databufout = struct.pack('3sBhhh2s','ABC',cmd,  Kp,  Ki,  Kd,  '\n')
        self.writer()
        
    # PID distance
    def pid_distance(self, Kp, Ki, Kd):
        cmd = 24
        self.databufout = struct.pack('3sBhhh2s','ABC', cmd,  Kp,  Ki,  Kd,  '\n')
        self.writer()
        
    #wheel_corection_factor
    def wheel_corection_factor(self, factor):
        cmd = 25
        self.databufout = struct.pack('3sBi2s', 'ABC',cmd, factor,  '\n')
        self.writer()
    
################################# Fonctions annexes inutilisees #########
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
        
# banc de test
test = test_CM(port, debit)
test.start()
test.power_on()
test.goto_direct_forward(100, 211)
test.position_get()
test.stop()
print "fin"
