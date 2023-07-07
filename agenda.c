
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
// uso a função strcspn para poder substitui o \n pelo o \0 pra indicar o fim da string, pra eu consseguir manipular ou comparar as strings que vão está no arquivo
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
// abro o arquivo e adciono os dados no fim do arquivo com o modo de escrita "a"(append), preservando o arquivo antigo ou criando 
// um novo arquivo se não tiver sido criado ainda 
    FILE* arquivo = fopen("contatos.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
// gravo no arquivo os dados no arquivo usando a função fprintf
    fprintf(arquivo, "%s\n%s\n%s\n%s\n", contato.nome, contato.telefone, contato.endereco, contato.email);
// fecha o arquivo 
    fclose(arquivo);

    printf("Contato cadastrado com sucesso.\n");
}

void listarContatos() {

// abro o arquivo no modo leitura 
    FILE* arquivo = fopen("contatos.txt", "r");
// é feita uma verificção se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Nenhum contato encontrado.\n");
        return;
    }

    Contato contato;
    int numContatos = 0;

    printf("Lista de Contatos:\n");
// crio um laço pra percorrer todo o arquivo 
    while (fgets(contato.nome, sizeof(contato.nome), arquivo) != NULL) {
        contato.nome[strcspn(contato.nome, "\n")] = '\0';
        fgets(contato.telefone, sizeof(contato.telefone), arquivo);
        contato.telefone[strcspn(contato.telefone, "\n")] = '\0';
        fgets(contato.endereco, sizeof(contato.endereco), arquivo);
        contato.endereco[strcspn(contato.endereco, "\n")] = '\0';
        fgets(contato.email, sizeof(contato.email), arquivo);
        contato.email[strcspn(contato.email, "\n")] = '\0';
// e printa as informaçoes de cada contanto
        printf("Nome: %s\n", contato.nome);
        printf("Telefone: %s\n", contato.telefone);
        printf("Endereco: %s\n", contato.endereco);
        printf("Email: %s\n\n", contato.email);

        numContatos++;
    }
// quando acabar o laço, feicho o arquivo 
    fclose(arquivo);

    if (numContatos == 0) {
        printf("Nenhum contato encontrado.\n");
    }
}


void buscarContato() {

// peço pro usuario digitar o nome que deseja buscar 
    char nomeBusca[MAX_CHAR];
    printf("Digite o nome do contato a ser buscado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
// abro o arquivo no modo leitura 
    FILE* arquivo = fopen("contatos.txt", "r");
        if (arquivo == NULL) {
        printf("Nenhum contato encontrado.\n");
        return;
    }

    Contato contato;
    int numContatos = 0;
    int encontrado = 0;
// crio um laço pra percorrer todo o arquivo até que seja encontrado o contato que o usuario digitou no começo da função 
    while (fgets(contato.nome, sizeof(contato.nome), arquivo) != NULL) {
        contato.nome[strcspn(contato.nome, "\n")] = '\0';

        fgets(contato.telefone, sizeof(contato.telefone), arquivo);
        contato.telefone[strcspn(contato.telefone, "\n")] = '\0';

        fgets(contato.endereco, sizeof(contato.endereco), arquivo);
        contato.endereco[strcspn(contato.endereco, "\n")] = '\0';

        fgets(contato.email, sizeof(contato.email), arquivo);
        contato.email[strcspn(contato.email, "\n")] = '\0';
// uso a função strcmp para comparar o nome que o usuario digitou no começo da função com o nome do atual contato.nome do laço
// se o teste for verdadeiro,significa que o contato que usuario tava procurando foi encontrado 
        if (strcmp(nomeBusca, contato.nome) == 0) {
            printf("\nContato encontrado:\n");
            printf("Nome: %s\n", contato.nome);
            printf("Telefone: %s\n", contato.telefone);
            printf("Endereco: %s\n", contato.endereco);
            printf("Email: %s\n", contato.email);

            encontrado = 1;
        // como o contato foi encontrado , usamos o break
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
// digito o nome do usuario que desejo atualizar 
    printf("Digite o nome do contato a ser atualizado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
// abro o arquivo no modo leitura
    FILE* arquivo = fopen("contatos.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum contato encontrado.\n");
        return;
    }
// crio um arquivo temporario no modo escrever
    FILE* arquivoTemp = fopen("contatos_temp.txt", "w");
    if (arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    Contato contato;
    int numContatos = 0;
    int encontrado = 0;
// crio um laço para fazer a leitura de todo o arquivo 
    while (fgets(contato.nome, sizeof(contato.nome), arquivo) != NULL) {
        contato.nome[strcspn(contato.nome, "\n")] = '\0';

        fgets(contato.telefone, sizeof(contato.telefone), arquivo);
        contato.telefone[strcspn(contato.telefone, "\n")] = '\0';

        fgets(contato.endereco, sizeof(contato.endereco), arquivo);
        contato.endereco[strcspn(contato.endereco, "\n")] = '\0';

        fgets(contato.email, sizeof(contato.email), arquivo);
        contato.email[strcspn(contato.email, "\n")] = '\0';
    // se o nome que o usuario digitou no começo da função for igual o nome do atual contato.nome 
    // o atual contato é printado e logo depois e  feito outra leitura para para atualizar os dados do atual contato
        if (strcmp(nomeBusca, contato.nome) == 0) {
            printf("Contato encontrado:\n");
            printf("Nome: %s\n", contato.nome);
            printf("Telefone: %s\n", contato.telefone);
            printf("Endereco: %s\n", contato.endereco);
            printf("Email: %s\n", contato.email);

            printf("Digite os novos dados para o contato:\n");
    // como eu disse antes , é feito uma nova leitura para atualizar os dados do contato 
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
    // todos os contato que estão no arquivo é salvo no arquivo temporario , incluindo o contato que foi atualizado 
        fprintf(arquivoTemp, "%s\n%s\n%s\n%s\n", contato.nome, contato.telefone, contato.endereco, contato.email);

        numContatos++;
    }
// fecho os dois arquivos , tanto o original e o temporario  
    fclose(arquivo);
    fclose(arquivoTemp);
// removo o arquivo original 
    remove("contatos.txt");
// e troco o nome do arquivo temporario (que está devidamente atualizado) pelo o nome do arquivo original
    rename("contatos_temp.txt", "contatos.txt");

    if (encontrado) {
        printf("Contato atualizado com sucesso.\n");
    } else {
        printf("Nenhum contato encontrado com o nome '%s'.\n", nomeBusca);
    }
}

void excluirContato() {
    char nomeExcluir[MAX_CHAR];
// digito o nome da pessoal que desejo excluir 
    printf("Digite o nome do contato a ser excluído: ");
    fgets(nomeExcluir,sizeof(nomeExcluir), stdin);
    nomeExcluir[strcspn(nomeExcluir,"\n")] = '\0';

// abro o arquivo no modo leitura
    FILE* arquivo = fopen("contatos.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum contato encontrado.\n");
        return;
    }

// crio um arquivo temporario no modo escrever
    FILE* arquivoTemp = fopen("contatos_temp.txt", "w");
    if (arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    Contato contato;
    int numContatos = 0;
    int excluido = 0;
// crio um laço para fazer a leitura de todo o arquivo 
    while (fgets(contato.nome, sizeof(contato.nome), arquivo) != NULL) {
        contato.nome[strcspn(contato.nome, "\n")] = '\0';

        fgets(contato.telefone, sizeof(contato.telefone), arquivo);
        contato.telefone[strcspn(contato.telefone, "\n")] = '\0';

        fgets(contato.endereco, sizeof(contato.endereco), arquivo);
        contato.endereco[strcspn(contato.endereco, "\n")] = '\0';

        fgets(contato.email, sizeof(contato.email), arquivo);
        contato.email[strcspn(contato.email, "\n")] = '\0';
// se o nome que o usuario digitou no começo da função for igual o nome do atual contato.nome
// uso a função continue , para voltar para a repetição 
        if (strcmp(nomeExcluir, contato.nome) == 0) {
            excluido = 1;
            continue;
        }
// como usei a função continue quando achei o contato que queria excluir, o contato que eu queria excluir não foi salvo 
// na função fprint 
        fprintf(arquivoTemp, "%s\n%s\n%s\n%s\n", contato.nome, contato.telefone, contato.endereco, contato.email);

        numContatos++;
    }

    fclose(arquivo);
    fclose(arquivoTemp);

// fecho os dois arquivos , tanto o original e o temporario  
    remove("contatos.txt");
// e troco o nome do arquivo temporario(que já está devidamente atualizado pois foi excluido o contato desejado) pelo o nome do arquivo original
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


