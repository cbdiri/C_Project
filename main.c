#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct categorie {
        int idcat;
        char nomcat[50];
};

struct type{
    int idtype;
    char nomtype[50];
    struct categorie cat;
};

struct madate{
    int jj;
    int mm;
    int aa;
};

struct produit{
    int id;
    char nom[50];
    struct type typ;
    struct madate date_exp;

};

void initcat(struct categorie *c)
{

    puts("\n Tapez id du categorie \n");
    scanf("%d",&c->idcat);
    puts("\n tapez nom du categorie \n");
    scanf("%s",c->nomcat);

}

void inittype(struct type *t)
{
     puts("\n Tapez id Type \n");
    scanf("%d",&t->idtype);
    puts("\n tapez nom Type \n");
    scanf("%s",t->nomtype);
    initcat(&t->cat);
}

void initdate(struct madate *d)
{
    do{
        printf(" tapez le jour d experation \n");
        scanf("%d",&d->jj);
    }while(d->jj <1 || d->jj>31);

    do{
        printf(" tapez le mois d experation \n");
        scanf("%d",&d->mm);
    }while(d->mm <1 || d->mm>12);

    do{
        printf(" tapez l annee d experation \n");
        scanf("%d",&d->aa);
    }while(d->aa <2023);
}
void initpdt(struct produit *p)
{
    printf("tapez ID de produit \n");
    scanf("%d",&p->id);
    printf("tapez le nom de produit \n");
    scanf("%s",p->nom);
    printf("tapez ID de type \n");
    scanf("%d",&p->typ.idtype);
  //inittype(&p->typ);
    initdate(&p->date_exp);

}

void afficherStock(struct produit p[100][50],int tabqte[], int nbtyp,struct type t[])
{
    printf("\t\t\t\t*************************************************************\n");
    printf("\t\t\t\t********************      Stock    **************************\n");
    printf("\t\t\t\t*************************************************************\n");
    printf("\t\t\t\t* Categorie     type     Qte     id_produit     date_exp     \n");
    printf("\t\t\t\t*------------------------------------------------------------\n");
    FILE *f;
    f=fopen("stock.txt","w");
    fprintf(f,"");
    fclose(f);


    f=fopen("stock.txt","a");
    int i;
    int l;
    int c;
    fprintf(f,"* Categorie     type     Qte     id_produit     date_exp     \n");

    for(i=0;i<nbtyp;i++)
    {

    printf("\t\t\t\t    %s           %s      %03d ",t[i].cat.nomcat,t[i].nomtype,tabqte[i]);

    fprintf(f,"%s %s %03d ",t[i].cat.nomcat,t[i].nomtype,tabqte[i]);

    if(tabqte[i]>0)
    {
        for(l=0;l<tabqte[i];l++)
        {
            printf("         %03d        %02d/%02d/%d ",p[l][i].id,p[l][i].date_exp.jj,p[l][i].date_exp.mm,p[l][i].date_exp.aa);
            printf("\n \t\t\t                                     ");
            fprintf(f,"      %03d        %02d/%02d/%d ",p[l][i].id,p[l][i].date_exp.jj,p[l][i].date_exp.mm,p[l][i].date_exp.aa);
            fprintf(f,"\n");

        }
    }

    printf("\n");
    fprintf(f,  "\n");
    }
    fclose(f);
}

void AjouterCat(struct categorie *c,int *nbcat )
{
    struct categorie cat;
    int nv_cat=1;

    if(*nbcat<20)
    {
        initcat(&cat);
    }

    for(int i=0;i<*nbcat;i++)
    {
        if(cat.idcat== (c+i)->idcat)
        {printf(" categorie exsite Deja ! \n\n");
        nv_cat=0;}
    }

    if(nv_cat==1){
        (c+*nbcat)->idcat= cat.idcat;
         strcpy((c+*nbcat)->nomcat,cat.nomcat);
        *nbcat=*nbcat+1;
    }

}

void Ajoutertype (struct type *t,int *nbtyp,struct categorie c[],int nbcat)
{
    struct type typ;
    int nv_typ=1;
    int i_cat=-1;

    if(*nbtyp<50)
    {
        inittype(&typ);
    }

    for(int i=0;i<*nbtyp;i++)
    {
        if(typ.idtype == (t+i)->idtype)
        {
        nv_typ=0;
        printf(" type existe deja \n\n ");
        }
    }

      for(int i=0;i<=nbcat;i++)
    {
        if(c[i].idcat == typ.cat.idcat)
        {
            i_cat=i;
        }
    }
    if(i_cat==-1){printf("categorie inseret n exist pas \n\n ");}

    if(nv_typ==1 && i_cat!=-1){
        (t+*nbtyp)->idtype = typ.idtype;
        strcpy((t+*nbtyp)->nomtype,typ.nomtype);
        (t+*nbtyp)->cat.idcat = c[i_cat].idcat;
        strcpy((t+*nbtyp)->cat.nomcat,c[i_cat].nomcat);

        *nbtyp=*nbtyp+1;
    }

}

void AjouterPdt ( struct produit p[100][50], int tabqte[], struct type t[] , int nbtyp)
{
    struct produit nv_p;
    int nv_pd=-1;
    int i_type=-1;
    int qte;
    int ligne;

    initpdt(&nv_p);

  for(int i=0;i<50;i++)
    {
        for(int j=0;j<100;j++)
        {
            if(nv_p.id == p[i][j].id)
            {
                nv_pd=0;
                printf(" le produit exsist deja \n");
            }
        }
    }
   if(nv_pd==-1){
    for(int i=0;i<nbtyp;i++)
    {
        if(nv_p.typ.idtype == t[i].idtype)
        {
            nv_pd=1;
            i_type=i;
        }
    }
    if(nv_pd==-1){printf("le type de produit inseret n exsist pas ! \n");}
    }

   if(nv_pd==1)
    {
        tabqte[i_type]=tabqte[i_type]+1;
        ligne=tabqte[i_type];
        p[ligne-1][i_type]=nv_p;
        strcpy(p[ligne-1][i_type].typ.nomtype,t[i_type].nomtype);
        p[ligne-1][i_type].typ.cat.idcat=t[i_type].cat.idcat;
        strcpy(p[ligne-1][i_type].typ.cat.nomcat,t[i_type].cat.nomcat);

    }
}

void SupprimerCat(struct categorie c[],int *nbcat,struct type t[] , int nbtyp)
{
    int id_cat;
    int sup_cat=0;
    int index;

    printf(" tapez ID de categorie a supprimer \n");
    scanf("%d",&id_cat);

    for(int i=0;i<*nbcat;i++)
    {
        if(id_cat == c[i].idcat)
        {

        sup_cat=2;
        index=i;
        }
    }

        for(int j=0;j<nbtyp;j++)
        {
            if(id_cat==t[j].cat.idcat){
                sup_cat=1;
            }
        }

    if(sup_cat==2)
    {
        for(int i = index ; i < *nbcat ;i++)
        {
            c[i]=c[i+1];
        }
        *nbcat=*nbcat-1;
    }
    else if(sup_cat==0){
        printf("le categorie inseret n exsit pas \n ");
    }
    else if(sup_cat== 1)
    {
        printf(" Categorie non supprimer type produit continet cette categorie \n ");
    }


}

void Supprimertype(struct type t[],int *nbtyp, struct produit p[100][50],int tabqte[])
{
    int id_typ;
    int sup_typ=0;
    int index;

    printf(" tapez ID de Type a supprimer \n");
    scanf("%d",&id_typ);

    for(int i=0;i<*nbtyp;i++)
    {
        if(id_typ == t[i].idtype)
        {

        sup_typ=2;
        index=i;
        }
    }

        for(int c=0;c<*nbtyp;c++)
        {
            for(int l=0;l<=tabqte[c];l++)
            {

            if(id_typ == p[l][c].typ.idtype)
                {
                sup_typ = 1;
                }
            }
        }

    if(sup_typ==2)
    {
         for(int i = index ; i < *nbtyp ;i++)
            {
                t[i]=t[i+1];
                tabqte[i]=tabqte[i+1];
            }
        for(int l=0 ; l<100;l++)
            {
                for(int c=index;c<*nbtyp;c++)
                {
                   p[l][c]=p[l][c+1];
                }
            }


        *nbtyp=*nbtyp-1;
    }
    else if(sup_typ==0)
    {
        printf("le type inseret n exsit pas \n ");
    }
    else if(sup_typ== 1)
    {
        printf(" type non supprimer produit continet ce type \n ");
    }


}

void SupprimerPdt(struct produit p[100][50], int tabqte[],int nbtyp)
{
    int sup_p=0;
    int id_p;
    int index_l;
    int index_c;

    printf(" taper l ID de produit \n ");
    scanf("%d",&id_p);

    for(int l=0;l<100;l++)
    {
        for(int c=0;c<nbtyp;c++)
        {
            if(id_p==p[l][c].id)
            {
                sup_p=2;
                index_l=l;
                index_c=c;
                if(tabqte[index_c]<1) // < 10
                {
                    sup_p=1;
                }
            }
        }
    }

    if(sup_p==2){
        for(int i=index_l;i<tabqte[index_c];i++)
        {
            p[i][index_c]=p[i+1][index_c];
        }
    tabqte[index_c]=tabqte[index_c]-1;
    }
    else if(sup_p==0){
        printf(" le produit n exsist pas \n ");
    }
    else if(sup_p==1){
        printf(" produit non supprimet la Qte < 1 \n");
    }

}

void VendrePdt(struct produit p[100][50], int tabqte[],struct type t[],int nbtyp)
{
    int vent_p=0;
    int typ_p;
    int index_l=0;
    int l;
    int index_c;
    struct produit p1;
    FILE *f;
    int  jour, mois, an;
    time_t now;
      time(&now);
    mois=localtime(&now)->tm_mon+1;
    jour=localtime(&now)->tm_mday;
    an=localtime(&now)->tm_year+1900;



    printf(" taper l ID de type produit a vendre \n ");
    scanf("%d",&typ_p);

    for(int i =0;i < nbtyp;i++)
    {
        if(typ_p == t[i].idtype)
        {
          vent_p=2;
          index_c=i;
          if(tabqte[i]<=0){vent_p=1;}
        }
    }



    if(vent_p==2)
    {
        p1=p[0][index_c];
        for( l =0;l<tabqte[index_c];l++)
        {
            if(((p1.date_exp.jj)+(p1.date_exp.mm*31)+(p1.date_exp.aa*365)) > (p[l][index_c].date_exp.jj)+(p[l][index_c].date_exp.mm*31)+(p[l][index_c].date_exp.aa*365)){
                p1=p[l][index_c];
                index_l=l;

            }
        }

        f=fopen("Trace.txt","a");
        fprintf(f,"%03d %s %02d %s %02d %s %02d/%02d/%d\n",p[index_l][index_c].id,p[index_l][index_c].nom,p[index_l][index_c].typ.idtype,p[index_l][index_c].typ.nomtype , p[index_l][index_c].typ.cat.idcat , p[index_l][index_c].typ.cat.nomcat,jour,mois,an);
        fclose(f);

        for(int i=index_l;i<tabqte[index_c];i++)
        {
            p[i][index_c]=p[i+1][index_c];
        }
        tabqte[index_c]=tabqte[index_c]-1;


    }

    else if(vent_p==0){
        printf(" le type n exsist pas \n ");
    }
    else if(vent_p==1){
        printf(" pas de Qte pour ce type \n");
    }
}

void StatMois()
{
    int mois_v,an_v;
    struct produit p;
    int jour,mois,an;
    FILE *f;
    struct categorie c[20]={0};;
    int tabqte[20]={0};
    int n=0;
    int inset_cat=1;
    int s=0;

    do{
    printf("donner le mois de vente \n");
    scanf("%d",&mois_v);
    }while(mois_v < 1 || mois_v >12);

    do{
        printf("donner l annee de vente \n");
        scanf("%d",&an_v);
    }while(an_v<1900 || an_v>9999);

    system("@cls||clear");

    f=fopen("Trace.txt","r");
    if (!f)
    {
        printf("\aERREUR: Impossible d'ouvrir "),
        exit(-1);
    }
    while(!feof(f)){

        fscanf(f,"%d %s %d %s %d %s %d/%d/%d\n",&p.id,p.nom,&p.typ.idtype,p.typ.nomtype,&p.typ.cat.idcat, p.typ.cat.nomcat,&jour,&mois,&an);


        if(mois_v==mois && an_v==an)
        {
            for(int i=0;i<n ;i++)
                {
                    if(p.typ.cat.idcat == c[i].idcat){inset_cat=0; tabqte[i]=tabqte[i]+1;}
                }
            if(inset_cat==1)
            {
                    c[n].idcat=p.typ.cat.idcat;
                    strcpy(c[n].nomcat,p.typ.cat.nomcat);
                    tabqte[n]=tabqte[n]+1;
                    n++;
            }
        }
       inset_cat=1;
    }

    printf("\n     statistique du %02d/%d \n",mois_v,an_v);
    printf("\n *-nbr des ventes mensuelles par categorie \n\n");
    printf(" *-Categories :    ");
    for(int i=0;i<n;i++)
    {
        printf("%02d ",c[i].idcat);

    }
    printf("\n");
    printf(" *-Qte de Ventes : ");
       for(int i=0;i<n;i++)
    {
        printf("%02d ",tabqte[i]);
    }
    printf("\n\n");
    printf(" *- Total des Ventes : ");
       for(int i=0;i<n;i++)
    {

        s=s+tabqte[i];
    }
    printf("%03d \n ",s);
    printf("\n\n\n");
    fclose(f);

}

void StatAnnee()
{
    int an_v;
    struct produit p;
    int jour,mois,an;
    FILE *f;
    struct categorie c[20]={0};;
    int tabqte[20]={0};
    int n=0;
    int inset_cat=1;
    int s=0;

    do{
        printf("donner l annee de vente \n");
        scanf("%d",&an_v);
    }while(an_v<1900 || an_v>9999);

    system("@cls||clear");

    f=fopen("Trace.txt","r");
    if (!f)
    {
        printf("\aERREUR: Impossible d'ouvrir "),
        exit(-1);
    }
    while(!feof(f)){

        fscanf(f,"%d %s %d %s %d %s %d/%d/%d\n",&p.id,p.nom,&p.typ.idtype,p.typ.nomtype,&p.typ.cat.idcat, p.typ.cat.nomcat,&jour,&mois,&an);


        if(an_v==an)
        {
            for(int i=0;i<n ;i++)
                {
                    if(p.typ.cat.idcat == c[i].idcat){inset_cat=0; tabqte[i]=tabqte[i]+1;}
                }
            if(inset_cat==1)
            {
                    c[n].idcat=p.typ.cat.idcat;
                    strcpy(c[n].nomcat,p.typ.cat.nomcat);
                    tabqte[n]=tabqte[n]+1;
                    n++;
            }
        }
       inset_cat=1;
    }

    printf("\n     statistique du %d \n",an_v);
    printf("\n *-nbr des ventes annuelles par categorie \n\n");
    printf(" *-Categories :    ");
    for(int i=0;i<n;i++)
    {
        printf("%02d ",c[i].idcat);

    }
    printf("\n");
    printf(" *-Qte de Ventes : ");
       for(int i=0;i<n;i++)
    {
        printf("%02d ",tabqte[i]);
    }
    printf("\n\n");
    printf(" *- Total des Ventes : ");
       for(int i=0;i<n;i++)
    {

        s=s+tabqte[i];
    }
    printf("%03d \n ",s);
    printf("\n\n\n");
    fclose(f);
}
int main()
{
    struct categorie tabcat[20];
    struct type tabtype[50];
    int tabqte[50]={0};
    struct produit stock[100][50];
    int nbcat=0;
    int nbtyp=0;
    struct produit p;
    int o;
    int o1;
    int o2;


while(1)
{
    menu:
do{
    printf("\n\t\t\t\t*************************************************************\n");
    printf("\t\t\t\t*******************      Welcom     *************************\n");
    printf("\t\t\t\t*************************************************************\n");
    printf("\t\t\t\t* Veuillez choisir une option                               *\n");
    printf("\t\t\t\t* 1- Tapez [1] pour Gestion du Stock                        *\n");
    printf("\t\t\t\t* 2- Tapez [2] pour Vente et Statestique                    *\n");
    printf("\t\t\t\t* 3- Tapez [0] pour quitter                                 *\n");
    scanf("%d",&o);
    system("@cls||clear");

}while(o<0 || o>2);

if(o==1)
    {
        option1:
    do{
    printf("\n\t\t\t\t***************************************************************\n");
    printf("\t\t\t\t* 1- Tapez [1] pour Afficher le Stock                         *\n");
    printf("\t\t\t\t* 2- Tapez [2] pour Ajuter categorie                          *\n");
    printf("\t\t\t\t* 3- Tapez [3] pour Ajouter type                              *\n");
    printf("\t\t\t\t* 4- Tapez [4] pour Ajouter produit                           *\n");
    printf("\t\t\t\t* 5- Tapez [5] pour Suprimer categorie                        *\n");
    printf("\t\t\t\t* 6- Tapez [6] pour Supprimer type                            *\n");
    printf("\t\t\t\t* 7- Tapez [7] pour Supprimer Produit                         *\n");
    printf("\t\t\t\t* 8- Tapez [8] pour retourner vers menu                       *\n");
    printf("\t\t\t\t* 9- Tapez [0] pour quitter                                   *\n");
    scanf("%d",&o1);
    system("@cls||clear");

    }while(o1<0 || o1> 8);

         if(o1==1){ afficherStock(stock,tabqte,nbtyp,tabtype); goto option1;      }
    else if(o1==2){ AjouterCat(tabcat,&nbcat );   goto option1;                  }
    else if(o1==3){ Ajoutertype(tabtype,&nbtyp,tabcat,nbcat);    goto option1;   }
    else if(o1==4){ AjouterPdt(stock,tabqte,tabtype,nbtyp); goto option1;        }
    else if(o1==5){ SupprimerCat(tabcat,&nbcat,tabtype,nbtyp); goto option1;     }
    else if(o1==6){ Supprimertype(tabtype,&nbtyp,stock,tabqte); goto option1;    }
    else if(o1==7){ SupprimerPdt(stock,tabqte,nbtyp); goto option1;              }
    else if(o1==8){ system("@cls||clear"); goto menu;                            }
    else if(o1==0){ exit(-1);                                                    }
}


else if(o==2)
{
      option2:
    do{
    printf("\n\t\t\t\t***************************************************************\n");
    printf("\t\t\t\t* 1- Tapez [1] Vendre Produit                                 *\n");
    printf("\t\t\t\t* 2- Tapez [2] statistiques des ventes mensuelles             *\n");
    printf("\t\t\t\t* 3- Tapez [3] statistiques des ventes annuelle               *\n");
    printf("\t\t\t\t* 4- Tapez [4] pour retourner vers menu                       *\n");
    printf("\t\t\t\t* 5- Tapez [5] pour quitter                                   *\n");
    scanf("%d",&o2);
    system("@cls||clear");
    }while(o2<0 || o2 > 5);

         if(o2==1){ VendrePdt(stock,tabqte,tabtype,nbtyp); goto option2;         }
    else if(o2==2){ StatMois();   goto option2;                                  }
    else if(o2==3){ StatAnnee();  goto option2;                                            }
    else if(o2==4){ system("@cls||clear"); goto menu;                            }
    else if(o2==5){ exit(-1);                                                    }
}
else if(o==0)
{
    exit(-1);
}

}
}

