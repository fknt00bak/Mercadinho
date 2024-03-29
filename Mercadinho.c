#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define RGSTRS "REGISTROS"

struct DadosDoProduto
{
    int codigo;
    int codigo2;
    char nome[72];
    char descricao[420];
    char lote[36];
    float valor;
    int unidades;
    int dia, mes, ano;
};
// struct DadosDoProduto dados;
// struct DadosDoProduto dados2;
// struct DadosDoProduto dados3;
struct DadosDoProduto produto;
struct DadosDoProduto produto_2;
struct DadosDoProduto produto_3;


struct DataEHorario
{
    int dia, mes, ano;
    int horas, minutos, segundos;
};
// struct DataEHorario data_e_horario;
struct DataEHorario data;
struct DataEHorario horario;


struct Validade
{
    int dia, mes, ano;
};
struct Validade validade;


bool verificarData(int dia, int mes, int ano)
{
    if(ano >= 1900 && ano <= 2200)
    {
        if(dia > 0 && dia <= 31 &&(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12))
            return true;
        if(dia > 0 && dia <= 30 && (mes == 4 || mes == 6 || mes == 9 || mes == 11))
            return true;
        if(mes == 2 && (dia > 0 && dia <= 29 && ano % 4 == 0 && (ano %400 == 0 || ano % 100 != 0)))
            return true;
        if(mes == 2 && (dia > 0 && dia <= 28))
            return true;
        else
            return false;
    }
    else
        return false;
}

int dataDeValidade(char alternativa)
{
    int dia, mes, ano;

    if((alternativa == 'n') || (alternativa == 'N'))
    {
        validade.dia = 0;
        validade.mes = 0;
        validade.ano = 0;
        return 0;
    }

    else if((alternativa == 's') || (alternativa == 'S'))
    {
        printf("INFORME A DATA DE VALIDADE:\n");
        scanf("%d %d %d", &dia, &mes, &ano);

        if(verificarData(dia, mes, ano) == true)
        {
            validade.dia = dia;
            validade.mes = mes;
            validade.ano = ano;
        }

        else if((alternativa == 's') || (alternativa == 'S'))
        {
            system("cls");
            printf("DATA INVÁLIDA!\nIMFORME NOVAMENTE.\n\n");
            system("pause");
            system("cls");

            printf("INFORME A DATA DE VALIDADE:\n");
            scanf("%d %d %d", &dia, &mes, &ano);
            printf("\n");

            if(verificarData(dia, mes, ano) == true)
            {
                validade.dia = dia;
                validade.mes = mes;
                validade.ano = ano;
            }

            else
            {
                system("cls");
                printf("DATA INVÁLIDA!\nIMFORME NOVAMENTE.\n\n");
                system("pause");
                system("cls");
                dataDeValidade(alternativa);
            }
        }
    }

    else
        return 0;

return 0;
}

void obterDataEHorario()
{
    struct tm *local;
    time_t t;
    t = time(NULL);
    local=localtime(&t);

    data.ano = local -> tm_year+1900;
    data.mes = local -> tm_mon+1;
    data.dia = local -> tm_mday;
    horario.horas = local -> tm_hour;
    horario.minutos = local -> tm_min;
    horario.segundos = local -> tm_sec;
}

int listar(FILE *arquivo)
{
    if(arquivo == NULL)
    {
        printf("\nNÃO FORAM ENCONTRADOS DADOS NOS REGISTROS.\n\n");
        return 0;
    }

    while(!feof(arquivo))
    {
        fscanf(arquivo, "%d\n", &produto.codigo);
        fflush(stdin);
        fscanf(arquivo, "%d\n", &produto.codigo2);
        fflush(stdin);
        fgets(produto.nome, 40, arquivo);
        fgets(produto.descricao, 250, arquivo);
        fflush(stdin);
        fgets(produto.lote, 20, arquivo);
        fflush(stdin);
        fscanf(arquivo, "%f\n", &produto.valor);
        fflush(stdin);
        fscanf(arquivo, "%d\n", &produto.unidades);
        fflush(stdin);
        fscanf(arquivo, "%d %d %d", &validade.dia, &validade.mes, &validade.ano);
        fflush(stdin);

        if(produto.codigo2 != 0)
            fscanf(arquivo, "%d %d %d %d %d %d\n", &data.dia, &data.mes, &data.ano, &horario.horas, &horario.minutos, &horario.segundos);

        else
            fscanf(arquivo, "\n");

        fflush(stdin);

        if(produto.codigo2 == 0)
        {
            printf("CÓDIGO DO PRODUTO:\tEST%d\n", produto.codigo);
        }
        else if(produto.codigo2 != 0)
        {
            printf("CÓDIGO DO PRODUTO:\tEST%d\n", produto.codigo);
            printf("NOTA FISCAL:\t\tVND%d\n", produto.codigo2);
        }

        fflush(stdout);
        printf("NOME:\t\t\t%s", produto.nome);
        printf("DESCRIÇÃO:\t\t%s", produto.descricao);
        printf("LOTE:\t\t\t%s", produto.lote);

        if(produto.codigo2 == 0)
        {
            printf("VALOR UNITÁRIO:\t\tR$%.2f\n", produto.valor);
            printf("UNIDADES DISPONÍVEIS:\t%d\n", produto.unidades);
        }
        else if(produto.codigo2 != 0)
        {
            printf("VALOR TOTAL:\t\tR$%.2f\n", produto.valor);
            printf("UNIDADES VENDIDAS:\t%d\n", produto.unidades);
        }


        if(validade.dia == 0)
        {
            printf("DATA DE VALIDADE:\tNÃO POSSUI.\n");
        }
        else
        {
            printf("DATA DE VALIDADE:\t%02d/%02d/%04d\n", validade.dia, validade.mes, validade.ano);
        }

        if(produto.codigo2 == 0)
        {
            printf("\n\n");
        }
        else if(produto.codigo2 != 0)
        {
            printf("HORARIO DA VENDA:\t%02d:%02d:%02d\n", horario.horas, horario.minutos, horario.segundos);
            printf("DATA DA VENDA:\t\t%02d/%02d/%04d\n\n\n", data.dia, data.mes, data.ano);
        }
    }

    fclose(arquivo);
}

int codigoDaVenda()
{
    int codVnd = 8210870;
    FILE *codigoVnd;
    codigoVnd = fopen("CdgoVnd.txt", "r+");

    if(codigoVnd == NULL)
    {
        codigoVnd = fopen("CdgoVnd.txt", "w+");
        fprintf(codigoVnd, "%d", codVnd);
        fclose(codigoVnd);
        return codVnd;
    }

    else
    {
        int codgVnd;
        fscanf(codigoVnd, "%d", &codgVnd);
        codgVnd++;
        codigoVnd = fopen("CdgoVnd.txt", "w+");
        fprintf(codigoVnd, "%d", codgVnd);
        fclose(codigoVnd);
        return codgVnd;
    }
}

int codigoDoEstoque(int *pont)
{
    int codEst = 4210870;
    FILE *codigoEst;
    codigoEst = fopen("CdgoEst.txt", "r+");

    if(codigoEst == NULL)
    {
        codigoEst = fopen("CdgoEst.txt", "w+");
        fprintf(codigoEst, "%d", codEst);
        fclose(codigoEst);
        *pont = codEst;
        return codEst;
    }

    else
    {
        int codgEst;
        fscanf(codigoEst, "%d", &codgEst);
        codgEst++;
        codigoEst = fopen("CdgoEst.txt", "w+");
        fprintf(codigoEst, "%d", codgEst);
        fclose(codigoEst);
        *pont = codgEst;
        return codgEst;
    }
}

void realocarDadosEstoque()
{
    int a;
    char caractere;

    FILE *origem, *destino;
    destino = fopen("ESTOQUE.txt", "w+");
    origem = fopen("ESTOQUE_3.txt", "r");

   while((caractere = fgetc(origem)) != EOF)
        fputc(caractere, destino);

    fclose(origem);
    fclose(destino);
}

void atualizarEstoque(int unidades, int codigo, int i)
{
    int j;

    FILE *arq, *arq2, *arq3;
    arq = fopen("ESTOQUE_2.txt", "r");
    arq2= fopen("ESTOQUE.txt", "r");
    arq3= fopen("ESTOQUE_3.txt", "w+");

    if(arq != NULL)
    {
        for(j = 0; !feof(arq2); j++)
        {
            fscanf(arq, "%d\n", &produto_2.codigo);
            fflush(stdin);
            fgets(produto_2.nome, 40, arq);
            fgets(produto_2.descricao, 250, arq);
            fflush(stdin);
            fgets(produto_2.lote, 20, arq);
            fflush(stdin);
            fscanf(arq, "%f\n", &produto_2.valor);
            fflush(stdin);
            fscanf(arq, "%d\n", &produto_2.unidades);
            fflush(stdin);
            fscanf(arq, "%d %d %d\n", &produto_2.dia, &produto_2.mes, &produto_2.ano);
            fflush(stdin);

            fscanf(arq2, "%d\n", &produto_3.codigo);
            fflush(stdin);
            fgets(produto_3.nome, 40, arq2);
            fgets(produto_3.descricao, 250, arq2);
            fflush(stdin);
            fgets(produto_3.lote, 20, arq2);
            fflush(stdin);
            fscanf(arq2, "%f\n", &produto_3.valor);
            fflush(stdin);
            fscanf(arq2, "%d\n", &produto_3.unidades);
            fflush(stdin);
            fscanf(arq2, "%d %d %d\n", &validade.dia, &validade.mes, &validade.ano);
            fflush(stdin);

            if(codigo == produto_3.codigo)
            {
                fprintf(arq3, "%d\n", produto_3.codigo);
                fputs(produto_3.nome, arq3);
                fputs(produto_3.descricao, arq3);
                fputs(produto_3.lote, arq3);
                fprintf(arq3, "%.2f", produto_3.valor);
                fprintf(arq3, "\n");
                fprintf(arq3, "%d", produto_3.unidades-unidades);
                fprintf(arq3, "\n");
                fprintf(arq3, "%02d %02d %04d", validade.dia, validade.mes, validade.ano);
                fprintf(arq3, "\n");
            }

            else
            {
                fprintf(arq3, "%d\n", produto_3.codigo);
                fputs(produto_3.nome, arq3);
                fputs(produto_3.descricao, arq3);
                fputs(produto_3.lote, arq3);
                fprintf(arq3, "%.2f", produto_3.valor);
                fprintf(arq3, "\n");
                fprintf(arq3, "%d", produto_3.unidades);
                fprintf(arq3, "\n");
                fprintf(arq3, "%02d %02d %04d", validade.dia, validade.mes, validade.ano);
                fprintf(arq3, "\n");
            }
        }
    }

    fclose(arq);
    fclose(arq2);
    fclose(arq3);

    realocarDadosEstoque();
}

int produtoVendido(int codigo_2, int unidades, int dia, int mes, int ano, int i)
{
    int j = 0;

    FILE *arq, *arq2;
    arq = fopen("ESTOQUE_2.txt", "w+");
    arq2 = fopen("ESTOQUE.txt", "r");

    if(arq2 == NULL)
        return 1;

    for(i = 0; !feof(arq2); i++)
    {
        fscanf(arq2, "%d\n", &produto_3.codigo);
        fflush(stdin);
        fgets(produto_3.nome, 40, arq2);
        fgets(produto_3.descricao, 250, arq2);
        fflush(stdin);
        fgets(produto_3.lote, 20, arq2);
        fflush(stdin);
        fscanf(arq2, "%f\n", &produto_3.valor);
        fflush(stdin);
        fscanf(arq2, "%d\n", &produto_3.unidades);
        fflush(stdin);
        fscanf(arq2, "%d %d %d\n", &validade.dia, &validade.mes, &validade.ano);
        fflush(stdin);

        if(codigo_2 == produto_3.codigo)
        {
            fprintf(arq, "%d\n", produto_3.codigo);
            fputs(produto_3.nome, arq);
            fputs(produto_3.descricao, arq);
            fputs(produto_3.lote, arq);
            fprintf(arq, "%.2f", produto_3.valor);
            fprintf(arq, "\n");
            fprintf(arq, "%d", produto_3.unidades-unidades);
            fprintf(arq, "\n");
            fprintf(arq, "%02d %02d %04d", validade.dia, validade.mes, validade.ano);
            fprintf(arq, "\n");
            return 1;
        }
    }

    fclose(arq2);
    fclose(arq);

return 0;
}

int lerInfoProduto(int codigo_2)
{
    FILE *estoque;
    estoque = fopen("ESTOQUE.txt", "r");

    int i;

    for(i = 0; !feof(estoque); i++)
    {
        fscanf(estoque, "%d\n", &produto_3.codigo);
        fflush(stdin);
        fgets(produto_3.nome, 40, estoque);
        fgets(produto_3.descricao, 250, estoque);
        fflush(stdin);
        fgets(produto_3.lote, 20, estoque);
        fflush(stdin);
        fscanf(estoque, "%f\n", &produto_3.valor);
        fflush(stdin);
        fscanf(estoque, "%d\n", &produto_3.unidades);
        fflush(stdin);
        fscanf(estoque, "%d %d %d\n", &validade.dia, &validade.mes, &validade.ano);
        fflush(stdin);

        if(produto_3.codigo == codigo_2)
            return 1;
    }

return 0;
}

int Vendas()
{
    FILE *estoque, *vendas;
    estoque = fopen("ESTOQUE.txt", "r");

    if(estoque == NULL)
    {
        printf("\nNÃO HÁ PRODUTOS NO ESTOQUE!\n\n");
        return 0;
    }

    fclose(estoque);

    int i = 0, j, codigo_2, unidades, dia, mes, ano;
    char nome[40], descricao[250], lote[20], a, b, c;
    float valor;

    printf("\n\n\t\t\t\t\t[VENDA DE PRODUTOS]\n\n");
    fflush(stdin);
    printf("\nINFORME O CÓDIGO DO PRODUTO:\nEST");
    fflush(stdin);
    scanf("%d", &codigo_2);
    fflush(stdin);
    lerInfoProduto(codigo_2);

    if(produto_3.codigo != codigo_2)
    {
        while(produto_3.codigo != codigo_2)
        {
            printf("\nCÓDIGO INVÁLIDO!\nINFORME O CÓDIGO DO PRODUTO:\nEST");
            scanf("%d", &codigo_2);
            fflush(stdin);
            lerInfoProduto(codigo_2);
        }
    }

    if(produto_3.codigo == codigo_2)
    {
        printf("\nINFORMAÇÕES SOBRE O PRODUTO:\n\n", produto_3.codigo);
        fflush(stdin);
        printf("NOME:\t\t\t%s", produto_3.nome);
        fflush(stdin);
        printf("DESCRIÇÃO:\t\t%s", produto_3.descricao);
        fflush(stdin);
        printf("LOTE:\t\t\t%s", produto_3.lote);
        fflush(stdin);
        printf("VALOR:\t\t\tR$%.2f\n", produto_3.valor);
        fflush(stdin);
        printf("UNIDADES DISPONÍVEIS:\t%d\n", produto_3.unidades);
        fflush(stdin);

        if(validade.dia == 0)
        {
            printf("DATA DE VALIDADE:\tNÃO POSSUI.\n");
            fflush(stdin);
        }
        else
        {
            printf("DATA DE VALIDADE:\t%02d/%02d/%04d\n\n",
                            validade.dia, validade.mes, validade.ano);
            fflush(stdin);
        }
    }

    printf("\nQUANTAS UNIDADES SERÃO VENDIDAS?\n");
    scanf("%d", &unidades);
    fflush(stdin);
    while(unidades <= 0 || unidades > produto_3.unidades)
    {
        printf("\nQUANTIDADE INVÁLIDA!\nINSIRA A QUANTIDADE NOVAMENTE:\n");
        scanf("%d", &unidades);
        fflush(stdin);
    }

    produtoVendido(codigo_2, unidades, dia, mes, ano, i);
    printf("\nVALOR TOTAL: R$%.2f\n\n", produto_3.valor * unidades);

    vendas = fopen("HISTORICO_DE_VENDAS.txt", "a+");

    fprintf(vendas, "%d\n", produto_3.codigo);
    fprintf(vendas, "%d\n", codigoDaVenda());
    fputs(produto_3.nome, vendas);
    fputs(produto_3.descricao, vendas);
    fputs(produto_3.lote, vendas);
    fprintf(vendas, "%.2f\n", produto_3.valor*unidades);
    fprintf(vendas, "%d\n", unidades);
    obterDataEHorario();
    fprintf(vendas, "%02d %02d %04d\n", validade.dia, validade.mes, validade.ano);
    fprintf(vendas, "%02d %02d %04d %02d %02d %02d\n", data.dia, data.mes, data.ano, horario.horas, horario.minutos, horario.segundos);
    fclose(vendas);
    atualizarEstoque(unidades, codigo_2, i);
}

struct Cadastro
{
    int codigo;
    char nome[40];
    char descricao[250];
    char lote[20];
    float valor;
};
struct Cadastro cadastro;


void cadastro()
{
    FILE *cadastro, *lote;

    printf("\n\n\t\t\t\t\t[CADASTRO DE PRODUTO]\n\n");
    fflush(stdin);

    printf("\nINSIRA O NOME DO PRODUTO:\n");
    gets(cadastro.nome);
    fflush(stdin);
    while(strlen(cadastro.nome) == 0)
    {
        printf("O NOME DO PRODUTO NÃO FOI INSERIDO!\nINSIRA O NOME:\n");
        gets(cadastro.nome);
        fflush(stdin);
    }

    printf("\nINSIRA A DESCRIÇÃO DO PRODUTO:\n");
    gets(cadastro.descricao);
    fflush(stdin);
    while(strlen(cadastro.descricao) == 0) {
        printf("A DESCRIÇÃO DO PRODUTO NÃO FOI INSERIDA!\nINSIRA A DESCRIÇÃO:\n");
        gets(cadastro.descricao);
        fflush(stdin);
    }

    printf("\nINSIRA O LOTE DO PRODUTO:\n");
    gets(cadastro.lote);
    fflush(stdin);
    while(strlen(cadastro.lote) == 0)
    {
        printf("O LOTE DO PRODUTO NÃO FOI INSERIDO!\nINSIRA O LOTE:\n");
        gets(cadastro.lote);
        fflush(stdin);
    }

    printf("\nINSIRA O VALOR UNITÁRIO DE VENDA DO PRODUTO:\n");
    scanf("%f", &cadastro.valor);
    fflush(stdin);
    while(cadastro.valor <= 0)
    {
        printf("\nO VALOR INSERIDO É INVÁLIDO!\nINFORME O VALOR:\n");
        scanf("%f", &cadastro.valor);
        fflush(stdin);
    }

    codigoDoEstoque(&cadastro.codigo);
    cadastro = fopen("ESTOQUE.txt", "a+");
    fprintf(cadastro, "%d\n", cadastro.codigo);
    fputs(cadastro.nome, cadastro);
    fprintf(cadastro, "\n");
    fputs(cadastro.descricao, cadastro);
    fprintf(cadastro, "\n");
    fputs(cadastro.lote, cadastro);
    fprintf(cadastro, "\n");
    fprintf(cadastro, "%.2f\n", cadastro.valor);

    fclose(cadastro);
    printf("\nO PRODUTO FOI CADASTRADO COM SUCESSO!\n");
    printf("O CÓDIGO DO PRODUTO É: EST%d.\n\n", cadastro.codigo);
}


int comandos(int opcao)
{
    switch(opcao)
   {
        FILE *arquivo;

        case 1:
                system("cls");
                cadastro();
                system("pause");
                system("cls");
                break;
        case 2:
                system("cls");
                printf("");
                break;
        case 3:
                system("cls");
                printf("");
                break;
        case 4:
                system("cls");
                Vendas();
                system("pause");
                system("cls");
                printf("");
                break;
        case 5:
                system("cls");
                arquivo = fopen("HISTORICO_DE_VENDAS.txt", "r");
                listar(arquivo);
                system("pause");
                system("cls");
                break;
        case 6:
                system("cls");
                produto.codigo2 = 0;
                arquivo = fopen("ESTOQUE.txt", "r");
                listar(arquivo);
                system("pause");
                system("cls");
                break;
        case 7:
                system("cls");
                printf("");
                break;
        case 8:
                system("cls");
                printf("");
                break;
        case 0:
                system("cls");
                printf("\nEncerrando...\n");
                exit(0);
        default:
                system("cls");
                printf("\nOpção inválida.\n\n");
                system("pause");
                system("cls");
                break;
    }
}

void menu()
{
    printf("\n\n");
    printf("\t\t\t  ########################################################  \n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  #\t\t\t  PRODUTOS\t\t         #\n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  ########################################################  \n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  #\t\t\t1 - Cadastrar\t\t\t #\n");
    printf("\t\t\t  #\t\t\t2 - Excluir\t\t\t #\n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  ########################################################  \n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  #\t\t      COMPRAS E VENDAS\t\t\t #\n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  ########################################################  \n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  #\t\t   3 - Comprar\t\t\t\t #\n");
    printf("\t\t\t  #\t\t   4 - Vender\t\t\t\t #\n");
    printf("\t\t\t  #\t\t   5 - Histórico de vendas\t\t #\n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  ########################################################  \n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  #\t\t\t  ESTOQUE\t\t\t #\n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  ########################################################  \n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  #\t\t\t6 - Exibir\t\t\t #\n");
    printf("\t\t\t  #\t\t\t7 - Aumentar\t\t\t #\n");
    printf("\t\t\t  #\t\t\t8 - Reduzir\t\t\t #\n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  ########################################################  \n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  #\t\t\t  PROGRAMA\t\t\t #\n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  ########################################################  \n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  #\t\t\t0 - Encerrar\t\t\t #\n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  ########################################################  \n\n\n");
}

void main()
{
    mkdir(RGSTRS);
    chdir(RGSTRS);
    system("cls");
    system("MODE con cols=109 lines=44");
    setlocale(LC_ALL, "Portuguese");

    int repetir, opcao, cont;

    while(repetir)
    {
        menu();
        printf("INFORME A OPÇÃO DESEJADA: ");
        scanf("%d", &opcao);
        system("cls");
        comandos(opcao);
    }
}
