#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <stack>

using namespace std;

unordered_map<string, string> deOndeEuVim_Estrela;

// Nome, distancia da cidade "pai"
struct vizinho
{
    string nome;
    int distancia;

    vizinho(string n, int d)
    {
        this->nome = n;
        this->distancia = d;
    }
};

struct dadosDaCidade
{
    // Nome, distancia da cidade
    vector<vizinho> vizinhos;
    // Para Bucharest
    int distanciaEmLinhaReta;
};

/*
    Guarda os vizinhos e suas distancias para a cidade chave, juntamente com a distancia
    da cidade chave em linha reta para Bucharest

*/
unordered_map<string, dadosDaCidade> mapa;

// Calcula a distancia entre duas cidades vizinhas, caso nao sejam retorna -1
int distanciaEntre(string origem, string destino)
{

    auto vizinhos = mapa[origem].vizinhos;
    for (auto cidade : vizinhos)
        if (cidade.nome == destino)
            return cidade.distancia;

    return -1;
}

// Struct para comparar qual cidade esta mais perto em linha reta
struct compararGuloso
{

    bool operator()(vizinho a, vizinho b)
    {
        return mapa[a.nome].distanciaEmLinhaReta > mapa[b.nome].distanciaEmLinhaReta;
    }
};

// Struct para comparar qual cidade esta mais perto em linha reta + distancia ate ela
struct compararEstrela
{

    bool operator()(vizinho a, vizinho b)
    {
        int distanciaA, distanciaB;
        distanciaA = distanciaB = 0;
        string anterior = deOndeEuVim_Estrela[a.nome];
        distanciaA = distanciaEntre(a.nome, anterior);
        anterior = deOndeEuVim_Estrela[b.nome];
        distanciaB = distanciaEntre(b.nome, anterior);

        distanciaA += mapa[a.nome].distanciaEmLinhaReta;
        distanciaB += mapa[b.nome].distanciaEmLinhaReta;

        return distanciaA > distanciaB;
    }
};

// Função que implementa a busca gulosa
int guloso(string origem)
{

    string cidadeAtual;
    // Cidades que foram visitadas e que estao na fila para serem visitadas
    // Mantem-se a lista de quais estao na fila para nao ser adicionada novamente
    unordered_map<string, bool> visitado, naFila = {
                                              {"Arad", false},
                                              {"Bucharest", false},
                                              {"Craiova", false},
                                              {"Drobeta", false},
                                              {"Eforie", false},
                                              {"Fagaras", false},
                                              {"Giurgiu", false},
                                              {"Hirsova", false},
                                              {"Iasi", false},
                                              {"Lugoj", false},
                                              {"Mehadia", false},
                                              {"Neamt", false},
                                              {"Oradea", false},
                                              {"Pitesti", false},
                                              {"Rimnicu_Vilcea", false},
                                              {"Sibiu", false},
                                              {"Timisoara", false},
                                              {"Urziceni", false},
                                              {"Vaslui", false},
                                              {"Zerind", false}};

    // Fila com prioridade na distancia em linha reta ate Bucharest
    priority_queue<vizinho, vector<vizinho>, compararGuloso> filaDeCidades;

    filaDeCidades.push({origem, 0});
    unsigned int distanciaAtual = 0;

    // Para salvar o caminho de volta do destino final e saber o melhor caminho
    unordered_map<string, string> deOndeEuVim_Guloso;
    cout << "Utilizando o algoritmo Guloso\nPartindo de " << origem;
    while (!filaDeCidades.empty())
    {
        cidadeAtual = filaDeCidades.top().nome;
        if (cidadeAtual == "Bucharest")
        {
            string cidade = cidadeAtual;
            stack<string> ordemDasCidades;
            ordemDasCidades.push(cidadeAtual);
            string anterior = cidadeAtual;

            // Faz o caminho contrario, do destino para origem
            while (cidade != origem)
            {
                cidade = deOndeEuVim_Guloso[cidade];
                distanciaAtual += distanciaEntre(anterior, cidade);
                anterior = cidade;
                ordemDasCidades.push(cidade);
            }

            const int tam = ordemDasCidades.size();

            cout << " o melhor caminho encontrado foi:\n";
            for (int i = 0; i < tam - 1; i++)
            {
                cout << ordemDasCidades.top() << " => ";
                ordemDasCidades.pop();
            }
            cout << ordemDasCidades.top();

            cout << "\nChegamos ao destino final, com uma distancia de: " << distanciaAtual << endl
                 << endl;
            return distanciaAtual;
        }

        visitado[cidadeAtual] = true;
        naFila[cidadeAtual] = false;
        filaDeCidades.pop();

        vector<vizinho> vizinhas = mapa[cidadeAtual].vizinhos;

        // Adiciona na fila de cidades a serem visitadas todas as que
        // ainda nao foram visitadas e que nao foram inseridas na fila por outra cidade
        for (auto cidade : vizinhas)
            if (!visitado[cidade.nome])
                if (!naFila[cidade.nome])
                {
                    filaDeCidades.push(cidade);
                    naFila[cidade.nome] = true;
                    deOndeEuVim_Guloso[cidade.nome] = cidadeAtual;
                }
    }
    // Nao foi possivel encontrar um caminho
    return -1;
}

// Função que implementa a busca A*
int Aestrela(string origem)
{

    string cidadeAtual;
    // Cidades que foram visitadas e que estao na fila para serem visitadas
    // Mantem-se a lista de quais estao na fila para nao ser adicionada novamente
    unordered_map<string, bool> visitado, naFila = {
                                              {"Arad", false},
                                              {"Bucharest", false},
                                              {"Craiova", false},
                                              {"Drobeta", false},
                                              {"Eforie", false},
                                              {"Fagaras", false},
                                              {"Giurgiu", false},
                                              {"Hirsova", false},
                                              {"Iasi", false},
                                              {"Lugoj", false},
                                              {"Mehadia", false},
                                              {"Neamt", false},
                                              {"Oradea", false},
                                              {"Pitesti", false},
                                              {"Rimnicu_Vilcea", false},
                                              {"Sibiu", false},
                                              {"Timisoara", false},
                                              {"Urziceni", false},
                                              {"Vaslui", false},
                                              {"Zerind", false}};

    // Fila com prioridade na distancia em linha reta ate Bucharest + distancia ate a cidade que esta sendo analisada
    priority_queue<vizinho, vector<vizinho>, compararEstrela> filaDeCidades;

    filaDeCidades.push({origem, 0});
    unsigned int distanciaAtual = 0;
    cidadeAtual = origem;

    cout << "Utilizando o algoritmo A*\nPartindo de " << cidadeAtual;
    while (!filaDeCidades.empty())
    {
        cidadeAtual = filaDeCidades.top().nome;
        visitado[cidadeAtual] = true;
        if (cidadeAtual == "Bucharest")
        {
            string cidade = cidadeAtual;
            stack<string> ordemDasCidades;
            ordemDasCidades.push(cidadeAtual);
            string anterior = cidadeAtual;

            // Faz o caminho contrario, do destino para origem
            while (cidade != origem)
            {
                cidade = deOndeEuVim_Estrela[cidade];
                distanciaAtual += distanciaEntre(anterior, cidade);
                anterior = cidade;
                ordemDasCidades.push(cidade);
            }

            const int tam = ordemDasCidades.size();

            cout << " o melhor caminho encontrado foi:\n";
            for (int i = 0; i < tam - 1; i++)
            {
                cout << ordemDasCidades.top() << " => ";
                ordemDasCidades.pop();
            }
            cout << ordemDasCidades.top();

            cout << "\nChegamos ao destino final, com uma distancia de: " << distanciaAtual << endl
                 << endl;
            return distanciaAtual;
        }

        naFila[cidadeAtual] = false;
        filaDeCidades.pop();

        vector<vizinho> vizinhas = mapa[cidadeAtual].vizinhos;

        // Adiciona na fila de cidades a serem visitadas todas as que
        // ainda nao foram visitadas e que nao foram inseridas na fila por outra cidade
        for (auto cidade : vizinhas)
            if (!visitado[cidade.nome])
                if (!naFila[cidade.nome])
                {
                    deOndeEuVim_Estrela[cidade.nome] = cidadeAtual;
                    filaDeCidades.push(cidade);
                    naFila[cidade.nome] = true;
                };
    }
    // Nao foi possivel encontrar um caminho
    return -1;
}

int main()
{
    /**
     * Sugestao de como rodar o programa
     * g++ codigo.cpp && ./a.out < input.txt > resposta.txt
     * Desta maneira serao inseridas todas as cidades (exeto Bucharest)
     * para serem testadas, que estao listadas no arquivo input.txt,
     * suas respostas serao escritas no arquivo respostas.txt
     */

    mapa["Arad"] = dadosDaCidade{{{"Zerind", 75}, {"Timisoara", 118}, {"Sibiu", 140}}, 366};
    mapa["Bucharest"] = dadosDaCidade{{{"Giurgiu", 90}, {"Urziceni", 85}, {"Pitesti", 101}, {"Fagaras", 211}}, 0};
    mapa["Craiova"] = dadosDaCidade{{{"Drobeta", 120}, {"Rimnicu_Vilcea", 146}, {"Pitesti", 138}}, 160};
    mapa["Drobeta"] = dadosDaCidade{{{"Mehadia", 75}, {"Craiova", 120}}, 242};
    mapa["Eforie"] = dadosDaCidade{{{"Hirsova", 86}}, 161};
    mapa["Fagaras"] = dadosDaCidade{{{"Sibiu", 99}, {"Bucharest", 211}}, 176};
    mapa["Giurgiu"] = dadosDaCidade{{{"Bucharest", 90}}, 77};
    mapa["Hirsova"] = dadosDaCidade{{{"Eforie", 86}, {"Urziceni", 98}}, 151};
    mapa["Iasi"] = dadosDaCidade{{{"Neamt", 87}, {"Vaslui", 92}}, 226};
    mapa["Lugoj"] = dadosDaCidade{{{"Timisoara", 111}, {"Mehadia", 70}}, 244};
    mapa["Mehadia"] = dadosDaCidade{{{"Lugoj", 70}, {"Drobeta", 75}}, 241};
    mapa["Neamt"] = dadosDaCidade{{{"Iasi", 87}}, 234};
    mapa["Oradea"] = dadosDaCidade{{{"Zerind", 71}, {"Sibiu", 151}}, 380};
    mapa["Pitesti"] = dadosDaCidade{{{"Craiova", 138}, {"Rimnicu_Vilcea", 97}, {"Bucharest", 101}}, 100};
    mapa["Rimnicu_Vilcea"] = dadosDaCidade{{{"Craiova", 146}, {"Sibiu", 80}, {"Pitesti", 97}}, 193};
    mapa["Sibiu"] = dadosDaCidade{{{"Arad", 140}, {"Oradea", 151}, {"Fagaras", 99}, {"Rimnicu_Vilcea", 80}}, 253};
    mapa["Timisoara"] = dadosDaCidade{{{"Arad", 118}, {"Lugoj", 111}}, 329};
    mapa["Urziceni"] = dadosDaCidade{{{"Bucharest", 85}, {"Hirsova", 98}, {"Vaslui", 142}}, 80};
    mapa["Vaslui"] = dadosDaCidade{{{"Iasi", 92}, {"Urziceni", 142}}, 199};
    mapa["Zerind"] = dadosDaCidade{{{"Arad", 75}, {"Oradea", 71}}, 374};

    string origem;
    // Podem ser utilizados varios casos de teste
    while (cin >> origem)
    {
        guloso(origem);
        Aestrela(origem);
    }
}
