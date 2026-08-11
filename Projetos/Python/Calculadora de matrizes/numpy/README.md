<h1 align="center">Calculadora de Matrizes — versão NumPy</h1>

<p align="center">
  Álgebra linear no terminal, com <code>numpy.ndarray</code> como estrutura de dados.<br>
  <strong>9 operações implementadas do zero</strong> — o NumPy guarda, os algoritmos são meus.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Python-3.10%2B-3776AB?style=for-the-badge&logo=python&logoColor=white" alt="Python 3.10+">
  <img src="https://img.shields.io/badge/NumPy-dtype%3Dobject-013243?style=for-the-badge&logo=numpy&logoColor=white" alt="NumPy dtype=object">
  <img src="https://img.shields.io/badge/Paradigma-OOP-ff69b4?style=for-the-badge" alt="OOP">
  <img src="https://img.shields.io/badge/Aritm%C3%A9tica-Exata-yellow?style=for-the-badge" alt="Aritmética exata">
</p>

<!-- COLE AQUI O PRINT DO MENU PRINCIPAL -->

---

Calculadora de matrizes com interface colorida em códigos ANSI e molduras em caracteres box-drawing. O diferencial está em dois pontos: todos os cálculos usam **aritmética exata com frações** (`1/3` continua sendo `1/3`, nunca vira `0.3333333333333333`), e o código é dividido em **classes com responsabilidade única**.

A matriz é um `np.ndarray` com `dtype=object`, guardando um `Fraction` em cada célula. O NumPy entra como **contêiner** — fatiamento, `shape`, fancy indexing e `hstack` — mas os algoritmos de escalonamento, determinante e inversa são implementados à mão, sem `np.linalg`.

> **Versão irmã:** existe uma implementação equivalente em listas puras, sem nenhuma dependência, no repositório [calculadora-matrizes](../sem-numpy). Ela é a versão principal do projeto — o porquê está em [O que o NumPy entrega aqui](#o-que-o-numpy-entrega-aqui).

---

## Sumário

- [Instalação e execução](#instalação-e-execução)
- [Funcionalidades](#funcionalidades)
- [Demonstração](#demonstração)
- [O que o NumPy entrega aqui](#o-que-o-numpy-entrega-aqui)
- [Bibliotecas utilizadas](#bibliotecas-utilizadas)
- [Cores e estilização no terminal](#cores-e-estilização-no-terminal)
- [Desenho das tabelas com f-string](#desenho-das-tabelas-com-f-string)
- [Arquitetura em classes](#arquitetura-em-classes)
- [O dicionário de operações](#o-dicionário-de-operações)
- [As operações matemáticas](#as-operações-matemáticas)
- [Modos de preenchimento](#modos-de-preenchimento)
- [Etapas e fluxo do programa](#etapas-e-fluxo-do-programa)
- [Validações de entrada](#validações-de-entrada)
- [Testes](#testes)
- [Problemas enfrentados](#problemas-enfrentados)

---

## Instalação e execução

```bash
pip install numpy
python3 calculadora_matrizes_numpy.py
```

Python 3.10 ou superior é obrigatório — a sintaxe de tipo `int | None` foi introduzida nessa versão. O NumPy é a única dependência externa.

---

## Funcionalidades

| # | Operação | Requisito | Algoritmo |
|:-:|----------|-----------|-----------|
| 1 | **Soma** | Mesmas dimensões | `A + B` (broadcast do NumPy) |
| 2 | **Subtração** | Mesmas dimensões | `A - B` |
| 3 | **Multiplicação** | Colunas de A = linhas de B | `A @ B` |
| 4 | **Determinante** | Matriz quadrada | Eliminação de Gauss com pivoteamento e controle de sinal |
| 5 | **Transposta** | Qualquer matriz | `.T` |
| 6 | **Traço** | Matriz quadrada | Soma da diagonal principal |
| 7 | **Norma** | Qualquer matriz | Norma-1 (maior soma absoluta entre colunas) |
| 8 | **Rank** | Qualquer matriz | Escalonamento por linhas + contagem de pivôs |
| 9 | **Inversa** | Quadrada e não singular | Gauss-Jordan com matriz aumentada `[A \| I]` |

Nenhuma função de `np.linalg` é usada. `np.linalg.det()` e `np.linalg.inv()` trabalham em ponto flutuante e não aceitam `dtype=object` — usá-las jogaria fora a aritmética exata, que é o motivo do projeto existir.

Além das operações:

- Aritmética exata com frações — resultados como `3/2` em vez de `1.4999999999999998`.
- Entrada aceita **inteiro** (`3`), **fração** (`3/4`) ou **decimal** (`0.5`), sempre convertida para `Fraction`.
- Três modos de preenchimento: número único, manual célula a célula e crescimento exponencial automático.
- Exibição com moldura, índices de linha/coluna e alinhamento calculado em tempo de execução.
- Mensagens padronizadas de sucesso, erro e aviso.
- Validação de dimensões antes de cada operação — avisa em vez de quebrar.

---

## Demonstração

**Menu principal:**

```
╔══════════════════════════════════╗
║     CALCULADORA DE MATRIZES      ║
╠═══╦══════════════════════════════╣
║ 1 ║ Somar matrizes               ║
║ 2 ║ Subtrair matrizes            ║
║ 3 ║ Multiplicar                  ║
║ 4 ║ Determinante                 ║
║ 5 ║ Transposta                   ║
║ 6 ║ Traço                        ║
║ 7 ║ Norma                        ║
║ 8 ║ Rank                         ║
║ 9 ║ Inversa                      ║
║ 0 ║ Sair                         ║
╚═══╩══════════════════════════════╝
```

**Entrada fracionária e determinante exato:**

```
Matriz
     1    2
  ┌──────────┐
1 │ 1/2   3  │
2 │  4    5  │
  └──────────┘
✓ Determinante = -19/2
```

**Saída fracionária exata (inversa da mesma matriz):**

```
Resultado — Inversa
      1       2
  ┌────────────────┐
1 │ -10/19   6/19  │
2 │  8/19   -1/19  │
  └────────────────┘
```

Conferindo à mão: o determinante é `-19/2`, então a inversa é `(-2/19) × [[5, -3], [-4, 1/2]]`, que dá exatamente a tabela acima. Um `np.linalg.inv()` devolveria `-0.5263157894736842` no lugar de `-10/19`.

<!-- COLE AQUI O PRINT DE UMA INVERSA COM FRAÇÕES -->

---

## O que o NumPy entrega aqui

Esta seção existe porque a resposta é contraintuitiva: **o NumPy deixa o código mais curto, mas não mais rápido.**

### Por que `dtype=object` é obrigatório

```python
np.full((linhas, colunas), Fr(0), dtype=object)
```

Sem `dtype=object`, o NumPy tenta encaixar os valores no tipo nativo mais próximo (`int64`, `float64`) e a fração vira aproximação decimal logo na criação da matriz — que é justamente o problema que o projeto existe para evitar.

Com `dtype=object`, o array deixa de ser um bloco contíguo de números de tamanho fixo e vira um **vetor de ponteiros para objetos Python**.

### O custo disso

O NumPy é rápido porque roda os laços em C sobre memória contígua. Com ponteiros para objetos, isso não acontece: cada multiplicação chama `Fraction.__mul__` no interpretador, célula por célula — exatamente como um laço Python faria.

Benchmark real, multiplicação de duas matrizes 60×60 de `Fraction`:

```
numpy dtype=object  : 0.1934s
listas puras        : 0.1979s
```

Empate técnico. **O responsável é o `dtype=object`:** ele desliga a vetorização, e o NumPy passa a ser só uma camada de indireção sobre o mesmo laço Python.

### O que sobra de ganho

Legibilidade em pontos específicos. A eliminação de uma linha inteira, por exemplo, cabe numa expressão:

```python
# NumPy — opera na fatia da linha de uma vez
M[lin, col:] -= (M[lin, col] / M[pivo, col]) * M[pivo, col:]

# Listas puras — precisa do laço explícito
fator = M[lin][col] / M[pivo][col]
for k in range(col, colunas):
    M[lin][k] -= fator * M[pivo][k]
```

| Operação | Listas puras | NumPy |
|----------|--------------|-------|
| Criar zerada | `[[Fr(0)] * c for _ in range(l)]` | `np.full((l, c), Fr(0), dtype=object)` |
| Acessar célula | `m[lin][col]` | `m[lin, col]` |
| Dimensões | `len(m)`, `len(m[0])` | `m.shape` |
| Somar | list comprehension dupla | `A + B` |
| Multiplicar | `sum(A[l][k] * B[k][c] ...)` | `A @ B` |
| Transpor | `[list(c) for c in zip(*m)]` | `m.T` |
| Trocar linhas | `m[i], m[j] = m[j], m[i]` | `m[[i, j]] = m[[j, i]]` |
| Colar identidade | `matriz[i][:] + identidade[i]` | `np.hstack([m, I])` |

### Conclusão honesta

Uma dependência que não entrega desempenho não se paga. Esta versão fica no repositório como **exercício comparativo** e como estudo da API do NumPy (fatiamento, `shape`, fancy indexing, `hstack`); a versão em listas puras é a recomendada para uso.

---

## Bibliotecas utilizadas

### `numpy` — Estrutura de dados

```python
import numpy as np
```

Usado exclusivamente como contêiner bidimensional. Os recursos aproveitados:

| Recurso | Onde aparece | O que faz |
|---------|--------------|-----------|
| `np.full()` | `Matriz.criar()` | Cria a matriz preenchida com um valor |
| `.shape` | tudo | Devolve `(linhas, colunas)` numa tupla só |
| Fatiamento 2D | `_escalonar()` | `M[lin, col:]` pega o pedaço da linha a partir de uma coluna |
| Fancy indexing | troca de linhas | `M[[i, j]] = M[[j, i]]` troca duas linhas sem variável temporária |
| `np.hstack()` | `inversa()` | Cola a identidade à direita da matriz |
| `np.where()` | `_tratar_zeros()` | Devolve as coordenadas de todas as células que batem numa condição |
| `@` | `multiplicacao()` | Produto matricial |
| `.T` | `transposta()` | Transposta |

**Sobre a troca de linhas por fancy indexing:**

```python
M[[pivo, alvo]] = M[[alvo, pivo]]
```

Isso funciona porque o fancy indexing do lado direito **cria uma cópia** antes de atribuir. Se fosse fatiamento normal (que devolve *view*, não cópia), a primeira linha seria sobrescrita antes de ser lida e a troca sairia errada.

### `fractions` — Aritmética exata

É a biblioteca mais importante do projeto:

```python
from fractions import Fraction as Fr
```

`Fraction` guarda o número como **numerador e denominador separados**, em vez de convertê-lo para um decimal aproximado.

**Comparação prática:**

```python
# Com float                      # Com Fraction
resultado = 1/3                  resultado = Fr(1, 3)
print(resultado * 3 == 1)        print(resultado * 3 == 1)
```

**Resultado com float:** `False`
**Resultado com Fraction:** `True`

O responsável pela diferença é a **representação binária do float**: `1/3` não tem representação exata em base 2, então o Python guarda `0.333333333333333314829...`. Multiplicando por 3 dá `0.9999999999999998`, que não é igual a 1. O `Fraction` guarda literalmente `1/3` e faz a multiplicação como fração: `(1×3)/3 = 3/3 = 1`.

Isso é decisivo aqui porque a eliminação de Gauss faz dezenas de divisões seguidas. Com float, um determinante que deveria dar `0` sai como `-4.44e-16`, e a checagem `if det == 0` para detectar matriz singular **nunca funcionaria**.

Outro detalhe: `Fraction` lê string direto, e é isso que permite aceitar os três formatos de entrada com uma linha só.

| O usuário digita | `Fr(texto)` guarda |
|------------------|--------------------|
| `3` | `3` |
| `3/4` | `3/4` |
| `0.5` | `1/2` |
| `-2/6` | `-1/3` (simplifica sozinho) |

### `os` — Interação com o sistema operacional

```python
os.system("cls" if os.name == "nt" else "clear")
```

`os.system()` executa um comando do terminal de dentro do Python. `os.name` verifica o sistema operacional: se for `'nt'` (Windows), executa `cls`; caso contrário (Linux/Mac), executa `clear`.

### `sys` — Escrita direta na saída padrão

Usado na animação de saída do programa:

```python
sys.stdout.write(f"{AMA}.{RE}")
sys.stdout.flush()
time.sleep(0.25)
```

`sys.stdout.write()` escreve texto na tela **sem pular linha** (diferente do `print`). O `flush()` força a exibição imediata — sem ele, o Python guardaria os pontos no buffer e mostraria todos de uma vez no final, quebrando a animação.

**Comparação prática:**

```python
# Com flush()                          # Sem flush()
for k in range(3):                     for k in range(3):
    sys.stdout.write(".")                  sys.stdout.write(".")
    sys.stdout.flush()                     time.sleep(0.25)
    time.sleep(0.25)
```

**Resultado com `flush()`:** aparece `.` → espera → `..` → espera → `...`
**Resultado sem `flush()`:** tela vazia por 0,75s → aparece `...` de uma vez

O responsável pela diferença é o **buffer de saída**: o Python acumula texto na memória e só escreve na tela quando o buffer enche ou encontra uma quebra de linha.

### `time` — Controle de pausas

```python
Tela.erro("Fator de crescimento não pode ser 0", 1.3)
```

`time.sleep()` pausa a execução. Serve para dar tempo do usuário ler as mensagens de erro antes do loop repetir a pergunta, e para controlar a velocidade da animação de saída.

### `math` — Produto da diagonal

```python
return sinal * math.prod(escalonada[i, i] for i in range(ordem))
```

`math.prod()` multiplica todos os elementos de um iterável, como o `sum()` faz com adição. É o passo final do determinante, depois que a matriz já está triangularizada.

### `typing` — Contrato do menu

```python
from typing import Callable, NamedTuple
```

`NamedTuple` cria a estrutura `Operacao`, que descreve cada linha do menu. `Callable` é a anotação de tipo para "isto é uma função".

---

## Cores e estilização no terminal

A interface colorida é feita com **sequências de escape ANSI**, códigos especiais interpretados pelo terminal para alterar cor e estilo do texto. As oito são criadas numa linha só:

```python
AZ, VERD, VERM, CI, AMA, ROSA, NEG, RE = (f"\033[{c}m" for c in (34, 32, 31, 36, 33, 35, 1, 0))
```

Uma expressão geradora produz as oito strings a partir dos números, e o desempacotamento múltiplo distribui cada uma em sua variável. O resultado é idêntico a escrever oito atribuições:

```python
AZ   = "\033[34m"   # Azul
VERD = "\033[32m"   # Verde
VERM = "\033[31m"   # Vermelho
CI   = "\033[36m"   # Ciano
AMA  = "\033[33m"   # Amarelo
ROSA = "\033[35m"   # Rosa/Magenta
NEG  = "\033[1m"    # Negrito
RE   = "\033[0m"    # Reset (volta ao normal)
```

Para usar, basta colocar a variável da cor antes do texto e o `RE` (reset) depois:

```python
print(f"{VERD}✓ Matriz criada{RE}")
```

**Resultado no terminal:** o texto aparece em verde, e o reset garante que o próximo texto volte à cor padrão. Sem o `RE`, **todo** o resto do terminal continuaria verde — inclusive depois do programa fechar.

As mensagens são padronizadas em três métodos da classe `Tela`, todos construídos sobre um método privado comum:

```python
@staticmethod
def _msg(simbolo: str, cor: str, texto: str, pausa: float = 0.0) -> None:
    print(f"{cor}{simbolo} {texto}{RE}")
    time.sleep(pausa)
```

| Método | Cor | Símbolo | Quando usar |
|--------|-----|---------|-------------|
| `Tela.sucesso()` | Verde | `✓` | Operação concluída |
| `Tela.erro()` | Vermelho | `✗` | Entrada inválida ou operação impossível |
| `Tela.aviso()` | Amarelo | `⚠` | Explica *por que* o erro aconteceu |

O padrão de uso é **erro + aviso juntos**: o erro diz o que houve, o aviso ensina a regra.

```python
Tela.erro(f"Matriz {matriz.shape[0]}x{matriz.shape[1]} não é quadrada")
Tela.aviso(f"{nome.capitalize()} só existe para matriz quadrada (n×n)")
```

**Resultado no terminal:**

```
✗ Erro: Matriz 2x3 não é quadrada
⚠ Determinante só existe para matriz quadrada (n×n)
```

<!-- COLE AQUI O PRINT DAS MENSAGENS DE ERRO/AVISO -->

> As cores ANSI funcionam nativamente no Linux, no Mac, no Windows Terminal e no PowerShell 7+. No `cmd.exe` antigo os códigos podem aparecer como texto cru.

---

## Desenho das tabelas com f-string

As molduras usam **caracteres box-drawing** do Unicode, que se conectam formando linhas contínuas:

```
Bordas simples:  ┌ ─ ┐ │ └ ┘
Bordas duplas:   ╔ ═ ╗ ║ ╚ ╝
Junções:         ╠ ╣ ╦ ╩
```

O alinhamento dentro da moldura é feito com **especificadores de formato dentro da f-string**:

```python
larg = 30
titulo = "CALCULADORA DE MATRIZES"

print(f"║{titulo:^{larg + 4}}║")
```

**Resultado no terminal:**

```
║     CALCULADORA DE MATRIZES      ║
```

Aqui tem uma f-string **aninhada**: as chaves internas `{larg + 4}` são resolvidas primeiro e viram o número `34`, então o Python lê `{titulo:^34}` — centralizar o título em 34 caracteres. É isso que permite mudar a largura da tabela inteira alterando uma única variável.

| Especificador | O que faz | Exemplo | Saída |
|---------------|-----------|---------|-------|
| `:^10` | Centraliza em 10 espaços | `f"{'oi':^10}"` | `    oi    ` |
| `:<10` | Alinha à esquerda | `f"{'oi':<10}"` | `oi        ` |
| `:>10` | Alinha à direita | `f"{'oi':>10}"` | `        oi` |

No método `Matriz.exibir()`, a largura da célula é **calculada em tempo de execução** a partir do maior número da matriz:

```python
textos = [[str(valor) for valor in linha] for linha in matriz]
largura = max(max(len(v) for linha in textos for v in linha) + 2, 3)
```

Repare que o `str()` é aplicado célula por célula. Um `print(matriz)` direto mostraria `Fraction(1, 2)` em cada posição, porque é assim que o NumPy formata objetos:

```
[[Fraction(1, 2) Fraction(3, 1)]
 [Fraction(4, 1) Fraction(5, 1)]]
```

Convertendo com `str()`, sai `1/2` e `3`. Por isso a exibição não usa o `print` nativo do array.

```
Largura = 3                   Largura = 8
    1  2  3                        1       2
  ┌─────────┐                 ┌────────────────┐
1 │ 1  2  3 │               1 │ -10/19   6/19  │
2 │ 4  5  6 │               2 │  8/19   -1/19  │
3 │ 7  8  9 │                 └────────────────┘
  └─────────┘
```

A margem à esquerda também é calculada, para o número da linha nunca desalinhar a moldura:

```python
margem = " " * (len(str(linhas)) + 1)
```

Uma matriz de 9 linhas usa margem de 2 caracteres; uma de 12 linhas usa 3, porque `"12"` ocupa dois dígitos.

---

## Arquitetura em classes

O código é dividido em **quatro classes e uma estrutura de dados**, cada uma com uma responsabilidade única.

| Classe | Responsabilidade | Não faz | Métodos principais |
|--------|------------------|---------|--------------------|
| `Tela` | Toda a parte visual: menu, molduras, mensagens, animações, leitura do teclado | Não sabe o que é uma matriz | `menu()`, `titulo()`, `sucesso()`, `erro()`, `aviso()`, `ler_numero()`, `escolher()` |
| `Matriz` | Criar, preencher e exibir matrizes | Não faz cálculo matemático | `criar()`, `preencher()`, `exibir()`, `_exponencial()`, `_tratar_zeros()` |
| `OperacoesMat` | Matemática pura: recebe matriz, devolve resultado | Não lê teclado | `soma()`, `multiplicacao()`, `determinante()`, `inversa()`, `rank()`, `_escalonar()` |
| `Operacao` | Estrutura de dados: descreve uma linha do menu | Não executa nada | `NamedTuple` com 7 campos |
| `Main` | Controle de fluxo e despacho do menu | Não implementa algoritmo | `executar()`, `_rodar()` |

A regra que amarra tudo: **só a `Tela` faz `print` e `input`**. As operações matemáticas chamam `Tela.erro()` para avisar e devolvem `None`, mas nunca escrevem direto.

A vantagem prática dessa separação: `OperacoesMat` pode ser importada e testada sozinha, sem terminal — foi exatamente assim que esta versão foi comparada célula a célula com a versão em listas puras.

### Por que quase tudo é `@staticmethod`

```python
class OperacoesMat:
    @staticmethod
    def transposta(matriz: np.ndarray) -> np.ndarray:
        return matriz.T
```

O `@staticmethod` significa que o método **não usa `self`** — ele não precisa de nenhum dado guardado no objeto. `transposta()` recebe a matriz como parâmetro, calcula e devolve; não existe "estado" para lembrar entre chamadas.

| Situação | O que usar |
|----------|-----------|
| O método precisa ler ou alterar algo guardado no objeto | `self` |
| O método só transforma o que recebeu por parâmetro | `@staticmethod` |

Neste projeto **nenhuma classe guarda estado**. Nem a `Main`: o laço principal é um `while True` que sai com `return`, sem precisar de uma flag `self.ativo`.

```python
if escolha == "0":
    Tela.sucesso("Até logo!")
    Tela.carregando("Saindo")
    return
```

---

## O dicionário de operações

Não existe `match/case` nem cadeia de `if` para rotear o menu. Cada operação é uma **tupla nomeada** que descreve o que ela precisa e o que devolve:

```python
class Operacao(NamedTuple):
    rotulo: str
    cor: str
    funcao: Callable
    matrizes: int = 1
    quadrada: bool = False
    escalar: bool = False
    aviso_singular: bool = False
```

E o menu inteiro é um dicionário dessas tuplas:

```python
OPERACOES = {
    "1": Operacao("Somar matrizes", VERD, OperacoesMat.soma, matrizes=2),
    "4": Operacao("Determinante", VERM, OperacoesMat.determinante,
                  quadrada=True, escalar=True, aviso_singular=True),
    "5": Operacao("Transposta", CI, OperacoesMat.transposta),
    ...
}
```

Repare que `OperacoesMat.soma` aparece **sem parênteses** — é a referência à função, não a chamada dela. Com parênteses, o Python tentaria executar a soma no momento de montar o menu.

O método `Main._rodar()` lê esses campos e monta o roteiro:

| Campo | O que ele decide |
|-------|------------------|
| `rotulo` | Texto do título e do resultado |
| `cor` | Cor do título |
| `funcao` | Qual conta é executada |
| `matrizes` | Quantas voltas o laço de coleta dá (1 ou 2) |
| `quadrada` | Se `criar()` pede a ordem ou pede linhas × colunas |
| `escalar` | Se a saída é linha de texto ou tabela |
| `aviso_singular` | Se checa determinante zero |

O coração disso é uma linha só:

```python
resultado = op.funcao(*matrizes)
```

O `*` desempacota a lista em argumentos posicionais:

| `op.matrizes` | `matrizes` | Vira a chamada |
|---|---|---|
| 1 | `[A]` | `OperacoesMat.determinante(A)` |
| 2 | `[A, B]` | `OperacoesMat.soma(A, B)` |

**Consequência prática:** para adicionar uma operação nova ao programa, escreve-se a função em `OperacoesMat` e uma linha em `OPERACOES`. O `_rodar()` não é tocado.

---

## As operações matemáticas

### Escalonamento — a base de tudo

`determinante()` e `rank()` compartilham o mesmo motor. `_escalonar()` devolve três coisas de uma vez:

```python
return M, sinal, pivo
```

| Valor | O que é | Quem usa |
|-------|---------|----------|
| `M` | A matriz já triangularizada | `determinante()` (produto da diagonal) |
| `sinal` | `1` ou `-1`, conforme o número de trocas de linha | `determinante()` |
| `pivo` | Quantidade de pivôs encontrados | `rank()` (é o próprio rank) |

A primeira linha do método é a mais importante:

```python
M = np.asarray(matriz, dtype=object).copy()
```

Isso **copia** a matriz antes de destruí-la. Sem o `.copy()`, o escalonamento alteraria a matriz original do usuário — e como arrays do NumPy costumam ser passados por referência através de *views*, esse bug seria silencioso.

A eliminação de uma linha inteira cabe numa expressão só:

```python
M[lin, col:] -= (M[lin, col] / M[pivo, col]) * M[pivo, col:]
```

O lado direito é avaliado **por completo** antes da subtração in-place — por isso `M[lin, col]` ainda vale o valor antigo quando o fator é calculado. Se fosse escrito em duas etapas com atribuição intermediária errada, a primeira coluna zeraria o fator e o resto da linha ficaria intacto.

### Determinante — eliminação de Gauss

O determinante é calculado escalonando a matriz até virar triangular superior e depois multiplicando a diagonal. Duas regras de álgebra linear sustentam isso:

1. Somar um múltiplo de uma linha a outra **não altera** o determinante.
2. Trocar duas linhas de lugar **inverte o sinal** do determinante.

Por isso existe a variável `sinal`:

```python
if alvo != pivo:
    M[[pivo, alvo]] = M[[alvo, pivo]]
    sinal = -sinal
```

A troca usa fancy indexing: `M[[alvo, pivo]]` monta um array novo com as duas linhas na ordem invertida, e a atribuição grava de volta. Como o lado direito é uma **cópia**, não uma view, nenhuma linha é sobrescrita antes de ser lida.

Quando o pivô é zero, o algoritmo procura uma linha abaixo com valor não nulo. A busca usa `next()` com um padrão de segurança:

```python
alvo = next((lin for lin in range(pivo, linhas) if M[lin, col] != 0), None)
if alvo is None:
    continue
```

O segundo argumento do `next()` é o valor devolvido quando o gerador se esgota. Sem ele, o Python levantaria `StopIteration`. Coluna toda zero significa que não há pivô ali: pula para a próxima coluna **sem** incrementar o contador de pivôs — e é exatamente isso que faz o rank sair certo em matrizes não quadradas.

No final, a checagem de singularidade não depende do produto:

```python
if rank < ordem:
    return Fr(0)
return sinal * math.prod(escalonada[i, i] for i in range(ordem))
```

### Inversa — Gauss-Jordan com matriz aumentada

A inversa é calculada colando a matriz identidade ao lado da matriz original:

```python
identidade = np.full((ordem, ordem), Fr(0), dtype=object)
for i in range(ordem):
    identidade[i, i] = Fr(1)
aumentada = np.hstack([matriz.copy(), identidade])
```

A identidade é montada à mão porque `np.eye()` devolve `float64` — misturar isso com `Fraction` reintroduziria o erro de arredondamento na primeira divisão.

**Resultado para uma matriz 2×2:**

```
Matriz original      Matriz aumentada [A | I]
┌       ┐            ┌               ┐
│ 1   2 │      →     │ 1   2 │ 1   0 │
│ 3   4 │            │ 3   4 │ 0   1 │
└       ┘            └               ┘
```

A normalização da linha do pivô e a eliminação nas outras linhas usam operações de linha inteira:

```python
aumentada[i] /= aumentada[i, i]
for k in range(ordem):
    if k != i and aumentada[k, i] != 0:
        aumentada[k] -= aumentada[k, i] * aumentada[i]
```

Nos dois casos o escalar do lado direito é lido **antes** da operação in-place começar. É o mesmo cuidado do escalonamento.

No final, corta-se a metade da esquerda com fatiamento:

```python
return aumentada[:, ordem:]
```

O `:` na posição das linhas significa "todas as linhas"; `ordem:` nas colunas significa "da coluna `ordem` em diante".

### Norma-1

```python
return max(sum((abs(v) for v in matriz[:, col]), Fr(0)) for col in range(matriz.shape[1]))
```

`matriz[:, col]` fatia a coluna inteira. Para cada uma, soma o módulo de todos os elementos; devolve a maior dessas somas. O `Fr(0)` como segundo argumento do `sum()` garante que o acumulador comece como fração, não como `int`.

---

## Modos de preenchimento

| Modo | Como funciona | Quando usar |
|------|---------------|-------------|
| Número único | Preenche todas as células com o mesmo valor | Matrizes constantes, teste rápido |
| Manual | Digita célula por célula, com a posição `[linha, coluna]` indicada | Matrizes específicas |
| Exponencial | Gera progressão geométrica a partir de valor inicial, fator e limite | Matrizes grandes de teste |

O modo exponencial ainda se subdivide em duas escolhas.

**Escopo do crescimento:**
- Mesma regra na matriz inteira — a sequência corre continuamente por todas as células.
- Uma regra por linha — cada linha recebe seus próprios parâmetros.

**O que fazer ao atingir o limite:**
- Preencher o resto com `0`.
- Reiniciar a sequência do começo em cada linha.

**Exemplo:** inicial `2`, fator `-2`, limite `100`, matriz 2×3.

**Resultado no terminal:**

```
     1    2    3
  ┌───────────────┐
1 │  2   -4    8  │
2 │ -16  32   -64 │
  └───────────────┘
```

A comparação com o limite usa **módulo**, não o valor com sinal:

```python
if abs(atual) > abs(limite):
```

Sem o `abs()`, um valor como `-256` passaria pela checagem `-256 > 100` (que é falsa) e continuaria sendo escrito, mesmo já tendo estourado o limite em magnitude.

### Tratamento de zeros

Se o modo "preencher com 0" deixar buracos na matriz, o programa detecta e oferece corrigir:

```python
zeros = list(zip(*np.where(matriz == 0)))
if not zeros:
    return matriz
```

`matriz == 0` faz a comparação **elemento a elemento** e devolve um array de booleanos — não um único `True`/`False`. `np.where()` transforma isso em duas tuplas de índices (linhas e colunas), e o `zip(*...)` recombina em pares `(lin, col)`. Assim o programa consegue perguntar célula por célula, citando a posição exata.

<!-- COLE AQUI O PRINT DO PREENCHIMENTO EXPONENCIAL -->

---

## Etapas e fluxo do programa

### 1. Menu principal

A tela é limpa e a tabela com as 10 opções é exibida. O usuário digita o número da operação, buscado direto no dicionário `OPERACOES`:

```python
if escolha not in OPERACOES:
    Tela.erro("Opção inválida", 1.0)
    continue
Main._rodar(OPERACOES[escolha])
```

### 2. Criação da matriz

O programa pede as dimensões. Se a operação exige matriz quadrada (determinante, traço, inversa), pede só a **ordem** e define linhas = colunas automaticamente:

```python
if quadrada:
    linhas = colunas = Tela.ler_inteiro("  Ordem (n de n×n)", minimo=1)
else:
    linhas = Tela.ler_inteiro("  Linhas", minimo=1)
    colunas = Tela.ler_inteiro("  Colunas", minimo=1)
```

Isso impede na origem que o usuário crie uma matriz inválida para aquela operação.

### 3. Preenchimento

O usuário escolhe entre os três modos descritos acima. A matriz é criada zerada com `np.full((linhas, colunas), Fr(0), dtype=object)` e depois populada.

<!-- COLE AQUI O PRINT DA ESCOLHA DE PREENCHIMENTO -->

### 4. Exibição e cálculo

A matriz é exibida com moldura, a operação é executada e o resultado aparece — matriz nova (soma, inversa, transposta) ou valor único (determinante, traço, norma, rank), conforme o campo `escalar`.

### 5. Retorno ao menu

O programa pausa esperando ENTER, para o usuário conseguir ler o resultado antes da tela ser limpa:

```python
input(f"\n{CI}Pressione ENTER para voltar ao menu\n>> {RE}")
```

Essa pausa fica **depois** da checagem da opção "0", então quem escolheu sair não precisa apertar ENTER para se despedir.

### Interrupções

O laço principal trata dois sinais que normalmente derrubariam o programa com stack trace:

```python
except KeyboardInterrupt:
    Tela.aviso("\nOperação cancelada", 1.0)
except EOFError:
    Tela.aviso("\nEntrada encerrada", 1.0)
    return
```

`Ctrl+C` no meio de uma operação cancela e volta ao menu; `Ctrl+D` encerra o programa com mensagem limpa.

---

## Validações de entrada

Existem dois leitores diferentes, porque existem dois tipos de dado.

| Leitor | Aceita | Onde é usado |
|--------|--------|--------------|
| `Tela.ler_inteiro()` | Só inteiro, com mínimo opcional | Linhas, colunas, ordem |
| `Tela.ler_numero()` | Inteiro, fração ou decimal | Valores das células |

Dimensão fracionária não existe — não faz sentido uma matriz `2.5 × 3`. Já o conteúdo da célula precisa aceitar tudo que o `Fraction` entende:

```python
@staticmethod
def ler_numero(msg: str) -> Fr:
    while True:
        texto = input(f"{AZ}{msg}{RE}\n>> ").strip()
        try:
            return Fr(texto)
        except ZeroDivisionError:
            Tela.erro("Denominador não pode ser 0")
        except ValueError:
            Tela.erro("Use inteiro (3), fração (3/4) ou decimal (0.5)")
```

São **dois `except` diferentes para dois erros diferentes**:

| O usuário digita | O que o Python levanta | Mensagem |
|------------------|------------------------|----------|
| `abc` | `ValueError` | "Use inteiro (3), fração (3/4) ou decimal (0.5)" |
| `3/0` | `ZeroDivisionError` | "Denominador não pode ser 0" |
| `-2` | Nada — é válido | Aceito |

**Resultado no terminal:**

```
[1,1]
>> ✗ Erro: Use inteiro (3), fração (3/4) ou decimal (0.5)
[1,1]
>> ✗ Erro: Denominador não pode ser 0
[1,1]
>> ✓ Preenchimento manual concluído
```

No `ler_inteiro()`, a lógica é a mesma, mas com uma defesa a mais:

```python
try:
    valor = int(input(f"{AZ}{msg}{RE}\n>> "))
except ValueError:
    Tela.erro("Digite um número inteiro")
    continue
if minimo is not None and valor < minimo:
    Tela.erro(f"Precisa ser ≥ {minimo}")
    continue
```

O `except` só pega erro de **tipo**. Um número negativo é um inteiro perfeitamente válido para o Python — quem precisa recusar é a regra do programa, no `if`.

A regra do preenchimento exponencial também é validada antes de rodar:

```
✗ Erro: Inicial 50 já passa do limite 10: a matriz sairia toda zerada
```

E as operações validam dimensões **antes** de calcular, retornando `None` em vez de quebrar:

```python
if A.shape[1] != B.shape[0]:
    Tela.erro(f"Multiplicação impossível: colunas de A({A.shape[1]}) ≠ linhas de B({B.shape[0]})")
    return None
```

Quem chamou verifica o retorno:

```python
resultado = op.funcao(*matrizes)
if resultado is None:
    return
```

**Por que `is None` importa ainda mais aqui:** com NumPy, escrever `resultado == None` faria a comparação **elemento a elemento** e devolveria um array de booleanos. Usar esse array num `if` levanta erro:

```
ValueError: The truth value of an array with more than one element is ambiguous
```

O `is` compara **identidade** de objeto, não valor — não dispara o operador sobrecarregado do NumPy e funciona igual para `ndarray`, `Fraction` e `int`. Pelo mesmo motivo, `if not resultado` também está fora de questão: além do erro de ambiguidade, um determinante `0` ou um rank `0` são resultados válidos que seriam escondidos.

---

## Testes

A camada matemática foi validada contra uma referência independente:

- **300 matrizes aleatórias** de ordem 1 a 4, valores de -4 a 4.
- Determinante conferido contra **expansão de Laplace** recursiva, implementada à parte só para o teste.
- Inversa conferida pela definição: `A × A⁻¹` tem que dar a identidade exata.
- Rank, norma e escalonamento comparados célula a célula contra a versão em listas puras.

```
300 testes aleatorios -> falhas: 0
```

O teste só é possível porque `OperacoesMat` não imprime nada nem lê teclado — dá para importar a classe e chamar os métodos direto, sem simular entrada de usuário.

---

## Problemas enfrentados

### 1. Erro de ponto flutuante no determinante

Na primeira versão, com `float`, matrizes singulares davam determinante `-4.44e-16` em vez de `0`. Como a checagem era `if det == 0`, o programa nunca detectava a matriz singular e a inversa quebrava com divisão por zero.

**Solução:** converter tudo para `fractions.Fraction` já na entrada do usuário e criar o array com `dtype=object`, único dtype que aceita objetos Python arbitrários.

### 2. NumPy convertendo as frações

Criar o array sem especificar o dtype fazia o NumPy escolher `float64` sozinho, e a fração virava decimal antes mesmo do primeiro cálculo.

**Solução:** `dtype=object` em toda criação de array — `np.full()`, a identidade da inversa e o `np.asarray()` do escalonamento.

### 3. `np.linalg` fora de questão

`np.linalg.det()` e `np.linalg.inv()` não aceitam `dtype=object` — trabalham só com tipos numéricos nativos, em ponto flutuante.

**Solução:** implementar Gauss e Gauss-Jordan à mão. O NumPy ficou restrito ao papel de contêiner.

### 4. Pivô zero na eliminação de Gauss

Quando o elemento da diagonal era `0`, a divisão pelo pivô gerava `ZeroDivisionError`.

**Solução:** antes de dividir, procurar uma linha abaixo com valor não nulo e trocar via fancy indexing. Se não existir nenhuma, a coluna inteira é zero: pula para a próxima coluna sem contar pivô.

### 5. O sinal invertido

Depois de implementar a troca de linhas, os determinantes começaram a sair com sinal errado em algumas matrizes.

**Causa:** cada troca de linhas inverte o sinal do determinante — regra de álgebra linear que o código estava ignorando.

**Solução:** a variável `sinal`, invertida a cada troca e aplicada no produto final.

### 6. Matriz alterada in-place

`determinante()` escalonava a matriz **recebida**, destruindo a original. Com NumPy o risco é maior que com listas, porque fatiamento devolve *view*, não cópia — alterar a view altera o array de origem.

**Solução:** `.copy()` explícito na primeira linha do `_escalonar()`.

### 7. Alinhamento da moldura com números de tamanhos diferentes

Com largura de célula fixa, uma matriz contendo `1` e `-15/4` ficava com a moldura torta. E o `print` nativo do array mostrava `Fraction(1, 2)` em vez de `1/2`.

**Solução:** converter cada célula com `str()`, medir o maior texto e usar esse número na f-string aninhada `{v:^{largura}}`.

### 8. Índice 1-based na entrada, 0-based na exibição

O prompt pedia o valor de `[2,3]`, mas a tabela rotulava aquela mesma célula como linha `1`, coluna `2`.

**Solução:** padronizar tudo em 1-based na exibição, com `range(1, colunas + 1)` e `enumerate(textos, start=1)`. O cálculo da margem passou de `len(str(linhas - 1))` para `len(str(linhas))`, senão uma matriz de 10 linhas desalinharia na última.

### 9. Limite exponencial comparado com sinal

Com fator negativo, a sequência `2, -4, 8, -16, 32, -64, 128` passava do limite `100` sem ser barrada, porque `-64 > 100` é falso.

**Solução:** comparar módulos — `abs(atual) > abs(limite)`.

### 10. Aviso de matriz singular preso a uma string

O aviso de determinante zero era disparado por `if op.rotulo == "Determinante"`. Renomear o rótulo no menu apagaria o aviso silenciosamente.

**Solução:** o campo `aviso_singular: bool` na `Operacao`.

### 11. NumPy sem ganho de desempenho

O objetivo original de portar para NumPy era ganhar velocidade. O benchmark mostrou empate técnico com listas puras.

**Causa:** `dtype=object` desliga a vetorização em C. O array vira um vetor de ponteiros e cada operação chama `Fraction.__mul__` no interpretador.

---

## Autor

**João Pedro Iop Beltrame** — Ciência da Computação, PUCPR

[![GitHub](https://img.shields.io/badge/GitHub-JoaoIopBeltrame-181717?style=flat-square&logo=github)](https://github.com/JoaoIopBeltrame)

Projeto desenvolvido para estudo de **álgebra linear**, **estruturas de dados** e **programação orientada a objetos**.
