# EspCar Joystick Web AP Server

Este é um servidor para controle de um carro com joystick utilizando a placa ESP32. O projeto é voltado para permitir o controle remoto de um veículo por meio de uma interface web com um joystick.

## Índice

- [Sobre](#sobre)
- [Tecnologias Utilizadas](#tecnologias-utilizadas)
- [Instalação](#instalação)
- [Como Usar](#como-usar)
- [Contribuições](#contribuições)
- [Licença](#licença)

## Sobre

O **EspCar Joystick Web AP Server** utiliza o microcontrolador ESP32 para implementar um servidor web que oferece uma interface de joystick para controlar um veículo (carro). O servidor pode ser acessado através de um navegador web e envia comandos ao veículo para controlar seus movimentos.

Este projeto é uma implementação de um controle remoto simples via interface web, utilizando a comunicação entre o ESP32 e o carro através de uma rede Wi-Fi do Access Point.

## Tecnologias Utilizadas

- **ESP32**: Microcontrolador que gerencia o controle do carro e se comunica com a interface web.
- **HTML/CSS/JavaScript**: Para a criação da interface web com o joystick.
- **WebSocket**: Protocolo de comunicação em tempo real entre o servidor e o navegador.
- **Arduino IDE**: Plataforma para o desenvolvimento do código no ESP32.
- **Bibliotecas ESP32**: Bibliotecas para configuração e controle da placa ESP32.

## Instalação

Para rodar o projeto, siga os seguintes passos:

### 1. Instale a IDE Arduino

Primeiro, é necessário ter a **Arduino IDE** instalada em seu computador. Você pode baixá-la [aqui](https://www.arduino.cc/en/software).

### 2. Instale as Bibliotecas do ESP32

Na IDE Arduino, vá até **Arquivo > Preferências** e adicione o seguinte URL de gerenciamento de pacotes:

```
https://dl.espressif.com/dl/package_esp32_index.json
```

Depois, vá em **Ferramentas > Placa > Gerenciador de Placas** e procure por "esp32". Instale a biblioteca ESP32.

### 3. Faça o Upload do Código para o ESP32

Clone este repositório para o seu computador:

```bash
git clone https://github.com/PatrickCalorioCarvalho/EspCar_JoystickWeb_APServer.git
```

Abra o arquivo `.ino` na Arduino IDE e faça o upload do código para o ESP32.

### 4. Conecte-se à Rede Wi-Fi

Verifique as configurações de rede no código do ESP32 e configure para conectar-se à sua rede Wi-Fi do Access Point.

## Como Usar

### 1. Acesse a Interface Web

Depois que o código estiver carregado no ESP32 e ele estiver conectado à sua rede, abra um navegador e acesse o endereço IP do ESP32. O IP será exibido no console serial da IDE Arduino após o ESP32 se conectar à rede Wi-Fi do Access Point.

Exemplo de IP:

```
Acesse: http://192.168.4.1
```

### 2. Controle o Veículo

Na interface web, você verá um joystick interativo. Use-o para controlar o movimento do veículo. Os comandos serão enviados em tempo real ao ESP32, que os processará para controlar o carro.

## Contribuições

Contribuições são bem-vindas! Se você tem ideias de melhorias ou encontrou algum erro, fique à vontade para abrir um **issue** ou **pull request**.

## Licença

Este projeto é licenciado sob a [MIT License](LICENSE).
