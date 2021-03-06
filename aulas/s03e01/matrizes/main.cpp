#include "libs/ed_base.h"
#include "libs/ed_mat.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int nlinhas = 20;
int ncolunas = 35;

//r red
//g green
//b blue
//m magenta
//c cyan -
//y yellow
//w white
//k black

vector<Par> pegar_vizinhos(Par par){
    vector<Par> vizinhos;
    vizinhos.push_back(Par(par.l, par.c - 1));
    vizinhos.push_back(Par(par.l, par.c + 1));
    vizinhos.push_back(Par(par.l - 1, par.c));
    vizinhos.push_back(Par(par.l + 1, par.c));
    return vizinhos;
}

vector<Par> shuffle(vector<Par> &vet){
    for(int i = 0; i < (int) vet.size(); i++){
        std::swap(vet[i], vet[rand() % (int) vet.size()]);
    }
    return vet;
}

int queimar(matchar &mat, Par p){
    if(p.l < 0 || p.l >= mat.sizeL())
        return 0;
    if(p.c < 0 || p.c >= mat.sizeC())
        return 0;

    mat_draw(mat);
    mat_focus(p, 'y');
    ed_show();

    //se for arvore
    if(mat.get(p) == 'g'){
        //para cada um dos vizinhos de p
        for(auto par : pegar_vizinhos(p)){
            if(mat.equals(par, 'b'))
                //retorne sem queimar
                return 0;
        }

        mat.get(p) = 'r';//antes da recursão
        mat_draw(mat);
        ed_show();
        int cont = 1;
        auto viz = pegar_vizinhos(p);
        shuffle(viz);
        for(auto par : viz){
            cont += queimar(mat, par);
        }

        mat.get(p) = 'k';//antes da recursão
        mat_draw(mat);
        ed_show();

        return cont;

    }
    return 0;
}



int main(){
    matchar mat(nlinhas, ncolunas, 'g');
    mat_paint_brush(mat, "wgb");
    Par p = mat_get_click(mat, "Escolha onde comeca o fogo.");
    queimar(mat, p);
    mat_draw(mat);

    ed_lock();

    return 0;
}


