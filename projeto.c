#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int opc;
#define MAX_CLIENTE 100
#define MAX_PRODUTO 100
#define MAX_TRANSPORTE 100

// estrutura clientes
struct Cliente {
    char nome[100];
    char morada[100];
    int nif;
    int tel;
};

// estrutura produto
struct Produto {
    char nomep[50];
    char marca[50];
    int serie;
    float peso;
};

// estrutura transporte
struct Transporte {
	char destinop[50];
	char destinoc[50];
	char ttransporte[50];
    int nif;
    int serie;
	float preco;
};


//leitura de strings com espaços
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void inserirCliente() {
    printf("\n\n############    Novo Cliente    ############\n");

    // apontador dos clientes e produtos introduzidos
    FILE *clienteFILE;
    // abertura de arquivos binários para clientes e produtos
    clienteFILE = fopen("baseclientes.txt", "ab+");
    // caso ficheiro cliente ou produto não abrir
    if (clienteFILE == NULL) {
        printf("Erro ao abrir o ficheiro");
        return;
    }

    // Indicador de dados na estrutura do novo cliente
    struct Cliente cliente;

    printf("\nNome do cliente: ");
    limparBufferEntrada();
    fgets(cliente.nome, sizeof(cliente.nome), stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = '\0';
    
    printf("\nNIF do cliente: ");
    scanf("%d", &cliente.nif);

    printf("\nMorada do cliente: ");
    limparBufferEntrada();
    fgets(cliente.morada, sizeof(cliente.morada), stdin);
    cliente.morada[strcspn(cliente.morada, "\n")] = '\0';

    printf("\nTelefone do cliente: ");
    scanf("%d", &cliente.tel);
    
    printf("\nCliente adicionado com Sucesso!!\n\n");

    // Reposiciona o ponteiro do arquivo para o final antes de escrever
    fseek(clienteFILE, 0, SEEK_END);  
    // escrita no arquivo binário baseclientes
    fwrite(&cliente, sizeof(struct Cliente), 1, clienteFILE);
    
    fclose(clienteFILE);
}


void inserirProduto() {
    printf("\n\n############    Novo Produto    ############\n");

    // apontador dos clientes e produtos introduzidos
    FILE *produtoFILE;
    // abertura de arquivos binários para clientes e produtos
    produtoFILE = fopen("baseprodutos.txt", "ab+");
    // caso ficheiro cliente ou produto não abrir
    if (produtoFILE == NULL) {
        printf("Erro ao abrir o ficheiro");
        return;
    }

    // Indicador de dados na estrutura do novo produto
    struct Produto produto;

    printf("\nNome do produto: ");
    limparBufferEntrada();
    fgets(produto.nomep, sizeof(produto.nomep), stdin);
    produto.nomep[strcspn(produto.nomep, "\n")] = '\0';

    printf("\nMarca do produto: ");
    fgets(produto.marca, sizeof(produto.marca), stdin);
    produto.marca[strcspn(produto.marca, "\n")] = '\0';

    printf("\nNúmero de série do produto: ");
    scanf("%d", &produto.serie);

    printf("\nPeso em Kg do produto: ");
    scanf("%f", &produto.peso);

    printf("\nProduto adicionado com Sucesso!!\n\n");

    // Reposiciona o ponteiro do arquivo para o final antes de escrever
    fseek(produtoFILE, 0, SEEK_END); 
    // escrita no arquivo binário baseprodutos
    fwrite(&produto, sizeof(struct Produto), 1, produtoFILE);

    fclose(produtoFILE);
}


void inserirTransporte(){
    int tpeso, found = 0;

    printf("\n\n###########  Tipo de Transporte   ############\n");

    // apontador dos transportes e produtos
    FILE *transporteFILE, *produtoFILE, *clienteFILE; 
    // abertura de arquivos binários para transporte, produtos e cliente
    transporteFILE = fopen("basetransportes.txt", "ab+");
    produtoFILE = fopen("baseprodutos.txt", "rb"); 
    clienteFILE = fopen("baseclientes.txt", "rb");
    // caso ficheiro transporte ou produto não abrir
    if (transporteFILE == NULL || clienteFILE == NULL || produtoFILE == NULL){ 
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    struct Transporte transporte;
    struct Produto produto;
    struct Cliente cliente;

    printf("\nIndique o número de série do produto: ");
    scanf("%d", &transporte.serie);
    // Reposiciona o ponteiro do arquivo para o início antes de ler
    fseek(produtoFILE, 0, SEEK_SET);
    while (fread(&produto, sizeof(struct Produto), 1, produtoFILE) == 1 && found == 0) {
        //comparação do numero de serie, guardar peso do produto
        if (transporte.serie == produto.serie) {
            found = 1;
            tpeso = produto.peso;
        }
    }
    //caso numero de serie inválido
    if (found == 0) {
        printf("\nNúmero de série incorreto ou produto não existente!! \nVerifique se colocou os dados corretamente\n");
        main();
    }
    else{
        printf("\nNúmero de série associado com sucesso!!\n");
    }
    
    printf("\nIndique o NIF do cliente: ");
    scanf("%d", &transporte.nif);
    found = 0;
    // Reposiciona o ponteiro do arquivo para o início antes de ler
    fseek(clienteFILE, 0, SEEK_SET);
    while (fread(&cliente, sizeof(struct Cliente), 1, clienteFILE) == 1 && found == 0) {
        //comparação do nif do cliente com nif inserido
        if (transporte.nif == cliente.nif) {
            found = 1;
        }
    }
    //caso numero de nif inválido
    if (found == 0) {
        printf("\nNIF incorreto ou cliente não existente!! \nVerifique se colocou os dados corretamente\n");
        inserirTransporte();
    }
    else{
        printf("\nNIF associado com sucesso!!\n");
    }

    // Tipo de transporte
    printf("\nTipo de transporte a selecionar: \n1. Avião (10.00€/kg) \t2. Camião (2.50€/Kg) \t3. Navio (5.00€/Kg)");
    printf("\nSelecione a opção: ");
    scanf("%d", &opc);

    switch (opc) {
        case 1:
            printf("\nTransporte Avião selecionado com sucesso\n");
            strcpy(transporte.ttransporte, "Avião");
            transporte.preco = (tpeso * 10);
            break;
        case 2:
            printf("\nTransporte Camião selecionado com sucesso\n");
            strcpy(transporte.ttransporte, "Camião");
            transporte.preco = (tpeso * 2.5);
            break;
        case 3:
            printf("\nTransporte Navio selecionado com sucesso\n");
            strcpy(transporte.ttransporte, "Navio");
            transporte.preco = (tpeso * 5);
            break;
        default:
            printf("\nOpção inválida. Tente novamente.\n");
            return inserirTransporte();
    }

  
    printf("\nIndique o país para onde pretende enviar o produto: ");
    limparBufferEntrada();
    fgets(transporte.destinop, sizeof(transporte.destinop), stdin);
    transporte.destinop[strcspn(transporte.destinop, "\n")] = '\0';

    printf("\nIndique a cidade para onde pretende enviar o produto: ");
    fgets(transporte.destinoc, sizeof(transporte.destinoc), stdin);
    transporte.destinoc[strcspn(transporte.destinoc, "\n")] = '\0';

    printf("\nPreço do transporte: %.2f\n", transporte.preco);


    printf("\nTransporte adicionado com Sucesso!!\n\n");

    // Reposiciona o ponteiro do arquivo para o final antes de escrever
    fseek(transporteFILE, 0, SEEK_END);  
    // escrita no arquivo binário baseclientes
    fwrite(&transporte, sizeof(struct Cliente), 1, transporteFILE);
    
    fclose(transporteFILE);
    fclose(clienteFILE);
    fclose(produtoFILE);
}


//joao
void pesquisarCliente() {
    int pnif, ptel, numtransporte = 0, found = 0, show = 1;
    float gastos = 0;
    char pnome[100];

    printf("\n\n############    Pesquisa Cliente    ############\n");

    // apontador dos clientes e do ficheiro temporário
    FILE *clienteFILE, *produtoFILE, *transporteFILE;
    // abertura de arquivos binários para clientes
    clienteFILE = fopen("baseclientes.txt", "rb");
    transporteFILE = fopen("basetransportes.txt", "rb");
    // caso ficheiro cliente ou temporário não abrir
    if (clienteFILE == NULL || produtoFILE == NULL || transporteFILE == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    struct Cliente cliente;
    struct Transporte transporte[MAX_TRANSPORTE];


    // Tipo de pesquisa do cliente
    printf("Introduza o método de pesquisa do cliente: \n1. NIF do cliente \t2. Nome do cliente \t3. Telefone do Cliente");
    printf("\nSelecione a opção: ");
    scanf("%d", &opc);

    switch (opc) {
        case 1:
            printf("\nIntroduza o NIF do cliente: ");
            scanf("%d", &pnif);
            break;
        case 2:
            printf("\nIntroduza o nome: ");
            scanf("%s", &pnome);
            break;
        case 3:
            printf("\nIntroduza o contacto telefónico: ");
            scanf("%d", &ptel);
            break;
        default:
            printf("\nOpção inválida. Tente novamente.\n");
            return pesquisarCliente();
    }

    while (fread(&transporte[numtransporte], sizeof(struct Transporte), 1, transporteFILE) == 1){
        numtransporte++;
    }

    // Reposiciona o ponteiro do arquivo para o início antes de ler
    fseek(clienteFILE, 0, SEEK_SET);
    while (fread(&cliente, sizeof(struct Cliente), 1, clienteFILE) == 1 && found == 0) {
        //strcmp --> string compare
        if ((pnif == cliente.nif) || (strcmp(pnome, cliente.nome) == 0) || (ptel == cliente.tel)) {
            found = 1;
            pnif = cliente.nif;
            //mostrar dados do cliente
            printf("\n\n############    Dados do Cliente    ############\n");
            printf("Nome Cliente: %s \nMorada Cliente: %s \nNIF Cliente: %d \nTelefone Cliente: %d", cliente.nome, cliente.morada, cliente.nif, cliente.tel);
        }
    }

    //caso cliente não encontrado
    if (found == 0) {
        printf("\nCliente não encontrado!! \nVerifique se colocou os dados corretamente\n");
    } 

    fclose(clienteFILE);
    fclose(transporteFILE);

    for(int i = 0; i < numtransporte; i++){
        if(transporte[i].nif == pnif && cliente.nif == pnif){
            gastos += transporte[i].preco;
            printf("\nQuanto já gastou: %.2f€\n", gastos);
            printf("\n%d", numtransporte);
        }
    }

    // Retorno ao menu principal
    printf("\n1. Voltar ao menu  \t2. Voltar a verificar dados do cliente \t0. Sair");
    printf("\nSelecione a opção: ");
    scanf("%d", &opc);

    switch (opc){
        do{
            case 1:
                //return para função main
                main();
                break;
            case 2:
                //return para pesquisa de cliente outra vez
                pesquisarCliente();
                break;
            case 0:
                //sair do programa
                printf("\nA sair do Programa...");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }while (opc =! 0);
    }
}


void pesquisarProduto() {
    int pserie, found = 0;
    char pnomep[100];

    printf("\n\n############    Pesquisa Produto    ############\n");

    // apontador dos produtos introduzidos
    FILE *produtoFILE;
    // abertura de arquivos binários para produtos
    produtoFILE = fopen("baseprodutos.txt", "rb");
    // caso ficheiro produto não abrir
    if (produtoFILE == NULL) {
        printf("Erro ao abrir o ficheiro...");
        return;
    }

    struct Produto produto;

    // Tipo de pesquisa do Produto
    printf("Introduza o método de pesquisa do Produto: \n1. Nº de serie \t2. Nome do Produto\n");
    printf("\nSelecione a opção: ");
    scanf("%d", &opc);

    switch (opc) {
        case 1:
            printf("\nIntroduza o Nº de serie do produto: ");
            scanf("%d", &pserie);
            break;
        case 2:
            printf("\nIntroduza o nome: ");
            scanf("%s", pnomep);
            break;
        default:
            printf("\nOpção inválida. Tente novamente.");
            return;
    }

    // Reposiciona o ponteiro do arquivo para o início antes de ler
    fseek(produtoFILE, 0, SEEK_SET);
    while (fread(&produto, sizeof(struct Produto), 1, produtoFILE) == 1 && found == 0) {
        //strcmp --> string compare
        if ((pserie == produto.serie) || (strcmp(pnomep, produto.nomep) == 0)) {
            found = 1;

            //mostrar dados do produto
            printf("\n\n############    Dados do Produto    ############\n");
            printf("Nome do produto: %s \nMarca do produto: %s \nNúmero de série: %d \nPeso em Kg do produto: %.2f\n", produto.nomep, produto.marca, produto.serie, produto.peso);
        }
    }

    //caso produto não encontrado
    if (found == 0) {
        printf("\nProduto não encontrado!! \nVerifique se colocou os dados corretamente\n");
    }

    fclose(produtoFILE);

    // Retorno ao menu principal
    printf("\n1. Voltar ao menu  \t2. Voltar a verificar dados do produto \t0. Sair");
    printf("\nSelecione a opção: ");
    scanf("%d", &opc);

    switch (opc){
        do{
            case 1:
                //return para função main
                main();
                break;
            case 2:
                //return para a função outra vez
                pesquisarProduto();
                break;
            case 0:
                //sair do programa
                printf("\nA sair do Programa...");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }while (opc != 0);
    }
}


void pesquisarTransporte(){
    int pnif, pserie, numcliente = 0, numproduto = 0, numtransporte = 0, found = 0;

    printf("\n\n############    Pesquisa Transporte    ############\n"); 

    // apontador dos clientes e do ficheiro temporário
    FILE *clienteFILE, *produtoFILE, *transporteFILE;
    // abertura de arquivos binários para clientes
    clienteFILE = fopen("baseclientes.txt", "rb");
    produtoFILE = fopen("baseprodutos.txt", "rb");
    transporteFILE = fopen("basetransportes.txt", "rb");
    // caso ficheiro cliente, produto ou transporte não abrir
    if (clienteFILE == NULL || produtoFILE == NULL || transporteFILE == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    struct Cliente cliente[MAX_CLIENTE];
    struct Produto produto[MAX_PRODUTO];
    struct Transporte transporte[MAX_TRANSPORTE];

        // Reposiciona o ponteiro do arquivo para o início antes de ler
        fseek(clienteFILE, 0, SEEK_SET);
        //verificar numero de estruturas de cada Struct
        while (fread(&cliente[numcliente], sizeof(struct Cliente), 1, clienteFILE) == 1){
            numcliente++;
        }
        fseek(transporteFILE, 0, SEEK_SET);
        while (fread(&transporte[numtransporte], sizeof(struct Transporte), 1, transporteFILE) == 1){
            numtransporte++;
        }
        fseek(produtoFILE, 0, SEEK_SET);
        while (fread(&produto[numproduto], sizeof(struct Produto), 1, produtoFILE) == 1) {
            numproduto++;
        }
            
        //fechar ficheiro binário
        fclose(transporteFILE);
        fclose(produtoFILE);
        fclose(clienteFILE);


    // Tipo de pesquisa do cliente
    printf("Introduza o método de pesquisa do transporte: \n1. NIF do cliente \t2. Número de série do produto");
    printf("\nSelecione a opção: ");
    scanf("%d", &opc);

    switch (opc) {
        case 1:
            printf("\nIntroduza o NIF do cliente: ");
            scanf("%d", &pnif);

            //pesquisar transportes
            printf("\n\n############    Dados do Transporte    ############\n");
            for (int t = 0; t < numtransporte; t++){
                if(transporte[t].nif == pnif){
                    for (int c = 0; c < numcliente; c++) {
                        if (cliente[c].nif == pnif) {
                            for (int p = 0; p < numproduto; p++){
                                if (produto[p].serie == transporte[t].serie) {

                                    found = 1;
                                    //mostrar dados do transporte   
                                    printf("\nNome Cliente: %s \tNIF Cliente: %d \tTelefone Cliente: %d\n", cliente[c].nome, cliente[c].nif, cliente[c].tel);                 
                                    printf("Tipo de Transporte selecionado: %s \tValor a pagar pelo transporte: %.2f€ \tPaís de entrega: %s \tCidade de entrega: %s\n", transporte[t].ttransporte, transporte[t].preco, transporte[t].destinop, transporte[t].destinoc);
                                    printf("Nome do produto: %s \tMarca do produto: %s \tNúmero de série: %d \tPeso em Kg do produto: %.2f\n", produto[p].nomep, produto[p].marca, produto[p].serie, produto[p].peso);
                                }
                            }
                        }
                    }
                }
            }
            if (found == 0) printf("Transporte não encontrado");
            break;
        case 2:
            printf("\nIntroduza o número de série: ");
            scanf("%d", &pserie);

            //pesquisar transportes
            printf("\n\n############    Dados do Transporte    ############\n");
            for (int y = 0; y < numtransporte; y++){
                if(pserie == transporte[y].serie){
                    found = 1;
                    for (int a = 0; a < numcliente; a++) {
                        if (cliente[a].nif == transporte[y].nif) {
                            for (int i = 0; i < numproduto; i++){
                                if (produto[i].serie == transporte[y].serie) {

                                    found = 1;
                                    //mostrar dados do transporte   
                                    printf("\nNome Cliente: %s \tNIF Cliente: %d \tTelefone Cliente: %d\n", cliente[y].nome, cliente[y].nif, cliente[y].tel);                 
                                    printf("Tipo de Transporte selecionado: %s \tValor a pagar pelo transporte: %.2f€ \tPaís de entrega: %s \tCidade de entrega: %s\n", transporte[a].ttransporte, transporte[a].preco, transporte[a].destinop, transporte[a].destinoc);
                                    printf("Nome do produto: %s \tMarca do produto: %s \tNúmero de série: %d \tPeso em Kg do produto: %.2f\n", produto[i].nomep, produto[i].marca, produto[i].serie, produto[i].peso);
                                }
                            }
                        }
                    }
                }
            }
            if (found == 0) printf("Transporte não encontrado");
            break;
        default:
            printf("\nOpção inválida. Tente novamente.\n");
            return pesquisarTransporte();
    }

    // Retorno ao menu principal
    printf("\n\n1. Voltar ao menu  \t2. Voltar a verificar transporte \t0. Sair");
    printf("\nSelecione a opção: ");
    scanf("%d", &opc);

    switch (opc){
        do{
            case 1:
                //return para função main
                main();
                break;
            case 2:
                //return para a função outra vez
                return pesquisarTransporte();
                break;
            case 0:
                //sair do programa
                printf("\nA sair do Programa...");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }while (opc != 0);
    }
}


//ingles
void alterarCliente(){
    int pnif, novoNIF, ptel, found = 0;
    char pnome[100];

    printf("\n\n############    Alterar Cliente    ############\n");

    // apontador dos clientes e do ficheiro temporário
    FILE *clienteFile;
    FILE *tempFile;
    // abertura de arquivos binários para clientes e ficheiro temporário
    clienteFile = fopen("baseclientes.txt", "rb");
    tempFile = fopen("temp.txt", "wb");
    // caso ficheiro cliente ou temporário não abrir
    if (clienteFile == NULL || tempFile == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    struct Cliente cliente;

    // Tipo de pesquisa do cliente
    printf("Introduza o método de pesquisa do cliente: \n1. NIF do cliente \t2. Nome do cliente \t3. Telefone do Cliente");
    printf("\nSelecione a opção: ");
    scanf("%d", &opc);

    switch (opc) {
        case 1:
            printf("\nIntroduza o NIF do cliente: ");
            scanf("%d", &pnif);
            break;
        case 2:
            printf("\nIntroduza o nome: ");
            scanf("%s", &pnome);
            break;
        case 3:
            printf("\nIntroduza o contacto telefónico: ");
            scanf("%d", &ptel);
            break;
        default:
            printf("\nOpção inválida. Tente novamente.\n");
            return alterarCliente();
    }

    while (fread(&cliente, sizeof(struct Cliente), 1, clienteFile) == 1){
        //tipo de pesquisa
        if ((pnif == cliente.nif) || (strcmp(pnome, cliente.nome) == 0) || (ptel == cliente.tel)) {
            found = 1;
            //atualização dos dados da estrutura do cliente
            printf("\nNome Atual: %s\n", cliente.nome);
            printf("Novo Nome: ");
            limparBufferEntrada();
            fgets(cliente.nome, sizeof(cliente.nome), stdin);
            cliente.nome[strcspn(cliente.nome, "\n")] = '\0';

            printf("\nNIF Atual: %d\n", cliente.nif);
            printf("Novo NIF: ");
            scanf("%d", &novoNIF);
            cliente.nif = novoNIF;

            printf("\nMorada Atual: %s\n", cliente.morada);
            printf("Nova Morada: ");
            limparBufferEntrada();
            fgets(cliente.morada, sizeof(cliente.morada), stdin);
            cliente.morada[strcspn(cliente.morada, "\n")] = '\0';

            printf("\nTelefone Atual: %d\n", cliente.tel);
            printf("Novo Telefone: ");
            scanf("%d", &cliente.tel);

            // posicionar o ponteiro no final
            fseek(tempFile, 0, SEEK_END);
            fwrite(&cliente, sizeof(struct Cliente), 1, tempFile);

            printf("\nCliente Alterado com Sucesso!!\n");
        }
        else{
            // Se não é o cliente a ser alterado, apenas copie para o arquivo temporário
            fseek(tempFile, 0, SEEK_END);
            fwrite(&cliente, sizeof(struct Cliente), 1, tempFile);
        }
    }

    fclose(clienteFile);
    fclose(tempFile);

    if (found == 0){
        printf("Cliente nao Encontrado.\n");
        remove("temp.txt");
    }
    else{
        remove("baseclientes.txt");
        rename("temp.txt", "baseclientes.txt");
    }
}


void alterarProduto(){
    int pserie, found = 0;
    char pnomep[100];

    printf("\n\n############    Alterar Produto    ############\n");

    // apontador dos produto e do ficheiro temporário
    FILE *produtoFile;
    FILE *tempFile;
    // abertura de arquivos binários para produtos e ficheiro temporário
    produtoFile = fopen("baseprodutos.txt", "rb");
    tempFile = fopen("temp.txt", "wb");
    // caso ficheiro produto ou temporário não abrir
    if (produtoFile == NULL || tempFile == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    struct Produto produto;

    // Tipo de pesquisa do produto
    printf("\nIntroduza o método de pesquisa do produto: \n1. Nº de Série do produto \t2. Nome do produto");
    printf("\nSelecione a opção: ");
    scanf("%d", &opc);

    switch (opc) {
        case 1:
            printf("\nIntroduza o Nº de Série do produto: ");
            scanf("%d", &pserie);
            break;
        case 2:
            printf("\nIntroduza o nome do produto: ");
            scanf("%s", &pnomep);
            break;
        default:
            printf("\nOpção inválida. Tente novamente.\n");
            return alterarProduto();
    }

    while (fread(&produto, sizeof(struct Produto), 1, produtoFile) == 1){
        //tipo de pesquisa
        if ((pserie == produto.serie) || (strcmp(pnomep, produto.nomep) == 0)) {
            found = 1;
            //atualização dos dados da estrutura do produto
            printf("\nNome o produto Atual: %s", produto.nomep);
            printf("\nNovo Nome: ");
            limparBufferEntrada();
            fgets(produto.nomep, sizeof(produto.nomep), stdin);
            produto.nomep[strcspn(produto.nomep, "\n")] = '\0';

            printf("\nMarca Atual: %s", produto.marca);
            printf("\nNova Marca: ");
            fgets(produto.marca, sizeof(produto.marca), stdin);
            produto.marca[strcspn(produto.marca, "\n")] = '\0';

            printf("\nNº de Série Atual: %d", produto.serie);
            printf("\nNovo Nº de Série: ");
            scanf("%d", &produto.serie);

            printf("\nPeso em Kg atual: %.2f", produto.peso);
            printf("\nNovo Peso em Kg: ");
            scanf("%f", &produto.peso);

            // posicionar o ponteiro no final
            fseek(tempFile, 0, SEEK_END);
            fwrite(&produto, sizeof(struct Produto), 1, tempFile);

            printf("\nProduto Alterado com Sucesso!!\n");
        }
        else{
            // Se não é o produto a ser alterado, apenas copie para o arquivo temporário
            fseek(tempFile, 0, SEEK_END);
            fwrite(&produto, sizeof(struct Produto), 1, tempFile);
        }
    }

    fclose(produtoFile);
    fclose(tempFile);


    if (found == 0){
        printf("Produto nao Encontrado.\n");
        remove("temp.txt");
    }
    else{
        remove("baseprodutos.txt");
        rename("temp.txt", "baseprodutos.txt");
    }
}

//Mira
void apagarCliente(){
    int pnif, novoNIF, ptel, found = 0;
    char pnome[100];

    printf("\n\n############    Apagar Cliente    ############\n");

    // apontador dos clientes e do ficheiro temporário
    FILE *clienteFILE;
    FILE *tempFILE;
    // abertura de arquivos binários para clientes e ficheiro temporário
    clienteFILE = fopen("baseclientes.txt", "rb");
    tempFILE = fopen("temp.txt", "wb");
    // caso ficheiro cliente ou temporário não abrir
    if (clienteFILE == NULL || tempFILE == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    struct Cliente cliente;

    // Tipo de pesquisa do cliente
    printf("Introduza o método de pesquisa do cliente: \n1. NIF do cliente \t2. Nome do cliente \t3. Telefone do Cliente");
    printf("\nSelecione a opção: ");
    scanf("%d", &opc);

    switch (opc) {
        case 1:
            printf("\nIntroduza o NIF do cliente: ");
            scanf("%d", &pnif);
            break;
        case 2:
            printf("\nIntroduza o nome: ");
            scanf("%s", &pnome);
            break;
        case 3:
            printf("\nIntroduza o contacto telefónico: ");
            scanf("%d", &ptel);
            break;
        default:
            printf("\nOpção inválida. Tente novamente.\n");
            return alterarCliente();
    }

    while (fread(&cliente, sizeof(struct Cliente), 1, clienteFILE) == 1){
        //tipo de pesquisa
        if ((pnif == cliente.nif) || (strcmp(pnome, cliente.nome) == 0) || (ptel == cliente.tel)) {
            found = 1;
            
            printf("\nEstes são os dados do produto selecionado: ");
            printf("\nNome Atual: %s\n", cliente.nome);
            printf("\nNIF Atual: %d\n", cliente.nif);
            printf("\nMorada Atual: %s\n", cliente.morada);
            printf("\nTelefone Atual: %d\n", cliente.tel);
            printf("\n1. Confirmar eliminação \t2. Cancelar eliminação \nSelecione a opção: ");
            scanf("%d", &opc);
            
            switch (opc){
            case 1:
                printf("\nCliente Apagado com Sucesso!!\n");
                break;
            case 2:
                printf("\nCliente não Apagado\n");
                fseek(tempFILE, 0, SEEK_END);
                fwrite(&cliente, sizeof(struct Cliente), 1, tempFILE);
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
                return apagarCliente();
            }

            
            
        }
        else{
            // Se não é o cliente a ser alterado, apenas copie para o arquivo temporário
            fseek(tempFILE, 0, SEEK_END);
            fwrite(&cliente, sizeof(struct Cliente), 1, tempFILE);
        }
    }

    fclose(clienteFILE);
    fclose(tempFILE);

    if (found == 0){
        printf("Cliente nao Encontrado.\n");
        remove("temp.txt");
    }
    else{
        remove("baseclientes.txt");
        rename("temp.txt", "baseclientes.txt");
    }
}


void apagarProduto(){
    int pserie, found = 0;
    char pnomep[100];

    printf("\n\n############    Apagar Produto    ############\n");

    // apontador dos produto e do ficheiro temporário
    FILE *produtoFILE;
    FILE *tempFILE;
    // abertura de arquivos binários para produtos e ficheiro temporário
    produtoFILE = fopen("baseprodutos.txt", "rb");
    tempFILE = fopen("temp.txt", "wb");
    // caso ficheiro produto ou temporário não abrir
    if (produtoFILE == NULL || tempFILE == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    struct Produto produto;

    // Tipo de pesquisa do produto
    printf("\nIntroduza o método de pesquisa do produto: \n1. Nº de Série do produto \t2. Nome do produto");
    printf("\nSelecione a opção: ");
    scanf("%d", &opc);

    switch (opc) {
        case 1:
            printf("\nIntroduza o Nº de Série do produto: ");
            scanf("%d", &pserie);
            break;
        case 2:
            printf("\nIntroduza o nome do produto: ");
            scanf("%s", &pnomep);
            break;
        default:
            printf("\nOpção inválida. Tente novamente.\n");
            return apagarProduto();
    }

    while (fread(&produto, sizeof(struct Produto), 1, produtoFILE) == 1){
        //tipo de pesquisa
        if ((pserie == produto.serie) || (strcmp(pnomep, produto.nomep) == 0)) {
            found = 1;
            //atualização dos dados da estrutura do produto
           
            printf("\nEstes são os dados do produto selecionado: ");
            printf("\nNome o produto Atual: %s", produto.nomep);
            printf("\nMarca Atual: %s", produto.marca);
            printf("\nNº de Série Atual: %d", produto.serie);
            printf("\nPeso em Kg atual: %.2f\n", produto.peso);
            printf("\n1. Confirmar eliminação \t2. Cancelar eliminação \nSelecione a opção: ");
            scanf("%d", &opc);
            
            
            switch (opc){
            case 1:
                printf("\nProduto Apagado com Sucesso!!\n");
                break;
            case 2:
                printf("\nProduto não Apagado\n");
                fseek(tempFILE, 0, SEEK_END);
                fwrite(&produto, sizeof(struct Produto),1, tempFILE);
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
                return apagarProduto();
            }

        
        }
        else{
            // Se não é o produto a ser alterado, apenas copia para o arquivo temporário
            fseek(tempFILE, 0, SEEK_END);
            fwrite(&produto, sizeof(struct Produto), 1, tempFILE);
        }
    }

    fclose(produtoFILE);
    fclose(tempFILE);


    if (found == 0){
        printf("Produto não Encontrado.\n");
        remove("temp.txt");
    }
    else{
        remove("baseprodutos.txt");
        rename("temp.txt", "baseprodutos.txt");
    }
}


//menu principal
int main(){
    //limpar terminal
    system ("cls");
    do {
        // Exibir o menu principal
        printf("\n############  TRANSPORTA-TUDO Lda Menu   ############\n");
        printf("1. Inserir Cliente\n");
        printf("2. Inserir Produto\n");
        printf("3. Pesquisar Cliente\n");
        printf("4. Pesquisar Produto\n");
        printf("5. Alterar Cliente\n");
        printf("6. Alterar Produto\n");
        printf("7. Apagar Cliente\n");
        printf("8. Apagar Produto\n");
        printf("9. Inserir transporte\n");
        printf("10. Pesquisar transporte\n");
        printf("0. Sair\n");
        printf("Selecione a opção: ");
        // Ler a opção do usuário
        scanf("%d", &opc);

        // Executar a opção escolhida
        switch (opc) {
            case 1:
                inserirCliente();
                break;
            case 2:
                inserirProduto();
                break;
            case 3:
                pesquisarCliente();
                break;
            case 4:
                pesquisarProduto();
                break;
            case 5:
                alterarCliente();
                break;
            case 6:
                alterarProduto();
                break;
            case 7:
                apagarCliente();
                break;
            case 8:
                apagarProduto();
                break;
            case 9:
                inserirTransporte();
                break;
            case 10:
                pesquisarTransporte();
                break;
            case 0:
                printf("\nA sair do programa...");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (opc != 0);
    return 0;
}