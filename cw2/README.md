Aby wyświetlić listę dostępnych poleceń należy wywołać komendę "make".

Przy n-krotnym wywołaniu funkcji fork i exec jak w ćwiczeniu 2
powstanie jeden proces macierzysty i n-procesów potomnych, łącznie
n+1 procesów. Dzieje się tak ponieważ dla i = n przy pierwszym wejściu do pętli zostaje wywołana funkcja fork() i w procesie potomnym, gdzie zwraca ona PID = 0 zostaje wywołana funkcja execlp(), przez co kod wykonywany przez kopię procesu powstałego w wyniku wywołania funkcji fork() zostaje zastąpiony przez kod programu, którego ścieżka została podana jako argument dla funkcji execlp(). Schemat ten powtarza się do momentu w którym i = n więc powstanie n procesów potomnych. Wraz z procesem macierzystym daje nam to łącznie n+1 procesów.
