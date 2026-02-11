# remember to install pyads with pip!
import pyads

TARGET_AMS_NET_ID = '192.168.56.1.1.1'
ADS_PORT = 851
TARGET_IP = '10.234.194.222'

# connect to plc and open connection
plc = pyads.Connection(TARGET_AMS_NET_ID, ADS_PORT, TARGET_IP)

# to conn
# plc = pyads.Connection('10.234.195.153.1.1', pyads.PORT_TC3PLC1)

plc.open()

# read int value by name
i = plc.read_by_name("GVL.TEMPO")

print(i)

plc.close()