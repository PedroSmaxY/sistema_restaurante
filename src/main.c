#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

enum TiposRefeicao
{
    MARMITA = 1,
    REFEICAO,
};

typedef struct
{
    char nome[50];
    float valorTotal;
} LucroMes;

typedef struct
{
    int posicao;
    float preco;
    float peso;
} Refeicao;

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void limparConsole()
{
#ifdef _WIN32
    system("CLS");
#else
    system("CLEAR");
#endif
}

float definirValorKilo()
{
    float valor;
    do
    {
        printf("Digite o preço do Kg: R$");
        scanf("%f", &valor);
        limparBuffer();
    } while (valor <= 0);

    return valor;
}

float definirBebidas()
{
    int escolha;
    float preco;
    while (1)
    {
        printf("\n------------ BEBIDAS ------------");
        printf("\n-------- Escolha pelo ID --------");
        printf("\n---------------------------------");
        printf("\nId: 1 - Coca Cola 2l - R$15,50");
        printf("\nId: 2 - Coca Cola 500ml - R$6,25");
        printf("\nId: 3 - Mate Leão 1.5l 500ml - R$12,30");
        printf("\nId: 4 - Mate Leão 300ml 500ml - R$5,00");
        printf("\nId: 5 - Choco Leite 250ml - R$6,00");
        printf("\nId: 6 - Frappuccino 500ml - R$18,00");
        printf("\n---------------------------------");
        printf("\nEscolha: ");
        scanf("%d", &escolha);
        if (escolha < 0 || escolha > 6)
        {
            printf("\nID INVÁLIDO TENTE NOVAMENTE");
            continue;
        }
        else
        {
            switch (escolha)
            {
            case 1:
                preco = 15.50;
                break;
            case 2:
                preco = 6.25;
                break;
            case 3:
                preco = 12.30;
                break;
            case 4:
                preco = 5.00;
                break;
            case 5:
                preco = 6.00;
                break;
            case 6:
                preco = 18.00;
                break;
            }
            return preco;
        }
    }
}

void ordenarValorDia(Refeicao vendas[], int tamanho)
{
    int i, j;
    Refeicao temp;

    for (i = 0; i < tamanho - 1; i++)
    {
        for (j = 0; j < tamanho - i - 1; j++)
        {
            if (vendas[j].preco < vendas[j + 1].preco)
            {
                // Troca os elementos
                temp = vendas[j];
                vendas[j] = vendas[j + 1];
                vendas[j + 1] = temp;
            }
        }
    }
}

void registrarVenda(Refeicao vendas[], int tamanho, int *contador, float precoKilo)
{
    int escolhaTipoRefeicao;
    char escolhaBebida;
    char continuar;

    for (int i = *contador; i < tamanho; i++)
    {
        if (i > 0)
        {
            if (escolhaTipoRefeicao == 2 || escolhaTipoRefeicao == 1)
            {
                printf("Deseja continuar? [S/N]: ");
                scanf(" %c", &continuar);
                limparBuffer();

                if (continuar == 'N' || continuar == 'n')
                    break;
            }
            else
            {
                i--;
            }
        }
        (*contador)++;
        vendas[i].posicao = i + 1;

        printf("\nVenda %d", vendas[i].posicao);
        printf("\n\nDigite o peso em gramas: ");
        scanf("%f", &vendas[i].peso);
        limparBuffer();

        vendas[i].peso /= 1000;

        printf("\nDeseja Bebida? [S/N]: ");
        scanf(" %c", &escolhaBebida);

        if (escolhaBebida == 'S' || escolhaBebida == 's')
        {
            vendas[i].preco += definirBebidas();
        }

        printf("\n1 - Marmita\n2 - Refeição\nEscolha: ");
        scanf("%d", &escolhaTipoRefeicao);
        limparBuffer();

        switch (escolhaTipoRefeicao)
        {
        case MARMITA:
            vendas[i].preco += (precoKilo * vendas[i].peso) + 0.50;
            break;
        case REFEICAO:
            vendas[i].preco += precoKilo * vendas[i].peso;
            break;
        default:
            printf("\nDigite um número válido!!!");
            printf("\nPressione ENTER para continuar. . .");
            getchar();
            continue;
        }
    }
    ordenarValorDia(vendas, tamanho);
}

float definirValorMensal()
{
    float valorMensal;

    while (1)
    {
        printf("\nDigite o valor bruto mensal: R$");
        scanf("%f", &valorMensal);
        if (valorMensal > 0)
        {
            break;
        }
        else
        {
            printf("\nValor Inválido!!!");
            continue;
        }
    }
    return valorMensal;
}

void ordenarValoresMes(LucroMes lucroMeses[])
{
    int i, j;
    LucroMes temp;

    for (i = 0; i < 12 - 1; i++)
    {
        for (j = 0; j < 12 - i - 1; j++)
        {
            if (lucroMeses[j].valorTotal < lucroMeses[j + 1].valorTotal)
            {
                // Troca os elementos
                temp = lucroMeses[j];
                lucroMeses[j] = lucroMeses[j + 1];
                lucroMeses[j + 1] = temp;
            }
        }
    }
}

void registroLucroMensal(LucroMes lucroMeses[], int *contador)
{
    int escolhaMenu;
    int contadorInterno = *contador;

    while (1)
    {
        limparConsole();

        printf("\n-------------------------------");
        printf("\nEscolha um Mês");
        printf("\n-------------------------------");
        printf("\n0 - Voltar para o menu");
        printf("\n1 - Janeiro - R$%.2f", lucroMeses[0].valorTotal);
        printf("\n2 - Fevereiro - R$%.2f", lucroMeses[1].valorTotal);
        printf("\n3 - Março - R$%.2f", lucroMeses[2].valorTotal);
        printf("\n4 - Abril - R$%.2f", lucroMeses[3].valorTotal);
        printf("\n5 - Maio - R$%.2f", lucroMeses[4].valorTotal);
        printf("\n6 - Junho - R$%.2f", lucroMeses[5].valorTotal);
        printf("\n7 - Julho - R$%.2f", lucroMeses[6].valorTotal);
        printf("\n8 - Agosto - R$%.2f", lucroMeses[7].valorTotal);
        printf("\n9 - Setembro - R$%.2f", lucroMeses[8].valorTotal);
        printf("\n10 - Outubro - R$%.2f", lucroMeses[9].valorTotal);
        printf("\n11 - Novembro - R$%.2f", lucroMeses[10].valorTotal);
        printf("\n12 - Dezembro - R$%.2f", lucroMeses[11].valorTotal);
        printf("\n-------------------------------");
        printf("\nDigite: ");
        scanf("%d", &escolhaMenu);
        limparBuffer();

        if (escolhaMenu != 0)
        {

            switch (escolhaMenu)
            {
            case 1:
                lucroMeses[0].valorTotal = definirValorMensal();
                strcpy(lucroMeses[0].nome, "Janeiro");
                if (contadorInterno < 12)
                    contadorInterno++;
                break;
            case 2:
                lucroMeses[1].valorTotal = definirValorMensal();
                strcpy(lucroMeses[1].nome, "Fevereiro");
                if (contadorInterno < 12)
                    contadorInterno++;
                break;
            case 3:
                lucroMeses[2].valorTotal = definirValorMensal();
                strcpy(lucroMeses[2].nome, "Março");
                if (contadorInterno < 12)
                    contadorInterno++;
                break;
            case 4:
                lucroMeses[3].valorTotal = definirValorMensal();
                strcpy(lucroMeses[3].nome, "Abril");
                if (contadorInterno < 12)
                    contadorInterno++;
                break;
            case 5:
                lucroMeses[4].valorTotal = definirValorMensal();
                strcpy(lucroMeses[4].nome, "Maio");
                if (contadorInterno < 12)
                    contadorInterno++;
                break;
            case 6:
                lucroMeses[5].valorTotal = definirValorMensal();
                strcpy(lucroMeses[5].nome, "Junho");
                if (contadorInterno < 12)
                    contadorInterno++;
                break;
            case 7:
                lucroMeses[6].valorTotal = definirValorMensal();
                strcpy(lucroMeses[6].nome, "Julho");
                if (contadorInterno < 12)
                    contadorInterno++;
                break;
            case 8:
                lucroMeses[7].valorTotal = definirValorMensal();
                strcpy(lucroMeses[7].nome, "Agosto");
                if (contadorInterno < 12)
                    contadorInterno++;
                break;
            case 9:
                lucroMeses[8].valorTotal = definirValorMensal();
                strcpy(lucroMeses[8].nome, "Setembro");
                if (contadorInterno < 12)
                    contadorInterno++;
                break;
            case 10:
                lucroMeses[9].valorTotal = definirValorMensal();
                strcpy(lucroMeses[9].nome, "Outubro");
                if (contadorInterno < 12)
                    contadorInterno++;
                break;
            case 11:
                lucroMeses[10].valorTotal = definirValorMensal();
                strcpy(lucroMeses[10].nome, "Novembro");
                if (contadorInterno < 12)
                    contadorInterno++;
                break;
            case 12:
                lucroMeses[11].valorTotal = definirValorMensal();
                strcpy(lucroMeses[11].nome, "Dezembro");
                if (contadorInterno < 12)
                    contadorInterno++;
                break;

            default:
                printf("\nVALOR INVÁLIDO!!!");
                break;
            }
        }
        else
        {
            break;
        }
    }
    *contador = contadorInterno;
    ordenarValoresMes(lucroMeses);
}

void resumoDiario(Refeicao vendas[], int contador, float precoKilo)
{
    float valorTotal = 0;
    printf("\n---------- Resumo Diário ----------");
    printf("\nPreço do Kg: %.2f", precoKilo);
    printf("\n-----------------------------------");
    for (int i = 0; i < contador; i++)
    {
        printf("\nVenda: %d", vendas[i].posicao);
        printf("\nPeso: %.3f Kg", vendas[i].peso);
        printf("\nPreço: R$%.2f ", vendas[i].preco);
        printf("\n-----------------------------------");
        valorTotal += vendas[i].preco;
    }
    printf("\nLucro bruto do dia: R$%.2f", valorTotal);

    printf("\nPresione ENTER para continuar. . .");
    getchar();
}

void resumoAnual(LucroMes lucroMeses[], int tamanho)
{
    float valorTotal = 0;
    printf("\n---------- Resumo Anual -----------");
    for (int i = 0; i < tamanho; i++)
    {
        valorTotal += lucroMeses[i].valorTotal;
        printf("\n%s", lucroMeses[i].nome);
        printf("\nPreço: %.2f", lucroMeses[i].valorTotal);
        printf("\n-----------------------------------");
    }
    printf("\nValor bruto anual: %.2f", valorTotal);
    printf("\nPresione ENTER para continuar. . .");
    getchar();
}

int main()
{
    int escolhaMenu;
    int contador = 0;
    int contadorAnual = 0;
    // FILE *arquivoDat = fopen("resumo_dia.dat", "wb");
    float precoKilo = 0;
    Refeicao vendas[100];
    LucroMes lucroMeses[12];

    for (size_t i = 0; i < sizeof(lucroMeses) / sizeof(lucroMeses[0]); i++)
    {
        lucroMeses[i].nome[0] = '\0';
        lucroMeses[i].valorTotal = 0.0;
    }

    for (size_t i = 0; i < sizeof(vendas) / sizeof(vendas[0]); i++)
    {
        vendas[i].peso = 0.0;
        vendas[i].preco = 0.0;
    }

    setlocale(LC_ALL, "Portuguese");
    limparConsole();

    while (1)
    {
        if (precoKilo == 0)
        {
            printf("\n-------------------------------");
            printf("\nSISTEMA - RESTAURANTE A KILO");
            printf("\n-------------------------------\n");
            precoKilo = definirValorKilo();
        }

        limparConsole();
        printf("\n-------------------------------");
        printf("\nSISTEMA - RESTAURANTE A QUILO");
        printf("\n-------------------------------");
        printf("\n1 - Registrar Venda Diária");
        printf("\n2 - Resumo Diário");
        printf("\n3 - Registrar Lucro Mensal");
        printf("\n4 - Resumo Anual");
        printf("\n5 - Redefinir o preço do Kg");
        printf("\n0 - Encerrar o programa");
        printf("\n-------------------------------");
        printf("\nDigite: ");
        scanf("%d", &escolhaMenu);
        limparBuffer();

        if (escolhaMenu != 0)
        {
            switch (escolhaMenu)
            {
            case 1:
                limparConsole();
                registrarVenda(vendas, sizeof(vendas) / sizeof(vendas[0]), &contador, precoKilo);
                break;
            case 2:
                limparConsole();
                resumoDiario(vendas, contador, precoKilo);
                break;
            case 3:
                registroLucroMensal(lucroMeses, &contadorAnual);
                break;
            case 4:
                limparConsole();
                resumoAnual(lucroMeses, contadorAnual);
                break;
            case 5:
                limparConsole();
                precoKilo = definirValorKilo();
                break;
            default:
                printf("\nDigite um número válido!!!");
                printf("\nPresione ENTER para continuar. . .");
                getchar();
                break;
            }
        }
        else
        {
            break;
        }
    }
    printf("\nPrograma Encerrado. . .");
    return 0;
}