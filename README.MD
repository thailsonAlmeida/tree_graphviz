# OBJETIVO
- Exportar os dados de uma arvore para um arquivo .dot utilizando o GRAPHVIZ
- Gerar PDF ou PNG da arvore exportada

# LINGUAGEM
- C

# PESQUISA
## O que é o Graphviz?
- É um software open source.
- Gera formas visuais que representam estruturas de informação.
- Gera diagramas
- Possui diversos layouts gráficos

## O que é Linguagem DOT?
- DOT é a sintaxe utilizada pelo Graphviz para criar as formas.
- DOT define os nodes, edges, graphs, subgraphs e clusters
- Tipos de estruturas que o Graphviz pode representar?
    - Representação de estruturas de dados
    - Lista
    - Árvore
    - Modelo de dados entidade e relacionamento
    - Árvore genealógica
    - Diagramas    
    - Estrutura de processos
    - Estrutura de rede de comutação
    - Todo e qualquer conceito pode ser representado por meio de formas.

## Como gerar um arquivo DOT que exporta uma árvore binária e, posteriormente, gerar um PDF ou PNG
```bash
dot -Tpng nome_arquivo.dot -o nome_arquivo.png
```

```bash
dot -Tpdf nome_arquivo.dot -o nome_arquivo.pdf
```


# LIKS UTEIS
- [Instale o Graphviz](https://graphviz.org/doc/winbuild.html)
- [Compreenda a linguagem DOT](https://graphviz.org/doc/info/lang.html)
- [Faça alguns exemplos de arquivo .dot manualmente e converta-os para PDF ou PNG via graphviz](https://graphviz.org/doc/info/command.html)
- [Aprenda a executar comandos do prompt via código C](https://man7.org/linux/man-pages/man3/system.3.html)