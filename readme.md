# Nome do Repositório

Este repositório contém um projeto voltado para o controle de pinos GPIO utilizando comandos do teclado, com o objetivo de aprender e aplicar conceitos de eletrônica e programação. O projeto utiliza a plataforma Wokwi para simulação de circuitos e o Pico Pi W SDK para o controle de hardware. O foco é facilitar a interação com pinos GPIO por meio da digitação de comandos no terminal, como GREEN, BLUE, RED, WHITE, BUZZER e OFF.

## Desenvolvedores

- Vinícius Ramos de Araújo
- Décio Francis da Silva
- Gabriel Silva Sampaio
- Maic de Oliveira Santos
- Kaique Almeida Barbosa
- [Nome do desenvolvedor]
- [Nome do desenvolvedor]
- [Nome do desenvolvedor]

## Tecnologias Utilizadas

- *Linguagens*: C
- *Ferramentas*: Wokwi, Pico Pi W SDK, CMake

## Como Começar

Para começar a usar este projeto, siga as instruções abaixo:

1. *Clonar o Repositório*
   - Para clonar o repositório no seu computador, utilize o comando abaixo no terminal:
     bash
     git clone https://github.com/GabrielSampa1o/Controle-de-Pinos-GPIO-com-BitDogLab
     

2. *Instalar Dependências*
   - Antes de começar, você precisará instalar as seguintes ferramentas:
     - *Wokwi*: Uma plataforma online de simulação de circuitos. Você pode usar a versão online através de [Wokwi Simulator](https://wokwi.com/).
     - *CMake*: Ferramenta de compilação necessária para construir o projeto. Para instalar o CMake, siga as instruções no site oficial: [https://cmake.org/install/](https://cmake.org/install/).
     - *Pico Pi W SDK*: SDK necessário para o desenvolvimento com o microcontrolador Raspberry Pi Pico. Acesse a documentação e os arquivos de instalação [aqui](https://www.raspberrypi.org/documentation/pico/getting-started/).

3. *Rodar o Projeto*
   - Para rodar o projeto, siga os seguintes passos:
     1. Importe o repositório no Wokwi Simulator. Isso pode ser feito diretamente na plataforma Wokwi, utilizando a opção de importar repositórios.
     2. Após importar o repositório, abra o arquivo diagram.json no simulador.
     3. Clique no botão *Play* para iniciar a simulação.
     4. Uma vez no simulador, interaja com o teclado e digite um dos comandos: GREEN, BLUE, RED, WHITE, BUZZER ou OFF.git
     
     ### O que acontece quando uma tecla é pressionada:
    -Tecla GREEN: Acende o LED verde (pino GPIO 11). O terminal exibirá "LED ativado: GREEN".
    -Tecla BLUE: Acende o LED azul (pino GPIO 12). O terminal exibirá "LED ativado: BLUE".
    -Tecla RED: Faz o LED vermelho (pino GPIO 13) piscar três vezes. O terminal exibirá "LED ativado: RED".
    -Tecla WHITE: Acende todos os LEDs (vermelho, verde e azul). O terminal exibirá "LED ativado: WHITE".
    -Tecla BUZZER: Ativa o buzzer por 2 segundos. O terminal exibirá "Buzzer ativado".
    -Tecla OFF: Desliga todos os LEDs. O terminal exibirá "Todos os LEDs foram apagados".

## Vídeo de Demonstração

[Assista ao vídeo de demonstração aqui]([https://www.dropbox.com/s/example/video.mp4?dl=0](https://www.dropbox.com/scl/fi/7hx1d0oze351n7ilbedim/VID_20250119_200205.mp4?rlkey=cdngyxbodq1irfhztgx6xjlrn&st=z8hlmbmg&dl=0))
