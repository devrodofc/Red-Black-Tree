# Red-Black Tree

Implementação robusta de **Árvore Rubro-Negra (Red-Black Tree)** em C com benchmarks de desempenho.

## 📋 Sobre o Projeto

Uma árvore rubro-negra é uma estrutura de dados de busca binária auto-balanceada que garante operações eficientes (inserção, remoção e busca) em tempo $O(\log n)$.

### Características

- ✅ **Operações otimizadas**: Inserção, remoção e busca em $O(\log n)$
- ✅ **Auto-balanceamento**: Mantém altura balanceada através das cores (RED/BLACK)
- ✅ **Benchmarks inclusos**: Suite completa de testes de desempenho
- ✅ **Relatórios em CSV**: Exportação de resultados para análise
- ✅ **Implementação em C puro**: Sem dependências externas

## 🏗️ Estrutura do Projeto

```
red-black-tree/
├── src/                      # Código-fonte
│   ├── main.c               # Entrada principal com benchmark
│   ├── rbtree.c             # Implementação da árvore
│   ├── benchmark.c          # Suite de benchmarks
│   └── csv.c                # Geração de relatórios CSV
├── include/                 # Headers
│   ├── rbtree.h             # Interface da árvore
│   ├── benchmark.h          # Interface dos benchmarks
│   └── csv.h                # Interface CSV
├── CMakeLists.txt           # Build CMake
├── Makefile                 # Build alternativo
├── results/                 # Resultados dos benchmarks
│   └── results.csv          # Dados exportados
└── README.md                # Este arquivo
```

## 🚀 Como Usar

### Requisitos

- **Compilador C**: GCC, Clang ou MSVC
- **CMake** (opcional): v3.20+
- **Make** (opcional): Para build via Makefile

### Compilação

#### Opção 1: CMake

```bash
# Build Debug
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .

# Build Release (otimizado)
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

#### Opção 2: Make

```bash
make build      # Compila o projeto
make run        # Executa os benchmarks
make clean      # Remove arquivos compilados
```

### Execução

```bash
./red_black_tree
```

O programa executará benchmarks de desempenho e salvará os resultados em `results/results.csv`.

## 📊 API da Árvore Rubro-Negra

### Estruturas

```c
typedef enum { RED, BLACK } Color;

typedef struct RBTree {
    RBNode *root;        // Raiz da árvore
    RBNode *nil;         // Sentinela NIL
    size_t node_count;   // Quantidade de nós
} RBTree;
```

### Funções Principais

| Função | Descrição |
|--------|-----------|
| `rbtree_create()` | Cria uma nova árvore vazia |
| `rbtree_insert(tree, key)` | Insere um elemento com balanceamento |
| `rbtree_search(tree, key)` | Busca um elemento (retorna nó ou NULL) |
| `rbtree_delete(tree, key)` | Remove um elemento mantendo propriedades |
| `rbtree_minimum(tree, node)` | Encontra o nó com chave mínima |

### Exemplo de Uso

```c
#include "include/rbtree.h"

RBTree *tree = rbtree_create();

// Inserir elementos
rbtree_insert(tree, 10);
rbtree_insert(tree, 5);
rbtree_insert(tree, 15);

// Buscar elemento
RBNode *node = rbtree_search(tree, 5);
if (node != NULL) {
    printf("Elemento encontrado: %d\n", node->key);
}

// Remover elemento
rbtree_delete(tree, 5);
```

## 📈 Benchmarks

O projeto inclui uma suite completa de testes de desempenho que medem:

- **Inserção**: Tempo para inserir N elementos
- **Busca**: Tempo para buscar elementos
- **Remoção**: Tempo para remover elementos
- **Casos variados**: Diferentes distribuições de dados

Os resultados são salvos em formato CSV em `results/results.csv` para análise posterior.

### Executar Benchmarks

```bash
make run
```

Os dados serão exportados para `results/results.csv`.

## 🔑 Propriedades da Árvore Rubro-Negra

Uma árvore rubro-negra válida satisfaz as seguintes propriedades:

1. Todo nó é vermelho ou preto
2. A raiz é sempre preta
3. Todas as folhas (NIL) são pretas
4. Se um nó é vermelho, seus filhos são pretos
5. Todo caminho da raiz a uma folha tem o mesmo número de nós pretos

Essas propriedades garantem que a árvore permanece balanceada, com altura máxima de $2 \log(n + 1)$.

## 🏆 Complexidade de Tempo

| Operação | Melhor | Médio | Pior |
|----------|--------|-------|------|
| Busca | $O(1)$ | $O(\log n)$ | $O(\log n)$ |
| Inserção | $O(1)$ | $O(\log n)$ | $O(\log n)$ |
| Remoção | $O(1)$ | $O(\log n)$ | $O(\log n)$ |
| Espaço | - | - | $O(n)$ |

## 🛠️ Build Otimizado

Para melhor desempenho, compile em modo Release:

```bash
cmake -DCMAKE_BUILD_TYPE=Release -B build
cmake --build build
```

Modo Release ativa otimizações como:
- `-O3`: Otimização agressiva
- `-march=native`: Otimizações específicas da CPU

## 📝 Licença

Este projeto é fornecido como material educacional.

## 👤 Autor

Rodrigo Morais Herrmann

Desenvolvido como projeto de estruturas de dados.


