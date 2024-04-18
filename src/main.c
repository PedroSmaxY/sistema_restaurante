/*
Allan Guilherme -  1230114406

Henry da Silva - 1230204910

Lucas Faria de Oliveira - 1230114255

Pedro Henrique da Silva Novais - 1230119539

Victor Jacques - 1230203770
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Define uma enumeração para os tipos de refeição
enum TiposRefeicao
{
    MARMITA = 1, // Define MARMITA como 1
    REFEICAO,    // Define REFEICAO como 2 (o próximo número após MARMITA)
};

// Define uma estrutura para armazenar informações sobre o lucro de um mês
typedef struct
{
    char nome[50];    // Nome do mês
    float valorTotal; // Valor total do lucro para o mês
} LucroMes;

// Define uma estrutura para armazenar informações sobre uma refeição
typedef struct
{
    int posicao; // Posição da refeição no menu
    float preco; // Preço da refeição
    float peso;  // Peso da refeição
} Refeicao;

// Função para limpar o buffer de entrada
void limparBuffer()
{
    int c;
    // Lê caracteres do buffer de entrada até encontrar um '\n' (fim de linha) ou EOF (fim de arquivo)
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Função para limpar o console
void limparConsole()
{
#ifdef _WIN32
    // Se o sistema operacional é Windows, usa o comando "CLS" para limpar o console
    system("CLS");
#else
    // Se o sistema operacional não é Windows, usa o comando "CLEAR" para limpar o console
    system("CLEAR");
#endif
}

// Função para definir o valor do quilo
float definirValorQuilo()
{
    float valor;
    do
    {
        // Solicita ao usuário que digite o preço do quilo
        printf("Digite o preço do Kg: R$");
        scanf("%f", &valor);
        // Limpa o buffer de entrada para remover qualquer entrada restante
        limparBuffer();
    } while (valor <= 0); // Repete até que o usuário digite um valor maior que 0

    return valor;
}

// Função para definir o preço das bebidas
float definirBebidas()
{
    int escolha; // Variável para armazenar a escolha do usuário
    float preco; // Variável para armazenar o preço da bebida escolhida

    // Loop infinito até que uma escolha válida seja feita
    while (1)
    {
        // Imprime o menu de bebidas
        printf("\n------------ BEBIDAS ------------");
        printf("\n-------- Escolha pelo ID --------");
        printf("\n---------------------------------");
        printf("\nId: 1 - Coca Cola 2l - R$15,50");
        printf("\nId: 2 - Coca Cola 500ml - R$6,25");
        printf("\nId: 3 - Mate Leão 1.5l - R$12,30");
        printf("\nId: 4 - Mate Leão 500ml - R$5,00");
        printf("\nId: 5 - Guaraná 250ml - R$6,00");
        printf("\nId: 6 - Sukita 2l - R$12,00");
        printf("\n---------------------------------");
        printf("\nEscolha: ");
        scanf("%d", &escolha); // Lê a escolha do usuário

        // Verifica se a escolha é válida
        if (escolha < 0 || escolha > 6)
        {
            printf("\nID INVÁLIDO TENTE NOVAMENTE");
            continue; // Se a escolha não é válida, volta para o início do loop
        }
        else
        {
            // Atribui o preço correspondente à escolha do usuário
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
                preco = 12.00;
                break;
            }
            return preco; // Retorna o preço da bebida escolhida
        }
    }
}

// Função para ordenar as vendas do dia por valor
void ordenarValorDia(Refeicao vendas[], int tamanho)
{
    int i, j;
    Refeicao temp;

    // Algoritmo de ordenação bubble sort
    for (i = 0; i < tamanho - 1; i++)
    {
        for (j = 0; j < tamanho - i - 1; j++)
        {
            // Se o preço da venda atual é menor que o próximo, troca os dois
            if (vendas[j].preco < vendas[j + 1].preco)
            {
                temp = vendas[j];
                vendas[j] = vendas[j + 1];
                vendas[j + 1] = temp;
            }
        }
    }
}

// Função para registrar uma venda
void registrarVenda(Refeicao vendas[], int tamanho, int *contador, float precoQuilo)
{
    int i;
    int escolhaTipoRefeicao; // Variável para armazenar o tipo de refeição escolhido
    char escolhaBebida;      // Variável para armazenar se o cliente quer uma bebida
    char continuar;          // Variável para armazenar se o usuário quer continuar registrando vendas
    int contadorVenda = *contador;

    // Loop para registrar as vendas
    // Loop para registrar as vendas
    for (i = *contador; i < tamanho;)
    {
        // Incrementa o contador de vendas
        contadorVenda++;
        vendas[i].posicao = contadorVenda;

        // Solicita ao usuário que digite o peso da refeição
        printf("\nVenda %d", vendas[i].posicao);
        printf("\n\nDigite o peso da refeição em gramas: ");
        scanf("%f", &vendas[i].peso);
        limparBuffer();

        // Converte o peso para quilogramas
        vendas[i].peso /= 1000;

        // Pergunta ao usuário se ele quer uma bebida
        printf("\nDeseja Bebida? [S/N]: ");
        scanf(" %c", &escolhaBebida);

        // Se o usuário quer uma bebida, adiciona o preço da bebida ao preço da refeição
        if (escolhaBebida == 'S' || escolhaBebida == 's')
        {
            vendas[i].preco += definirBebidas();
        }

        // Pergunta ao usuário o tipo de refeição
        printf("\n1 - Marmita com custo adicional\n2 - Refeição sem custo adicional\nEscolha: ");
        scanf("%d", &escolhaTipoRefeicao);
        limparBuffer();

        // Calcula o preço da refeição com base no tipo escolhido
        switch (escolhaTipoRefeicao)
        {
        case MARMITA:
            vendas[i].preco += ((precoQuilo * vendas[i].peso) + 20) + 0.50;
            break;
        case REFEICAO:
            vendas[i].preco += precoQuilo * vendas[i].peso;
            break;
        default:
            printf("\nDigite um número válido!!!");
            printf("\nPressione ENTER para continuar. . .");
            getchar();
            continue;
        }

        // Pergunta se o usuário quer continuar
        printf("Deseja continuar? [S/N]: ");
        scanf(" %c", &continuar);
        limparBuffer();

        // Se o usuário não quer continuar, sai do loop
        if (continuar == 'N' || continuar == 'n')
            break;

        // Incrementa o contador do loop
        i++;
    }
    *contador = contadorVenda;

    // Ordena as vendas do dia por valor
    ordenarValorDia(vendas, tamanho);
}

// Função para definir o valor mensal
float definirValorMensal()
{
    float valorMensal; // Variável para armazenar o valor mensal

    // Loop infinito até que um valor válido seja inserido
    while (1)
    {
        printf("\nDigite o valor bruto mensal: R$"); // Solicita ao usuário que insira o valor mensal
        scanf("%f", &valorMensal);                   // Lê o valor mensal

        // Se o valor for maior que 0, sai do loop
        if (valorMensal > 0)
        {
            break;
        }
        else
        {
            printf("\nValor Inválido!!!"); // Imprime uma mensagem de erro se o valor for inválido
            continue;                      // Continua o loop se o valor for inválido
        }
    }
    return valorMensal; // Retorna o valor mensal
}

// Função para ordenar os valores mensais
void ordenarValoresMes(LucroMes lucroMeses[])
{
    int i, j;      // Variáveis para os índices do loop
    LucroMes temp; // Variável temporária para a troca de elementos

    // Algoritmo de ordenação bubble sort
    for (i = 0; i < 12 - 1; i++)
    {
        for (j = 0; j < 12 - i - 1; j++)
        {
            // Se o valor atual for menor que o próximo, troca os elementos
            if (lucroMeses[j].valorTotal < lucroMeses[j + 1].valorTotal)
            {
                temp = lucroMeses[j];              // Armazena o valor atual na variável temporária
                lucroMeses[j] = lucroMeses[j + 1]; // Substitui o valor atual pelo próximo
                lucroMeses[j + 1] = temp;          // Substitui o próximo valor pelo valor temporário
            }
        }
    }
}

// Função para registrar o lucro mensal
void registroLucroMensal(LucroMes lucroMeses[], int *contador)
{
    int escolhaMenu;                 // Variável para armazenar a escolha do menu do usuário
    int contadorInterno = *contador; // Variável para armazenar o valor do contador

    // Loop infinito até que a opção 0 seja escolhida
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

        // Se a escolha não for 0, entra no switch case
        if (escolhaMenu != 0)
        {
            // Switch case para cada mês
            switch (escolhaMenu)
            {
            case 1:
                // Define o valor mensal para Janeiro
                lucroMeses[0].valorTotal = definirValorMensal();
                // Define o nome do mês para Janeiro
                strcpy(lucroMeses[0].nome, "Janeiro");
                // Incrementa o contador se for menor que 12
                if (contadorInterno < 12)
                    contadorInterno++;
                break;
                // O mesmo é feito para os outros meses...
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
            // Se a escolha for 0, sai do loop
            break;
        }
    }
    *contador = contadorInterno;
    ordenarValoresMes(lucroMeses);
}

// Função para salvar os dados diários
void salvarDadosDiario(Refeicao vendas[], int contador, float precoQuilo)
{
    int i;
    // Tenta abrir o arquivo 'resumo_diario.dat' no modo binário de escrita
    FILE *arquivoDat = fopen("resumo_diario.dat", "wb");

    // Se o arquivo não puder ser aberto (ou criado), exibe uma mensagem de erro e encerra o programa
    if (arquivoDat == NULL)
    {
        printf("\nErro: Falha ao criar o arquivo 'resumo_diario.dat' para gravação!");
        exit(1);
    }

    // Grava o preço por quilo no arquivo
    fwrite(&precoQuilo, sizeof(float), 1, arquivoDat);

    // Grava o contador de vendas no arquivo
    fwrite(&contador, sizeof(int), 1, arquivoDat);

    // Grava cada venda no arquivo
    for (i = 0; i < contador; i++)
    {
        fwrite(&vendas[i], sizeof(Refeicao), 1, arquivoDat);
    }

    // Fecha o arquivo
    fclose(arquivoDat);

    // Exibe uma mensagem indicando que os dados foram salvos com sucesso
    printf("\nDados diários salvos com sucesso no arquivo 'resumo_diario.dat'!");
}

// Função para exibir um resumo diário das vendas
void resumoDiario(Refeicao vendas[], int contador, float precoQuilo)
{
    float valorTotal = 0; // Variável para armazenar o valor total das vendas
    char escolha;
    int i;
    // Imprime o cabeçalho do resumo diário e o preço por quilo
    printf("\n--------- Resumo Diário -----------");
    printf("\nPreço do Kg: %.2f", precoQuilo);
    printf("\n-----------------------------------");

    // Loop para percorrer todas as vendas
    for (i = 0; i < contador; i++)
    {
        // Imprime os detalhes de cada venda
        printf("\nVenda: %d", vendas[i].posicao);
        printf("\nPeso: %.3f Kg", vendas[i].peso);
        printf("\nPreço: R$%.2f ", vendas[i].preco);
        printf("\n-----------------------------------");
        // Adiciona o preço da venda ao valor total
        valorTotal += vendas[i].preco;
    }

    // Imprime o lucro bruto do dia
    printf("\nLucro bruto do dia: R$%.2f", valorTotal);

    // Aguarda o usuário pressionar ENTER para continuar

    while (1)
    {
        printf("\nDeseja salvar em um arquivo? [S/N]: ");
        scanf(" %c", &escolha);
        limparBuffer();

        if (escolha == 'S' || escolha == 's')
        {
            salvarDadosDiario(vendas, contador, precoQuilo);
            break;
        }
        else
        {
            break;
        }
    }

    printf("\nPresione ENTER para continuar. . .");
    getchar();
}

// Função para salvar os dados anuais
void salvarDadosAnuais(LucroMes lucroMeses[], int tamanho)
{
    int i;
    // Tenta abrir o arquivo 'resumo_anual.dat' no modo binário de escrita
    FILE *arquivoDat = fopen("resumo_anual.dat", "wb");

    // Se o arquivo não puder ser aberto (ou criado), exibe uma mensagem de erro e encerra o programa
    if (arquivoDat == NULL)
    {
        printf("\nErro: Falha ao criar o arquivo 'resumo_anual.dat' para gravação!");
        exit(1);
    }

    // Grava o tamanho (número de meses) no arquivo
    fwrite(&tamanho, sizeof(int), 1, arquivoDat);

    // Grava os dados de cada mês no arquivo
    for (i = 0; i < tamanho; i++)
    {
        fwrite(&lucroMeses[i], sizeof(LucroMes), 1, arquivoDat);
    }

    // Fecha o arquivo
    fclose(arquivoDat);

    // Exibe uma mensagem indicando que os dados foram salvos com sucesso
    printf("\nDados diários salvos com sucesso no arquivo 'resumo_anual.dat'!");
}

// Função para exibir um resumo anual das vendas
void resumoAnual(LucroMes lucroMeses[], int tamanho)
{
    int i;
    char escolha;
    float valorTotal = 0; // Variável para armazenar o valor total das vendas

    // Imprime o cabeçalho do resumo anual
    printf("\n---------- Resumo Anual -----------");

    // Loop para percorrer todos os meses
    for (i = 0; i < tamanho; i++)
    {
        // Adiciona o valor total do mês ao valor total anual
        valorTotal += lucroMeses[i].valorTotal;

        // Imprime os detalhes de cada mês
        printf("\n%s", lucroMeses[i].nome);
        printf("\nPreço: %.2f", lucroMeses[i].valorTotal);
        printf("\n-----------------------------------");
    }

    // Imprime o valor bruto anual
    printf("\nValor bruto anual: %.2f", valorTotal);

    while (1)
    {
        printf("\nDeseja salvar em um arquivo? [S/N]: ");
        scanf(" %c", &escolha);
        limparBuffer();

        if (escolha == 'S' || escolha == 's')
        {
            salvarDadosAnuais(lucroMeses, tamanho);
            break;
        }
        else
        {
            break;
        }
    }

    // Aguarda o usuário pressionar ENTER para continuar
    printf("\nPresione ENTER para continuar. . .");
    getchar();
}

// Função para exibir os dados armazenados nos arquivos
void exibirDadosArquivos()
{
    int escolha;
    // Loop infinito até que o usuário escolha sair
    while (1)
    {
        // Solicita ao usuário que escolha uma opção
        printf("\n1 - Resumo Diário\n2 - Resumo Anual\n0 - Sair\nEscolha: ");
        scanf("%d", &escolha);
        limparBuffer();

        // Se a escolha for 1, exibe o resumo diário
        if (escolha == 1)
        {
            limparConsole();

            int i;

            // Abre o arquivo de resumo diário para leitura
            FILE *arquivoDat = fopen("resumo_diario.dat", "rb");

            // Se o arquivo não puder ser aberto, exibe uma mensagem de erro e retorna
            if (arquivoDat == NULL)
            {
                printf("\nErro: Falha ao abrir o arquivo 'resumo_diario.dat' para leitura!");
                printf("\nPressione ENTER para continuar. . .");
                getchar();
                return;
            }

            float precoQuilo;
            int contador;

            // Lê o preço por quilo e o contador do arquivo
            fread(&precoQuilo, sizeof(float), 1, arquivoDat);
            fread(&contador, sizeof(int), 1, arquivoDat);

            // Imprime o cabeçalho do resumo
            printf("\n-------- Resumo Diário -----------");
            printf("\nPreço do Quilo: %.2f", precoQuilo);
            printf("\n----------------------------------");

            // Lê e imprime cada venda
            for (i = 0; i < contador; i++)
            {
                Refeicao venda;
                fread(&venda, sizeof(Refeicao), 1, arquivoDat);

                printf("\nVenda: %d", venda.posicao);
                printf("\nPeso: %.3f Kg", venda.peso);
                printf("\nPreço: R$%.2f ", venda.preco);
                printf("\n-----------------------------------");
            }

            // Fecha o arquivo
            fclose(arquivoDat);
        }
        // Se a escolha for 2, exibe o resumo anual
        else if (escolha == 2)
        {
            limparConsole();

            int tamanho;
            int i;

            // Abre o arquivo de resumo anual para leitura
            FILE *arquivoDat = fopen("resumo_anual.dat", "rb");
            if (arquivoDat == NULL)
            {
                printf("\nErro: Falha ao abrir o arquivo '%s' para leitura!", "resumo_anual.dat");
                return;
            }

            // Lê o tamanho do arquivo
            fread(&tamanho, sizeof(int), 1, arquivoDat);

            // Lê e imprime cada mês e seu lucro
            printf("\n-----------------------------------");
            for (i = 0; i < tamanho; i++)
            {
                LucroMes lucroMes;
                fread(&lucroMes, sizeof(LucroMes), 1, arquivoDat);

                printf("\n%s", lucroMes.nome);
                printf("\nValor Bruto: R$%.2f", lucroMes.valorTotal);
                printf("\n-----------------------------------");
            }

            // Fecha o arquivo
            fclose(arquivoDat);
        }
        // Se a escolha for 0, sai do loop
        else if (escolha == 0)
            break;
        // Se a escolha não for 1, 2 ou 0, exibe uma mensagem de erro
        else
        {
            printf("\nDigite um número válido !!!");
            printf("\nPressione ENTER para continuar. . .");
            getchar();
        }
    }
}

// Função principal do programa
int main()
{
    // Declaração de variáveis
    size_t i;
    int escolhaMenu;         // Variável para armazenar a escolha do menu do usuário
    int contador = 0;        // Contador para as vendas diárias
    int contadorAnual = 0;   // Contador para o lucro mensal
    float precoQuilo = 0;    // Preço por quilo
    Refeicao vendas[100];    // Array para armazenar as vendas diárias
    LucroMes lucroMeses[12]; // Array para armazenar o lucro mensal

    // Inicialização dos arrays
    for (i = 0; i < sizeof(lucroMeses) / sizeof(lucroMeses[0]); i++)
    {
        lucroMeses[i].nome[0] = '\0';   // Inicializa o nome do mês com uma string vazia
        lucroMeses[i].valorTotal = 0.0; // Inicializa o valor total do mês com 0
    }

    for (i = 0; i < sizeof(vendas) / sizeof(vendas[0]); i++)
    {
        vendas[i].peso = 0.0;  // Inicializa o peso da venda com 0
        vendas[i].preco = 0.0; // Inicializa o preço da venda com 0
    }

    // Configura o locale para português
    setlocale(LC_ALL, "Portuguese");
    // Limpa o console
    limparConsole();

    // Loop infinito para o menu principal
    while (1)
    {
        // Se o preço por quilo ainda não foi definido, solicita ao usuário que o defina
        if (precoQuilo == 0)
        {
            printf("\n-------------------------------");
            printf("\nSISTEMA - RESTAURANTE A QUILO");
            printf("\n-------------------------------\n");
            precoQuilo = definirValorQuilo();
        }

        // Limpa o console e imprime o menu principal
        limparConsole();
        printf("\n-------------------------------");
        printf("\nSISTEMA - RESTAURANTE A QUILO");
        printf("\n-------------------------------");
        printf("\n1 - Registrar Venda Diária");
        printf("\n2 - Resumo Diário");
        printf("\n3 - Registrar Lucro Mensal");
        printf("\n4 - Resumo Anual");
        printf("\n5 - Redefinir o preço do Kg");
        printf("\n6 - Carregar dados dos arquivos");
        printf("\n0 - Encerrar o programa");
        printf("\n-------------------------------");
        printf("\nDigite: ");
        scanf("%d", &escolhaMenu); // Lê a escolha do usuário
        limparBuffer();            // Limpa o buffer

        // Se a escolha não for 0, entra no switch case
        if (escolhaMenu != 0)
        {
            switch (escolhaMenu)
            {
            case 1:
                // Registra uma venda diária
                limparConsole();
                registrarVenda(vendas, sizeof(vendas) / sizeof(vendas[0]), &contador, precoQuilo);
                break;
            case 2:
                // Exibe o resumo diário
                limparConsole();
                resumoDiario(vendas, contador, precoQuilo);
                break;
            case 3:
                // Registra o lucro mensal
                registroLucroMensal(lucroMeses, &contadorAnual);
                break;
            case 4:
                // Exibe o resumo anual
                limparConsole();
                resumoAnual(lucroMeses, contadorAnual);
                break;
            case 5:
                // Redefine o preço por quilo
                limparConsole();
                precoQuilo = definirValorQuilo();
                break;
            case 6:
                // Exibi as informações salvas nos arquivos
                limparConsole();
                exibirDadosArquivos(contadorAnual);
                break;
            default:
                // Imprime uma mensagem de erro se a escolha for inválida
                printf("\nDigite um número válido!!!");
                printf("\nPresione ENTER para continuar. . .");
                getchar();
                break;
            }
        }
        else
        {
            // Se a escolha for 0, sai do loop e encerra o programa
            break;
        }
    }
    // Imprime uma mensagem de encerramento do programa
    printf("\nPrograma Encerrado. . .");
    return 0; // Retorna 0 indicando que o programa terminou com sucesso
}