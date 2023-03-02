import canopen
import time
import sys, tty, termios

EDS_FILE = "maxon_motor_IDX_0170h_6650h_0000h_0000h.eds"        #EDS file.
MOLTIPLICATORE = 10



def initCANopen(BaudRate = 1e6):    #Default Parameter.
# M: Initialize CANopen.                                                    :M #
        nw = canopen.Network()   #NetWork.
        nw.connect(channel='can0', bustype='socketcan', bitrate=1000000)
        node = nw.add_node(1, EDS_FILE)
        return nw,node

def PrintDictionary(node):
	print("\nNode", node, "dictionary:")
	for obj in s60.object_dictionary.values():
		print(obj.index, obj.name)
	print("")

def getchartest():
	fd = sys.stdin.fileno()
	old_settings = termios.tcgetattr(fd)
	try:
		tty.setraw(sys.stdin.fileno())
		ch = sys.stdin.read(1)
	finally:
		termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
	return ch


if __name__=="__main__":
	network, s60 = initCANopen()

	PrintDictionary(s60)

	s60.nmt.state = 'OPERATIONAL'
	print("Gone Operational")
	# Write Node-ID
	# s60.sdo.download(0x2000,0,b'\x01')
	# Read actual position
	# print(int.from_bytes(s60.sdo.upload(0x6064,0), "little"))
	# # Read Node-ID
	# print(int.from_bytes(s60.sdo.upload(0x2000,0), "little"))
	# print(int.from_bytes(s60.sdo.upload(0x6061,0), "little"))

	# Enable device
	s60.sdo.download(0x6060,0,b'\x01')
	s60.sdo.download(0x6040,0,b'\x06\x00')
	s60.sdo.download(0x6040,0,b'\x0F\x00')

	pos = 0
	while True:
		a = getchartest()
		if a == 'd':
			pos = pos+1000
			# if pos > 20000:
			# pos = 20000
			print(pos)
			# invio l'angolo attuale
			s60.sdo.download(0x607A,0,(pos).to_bytes(4, 'little', signed=True))
			# Control Motor
			# 0x0F abilita
			s60.sdo.download(0x6040,0,b'\x0F\x00')
			# 0x1F attua
			s60.sdo.download(0x6040,0,b'\x1F\x00')
		if a == 'a':
			pos = pos-1000
			# if pos < -10000:
			# pos = -10000
			print(pos)
			s60.sdo.download(0x607A,0,(pos).to_bytes(4, 'little', signed=True))
			# Control Motor
			s60.sdo.download(0x6040,0,b'\x0F\x00')
			s60.sdo.download(0x6040,0,b'\x1F\x00')
		if a == 'q':
			# Disable Device
			s60.sdo.download(0x6040,0,b'\x0B\x00')
			s60.sdo.download(0x6040,0,b'\x00\x00')
			break

print("Finito :-)")