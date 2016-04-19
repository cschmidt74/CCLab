# CCLab
## go_programs
    - dir
    - Sammlung diverser GO-Test-Programm
    - Syntax der Benennung:
        - p:=positiver Fall (Diese Programme sollten vom compiler zugelassen werden)
        - n:=negativer Fall (Diese Programme sollten zu einem Abbruch mit Fehlermeldung führen)
        - Zahlen aufsteigend nach Komplexität sortiert.
        - Bsp: p101 (Das minimalst-mögliche GO-Programm, ohne Fehlermeldungen)
        - Bsp: n403 (Ein sehr komplexes und fehlerhaftes GO-Programm)


## Commit Syntax
    Beim Commit wird ein Beschreibungstext verlangt. Hier die Syntax:
    - Title der Veränderung
    - Beschreibungstext (Optional)
        - M:=Modified (Präfix für eine Liste veränderter Dateien)
        - A:=Added    (... für hinzugefügte Dateien)
        - R:=Removed  (... für entfernte/gelöschte Dateien)
    - Bsp: 
        GO-Testfälle hinzugefügt
        A: p103, p104, n103
        M: p102 (kleiner error behoben)
        R: pfail
