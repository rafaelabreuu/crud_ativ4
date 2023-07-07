




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100

typedef struct {
    char nome[MAX_CHAR];
    char telefone[MAX_CHAR];
    char endereco[MAX_CHAR];
    char email[MAX_CHAR];
} Contato;

void cadastrarContato() {
    Contato contato;

    printf("Nome: ");
    fgets(contato.nome, sizeof(contato.nome), stdin);
    contato.nome[strcspn(contato.nome, "\n")] = '\0';

    printf("Telefone: ");
    fgets(contato.telefone, sizeof(contato.telefone), stdin);
    contato.telefone[strcspn(contato.telefone, "\n")] = '\0';

    printf("Endereco: ");
    fgets(contato.endereco, sizeof(contato.endereco), stdin);
    contato.endereco[strcspn(contato.endereco, "\n")] = '\0';

    printf("Email: ");
    fgets(contato.email, sizeof(contato.email), stdin);
    contato.email[strcspn(contato.email, "\n")] = '\0';

    FILE* arquivo = fopen("contatos.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(arquivo, "%s\n%s\n%s\n%s\n", contato.nome, contato.telefone, contato.endereco, contato.email);

    fclose(arquivo);

    printf("Contato cadastrado com sucesso.\n");
}

void listarContatos() {
    FILE* arquivo = fopen("contatos.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum contato encontrado.\n");
        return;
    }

    Contato contato;
    int numContatos = 0;

    printf("Lista de Contatos:\n");

    while (fgets(contato.nome, sizeof(contato.nome), arquivo) != NULL) {
        contato.nome[strcspn(contato.nome, "\n")] = '\0';
        fgets(contato.telefone, sizeof(contato.telefone), arquivo);
        contato.telefone[strcspn(contato.telefone, "\n")] = '\0';
        fgets(contato.endereco, sizeof(contato.endereco), arquivo);
        contato.endereco[strcspn(contato.endereco, "\n")] = '\0';
        fgets(contato.email, sizeof(contato.email), arquivo);
        contato.email[strcspn(contato.email, "\n")] = '\0';

        printf("Nome: %s\n", contato.nome);
        printf("Telefone: %s\n", contato.telefone);
        printf("Endereco: %s\n", contato.endereco);
        printf("Email: %s\n\n", contato.email);

        numContatos++;
    }

    fclose(arquivo);

    if (numContatos == 0) {
        printf("Nenhum contato encontrado.\n");
    }
}


void buscarContato() {
    char nomeBusca[MAX_CHAR];
    printf("Digite o nome do contato a ser buscado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    FILE* arquivo = fopen("contatos.txt", "r");
        if (arquivo == NULL) {
        printf("Nenhum contato encontrado.\n");
        return;
    }

    Contato contato;
    int numContatos = 0;
    int encontrado = 0;

    while (fgets(contato.nome, sizeof(contato.nome), arquivo) != NULL) {
        contato.nome[strcspn(contato.nome, "\n")] = '\0';

        fgets(contato.telefone, sizeof(contato.telefone), arquivo);
        contato.telefone[strcspn(contato.telefone, "\n")] = '\0';

        fgets(contato.endereco, sizeof(contato.endereco), arquivo);
        contato.endereco[strcspn(contato.endereco, "\n")] = '\0';

        fgets(contato.email, sizeof(contato.email), arquivo);
        contato.email[strcspn(contato.email, "\n")] = '\0';

        if (strcmp(nomeBusca, contato.nome) == 0) {
            printf("\nContato encontrado:\n");
            printf("Nome: %s\n", contato.nome);
            printf("Telefone: %s\n", contato.telefone);
            printf("Endereco: %s\n", contato.endereco);
            printf("Email: %s\n", contato.email);

            encontrado = 1;
            break;
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Nenhum contato encontrado com o nome '%s'.\n", nomeBusca);
    }
}

void atualizarContato() {
    char nomeBusca[MAX_CHAR];
    printf("Digite o nome do contato a ser atualizado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    FILE* arquivo = fopen("contatos.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum contato encontrado.\n");
        return;
    }

    FILE* arquivoTemp = fopen("contatos_temp.txt", "w");
    if (arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    Contato contato;
    int numContatos = 0;
    int encontrado = 0;

    while (fgets(contato.nome, sizeof(contato.nome), arquivo) != NULL) {
        contato.nome[strcspn(contato.nome, "\n")] = '\0';

        fgets(contato.telefone, sizeof(contato.telefone), arquivo);
        contato.telefone[strcspn(contato.telefone, "\n")] = '\0';

        fgets(contato.endereco, sizeof(contato.endereco), arquivo);
        contato.endereco[strcspn(contato.endereco, "\n")] = '\0';

        fgets(contato.email, sizeof(contato.email), arquivo);
        contato.email[strcspn(contato.email, "\n")] = '\0';

        if (strcmp(nomeBusca, contato.nome) == 0) {
            printf("Contato encontrado:\n");
            printf("Nome: %s\n", contato.nome);
            printf("Telefone: %s\n", contato.telefone);
            printf("Endereco: %s\n", contato.endereco);
            printf("Email: %s\n", contato.email);

            printf("Digite os novos dados para o contato:\n");

            printf("Novo Nome: ");
            fgets(contato.nome, sizeof(contato.nome), stdin);
            contato.nome[strcspn(contato.nome, "\n")] = '\0';

            printf("Novo Telefone: ");
            fgets(contato.telefone, sizeof(contato.telefone), stdin);
            contato.telefone[strcspn(contato.telefone, "\n")] = '\0';

            printf("Novo Endereco: ");
            fgets(contato.endereco, sizeof(contato.endereco), stdin);
            contato.endereco[strcspn(contato.endereco, "\n")] = '\0';

            printf("Novo Email: ");
            fgets(contato.email, sizeof(contato.email), stdin);
            contato.email[strcspn(contato.email, "\n")] = '\0';

            encontrado = 1;
        }

        fprintf(arquivoTemp, "%s\n%s\n%s\n%s\n", contato.nome, contato.telefone, contato.endereco, contato.email);

        numContatos++;
    }

    fclose(arquivo);
    fclose(arquivoTemp);

    remove("contatos.txt");
    rename("contatos_temp.txt", "contatos.txt");

    if (encontrado) {
        printf("Contato atualizado com sucesso.\n");
    } else {
        printf("Nenhum contato encontrado com o nome '%s'.\n", nomeBusca);
    }
}

void excluirContato() {
    char nomeExcluir[MAX_CHAR];
    printf("Digite o nome do contato a ser excluído: ");
    fgets(nomeExcluir,sizeof(nomeExcluir), stdin);
    nomeExcluir[strcspn(nomeExcluir,"\n")] = '\0';

    FILE* arquivo = fopen("contatos.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum contato encontrado.\n");
        return;
    }

    FILE* arquivoTemp = fopen("contatos_temp.txt", "w");
    if (arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    Contato contato;
    int numContatos = 0;
    int excluido = 0;

    while (fgets(contato.nome, sizeof(contato.nome), arquivo) != NULL) {
        contato.nome[strcspn(contato.nome, "\n")] = '\0';

        fgets(contato.telefone, sizeof(contato.telefone), arquivo);
        contato.telefone[strcspn(contato.telefone, "\n")] = '\0';

        fgets(contato.endereco, sizeof(contato.endereco), arquivo);
        contato.endereco[strcspn(contato.endereco, "\n")] = '\0';

        fgets(contato.email, sizeof(contato.email), arquivo);
        contato.email[strcspn(contato.email, "\n")] = '\0';

        if (strcmp(nomeExcluir, contato.nome) == 0) {
            excluido = 1;
            continue;
        }

        fprintf(arquivoTemp, "%s\n%s\n%s\n%s\n", contato.nome, contato.telefone, contato.endereco, contato.email);

        numContatos++;
    }

    fclose(arquivo);
    fclose(arquivoTemp);

    remove("contatos.txt");
    rename("contatos_temp.txt", "contatos.txt");

    if (excluido) {
        printf("Contato excluído com sucesso.\n");
    } else {
        printf("Nenhum contato encontrado com o nome '%s'.\n", nomeExcluir);
}
}

int main() {
int opcao;
while (1) {
    printf("\nAgenda de Contatos\n");
    printf("1. Cadastrar novo contato\n");
    printf("2. Listar contatos\n");
    printf("3. Buscar contato\n");
    printf("4. Excluir contato\n");
    printf("5. Atualizar contato\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar(); // Limpa o buffer do teclado

    switch (opcao) {
        case 1:
            cadastrarContato();
            break;
        case 2:
            listarContatos();
            break;
        case 3:
            buscarContato();
            break;
        case 4:
            excluirContato();
            break;

        case 5:
            atualizarContato();
            break;

        case 6:
            printf("Encerrando o programa...\n");
            exit(0);
        default:
            printf("Opção inválida. Tente novamente.\n");
            break;
    }
}
return 0;

}


