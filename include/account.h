/**
 * @file account.h 
 * @author Ranna Raabe
 */

#include <iostream>
#include <string>

/** Modelo de classe que representaria uma conta bancária.
 */
struct Account
{
    using AcctKey = int;

    int chave;                //!< Chave
    int cod_banco;            //!< Código do banco
    int ag;                   //!< Agência da conta
    int conta;                //!< Número d a conta
    float saldo;              //!< Saldo
    std::string nome_cliente; //!< Nome do cliente

    /** Construtor parametrizado
     */
    Account(int chave_, int cod, int agencia, int conta_, float saldo_, std::string nome)
        : chave(chave_), cod_banco(cod), ag(agencia), conta(conta_), saldo(saldo_), nome_cliente(nome)
    {
        /*empty*/
    }

    /** Construtor padrão
     */
    Account()
    {
        chave = 0;
        cod_banco = 0;
        ag = 0;
        conta = 0;
        saldo = 0;
        nome_cliente = "";
    }

    int getChave()
    {
        return chave;
    }

    /** Operador de atribuição 
     */
    Account &operator=(const Account &a)
    {
        this->chave = a.chave;
        this->cod_banco = a.cod_banco;
        this->ag = a.ag;
        this->conta = a.conta;
        this->saldo = a.saldo;
        this->nome_cliente = a.nome_cliente;

        return *this;
    }

    /** Operador lógico
     */
    friend bool operator==(const Account lhs, const Account rhs)
    {
        if (lhs.chave == rhs.chave and lhs.cod_banco == rhs.cod_banco and lhs.ag == rhs.ag and lhs.conta == rhs.conta and lhs.saldo == rhs.saldo and lhs.nome_cliente == rhs.nome_cliente)
            return true;

        return false;
    };
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