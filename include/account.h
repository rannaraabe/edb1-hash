/**
 * @file account.h 
 * @author Ranna Raabe
 */

#include <iostream>
#include <string>

/** Modelo de classe que representaria uma conta bancária.
 */
class Account
{
  public:
    using AcctKey = int;

    int chave;                //!< Chave
    int cod_banco;            //!< Código do banco
    int ag;                   //!< Agência da conta
    int conta;                //!< Número d a conta
    float m_balance;          //!< Saldo
    std::string nome_cliente; //!< Nome do cliente

    /** Construtor parametrizado
     */
    Account(std::string nome = "", int chave_ = 0, int cod = 0, int conta_ = 0, float saldo = 0.0)
        : nome_cliente(nome), chave(chave_), cod_banco(cod), conta(conta_), m_balance(saldo)
    {
        /*empty*/
    }

    int getKey()
    {
        return chave;
    }

    /** Operador de atribuição 
     */
    Account &operator=(const Account &a)
    {
        this->nome_cliente = a.nome_cliente;
        this->chave = a.chave;
        this->cod_banco = a.cod_banco;
        this->ag = a.ag;
        this->conta = a.conta;
        this->m_balance = a.m_balance;

        return *this;
    }

    /** Operador lógico
     */
    friend bool operator==(const Account lhs, const Account rhs)
    {
        if (lhs.chave == rhs.chave and lhs.cod_banco == rhs.cod_banco and lhs.ag == rhs.ag and lhs.conta == rhs.conta and lhs.m_balance == rhs.m_balance and lhs.nome_cliente == rhs.nome_cliente)
            return true;

        return false;
    }
};

/** Functor KeyHash. Classe que sobrecarrega o operador funcional operator().
 */
struct KeyHash
{
    /** Função de disperção primária. Recebe como argumento uma chave e retorn um inteiro sem sinal. 
     */
    std::size_t operator()(const Account::AcctKey &key) const
    {
        return std::hash<int>()(key);
    }
};

/** Functor KeyEqual. Classe que sobrecarrega o operador funcional operator().
 */
struct KeyEqual
{
    /** Função de comparação de chaves. Recebe duas chaves e retorna um booleano indicando se são iguais.
     */
    bool operator()(const Account::AcctKey &lhs, const Account::AcctKey &rhs) const
    {
        return lhs == rhs;
    }
};