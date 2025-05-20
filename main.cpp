// Sistema de Irrigação Inteligente com ESP32

#include <DHT.h>

// --- Definições dos pinos ---
#define PINO_DHT       4   // Sensor de umidade (DHT22)
#define TIPO_DHT       DHT22
#define PINO_PH        34  // Sensor de pH simulado (LDR)
#define BOTAO_FOSFORO  15  // Botão que simula fósforo
#define BOTAO_POTASSIO 2   // Botão que simula potássio
#define PINO_RELE      18  // LED/relé da bomba

DHT sensorUmidade(PINO_DHT, TIPO_DHT);

void setup() {
    Serial.begin(115200);
    // Inicializa o DHT22
    sensorUmidade.begin();

    // Configurações dos pinos
    pinMode(BOTAO_FOSFORO, INPUT_PULLUP);
    pinMode(BOTAO_POTASSIO, INPUT_PULLUP);
    pinMode(PINO_RELE, OUTPUT);
}

void loop() {
    // Leitura dos sensores
    bool fosforoPresente  = (digitalRead(BOTAO_FOSFORO)  == LOW);
    bool potassioPresente = (digitalRead(BOTAO_POTASSIO) == LOW);
    int  valorPH          = analogRead(PINO_PH);            // 0–4095
    float ph              = map(valorPH, 0, 4095, 0, 14);   // converte para 0–14
    float umidade         = sensorUmidade.readHumidity();   // % de umidade

    // Lógica de controle: irrigar se todos os critérios forem atendidos
    bool irrigar = fosforoPresente 
                  && potassioPresente 
                  && (ph >= 5.5 && ph <= 7.5) 
                  && (umidade < 40.0);

    // Ativa/desativa a bomba
    digitalWrite(PINO_RELE, irrigar ? HIGH : LOW);

    // Saída no monitor serial
    Serial.print("Fósforo: ");      Serial.print(fosforoPresente);
    Serial.print(" | Potássio: ");  Serial.print(potassioPresente);
    Serial.print(" | pH: ");        Serial.print(ph);
    Serial.print(" | Umidade: ");   Serial.print(umidade);
    Serial.print(" | Irrigando: "); Serial.println(irrigar);

    delay(2000); // Aguarda 2 segundos antes da próxima leitura
}
