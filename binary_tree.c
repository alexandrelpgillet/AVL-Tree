#include<stdio.h>
#include <stdlib.h>

typedef struct node {

    struct node *left;
    struct node *right;
    int value;

}node;


typedef struct {

    int size;
    int high;
    node *root;

}binaryTree;


node* createNode(int item){

    node *aux = (node *) malloc (sizeof(node));

    if(!aux) exit(-1);
    
    aux->right = NULL;
    aux->left = NULL;
    aux->value = item;
        
    return aux;

}


node* findPositionInsert(node *root , int item){
    
    node *pos=root;

   

    
    if(root){
        
        if(item>=root->value){

         
            if(root->right) pos = findPositionInsert(root->right,item);
            else pos = root;   
        }
        
        if(item<root->value && root->left){ 
          
            if(root->left) pos = findPositionInsert(root->left, item);
            else pos = root;

        }
        
    }

    return pos;
    
    
}


node* findPositionRemove(node *root , int item){
    
    node *pos = root;
    
    if(root){

        if(item == root->left->value) return pos;
        
        if(item ==root->right->value) return pos;
        
        if(item == root->value) return pos;

        if(item<root->value) pos = findPositionRemove(root->left, item);
        
        if(item>root->value) pos = findPositionRemove(root->right, item);
    }
    else if(!root){

        pos = NULL;
    }

    return pos;
}






void createBinaryTree(binaryTree *B){

    B->size= 0;
    B->high =0;
    B->root = NULL;

}


void insertBinaryTree(binaryTree *B, int item){

    node *newNode = createNode(item);
    
    if(!newNode) exit(-1);
     
    B->size++;
    
    if(!B->root){
        
    
        B->root = newNode;

    }
    else{

        node *pos  = findPositionInsert(B->root, item);
        
        if(item>=pos->value){

            pos->right = newNode;

        }
        else if(item<pos->value){

            pos->left = newNode;

        }
    

    }
}


node* maxSheet(node *root){
    
    node *maxNode = root;
    
    if(root)
    {
        if(root->right){
            maxNode = maxSheet(root->right);
        }
    }

    return maxNode;
    

} 

node* minSheet(node *root){

    node *minNode = root;

    if(root){
        if(root->left){
            minNode = minSheet(root->left);
        }
    }

    return minNode;
}


int highNode(node *root){

    int heighLeft, heighRight;

    heighLeft = 0 ;
    heighRight = 0;


    
    if(root)
    {
        if(root->right){
            
            heighRight = highNode(root->right);
            heighRight++;
        }    
         
        if(root->left){
            
            heighLeft = highNode(root->left);
            heighLeft++; 
        }
    

    }


    if(heighLeft>heighRight){
        
        return heighLeft;
    }
    else if(heighRight>heighLeft)
    {

        return heighRight;

    }
    else{

        return heighLeft;
    }
}


void removeItemBinaryTree(binaryTree *B , int item){


    node *auxNode = findPositionRemove(B->root,item);
    node *removeNode;
    int dir =0;

    if(auxNode){

        if(auxNode->value == item)
        {

            //Nó a ser removido é o nó raiz

            node  *newRoot = auxNode->right;

            node *rightLeft = minSheet(newRoot);

            rightLeft->left = auxNode->left;

            free(auxNode);

            B->root = newRoot;

            
        }
        else
        {
            if(auxNode->left->value == item){
                
                removeNode = auxNode->left;
                
                

            }
            else if(auxNode->right->value == item){

                removeNode = auxNode->right;
                dir= 1;   
             
            }


            if(removeNode->left && removeNode->right){

                //Nó com dois filhos

                node *leftNode  = removeNode->left;
                
                node *rightLeftNode = minSheet(removeNode->right);

                rightLeftNode->left = leftNode;

                if(dir)
                {
                    auxNode->right = removeNode->right;

                }else if(!dir){

                    auxNode->left = removeNode ->right;

                }

                free(removeNode);
            }
            else if(removeNode->left){
                //Nó com 1 filho a esquerda

                if(dir){

                    auxNode->right = removeNode->left;
                         

                }
                else if(!dir){
                    
                    auxNode->left = removeNode->left;
                }

                free(removeNode);
            }
            else if(removeNode->right){
                //Nó com 1 filho a direita

                if(dir){
                    
                    auxNode->right = removeNode->right;
                    free(removeNode);   
                }
                else if(!dir){

                    auxNode->left = removeNode->right;
                    free(removeNode);
                }
            }
            else{

                //No com nenhum filho

                free(removeNode);

                if(dir)
                {

                    auxNode->right = NULL;


                }
                else if(!dir){

                    auxNode->left = NULL;

                }
            }
        }


    
    
    }


}


int clearNode(node *root){

    if(root)
    {
        if(root->left) clearNode(root->left);
        if(root->right) clearNode(root->right);

        free(root);
    }

}


int clearBinaryTree(binaryTree *B){

    clearNode(B->root);
}



void printNode(node *root){

    if(root){

        printNode(root->left);
        printf("%d\n", root->value);
        printNode(root->right);
    }
}

void printBinaryTree(binaryTree *B){

     if(B->root){
        printNode(B->root);
     }

}





int main(){

    int V[]={6,5,5,2,7,8,10,9};

    int N = (int) sizeof(V)/4;

    binaryTree B;

    createBinaryTree(&B);

    for(int i=0 ; i<N ; i++){

        insertBinaryTree(&B, V[i]);
    }

    printBinaryTree(&B);

    
    node *max = maxSheet(B.root); 
    node *min = minSheet(B.root);


    printf("\n\nMax = %d |Min %d \n ", max->value, min->value);

    //removeItemBinaryTree(&B,6);
    //removeItemBinaryTree(&B, 5);
    //removeItemBinaryTree(&B,2);
    //removeItemBinaryTree(&B,5);
    //removeItemBinaryTree(&B,7);

    //printBinaryTree(&B);

    printf("H = %d \n", highNode(B.root));
    
    clearBinaryTree(&B);
}



//Necessário fazer o máximo e o mínimo de uma Arvore