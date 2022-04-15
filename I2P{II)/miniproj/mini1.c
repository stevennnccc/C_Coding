#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// for lex
#define MAXLEN 256

typedef struct _Register
{
    int using;
    int val;
    int defined;
} Register;

Register r[8];

// Token types
typedef enum
{
    UNKNOWN,
    END,
    ENDFILE,
    INT,
    ID,
    ADDSUB,
    MULDIV,
    ASSIGN,
    LPAREN,
    RPAREN,
    INCDEC,
    AND,
    OR,
    XOR
} TokenSet; // [Done]: Added operations

TokenSet getToken(void);
TokenSet curToken = UNKNOWN;
char lexeme[MAXLEN];

// Test if a token matches the current token
int match(TokenSet token);
// Get the next token
void advance(void);
// Get the lexeme of the current token
char *getLexeme(void);

// for parser
#define TBLSIZE 64

// Structure of the symbol table
typedef struct
{
    int val;
    int defined;
    char name[MAXLEN];
} Symbol;

// Structure of a tree node
typedef struct _Node
{
    TokenSet data;
    int val;
    char lexeme[MAXLEN];
    struct _Node *left;
    struct _Node *right;
} BTNode;

int sbcount = 0;
Symbol table[TBLSIZE];

// Initialize the symbol table with builtin variables
void initTable(void);
// Get the value of a variable
int getval(const char *str);
// Make a new node according to token type and lexeme
BTNode *makeNode(TokenSet tok, const char *lexe);
// Free the syntax tree
void freeTree(BTNode *root);
BTNode *factor(void);
BTNode *unary_expr(void);
BTNode *muldiv_expr_tail(BTNode *left);
BTNode *muldiv_expr(void);
BTNode *addsub_expr_tail(BTNode *left);
BTNode *addsub_expr(void);
BTNode *and_expr_tail(BTNode *left);
BTNode *and_expr(void);
BTNode *xor_expr_tail(BTNode *left);
BTNode *xor_expr(void);
BTNode *or_expr_tail(BTNode *left);
BTNode *or_expr(void);
BTNode *assign_expr(void);
void statement(void);
void exit_1(void);
int get_val_place(char *str);
int find_enable_reg(void);
int find_id(BTNode *root);

// for codeGen
// Evaluate the syntax tree
int evaluateTree(BTNode *root);
// Print the syntax tree in prefix
void printPrefix(BTNode *root);

/*============================================================================================
lex implementation
============================================================================================*/

TokenSet getToken(void)
{
    int i = 0;
    char c = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t')
        ;

    if (isdigit(c))
    {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN)
        {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    }
    else if (c == '+' || c == '-') // [Done]: INCDEC
    {
        lexeme[0] = c;
        c = fgetc(stdin);
        if (c == '+' || c == '-')
        {
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        }
        else
        {
            ungetc(c, stdin);
            lexeme[1] = '\0';
            return ADDSUB;
        }
    }
    else if (c == '&') // [Done]: AND
    {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return AND;
    }
    else if (c == '^') // [Done]: XOR
    {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return XOR;
    }
    else if (c == '|') // [Done]: OR
    {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return OR;
    }
    else if (c == '*' || c == '/')
    {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    }
    else if (c == '\n')
    {
        lexeme[0] = '\0';
        return END;
    }
    else if (c == '=')
    {
        strcpy(lexeme, "=");
        return ASSIGN;
    }
    else if (c == '(')
    {
        strcpy(lexeme, "(");
        return LPAREN;
    }
    else if (c == ')')
    {
        strcpy(lexeme, ")");
        return RPAREN;
    }
    else if (isalpha(c) || c == '_')
    {
        lexeme[0] = c;
        char str[MAXLEN] = {'\0'};
        int count = 1;
        fscanf(stdin, "%[a-zA-Z0-9_]", str);
        while (str[count - 1] != '\0')
        {
            lexeme[count] = str[count - 1];
            count++;
        }
        lexeme[count] = '\0';
        return ID;
    }
    else if (c == EOF)
    {
        return ENDFILE;
    }
    else
    {
        return UNKNOWN;
    }
}

void advance(void)
{
    curToken = getToken();
}

int match(TokenSet token)
{
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

char *getLexeme(void)
{
    return lexeme;
}

/*============================================================================================
parser implementation
============================================================================================*/

void initTable(void)
{
    strcpy(table[0].name, "x");
    table[0].val = 0;
    table[0].defined = 1;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    table[1].defined = 1;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    table[2].defined = 1;
    sbcount = 3;
}

int getval(const char *str)
{
    int i = 0;

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;

    if (sbcount >= TBLSIZE)
        exit_1();

    strcpy(table[sbcount].name, str);
    table[sbcount].val = 0;
    sbcount++;
    return 0;
}

int get_val_place(char *str)
{
    for (int i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return i;
    return -1;
}

BTNode *makeNode(TokenSet tok, const char *lexe)
{
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = getval(lexe);
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

//        NEW := INT | ID |
//            INCDEC ID |
//            LPAREN assign_expr RPAREN

BTNode *factor(void) // [Done]
{
    BTNode *retp = NULL;

    if (match(INT))
    {
        retp = makeNode(INT, getLexeme());
        advance();
    }
    else if (match(ID))
    {
        retp = makeNode(ID, getLexeme());
        advance();
    }
    else if (match(INCDEC))
    {
        retp = makeNode(INCDEC, getLexeme());
        advance();
        retp->left = NULL;
        if (match(ID))
        {
            retp->right = makeNode(ID, getLexeme());
            advance();
        }
        else
        {
            exit_1();
        }
    }
    else if (match(LPAREN))
    {
        advance();
        retp = assign_expr();
        if (match(RPAREN))
            advance();
        else
            exit_1();
    }
    else
        exit_1();
    return retp;
}

BTNode *assign_expr(void) // Grammar := ID ASSIGN assign_expr | or_expr
{
    BTNode *retp = NULL, *left = NULL;
    left = or_expr();

    if (match(ASSIGN))
    {
        retp = makeNode(ASSIGN, getLexeme());
        retp->left = left;
        advance();
        retp->right = assign_expr();
        if (retp->left != NULL)
        {
            int val_place = get_val_place(retp->left->lexeme);
            table[val_place].defined = 1;
        }
    }
    else
    {
        retp = left;
    }
    return retp;
}

BTNode *or_expr(void) // Grammar := xor_expr or_expr_tail
{
    BTNode *retp = xor_expr();
    return or_expr_tail(retp);
}

BTNode *or_expr_tail(BTNode *left) // Grammar := OR xor_expr or_expr_tail | NiL
{
    BTNode *retp = NULL;

    if (match(OR))
    {
        retp = makeNode(OR, getLexeme());
        advance();
        retp->left = left;
        retp->right = xor_expr();
        return or_expr_tail(retp);
    }
    else // NiL
        return left;
}

BTNode *xor_expr(void) // Grammar := and_expr xor_expr_tail
{
    BTNode *retp = and_expr();
    return xor_expr_tail(retp);
}

BTNode *xor_expr_tail(BTNode *left) // Grammar := XOR and_expr xor_expr_tail | NiL
{
    BTNode *retp = NULL;

    if (match(XOR))
    {
        retp = makeNode(XOR, getLexeme());
        advance();
        retp->left = left;
        retp->right = and_expr();
        return xor_expr_tail(retp);
    }
    else // NiL
        return left;
}

BTNode *and_expr(void) // Grammar := addsub_expr and_expr_tail
{
    BTNode *retp = addsub_expr();
    return and_expr_tail(retp);
}

BTNode *and_expr_tail(BTNode *left) // := AND addsub_expr and_expr_tail | NiL
{
    BTNode *retp = NULL;

    if (match(AND))
    {
        retp = makeNode(AND, getLexeme());
        advance();
        retp->left = left;
        retp->right = addsub_expr();
        return and_expr_tail(retp);
    }
    else // NiL
        return left;
}

BTNode *addsub_expr(void) // := muldiv_expr addsub_expr_tail
{
    BTNode *retp = muldiv_expr();
    return addsub_expr_tail(retp);
}

BTNode *addsub_expr_tail(BTNode *left) // := ADDSUB muldiv_expr addsub_expr_tail | NiL
{
    BTNode *retp = NULL;

    if (match(ADDSUB))
    {
        retp = makeNode(ADDSUB, getLexeme());
        advance();
        retp->left = left;
        retp->right = muldiv_expr();
        return addsub_expr_tail(retp);
    }
    else // NiL
        return left;
}

BTNode *muldiv_expr(void) // Grammar := unary_expr muldiv_expr_tail
{
    BTNode *retp = unary_expr();
    return muldiv_expr_tail(retp);
}

BTNode *muldiv_expr_tail(BTNode *left) // Grammar := MULDIV unary_expr muldiv_expr_tail | NiL
{
    BTNode *retp = NULL;

    if (match(MULDIV))
    {
        retp = makeNode(MULDIV, getLexeme());
        advance();
        retp->left = left;
        retp->right = unary_expr();
        return muldiv_expr_tail(retp);
    }
    else // NiL
        return left;
}

BTNode *unary_expr(void) // Grammar := ADDSUB unary_expr | factor
{
    BTNode *retp = NULL;

    if (match(ADDSUB))
    {
        retp = makeNode(ADDSUB, getLexeme());
        advance();
        retp->left = makeNode(INT, "0");
        retp->right = unary_expr();
    }
    else
        retp = factor();
    return retp;
}

// statement := ENDFILE | END | assign_expr END
void statement(void)
{
    BTNode *retp = NULL;

    if (match(ENDFILE))
    {
        printf("MOV r0 [0]\n");
        printf("MOV r1 [4]\n");
        printf("MOV r2 [8]\n");
        printf("EXIT 0\n");
        exit(0);
    }
    else if (match(END))
    {
        // printf(">> ");
        advance();
    }
    else
    {
        retp = assign_expr();

        if (match(END))
        {
            evaluateTree(retp);
            // printf("Prefix traversal: ");
            // printPrefix(retp);
            // printf("\n");
            freeTree(retp);
            for (int i = 0; i < 8; i++)
                r[i].using = 0,
                r[i].val = 0;
            // printf(">> ");
            advance();
        }
        else
        {
            exit_1();
        }
    }
}

void exit_1()
{
    printf("EXIT 1\n");
    exit(0);
}

/*============================================================================================
codeGen implementation
============================================================================================*/

int evaluateTree(BTNode *root)
{
    int lreg = 0, rreg = 0, val_place = -1, avail_reg = -1, tmp = 0;

    if (root != NULL)
    {
        switch (root->data)
        {
        case ID:
            val_place = get_val_place(root->lexeme);
            avail_reg = find_enable_reg();
            printf("MOV r%d [%d]\n", avail_reg, val_place * 4);
            r[avail_reg].using = 1;
            r[avail_reg].val = table[val_place].val;
            r[avail_reg].defined = table[val_place].defined;
            break;
        case INT:
            avail_reg = find_enable_reg();
            r[avail_reg].using = 1;
            r[avail_reg].val = atoi(root->lexeme);
            r[avail_reg].defined = 1;
            printf("MOV r%d %d\n", avail_reg, atoi(root->lexeme));
            break;
        case ASSIGN:
            if (root->left->data == ID)
            {
                val_place = get_val_place(root->left->lexeme);
                avail_reg = evaluateTree(root->right);
                if (r[avail_reg].defined == 0)
                    exit_1();
                printf("MOV [%d] r%d\n", val_place * 4, avail_reg);
                r[avail_reg].using = 0;
                table[val_place].val = r[avail_reg].val;
            }
            else
                exit_1();
            break;
        case ADDSUB:
        case MULDIV:
            if (strcmp(root->lexeme, "+") == 0)
            {
                lreg = evaluateTree(root->left);
                rreg = evaluateTree(root->right);
                printf("ADD r%d r%d\n", lreg, rreg);
                avail_reg = lreg;
                r[rreg].using = 0;
                r[lreg].val = r[lreg].val + r[rreg].val;
                r[lreg].defined = r[lreg].defined & r[rreg].defined;
            }
            else if (strcmp(root->lexeme, "-") == 0)
            {
                lreg = evaluateTree(root->left);
                rreg = evaluateTree(root->right);
                printf("SUB r%d r%d\n", lreg, rreg);
                avail_reg = lreg;
                r[rreg].using = 0;
                r[lreg].val = r[lreg].val - r[rreg].val;
                r[lreg].defined = r[lreg].defined & r[rreg].defined;
            }
            else if (strcmp(root->lexeme, "*") == 0)
            {
                lreg = evaluateTree(root->left);
                rreg = evaluateTree(root->right);
                printf("MUL r%d r%d\n", lreg, rreg);
                avail_reg = lreg;
                r[rreg].using = 0;
                r[lreg].val = r[lreg].val * r[rreg].val;
                r[lreg].defined = r[lreg].defined & r[rreg].defined;
            }
            else if (strcmp(root->lexeme, "/") == 0)
            {
                lreg = evaluateTree(root->left);
                rreg = evaluateTree(root->right);

                // Error -> divide by 0
                if (r[rreg].val == 0 && !find_id(root->right))
                    exit_1();
                else
                {
                    printf("DIV r%d r%d\n", lreg, rreg);
                    avail_reg = lreg;
                    r[rreg].using = 0;
                    if (r[rreg].val != 0)
                        r[lreg].val = r[lreg].val / r[rreg].val;
                    else
                        r[lreg].val = 0;
                    r[lreg].defined = r[lreg].defined & r[rreg].defined;
                }
            }
            break;
        case AND:
            lreg = evaluateTree(root->left);
            rreg = evaluateTree(root->right);
            printf("AND r%d r%d\n", lreg, rreg);
            avail_reg = lreg;
            r[rreg].using = 0;
            r[lreg].val = r[lreg].val & r[rreg].val;
            r[lreg].defined = r[lreg].defined & r[rreg].defined;
            break;
        case OR:
            lreg = evaluateTree(root->left);
            rreg = evaluateTree(root->right);
            printf("OR r%d r%d\n", lreg, rreg);
            avail_reg = lreg;
            r[rreg].using = 0;
            r[lreg].val = r[lreg].val | r[rreg].val;
            r[lreg].defined = r[lreg].defined & r[rreg].defined;
            break;
        case XOR:
            lreg = evaluateTree(root->left);
            rreg = evaluateTree(root->right);
            printf("XOR r%d r%d\n", lreg, rreg);
            avail_reg = lreg;
            r[rreg].using = 0;
            r[lreg].val = r[lreg].val ^ r[rreg].val;
            r[lreg].defined = r[lreg].defined & r[rreg].defined;
            break;
        case INCDEC:
            val_place = get_val_place(root->right->lexeme);
            avail_reg = find_enable_reg();

            if (root->right->data != ID)
                exit_1();

            printf("MOV r%d [%d]\n", avail_reg, val_place * 4);
            r[avail_reg].using = 1;
            tmp = find_enable_reg();
            printf("MOV r%d 1\n", tmp);
            if (root->lexeme[0] == '+')
            {
                printf("ADD r%d r%d\n", avail_reg, tmp);
                root->right->val++;
            }
            else if (root->lexeme[0] == '-')
            {
                printf("SUB r%d r%d\n", avail_reg, tmp);
                root->right->val--;
            }
            printf("MOV [%d] r%d\n", val_place * 4, avail_reg);

            r[avail_reg].val = root->right->val;
            r[avail_reg].defined = table[val_place].defined;
            break;
        default:
            break;
        }
    }
    return avail_reg;
}

int find_id(BTNode *root)
{
    if (root == NULL)
        return 0;
    if (root->data == ID)
        return 1;

    return 0 | find_id(root->left) | find_id(root->right);
}

int find_enable_reg()
{
    for (int i = 0; i < 8; i++)
    {
        if (r[i].using == 0)
            return i;
    }
    exit_1();
}

/*============================================================================================
main
============================================================================================*/

// This package is a calculator
// It works like a Python interpretor
// Example:
// >> y = 2
// >> z = 2
// >> x = 3 * y + 4 / (2 * z)
// It will print the answer of every line
// You should turn it into an expression compiler
// And print the assembly code according to the input

// This is the grammar used in this package
// You can modify it according to the spec and the slide
// statement  :=  ENDFILE | END | expr END
// expr    	  :=  term expr_tail
// expr_tail  :=  ADDSUB term expr_tail | NiL
// term 	  :=  factor term_tail
// term_tail  :=  MULDIV factor term_tail| NiL
// factor	  :=  INT | ADDSUB INT |
//		   	      ID  | ADDSUB ID  |
//		   	      ID ASSIGN expr |
//		   	      LPAREN expr RPAREN |
//		   	      ADDSUB LPAREN expr RPAREN

int main()
{
    // freopen("input.txt", "w", stdout);
    initTable();
    // printf(">> ");
    while (1)
    {
        statement();
    }
    return 0;
}
