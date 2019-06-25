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
    // Account &operator=(const Account &a)
    // {
    //     this->nome_cliente = a.nome_cliente;
    //     this->chave = a.chave;
    //     this->cod_banco = a.cod_banco;
    //     this->ag = a.ag;
    //     this->conta = a.conta;
    //     this->m_balance = a.m_balance;

    //     return *this;
    // }

    /** Operador lógico
     */
    friend bool operator==(const Account lhs, const Account rhs)
    {
        if (lhs.chave == rhs.chave and lhs.cod_banco == rhs.cod_banco and lhs.ag == rhs.ag and lhs.conta == rhs.conta and lhs.m_balance == rhs.m_balance and lhs.nome_cliente == rhs.nome_cliente)
            return true;

        return false;
    }
};