[grammar](https://github.com/cschmidt74/CCLab/blob/master/p1/grammar.md)

- Vagrant installieren
    - [LINK] (https://www.vagrantup.com/docs/installation/)  
    - [mehr Infos] (https://www.vagrantup.com/docs/getting-started/)

- Vagrant starten
    - Im Terminal oder in der Konsole zum Ordner mit 'Vagrantfile' navigieren
    - 'vagrant up'  (kann sehr lange dauern)
    - 'vagrant ssh'
        - Sollte es hier Probleme geben: 'vagrant destroy' und Vagrant nochmal starten. Bei mir hat das funktioniert  

- Projekt Kompilieren & Ausführen über vagrant@archlinux:
    - 'cd /vagrant/' (hier befindet sich der geteilte Ordner, in der sich 'Vagrantfile' befindet)
    - im 'GoLangParser'-Ordner befindet sich eine makefile, die man einfach mit 'make' ausführen kann.
    - es wird eine ausführbare Datei 'exec' erstellt. einfach mit './exec' starten
