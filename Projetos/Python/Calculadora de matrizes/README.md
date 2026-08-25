# Calculadora de matrizes

Três versões do mesmo problema, cada uma com uma abordagem diferente.

## Versões

| Pasta | Abordagem | Status |
|---|---|---|
| [`loops/`](./loops) | Lógica manual com `for`| pronta |
| [`numpy/`](./numpy) | Usando NumPy (`np.linalg.det()` etc) | pronta |
| [`tkinter/`](./tkinter) | Interface gráfica (Tk) sobre uma das lógicas acima | planejada |

## Por que três versões

A ideia não é ter três calculadoras diferentes, é mostrar o mesmo problema resolvido em três níveis: na mão (loops), com ferramenta pronta (numpy), e com interface (tkinter). Cada pasta tem seu próprio README explicando as decisões técnicas específicas daquela versão.

## Operações cobertas

- Soma e subtração de matrizes
- Multiplicação de matrizes
- Determinante (Sarrus para 3x3, Chió para NxN)

## Autor

João Iop Beltrame
