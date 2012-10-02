#!/usr/bin/env python2

import socket
import struct

from threading import Thread

from sys import argv, exit

try:
	import serial
except:
	print("Cannot import Pyserial")

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# associate the socket with a port


if len(argv) < 3:
	print "Yo try to run me without port ? Better hide yo kids and yo woman !"
	print "Usage : "+argv[0]+" [ip port] [serial port]"
	exit(0)

s.bind(('', int(argv[1])))

robot = serial.Serial(argv[2], baudrate=57600, timeout = 1)


class SerialToTcpThread(Thread):
	
	def __init__(self, sock):
		Thread.__init__(self)
		self.running = True
		self.conn = sock
		self.packer = struct.Struct("B")
		robot.flushInput()
		
	def run(self):
		while self.running:
			c = robot.read(1)
			if len(c) != 0:		# Si on a pas timeout
				self.conn.send(self.packer.pack(ord(c)))

	def kill(self):
		self.running = False
		print("Waiting for kill")

class TcpToSerialThread(Thread):
	def __init__(self):
		Thread.__init__(self)
		self.running = True
	
	def run(self):
		
		print("Waiting for client...")
		# accept "call" from client
		s.listen(1)
		conn, addr = s.accept()
		print('client is at' + str(addr))
		conn.send("Bienvenue chez Procty, Robot proctologue \r\n")
		thread = SerialToTcpThread(conn)
		thread.start()
		
		while self.running:
			try:
				data = conn.recv(1)
			except:
				data = 0
			if data == 0:
				break
			robot.write(data)
			
		thread.kill()
			
		

	def kill(self):
		self.running = False
	

if __name__ == "__main__":
	t = TcpToSerialThread()
	t.start()
	
	try:
		while True:
			pass
	except:
		t.kill()
		print("Exit soon, flushing TCP/IP buffers...")
		s.close()
