# 🖐️ Mão Robótica Controlada por Luva  
**Projeto Integrador I – UFSC**  
Maria Luiza Fontes Dantas

sdfasdas

Este repositório apresenta o desenvolvimento de uma **mão robótica acionada por sensores de flexão instalados em uma luva**, permitindo que os movimentos dos dedos humanos sejam reproduzidos por uma estrutura mecânica impressa em 3D.  
O foco é utilizar **tecnologia acessível** para criar uma solução funcional de baixo custo, unindo eletrônica, computação e mecânica.

<img src="imgs\mao_paz.jpg" width="300" alt="Imagem mão robotica">

gfergre

---

## ✨ Visão Geral do Projeto

O sistema é dividido em duas partes principais:

### **1. Luva sensorizada**
- Sensores de flexão caseiros construídos com folha de alumínio, papel e fita isolante.
- Cada sensor detecta a flexão do dedo por meio da variação de resistência.
- Os sinais são lidos por meio de divisores de tensão no Arduino.
- O software realiza tratamentos simples para compensar ruídos e instabilidades dos sensores caseiros.

<img src="imgs\mao1 (1).jpg" width="300" alt="Imagem flex sensors">

### **2. Mão robótica**
- Estrutura impressa em 3D com articulações que imitam os dedos humanos.
- Movimentação por **servos MG996R**, ligados aos dedos por linhas de pesca (tendões artificiais).
- Elásticos na parte posterior dos dedos realizam o movimento de abertura.
- Os motores recebem comandos com base nos dados dos sensores da luva em tempo real.

<img src="imgs\imp3d_2.png" width="300" alt="Imagem impressao 3D">

---

## 🎯 Objetivo do Projeto

O objetivo principal é demonstrar como é possível construir um sistema de **teleoperação** simples e funcional usando:

- componentes de baixo custo,  
- sensores produzidos manualmente,  
- Arduino como plataforma de controle,  
- integração de mecânica, eletrônica e software.

O projeto busca oferecer um modelo inicial para aplicações de **reabilitação motora**, próteses didáticas e interação homem–máquina.

---

## 🛠️ Tecnologias usadas

-  Arduino Uno R3
- Sensores de flexão caseiros
- Servos MG996R
- Estrutura 3D impressa
- Processamento de dados para melhorar acurácia da aplicação
- Circuito divisor de tensão



