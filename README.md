# :books: Bookstore Management System
## :label: Tema: 
 Scopul aplicatiei este de a intretine managementul unei librarii.
Aceasta functioneaza in spatele unui meniu interactiv in consola C++,
construita pe baza principiilor OOP.
#### :bookmark: Asadar, au fost implementate 5 clase:
1. MyString
    - Functioneaza similar unei clase string. 
    - Are doua proprietati: data (alocare dinamica unui vector tip char) si size.
    - Permite citirea, afisarea, copierea, asignarea valorilor char.
    - Foloseste alocare dinamica.
    - Se conecteaza la celelalte obiecte prin compunere.
    - Constructori: cu parametru si fara parametru.
    - Un destructor netrivial.
2. Book
    - Are proprietatile unei carti: nume, autor, pret.
    - Permite afisarea, asignarea, copierea si crearea, schimbarea valorilor de tip Book.
    - Constructori: cu parametru si fara parametru.
    - 3 setteri si 3 getteri.
3. Customer
    - Are caracteristicile unui client: nume, ID, numar de comenzi, tip (efficient/traditional).
    - Tipul clientului va fi setat automat de o metoda in functie de numarul de comenzi efectuate.
    - Permite afisarea, asignarea, copierea si crearea, schimbarea valorilor de tip Book.
    - Constructori: cu parametru si fara parametru.
    - 1 setter si un getter.
4. Employee
    - Are proprietatile: nume, ID, salariu, rol.
    - Permite afisarea, asignarea, copierea si crearea, schimbarea valorilor de tip Book.
    - Constructori: cu parametru si fara parametru.
    - 4 setteri si 4 getteri.
5. Bookstore
    - Are proprietatile: nume, adresa, un vector de obiecte tip Book, un vector de obiecte tip Employee, un vector de obiecte tip Customer.
    - Foloseste alocare dinamica pentru crearea vectorilor de obiecte.
    - Permite afisarea, asignarea, copierea si crearea, schimbarea valorilor de tip Bookstore.
    - Include 4 metode de "logica de bussiness" si se conecteaza la celelalte obiecte prin compunere.
    - Constructori: cu parametru si fara parametru.
    - Un destructor netrivial.
    - 5 setteri.

#### :chart_with_upwards_trend: Functionalitati:
1. Are propria clasa string - `MyString`, care poate citi si afisa un sir de caractere. La fel, e posibila asignarea, copierea sirului. Clasa functioneaza prin alocare dinamica.
2. Capacitatea de a citi, retine si afisa o lista de carti, angajati si clienti prin alocare dinamica, pastrand caracteristicile acestora. 
3. Returneaza salariul mediu al angajatilor printr-o valoare de tip double. Vezi `double mediumSalary()`.
4. Returneaza pretul mediu pentru produsele din librarie `double mediumPrice()`.
5. Returneaza numarul de clienti care au mai mult de 2 comenzi `int efficientCustomers()`.
6. Returneaza numele angajatului cu cel mai mare salariu `const MyString maxSalary()`.
7. Folosind setteri, exista optiunea de a seta valori default pentru a testa programul si metodele, dar aceleasi valori pot fi introduse de la tastatura.
8. La fel a fost supraincarcat `operator<<` pentru afisarea fiecarei clase.
9. In main exista un meniu interactiv unde poti alege metoda de completare a datelor si testa functionalitatile.


