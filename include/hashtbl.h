/**
 * @file hashtbl.h 
 * @author Ranna Raabe
 */

#ifndef HASHTBL_H
#define HASHTBL_H

#include <iostream>
#include <forward_list>

namespace ac
{
/** Classe HashEntry
 */
template <class KeyType, class DataType>
class HashEntry
{
  public:
    HashEntry(KeyType key, DataType data)
        : m_key(key), m_data(data)
    {
        /*empty*/
    }

    KeyType m_key;   //!< Para armazezar a chave
    DataType m_data; //!< Para armazezar os dados
};

/** Classe HashTbl
 */
template <class KeyType, class DataType, typename KeyHash = std::hash<KeyType>, typename KeyEqual = std::equal_to<KeyType>>
class HashTbl
{
  public:
    using Entry = HashEntry<KeyType, DataType>; //!< Alias
    KeyHash hashFunctor;                        //!< Instacia o functor para primary hash.
    KeyEqual equalFunctor;                      //!< Instacia o functor para equal for test.

    /** Construtor default
     */
    HashTbl(size_t tbl_size = DEFAULT_SIZE)
    {
        m_size = tbl_size;
        m_count = 0;
        m_data_table = new std::forward_list<Entry>[m_size];
    }

    /** Destrutor
     */
    virtual ~HashTbl()
    {
        delete[] m_data_table;
    }

    /** Construtor de cópia
     */
    HashTbl(const HashTbl &other)
    {
        m_data_table = new std::forward_list<Entry>[other.m_size];
        m_size = other.m_size;

        auto inicio = other.m_data_table.begin(); //!< Inicio da lista
        auto fim = other.m_data_table.end();      //!< Final da lista

        for (auto i{0}; i < m_size; i++)
        {
            if (other.m_data_table[i].empty() == false)
            {
                for (auto it(inicio); it != fim; it++)
                {
                    Entry new_entry(it->m_key, it->m_data);
                    m_data_table[i].push_front(new_entry);
                }
            }
        }

        m_count = other.m_count;
    }

    /** Construtor de lista inicializadora
     */
    HashTbl(std::initializer_list<Entry> ilist);

    /** Operador de atribuição 
     */
    HashTbl &operator=(const HashTbl &other)
    {
        // Limpo a lista, caso tenha elementos
        clear();
        m_size = other.m_size;

        auto inicio = other.m_data_table.begin(); //!< Inicio da lista
        auto fim = other.m_data_table.end();      //!< Final da lista

        for (auto i{inicio}; i < fim; i++)
            m_data_table[i] = other.m_data_table[i];

        return *this;
    }

    /** Operador de atribuição 
     */
    HashTbl &operator=(std::initializer_list<Entry> ilist);

    /** Insere na tabela a informação contida em \data e associada a uma chave \key.
     *
     * @key chave a ser associada ao valor
     * @data valor que será adicionado
     */
    bool insert(const KeyType &key, const DataType &data)
    {
        Entry new_entry(key, data); //!< Cria uma Entry baseada nos arguementos passados como parametros

        auto end(hashFunctior(key) % m_size); //!< Aplica o double hashing

        auto inicio = m_data_table[end].begin(); //!< Inicio da lista
        auto fim = m_data_table[end].end();      //!< Final da lista

        /* Nao precisa conferir se a lista está vazia, pois se estiver basta adicionar o elemento normalmente!!! */

        for (auto it(inicio); it != fim; it++)
        {
            // Compara as chaves para o caso de colisão
            if (equalFunctor(it->key, new_entry.key))
            {
                it->data = new_entry.m_data;
                // Somo um na quantidade de itens na lista
                m_count++;

                return false;
            }

            // Adidicona o valor na lista
            m_data_table[end].push_front(new_entry);
            // Somo um na quantidade de itens na lista
            m_count++;

            return true;
        }
    }

    /** Remove um item de tabela identificado pela chave \key. Se a chave for encontrada
     * retorna true, caso contrário false.  
     * 
     * @key chave que identifica o item
     */
    bool erase(const KeyType &key)
    {
        auto end(hashFunctior(key) % m_size); //!< Aplica o double hashing

        auto inicio = m_data_table[end].begin(); //!< Inicio da lista
        auto fim = m_data_table[end].end();      //!< Final da lista

        for (auto it(inicio); it != fim; it++)
        {
            // Compara as chaves para o caso de colisão
            if (equalFunctor(it->key, key))
            {
                // Remove o valor na lista
                m_data_table[end].remove(m_data_table[end].m_key == key);
                // Diminui um no valor da quantidade de elementos
                m_count--;
                return true;
            }

            return false;
        }
    }

    /** Recupera em \data a informação associada a chave \key passada. Se a chave for
     * encontrada retorna true, caso contrário false.
     * 
     * @key chave a ser associada ao valor
     * @data valor a ser recuperado
     */
    bool retrieve(const KeyType &key, DataType &data) const
    {
        KeyHash hashFunctior;
        KeyEqual equalFunctior;

        auto end(hashFunctior(key) % m_size);
        auto inicio = m_data_table[end].begin();
        auto fim = m_data_table[end].end();

        if (m_data_table->empty())
            return false;
        else
        {
            for (auto it(inicio); it != fim; it++)
            {
                if (equalFunctior(it->m_key, key))
                    data = it->m_data;
            }

            return true;
        }

        return false;
    }

    /** Apaga toda a memória associada às listas de colisão da tabela.
     */
    void clear(void)
    {
        // Confere se a lista está vazia
        if (this->m_data_table.empty())
            return;
        else
        {
            // Caso não esteja vazia, percorre cada elemento da lista apagando
            for (auto i{0}; i < m_size; i++)
                m_data_table[i].clear();
        }
    }

    /** Retorna true se a tabela estiver vazia, caso contrário false.
     */
    bool empty(void) const
    {
        if (this->m_count == 0)
            return true;

        return false;
    }

    /** Retorna a quantidade de elementos na tabela. 
     */
    size_t size(void) const
    {
        return this->m_count;
    }

    /** É método de depuração para gerar uma representação textual da tabela e seus elementos.
     */
    friend std::ostream &operator<<(std::ostream &os, const HashTbl &hash)
    {
        for (auto i{0}; i < hash.m_size; i++)
        {
            auto inicio = hash.m_data_table[i].begin();
            auto fim = hash.m_data_table[i].end();

            os << "[" << i << "]";

            for (auto it{inicio}; it != fim; it++)
                os << "  " << it->m_data;

            os << std::endl;
        }

        return os;
    }

    /** Retorna uma referência para o dado associado a chave \key fornecida, se existir.
     * Se a chave não estiver na tabela, o método lança uma exceção do tipo std::out_of_range.
     * 
     * @key chave referente ao dado
     */
    DataType &at(const KeyType &key)
    {
        DataType dt;
        Entry new_entry(key, dt); //!< Cria uma Entry baseada nos arguementos passados como parametros

        auto end(hashFunctior(key) % m_size);
        auto inicio = m_data_table[end].begin();
        auto fim = m_data_table[end].end();

        for (auto it(inicio); it != fim; it++)
        {
            // Compara as chaves para o caso de colisão
            if (equalFunctor(it->key, new_entry.key))
                dt = it->m_data;

            return dt;
        }
    }

    /** Retorna uma referência para o dado associado a chave \key, se existir. 
     * Se a chave não estiver na tablea, o metodo realiza  ainserção e retorna a
     * referência para o dado inserido na tabela.
     * 
     * @key chave referente ao dado
     */
    DataType &operator[](const KeyType &key)
    {
        DataType *dt;

        // Chama a funcao retrieve que recupera o valor associado a chave passada
        this->retrieve(key, *dt);

        // Caso a chave não esteja na tabela faz a inserção
        if (this->retrieve(key, *dt) == false)
            insert(key, *dt);

        return dt;
    }

    /** Retorna a quantidade de elementos da tabela que estão na lista de colisão 
     * associada a chave \key.
     * 
     * @key chave referente ao dado
     */
    size_t count(const KeyType &key) const
    {
        KeyHash hashFunc;
        size_t cont = 0;
        auto end(hashFunc(key) % m_size);

        // Se a lista estiver vazia retorna 0
        if (m_data_table->empty())
            return cont;
        else
        {
            // Inicio e final da lista
            auto inicio = m_data_table[end].begin();
            auto fim = m_data_table[end].end();

            // Percorre a lista, contando os elementos
            for (auto it(inicio); it != fim; it++)
                cont++;
        }

        return cont;
    }

  private:
    unsigned int m_size;                    //!< Tamanho da tabela hash
    unsigned int m_count;                   //!< Numero de elementos na tabelas
    std::forward_list<Entry> *m_data_table; //!< Array de ponteiros para lista de colisão. Cada elemento alocado eh uma lista encadeada de itens da tabela

    // Definindo um tamanho default para hash table
    static const short DEFAULT_SIZE = 11;

    /** Método chamado quando o fator de carga λ for maior que 1.0. Cria uma nova tabela
     * cujo tamanho será igual ao menor número primo >= que o dobro do tamanho da tabela antes da chamada.
     */
    void rehash()
    {
        KeyHash hashFunctor;
    }
};
}; // namespace ac

#endif