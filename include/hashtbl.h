/**
 * @file hashtbl.h 
 * @author Ranna Raabe
 */

#ifndef HASHTBL_H
#define HASHTBL_H

#include <iostream>
#include <forward_list>
#include <exception>

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
        : m_size(tbl_size), m_count(0)
    {
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
        m_size = other.m_size;
        m_count = other.m_count;
        m_data_table = new std::forward_list<Entry>[m_size];

        // Copiando os valores
        for (int i = 0; i < m_size; i++)
            m_data_table[i] = other.m_data_table[i];
    }

    /** Construtor de cópia de lista inicializadora
     */
    HashTbl(std::initializer_list<Entry> ilist)
    {
        m_size = ilist.size();
        m_count = 0;
        m_data_table = new std::forward_list<Entry>[m_size];

        for (auto it = ilist.begin(); it != ilist.end(); ++it)
            insert(it->m_key, it->m_data);
    }

    /** Operador de atribuição 
     */
    HashTbl &operator=(const HashTbl &other)
    {
        clear();
        delete[] m_data_table;

        m_size = other.m_size;
        m_count = other.m_count;
        m_data_table = new std::forward_list<Entry>[m_size];

        // Copiando os valores
        for (int i = 0; i < m_size; i++)
            m_data_table[i] = other.m_data_table[i];

        return *this;
    }

    /** Operador de atribuição de lista inicializadora
     */
    HashTbl &operator=(std::initializer_list<Entry> ilist)
    {
        delete[] m_data_table;

        m_size = ilist.size();
        m_count = 0;
        m_data_table = new std::forward_list<Entry>[m_size];

        for (auto it = ilist.begin(); it != ilist.end(); ++it)
            insert(it->m_key, it->m_data);

        return *this;
    }

    /** Insere na tabela a informação contida em \data e associada a uma chave \key.
     *
     * @key chave a ser associada ao valor
     * @data valor que será adicionado
     */
    bool insert(const KeyType &key, const DataType &data)
    {
        KeyHash hashFunctor;
        KeyEqual equalFunctor;

        auto end = hashFunctor(key) % m_size;

        Entry new_entry(key, data); //!< Cria uma Entry baseada nos arguementos passados como parametros

        for (auto it = m_data_table[end].begin(); it != m_data_table[end].end(); it++)
        {
            if (equalFunctor(it->m_key, new_entry.m_key))
            {
                it->m_data = data;
                return false;
            }
        }

        m_count++;
        m_data_table[end].push_front(new_entry);

        return true;
    }

    /** Remove um item de tabela identificado pela chave \key. Se a chave for encontrada
     * retorna true, caso contrário false.  
     * 
     * @key chave que identifica o item
     */
    bool erase(const KeyType &key)
    {
        KeyHash hashFunctor;
        KeyEqual equalFunctor;

        auto end(hashFunctor(key) % m_size); //!< Aplica o double hashing

        auto pos = this->m_data_table[end];
        auto inicio = pos.begin(); //!< Inicio da lista
        auto fim = pos.end();      //!< Final da lista

        auto garfo = pos.before_begin();

        for (auto it{inicio}; it != fim; ++it)
        {
            // Compara as chaves para o caso de colisão
            if (equalFunctor(it->m_key, key))
            {
                // Remove o valor na lista
                pos.erase_after(garfo);

                // Diminui um no valor da quantidade de elementos
                m_count--;
                return true;
            }
            garfo++;
        }

        return false;
    }

    /** Recupera em \data a informação associada a chave \key passada. Se a chave for
     * encontrada retorna true, caso contrário false.
     * 
     * @key chave a ser associada ao valor
     * @data valor a ser recuperado
     */
    bool retrieve(const KeyType &key, DataType &data) const
    {
        KeyHash hashFunctor;
        KeyEqual equalFunctor;

        auto end(hashFunctor(key) % m_size); //!< Aplica o double hashing

        for (auto it = m_data_table[end].begin(); it != m_data_table[end].end(); it++)
        {
            if (equalFunctor(it->m_key, key))
            {
                data = it->m_data;
                return true;
            }
        }

        return false;
    }

    /** Apaga toda a memória associada às listas de colisão da tabela.
     */
    void clear(void)
    {
        // Caso não esteja vazia, percorre cada elemento da lista apagando
        for (auto i{0}; i < m_size; i++)
            m_data_table[i].clear();

        m_count = 0;
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

        if (not(retrieve(key, dt)))
            throw std::out_of_range("Valor fora do intervalo.");

        return dt;
    }

    /** Retorna uma referência para o dado associado a chave \key, se existir. 
     * Se a chave não estiver na tablea, o metodo realiza  ainserção e retorna a
     * referência para o dado inserido na tabela.
     * 
     * @key chave referente ao dado
     */
    DataType &operator[](const KeyType &key)
    {
        // Caso a chave não esteja na tabela faz a inserção
        KeyHash hashFunctor;
        KeyEqual equalFunctor;

        auto end(hashFunctor(key) % m_size);

        for (auto &e : m_data_table[end])
        {
            if (equalFunctor(e.m_key, key) == true)
                return e.m_data;
        }

        DataType dt = DataType();
        Entry entry(key, dt);

        m_count++;
        m_data_table[end].push_front(entry);

        return m_data_table[end].front().m_data;
    }

    /** Retorna a quantidade de elementos da tabela que estão na lista de colisão 
     * associada a chave \key.
     * 
     * @key chave referente ao dado
     */
    size_t count(const KeyType &key) const
    {
        KeyHash hashFunctor;

        size_t cont = 0;
        auto end(hashFunctor(key) % m_size);

        // Inicio e final da lista
        auto inicio = m_data_table[end].begin();
        auto fim = m_data_table[end].end();

        // Percorre a lista, contando os elementos
        for (auto it(inicio); it != fim; it++)
            cont++;

        return cont;
    }

    bool ehPrimo(int num)
    {

        for (int i = 2; i < num; i++)
        {
            if (num % i == 0)
                return false;
        }
        return true;
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
    void rehash();
};
}; // namespace ac

#endif
