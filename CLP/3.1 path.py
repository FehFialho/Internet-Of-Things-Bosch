import pyads
import time
from collections import deque

# ------------------------
# CONFIGURAÇÃO DE CONEXÃO COM CLP
# ------------------------
TARGET_AMS_NET_ID = '10.234.199.82.1.1'
ADS_PORT = 851
TARGET_IP = '10.234.199.82'

plc = pyads.Connection(TARGET_AMS_NET_ID, ADS_PORT, TARGET_IP)

# ------------------------
# POSIÇÕES
# ------------------------
positions = {
    0: "PHOME",
    1: "P1",
    2: "P2",
    3: "P3",
    4: "P4",
    5: "P5",
}

# ------------------------
# FILAS
# ------------------------
path = deque()
gripper_queue = deque()

# ------------------------
# FUNÇÃO DE PROCESSAMENTO DO ROBÔ
# ------------------------
def processar_fila():
    while True:
        # MOVIMENTO DO ROBÔ
        if path:
            destino = path[0]  # peek sem remover
            robot_status = plc.read_by_name("GVL.robotStatus", pyads.PLCTYPE_INT)
            if robot_status == 1:
                destino = path.popleft()  # só remove se vai mover
                print(f"\nMovendo para {destino} ({positions[destino]})")
                plc.write_by_name("GVL.position", destino, pyads.PLCTYPE_INT)

                # Espera o robô chegar
                tempo_max = 10
                inicio = time.time()
                while True:
                    pos_atual = plc.read_by_name("GVL.position", pyads.PLCTYPE_INT)
                    if pos_atual == destino:
                        print(f"Chegou em {destino} ({positions[destino]})")
                        break
                    if time.time() - inicio > tempo_max:
                        print(f"ERRO: Timeout ao chegar em {destino} ({positions[destino]})")
                        break
                    time.sleep(0.1)
            else:
                print("Robô ocupado, aguardando...")
        
        # COMANDOS DA GARRA
        if gripper_queue:
            comando = gripper_queue.popleft()
            plc.write_by_name("GVL.gripperStatus", comando, pyads.PLCTYPE_INT)
            print(f"Garra {'Aberta' if comando else 'Fechada'}")

        time.sleep(0.1)  # pausa pequena para não travar o loop

# ------------------------
# INICIALIZAÇÃO
# ------------------------
with plc:
    print(f"Conectado ao CLP: {plc.ip_address}")
    
    # Posição inicial
    plc.write_by_name("GVL.position", 0, pyads.PLCTYPE_INT)
    plc.write_by_name("GVL.gripperStatus", 0, pyads.PLCTYPE_INT)  # garra fechada

    running = True

    # Loop principal: adiciona itens na fila
    while running:
        print("\nFila atual:", list(path))
        
        # --- Posição ---
        try:
            mover = int(input("Insira posição desejada (ou negativo para sair): "))
        except ValueError:
            print("Insira um número válido!")
            continue

        if mover < 0:
            running = False
            break

        if mover not in positions:
            print("Posição inválida!")
            continue

        path.append(mover)

        # --- Garra ---
        try:
            garra = int(input("Abrir garra? (0 = fechar, 1 = abrir): "))
        except ValueError:
            print("Insira 0 ou 1")
            continue

        if garra not in (0, 1):
            print("Valor inválido! Use 0 ou 1")
            continue

        gripper_queue.append(garra)

        # PROCESSA A FILA (não bloqueante)
        while path or gripper_queue:
            destino = path[0] if path else None
            if destino is not None:
                if plc.read_by_name("GVL.robotStatus", pyads.PLCTYPE_INT) == 1:
                    destino = path.popleft()
                    print(f"\nMovendo para {destino} ({positions[destino]})")
                    time.sleep(1) # Apenas para simulação!
                    
                    plc.write_by_name("GVL.position", destino, pyads.PLCTYPE_INT)

                    tempo_max = 10
                    inicio = time.time()
                    while True:
                        pos_atual = plc.read_by_name("GVL.position", pyads.PLCTYPE_INT)
                        if pos_atual == destino:
                            print(f"Chegou em {destino} ({positions[destino]})")
                            break
                        if time.time() - inicio > tempo_max:
                            print(f"ERRO: Timeout ao chegar em {destino} ({positions[destino]})")
                            break
                        time.sleep(0.1)
                else:
                    break  # sai do while e continua input

            # Comando da garra
            if gripper_queue:
                comando = gripper_queue.popleft()
                plc.write_by_name("GVL.gripperStatus", comando, pyads.PLCTYPE_INT)
                print(f"Garra {'Aberta' if comando else 'Fechada'}")
            else:
                break