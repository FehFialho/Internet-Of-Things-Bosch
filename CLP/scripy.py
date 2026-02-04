import pyads

# connect to plc and open connection
plc = pyads.Connection('10.234.195.153.1.1', pyads.PORT_TC3PLC1)
plc.open()

# read int value by name
i = plc.read_by_name("GVL.tempo")

print(i)

plc.close()