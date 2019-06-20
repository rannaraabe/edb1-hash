# Intro
Este projeto consiste na implementação de uma estrutura de dados tabela de disperção em C++.  
A implementação do projeto explora conceitos abordados da discplina de Estrutura de Dados Básica I, ministrada pelo professor [Selan Rodrigues](https://docente.ufrn.br/2497950/perfil).

# Funções implementadas

## Funções membros
``` (construtor) ```: construtor padrão; 

``` (destrutor) ```: destrutor;

``` operator= ```: atribui um conteúdo; 

## Capacidade
``` size_type size() const ```: retorna o número de elementos da lista;

``` size_type capacity() const ```: retorna o número da capacidade da lista;

``` bool empty() ```: retorna se a lista está vazia ou não;

## Acessando elementos
``` const T & operator[]( size_type pos) const ```: retorna o objeto que está no indice \pos no array, sem verificar os limites;

``` T & operator[]( size_type pos) ```: retorna o objeto que está no indice \pos no array, sem verificar os limites;

``` const T & at ( size_type pos ) const ```: retorna o objeto na posicao do indice do array, verificando os limites;

``` T & at ( size_type pos ) ```: retorna o objeto na posicao do indice do array, verificando os limites;


## Modificadores
``` void assign( sizet_type count, const T & value ) ```: substitui o conteudo da lista por copias de count de value;

``` void assign( InItr first, InItr last ) ```: substitui o conteudo do array com os elementos da lista ilist;

``` void assign( std::initializer_list<T> ilist ) ```: substitui o conteudo da lista por copias dos elementos no intervalo [first; last);

``` iterator insert( iterator pos, InItr first, InItr last ) ```: insere elementos do intervalo [first; last) antes de \pos;

``` iterator insert( const_iterator pos, std::initializer_list<T> ilist ) ```: insere elementos da lista inicializadora \ilist antes de \pos;

``` iterator erase( iterator pos ) ```: remove o objeto na posicao pos;

``` iterator erase( iterator first, iterator last ) : ```: remove todos os elementos od intervalo [first, last];

``` void clear() ```: remove todos os elementos da lista;



--

Autor: Ranna Raabe