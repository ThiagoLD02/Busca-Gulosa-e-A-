#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <cmath>
#include <set>

using namespace std;

// Estrutura para armazenar as informações de uma cidade
struct City
{
    string name;
    int straight_distance;
    vector<pair<City *, int>> neighbors;
};

// Comparador para a fila de prioridade
struct Compare
{
    bool operator()(const pair<City *, int> &a, const pair<City *, int> &b)
    {
        return a.second > b.second;
    }
};

// Função para criar o grafo
map<string, City> createGraph()
{
    map<string, City> graph;

    vector<tuple<string, string, int>> connections = {
        {"Arad", "Sibiu", 140},
        {"Arad", "Zerind", 75},
        {"Arad", "Timisoara", 111},
        {"Zerind", "Oradea", 71},
        {"Oradea", "Sibiu", 151},
        {"Timisoara", "Lugoj", 111},
        {"Lugoj", "Mehedia", 70},
        {"Mehedia", "Drobeta", 75},
        {"Drobeta", "Craiova", 120},
        {"Craiova", "Rimnicu Vilcea", 146},
        {"Craiova", "Pitesti", 138},
        {"Rimnicu Vilcea", "Pitesti", 97},
        {"Rimnicu Vilcea", "Sibiu", 80},
        {"Sibiu", "Fagaras", 99},
        {"Fagaras", "Bucharest", 211},
        {"Pitesti", "Bucharest", 101},
        {"Bucharest", "Giurgiu", 90},
        {"Bucharest", "Urziceni", 85},
        {"Urziceni", "Hirsova", 98},
        {"Urziceni", "Vaslui", 142},
        {"Hirsova", "Eforie", 86},
        {"Vaslui", "Iasi", 92},
        {"Iasi", "Neamt", 87}};

    for (const auto &connection : connections)
    {
        const auto &city1 = get<0>(connection);
        const auto &city2 = get<1>(connection);
        int distance = get<2>(connection);

        graph[city1].neighbors.push_back(make_pair(&graph[city2], distance));
        graph[city2].neighbors.push_back(make_pair(&graph[city1], distance));
    }

    return graph;
}

// Função para adicionar as distâncias em linha reta até Bucharest
void addStraightDistances(map<string, City> &graph)
{
    graph["Arad"].straight_distance = 366;
    graph["Bucharest"].straight_distance = 0;
    graph["Craiova"].straight_distance = 160;
    graph["Drobeta"].straight_distance = 242;
    graph["Eforie"].straight_distance = 161;
    graph["Fagaras"].straight_distance = 176;
    graph["Giurgiu"].straight_distance = 77;
    graph["Hirsova"].straight_distance = 151;
    graph["Iasi"].straight_distance = 226;
    graph["Lugoj"].straight_distance = 244;
    graph["Mehadia"].straight_distance = 241;
    graph["Neamt"].straight_distance = 234;
    graph["Oradea"].straight_distance = 380;
    graph["Pitesti"].straight_distance = 100;
    graph["Rimnicu Vilcea"].straight_distance = 193;
    graph["Sibiu"].straight_distance = 253;
    graph["Timisoara"].straight_distance = 329;
    graph["Urziceni"].straight_distance = 80;
    graph["Vaslui"].straight_distance = 199;
    graph["Zerind"].straight_distance = 374;

    for (auto &city : graph)
    {
        city.second.name = city.first;
    }
}

// Busca gulosa
vector<City *> greedySearch(City *start, City *goal)
{
    map<City *, City *> came_from;
    set<City *> visited;
    priority_queue<pair<City *, int>, vector<pair<City *, int>>, Compare> frontier;
    frontier.push(make_pair(start, start->straight_distance));

    came_from[start] = nullptr;
    visited.insert(start);

    while (!frontier.empty())
    {
        City *current = frontier.top().first;
        frontier.pop();

        if (current == goal)
        {
            break;
        }

        for (auto &edge : current->neighbors)
        {
            City *next = edge.first;

            if (visited.find(next) == visited.end())
            {
                int priority = next->straight_distance;
                frontier.push(make_pair(next, priority));
                came_from[next] = current;
                visited.insert(next);
            }
        }
    }

    vector<City *> path;
    if (came_from.find(goal) != came_from.end())
    {
        City *current = goal;
        while (current != nullptr)
        {
            path.push_back(current);
            current = came_from[current];
        }
        reverse(path.begin(), path.end());
    }

    return path;
}

// Busca A*
vector<City *> aStarSearch(City *start, City *goal)
{
    map<City *, City *> came_from;
    map<City *, int> cost_so_far;
    priority_queue<pair<City *, int>, vector<pair<City *, int>>, Compare> frontier;
    frontier.push(make_pair(start, 0));

    came_from[start] = nullptr;
    cost_so_far[start] = 0;

    while (!frontier.empty())
    {
        City *current = frontier.top().first;
        frontier.pop();

        if (current == goal)
        {
            break;
        }

        for (auto &edge : current->neighbors)
        {
            City *next = edge.first;
            int new_cost = cost_so_far[current] + edge.second;

            if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next])
            {
                cost_so_far[next] = new_cost;
                int priority = new_cost + next->straight_distance;
                frontier.push(make_pair(next, priority));
                came_from[next] = current;
            }
        }
    }

    vector<City *> path;
    if (came_from.find(goal) != came_from.end())
    {
        City *current = goal;
        while (current != nullptr)
        {
            path.push_back(current);
            current = came_from[current];
        }
        reverse(path.begin(), path.end());
    }

    return path;
}

void printPath(const vector<City *> &path, const string &search_type)
{
    cout << "Caminho encontrado pela busca " << search_type << ":" << endl;
    int total_distance = 0;
    for (size_t i = 0; i < path.size(); ++i)
    {
        cout << path[i]->name;
        if (i < path.size() - 1)
        {
            cout << " -> ";
            for (const auto &edge : path[i]->neighbors)
            {
                if (edge.first == path[i + 1])
                {
                    total_distance += edge.second;
                    break;
                }
            }
        }
    }
    cout << endl
         << "Distância total (" << search_type << "): " << total_distance << endl
         << endl;
}

int main()
{
    map<string, City> graph = createGraph();
    addStraightDistances(graph);

    City *start = &graph["Arad"];
    City *goal = &graph["Bucharest"];

    vector<City *> greedy_path = greedySearch(start, goal);
    vector<City *> a_star_path = aStarSearch(start, goal);

    printPath(greedy_path, "Gulosa");
    printPath(a_star_path, "A*");
}

/*
**greedySearch**

A lógica do algoritmo de busca gulosa (greedy search) é selecionar o vizinho que parece ser o melhor a cada passo, sem levar em consideração o custo já percorrido. Nesse caso, a heurística utilizada foi a distância em linha reta entre a cidade atual e a cidade destino (Bucharest). O algoritmo consiste nas seguintes etapas:

1. Começar na cidade inicial e marcá-la como visitada.
2. Selecionar o vizinho não visitado com a menor distância em linha reta até o destino.
3. Marcar o vizinho selecionado como visitado e definir a cidade atual como sendo o vizinho selecionado.
4. Repetir os passos 2 e 3 até alcançar a cidade destino ou não houver mais vizinhos não visitados.

**aStarSearch**

O algoritmo A* é um algoritmo de busca informada que combina a heurística do algoritmo de busca gulosa e o custo real para se mover do nó inicial até o nó atual. A heurística utilizada também foi a distância em linha reta entre a cidade atual e a cidade destino. O algoritmo consiste nas seguintes etapas:

1. Inserir a cidade inicial na lista aberta (open list) e calcular o custo total estimado (f = g + h) para cada cidade.
2. Enquanto a lista aberta não estiver vazia, fazer:
   a. Selecionar a cidade com o menor custo total estimado (f) na lista aberta e definir como a cidade atual.
   b. Se a cidade atual for a cidade destino, reconstruir e retornar o caminho.
   c. Remover a cidade atual da lista aberta e inserir na lista fechada.
   d. Para cada vizinho da cidade atual, calcular o custo total estimado (f) e atualizar a cidade anterior do vizinho, se necessário. Inserir o vizinho na lista aberta caso não esteja na lista fechada.

**Comparativo**

- Complexidade:
  - greedySearch: A complexidade do algoritmo de busca gulosa é, em geral, menor que a do A* porque explora menos caminhos. No entanto, isso pode levar a soluções subótimas.
  - aStarSearch: A complexidade do algoritmo A* é maior, pois explora mais caminhos. Porém, isso faz com que ele encontre a solução ótima na maioria dos casos.

- Tempo:
  - greedySearch: A busca gulosa geralmente é mais rápida, pois explora menos caminhos.
  - aStarSearch: O A* pode ser mais lento, pois explora mais caminhos, mas pode ser otimizado utilizando heurísticas apropriadas.

- Resultados:
  - greedySearch: O algoritmo de busca gulosa pode encontrar soluções subótimas, pois não leva em consideração o custo já percorrido.
  - aStarSearch: O algoritmo A* encontra a solução ótima na maioria dos casos, pois considera tanto a heurística quanto o custo real do caminho.

Em resumo, a busca gulosa é geralmente mais rápida, mas pode encontrar soluções subótimas. O algoritmo A* é mais completo e encontra soluções ótimas na maioria dos casos.

 */