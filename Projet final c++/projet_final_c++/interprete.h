#ifndef INTERPRETE_H
#define INTERPRETE_H

#include "pile.h"
#include <iostream>
#include <QtWidgets>

class interprete : public QWidget
{
    Q_OBJECT
public:
    interprete();
    interprete(int, char**);
    void interpretation(const string &);
    //char * getArgv(){return val_argv;}
    void pop();
    void popstr();
    void copy();
    void copystr();
    void print();
    void printstr();
    void display();
    void displaystr();
    void count();
    void countstr();
    void swap();
    void swapstr();
    void sinus();
    void cosinus();
    void tangente();
    void racine();
    void tronque();
    void line();
    void color();
    void drawstr();
    void exit();
    void addition();
    void soustraction();
    void multiplication();
    void division();
    void affichageResult(double);
    void affichageResult(string);

private:
    Pile<double> pDouble;
    Pile<string> pString;
    QTextEdit* affichage;
    QLineEdit* msg;
    int val_argc;
    const char * val_argv;
    map<string,void(interprete::*) ()> bdd;
private slots:
    void affichageMsg();
};

#endif // INTERPRETE_H
