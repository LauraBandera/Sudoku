#include <iostream>
using namespace std;

const unsigned TAM = 9;

typedef unsigned TMatriz[TAM][TAM];

typedef bool TArray[TAM+1]; // la casilla 0 no se usa

void leer(TMatriz& tablero) {
    cout << "Introduzca un tablero de sudoku:" << endl;

    for (unsigned fi = 0; fi < TAM; fi++) {
        for (unsigned co = 0; co < TAM; co++) {
            cin >> tablero[fi][co];
        }
    }

}

void inicializar(TArray& numAparecidos) {
    for (unsigned i = 1; i < TAM+1; i++) {
        numAparecidos[i] = false;
    }
}


bool filaValida(const TMatriz& tablero, unsigned fi) {
    TArray numAparecidos;
    bool valida = true;
    unsigned co;

    inicializar(numAparecidos);
    co = 0;
    while (co < TAM && valida) {
        if (tablero[fi][co] == 0) {
            co++;
        } else if ((tablero[fi][co] >= 1 && tablero[fi][co] <= 9) &&
                    !numAparecidos[tablero[fi][co]]) {
            numAparecidos[tablero[fi][co]] = true;
            co++;
        } else {
            valida = false;
        }
    }

    return co >= TAM;
}

bool filasValidas(const TMatriz& tablero) {
    unsigned fi;

    fi = 0;
    while (fi < TAM && filaValida(tablero,fi)) {
        fi++;
    }

    return fi >= TAM;
}

bool columnaValida(const TMatriz& tablero, unsigned co) {
    TArray numAparecidos;
    bool valida = true;
    unsigned fi;

    inicializar(numAparecidos);
    fi = 0;
    while (co < TAM && valida) {
        if (tablero[fi][co] == 0) {
            fi++;
        } else if ((tablero[fi][co] >= 1 && tablero[fi][co] <= 9) &&
                    !numAparecidos[tablero[fi][co]]) {
            numAparecidos[tablero[fi][co]] = true;
            fi++;
        } else {
            valida = false;
        }
    }

    return fi >= TAM;
}

bool columnasValidas(const TMatriz& tablero) {
    unsigned co;

    co = 0;
    while (co < TAM && columnaValida(tablero,co)) {
        co++;
    }

    return co >= TAM;
}

bool regionValida(const TMatriz& tablero, unsigned fiCentroReg, unsigned coCentroReg) {
    TArray numAparecidos;
    bool valida = true;
    unsigned fi,co;

    inicializar(numAparecidos);
    fi = fiCentroReg-1;
    while (fi <= fiCentroReg+1 && valida) {
        co = coCentroReg-1;
        while (co <= coCentroReg+1 && valida) {
            if (tablero[fi][co] == 0) {
                co++;
            } else if ((tablero[fi][co] >= 1 && tablero[fi][co] <= 9) &&
                       !numAparecidos[tablero[fi][co]]) {
                numAparecidos[tablero[fi][co]] = true;
                co++;
            } else {
                valida = false;
            }
        }
        fi++;
    }

    return valida;

}

bool regionesValidas(const TMatriz& tablero) {
    unsigned re;
    unsigned fiCentroReg,coCentroReg;

    re = 0;
    fiCentroReg = 1;
    coCentroReg = 1;
    while (re < TAM && regionValida(tablero,fiCentroReg,coCentroReg)) {
        re++;
        coCentroReg = (coCentroReg + 3) % TAM;
        if (re == 3 || re == 6) {
            fiCentroReg += 3;
        }
    }

    return re >= TAM;

 /*
    return regionValida(tablero,1,1) && regionValida(tablero,1,4) && regionValida(tablero,1,7) &&
            regionValida(tablero,4,1) && regionValida(tablero,4,4) && regionValida(tablero,4,7) &&
            regionValida(tablero,7,1) && regionValida(tablero,7,4) && regionValida(tablero,7,7);
 */
}


bool tableroValido(const TMatriz& tablero) {

    return filasValidas(tablero) && columnasValidas(tablero) && regionesValidas(tablero);

}


int main() {
    TMatriz tablero = { {0,0,0,0,0,0,0,0,0},
                        {3,0,0,0,0,0,4,0,9},
                        {0,6,0,0,1,3,0,7,0},
                        {2,9,0,0,6,8,0,0,0},
                        {0,3,0,1,0,0,0,0,0},
                        {0,0,6,0,0,4,8,0,2},
                        {9,7,0,0,4,0,0,0,0},
                        {6,0,1,3,0,9,0,0,0},
                        {0,0,0,0,0,7,2,0,0}
                        };

    //leer(tablero);

    if (tableroValido(tablero)) {
        cout << "El tablero introducido es un sudoku VALIDO" << endl;
    } else {
        cout << "El tablero introducido es un sudoku NO VALIDO" << endl;
    }

    return 0;
}
