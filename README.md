# Sistema de Irrigação Inteligente com ESP32  
**Autor:** Lucas Samuel  
**Projeto:** FarmTech Solutions – Fase 3 – Entrega 1  

---

## 1. Visão Geral  
Este projeto simula um sistema de irrigação automatizado que monitora nutrientes, pH e umidade do solo e aciona uma bomba de água conforme condições definidas. Utilizamos um ESP32 para ler sensores simulados (botões, LDR e DHT22) na plataforma Wokwi e mostrar o status via monitor serial.

---

## 2. Componentes e Conexões  

| Componente             | Pino ESP32 | Ligações                                                          |
|------------------------|------------|-------------------------------------------------------------------|
| **Botão Fósforo**      | GPIO 15    | Um terminal ao GPIO15, outro ao GND (usar `INPUT_PULLUP`).        |
| **Botão Potássio**     | GPIO 2     | Um terminal ao GPIO2, outro ao GND (usar `INPUT_PULLUP`).         |
| **LDR (pH)**           | GPIO 34    | Divisor de tensão: LDR → GPIO34; resistor 10 kΩ → GND.            |
| **DHT22 (Umidade)**    | GPIO 4     | Data → GPIO4; VCC → 3.3 V; GND → GND.                             |
| **Bomba (LED/Relé)**   | GPIO 18    | Cathode (–) do LED/relé → GND; Anode (+) → GPIO18.                |

![Esquema de montagem no Wokwi](circuito.png)

---

## 3. Como Usar  

1. **Copiar** `main.cpp` para o seu projeto no Wokwi ou VS Code (PlatformIO).  
2. **Construir** o circuito conforme o esquema acima.  
3. **Iniciar** a simulação e abrir o monitor serial a 115200 bps.  
4. **Pressionar** os botões para simular presença de fósforo e potássio; variar a luminosidade sobre o LDR para mudar o pH; aguardar a leitura da umidade.  
5. O sistema imprime no serial:

Fósforo: 1 | Potássio: 1 | pH: 6.80 | Umidade: 35.20 | Irrigando: 1

- “1” = condição verdadeira; “0” = condição falsa.  
6. Quando **Irrigando: 1**, o GPIO18 fica em nível alto, ligando o LED/relé.

---

## 4. Explicação do Código (`main.cpp`)  

- **Biblioteca DHT**: usada para interface com o sensor DHT22.  
- **map()**: converte a leitura analógica do LDR (0–4095) para escala de pH (0–14).  
- **INPUT_PULLUP**: mantém o botão em HIGH por default, detectando LOW quando pressionado.  
- **Lógica de irrigação**:
```cpp
bool irrigar = fosforoPresente 
             && potassioPresente 
             && (ph >= 5.5 && ph <= 7.5) 
             && (umidade < 40.0);

Só liga a bomba se TODOS os critérios forem atendidos.
5. Estrutura do Repositório

ESP32_Irrigacao/
├── main.cpp        # Fonte em C++
├── circuito.png    # Print do projeto Wokwi
└── README.md       # Documentação (este arquivo)
