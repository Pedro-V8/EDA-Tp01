/*
    Objetivo: Abrir arquivo com um texto
    e gerar vetor de vocabulario e cinco arquivos
    e cinco vetores e calcular TF-IDF

    Entrada: Endere�o do arquivo

    Sa�da: TF-IDF
*/
#include "arquivos.h"
#include <conio.h>
#include <ctype.h>
#include <locale.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIMITE 1024
#define TAM_PALAVRA 20
//Estrutura de dados csv:
struct dados_csv{
    char avaliacao[LIMITE];
    char nota[2];
};
//Menu de op��es
void mensagem_menu(){
   	printf("\n_______________________________________________________\n");
   	printf("|             Bem Vindo ao Menu Principal              |\n");
    printf("|                                                      |\n");
    printf("| Escolha uma opcao:                                   |\n");
	printf("| 1 - Ler o arquivo.csv de avaliacoes                  |\n");
    printf("| 2 - Gerar arquivo .txt para o vocabulario            |\n");
    printf("| 3 - Gerar todos os TF-IDFs em um arquivo .csv        |\n");
    printf("| 4 - Mostrar TF-IDF de uma nota especifica em ordem   |\n");
    printf("|     decrescente de valor                             |\n");
    printf("| 5 - Sair                                             |\n");
    printf("|                                                      |\n");
    printf("|______________________________________________________|\n\n");
}
int main(){
    //Declara��es
    char endereco_arquivo[30];//Ponteiro para endereco do arquivo
    char *nome_ptr_1;// Ponteiro para armazenar nome de arquivo digitado
    char *vetor_palavras_csv;//Vetor de palavras sem as pontuacoes
    char *vetor_palavras_csv_s3c;//" " e sem tres caracteres
    char *vetor_ptr_2;
    char *vetor_aux;
    char *parte = NULL;
    char *vetor_avaliacao;
    FILE *arquivo_csv = NULL;//Arquivo principal csv no qual se buscara os simbolos especificos
    FILE *arquivo_nota1 = NULL;//Arquivo com as avalia��es de nota 1
    FILE *arquivo_nota2 = NULL;//" " nota 2
    FILE *arquivo_nota3 = NULL;//" " nota 3
    FILE *arquivo_nota4 = NULL;//" " nota 4
    FILE *arquivo_nota5 = NULL;//" " nota 5
    FILE * vocabulario = NULL;
    int opcao;
    int i, j;
    int pos_i;
    int pos_f;
    int num_palavras;//Numero de palavras totais
    int num_palavras_nr;//Numero de palavras nao repetidas
    int num_dados;
    int caractere;
    int bandeira_1, bandeira_2, bandeira_3, bandeira_4 = 0;
    long int tam_csv;//Tamanho do arquivo_csv
    long int tam_n1;//" " nota1
    long int tam_n2;//" " nota2
    long int tam_n3;//" " nota3
    long int tam_n4;//" " nota4
    long int tam_n5;//" " nota5
    //Instru��es
    i = 0;
    j = 0;
    //Inicializar tamanho do arquivo csv
    tam_csv = 0;
    //Adaptar idioma de localidade
    setlocale(LC_ALL,"");
    //Sinal onde deve retornar
    sinal:
    //Limpar a tela apos retorno
    if(opcao != 0 && opcao != 6){
        getch();
        clearf();
    }
    //Chamar menu de escolhas
    mensagem_menu();
    //Ler escolha do usu�rio
    scanf("%d", &opcao);
    //Limpar a tela
    clearf();
    switch (opcao){
        //Abrir arquivo csv para leitura
        case 1:
            /*          Etapas
                      1) Abrir arquivo csv FEITO
                      2) Separar avaliacao por notas em cinco arquivos ERRO PARCIAL
                      3) Calcular tam_csv FEITO
                      4) Gerar vetor_ptr_csv (avaliacao,nota) FEITO
            */
            printf("Digite o endereco do arquivo a ser aberto (exemplo, digite: hotel.csv):\n");
            //Ler dados
            scanf("%s", endereco_arquivo);//A string do tipo palavra.csv
            arquivo_csv = abrir_arquivo_leitura(endereco_arquivo);
            if(arquivo_csv == NULL){
                //Nao aberto
                printf("Erro! Arquivo %s nao pode ser aberto.\n", endereco_arquivo);
            }else{
                //Sinalizar arquivo aberto
                bandeira_1 = 1;
                //Aberto
                printf("Arquivo %s aberto com sucesso.\n", endereco_arquivo);
                //Armazenar nome do arquivo digitado
                nome_ptr_1 = endereco_arquivo;
                //Gerar os cincos arquivos com texto separado por notas
                separar_por_notas(arquivo_csv);
                //Armazenar tamanho do arquivo
                tam_csv = tamanho_do_arquivo(arquivo_csv);
                //printf("Tamanho arq.: %d", tam_csv);
                //Alocar espa�o com tam_csv
                vetor_palavras_csv = calloc(tam_csv, sizeof(char));
                //Vetor de palavras sem pontua��es
                vetor_palavras_csv = vetor_do_arquivo(arquivo_csv, tam_csv);
                //Fechar arquivo
                fclose(arquivo_csv);
            }
            goto sinal;
            break;
        //Gerar vetor de vocabularios
        case 2:
            /*          Etapas
                      1) Gerar vetor de palavras maiores de tres caracteres FEITO
                      2) Calcular numero de palavras total do arquivo FEITO
                      3) Eliminar palavras repetidas do vetor FALTA
                      4) Gerar vetor vocabulario final FALTA
                      5) Calcular numero de palavras n�o repetidas do arquivo FALTA
            */
            if(bandeira_1 = 1){
                typedef struct{ //essa struct servirá para cada palavra
                    char letras[15];
                }String;
                int i=0, j=0, palavras_ok=0, qtd_char;
                int str_igual=0;
                String palavra;

                //Vetor sem palavras iguais ou menores que 3 caracteres
                vetor_palavras_csv_s3c = vetor_menos_palavras(vetor_palavras_csv, tam_csv); // = str
                //Liberar vetor antigo
                free(vetor_palavras_csv);
                //Calcular quantidade total de palavras do arquivo csv
                num_palavras = numero_de_palavras(vetor_palavras_csv_s3c, tam_csv);
                String palavras[num_palavras];
                //Ver
                printf("Numero total de palavras: %d\n", num_palavras);
                printf("Arquivo vocabulario.txt criado com sucesso !!");
                vocabulario = fopen("vocabulario.txt", "w");
                fputs(vetor_palavras_csv_s3c,vocabulario);
                fclose(vocabulario);

                /*A PARTIR DAQUI � PRECISO GERAR VETOR COM PALAVRAS NAO-REPETIDAS
                CALCULAR num_palavras_nr
                Quando tiver resolvido isso, publicar:
                printf("Vetor vocabulario gerado com sucesso.\n ");*/
                //mostrar_vetor(vetor_palavras_csv, tam_csv);

            }else{
                printf("N�o foi possivel encontrar vetor vocabulario.\n ");
            }
            goto sinal;
            break;
        //Substituir palavras
        case 3:
            /*          Etapas
                      1) Calcular TF-IDF
            */
            /*parte = strtok(vetor_palavras_csv_s3c, "\n");
            do{
                printf("Parte: %s\n", parte);
                //A posicao inicial
                pos_i = 0;
                //A posi��o quando encontra n�mero
                pos_f = 0;
                //Procurar nova linha
                for(i = pos_i; i <= tam_csv; i++){
                    //printf("CSV %c", vetor_palavras_csv[i]);
                    //Se encontrar nova linha
                    if(vetor_palavras_csv_s3c[i] == '\n'){
                        //A posi��o em que '\n' foi achado
                        pos_f = i;
                        //Armazenar palavra encontrada
                        for(pos_i = pos_i; pos_i < pos_f; pos_i++){
                            vetor_aux[j++] = vetor_palavras_csv_s3c[pos_i];
                        }
                        //printf("Vetor: %s\n", vetor_aux);
                        //Se as duas palavras forem iguais
                        if(strcmp(vetor_aux, parte) == 0){
                            //Achou
                            //printf("Palavra %s achada", parte);
                        }
                        //Limpar vetor
                        memset(vetor_aux, 0, 100);
                        //Zerar contador
                        j = 0;
                        //Nova posi��o inicial da procura
                        pos_i = pos_f;
                    }
                }
                //Pegar proxima palavra
                parte = strtok(NULL, "\n");
            }while(parte != NULL);
            free(vetor_palavras_csv_s3c);
            free(parte);

           //vetor: vetor_ptr_1 e arquivo: arquivo_simbolos
           do{
                //Apenas uma vez
                if(bandeira_4 == 0){
                parte = strtok(vetor_ptr_1, "\n");
                }
                //Mudar valor da bandeira
                bandeira_4 = 1;
                //Pegar uma string do arquivo_de_simbolos
                fgets(vetor_palavra, TAM_PALAVRA, arquivo_simbolos);
                //Substituir o \n por \0 no vetor_palavra
                vetor_palavra[strcspn(vetor_palavra, "\n")] = '\0';
                printf("Do arquivo: %s\n", vetor_palavra);
                //Procurar entre vetor do arquivo e vetor palavra
                vetor_ptr_2 = strstr(vetor_ptr_1, vetor_palavra);
                //Ver
                printf("Achou: %s\n", vetor_ptr_2);
                //Armazenar a pr�xima palavra de vetor_ptr_1 no ponteiro parte
                parte = strtok(NULL, "\n");
                //printf("Parte: %s\n", parte);
            }while(!feof(arquivo_simbolos));*/

    /*parte = strtok(vetor_ptr, "\n");
    do{
        j++;
        //Se encontrar uma quebra de linha
        if(vetor_ptr[j] == '\n'){
            //Armazenar
            //for(i = 0; i <= j; i++){
                //vetor_copia[i] = vetor_ptr[i];
            //}
            //Se as palavras forem iguais
            if(strcmp("Jose", parte) == 0){
                printf("Achou");
                break;
            }
        }
        j++;
        parte = strtok(NULL, "\n");
    }while((vetor_ptr[i] != EOF) && (parte != EOF));
}*/

            vocabulario = fopen("vocabulario.txt","r");
            char c;
            while(c = fgetc(vocabulario) != EOF){
                if(c == '\n'){
                    printf("Espaçamento");
                }
                printf("%c",c);
                c = fgetc(vocabulario);
            }
            fclose(vocabulario);

            goto sinal;
            break;
        //Mostrar arquivo principal se j� fora aberto
        case 4:
            /*          Etapas
                      1) Exibir TF-IDF para uma nota
            */
            goto sinal;
            break;
        case 5:
            sair();
            if(bandeira_1 == 1){
                //fclose(arquivo_nota1);
                //fclose(arquivo_nota2);
                //fclose(arquivo_nota3);
                //fclose(arquivo_nota4);
                //fclose(arquivo_nota5);
            }
            break;
        default:
        break;
    }
    return 0;
}
