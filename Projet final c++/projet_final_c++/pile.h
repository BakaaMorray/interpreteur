#ifndef PILE_H
#define PILE_H

#include <iostream>
using namespace std;
template<typename Type>class Pile
{
public:
    Pile(unsigned int taille=128);
    Pile(const Pile&);
    void empiler(const Type&);
    Type depiler();
    inline unsigned int compter() const {return sommet;}
    void afficher() const;
    inline ~Pile(){delete [] pile;}
    Type operator[](int);
    unsigned int getTaillePile(){return taillePile;}

private:
    unsigned int taillePile;
    Type *pile;
    unsigned int sommet;

    void realloc();
};

template<typename Type>Pile<Type>::Pile(unsigned taille):taillePile(taille),pile(NULL),sommet(0)
{
    pile = new Type[taillePile];
}

template<typename Type>Pile<Type>::Pile(const Pile& src):taillePile(src.taillePile), pile(NULL), sommet(src.sommet)
{
    pile = new Type[taillePile];

    for(unsigned int i=0; i<src.sommet; i++)
        pile[i]=src.pile[i];
}

template<typename Type> void Pile<Type>::empiler(const Type& carac)
{
    if (sommet<taillePile)
        pile[sommet++]=carac;
    else
        cerr << "Pile pleine" << endl;
}

template<typename Type> Type Pile<Type>::depiler()
{
    if (sommet>0)
        return pile[--sommet];
    else
    {
        throw;
    }
}

template<typename Type>void Pile<Type>::afficher() const
{
    for(unsigned int i=sommet; i>0; i--)
        cout << "|" << pile[i-1] << "|" << endl;

    cout << "---";
}

template<typename Type>void Pile<Type>::realloc()
{
    Type * pileTmp=new Type[2*taillePile];

    for(unsigned int i=0; i<taillePile; i++)
        pileTmp[i]=pile[i];

    delete [] pile;

    pile=pileTmp;
}

template<typename Type>Type Pile<Type>::operator[](int a)
{
    return pile[a];
}

#endif // PILE_H
