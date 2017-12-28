#include<cstdio>
#include<string.h>
#include<string>
#include<vector>

using namespace std;

typedef enum type {
    INCRBYTE, DECRBYTE, LFTPTR, RGTPTR, LEFTLOOP, RIGHTLOOP, OUT, IN, ROOT
} Type;

typedef struct token {
    Type type;
    string value;
} Token;

typedef struct astnode {
    Type type;
    string value;
    vector<struct astnode> params;
} ASTNode;

string generateCode(ASTNode node);

ASTNode parse(vector<Token> tokens);
ASTNode walk(vector<Token> tokens, unsigned int &current);

vector<Token> tokenize(char *input);

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Usage: desu [filename]\n");
        return 0;
    }

    if(argv[1] == NULL)
    {
        printf("Ivalid file name\n");
        return 0;
    }

    const char *filename = argv[1];
    FILE *fptr = NULL;
    fptr = fopen(filename, "r+");

    if(fptr == NULL)
    {
        printf("Failed to open file %s\n", argv[1]);
        fclose(fptr);
        return 0;
    }

    fseek(fptr, 0L, SEEK_END);
    size_t fs = ftell(fptr);
    fseek(fptr, 0L, SEEK_SET);
    char input[fs];
    fread(input, fs, 1, fptr);
    fclose(fptr);

    try
    {
        vector<Token> tokens = tokenize(input);
        ASTNode root = parse(tokens);
        string code = generateCode(root);
        
        fptr = NULL;
        fptr = fopen("d.c", "w");
        fwrite(code.c_str(), code.length(), 1, fptr);
        fclose(fptr);

        char *filenameshort = strtok(argv[1], ".");
        char s[] = {'g', 'c', 'c', ' ', 'd', '.', 'c', ' ', '-', 'o', ' ' };

        system(strcat(s, filenameshort));
        system("rm d.c");
    } 
    catch(string msg)
    {
        fprintf(stderr, "%s\n", msg.c_str());
    }
}

string generateCode(ASTNode node)
{
    string ret = "#include<stdio.h>\nchar d[999]; int p;int main(){";
    for(auto itr = node.params.begin(); itr != node.params.end(); ++itr)
    {
        ASTNode current = *itr;
        switch(current.type)
        {
            case DECRBYTE:
                ret += current.value; 
                break;
            case INCRBYTE: 
                ret += current.value;
                break;
            case RGTPTR:
                ret += current.value;
                break;
            case LFTPTR:
                ret += current.value; 
                break;
            case LEFTLOOP: 
                ret += current.value;
                break;
            case RIGHTLOOP: 
                ret += current.value;
                break;
            case OUT: 
                ret += current.value;
                break;
            case IN:
                ret += current.value; 
                break;
            default: throw "ASTNode type invalid " + to_string(current.type) + " : " + current.value;
        }
    }
    ret += "}";
    return ret;
}

ASTNode parse(vector<Token> tokens)
{
    ASTNode root = {ROOT, "Program", vector<ASTNode>()};
    unsigned int current = 0;
    while(current < tokens.size())
    {
        root.params.push_back(walk(tokens, current));
    }
    return root;
}

ASTNode walk(vector<Token> tokens, unsigned int &current)
{
    Token token = tokens[current];
    if(token.type == INCRBYTE)
    {
        current++;
        return {INCRBYTE, "d[p]++;"};
    }
    if(token.type == DECRBYTE)
    {
        current++;
        return {DECRBYTE, "d[p]--;"};
    }
    if(token.type == LFTPTR)
    {
        current++;
        return {LFTPTR, "p--;"};
    }
    if(token.type == RGTPTR)
    {
        current++;
        return {RGTPTR, "p++;"};
    }
    if(token.type == LEFTLOOP)
    {
        current++;
        return {LEFTLOOP, "while(d[p] ^ 0){"};
    }
    if(token.type == RIGHTLOOP)
    {
        current++;
        return {RIGHTLOOP, "}"};
    }
    if(token.type == OUT)
    {
        current++;
        return {OUT, "printf(\"%c\", d[p]);"};
    }
    if(token.type == IN)
    {
        current++;
        return {IN, "scanf(\"%c\", &d[p]);"};
    }
    throw "Unrecognized token " + to_string(token.type) + " : " + token.value;
}

vector<Token> tokenize(char *input)
{
    vector<Token> tokens;
    char *token = strtok(input, " \n\t\r\v\f");
    while(token != NULL)
    {
        if(strcmp(token, "desuwa") == 0)
            tokens.push_back({INCRBYTE, token});
        else if(strcmp(token, "desuwah") == 0)
            tokens.push_back({DECRBYTE, token});
        else if(strcmp(token, "desu") == 0)
            tokens.push_back({RGTPTR, token});
        else if(strcmp(token, "des") == 0)
            tokens.push_back({LFTPTR, token});
        else if(strcmp(token, "tan") == 0)
            tokens.push_back({LEFTLOOP, token});
        else if(strcmp(token, "chan") == 0)
            tokens.push_back({RIGHTLOOP, token});
        else if(strcmp(token, "senpai") == 0)
            tokens.push_back({OUT, token});
        else if(strcmp(token, "waifu") == 0)
            tokens.push_back({IN, token});
        else
        {
            string t = "Unrecognized token ";
            t += token;
            throw t;
        }

        token = strtok(NULL, " \n\t\r\v\f");
    }
    return tokens;
}