# Tabela Hash

## Etapa 1:

Elabore um algoritmo que crie um arquivo de entrada com um conjunto de valores e suas respectivas chaves, para serem inseridos em uma tabela Hash. Este algoritmo recebe como parâmetro o número de elementos, o tipo das entradas e o nome do arquivo resultante.

Cada registro é posto em uma linha do arquivo e deve conter uma chave inteira com valor entre 0 e 1023, e um valor composto por 3 letras. Estes valores serão definidos aleatoriamente, mas garanta que não exitem chaves com valores repetidos.

São dois tipos de arquivos de entrada possíveis: 1) todas as chaves geradas têm valor par; 2) sem restrição.

## Etapa 2:

Implemente uma tabela Hash, uma que trate as colisões com encadeamento externo. Desenvolva todas as funções necessárias para manipulação da estrutura (inserção, busca, etc).

## Etapa 3:

Desenvolva um sistema para avaliação da função Hash. Implemente 2 funções Hash distintas. Este sistema irá utilizar uma tabela Hash de tamanho 100. A avaliação deverá executar um mesmo aquivo de entrada para cada função Hash implementada.

Para cada execução, contabilize o número de colisões que ocorreram.

Gere 10 entradas com 20, com 50 e 80 registros (total de 30 arquivos) diferentes que serão utilizadas nos testes. Em cada conjunto de 10 arquivos, 5 são do tipo 1 e 5 do tipo 2.
