#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30

typedef struct {
    int numero;
    char nom[50];
    int type;
    float solde;
} Compte;

float taux(int type) {
    if (type == 1) return 3;
    if (type == 2) return 1;
    if (type == 3) return 5;
    return 0;
}

float interet(Compte c) {
    return c.solde * taux(c.type) / 100;
}

const char* nomType(int type) {
    if (type == 1) return "Epargne";
    if (type == 2) return "Courant";
    if (type == 3) return "Jeune  ";
    return "Inconnu";
}

void ajouter(Compte t[], int *n) {
    int nb, i, num;
    printf("\n  Combien de comptes a ajouter ? ");
    scanf("%d", &nb);

    for (i = 0; i < nb; i++) {
        if (*n >= MAX) {
            printf("  [!] Tableau plein\n");
            return;
        }
        printf("\n  +--- Nouveau compte %d ----------------------------+\n", *n + 1);

        printf("  |  Numero   : ");
        scanf("%d", &num);

        for (int j = 0; j < *n; j++) {
            if (t[j].numero == num) {
                printf("  [!] Ce numero existe deja\n");
                return;
            }
        }
        t[*n].numero = num;

        printf("  |  Nom      : ");
        scanf("%s", t[*n].nom);

        printf("  |  Type     : 1=Epargne  2=Courant  3=Jeune\n");
        printf("  |  Choix    : ");
        scanf("%d", &t[*n].type);
        if (t[*n].type < 1 || t[*n].type > 3) {
            printf("  [!] Type invalide\n");
            return;
        }

        printf("  |  Solde    : ");
        scanf("%f", &t[*n].solde);

        printf("  +--------------------------------------------------+\n");
        printf("  [OK] Compte ajoute avec succes\n");
        (*n)++;
    }
}

void triSolde(Compte t[], int n) {
    Compte tmp;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (t[i].solde < t[j].solde) {
                tmp = t[i]; t[i] = t[j]; t[j] = tmp;
            }
}

void triNom(Compte t[], int n) {
    Compte tmp;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (strcmp(t[i].nom, t[j].nom) > 0) {
                tmp = t[i]; t[i] = t[j]; t[j] = tmp;
            }
}

void releve(Compte t[], int n) {
    float totalS = 0, totalI = 0, I;

    triSolde(t, n);

    printf("\n  +======================================================+\n");
    printf("  |           RELEVE GENERAL DES COMPTES                |\n");
    printf("  +------+------------------+----------+--------+--------+\n");
    printf("  | Rang | Nom              | Type     |  Solde |Interet |\n");
    printf("  +------+------------------+----------+--------+--------+\n");

    for (int i = 0; i < n; i++) {
        I = interet(t[i]);
        printf("  |  %-3d | %-16s | %-8s |%8.2f|%8.2f|\n",
               i + 1, t[i].nom, nomType(t[i].type), t[i].solde, I);
        totalS += t[i].solde;
        totalI += I;
    }

    printf("  +------+------------------+----------+--------+--------+\n");
    printf("  |                   TOTAL              |%8.2f|%8.2f|\n", totalS, totalI);
    printf("  +======================================+========+========+\n");
}

void listeNom(Compte t[], int n) {
    triNom(t, n);

    printf("\n  +------------------+----------+------------------+\n");
    printf("  |    LISTE DES COMPTES PAR NOM                   |\n");
    printf("  +------------------+----------+------------------+\n");
    printf("  | Nom              | Type     |            Solde |\n");
    printf("  +------------------+----------+------------------+\n");

    for (int i = 0; i < n; i++) {
        printf("  | %-16s | %-8s | %16.2f |\n",
               t[i].nom, nomType(t[i].type), t[i].solde);
    }

    printf("  +------------------+----------+------------------+\n");
}

void recherche(Compte t[], int n) {
    char nom[50];
    printf("\n  Nom a rechercher : ");
    scanf("%s", nom);

    for (int i = 0; i < n; i++) {
        if (strcmp(t[i].nom, nom) == 0) {
            printf("\n  +--- Compte trouve ----------------------------+\n");
            printf("  |  Numero  : %-32d|\n", t[i].numero);
            printf("  |  Nom     : %-32s|\n", t[i].nom);
            printf("  |  Type    : %-32s|\n", nomType(t[i].type));
            printf("  |  Solde   : %-32.2f|\n", t[i].solde);
            printf("  |  Interet : %-32.2f|\n", interet(t[i]));
            printf("  +----------------------------------------------+\n");
            return;
        }
    }

    printf("  [!] Aucun compte trouve pour \"%s\"\n", nom);
}

void operation(Compte t[], int n) {
    int num, i, choix;
    float m;

    printf("\n  Numero du compte : ");
    scanf("%d", &num);

    for (i = 0; i < n; i++) {
        if (t[i].numero == num) {
            printf("  +--- Operation --------------------------------+\n");
            printf("  |  Compte : %-33s|\n", t[i].nom);
            printf("  |  Solde  : %-33.2f|\n", t[i].solde);
            printf("  +----------------------------------------------+\n");
            printf("  Operation : 1=Depot   2=Retrait : ");
            scanf("%d", &choix);

            printf("  Montant : ");
            scanf("%f", &m);
            if (m <= 0) {
                printf("  [!] Montant invalide\n");
                return;
            }

            if (choix == 1) {
                t[i].solde += m;
                printf("  [OK] Depot effectue  ->  Nouveau solde : %.2f\n", t[i].solde);
            } else if (choix == 2) {
                if (t[i].solde >= m) {
                    t[i].solde -= m;
                    printf("  [OK] Retrait effectue  ->  Nouveau solde : %.2f\n", t[i].solde);
                } else {
                    printf("  [!] Solde insuffisant (disponible : %.2f)\n", t[i].solde);
                }
            }
            return;
        }
    }

    printf("  [!] Compte numero %d introuvable\n", num);
}

int main() {
    Compte t[MAX];
    int n = 0, choix;

    do {
        printf("\n  +==============================+\n");
        printf("  |       GESTION BANCAIRE       |\n");
        printf("  +==============================+\n");
        printf("  |  1 - Ajouter des comptes     |\n");
        printf("  |  2 - Releve general          |\n");
        printf("  |  3 - Liste par nom           |\n");
        printf("  |  4 - Rechercher un compte    |\n");
        printf("  |  5 - Depot / Retrait         |\n");
        printf("  |  0 - Quitter                 |\n");
        printf("  +==============================+\n");
        printf("  Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouter(t, &n);  break;
            case 2: releve(t, n);    break;
            case 3: listeNom(t, n);  break;
            case 4: recherche(t, n); break;
            case 5: operation(t, n); break;
            case 0: printf("\n  Au revoir!\n\n"); break;
            default: printf("  [!] Choix invalide\n"); break;
        }

    } while (choix != 0);
      return 0;
      }
