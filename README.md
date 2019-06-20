# Intro
Este projeto consiste na implementação de uma estrutura de dados tabela de disperção em C++.  
A implementação do projeto explora conceitos abordados da discplina de Estrutura de Dados Básica I, ministrada pelo professor [Selan Rodrigues](https://docente.ufrn.br/2497950/perfil).

# Funções implementadas

## Funções membros
``` (construtor) ```: construtor padrão; 

``` (destrutor) ```: destrutor;

``` operator= ```: atribui um conteúdo; 

## Iteradores
``` iterator begin() ```: retorna um iterador apontando para o primeiro item da lista;

``` iterator end() ```: retorna um iterador apontando para o ultimo item da lista;

``` const_iterator cbegin() const ```: retorna um iterador apontando para o primeiro item da lista;

``` const_iterator cend() const ```: retorna um iterador apontando para o ultimo item da lista;

## Capacidade
``` size_type size() const ```: retorna o número de elementos do container;

``` size_type capacity() const ```: retorna o número da capacidade do container;

``` bool empty() ```: retorna se a lista está vazia ou não;

``` void reserve( size_type new_cap ) ```:

## Acessando elementos
``` const T & operator[]( size_type pos) const ```: retorna o objeto que está no indice \pos no array, sem verificar os limites;

``` T & operator[]( size_type pos) ```: retorna o objeto que está no indice \pos no array, sem verificar os limites;

``` const T & at ( size_type pos ) const ```: retorna o objeto na posicao do indice do array, verificando os limites;

``` T & at ( size_type pos ) ```: retorna o objeto na posicao do indice do array, verificando os limites;

``` const T & back() const ```: retorna o objeto do final da lista;

``` T & back() ```: retorna o objeto do final da lista;

``` const T & front() const ```: retorna o objeto do inicio da lista;

``` T & front() ```: retorna o objeto do inicio da lista;

## Modificadores
``` void assign( sizet_type count, const T & value ) ```: substitui o conteudo da lista por copias de count de value;

``` void assign( InItr first, InItr last ) ```: substitui o conteudo do array com os elementos da lista ilist;

``` void assign( std::initializer_list<T> ilist ) ```: substitui o conteudo da lista por copias dos elementos no intervalo [first; last);

``` void push_front( const T & value ) ```: adiciona value no inicio do cointainer;

``` void push_back( const T & value ) ```: adiciona value no final do cointainer;

``` void pop_back() ```: remove o elemento do inicio do cointainer;

``` void pop_front() ```: remove o elemento do final do cointainer;

``` iterator insert( iterator pos, InItr first, InItr last ) ```: insere elementos do intervalo [first; last) antes de \pos;

``` iterator insert( const_iterator pos, std::initializer_list<T> ilist ) ```: insere elementos da lista inicializadora \ilist antes de \pos;

``` iterator erase( iterator pos ) ```: remove o objeto na posicao pos;

``` iterator erase( iterator first, iterator last ) : ```: remove todos os elementos od intervalo [first, last];

``` void clear() ```: remove todos os elementos da lista;



--

Autor: Ranna Raabe