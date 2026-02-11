import pyads

# ------------------------
# CONFIGURAÇÃO DE CONEXÃO COM CLP
# ------------------------
TARGET_AMS_NET_ID = '10.234.199.82.1.1'
ADS_PORT = 851
TARGET_IP = '10.234.199.82'

# Cria conexão
plc = pyads.Connection(TARGET_AMS_NET_ID, ADS_PORT, TARGET_IP)

with plc:
    print(f"Conectado ao CLP: {plc.ip_address}")

    while True:
        try:
            valor = int(input("Digite robotStatus: "))
        except ValueError:
            print("Insira um número válido!")
            continue

        if valor < 0:
            print("Saindo...")
            break

        if valor not in (0, 1):
            print("Valor inválido! Só 0 ou 1.")
            continue

        # Escreve robotStatus no CLP
        plc.write_by_name("GVL.robotStatus", valor, pyads.PLCTYPE_INT)
        print(f"robotStatus atualizado para {valor}")
