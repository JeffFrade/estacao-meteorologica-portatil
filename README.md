# Exemplo de estação meteorológica portátil
---

Há 2 modelos de como montar uma estação meteorológica portátil nesse projeto.
Uma utilizando o módulo `AHT20+BMP280` (Integrado) e outra utilizando os módulos `BMP280` e `DHT22` (Ou `DHT11`) de forma separada.
Cada pasta contém sob qual(is) módulos a estação foi desenvolvida, mas falando de forma simplificada, a estação coleta altitude em metros, pressão em Pascal, temperatura em Celsius, umidade em percentual e dados de GPS como latitude, longitude e velocidade. (Válidos para os 2 exemplos).

Cada exemplo possui seus sketches e junto aos sketches tem as bibliotecas utilizadas como seus respectivos esquemáticos de montagem.
Vale ressaltar que para o exemplo foi utilizado um `ESP-32` e também deixei a conexão com o `Wi-Fi` já pronta, caso queiram a utilizar ou conectar a um serviço de coletas de métricas como o `J3M`.

Link do post no [LinkedIn](https://www.linkedin.com/posts/jefferson-frade_php-iot-arduino-activity-7274573102393536512-Jqab)
