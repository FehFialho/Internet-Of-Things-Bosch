import pyads
import time

TARGET_AMS_NET_ID = '192.168.56.1.1.1'
ADS_PORT = 851
TARGET_IP = '10.234.194.222'

plc = pyads.Connection(TARGET_AMS_NET_ID, ADS_PORT, TARGET_IP)

positions = {
    0: "PHOME",
    1: "P1",
    2: "P2",
    3: "P3",
    4: "P4",
    5: "P5",
}

with plc:
    print(f"Conexão com: {plc.ip_address}")
    
    # Default Position
    position = 0
    plc.write_by_name("GVL.position", 0, pyads.PLCTYPE_INT)
    gripperStatus = 0
    plc.write_by_name("GVL.gripperStatus", 0, pyads.PLCTYPE_INT)

    running = True  # Flag Loop

    while running:
        time.sleep(1)
        
        # Movendo Posição
        mover = int(input("Insira posição desejada (ou número negativo para sair): "))
        while mover not in positions:
            if mover < 0:
                running = False  # seta a flag para encerrar o loop principal
                break  # sai do loop interno
            mover = int(input("Insira uma posição válida: "))
        
        if not running:
            break  # sai do loop principal
        
        plc.write_by_name("GVL.position", mover, pyads.PLCTYPE_INT)
        
        # Movendo Garra
        garra = int(input("Abrir Garra (0 = Fechar, 1 = Abrir): "))
        while garra not in (0, 1):
            garra = int(input("Insira um valor válido: "))
        plc.write_by_name("GVL.gripperStatus", garra, pyads.PLCTYPE_INT)
        
        # Esperando
        print("Movendo...")
        time.sleep(1)