#include <PubSubClient.h>

extern unsigned long tempo;

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("MSG recebida no tópico: ");
  Serial.println(topic);

  String msg = "";
  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }
  Serial.println("Conteudo: " + msg);

  // LIGA / DESLIGA
  if (msg == "LIGA") {
    digitalWrite(LED_PIN, LOW);
    client.publish(topico_status, "LIGADO", true);
    controller = true;
  } 
  else if (msg == "DESLIGA") {
    digitalWrite(LED_PIN, HIGH);
    client.publish(topico_status, "DESLIGADO", true);
    controller = false;
  } 
  
  // Controle de cores
  else {
    if (!controller) {
      Serial.println("Control OFF");
      return;
    }

    int separador = msg.indexOf(':');
    if (separador == -1) return;

    String key = msg.substring(0, separador);
    int value = msg.substring(separador + 1).toInt();
    int pwm = (1000 - value) * 255 / 1000;

    Serial.println("Control OK: " + key + " -> " + String(value));

    // Loop pelo mapa de cores
    for (int i = 0; i < totalCores; i++) {
      if (key.equalsIgnoreCase(cores[i].nome)) {
        analogWrite(cores[i].pino, pwm);
        break;
      }
    }
  }
}

boolean attemptMqttConnection() {
  String clientId = String(mqtt_client_id) + "_" + String(WiFi.macAddress());
  Serial.print("Tentando MQTT como: " + clientId + "... ");
  if (client.connect(clientId.c_str(), NULL, NULL, topico_status, 0, true, "OFFLINE")){
    Serial.println("CONECTADO!");
    client.publish(topico_status, "ONLINE", true);
    client.subscribe(topico_comando);
    client.subscribe(topico_texto);
    return true;
  } else {
    Serial.print("Falha. rc=");
    Serial.print(client.state());
    return false;
  }
}

void taConectado(){
  if (!client.connected()) {
    isConnected = false;
    if (tempo > 5000) {
      tempo = 0;
      if (attemptMqttConnection()) tempo = 0;
    }
  } else {
    isConnected = true;
    client.loop();
  }
}