### Spreadsheet

**Jednoduchý tabulkový editor**

Tabulka (Spreadsheet.h) je reprezentovana jako mapa s ukazately na bunky (Cell.h).

Kazda bunka ma svuj druh (cislo(Number.h), retezec(String.h), funkce(Fuction.h), ukazatel na jinou bunku(Pointer.h) nebo vyraz(Expression.h)). Kdyz pridavame do tabulky novy prikaz pro bunku, napr. prikazem v terminalu "A3 = 99 + 1", pak retezec "A3" je pozice v tabulce ( index v mape ) a "99 + 1" je prikaz bunky. Na zaklade druhu prikazu program vytvory vhodny druh bunky.
