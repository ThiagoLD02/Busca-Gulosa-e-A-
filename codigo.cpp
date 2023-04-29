#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// Declarando lista de distâncias
vector<vector<pair<string, int>>> grafo(20); // lista de adjacências
unordered_map<string, int> codigoDasCidades;
unordered_map<string, vector<string>> cidadesVizinhas;

// Função que implementa a busca gulosa
int guloso(string origem, string destino)
{

    string cidadeAtual;
    unordered_map<string, bool> visitado = {
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

    cidadeAtual = origem;
    unsigned int distanciaAtual = 0;
    bool procurando = true;

    cout << "Partindo de " << origem << endl;
    while (procurando)
    {
        // Marcando esta cidade como visitada
        visitado.at(cidadeAtual) = true;
        // Se a cidade de inicio eh a de destino
        if (cidadeAtual == destino)
        {
            cout << "Chegamos a " << cidadeAtual << ", percorrendo uma distancia de " << distanciaAtual << endl;
            return distanciaAtual;
        }
        // Caso contrario encontrar o menor caminho das cidades vizinhas

        int codigoCidadeAtual;
        // Inicializando com vazio
        pair<string, int> cidadeMaisProxima = {"", -1};

        codigoCidadeAtual = codigoDasCidades.at(cidadeAtual);

        vector<pair<string, int>> cidadesVizinhas = grafo.at(codigoCidadeAtual);

        for (auto cidade : cidadesVizinhas)
        {
            // Se a cidade nao foi visitada
            if (visitado.at(cidade.first) == false)
            {

                if (cidadeMaisProxima.first == "")
                { // Caso inicial
                    cidadeMaisProxima = cidade;
                    continue;
                }

                // Se a distancia para esta cidade eh menor do que a anterior, salvamos
                if (cidade.second < cidadeMaisProxima.second)
                {
                    cidadeMaisProxima = cidade;
                }
            }
        }

        if (cidadeMaisProxima.first != "")
        { // Encontramos uma cidade para visitar
            cout << "Encontramos uma cidade para visitar: " << cidadeMaisProxima.first << ", que esta a " << cidadeMaisProxima.second << " de distancia.\n";
            distanciaAtual += cidadeMaisProxima.second;
            cidadeAtual = cidadeMaisProxima.first;
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

int main()
{

    cidadesVizinhas = {

        {"Arad", {"Zerind", "Timisoara", "Sibiu"}},
        {"Bucharest", {"Giurgiu", "Urziceni", "Pitesti", "Fagaras"}},
        {"Craiova", {"Drobeta", "Rimnicu_Vilcea", "Pitesti"}},
        {"Drobeta", {"Mehadia", "Craiova"}},
        {"Eforie", {"Hirsova"}},
        {"Fagaras", {"Sibiu", "Bucharest"}},
        {"Giurgiu", {"Bucharest"}},
        {"Hirsova", {"Eforie", "Urziceni"}},
        {"Iasi", {"Neamt", "Vaslui"}},
        {"Lugoj", {"Timisoara", "Mehadia"}},
        {"Mehadia", {"Lugoj", "Drobeta"}},
        {"Neamt", {"Iasi"}},
        {"Oradea", {"Zerind", "Sibiu"}},
        {"Pitesti", {"Rimnicu_Vilcea", "Craiova", "Bucharest"}},
        {"Rimnicu_Vilcea", {"Sibiu", "Craiova", "Pitesti"}},
        {"Sibiu", {"Arad"
                   "Oradea",
                   "Fagaras", "Rimnicu_Vilcea"}},
        {"Timisoara", {"Arad", "Lugoj"}},
        {"Urziceni", {"Vaslui", "Hirsova", "Bucharest"}},
        {"Vaslui", {"Iasi", "Urziceni"}},
        {"Zerind", {"Oradea", "Arad"}}};

    codigoDasCidades = {
        {"Arad", 0},
        {"Bucharest", 1},
        {"Craiova", 2},
        {"Drobeta", 3},
        {"Eforie", 4},
        {"Fagaras", 5},
        {"Giurgiu", 6},
        {"Hirsova", 7},
        {"Iasi", 8},
        {"Lugoj", 9},
        {"Mehadia", 10},
        {"Neamt", 11},
        {"Oradea", 12},
        {"Pitesti", 13},
        {"Rimnicu_Vilcea", 14},
        {"Sibiu", 15},
        {"Timisoara", 16},
        {"Urziceni", 17},
        {"Vaslui", 18},
        {"Zerind", 19}};

    string origem, destino;
    while (cin >> origem >> destino)
        guloso(origem, destino);
}
