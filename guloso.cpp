#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

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

unordered_map<string, dadosDaCidade> mapa;

struct comparar
{

    bool operator()(vizinho a, vizinho b)
    {
        return mapa[a.nome].distanciaEmLinhaReta > mapa[b.nome].distanciaEmLinhaReta;
    }
};

int distanciaEntre(string origem, string destino)
{

    auto vizinhos = mapa[origem].vizinhos;
    for (auto cidade : vizinhos)
        if (cidade.nome == destino)
            return cidade.distancia;

    return -1;
}

// Função que implementa a busca gulosa
int guloso(string origem)
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

    priority_queue<vizinho, vector<vizinho>, comparar> filaDeCidades;

    filaDeCidades.push({origem, 0});
    unsigned int distanciaAtual = 0;

    cout << "Partindo de " << origem << endl;
    while (!filaDeCidades.empty())
    {
        cidadeAtual = filaDeCidades.top().nome;
        if (cidadeAtual == "Bucharest")
        {
            cout << "Chegamos ao destino final, com uma distancia de: " << distanciaAtual << endl
                 << endl;
            return distanciaAtual;
        }

        visitado[cidadeAtual] = true;
        filaDeCidades.pop();

        vector<vizinho> vizinhas = mapa[cidadeAtual].vizinhos;

        for (auto cidade : vizinhas)
            if (!visitado[cidade.nome])
                filaDeCidades.push(cidade);

        cout << "Indo para " << filaDeCidades.top().nome << endl;
    }
    return -1;
}

int main()
{

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
    mapa["Rimnicu_Vilcea"] = dadosDaCidade{{{"Craiova", 146}, {"Drobeta", 80}, {"Pitesti", 97}}, 193};
    mapa["Sibiu"] = dadosDaCidade{{{"Arad", 140}, {"Oradea", 151}, {"Fagaras", 99}, {"Rimnicu_Vilcea", 80}}, 253};
    mapa["Timisoara"] = dadosDaCidade{{{"Arad", 118}, {"Lugoj", 111}}, 329};
    mapa["Urziceni"] = dadosDaCidade{{{"Bucharest", 85}, {"Hirsova", 98}, {"Vaslui", 142}}, 80};
    mapa["Vaslui"] = dadosDaCidade{{{"Iasi", 92}, {"Urziceni", 142}}, 199};
    mapa["Zerind"] = dadosDaCidade{{{"Arad", 75}, {"Oradea", 71}}, 374};

    string origem;
    while (cin >> origem)
        guloso(origem);
}
