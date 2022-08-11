#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int n=0,vezes=0;
float monta=0;
char Nome[20],nome_ficheiro[20],nome_ficheiro2[20];
int nume,Pin;
float din;

struct cliente{
    char nome[20];
    int numero_conta;
    int pin;
    float montante;

}clientes[50];

struct dc{
    char nome[20];
    int numero_conta;
    int pin;
    float montante;
}dcs[50];

criacliente(){
    FILE *f;
    int temp=n,x,y;
    cli:
        printf("Quantos Clientes pretende criar?\n");
        scanf("%i",&y);
        fflush(stdin);
        if(temp+y>50){
            printf("Só pode criar mais %i registros\n",50-temp);
            goto cli;
        }
    n=temp+y;
    fflush(stdin);
    for(x=temp;x<n;x++){
        printf("Insira o nome do cliente\n");
        gets(clientes[x].nome);
        printf("Insira o número da conta (6 dígitos)\n");
        scanf("%i",&clientes[x].numero_conta);
        if(clientes[x].numero_conta<=100000 || clientes[x].pin>=999999)
            printf("Insira um número de 6 digitos entra 100000 e 999999");
        printf("Insira o pin da conta (4 dígitos)\n");
        scanf("%i",&clientes[x].pin);
        if(clientes[x].pin<=1000 || clientes[x].pin>=9999)
            printf("Insira um pin de 4 digitos entra 1000 e 9999");
        printf("Insira o montante da conta\n");
        scanf("%f",&clientes[x].montante);
        fflush(stdin);
    }

    for(x=temp;x<n;x++){
        if((f=fopen("contas.txt","a"))==NULL){
            printf("Erro ao criar o ficheiro\n");
        }else{
            fprintf(f,"%s | %i | %i | %.2f\n",clientes[x].nome, clientes[x].numero_conta, clientes[x].pin, clientes[x].montante);
        }
    }
    fclose(f);

}

logincliente(){
    FILE *f,*fp;
    int i,x,nu,pi,num,pin,soma=0,cont=0,cont2=0;
    float mont;
    char nome[20],numero[20];
    conta:
    printf("Insira o número da sua conta\n");
    scanf("%i",&nu);
    printf("Insira o pin da sua conta\n");
    scanf("%i",&pi);
    if((f=fopen("contas.txt","r"))==NULL){
        printf("Erro ao tentar abrir o ficheiro\n");
    }else{
        while ((fscanf(f, "%s | %i | %i | %f",nome,&num,&pin,&mont))!=EOF) {
            if(nu==num){
                cont2++;
                if(pi==pin){
                    monta=mont;
                    cont++;
                    strcpy(Nome,nome);
                    nume=num;
                    Pin=pin;
                    din=mont;
                    itoa(num,numero,10);
                    strcpy(nome_ficheiro,numero);
                    strcat(nome_ficheiro,".txt");
                    menu2();
                }
            }
        }
        if(cont==0){
            printf("Pin incorreto\n");
            goto conta;
        }
        else if(cont2==0){
            printf("Número de conta incorreto\n");
            goto conta;
            }
    }

    if((fp=fopen(nome_ficheiro,"a+"))==NULL){
       printf("Erro ao tentar abrir o ficheiro\n");
    }else{
        rewind(fp);
        soma=0;
        while((i=fgetc(fp))!=EOF){
            if(fgetc(fp)==' ')
                soma++;
        }
        if(soma==0)
            fprintf(fp,"%s | %i |%i\n",Nome,nume,Pin);
    }
    fclose(fp);
    fclose(f);
}
menu2(){
    FILE *f;
    int op,x,num,pin;
    float mont;
    char nome[20];
    if((f=fopen("contas.txt","r"))==NULL){
        printf("Erro ao tentar abrir o ficheiro\n");
    }else{
        for(x=0;x<n;x++){
            if((fscanf(f, "%s | %i | %i | %f",nome,&num,&pin,&mont))!=EOF){
                    strcpy(dcs[x].nome,nome);
                    dcs[x].numero_conta=num;
                    dcs[x].pin=pin;
                    dcs[x].montante=mont;
            }
        }
    }
    fclose(f);
    printf("-------Menu do Cliente-------\n");
    printf("1- Consultas\n");
    printf("2- Depósitos\n");
    printf("3- Levantamentos\n");
    printf("4- Transferências\n");
    printf("5- Voltar para o menu inicial\n");
    printf("6- Sair\n");
    printf("Escolha uma opção\n");
    scanf("%i",&op);
    switch(op){
        case 1: consultas();
                break;
        case 2: depositos();
                break;
        case 3: levantamentos();
                break;
        case 4: transferencias();
                break;
        case 5: main();
                break;
        case 6: break;
    }
}
consultas(){
    FILE *f1;
    int i;
    if((f1=fopen(nome_ficheiro,"r"))==NULL){
        printf("Erro ao criar o ficheiro\n");
    }else{
            while((i=fgetc(f1))!=EOF){
                printf("%c",i);
            }
    }
    fclose(f1);
    printf("O seu saldo atual é: %.2f\n",din);
    menu2();
}

int depositos(){
    FILE *f,*fp;
    int x,num,pin;
    float d,mont;
    char nome[20];
    printf("Quanto dinheiro deseja depositar?\n");
    scanf("%f",&d);
    if((f=fopen("contas.txt","r"))==NULL){
        printf("Erro ao tentar abrir o ficheiro\n");
    }else{
        for(x=0;x<n;x++){
            if((fscanf(f, "%s | %i | %i | %f",nome,&num,&pin,&mont))!=EOF)
                    if(nume==num){
                        din=din+d;
                        dcs[x].montante=din;
                    }
            }
        }
    fclose(f);
    if((fp=fopen(nome_ficheiro,"a"))==NULL){
       printf("Erro ao tentar abrir o ficheiro\n");
    }else{
        fprintf(fp,"Depósito: +%.2f Euros\n",d);
    }
    fclose(fp);
    if((f=fopen("contas.txt","w"))==NULL){
        printf("Erro ao tentar abrir o ficheiro\n");
    }else{
        for(x=0;x<n;x++){
            fprintf(f,"%s | %i | %i | %.2f\n",dcs[x].nome, dcs[x].numero_conta, dcs[x].pin, dcs[x].montante);
        }
    }
    fclose(f);
    menu2();
}

int levantamentos(){
    FILE *f,*fp;
    int x,num,pin;
    float d,mont;
    char nome[20];
    int op;
    le:
    printf("-------Levantamentos-------\n");
    printf("1- 20 Euros\n");
    printf("2- 50 Euros\n");
    printf("3- 100 Euros\n");
    printf("4- 150 Euros\n");
    printf("5- 200 Euros\n");
    printf("6- Outras importâncias\n");
    printf("7- Voltar para o Menu do Cliente\n");
    printf("Escolha uma opção\n");
    scanf("%i",&op);
    switch(op){
        case 1: if((f=fopen("contas.txt","r"))==NULL){
                    printf("Erro ao tentar abrir o ficheiro\n");
                }else{
                    for(x=0;x<n;x++){
                        if((fscanf(f, "%s | %i | %i | %f",nome,&num,&pin,&mont))!=EOF)
                            if(nume==num){
                                din=din-20;
                                dcs[x].montante=din;
                            }
                    }
                }
                fclose(f);
                if((fp=fopen(nome_ficheiro,"a"))==NULL){
                    printf("Erro ao tentar abrir o ficheiro\n");
                }else{
                    fprintf(fp,"Levantamento: -20,00 Euros\n");
                }
                fclose(fp);
                if((f=fopen("contas.txt","w"))==NULL){
                    printf("Erro ao tentar abrir o ficheiro\n");
                }else{
                    for(x=0;x<n;x++){
                    fprintf(f,"%s | %i | %i | %.2f\n",dcs[x].nome, dcs[x].numero_conta, dcs[x].pin, dcs[x].montante);
                    }
                }
                fclose(f);
                goto le;
                break;
        case 2: if((f=fopen("contas.txt","r"))==NULL){
                    printf("Erro ao tentar abrir o ficheiro\n");
                }else{
                    for(x=0;x<n;x++){
                        if((fscanf(f, "%s | %i | %i | %f",nome,&num,&pin,&mont))!=EOF)
                            if(nume==num){
                                din=din-50;
                                dcs[x].montante=din;
                            }
                    }
                }
                fclose(f);
                if((fp=fopen(nome_ficheiro,"a"))==NULL){
                    printf("Erro ao tentar abrir o ficheiro\n");
                }else{
                    fprintf(fp,"Levantamento: -50,00 Euros\n");
                }
                fclose(fp);
                if((f=fopen("contas.txt","w"))==NULL){
                    printf("Erro ao tentar abrir o ficheiro\n");
                }else{
                    for(x=0;x<n;x++){
                    fprintf(f,"%s | %i | %i | %.2f\n",dcs[x].nome, dcs[x].numero_conta, dcs[x].pin, dcs[x].montante);
                    }
                }
                fclose(f);
                goto le;
                break;
        case 3: if((f=fopen("contas.txt","r"))==NULL){
                    printf("Erro ao tentar abrir o ficheiro\n");
                }else{
                    for(x=0;x<n;x++){
                        if((fscanf(f, "%s | %i | %i | %f",nome,&num,&pin,&mont))!=EOF)
                            if(nume==num){
                                din=din-100;
                                dcs[x].montante=din;
                            }
                    }
                }
                fclose(f);
                if((fp=fopen(nome_ficheiro,"a"))==NULL){
                    printf("Erro ao tentar abrir o ficheiro\n");
                }else{
                    fprintf(fp,"Levantamento: -100 Euros\n");
                }
                fclose(fp);
                if((f=fopen("contas.txt","w"))==NULL){
                    printf("Erro ao tentar abrir o ficheiro\n");
                }else{
                    for(x=0;x<n;x++){
                    fprintf(f,"%s | %i | %i | %.2f\n",dcs[x].nome, dcs[x].numero_conta, dcs[x].pin, dcs[x].montante);
                    }
                }
                fclose(f);
                goto le;
                break;
        case 4: if((f=fopen("contas.txt","r"))==NULL){
                    printf("Erro ao tentar abrir o ficheiro\n");
                }else{
                    for(x=0;x<n;x++){
                        if((fscanf(f, "%s | %i | %i | %f",nome,&num,&pin,&mont))!=EOF)
                            if(nume==num){
                                din=din-150;
                                dcs[x].montante=din;
                            }
                    }
                }
                fclose(f);
                if((fp=fopen(nome_ficheiro,"a"))==NULL){
                    printf("Erro ao tentar abrir o ficheiro\n");
                }else{
                    fprintf(fp,"Levantamento: -150 Euros\n");
                }
                fclose(fp);
                if((f=fopen("contas.txt","w"))==NULL){
                    printf("Erro ao tentar abrir o ficheiro\n");
                }else{
                    for(x=0;x<n;x++){
                    fprintf(f,"%s | %i | %i | %.2f\n",dcs[x].nome, dcs[x].numero_conta, dcs[x].pin, dcs[x].montante);
                    }
                }
                fclose(f);
                goto le;
                break;
        case 5: if((f=fopen("contas.txt","r"))==NULL){
                    printf("Erro ao tentar abrir o ficheiro\n");
                }else{
                    for(x=0;x<n;x++){
                        if((fscanf(f, "%s | %i | %i | %f",nome,&num,&pin,&mont))!=EOF)
                            if(nume==num){
                                din=din-200;
                                dcs[x].montante=din;
                            }
                    }
                }
                fclose(f);
                if((fp=fopen(nome_ficheiro,"a"))==NULL){
                    printf("Erro ao tentar abrir o ficheiro\n");
                }else{
                    fprintf(fp,"Levantamento: -200 Euros\n");
                }
                fclose(fp);
                if((f=fopen("contas.txt","w"))==NULL){
                    printf("Erro ao tentar abrir o ficheiro\n");
                }else{
                    for(x=0;x<n;x++){
                    fprintf(f,"%s | %i | %i | %.2f\n",dcs[x].nome, dcs[x].numero_conta, dcs[x].pin, dcs[x].montante);
                    }
                }
                fclose(f);
                goto le;
                break;
        case 6: pe:
                printf("Quanto dinheiro deseja depositar?\n");
                scanf("%f",&d);
                if(d<=0 || d>200){
                    printf("Quantia invalida, insira um número entre 0 e 200 euros\n");
                    goto pe;
                }else if((int)d%5==0){
                    printf("Quantia invalida, insira um número divisível por 5\n");
                    goto pe;
                }else{
                    if((f=fopen("contas.txt","r"))==NULL){
                    printf("Erro ao tentar abrir o ficheiro\n");
                    }else{
                        for(x=0;x<n;x++){
                            if((fscanf(f, "%s | %i | %i | %f",nome,&num,&pin,&mont))!=EOF)
                                if(nume==num){
                                    din=din-d;
                                    dcs[x].montante=din;
                                }
                        }
                    }
                    fclose(f);
                    if((fp=fopen(nome_ficheiro,"a"))==NULL){
                        printf("Erro ao tentar abrir o ficheiro\n");
                    }else{
                        fprintf(fp,"Levantamento: -%.2f Euros\n",d);
                    }
                    fclose(fp);
                    if((f=fopen("contas.txt","w"))==NULL){
                        printf("Erro ao tentar abrir o ficheiro\n");
                    }else{
                        for(x=0;x<n;x++){
                        fprintf(f,"%s | %i | %i | %.2f\n",dcs[x].nome, dcs[x].numero_conta, dcs[x].pin, dcs[x].montante);
                        }
                    }
                    fclose(f);
                    goto le;
                }
                break;
        case 7: menu2();
                break;
    }

}

int transferencias(){
    FILE *f,*fp,*fp2;
    int x,z,num,pin;
    float d,mont;
    char nome[20],numero[20];
    printf("Quanto dinheiro deseja transferir?\n");
    scanf("%f",&d);
    printf("Insira o número da conta para a qual quer transferia a quantia?\n");
    scanf("%i",&z);
    itoa(z,numero,10);
    strcpy(nome_ficheiro2,numero);
    strcat(nome_ficheiro2,".txt");
    if((f=fopen("contas.txt","r"))==NULL){
        printf("Erro ao tentar abrir o ficheiro\n");
    }else{
        for(x=0;x<n;x++){
            if((fscanf(f, "%s | %i | %i | %f",nome,&num,&pin,&mont))!=EOF)
                    if(nume==num){
                        din=din-d;
                        dcs[x].montante=din;
                    }
            }
        }
    fclose(f);
     if((fp=fopen(nome_ficheiro,"a+"))==NULL){
        printf("Erro ao tentar abrir o ficheiro\n");
    }else{
        fprintf(fp,"Transferência para %i: -%.2f Euros\n",z,d);
        }
    fclose(fp);
    if((f=fopen("contas.txt","r"))==NULL){
        printf("Erro ao tentar abrir o ficheiro\n");
    }else{
        for(x=0;x<n;x++){
            if((fscanf(f, "%s | %i | %i | %f",nome,&num,&pin,&mont))!=EOF)
                    if(z==num){
                        dcs[x].montante=dcs[x].montante+d;
                    }
            }
        }
    fclose(f);
    if((fp2=fopen(nome_ficheiro2,"a+"))==NULL){
        printf("Erro ao tentar abrir o ficheiro\n");
    }else{
        fprintf(fp,"Transferência de %i: +%.2f Euros\n",nume,d);
        }
    fclose(fp2);
    if((f=fopen("contas.txt","w"))==NULL){
        printf("Erro ao tentar abrir o ficheiro\n");
    }else{
        for(x=0;x<n;x++){
            fprintf(f,"%s | %i | %i | %.2f\n",dcs[x].nome, dcs[x].numero_conta, dcs[x].pin, dcs[x].montante);
        }
    }
    fclose(f);
    menu2();
}

int main()
{
    n=0;
    setlocale(LC_ALL, "Portuguese");
    int op,i;
    FILE *f;
    if((f=fopen("contas.txt","r"))==NULL){
        printf("Erro ao tentar abrir o ficheiro\n");
    }else{
            while((i=fgetc(f))!=EOF){
                if(i=='\n')
                    vezes++;
                if(vezes==1){
                    n++;
                    vezes=0;
                }
            }
                printf("Já existem %i contas registadas\n",n);
    }
    fclose(f);
    inicio:
    printf("-------Menu-------\n");
    printf("1- Criar Cliente\n");
    printf("2- Login Cliente\n");
    printf("3- Sair\n");
    printf("Escolha uma opção\n");
    scanf("%i",&op);
    switch(op){
        case 1: criacliente();
                goto inicio;
                break;
        case 2: logincliente();
                break;
        case 3: break;
    }
    return 0;
}
