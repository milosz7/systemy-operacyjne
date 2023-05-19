#Kompilacja

Aby wyświetlić możliwe dostępne komendy do kompilacji i uruchamiania programów
należy skorzystać z polecenia "make". w celu samodzielnego uruchomienia programów
z wiersza poleceń należy kolejno podać następujące argumenty:

#Uruchamianie programów

./*nazwa programu* *nazwa programu konsumenta* *nazwa programu producenta* *nazwa pliku wejściowego* *nazwa pliku wyjściowego*

#Pseudokod do ćwiczenia uogólniający synchronizację wielu producentów i konsumentów

Proces główny:
    - inicjujemy pamięć dzieloną, która zawiera:
        - bufor,
        - indeks wstawiania,
        - indeks wyjmowania,
        - liczbę producentów,
        - zmienną wskazującą na liczbę producentów którzy zakończyli pracę
        - PGID procesów potomnych
    - inicjujemy semafory dla producentów i konsumentów
    - uruchamiamy w pętli procesy producentów i konsumentów
    - zapisujemy do zmiennej PGID procesów potomnych
    - uruchamiamy procesy producentów i konsumentów
Konsument:
    Towar towarKons;
    while(1)
        P(KONS)
        towarKons = bufor[wyjmij]
        wyjmij = (wyjmij + 1) % N
        V(PROD)
    - po zakończeniu konsumpcji konsument sprawdza czy liczba procesów producentów,
      która zakończyła działanie równa się liczbie producentów i jeżeli tak, to
      wysyła sygnał kill do grupy procesów o PGID zawartym w pamięci dzielonej
Producent:
     towarProd;
    while (1)
        P(PROD)
        bufor[wstaw] = towarProd
        wstaw = (wstaw + 1) % N
        V(KONS)
    -dodatkowo gdy producent zakończy swoje działanie inkrementuje wartość 
     liczby producentów, którzy zakończyli działanie

Pozwoliłem użyć sobie pseudokodu konsumenta i producenta z treści polecenia, ponieważ
będzie on analogiczny niezależnie od ilości procesów.
