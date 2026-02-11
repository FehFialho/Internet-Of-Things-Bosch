import pyads
import time
from collections import deque

# ------------------------
# CONEXÃO COM CLP
# ------------------------

plc = pyads.Connection('192.168.0.1.1.1', 851)
plc.open()

# ------------------------
# GRAFO
# ------------------------

grafo = {
    0: [1],        # HOME -> 1
    1: [0, 2, 3],  # 1 -> HOME, 2, 3
    2: [1],        # 2 -> 1 (só volta para 1)
    3: [1, 4],     # 3 -> 1 ou 4
    4: [3]         # 4 -> 3 (só volta)
}

# ------------------------
# BFS
# ------------------------

def achar_caminho(inicio, fim):
    fila = deque([[inicio]])
    visitados = set()

    while fila:
        caminho = fila.popleft()
        ponto = caminho[-1]

        if ponto == fim:
            return caminho

        if ponto not in visitados:
            visitados.add(ponto)

            for vizinho in grafo[ponto]:
                novo = list(caminho)
                novo.append(vizinho)
                fila.append(novo)

    return None

# ------------------------
# MOVIMENTO REAL VIA CLP
# ------------------------

def mover_para(destino):
    # Lê posição atual do CLP
    posicao = plc.read_by_name("GVL.position", pyads.PLCTYPE_INT)

    caminho = achar_caminho(posicao, destino)
    print("Caminho calculado:", caminho)

    for ponto in caminho[1:]:
        print("Indo para", ponto)

        # Escreve destino no CLP
        plc.write_by_name("GVL.targetPosition", ponto, pyads.PLCTYPE_INT)

        # Espera o robô chegar
        while True:
            posicao = plc.read_by_name("GVL.position", pyads.PLCTYPE_INT)
            if posicao == ponto:
                break
            time.sleep(0.1)

# ------------------------
# MISSÃO COMPLETA
# ------------------------

print("Indo pegar garrafa (P4)")
mover_para(4)

print("Fechando garra")
plc.write_by_name("GVL.gripperStatus", 1, pyads.PLCTYPE_INT)

time.sleep(1)

print("Indo deixar em P2")
mover_para(2)

print("Abrindo garra")
plc.write_by_name("GVL.gripperStatus", 0, pyads.PLCTYPE_INT)

print("Voltando para HOME")
mover_para(0)

plc.close()