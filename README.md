 # **Comando por voz**

- See in [English 🇬🇧](./README-en-US.md).
<div align="center">
<img src="https://user-images.githubusercontent.com/79997705/115067227-fd944d00-9ec6-11eb-877f-e2678627c54f.PNG"/>
</div>
</br>
Esse é um projeto de comando por voz com Arduino.

## Componentes do projeto

- Arduíno UNO;
- Módulo de reconhecimento de voz V3;
- Módulo Relé 4 canais;
- Protoboard de 400 pinos;
- Jumpers;
- 6 Led’s indicadores;
- 2 pushbuttons;
- Speaker;
- Resistores 330Ω;
- Resistores 1kΩ;
- Resistor LDR;

 ## Linguagens da aplicação
  
![image](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

## Esquemático do Projeto
![Capturar3](https://user-images.githubusercontent.com/79997705/115067241-008f3d80-9ec7-11eb-8692-587b194c557e.PNG)

## Como utilizar?

É possível configurar até sete comandos, os quais podem ser selecionados através do botão branco. Uma vez selecionado o número do comando, ele pode ser gravado ou regravado dando um click no botão verde. 

Na hora de falar o comando a ser gravado o ideal é falar normalmente e de maneira clara. O led amarelo do módulo indica o início do processo de gravação. O comando deve ser dito assim que o led vermelho estiver acesso. Fala-se o comando apenas uma vez e em seguida, aguarda o led vermelho ficar aceso novamente. Quando os dois leds piscam juntos, o cadastro foi feito corretamente. 

Ao final de uma nova gravação é necessário dar um click no botão branco para que os comandos sejam carregados. Quando os comandos estão carregados o led amarelo do módulo fica piscando, indicando que a placa já está captando o que o usuário fala. Se a placa reconhecer algum comando, o trecho de código referente a ele é executado no arduíno.

> Status do Projeto: Concluido :heavy_check_mark:
***
 ![image](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white) 
 
 Visite o meu [LinkedIn](https://www.linkedin.com/in/nathan-de-souza-silva-firmo/). 


