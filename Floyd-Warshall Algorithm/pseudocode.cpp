

D[liczba_wierzcholkow][liczba_wierzcholkow] <-- macierz sasiedztwa gdzie polaczenie miedzy wierzcholkami ma wartosc > 0
                                                , jest to jego waga, brak polaczenia to +in
P[liczba_wierzcholkow][liczba_wierzcholkow] <-- macierz ścieżek
floyd_warshall(D, P){
    for i <-- 1 to liczba_wierzcholkow
        for j <-- 1 to liczba_wierzcholkow
            P[j][i] = j

    for i <-- 1 to liczba_wierzcholkow + 1
        for j <-- 1 to liczba_wierzcholkow + 1
            for k <-- 1 to liczba_wierzcholkow + 1
                if D[j][k] > D[j][i] + D[i][k]
                    then D[j][k] = D[j][i] + D[i][k]
                         P[j][k] = P[i][k]

    //odtworzenie sciezki
    path[o] = k
    i = 0
    while j != k do:
        ++i;
        k = P[j][k]
        path[i] = k

    //wypisanie sciezki
    while i > -1 do:
        print path[i++]
}

