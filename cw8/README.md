Aby wyświetlić dostępne polecenia należy skorzystać z komendy "make"
Aby manualnie uruchomić programy należy (w zależności od sposobu kompilacji biblioteki)
wpisać:
./clients.x | ./servers.x aby uruchomić klienta | serwer dla opcji kompilacji cw8s

./clientd1.x | ./serverd1.x aby uruchomić klienta | serwer dla opcji kompilacji cw8d1

export LD_LIBRARY_PATH=./lib:; \ ./clientd2.x | ./serverd2.x aby uruchomić klienta | serwer dla opcji kompilacji cw8d2

Aby wyłączyć serwer należy wysłać mu sygnał SIGINT, gdyż chodzi on w nieskończonej pętli.