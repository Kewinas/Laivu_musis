#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class Laivas
{
  private:
        char direction;
        int ilgis;
        vector<int> LaivasEile;
        vector<int> LaivasStulpas;
        int hits;
        string name;
    public:
        Laivas(char d, int lgth, vector<int> r, vector<int> c, int hit, string nme)
        {
            direction=d;
            ilgis=lgth;
            LaivasEile=r;
            LaivasStulpas=c;
            hits=hit;
            name=nme;
        }
        void setHit()
        {
            hits++;
        }
        int checkSunk(int LaivasDydis)
        {
            if(hits>=LaivasDydis)
            {
                return 9;
            }
            else
            {
                return 0;
            }
        }
        void LaivasKoordinates()
        {
            cout << "Koordinates, laivo: " << name << endl << endl;
            for(int i=0; i<ilgis; i++)
            {
                cout << "Vieta [" << LaivasEile[i] << "][" << LaivasStulpas[i] << "]" << endl;
            }
        cout << endl;
        }

        string getLaivas(int r, int c)
        {
            for(int i=0; i<ilgis; i++)
            {
                if((LaivasEile[i]==r) && (LaivasStulpas[i]==c))
                {
                    return name;
                }
            }
            return "";
         }
};

enum LaivasDydis { PovandeninisLaivas = 2, Minininkas = 3, SarvuotasLaivas = 4, Lektuvnesis = 5 };
void inicializavimas(int grid[][10]);
void spausdintiLenta(int grid[][10]);
void spausdintZaidimoLenta(int grid[][10]);
int EilStulpReset(int stulp, int &eile, int LaivasDydis, char d);
char Kryptis(int d);
int Tarpai(int grid[][10], int c, int r, int s, char d);
void KeistiVieta(int grid[][10], int stulp, int eile, int LaivasDydis, char direction);
bool statytiLaiva(int grid[][10], int LaivasDydis, int name, vector<Laivas> &LaivuSarasas);
void KeistiLaivoInfo(int grid[][10], int c, int r, int LaivasDydis, char d, vector<Laivas> &LaivuSarasas, int name);
int Zaidimas(int grid[][10], vector<Laivas> &LaivuSarasas);
int gautiTarpa(int grid[][10], int eile, int stulp);

int main()
{
    int grid[10][10];
    vector<Laivas> LaivuSarasas;
    char zaisti;
    inicializavimas(grid);
    statytiLaiva(grid, Lektuvnesis, 1, LaivuSarasas);
    statytiLaiva(grid, SarvuotasLaivas, 2, LaivuSarasas);
    statytiLaiva(grid, SarvuotasLaivas, 3, LaivuSarasas);
    statytiLaiva(grid, Minininkas, 4, LaivuSarasas);
    statytiLaiva(grid, Minininkas, 5, LaivuSarasas);
    statytiLaiva(grid, Minininkas, 6, LaivuSarasas);
    statytiLaiva(grid, PovandeninisLaivas, 7, LaivuSarasas);
    statytiLaiva(grid, PovandeninisLaivas, 8, LaivuSarasas);
    statytiLaiva(grid, PovandeninisLaivas, 9, LaivuSarasas);
    statytiLaiva(grid, PovandeninisLaivas, 10, LaivuSarasas);

    cout << "Sveiki atvyke i Laivu musi, noredami zaisti spauskite raide - p." << endl << endl;
    cout << "Jeigu pataikete, lentoje matysite skaiciu 1, jei prasovete matysite skaiciu 9." << endl << endl;
    cin >> zaisti;
    if(zaisti=='p')
    {
        Zaidimas(grid, LaivuSarasas);
    }
    return 0;
}

void inicializavimas(int grid[][10])
{
    for(int stulp=0; stulp<10; stulp++)
    {
        for(int eile=0; eile<10; eile++)
        {
            grid[stulp][eile]=0;
        }
    }
}

void spausdintiLenta(int grid[][10])
{
    cout << "   0|1|2|3|4|5|6|7|8|9" << endl << endl;
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            if(j==0)
            {
                cout << i << "  " ;
            }
            cout << grid[i][j] ;
            if(j!=9)
            {
                cout << "|";
            }
        }
    cout << endl;
    }
    cout << endl;
}

void spausdintZaidimoLenta(int grid[][10])
{
    cout << "   0|1|2|3|4|5|6|7|8|9" << endl << endl;
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            if(j==0)
            {
                cout << i << "  " ;
            }
            if(grid[i][j]==1)
            {
                cout << 1;
            } else if(grid[i][j]==9)
            {
                cout << 9;
            } else
            {
                cout << 0;
            }

            if(j!=9)
            {
                cout << "|";
            }
        }
    cout << endl;
    }
    cout << endl;
}

bool statytiLaiva(int grid[][10], int LaivoDydis, int name, vector<Laivas> &LaivuSarasas)
{
    srand(time(0));
    int stulp=0;
    int eile=0;
    char d='v';
    bool statymoKlaida=true;
    char check='v';
    int cS=0;

    d=Kryptis(rand()%10);
    stulp=EilStulpReset(stulp, eile, LaivoDydis, d);

    while(statymoKlaida)
    {
        if(d=='h')
        {
            cS=Tarpai(grid, stulp, eile, LaivoDydis, d);
            if(cS==1)
            {
                d=Kryptis(rand()%10);
                stulp=EilStulpReset(stulp, eile, LaivoDydis, d);
                cS==0;
                continue;
            }
            KeistiVieta(grid, stulp, eile, LaivoDydis, d);
            KeistiLaivoInfo(grid, stulp, eile, LaivoDydis, d, LaivuSarasas, name);
            return 0;
        }
        else if(d=='v')
        {
            cS=Tarpai(grid, stulp, eile, LaivoDydis, d);
            if(cS==1)
            {
                d=Kryptis(rand()%10);
                stulp=EilStulpReset(stulp, eile, LaivoDydis, d);
                cS==0;
                continue;
            }
            KeistiVieta(grid, stulp, eile, LaivoDydis, d);
            KeistiLaivoInfo(grid, stulp, eile, LaivoDydis, d, LaivuSarasas, name);
            return 0;
        }
     }
}

char Kryptis(int d)
{
    if(d>4)
        {
            return 'h';
        }
        else
        {
            return 'v';
        }
}

void KeistiVieta(int grid[][10], int stulp, int eile, int LaivoDydis, char direction)
{
    if(direction=='h')
    {
        for(int i=0; i<LaivoDydis; i++)
        {
            grid[eile][stulp]=LaivoDydis;
            stulp++;
            cout << endl;
        }
    }
    else if(direction=='v')
    {
        for(int i=0; i<LaivoDydis; i++)
        {
            grid[eile][stulp]=LaivoDydis;
            eile++;
            cout << endl;
        }
    }
    else
    {
        cout << "Klaida, netinkama kryptis" << endl;
    }
}

int Tarpai(int grid[][10], int c, int r, int s, char d)
{
    int check=0;
    if(d=='h')
    {
        for(int i=c; i<c+s; i++)
        {
        check=grid[r][i];
                if(check!=0)
                {
                    return 1;
                }
        }

        return 0;
    }
    else
    {
        for(int i=r; i<r+s; i++)
        {
        check=grid[i][c];
                if(check!=0)
                {
                    return 1;

                }
        }

        return 0;
    }
}

int EilStulpReset(int stulp, int &eile, int LaivoDydis, char d)
{
    switch(LaivoDydis)
    {
        case PovandeninisLaivas:
            if(d=='h')
            {
                stulp=rand()%8;
                eile=rand()%10;
            }
            else
            {
                stulp=rand()%10;
                eile=rand()%8;
            }
            break;
        case Minininkas:
            if(d=='h')
            {
                stulp=rand()%7;
                eile=rand()%10;
            }
            else
            {
                stulp=rand()%10;
                eile=rand()%7;
            }
            break;
        case SarvuotasLaivas:
            if(d=='h')
            {
                stulp=rand()%6;
                eile=rand()%10;
            }
            else
            {
                stulp=rand()%10;
                eile=rand()%6;
            }
            break;
        case Lektuvnesis:
            if(d=='h')
            {
                stulp=rand()%5;
                eile=rand()%10;
            }
            else
            {
                stulp=rand()%10;
                eile=rand()%5;
            }
    }
    return stulp;
}

void KeistiLaivoInfo(int grid[][10], int c, int r, int LaivoDydis, char d, vector<Laivas> &LaivuSarasas, int name)
{
    switch(name)
    {
        case 1:
            if(d=='h')
            {
                vector<int> r1 (5);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                }
                vector<int> c1 (5);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                    c++;
                }
            Laivas LaivasLektuvnesis('h', 5, r1, c1, 0, "Lektuvnesi");
            LaivuSarasas.push_back(LaivasLektuvnesis);
            }
            else if(d=='v')
            {
                vector<int> r1 (5);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                    r++;
                }
                vector<int> c1 (5);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                }
            Laivas LaivasLektuvnesis('v', 5, r1, c1, 0, "Lektuvnesi");
            LaivuSarasas.push_back(LaivasLektuvnesis);
            }
            break;
        case 2:
            if(d=='h')
            {
                vector<int> r1 (4);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                }
                vector<int> c1 (4);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                    c++;
                }
            Laivas LaivasSarvuotas('h', 4, r1, c1, 0, "Sarvuota Laiva 1");
            LaivuSarasas.push_back(LaivasSarvuotas);
            }
            else if(d=='v')
            {
                vector<int> r1 (4);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                    r++;
                }
                vector<int> c1 (4);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                }
            Laivas LaivasSarvuotas('v', 4, r1, c1, 0, "Sarvuota Laiva 1");
            LaivuSarasas.push_back(LaivasSarvuotas);
        }
        break;
        case 3:
            if(d=='h')
            {
                vector<int> r1 (4);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                }
                vector<int> c1 (4);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                    c++;
                }
            Laivas LaivasSarvuotas2('h', 4, r1, c1, 0, "Sarvuota Laiva 2");
            LaivuSarasas.push_back(LaivasSarvuotas2);
            }
            else if(d=='v')
            {
                vector<int> r1 (4);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                    r++;
                }
                vector<int> c1 (4);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                }
            Laivas LaivasSarvuotas2('v', 4, r1, c1, 0, "Sarvuota Laiva 2");
            LaivuSarasas.push_back(LaivasSarvuotas2);
            }
            break;
        case 4:
            if(d=='h')
            {
                vector<int> r1 (3);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                }
                vector<int> c1 (3);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                    c++;
                }
             Laivas LaivasMinininkas('h', 3, r1, c1, 0, "Minininka 1");
             LaivuSarasas.push_back(LaivasMinininkas);
             }
             else if(d=='v')
             {
                vector<int> r1 (3);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                    r++;
                }
                vector<int> c1 (3);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                }
             Laivas LaivasMinininkas('v', 3, r1, c1, 0, "Minininka 1");
             LaivuSarasas.push_back(LaivasMinininkas);
             }
             break;
        case 5:
        if(d=='h')
        {
            vector<int> r1 (3);
            for (int i=0; i<(int)r1.size(); ++i)
            {
                r1.at(i)=r;
            }
            vector<int> c1 (3);
            for (int i=0; i<(int)c1.size(); ++i)
            {
                c1.at(i)=c;
                c++;
            }
        Laivas LaivasMinininkas2('h', 3, r1, c1, 0, "Minininka 2");
        LaivuSarasas.push_back(LaivasMinininkas2);
        }
        else if(d=='v')
        {
            vector<int> r1 (3);
            for (int i=0; i<(int)r1.size(); ++i)
            {
                r1.at(i)=r;
                r++;
            }
            vector<int> c1 (3);
            for (int i=0; i<(int)c1.size(); ++i)
            {
                c1.at(i)=c;
            }
            Laivas LaivasMinininkas2('v', 3, r1, c1, 0, "Minininka 2");
            LaivuSarasas.push_back(LaivasMinininkas2);
        }
            break;
        case 6:
            if(d=='h')
            {
                vector<int> r1 (3);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                }
                vector<int> c1 (3);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                    c++;
                }
            Laivas LaivasMinininkas3('h', 3, r1, c1, 0, "Minininka 3");
            LaivuSarasas.push_back(LaivasMinininkas3);
            }
            else if(d=='v')
            {
                vector<int> r1 (3);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                    r++;
                }
                vector<int> c1 (3);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                }
            Laivas LaivasMinininkas3('v', 3, r1, c1, 0, "Minininka 3");
            LaivuSarasas.push_back(LaivasMinininkas3);
            }
            break;
        case 7:
            if(d=='h')
            {
                vector<int> r1 (2);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                }
                vector<int> c1 (2);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                    c++;
                }
            Laivas LaivasPovandeninis('h', 2, r1, c1, 0, "Povandenini Laiva 1");
            LaivuSarasas.push_back(LaivasPovandeninis);
            }
            else if(d=='v')
            {
                vector<int> r1 (2);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                    r++;
                }
                vector<int> c1 (2);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                }
            Laivas LaivasPovandeninis('v', 2, r1, c1, 0, "Povandenini Laiva 1");
            LaivuSarasas.push_back(LaivasPovandeninis);
            }
            break;
        case 8:
            if(d=='h')
            {
                vector<int> r1 (2);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                }
                vector<int> c1 (2);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                    c++;
                }
            Laivas LaivasPovandeninis2('h', 2, r1, c1, 0, "Povandenini Laiva 2");
            LaivuSarasas.push_back(LaivasPovandeninis2);
            }
            else if(d=='v')
            {
                vector<int> r1 (2);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                    r++;
                }
                vector<int> c1 (2);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                }
            Laivas LaivasPovandeninis2('v', 2, r1, c1, 0, "Povandenini Laiva 2");
            LaivuSarasas.push_back(LaivasPovandeninis2);
            }
            break;
        case 9:
            if(d=='h')
            {
                vector<int> r1 (2);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                }
                vector<int> c1 (2);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                    c++;
                }
            Laivas LaivasPovandeninis3('h', 2, r1, c1, 0, "Povandenini Laiva 3");
            LaivuSarasas.push_back(LaivasPovandeninis3);
            }
            else if(d=='v')
            {
                vector<int> r1 (2);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                    r++;
                }
                vector<int> c1 (2);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                }
            Laivas LaivasPovandeninis3('v', 2, r1, c1, 0, "Povandenini Laiva 3");
            LaivuSarasas.push_back(LaivasPovandeninis3);
            }
            break;
        case 10:
        if(d=='h')
        {
            vector<int> r1 (2);
            for (int i=0; i<(int)r1.size(); ++i)
            {
                r1.at(i)=r;
            }
            vector<int> c1 (2);
            for (int i=0; i<(int)c1.size(); ++i)
            {
                c1.at(i)=c;
                c++;
            }
        Laivas LaivasPovandeninis4('h', 2, r1, c1, 0, "Povandenini Laiva 4");
        LaivuSarasas.push_back(LaivasPovandeninis4);
        }
        else if(d=='v')
        {
            vector<int> r1 (2);
            for (int i=0; i<(int)r1.size(); ++i)
            {
                r1.at(i)=r;
                r++;
            }
            vector<int> c1 (2);
            for (int i=0; i<(int)c1.size(); ++i)
            {
                c1.at(i)=c;
            }
        Laivas LaivasPovandeninis4('v', 2, r1, c1, 0, "Povandenini Laiva 4");
        LaivuSarasas.push_back(LaivasPovandeninis4);
        }
        break;
    }
}

int Zaidimas(int grid[][10], vector<Laivas> &LaivuSarasas)
{
    bool veikimas=true;
    int eile=0;
    int stulp=0;
    int spejimas=0;
    int hit=0;
    int miss=0;
    int tarpas=0;
    char d='g';
    string hitas="";
    int sunk=0;

    while(veikimas)
    {
        spausdintZaidimoLenta(grid);
        cout << "Iveskite eiles numeri: ";
        cin >> eile;
        cout << "Iveskite stulpelio numeri: ";
        cin >> stulp;
        cout << endl;
        spejimas++;
        tarpas=gautiTarpa(grid, eile, stulp);

        switch(tarpas)
        {
            case 0:
                cout << "Jus nepataikete!" << endl;
                grid[eile][stulp]=9;
                miss++;
                break;
            case 1:
                cout << "Si vieta jau buvo bomborduota." << endl;
                break;
            case 2:
                grid[eile][stulp]=1;
                hit++;

                hitas=LaivuSarasas[6].getLaivas(eile, stulp);
                if(hitas=="Povandenini Laiva 1")
                {
                    cout << "Jus pataikete i " << hitas << "!" << endl;
                    LaivuSarasas[6].setHit();
                    sunk=LaivuSarasas[6].checkSunk(PovandeninisLaivas);
                    if(sunk==9)
                    {
                        cout << "Jus nuskandinote Povandenini Laiva 1." << endl;
                    }
                } else if(hitas.empty())
                {
                    hitas=LaivuSarasas[7].getLaivas(eile, stulp);
                    if(hitas=="Povandenini Laiva 2")
                    {
                        cout << "Jus pataikete i " << hitas << "!" << endl;
                        LaivuSarasas[7].setHit();
                        sunk=LaivuSarasas[7].checkSunk(PovandeninisLaivas);
                        if(sunk==9)
                        {
                            cout << "Jus nuskandinote Povandenini Laiva 2." << endl;
                        }
                    } else if(hitas.empty())
                    {
                        hitas=LaivuSarasas[8].getLaivas(eile, stulp);
                        cout << "Jus pataikete i " << hitas << "!" << endl;
                        LaivuSarasas[8].setHit();
                        sunk=LaivuSarasas[8].checkSunk(PovandeninisLaivas);
                        if(sunk==9)
                        {
                            cout << "Jus nuskandinote Povandenini Laiva 3." << endl;
                        }
                    } else if(hitas.empty())
                    {
                        hitas=LaivuSarasas[9].getLaivas(eile, stulp);
                        cout << "Jus pataikete i " << hitas << "!" << endl;
                        LaivuSarasas[9].setHit();
                        sunk=LaivuSarasas[9].checkSunk(PovandeninisLaivas);
                        if(sunk==9)
                        {
                            cout << "Jus nuskandinote Povandenini Laiva 4." << endl;
                        }
                    }
                }
                hitas.clear();
                break;
            case 3:
                grid[eile][stulp]=1;
                hit++;
                hitas=LaivuSarasas[3].getLaivas(eile, stulp);
                if(hitas=="Minininka 1")
                {
                    cout << "Jus pataikete i " << hitas << "!" << endl;
                    LaivuSarasas[3].setHit();
                    sunk=LaivuSarasas[3].checkSunk(Minininkas);
                    if(sunk==9)
                    {
                        cout << "Jus nuskandinote Minininka 1." << endl;
                    }
                } else if(hitas.empty())
                {
                    hitas=LaivuSarasas[4].getLaivas(eile, stulp);
                    if(hitas=="Minininka 2")
                    {
                        cout << "Jus pataikete i " << hitas << "!" << endl;
                        LaivuSarasas[4].setHit();
                        sunk=LaivuSarasas[4].checkSunk(Minininkas);
                        if(sunk==9)
                        {
                            cout << "Jus nuskandinote Minininka 2." << endl;
                        }
                    } else if(hitas.empty())
                    {
                        hitas=LaivuSarasas[5].getLaivas(eile, stulp);
                        cout << "Jus pataikete i " << hitas << "!" << endl;
                        LaivuSarasas[5].setHit();
                        sunk=LaivuSarasas[5].checkSunk(Minininkas);
                        //cout << "sunk is " << sunk << endl;
                        if(sunk==9)
                        {
                            cout << "Jus nuskandinote Minininka 3." << endl;
                        }
                    }
                }
                hitas.clear();
                break;
            case 4:
                grid[eile][stulp]=1;
                hit++;

                hitas=LaivuSarasas[1].getLaivas(eile, stulp);
                if(hitas=="Sarvuota Laiva 1")
                {
                    cout << "Jus pataikete i " << hitas << "!" << endl;
                    LaivuSarasas[1].setHit();
                    sunk=LaivuSarasas[1].checkSunk(SarvuotasLaivas);
                    if(sunk==9)
                    {
                        cout << "Jus nuskandinote Sarvuota Laiva 1." << endl;
                    }
                }
                if(hitas.empty())
                {
                    hitas=LaivuSarasas[2].getLaivas(eile, stulp);
                    cout << "Jus pataikete i " << hitas << "!" << endl;
                    LaivuSarasas[2].setHit();
                    sunk=LaivuSarasas[2].checkSunk(SarvuotasLaivas);
                    if(sunk==9)
                    {
                        cout << "Jus nuskandinote Sarvuota Laiva 2." << endl;
                    }
                }
                hitas.clear();
                break;
            case 5:
                cout << "Jus nuskandinote Lektuvnesi! " << endl;
                grid[eile][stulp]=1;
                hit++;
                LaivuSarasas[0].setHit();
                sunk=LaivuSarasas[0].checkSunk(Lektuvnesis);
                if(sunk==9)
                {
                    cout << "Jus nuskandinote Lektuvnesi!" << endl;
                }
                break;
        }
        if(hit==30)
        {
            veikimas=false;
        }
    }
    cout << "Aciu, kad zaidete. Visus laivus nuskandinote per " << spejimas << " ejimus!" << endl;

}
int gautiTarpa(int grid[][10], int eile, int stulp)
{
    int tarpas=0;
    tarpas=grid[eile][stulp];
    return tarpas;
}
