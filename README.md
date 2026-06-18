"Viešbučio kambarių valdymo sistema"
1. Projekto tikslas: Programa skirta viešbučio kambarių ir klientų duomenims valdyti. Sistema leidžia sekti kambarių būsenas, registruoti klientus ir atlikti pagrindines operacijas.
2. Pasirinktos temos aprašymas: Viešbučio kambariai. Kiekvienas kambarys turi unikalų ID, kambario numerį, tipą (standart / lux / deluxe), kainą per parą ir būseną (laisvas / užimtas). Klientas registruojamas atvykus ir susiejamas su kambario ID.
3. Programos funkcionalumo aprašymas (CRUD): Create: naujo kambario pridėjimas (7 punktas), kliento registracija rezervuojant kambarį (3 punktas)
Read: visų kambarių peržiūra (1 punktas), laisvų kambarių peržiūra (2 punktas), kliento duomenų peržiūra (6 punktas)
Update: kliento perkėlimas į kitą kambarį – keičiamas kambario ID klientui ir kambarių būsenos (5 punktas)
Delete: kliento ištrynimas išvykus (4 punktas), kambario šalinimas iš sistemos (8 punktas).
4. Papildomos funkcijos:Paieška pagal kambario tipą (9 punktas)
Kambarių rikiavimas pagal kainą (10 punktas)
5. Naudojamų failų aprašymas: hotel.cpp – pagrindinis programos kodas
kambariai.txt – kambarių duomenys (laukai: id, numeris, tipas, kaina, statusas, kliento_id), ne mažiau kaip 16 įrašų, skyrikliai – tarpai
klientai.txt – klientų duomenys (laukai: id, vardas, pavardė, kambario_id), pildomas automatiškai rezervuojant
6. Programos paleidimo instrukcija: Failai kambariai.txt ir klientai.txt turi būti tame pačiame aplanke kaip ir programa.Tada reikia, kad kodas būtų sėkmingai kompiliuotas, ir tuomet tikimasi, kad programa bus sėkmingai paleista.
7. Papildomų funkcijų aprašymas: Paieška pagal tipą (9 punktas) – vartotojas įveda kambario tipą (standart / lux / deluxe) ir programa parodo visus tam tipui priklausančius kambarius su jų duomenimis ir būsena.
Rikiavimas pagal kainą (10 punktas) – programa surikiuoja visus kambarius didėjančia tvarka pagal kainą, naudojant burbulo rikiavimo algoritmą, ir parodo surikiuotą sąrašą.
