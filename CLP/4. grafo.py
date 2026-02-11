from collections import deque

# ----- GRAFO CORRIGIDO -----
# 0 = HOME, 1 = P1, 2 = P2, 3 = P3, 4 = P4
grafo = {
    0: [1],        # HOME -> 1
    1: [0, 2, 3],  # 1 -> HOME, 2, 3
    2: [1],        # 2 -> 1 (só volta para 1)
    3: [1, 4],     # 3 -> 1 ou 4
    4: [3]         # 4 -> 3 (só volta)
}

# ----- FUNÇÃO PARA ACHAR CAMINHO (BFS simples) -----
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
                novo_caminho = list(caminho)
                novo_caminho.append(vizinho)
                fila.append(novo_caminho)

    return None

# ----- SIMULAÇÃO DO ROBÔ -----
posicao = 0       # Começa em HOME
carregando = False

def mover_para(destino):
    global posicao, carregando
    # Regra: não ir para P2 sem garrafa
    if destino == 2 and not carregando:
        print("\nNão posso ir para P2 sem garrafa!")
        return

    caminho = achar_caminho(posicao, destino)
    if not caminho:
        print(f"\nSem caminho de {posicao} para {destino}")
        return

    print(f"\nCaminho: {caminho}")

    for ponto in caminho[1:]:
        print(f"Movendo de {posicao} para {ponto}")
        posicao = ponto

# ----- MISSÃO -----
print("== Indo pegar garrafa ==")
mover_para(4)
print("Garra fechada")
carregando = True

print("\n== Indo deixar em P2 ==")
mover_para(2)
print("Garra aberta")
carregando = False

print("\n== Voltando para HOME ==")
mover_para(0)