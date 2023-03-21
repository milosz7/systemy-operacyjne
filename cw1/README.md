Aby dowiedzieć się jak korzystać z makefile należy wywołać komendę "make", która
wylistuje dostępne polecenia.

Procesem adoptującym osierocone procesy w ćwiczeniu 1c jest proces o nazwie: systemd

Przykładowe drzewo stworzone na podstawie outputu dla ćwiczenia 1d:

PID: 9879 PPID: 6021 PGID: 9879
PID: 9880 PPID: 9879 PGID: 9879
PID: 9881 PPID: 9879 PGID: 9879
PID: 9882 PPID: 9879 PGID: 9879
PID: 9884 PPID: 9880 PGID: 9879
PID: 9885 PPID: 9880 PGID: 9879
PID: 9886 PPID: 9881 PGID: 9879
PID: 9887 PPID: 9884 PGID: 9879

(9879,6021,9879)
|
|
|---(9880,9879,9879)
|                 |---(9884,9880,9879)
|                 |                  |---(9887,9884,9879)
|                 |
|                 |---(9885,9880,9879)
|
|---(9881,9879,9879)
|                 |
|                 |---(9886,9881,9879)
|
|---(9882,9879,9879)

Przy n-krotnym wywołaniu funkcji fork() otrzymamy 2^(n-1) procesów potomnych. Np dla i = 3: przy pierwszym wejściu do pętli proces macierzysty dzieli się na 2 potomne w których i = 0. (Mamy 2 procesy 1 macierzysty) Następnie każdy z nich dzieli się na 2 kolejne procesy, w których i = 1. (Mamy 4 procesy, 1 macierzysty). Następnie i = 2, jest to ostatnia iteracja, każdy z uprzednio powstałych 4 programów znowu dzieli się na 2. (Mamy 8 procesów, 1 macierzysty). W wyniku takiego działania otrzymujemy więc 2^(n-1) procesów potomnych, gdzie u nas n = 3.
