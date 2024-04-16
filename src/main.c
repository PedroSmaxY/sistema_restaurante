#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

enum TiposRefeicao
{
    MARMITA,
    REFEICAO,
};

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

void registrarVenda(Refeicao vendas[], int tamanho, int *contador, float precoKilo)
{
    int escolhaTipoRefeicao;
    char continuar;
    for (int i = 0; i < tamanho; i++)
    {
        if (i > 0)
        {
            printf("Deseja continuar? [S/N]: ");
            scanf(" %c", &continuar);

            if (continuar == 'N' || continuar == 'n')
                break;
        }

        (*contador)++;
        vendas[i].posicao = i + 1;

        printf("\nVenda %d", vendas[i].posicao);
        printf("\n\nDigite o peso em Kg: ");
        scanf("%f", &vendas[i].peso);
        limparBuffer();

        printf("Escolha:\n1 - Marmita\n2 - Refeição");
        scanf("%d", &escolhaTipoRefeicao);
        limparBuffer();

        switch (escolhaTipoRefeicao)
        {
        case MARMITA:
            vendas[i].preco = (precoKilo * vendas[i].peso) + 0.50;
            break;
        case REFEICAO:
            vendas[i].preco = precoKilo * vendas[i].peso;
            break;
        default:
            printf("\nDigite um número válido!!!");
            printf("\nPressione ENTER para continuar. . .");
            getchar();
            continue;
        }
    }
}

int main()
{
    int escolhaMenu;
    int contador = 0;
    float precoKilo = 0;

    Refeicao vendas[100];

    for (int i = 0; i < 100; i++)
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
        printf("\n1 - Redefinir o preço do Kg");
        printf("\n2 - Registrar Venda");
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
                precoKilo = definirValorKilo();
                break;
            case 2:
                limparConsole();
                registrarVenda(vendas, sizeof(vendas) / sizeof(vendas[0]), &contador, precoKilo);
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