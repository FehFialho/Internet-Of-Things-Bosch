import pyads

TARGET_AMS_NET_ID = '192.168.56.1.1.1'
ADS_PORT = 851
TARGET_IP = '10.234.194.222'

plc = pyads.Connection(TARGET_AMS_NET_ID, ADS_PORT, TARGET_IP)

with plc:
    print(f"Conexão com: {plc.ip_address}")
    
    num = int(input("Digite um número: "))
    is_written = plc.write_by_name("GVL.tempo", num, pyads.PLCTYPE_INT)
    
    result = plc.read_by_name("GVL.tempo", pyads.PLCTYPE_INT)
    print(result)