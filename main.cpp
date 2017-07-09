#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "modul.c"


using namespace std;

struct mazeRunner
{
    int x, y;
    bool u, d, l, r;

    mazeRunner(): x(0), y(0), u(true), d(true), l(true), r(true) {};

    void edgeDetect(int vel)
    {
        if (x == 0) u = false;
        else u = true;

        if (y == 0) l = false;
        else l = true;

        if (x == vel) d = false;
        else d = true;

        if (y == vel) r = false;
        else r = true;
    }
    void mozeDesno(vector<vector<string> > &mat)
    {
        if((y < mat.size()) && (r == true))
        {
            if(mat.at(x).at(y+1) == "_") r = true;
            else r = false;
        }
    }
    void mozeLevo(vector<vector<string> > &mat)
    {

        if((y > 0) && (l == true))
        {
            if(mat.at(x).at(y-1) == "_") l = true;
            else l = false;
        }
        else l = false;
    }

    void mozeGore(vector<vector<string> > &mat)
    {
        if((x > 0)&&(u == true))
        {
            if(mat.at(x-1).at(y) == "_") u = true;
            else u = false;
        }
        else u = false;
    }
    void mozeDole(vector<vector<string> > &mat)
    {
        if((x < mat.size()) && (d == true))
        {
            if(mat.at(x+1).at(y) == "_") d = true;
            else d = false;
        }
        else d = false;
    }
    void randomSmer(vector<int> &v)
    {
        int random = rand() % 3;
        if(random == 0)//ide gore
        {
            if(u == true)
            {
                x--;
                v.push_back(0);
                return;
            }
        }

        if(random == 1)//ide dole
        {
            if(d == true)
            {
                x++;
                v.push_back(1);
                return;
            }
        }
        if(random == 2) // ide levo
        {
            if(l == true)
            {
                y--;
                v.push_back(2);
                return;            }
        }
        v.push_back(4);
    }
    void skreniDesno(vector<int> &v)
    {
        if(r == true)
        {
            y++;
            v.push_back(3);
        }
        else
        {
            v.push_back(4);
        }
    }
};
void napraviPraznuMatricu (vector<vector<string> > &mat, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        vector<string> pomoc;
        string s = "A";
        for(int j = 0; j < cols; j++)
        {
            pomoc.push_back(s);
        }
        mat.push_back(pomoc);
    }
}
void stampajMatricu(vector<vector<string> > &mat)
{
    for(int i = 0; i < mat.size(); i++)
    {
         for(int j =0; j < mat.at(i).size(); j++)
         {
            cout << mat.at(i).at(j);
         }
        cout<<endl;
    }

}
void napraviRedove(vector<string> &red)
{
    ifstream lavirint("lavirint1.txt");
    string line;
    while(getline(lavirint, line))
        red.push_back(line);
}
void ucitajLavirint(vector<vector<string> > &mat)
{
    vector<string> lines;
    napraviRedove(lines);
    for(int i = 0; i < mat.size(); i++)
        for(int j = 0; j < mat.at(i).size(); j++)
        {
            mat.at(i).at(j) = lines.at(i).at(j);
        }

}

int main()
{
    srand(time(NULL));
    int rows = 40;
    int cols = 40;
    vector<int> v;
    vector<vector<string> > mat;
    napraviPraznuMatricu(mat, rows, cols);
    ucitajLavirint(mat);
    mazeRunner p1;
    ofstream upis("kretanje.txt");
    for(int i = 0; i < 1000; i++)
    {
        p1.edgeDetect(39);

        p1.mozeDesno(mat);
        p1.mozeLevo(mat);
        p1.mozeGore(mat);
        p1.mozeDole(mat);

        if(p1.r == true)
        {
            p1.skreniDesno(v);
        }
        else
        {
             p1.randomSmer(v);
        }
    }

    for(int i = 0; i < v.size(); i++)
       upis << v.at(i) << endl;

}
