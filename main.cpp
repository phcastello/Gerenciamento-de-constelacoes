//trabalho final algoritmos 2
//versão: v1.0

#include<bits/stdc++.h>
#define nl std::cout<<"\n";

typedef struct{
    std::string nome;
    int principaisEstrelas;
    char hemisferio; //N para norte e S para sul
    std::string descricao;
} constelacao;

void aumentarCatalogo(constelacao *&catalogo, int capacidade){
    capacidade *= 2;
    constelacao *novoCatalogo = new constelacao[capacidade];
    for (int i = 0; i < capacidade / 2; i++) {
        novoCatalogo[i] = catalogo[i];
    }
    delete[] catalogo;
    catalogo = novoCatalogo;
}

int buscaBinaria(constelacao *&catalogo, int tamanho, const std::string &nome){
    int left = 0, right = tamanho - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (catalogo[mid].nome == nome) {
            return mid;
        } else if (catalogo[mid].nome < nome) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Não encontrado
}

void merge(constelacao *catalogo, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    constelacao *catalogoEsquerda = new constelacao[n1];
    constelacao *catalogoDireita = new constelacao[n2];

    // Copia dados para os arrays temporários
    for (int i = 0; i < n1; i++)
        catalogoEsquerda[i] = catalogo[left + i];
    for (int j = 0; j < n2; j++)
        catalogoDireita[j] = catalogo[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (catalogoEsquerda[i].nome < catalogoDireita[j].nome) {
            catalogo[k++] = catalogoEsquerda[i++];
        } else {
            catalogo[k++] = catalogoDireita[j++];
        }
    }

    while (i < n1) {
        catalogo[k] = catalogoEsquerda[i];
        i++;
        k++;
    }

    while (j < n2) {
        catalogo[k] = catalogoDireita[j];
        j++;
        k++;
    }
}

void mergeSort(constelacao *catalogo, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordena a primeira e a segunda metade
        mergeSort(catalogo, left, mid);
        mergeSort(catalogo, mid + 1, right);

        // Mescla as duas metades ordenadas
        merge(catalogo, left, mid, right);
    }
}

void adicionarConstelacao(constelacao *&catalogo,int &tamanho, int &capacidade){
    if (tamanho >= capacidade) {
        aumentarCatalogo(catalogo, capacidade);
    }
    bool entradaValida = false;

    std::cout << "Digite o nome da constelacao: ";
    std::cin.ignore();
    getline(std::cin, catalogo[tamanho].nome);

    std::cout << "Digite o numero de estrelas principais: ";

    //decidi usar esse do-while complexo primeiro pq é dificil estipular um input válido pra um numero
    do{
        std::cin >> catalogo[tamanho].principaisEstrelas;
        if (std::cin.fail()){// detectou como NaN, limpa a resposta e o erro e pede dnv
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. \nPor favor, insira o NUMERO de estrelas principais: ";
        }
        else{
            entradaValida = true;
        }
    }while(!entradaValida);
    
    entradaValida = false;
    std::cout << "Digite o hemisferio (Norte/Sul/Ambos): ";
    std::string input;
    
    

    // decidi usar nesse do-wilhe só if-else pq só existem 3 opções validas possiveis.
    do{
        std::cin >> input;
        if(input == "Norte" or input == "norte"){
            catalogo[tamanho].hemisferio = 'N';
            entradaValida = true;
        }
        else if(input == "Sul" or input == "sul"){
            catalogo[tamanho].hemisferio = 'S';
            entradaValida = true;
        }
        else if(input == "Ambos" or input == "ambos"){
            catalogo[tamanho].hemisferio = 'A';
            entradaValida = true;
        }
        else{
            std::cout << "Entrada invalida. Digite novamente."; nl
            entradaValida = false;
        }
    }while(!entradaValida);

    std::cin.ignore();
    std::cout << "Digite uma descricao curta: ";
    getline(std::cin, catalogo[tamanho].descricao);

    tamanho++;
    mergeSort(catalogo, 0, tamanho - 1);
    std::cout << "Constelação adicionada com sucesso!\n";
}

void listarConstelacoes(constelacao *catalogo, int tamanho){
    if (tamanho == 0) {
        std::cout << "\nNenhuma constelacao no catalogo.";nl nl
        return;
    }
    std::cout << "\nCatalogo de Constelacoes:\n";
    for (int i = 0; i < tamanho; i++) {
        std::cout << i + 1 << ". " << catalogo[i].nome << " - ";
        if(catalogo[i].hemisferio == 'N') std::cout << "Hemisferio norte";
        else if(catalogo[i].hemisferio == 'S') std::cout << "Hemisferio sul";
        else std::cout << "Ambos os hemisferios";
        std::cout << " (" << catalogo[i].principaisEstrelas << " estrelas)\n";
        std::cout << "   Descricao: ";
        int contadorLetras = 0; // Para contar as letras
        const int limitePorLinha = 40; // Número de letras antes de pular linha

        for (char c : catalogo[i].descricao) {
            if (std::isalpha(c)) {
            contadorLetras++;
            }
            std::cout << c;

            if (contadorLetras >= limitePorLinha) {
                contadorLetras = 0;
                std::cout << "-";
                nl
                std::cout << "   ";
            }
        }
        nl nl

    }
}

void removerConstelacoes(constelacao *&catalogo, int &tamanho){
    if (tamanho == 0) {
        std::cout << "\nNenhuma constelacao para remover.";nl nl
        return;
    }

    std::string nome;
    std::cout << "Digite o nome da constelacao a ser removida: ";
    std::cin.ignore();
    getline(std::cin, nome);

    int index = buscaBinaria(catalogo, tamanho, nome);
    if (index == -1) {
        std::cout << "Constelacao nao encontrada.";nl
        return;
    }

    for (int i = index; i < tamanho - 1; i++) {
        catalogo[i] = catalogo[i + 1];
    }
    tamanho--;
    std::cout << "\nConstelacao removida com sucesso!";nl nl
}

int main(){
    constelacao *catalogo = nullptr;
    int tamanho = 0; 
    int capacidade = 2;

    catalogo = new constelacao[capacidade];

    std::cout << "Bem vido ao Sistema de Gerenciamento de Constelacoes.";nl
    int input;
    do{
        std::cout << "1. Adicionar Constelacao\n2. Listar Constelacoes \n3. Buscar constelacao por nome";nl
        std::cout << "4. Remover constelacao\n5. Sair";nl
        std::cout << "Entrada: ";
        std::cin >> input;
        
        switch(input){
        case 1:
            adicionarConstelacao(catalogo, tamanho, capacidade);
            break;
        
        case 2:
            listarConstelacoes(catalogo, tamanho);
            break;
        
        case 3:
        {   //por algum motivo o c++ não deixa eu declarar uma variavel num switch, então criei um escopo sem nada ¯\(ツ)/¯
            std::string nomeBusca;
                std::cout << "Digite o nome da constelacao para buscar: ";
                std::cin.ignore();
                getline(std::cin, nomeBusca);

                int index = buscaBinaria(catalogo, tamanho, nomeBusca);
                if (index != -1) {
                    std::cout << "\n---- Constelacao encontrada! ----";nl 
                    std::cout << "Nome: " << catalogo[index].nome; nl
                    std::cout << "Numero de estrelas principais: " << catalogo[index].principaisEstrelas; nl
                    if(catalogo[index].hemisferio == 'N'){
                        std::cout << "Hemisferio: Norte";nl
                    }
                    else if(catalogo[index].hemisferio == 'S'){
                        std::cout << "Hemisferio: Sul";nl
                    }
                    else{
                        std::cout << "Hemisferio: Ambos";nl
                    }
                    std::cout << "Descrição: " << catalogo[index].descricao; nl nl
                }
                else{
                    std::cout << "\nConstelacao \"" << nomeBusca << "\" nao encontrada.";nl nl
                }
                break;
        }
        case 4:
            removerConstelacoes(catalogo, tamanho);
            break;
        
        case 5:
            std::cout << "Obrigado por usar o catalogo de constelacoes. Saindo...";nl
            exit(0);
            break;

        default:
            std::cout << "entrada invalida!";
            break;
        }

    }while(input != 5);

    return 0;
}