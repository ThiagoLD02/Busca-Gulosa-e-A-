#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// Declarando lista de distâncias
vector<vector<pair<string, int>>> grafo(20); // lista de adjacências
unordered_map<string, vector<string>> cidadesVizinhas;
unordered_map<string, int> distanciasEmLinhaReta;
unordered_map<string, int> codigoDasCidades;
vector<vector<pair<string, int>>> distancias(20);

int distanciaEntre(string origem, string destino)
{
    int index = codigoDasCidades[origem];
    auto vizinhos = distancias[index];
    for (auto cidade : vizinhos)
        if (cidade.first == destino)
            return cidade.second;

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

    queue<string> filaDeCidades;

    filaDeCidades.push(origem);
    unsigned int distanciaAtual = 0;

    cout << "Partindo de " << origem << endl;
    while (!filaDeCidades.empty())
    {
        cidadeAtual = filaDeCidades.front();
        if (cidadeAtual == "Bucharest")
        {
            cout << "Chegamos ao destino final, com uma distancia de: " << distanciaAtual << endl;
            return distanciaAtual;
        }

        visitado[cidadeAtual] = true;
        vector<string> vizinhas = cidadesVizinhas[cidadeAtual];
        int menor = 10000;
        string proximaCidade;

        for (string cidade : vizinhas)
        {
            if (!visitado[cidade])
                if (distanciasEmLinhaReta[cidade] < menor)
                {
                    proximaCidade = cidade;
                    menor = distanciasEmLinhaReta[cidade];
                }
        }
        if (menor == 10000)
        {
            cout << "Nao foi possivel chegar ao destino escolhido\n";
            return -1;
        }
        distanciaAtual += distanciaEntre(cidadeAtual, proximaCidade);
        filaDeCidades.pop();
        filaDeCidades.push(proximaCidade);
        cout << "Indo para " << proximaCidade << " a uma distancia de " << distanciaEntre(cidadeAtual, proximaCidade) << endl;
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
        {"Sibiu", {"Arad", "Oradea", "Fagaras", "Rimnicu_Vilcea"}},
        {"Timisoara", {"Arad", "Lugoj"}},
        {"Urziceni", {"Vaslui", "Hirsova", "Bucharest"}},
        {"Vaslui", {"Iasi", "Urziceni"}},
        {"Zerind", {"Oradea", "Arad"}}};

    // Lista de distâncias
    distancias[0] = {{"Zerind", 75}, {"Timisoara", 118}, {"Sibiu", 140}};                       // Arad
    distancias[1] = {{"Giurgiu", 90}, {"Urziceni", 85}, {"Pitesti", 101}, {"Fagaras", 211}};    // Bucharest
    distancias[2] = {{"Drobeta", 120}, {"Rimnicu_Vilcea", 146}, {"Pitesti", 138}};              // Craiova
    distancias[3] = {{"Mehadia", 75}, {"Craiova", 120}};                                        // Drobeta
    distancias[4] = {{"Hirsova", 86}};                                                          // Eforie
    distancias[5] = {{"Sibiu", 99}, {"Bucharest", 211}};                                        // Fagaras
    distancias[6] = {{"Bucharest", 90}};                                                        // Giurgiu
    distancias[7] = {{"Eforie", 86}, {"Urziceni", 98}};                                         // Hirsova
    distancias[8] = {{"Neamt", 87}, {"Vaslui", 92}};                                            // Iasi
    distancias[9] = {{"Lugoj", 111}, {"Mehadia", 70}};                                          // Lugoj
    distancias[10] = {{"Lugoj", 70}, {"Drobeta", 75}};                                          // Mehadia
    distancias[11] = {{"Iasi", 87}};                                                            // Neamt
    distancias[12] = {{"Zerind", 71}, {"Sibiu", 151}};                                          // Oradea
    distancias[13] = {{"Craiova", 138}, {"Rimnicu_Vilcea", 97}, {"Bucharest", 101}};            // Pitesti
    distancias[14] = {{"Craiova", 146}, {"Drobeta", 80}, {"Pitesti", 97}};                      // Rimnicu_Vilcea
    distancias[15] = {{"Arad", 140}, {"Oradea", 151}, {"Fagaras", 99}, {"Rimnicu_Vilcea", 80}}; // Sibiu
    distancias[16] = {{"Arad", 118}, {"Lugoj", 111}};                                           // Timisoara
    distancias[17] = {{"Bucharest", 85}, {"Hirsova", 98}, {"Vaslui", 142}};                     // Urziceni
    distancias[18] = {{"Iasi", 92}, {"Urziceni", 142}};                                         // Vaslui
    distancias[19] = {{"Arad", 75}, {"Oradea", 71}};                                            // Zerind

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

    distanciasEmLinhaReta["Arad"] = 366;
    distanciasEmLinhaReta["Craiova"] = 160;
    distanciasEmLinhaReta["Drobeta"] = 242;
    distanciasEmLinhaReta["Eforie"] = 161;
    distanciasEmLinhaReta["Fagaras"] = 176;
    distanciasEmLinhaReta["Giurgiu"] = 77;
    distanciasEmLinhaReta["Hirsova"] = 151;
    distanciasEmLinhaReta["Iasi"] = 226;
    distanciasEmLinhaReta["Lugoj"] = 244;
    distanciasEmLinhaReta["Mehadia"] = 241;
    distanciasEmLinhaReta["Neamt"] = 234;
    distanciasEmLinhaReta["Oradea"] = 380;
    distanciasEmLinhaReta["Pitesti"] = 100;
    distanciasEmLinhaReta["Rimnicu_Vilcea"] = 193;
    distanciasEmLinhaReta["Sibiu"] = 253;
    distanciasEmLinhaReta["Timisoara"] = 329;
    distanciasEmLinhaReta["Urziceni"] = 80;
    distanciasEmLinhaReta["Vaslui"] = 199;
    distanciasEmLinhaReta["Zerind"] = 374;

    string origem;
    while (cin >> origem)
        guloso(origem);
}
