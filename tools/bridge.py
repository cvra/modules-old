import socket
# from threading import Thread
from thread import *

from sys import argv

import serial

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# associate the socket with a port
s.bind(('', int(argv[1])))

robot = serial.Serial("/dev/ttyUSB0", baudrate=57600, timeout = 1)


class SerialToTcpThread(Thread):
	
	def __init__(self, sock):
		Thread.__init__(self)
		self.running = True
		self.conn = sock
		
		
	def run(self):
		while self.running:
			c = robot.read(1)
			self.conn.write(c)

	def kill(self):
		self.running = False
		print("Waiting for kill")

class TcpToSerialThread(Thread):
	def __init__(self):
		Thread.__init__(self)
		self.running = True
	
	def run(self):
		
		# accept "call" from client
		print("Start waiting client")
		s.listen(1)
		conn, addr = s.accept()
		print('client is at' + str(addr))
		
		thread = SerialToTcpThread(conn)
		thread.start()
		
		while self.running:
			try:
				data = conn.recv(1024)
			except:
				data = 0
			if data == 0:
				break
			print(data)
			
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
	
