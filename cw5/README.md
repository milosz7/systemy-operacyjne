Aby wyświetlić dostępne polecenia Makefile należy wpisać "make"
W celu samodzielnego uruchomienia programu należy skorzystać z komendy:

./cw5a.x *nazwa pliku wejściowego* *nazwa pliku wyjściowego* *ścieżka do fifo*

Ze względu na to jak zaimplementowane są handlery sygnałów aby program działał
poprawnie należy podać jako ścieżkę "./pipe.FIFO" - w innym wypadku funkcja atexit
oraz signal nie będzie działała poprawnie.

https://stackoverflow.com/questions/6970224/providing-passing-argument-to-signal-handler

Ćwiczenie 5b polega na stworzeniu potoku nazwanego, a następnie współbieżnym uruchomieniu programów do czytania oraz zapisywania. Można to manualnie, lecz komenda "make run-cw5b"
wykonuje cały proces za nas.