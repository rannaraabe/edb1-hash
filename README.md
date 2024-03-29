# Intro
Este projeto consiste na implementação de uma estrutura de dados tabela de disperção em C++.  
A implementação do projeto explora conceitos abordados da discplina de Estrutura de Dados Básica I, ministrada pelo professor [Selan Rodrigues](https://docente.ufrn.br/2497950/perfil).

## Compilando
Para compilar, é necessário ter o CMake instalado. Caso você não tenha instalado, execute ```sudo apt-get install cmake``` no terminal.

Caso você já tenha instalado, abra um termial na pasta raiz do projeto.

Crie o diretorio "build" e entre nele: ```$ mkdir build && cd build ```

Agora gere os arquivos para a compilação com: ```$ cmake -G"Unix Makefiles" ..```

Agora compile o projeto com: ```$ make ```

## Executando
Para executar o projeto: ```$ ./hash ```.

## Observação
Os testes que falharam foram:

```
  [  FAILED  ] HTTest.InsertingData
  [  FAILED  ] HTTest.OperatorSquareBraketsRHS
  [  FAILED  ] HTTest.OperatorSquareBraketsLHS
  [  FAILED  ] HTTest.EraseExisting
  [  FAILED  ] HTTest.Count
```

Além desses o AtRHS e AtLHS deram segmentation fault, para conseguir testar todos os testes eu comentei esses dois testes no arquivo ```test/main.cpp```, portanto teoricamente eles também falharam.


Autor: Ranna Raabe