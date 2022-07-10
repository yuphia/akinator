#ifndef AKINATOR_CPP
#define AKINATOR_CPP 1

#include "akinator.hpp"

Errors gameStartup (BinaryTree *tree)
{
    checkNullptr (tree);
    Errors tempErr = NO_ERROR;

    char* rootData = nullptr;
    
    tempErr = readData (&rootData, stdin);
    passErr();

    tempErr = treeCtor (tree, rootData);
    passErr();

    return tempErr;
}

Errors gameFinish (BinaryTree *tree)
{
    checkNullptr (tree);
    Errors tempErr = NO_ERROR;

    drawRoot (tree);

    tempErr = treeDtor (tree);
    passErr();

    return tempErr;
}

Errors gameShell()
{
    Errors tempErr = NO_ERROR;

    BinaryTree *tree = 
        (BinaryTree*)calloc (1, sizeof(BinaryTree));
    if (tree == nullptr)
        return ALLOC_ERROR;

    tempErr = gameStartup (tree);
    passErr();

    tempErr = readTree_ (tree);
    passErr();

    drawRoot(tree);

    while (true)
    {
        printf ("Choose your gameMod:\n\
                1 - game\n\
                5 - exit\n");
        
        GameMod gamemod = FINISH;

        if (scanf ("%d", (int*)&gamemod) == EOF)
        {
            if (errno == EAGAIN)
                return STREAM_BLOCKED;
            if (errno == EBADF)
                return STREAM_INVALID;
            if (errno == EINTR)
                return SIGNAL_INTERRUPT;
            if (errno == ENOMEM)
                return MEM_ERROR;
            if (errno == ERANGE)
                return INT_CAST_ERROR;
        }
        while(getchar() != '\n');
           
        if (gamemod == FINISH)
            break;

        gamePlay (tree, tree->root);
    }

    tempErr = writeTree_ (tree);
    passErr();

    tempErr = gameFinish (tree);
    passErr();

    return NO_ERROR;
}

Errors gamePlay (BinaryTree *tree, BinaryTreeNode *node)
{
    Errors tempErr = NO_ERROR;

    if (node->lChild == nullptr && node->rChild == nullptr)
    {
        printf ("Is your object %s?", node->data);

        char yn = askYN();
        
        if (yn == 'y')
        {
            onSuccessFind();
            return tempErr;
        }
        else if (yn == 'n')
        {
            onFailFind (tree, node);
            return tempErr;
        }
        else
        {
            printf ("Wrong input, please print y/n\n");
            return tempErr;
        }
    }
    else 
    {
        printf ("Does your object have a feature of %s?", node->data);
        char yn = askYN();

        if (yn == 'y')
            tempErr = gamePlay (tree, node->lChild);
        else if (yn == 'n')
            tempErr = gamePlay (tree, node->rChild);
        else
            printf ("Wrong input, please print y/n\n");

        passErr();

        return tempErr;
    }   
}

Errors onSuccessFind()
{
    printf ("Knew it.\n");
    return NO_ERROR;
}

Errors onFailFind (BinaryTree *tree, BinaryTreeNode *node)
{
    Errors tempErr = NO_ERROR;
    printf ("Govno\n");
    printf ("What were you thinking of? Tell me: \n"); 

    char* newChallenger = nullptr;
    tempErr = readData (&newChallenger, stdin);
    passErr();

    tempErr = treeAppendElement (tree, node, newChallenger, LEFT);
    passErr();

    printf ("What %s is and %s is not? \nIt is: ", newChallenger, node->data);
    
    char* newFeature = nullptr;
    tempErr = readData (&newFeature, stdin);
    passErr();

    printf ("here newFeature = %s\n", newFeature);
    tempErr = treeAppendElement (tree, node, node->data, RIGHT);
    passErr();

    node->data = newFeature; 

    printf ("Thanks for the contribution.\n");

    return tempErr;
}

char askYN()
{
    char yn = 0;

    int checkFflush = fflush (stdin);
    if (checkFflush == EOF)
    {
        if(errno == EBADF)
            return FFLUSH_ERROR;
        
        return UNREC_ERROR;
    }

    if (scanf ("%c", &yn) == EOF)
    {
        if (errno == EAGAIN)
            return STREAM_BLOCKED;
        if (errno == EBADF)
            return STREAM_INVALID;
        if (errno == EINTR)
            return SIGNAL_INTERRUPT;
        if (errno == ENOMEM)
            return MEM_ERROR;
        if (errno == ERANGE)
            return INT_CAST_ERROR;
    }
    
    while(getchar() != '\n');

    return yn;
}

Errors readData (char** data, FILE *stream)
{
    checkNullptr (data);
    checkNullptr (*data);
    checkFile (stream);

    int checkFflush = 0;
    int checkGetline = 0;

    size_t bufSize = 0;
    checkFflush = fflush (stream);
    if (checkFflush == EOF)
    {
        if(errno == EBADF)
            return FFLUSH_ERROR;
        
        return UNREC_ERROR;
    }

    checkGetline = (int)getline (data, &bufSize, stream);
    if (checkGetline == -1)
    {
        if (errno == EINVAL)
            return BAD_ARG;
        if (errno == ENOMEM)    
            return GETLINE_REALLOC_ERROR;
    }

    char* pointer = strchr (*data, '\0');
    if (pointer == nullptr)
        return STRCHR_ERROR;

    (*data) [(int)(pointer - (*data)) - 1] = '\0';

    return NO_ERROR;
}

Errors writeTree_ (BinaryTree *tree)
{
    Errors tempErr = NO_ERROR;

    checkNullptr (tree);
    FILE* db = fopen ("exec/akinator.txt", "w");
    checkFile (db);

    if (db == nullptr)
        return FILE_OPEN_ERROR; 

    tempErr = writeTree (tree, tree->root, db);
    passErr();

    fclose (db);   
    if (errno == EBADF)
        return FILE_DEAD;

    return tempErr;
}

Errors writeTree (BinaryTree *tree, BinaryTreeNode *node, FILE* db)
{
    Errors tempErr = NO_ERROR;
    int printfCheck = 0;

    checkNullptr (tree);
    checkNullptr (node);
    checkFile (db);
    checkNullptr (node->data);
   
    printTabs (db, node->depth);
    printfCheck = fprintf (db, "{\n");
    if (printfCheck < 0)
        return FPRINTF_ERROR;
    
    printTabs (db, node->depth);
    fprintf (db, "%s\n", node->data);
    if (printfCheck < 0)
        return FPRINTF_ERROR;
    

    if (node->lChild != nullptr)
    {
        tempErr = writeTree (tree, node->lChild, db);
        passErr ();
    }
    if (node->rChild != nullptr)
    {
        tempErr = writeTree (tree, node->rChild, db);
        passErr();
    }

    printTabs (db, node->depth);
    printfCheck = fprintf (db, "}\n");
    if (printfCheck < 0)
        return FPRINTF_ERROR;

    return tempErr;
}

Errors readTree_ (BinaryTree* tree)
{
    Errors tempErr = NO_ERROR;
    checkNullptr (tree);

    FILE *db = fopen ("exec/akinator.txt", "r");
    checkFile (db);

    char *dbBuff = nullptr;
    tempErr = readFileToBuffer (db, &dbBuff);
    passErr();

    tempErr = readTree (tree, &(tree->root), &dbBuff, nullptr);
    passErr();

    fclose (db);
    if (errno == EBADF)
        return FILE_DEAD;

    return tempErr;
}

Errors readTree (BinaryTree *tree, BinaryTreeNode **node,
               char **dbBuff, BinaryTreeNode *parent)
{
    Errors tempErr = NO_ERROR;
    checkNullptr (tree);
    checkNullptr (node);
    checkNullptr (dbBuff);
    checkNullptr (*dbBuff);
    checkNullptr (parent);

    tempErr = skipTabsSpaces (dbBuff);
    passErr();

    if (**dbBuff == '{')
    {
        (*dbBuff)++;

        tempErr = skipTabsSpaces (dbBuff);
        passErr();

        data_t* newLinePointer = strchr (*dbBuff, '\n');
        if (newLinePointer == nullptr)
            return STRCHR_ERROR;

        data_t* dataBuff = nullptr;
        size_t amount = size_t(newLinePointer - *dbBuff);
       
        tempErr = allocData (&dataBuff, amount);
        passErr();

        tempErr = copyData (dataBuff, *dbBuff, amount);
        passErr();

        tempErr = allocNode (node, dataBuff);
        passErr();

        if (parent != nullptr)
        {
            (*node)->parent = parent;
            (*node)->depth = parent->depth + 1;
        }

        *dbBuff += amount;

        tempErr = readTree (tree, &(*node)->lChild, dbBuff, *node);
        passErr();

        tempErr = skipTabsSpaces (dbBuff);
        passErr();

        tempErr = readTree (tree, &(*node)->rChild, dbBuff, *node);
        passErr();

        tempErr = skipTabsSpaces (dbBuff);
        passErr();

        if (**dbBuff == '}') 
        {
            (*dbBuff)++;
            return tempErr;  
        }
    }

    return tempErr;
}

Errors printTabs (FILE *db, size_t amount)
{
    checkNullptr (db);

    for (size_t i = 0; i < amount; i++)
    {
        fprintf (db, "  ");
    }

    return NO_ERROR;
}

Errors skipTabsSpaces (char **buffer)
{
    checkNullptr (buffer);
    checkNullptr (*buffer);

    const char accept[] = {"    \n"};
    *buffer = *buffer + strspn (*buffer, accept);

    return NO_ERROR;
}

Errors readFileToBuffer (FILE *file, char **buffer)
{
    checkNullptr (buffer);
    checkNullptr (*buffer);
    checkFile (file);

    fseek (file, 0, SEEK_END); 
    if (errno == ESPIPE)
        return DESCR_UNSEEKABLE;

    size_t size = (size_t)ftell (file);
    if (errno == ESPIPE)
        return DESCR_UNSEEKABLE;

    fseek (file, 0, SEEK_SET);
    if (errno == ESPIPE)
        return DESCR_UNSEEKABLE;

    *buffer = (char*) calloc (size, sizeof (size_t));
    if (*buffer == nullptr)
        return ALLOC_ERROR;

    fread (*buffer, sizeof (char), size, file);

    return NO_ERROR;
}

Errors copyData (data_t* buff, data_t* readBuff, size_t amount)
{
    checkNullptr (buff);
    checkNullptr (readBuff);

    for (size_t i = 0; i < amount; i++)
        buff [i] = readBuff [i];

    return NO_ERROR;
}

#endif