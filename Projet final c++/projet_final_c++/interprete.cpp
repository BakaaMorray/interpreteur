#include "interprete.h"
#include <fstream>
#include <math.h>
#include <sstream>

const double Pi = 3.14159265358979323846;

interprete::interprete(int argc, char * argv[]): val_argc(argc)
{
    affichage = new QTextEdit(this);
    affichage->setReadOnly(true);
    msg = new QLineEdit(this);

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(affichage);
    layout->addWidget(msg);
    setLayout(layout);

    QObject::connect(msg,SIGNAL(editingFinished()),this,SLOT(affichageMsg()));
    pDouble.empiler((double)height());
    pDouble.empiler((double)width());

    bdd["pop"] = &interprete::pop;
    bdd["popstr"] = &interprete::popstr;
    //bdd["pushstr"] = &interprete::pushstr;
    //bdd["push"] = &interprete::push;
    bdd["+"] = &interprete::addition;
    bdd["-"] = &interprete::soustraction;
    bdd["*"] = &interprete::multiplication;
    bdd["/"] = &interprete::division;
    bdd["copy"] = &interprete::copy;
    bdd["copystr"] = &interprete::copystr;
    bdd["print"] = &interprete::print;
    bdd["printstr"] = &interprete::printstr;
    bdd["display"] = &interprete::display;
    bdd["displaystr"] = &interprete::displaystr;
    bdd["count"] = &interprete::count;
    bdd["countstr"] = &interprete::countstr;
    bdd["swap"] = &interprete::swap;
    bdd["swapstr"] = &interprete::swapstr;
    bdd["sin"] = &interprete::sinus;
    bdd["cos"] = &interprete::cosinus;
    bdd["tan"] = &interprete::tangente;
    bdd["sqrt"] = &interprete::racine;
    bdd["trunc"] = &interprete::tronque;
    bdd["line"] = &interprete::line;
    bdd["color"] = &interprete::color;
    bdd["drawstr"] = &interprete::drawstr;
    bdd["exit"] = &interprete::exit;

    if(val_argc == 2)
    {
        val_argv = argv[1];
        pString.empiler(val_argv);
        interpretation(val_argv);
    }
    else
        pString.empiler(argv[0]);
}

void interprete::pop()
{
    pDouble.depiler();
}

void interprete::popstr()
{
    pString.depiler();
}

/* void interprete::push()
{

}

void interprete::pushstr()
{

} */

void interprete::copy()
{
     int tmp_int = (int)(pDouble.depiler());
     pDouble.empiler(pDouble[tmp_int]);
}

void interprete::copystr()
{
    int tmp_int = (int)(pDouble.depiler());
    pString.empiler(pString[tmp_int]);
}

void interprete::addition()
{

}

void interprete::soustraction()
{

}

void interprete::multiplication()
{

}

void interprete::division()
{

}

void interprete::print()
{
    affichageResult(pDouble.depiler());
}

void interprete::printstr()
{
    affichageResult(pString.depiler());
}

void interprete::display()
{

    for(unsigned int i = 0u; i<pDouble.compter(); i++)
    {
        affichageResult(pDouble[i]);
    }
}
void interprete::displaystr()
{
    for(unsigned int i = 0u; i<pString.compter(); i++)
    {
        affichageResult(pString[i]);
    }
}
void interprete::count()
{
    affichageResult(pDouble.compter());
}
void interprete::countstr()
{
     affichageResult(pString.compter());
}
void interprete::swap()
{
    double tmp_sommet = pDouble.depiler();
    double tmp_2eme = pDouble.depiler();

    pDouble.empiler(tmp_2eme);
    pDouble.empiler(tmp_sommet);
}
void interprete::swapstr()
{

    string tmp_sommet = pString.depiler();
    string tmp_2eme = pString.depiler();

    pString.empiler(tmp_2eme);
    pString.empiler(tmp_sommet);
}
void interprete::sinus()
{
     pDouble.empiler(sin((pDouble.depiler()*Pi)/180));
}

void interprete::cosinus()
{
     pDouble.empiler(cos(pDouble.depiler()*Pi)/180);
}

void interprete::tangente()
{
    pDouble.empiler(tan(pDouble.depiler()*Pi)/180);
}

void interprete::racine()
{
    pDouble.empiler(sqrt(pDouble.depiler()));
}

void interprete::tronque()
{
    pDouble.empiler(trunc(pDouble.depiler()));
}

void interprete::line()
{
    double x1 = pDouble.depiler();
    double y1 = pDouble.depiler();
    double x2 = pDouble.depiler();
    double y2 = pDouble.depiler();

    //QPainter
}

void interprete::color()
{

}

void interprete::drawstr()
{

}

void interprete::exit()
{

}

void interprete::affichageResult(double a)
{
    string tmp;
    ostringstream oss;
    oss << a;
    tmp = oss.str();
    QString tmp2 = tmp.c_str();
    affichage->append(tmp2);
}

void interprete::affichageResult(string a)
{
    QString tmp = a.c_str();
    affichage->append(tmp);
}

void interprete::affichageMsg()
{
    affichage->append(msg->text());
    msg->clear();
    msg->clearFocus();
}

void interprete::interpretation(const string & a)
{
    ifstream fin(a.c_str());
    bool test = false;
    bool testInt = true;
    char temp;
    if(!fin)
    {
        //return "probleme d'ouverture du script";
        affichage->append("<em>Pb ouverture</em>");
    }
    else
    {
        do
        {
            string tempBis;
            getline(fin,tempBis);
            string * stockage = new string();
            string * stockageInt = new string();
            for(int i=0;i<=tempBis.length();i++)
            {

                temp = tempBis[i];
                if(isdigit(temp) == 1)
                {
                   *stockageInt = (*stockageInt) + temp;
                }
                if(temp == ' ' || temp == '\0')
                {
                    map<string, void(interprete::*)()>::iterator it;
                    for(it = bdd.begin(); it!= bdd.end();++it)
                    {
                        if(it->first == *stockage)
                        {

                            (this->*it->second)(); // PUTIN DE MERDE YOLO !!!
                            testInt = false;
                        }
                    }
                    if(testInt)
                    {
                        QString bite = stockageInt->c_str();
                        pDouble.empiler(bite.toDouble());
                    }
                    test = true;
                }

                    *stockage = (*stockage) + temp;

                if(test)
                {
                    //affichage->append(*stockage);


                    *stockage = "";
                    test = false;

                }
            }
            delete stockage;
        }while(!fin.eof());
    }
}
