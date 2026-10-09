#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
//predlozena kombinacija brojeva sa vezbi (Numerical Recipes in C)
unsigned long seed=1;
int LKG() {
    seed=1664525*seed+1013904223;
    return (int)(seed/4294967296.*13)+1;
}

//Jednostruko ulancana lista
typedef struct lista {
    int broj_karte;
    struct lista *sledeci;
}cvor;
//funkcije za rad sa listom
void dodaj_na_pocetak(cvor **L,int element) {
    cvor *novi=(cvor*)malloc(sizeof(cvor));
    novi->broj_karte=element;
    novi->sledeci=*L;
    (*L)=novi;
}

void dodaj_na_kraj(cvor **L,int element) {
    cvor *novi=(cvor*)malloc(sizeof(cvor));
    novi->broj_karte=element;
    novi->sledeci=NULL;
    if (*L==NULL) *L=novi;
    else {
        cvor *t=*L;
        while (t->sledeci!=NULL) {
        t=t->sledeci;
    }
        t->sledeci=novi;
    }
}

int ukloni_sa_pocetka(cvor **L) {
    if (*L==NULL) return -1; //ako je lista prazna
    int br=(*L)->broj_karte;
    cvor *t=*L;
    *L=(*L)->sledeci;
    free(t);
    return br;
}

int ukloni_sa_kraja(cvor **L) {
    if (*L==NULL) return -1; //ako je lista prazna
    cvor *t=*L;
    while ((t->sledeci)->sledeci!=NULL) {
        t=t->sledeci;
    }
    cvor *p=t->sledeci;
    int br=p->broj_karte;
    free(p);
    t->sledeci=NULL;
    return br;
}

int pogledaj_pocetak(cvor **L) {
    if (*L==NULL) return -1; //ako je prazno
    return (*L)->broj_karte;
}

int pogledaj_kraj(cvor **L) {
    if (*L==NULL) return -1;
    cvor *t=*L;
    while (t->sledeci!=NULL) {
        t=t->sledeci;
    }
    return t->broj_karte;
}

bool je_prazna(cvor **L) {
 if (*L==NULL) return true;
    return false;
}

int velicina(cvor **L) {
    if (*L==NULL) return 0;
    cvor *t=*L;
    int n=0;
    while (t!=NULL) {
        t=t->sledeci;
        n++;
    }
    return n;
}

//funkcije za rad sa stekom
void push(cvor **L,int element) {
    cvor *novi=(cvor*)malloc(sizeof(cvor));
    novi->broj_karte=element;
    novi->sledeci=*L;
    (*L)=novi;
}

int pop(cvor **L) {
    int br=(*L)->broj_karte;
    cvor *t=*L;
    *L=(*L)->sledeci;
    free(t);
    return br;
}

void obrisi(cvor ** L) {
    while (*L!=NULL) {
        pop(L);
    }
}

int pogledaj_vrh_steka(cvor **L) {
    if (*L==NULL) return -1;
    return (*L)->broj_karte;
}

bool je_prazan(cvor **L) {
    if (*L==NULL) return true;
    return false;
}

//pocinje igra
void glavni_meni() {
    printf("\n\n=== KARTASKA IGRA ===\n");
    printf("1. Promesaj spil i podeli karte\n");
    printf("2. Potez igraca 1\n");
    printf("3. Potez igraca 2\n");
    printf("4. Prikazi trenutno stanje\n");
    printf("0. Izlaz\n");
    printf("\n\nUnesite svoj izbor: ");
}
void meni_igraca(int br) {
    printf("\n\n=== POTEZ IGRACA %d ===\n",br);
    printf("1. Vuci kartu sa zatvorenog spila\n");
    printf("2. Vuci kartu sa otvorenog spila\n");
    printf("3. Postavi izvucenu kartu na sredinu\n");
    printf("4. Postavi izvucenu kartu kod protivnika\n");
    printf("5. Postavi izvucenu kartu na svoju gomilu i zavrsi potez\n");
    printf("6. Prikazi trenutno stanje\n");
    printf("Izaberite svoj potez: ");

}
void ispisi_talon(cvor **p_zatvoren, cvor **p_otvoren, cvor **sredina,cvor **d_zatvoren,cvor **d_otvoren, int izvucena_j,int izvucena_d) {
    char zamena[14][5]={"X","A","2","3","4","5","6","7","8","9","10","J","D","K"}; //X znaci da je prazan
    if (izvucena_j==-1)izvucena_j=0;
    if (izvucena_d==-1)izvucena_d=0;
    int po=pogledaj_vrh_steka(p_otvoren);
    if (po==-1) po=0;
    int s=pogledaj_vrh_steka(sredina);
    if (s==-1) s=0;
    int d_o=pogledaj_vrh_steka(d_otvoren);
    if (d_o==-1) d_o=0;
    printf("%d  %s  %s  %s  %s  %s  %d\n",velicina(p_zatvoren),zamena[izvucena_j],zamena[po],zamena[s],zamena[d_o],zamena[izvucena_d],velicina(d_zatvoren));
}
//refresovanje podataka i mesanje karata
void refresh(cvor **z_prvi,cvor **z_drugi,cvor **o_prvi,cvor **o_drugi, cvor **sredina) {
    if (*z_prvi!=NULL)  obrisi(z_prvi);
    if (*z_drugi!=NULL) obrisi(z_drugi);
    if (*o_drugi!=NULL) obrisi(o_drugi);
    if (*sredina!=NULL) obrisi(sredina);
    if (*o_prvi!=NULL) obrisi(o_prvi);
}
void promesaj_spil(cvor **prvi,cvor **drugi) {
    printf("Unesite vrednost semena: ");
    scanf("%lu",&seed);
    int broj_izvucenih_karata[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};
    int pom;
    for (int j=0;j<52;) {
        pom=LKG();
        if (broj_izvucenih_karata[pom-1]<4) {
            broj_izvucenih_karata[pom-1]++;
            if (j<26)
                dodaj_na_pocetak(prvi,pom);
            else
                dodaj_na_pocetak(drugi,pom);
            j++;
        }
    }
}

bool postavi_kartu(cvor **gde_stavljam,int karta) {
    if (je_prazan(gde_stavljam)&&karta==1)
    {
        push(gde_stavljam,karta);
        return true;
    }
    if (!je_prazan(gde_stavljam)&&(karta==1+pogledaj_vrh_steka(gde_stavljam)||(karta==1&&pogledaj_vrh_steka(gde_stavljam)==13))) {
        push(gde_stavljam,karta);
        return true;
    }
    printf("Ne mozete da je stavite tu!!!");
    return false;
}
bool pobeda(cvor **zatvoren,cvor **otvoren,int izabrana_karta) {
    if (je_prazna(zatvoren)&&je_prazan(otvoren)&&izabrana_karta==-1)
        return true;
    return false;
}

void okreni(cvor **zatvoren,cvor **otvoren) {
    while (!je_prazan(otvoren)) {
        dodaj_na_pocetak(zatvoren,pop(otvoren));
    }
}

bool potez_igraca(int br,cvor **zatvoren,cvor **otvoren_moj,cvor **otvoren_tudji,cvor **sredina,cvor **zatvoren_tudji) {
    int izbor;
    char zamena[14][5]={"X","A","2","3","4","5","6","7","8","9","10","J","D","K"};
    int potez_u_toku=true;
    int izvucena_karta=-1;
    meni_igraca(br);
    while (potez_u_toku) {

        scanf("%d",&izbor);
        switch (izbor) {
            case 1: {
                if (izvucena_karta==-1) {
                    if (je_prazna(zatvoren)) okreni(zatvoren,otvoren_moj);
                    izvucena_karta=ukloni_sa_pocetka(zatvoren);
                    if (izvucena_karta==-1)
                        printf("Vas zatvoren spil je prazan! Izaberi drugi potez.\n");
                    else printf("Vasa izvucnena karta je: %s\n",zamena[izvucena_karta]);

                }
                else printf("Vec imate izvucenu kartu!\n");
            }break;
                case 2: {
                    if (izvucena_karta==-1) {
                        izvucena_karta=pogledaj_vrh_steka(otvoren_moj);
                        if (izvucena_karta==-1) printf("Vas otvoren spil je prazan! Izaberi drugi potez.\n");
                        else {
                            izvucena_karta=pop(otvoren_moj);
                            printf("Uzeli ste kartu %s\n",zamena[izvucena_karta]);

                        }
                    }
                    else printf("Vec imate izvucenu kartu!\n");

                }break;
            case 3: {
                if (izvucena_karta!=-1) {
                    if (postavi_kartu(sredina,izvucena_karta)==true) {
                        izvucena_karta=-1;
                        if (pobeda(zatvoren,otvoren_moj,izvucena_karta)==true) {
                            printf("KRAJ IGRE! POBEDNIK JE IGRAC BROJ %d\n",br);
                            return true;
                        }
                    }

                }
                else printf("Niste izvukli kartu!\n");
            }break;
                case 4: {
                    if (izvucena_karta!=-1) {
                        if (postavi_kartu(otvoren_tudji,izvucena_karta)==true) {
                            izvucena_karta=-1;
                            if (pobeda(zatvoren,otvoren_moj,izvucena_karta)==true) {
                                printf("KRAJ IGRE! POBEDNIK JE IGRAC BROJ %d\n\n",br);
                                return true;
                            }
                        }
                    }
                    else printf("Niste izvukli kartu!\n");

                }break;
                case 5: {
                    if (izvucena_karta!=-1) {
                        push(otvoren_moj,izvucena_karta);
                        potez_u_toku=false;
                        izvucena_karta=-1;
                    }
                    else printf("Niste izvukli kartu!\n");
                }break;
            case 6: {
                if (br==1) {
                    ispisi_talon(zatvoren,otvoren_moj,sredina,zatvoren_tudji,otvoren_tudji,izvucena_karta,0);

                }
                else ispisi_talon(zatvoren_tudji,otvoren_tudji,sredina,zatvoren,otvoren_moj,0,izvucena_karta);

            }break;
                default: printf("Niste uneli opciju od ponudjenih!\n");break;
        }
    }
return false;
}

int main(void) {

    cvor *zatvoren_prvi=NULL;
    cvor *zatvoren_drugi=NULL;
    cvor *otvoren_prvi=NULL;
    cvor *otvoren_drugi=NULL;
    cvor *sredina=NULL;
    bool igra_u_toku=true;
    int izbor=0;
    int na_potezu=1;
    bool imamo_pobednika=false;
    bool spil_je_promesan=false;
    while (igra_u_toku) {
        if (imamo_pobednika==false) {
            glavni_meni();
            scanf("%d",&izbor);
            if (spil_je_promesan==false && (izbor==2||izbor==3||izbor==4)) {
                printf("Greska. Morate promesati spil.");
                continue;
            }
            switch (izbor){
                case 1: {
                    refresh(&zatvoren_prvi,&zatvoren_drugi,&otvoren_prvi,&otvoren_drugi,&sredina);
                    na_potezu=1;
                    imamo_pobednika=false;
                    spil_je_promesan=true;
                    promesaj_spil(&zatvoren_prvi,&zatvoren_drugi);

                }break;
                case 2: {
                    if (na_potezu!=1) {
                        printf("Greska! Na potezu je igrac 2!\n");
                    }
                    else {
                        imamo_pobednika=potez_igraca(1,&zatvoren_prvi,&otvoren_prvi,&otvoren_drugi,&sredina,&zatvoren_drugi);
                    }
                    na_potezu=2;
                }break;
                case 3: {
                    if (na_potezu!=2) {
                        printf("Greska! Na potezu je igrac 1!\n");
                    }
                    else {
                        imamo_pobednika=potez_igraca(2,&zatvoren_drugi,&otvoren_drugi,&otvoren_prvi,&sredina,&zatvoren_prvi);
                    }
                    na_potezu=1;
                }break;

                case 4: {
                    ispisi_talon(&zatvoren_prvi,&otvoren_prvi,&sredina,&zatvoren_drugi,&otvoren_drugi,0,0);
                }break;
                case 0:{igra_u_toku=false;}break;
                default: {
                    printf("Morate uneti jedan od 5 ponudjenih izbora.\n");
                }break;
            }

        }
        else {
            printf("Da bi ste poceli igru opet unesite 1.");
            spil_je_promesan=false;
            imamo_pobednika=false;
        }

    }
    return 0;
}
