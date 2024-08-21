%{
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <map>
#include <vector>
#include <stack>
#include <utility>
using namespace std;

extern int yylineno;
extern FILE *yyin;
extern std::stack<int> indentStk;
extern char * yytext;
int yylex();
void yyerror(const char *s);


/*AST generation code*/
// map<int, pair<string, vector<int>>> AST;
// int nodeCount = -1;

// int nodeInit(string nodeName){
//   nodeCount++;
//   vector<int>children;
//   string name = nodeName;
//   AST[nodeCount].first = name;
//   AST[nodeCount].second = children;
//   return nodeCount;
// }

// void linkChildtoParent(int parent, int child){
//   AST[parent].second.push_back(child);
// }

// void write_gv(string &filename){
//   ofstream out(filename);
//   if(!out.is_open()){
//     cerr << "ERROR: gv file can't be opened ";
//     return;
//   }
//   out << "digraph AST {\n";

//   for(const auto &node: AST){
//     int nodeId = node.first;
//     string nodeName = node.second.first;
//     vector<int> nodeChildren = node.second.second;

//     if (nodeName[nodeName.size() - 2] == '\"') {
//             //is string 
//             nodeName = nodeName.substr(0, nodeName.size() - 2);
//             int i = 0;
//             while (i < nodeName.size() && nodeName[i] != '\"') {
//                 i++;
                
//             }
//             // for(i = 0; i<nodeName.size()-2; i++){
//             //     if(nodeName[i] == '\"')break;
//             // }

//             nodeName = nodeName.substr(0,i) + "\\\"" + nodeName.substr(i + 1, nodeName.size()-1) + "\\\")";
//         }

//     out << nodeId << " [label=\"" << nodeName << "\"];\n";
//     for(auto c: nodeChildren){
//       if(c!=-1) out << nodeId << "->" << c << ";\n";
//     }
//   }
//   out << "}";
//   out.close();
// }


map<int, pair<string, vector<int>>> AST;
int nodeCount = -1;

void linkChildtoParent(int parent, int child) {
  (AST[parent].second).push_back(child);
}
int nodeInit(string nodeName) {
  string name = nodeName;
  vector<int> children;
  AST[nodeCount] = make_pair(name, children);
  return nodeCount;
}


void write_gv(string &filename) {
  ofstream out(filename);
  if (!out.is_open()) {
    cerr << "ERROR: gv file can't be opened ";
    return;
  }

  out << "digraph AST {\n";
  
  for (const auto &node : AST) {
    int nodeId = node.first;
    string nodeName = node.second.first;
    vector<int> nodeChildren = node.second.second;



    out << nodeId << " [label=\"" << nodeName << "\"];\n";
    for (auto c : nodeChildren) {
      if (c>=0) {
        out << nodeId << "->" << c << ";\n";
      }
    }
  }

  out << "}";
  out.close();
}

int debug = 1;

void debugging(string msg, int mode){
    if(debug == mode){
        cout <<"Debugging: "<<"message is->"<< msg << endl;
    }

}

%}

%union{
    int nodeNum;
    char* text;
}





%token NEWLINE

%token AS ASYNC ASSERT AWAIT BREAK CLASS CONTINUE DEF DEL ELIF ELSE EXCEPT FALSE FINALLY FOR FROM GLOBAL IF IMPORT IN IS LAMBDA NONE NONLOCAL PASS RAISE RETURN TRUE TRY WHILE WITH YIELD


%token <text> NAME
%token <text> NUMBER

%token INT FLOAT STR BOOL LIST

%token TRIPLE_DOT


%token MINUS PLUS ASTERISK FORWARDSLASH DOUBLESLASH DOUBLE_STAR NOT OR AND  LT_LT GT_GT AMPERSAND BAR CAP TILDE COLON_EQ LT GT LT_EQ GT_EQ EQ_EQ NOT_EQ PERCENT


%token <text>STRING

%token LPAREN RPAREN LCURLY RCURLY LSQUARE RSQUARE DOT COMMA COLON SEMICOLON RARR

%token AMPERSAND_EQ AT AT_EQ CAP_EQ DOUBLE_SLASH_EQ DOUBLE_STAR_EQ EQUALS FORWARDSLASH_EQ LT_GT LT_LT_EQ MINUS_EQ PERCENT_EQ PIPE_EQ PLUS_EQ RT_RT_EQ STAR_EQ


%left LT GT LT_EQ GT_EQ 
%left PLUS MINUS ASTERISK FORWARDSLASH DOUBLESLASH
%left OR AND
%left PERCENT DOUBLE_STAR GT_GT 
%left AT


%right EQUALS PLUS_EQ MINUS_EQ STAR_EQ FORWARDSLASH_EQ DOUBLE_SLASH_EQ PERCENT_EQ AT_EQ AMPERSAND_EQ PIPE_EQ CAP_EQ RT_RT_EQ LT_LT_EQ DOUBLE_STAR_EQ 

%right TILDE COLON_EQ NOT


%token INDENT
%token DEDENT
%token ENDMARKER




%type <nodeNum> input
%type <nodeNum> stmts
%type <nodeNum> normalstmt ending exprstmt listType stmt funccall delstmt globalstatement assignstmt assignments multiplicativeExpr ids vardeclaration typeDeclaration primitiveType numericType  listExpr expression logicalOr logicalAnd bitwiseOr bitwiseXor bitwiseAnd equalExpr shiftExpr addExpr expoExpr relExpr negated_expr nonlocalstmt primaryExpr arguments compoundstmt ifstatement elifstmts elifstmt elseblock whilestatement forstmt forexpr ForList funcdef parameters returnType Suite classdef returnnstmt


%start input


%%


    

/* Starting symbol */
    input 
        : stmts ending  {
            debugging("input", 1);
            $$ = nodeInit("input");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $2);
            $$ = $$;

            }
        |  ending {
            $$ = nodeInit("input");
            nodeCount++;
            linkChildtoParent($$, $1);
        }
        ;
    

    stmts : 
        stmt   { 
            $$ = $1;
            debugging("stmts", 1);
        }
        | stmts stmt { 
            debugging("stmts", 1);
            $$ = nodeInit("stmts");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $2);
        }
        ;

        globalstatement :
        GLOBAL NAME    { 
            debugging("global statement", 1);
            $$ = nodeInit("Global");
            nodeCount++;
            linkChildtoParent($$, nodeInit($2));
            nodeCount++;
        }
        ;
    
    nonlocalstmt :
        NONLOCAL NAME  { 
            debugging("nonlocal statement", 1);
            $$ = nodeInit("nonlocal");
            nodeCount++;
            linkChildtoParent($$, nodeInit($2));
            nodeCount++;
        }
        ;

    stmt : 
        normalstmt NEWLINE  {
            $$ = $1;
            debugging("stmt", 1);
        }
        | compoundstmt  { 
            debugging("stmt", 1);
            $$ = $1;
        }
        ;

    normalstmt :
        exprstmt     { 
            debugging("normalstmt", 1);
            $$ = $1;
        }
        | delstmt              { 
            $$ = $1;
            cout << "simple stmt" << endl;
        }
        | BREAK           {
            debugging("normal break stmt", 1);
    
            $$ = nodeInit("break");
            nodeCount++;

        }
        | CONTINUE         { 
            $$ = nodeInit("continue");
            nodeCount++;
            debugging("normal continue stmt", 1);
        }
        | PASS  {
            debugging("normal pass stmt", 1);
            $$ = nodeInit("pass");
            nodeCount++;
        }
        | globalstatement         { 
            debugging("normal global stmt", 1);
            $$ = $1;
        }
        | nonlocalstmt      { 
            debugging("normal nonlocal stmt", 1);
            $$ = $1;
        }
        | assignstmt        { 
            debugging("normal assign stmt", 1);
            $$ = $1;
        }
        | returnnstmt         { 
            debugging("normal return stmt", 1);
            $$ = $1;
        }
        | expression                 { 
            debugging("normal expression stmt", 1);
            $$ = $1;
        }
        ;
        
         compoundstmt : 
        ifstatement  {
            debugging("compound stmt", 1);
            $$=$1;
        }
        | whilestatement  { 
            debugging("compound stmt", 1);
            $$ = $1;
        }
        | forstmt  { 
            debugging("compound stmt", 1);
            $$ = $1;
        }
        | funcdef  { 
            debugging("compound stmt", 1);
            $$ = $1;
        }
        | classdef  { 
            debugging("compound stmt", 1);
            $$ = $1;
        }
        ;


    
    exprstmt :
        vardeclaration    { 
            debugging("exprstmt", 1);
            $$ = $1;
        }
     
        ;
        returnnstmt :
        RETURN expression   { 
            debugging("return statement",1);
            $$ = nodeInit("return");
            nodeCount++;
            linkChildtoParent($$, $2);

        }
        | RETURN  { 
            debugging("return statement",1);
            $$ = nodeInit("return");
            nodeCount++;
        }
        ;

    delstmt :
        DEL expression   { 
            debugging("delstmt", 1);
            $$ = nodeInit("deleteStmt");
            nodeCount++;
            linkChildtoParent($$, $2);
        }
        ;
    
    
   

    assignstmt:
        assignments
        | ids PLUS_EQ expression  {
            $$ = nodeInit("+=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | ids MINUS_EQ expression  {
            $$ = nodeInit("-=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
         }
        | ids STAR_EQ expression  { 
            $$ = nodeInit("*=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | ids FORWARDSLASH_EQ expression  {
            $$ = nodeInit("/=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
         }
        | ids DOUBLE_SLASH_EQ expression  {
            $$ = nodeInit("//=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
         }
        | ids PERCENT_EQ expression  { 
            $$ = nodeInit("%=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | ids AT_EQ expression  { 
            $$ = nodeInit("@=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | ids AMPERSAND_EQ expression  {
            $$ = nodeInit("&=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
         }
        | ids PIPE_EQ expression  { 
            $$ = nodeInit("|=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | ids CAP_EQ expression  { 
            $$ = nodeInit("^=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | ids RT_RT_EQ expression  {
            $$ = nodeInit(">>=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
         }
        | ids LT_LT_EQ expression  { 
            $$ = nodeInit("<<=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | ids DOUBLE_STAR_EQ expression  { 
            $$ = nodeInit("**=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        ; 

    assignments :
        ids EQUALS assignments { 
            debugging("assignments", 1);
            $$ = nodeInit("=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | ids EQUALS expression  {
            debugging("assignments", 1);
            $$ = nodeInit("=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
         }
        ;

  
    vardeclaration :
        typeDeclaration EQUALS expression { 
            debugging("variable declaration", 1);
            $$ = nodeInit("=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);

        }
        | typeDeclaration {
            debugging("variable declaration", 1);
            $$ = $1;
        }

        ;

    typeDeclaration :
        NAME COLON primitiveType  {
            $$ = nodeInit(":");
            nodeCount++;
            debugging("type declaration", 1);
            string t= $1;
            string s = "ID(" +t + ")";

            linkChildtoParent($$, nodeInit(s));
            nodeCount++;
            linkChildtoParent($$, $3);
        }
        
        | NAME DOT typeDeclaration { 
            $$ = nodeInit("atomicExpe");
            nodeCount++;
            debugging("type declaration", 1);
            string t= $1;
            string s = "ID(" +t + ")";
            linkChildtoParent($$, nodeInit(s));
            nodeCount++;
            int dot = nodeInit(".");
            nodeCount++;
            linkChildtoParent($$, dot);
            linkChildtoParent(dot, $3);
        }
        ;
          ids : 
        NAME{
            debugging("ids", 1);
            string t= $1;
            string s = "ID(" +t + ")"; 
            $$ = nodeInit(s);
            nodeCount++;
         }
        | NAME LSQUARE expression RSQUARE {
            debugging("ids", 1);
            $$ = nodeInit("atom_expr");
            nodeCount++;

            string t= $1;
            string s = "ID(" +t + ")"; 
            linkChildtoParent($$, nodeInit(s));
            nodeCount++;
            
            int child= nodeInit("[]");
            nodeCount++;
            linkChildtoParent($$, child);
            linkChildtoParent(child, $3);
        }
        | NAME DOT ids {
            debugging("ids", 1);
            $$ = nodeInit("atomic_expr");
            nodeCount++;
            
            string t= $1;
            string s = "ID(" +t + ")";

            linkChildtoParent($$, nodeInit(s));
            nodeCount++;
            int dot = nodeInit(".");
            nodeCount++;
            linkChildtoParent($$, dot);
            linkChildtoParent(dot, $3);

        }
        ;


    primitiveType : 
        numericType   { 
            debugging("primitive numeric", 1);
            $$ = $1;
        }
        | STR     { 
            debugging("primitive string", 1);
            $$ = nodeInit("string");
            nodeCount++;
        }
        | BOOL    {
            debugging("primitive boolean", 1);
            $$ = nodeInit("bool"); 
            nodeCount++;

        }
        | listType   {
             debugging("primitive list", 1);
                $$ = $1;
        }
        | NAME       {
            debugging("primitive ids", 1);
            string t= $1;
            string s = "ID(" +t + ")";

            $$ = nodeInit(s);
            nodeCount++;
        }

        ; 
    
    numericType : 
        INT       { 
            debugging("numeric int", 1);
            $$ = nodeInit("int");
            nodeCount++;
        }
        | FLOAT   {
            debugging("numeric float", 1);
            $$ = nodeInit("float");
            nodeCount++;
        }
        ;


    listType :
        LIST LSQUARE primitiveType RSQUARE { 
            debugging("list type", 1);
            $$ = nodeInit("atomExpr");
            nodeCount++;
            linkChildtoParent($$, nodeInit("list"));
            nodeCount++;
            int child = nodeInit("[]");
            nodeCount++;
            linkChildtoParent(child, $3);
            linkChildtoParent($$, child);
        }
        ;

  
    

    
logicalOr 
        : logicalAnd    {
            debugging("logical or", 1);
            $$ = $1;
        }
        | logicalOr OR logicalAnd { 
            debugging("logical or", 1);
            $$ = nodeInit("or");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        ;

    logicalAnd 
        : bitwiseOr  { 
            debugging("logical and", 1);
            $$ = $1;
        }
        | logicalAnd AND bitwiseOr { 
            debugging("logical and", 1);
            $$= nodeInit("and");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        ;

  

    bitwiseOr 
        : bitwiseXor   { 
            debugging("bitwise or", 1);
            $$ = $1;
        }
        | bitwiseOr BAR bitwiseXor { 
            debugging("bitwise or", 1);
            $$ = nodeInit("|");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        ;

    bitwiseXor 
        : bitwiseAnd   { 
            debugging("bitwise xor", 1);
            $$ = $1;
        }
        | bitwiseXor CAP bitwiseAnd { 
            debugging("bitwise xor", 1);
            $$ = nodeInit("^");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
    ;

    bitwiseAnd 
        : equalExpr    { 
            debugging("bitwise and", 1);
            $$ = $1;
        }
        | bitwiseAnd AMPERSAND equalExpr { 
            debugging("bitwise and", 1);
            $$ = nodeInit("&");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        ;

        listExpr :
        expression COMMA listExpr  { 
            debugging("list expression", 1);
            $$ = nodeInit(",");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | expression { 
            debugging("list expression", 1);
            $$ = $1;
        }
        | %empty {
            $$ = -1;
        }
        

        expression 
        : logicalOr { 
            debugging("expression", 1);
            $$ = $1;
        }
        ;

    equalExpr 
        : relExpr  { 
            debugging("equality expression", 1);
            $$ = $1;
        }
        | equalExpr EQ_EQ relExpr {  
            debugging("equality expression", 1);
            $$ = nodeInit("==");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | equalExpr NOT_EQ relExpr {
            debugging("equality expression", 1);
            $$ = nodeInit("!=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | equalExpr COLON_EQ relExpr {
            debugging("equality expression", 1);
            $$ = nodeInit(":=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | equalExpr IS relExpr {
            debugging("equality expression", 1);
            $$ = nodeInit("=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | equalExpr IN ids {
            debugging("equality expression", 1);
            $$ = nodeInit("in");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | equalExpr NOT IN ids {
            debugging("equality expression", 1);
            $$ = nodeInit("!=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $4);
        }
        ;

   

    shiftExpr 
        : addExpr
        | shiftExpr LT_LT addExpr {
            debugging("shift expression", 1);
            $$ = nodeInit("<<");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
         }
        | shiftExpr GT_GT addExpr { 
            debugging("shift expression", 1);
            $$ = nodeInit(">>");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        ;

    addExpr 
        : multiplicativeExpr  { 
            debugging("additive expression", 1);
            $$ = $1;
        }
        | addExpr PLUS multiplicativeExpr { 
            debugging("additive expression", 1);
            $$ = nodeInit("+");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | addExpr MINUS multiplicativeExpr { 
            debugging("additive expression", 1);
            $$ = nodeInit("-");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        ;

         relExpr 
        : shiftExpr  { 
            debugging("relational expression", 1);
            $$ = $1;
        }
        | relExpr LT_GT shiftExpr { 
            debugging("relational expression", 1);
            $$ = nodeInit("<>");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | relExpr LT shiftExpr { 
            debugging("relational expression", 1);
            $$ = nodeInit("<");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }

        | relExpr GT shiftExpr { 
            debugging("relational expression", 1);
            $$ = nodeInit(">");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | relExpr LT_EQ shiftExpr {
            debugging("relational expression", 1);
            $$ = nodeInit("<=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
         }
        | relExpr GT_EQ shiftExpr {
            debugging("relational expression", 1);
            $$ = nodeInit(">=");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
         }
        ;

    multiplicativeExpr 
        : expoExpr   { 
            debugging("multiplicative expression", 1);
            $$ = $1;
        }
        | multiplicativeExpr ASTERISK expoExpr { 
            debugging("multiplicative expression", 1);
            $$ = nodeInit("*");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | multiplicativeExpr FORWARDSLASH expoExpr  {
            debugging("multiplicative expression", 1);
            $$ = nodeInit("/");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
         }
        | multiplicativeExpr DOUBLESLASH expoExpr {
            debugging("multiplicative expression", 1);
            $$ = nodeInit("//");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
         }
        | multiplicativeExpr PERCENT expoExpr { 
            debugging("multiplicative expression", 1);
            $$ = nodeInit("%");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        ;

    expoExpr 
        : negated_expr     {
            debugging("exponentiation expression", 1);
            $$ = $1;
         }
        | negated_expr DOUBLE_STAR expoExpr {
            debugging("exponentiation expression", 1);
            $$ = nodeInit("**");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
         }
        ;

    negated_expr 
        : primaryExpr    {
            debugging("negated expression", 1);
            $$ = $1;
        }
        | MINUS negated_expr {
            debugging("negated expression", 1);
            $$ = nodeInit("-");
            nodeCount++;
            linkChildtoParent($$, $2);
         }
        | NOT negated_expr { 
            debugging("negated expression", 1);
            $$ = nodeInit("not");
            nodeCount++;
            linkChildtoParent($$, $2);
        }
        | TILDE negated_expr {
            debugging("negated expression", 1);
            $$ = nodeInit("~");
            nodeCount++;
            linkChildtoParent($$, $2);
         }
        | PLUS negated_expr { 
            debugging("negated expression", 1);
            $$ = nodeInit("+");
            nodeCount++;
            linkChildtoParent($$, $2);
        }
        ;

    primaryExpr 
        : ids { 
            debugging("primary expression", 1);
            cout << "primary expression" << endl;
            $$ = $1;
        }
        | NUMBER { 
            debugging("primary expression", 1);
            string t= $1;
            string s = "LITERAL(" +t + ")"; 
            $$ = nodeInit(s);
            nodeCount++;
        }
        | STRING { 
            debugging("primary expression, string", 1);
            string t= $1;
            // 
            t = t.substr(1, t.size()-2);
            t = "\\\"" + t + "\\\"";
            string s = "LITERAL(" +t + ")";
            $$ = nodeInit(s);
            nodeCount++;
        }
        | TRUE {
            debugging("primary expression, true", 1);
            $$ = nodeInit("True");
            nodeCount++;
         }
        | FALSE {
            debugging("primary expression, false", 1);
            $$ = nodeInit("False");
            nodeCount++;
         }
        | NONE { 
            debugging("primary expression, none", 1);
            $$ = nodeInit("None");
            nodeCount++;
        }
        | funccall { 
            debugging("function call", 1);
            $$ = $1;
        }
        | LPAREN expression RPAREN { 
            $$ = nodeInit("()");
            nodeCount++;
            linkChildtoParent($$, $2);
        }
        | LSQUARE listExpr RSQUARE {
            $$ = nodeInit("[]");
            nodeCount++;
            linkChildtoParent($$, $2);
        }
        ;


   
    
    arguments :
        expression { 
            debugging("arguments", 1);
            $$ = $1;
        }
        | expression COMMA arguments {
            debugging("arguments", 1);
            $$ = nodeInit(",");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | %empty  {
            $$ = -1;
        }
        ;
         funccall :
        NAME LPAREN arguments RPAREN {
            $$ = nodeInit("funccall");
            nodeCount++;
            linkChildtoParent($$, nodeInit($1));
            nodeCount++;
            int child = nodeInit("()");
            nodeCount++;
            linkChildtoParent($$, child);
            linkChildtoParent(child, $3);
        }
        | NAME DOT funccall { 
            $$ = nodeInit("funccall");
            nodeCount++;
            linkChildtoParent($$, nodeInit($1));
            nodeCount++;
            nodeCount++;
            int dot = nodeInit(".");
            linkChildtoParent($$, dot);
            linkChildtoParent(dot, $3);
        }
        ;


   
    
    ifstatement : 
        IF expression COLON Suite elifstmts elseblock {
            debugging("if stmt", 1);
            $$ = nodeInit("if");
            nodeCount++;
            linkChildtoParent($$, $2);
            nodeCount++;
            linkChildtoParent($$, nodeInit(":"));
            linkChildtoParent($$, $4);
            linkChildtoParent($$, $5);
            linkChildtoParent($$, $6);

        }
        | IF expression COLON Suite elifstmts { 
            debugging("if stmt", 1);
            $$ = nodeInit("if");
            nodeCount++;
            linkChildtoParent($$, $2);
            linkChildtoParent($$, nodeInit(":"));
            nodeCount++;
            linkChildtoParent($$, $4);
            linkChildtoParent($$, $5);
        }
        | IF expression COLON Suite elseblock { 
            debugging("if stmt", 1);
            $$ = nodeInit("if");
            nodeCount++;
            linkChildtoParent($$, $2);
            linkChildtoParent($$, nodeInit(":"));
            nodeCount++;
            linkChildtoParent($$, $4);
            linkChildtoParent($$, $5);
        }
        | IF expression COLON Suite { 
            debugging("if stmt", 1);
            $$ = nodeInit("if");
            nodeCount++;
            linkChildtoParent($$, $2);
            linkChildtoParent($$, nodeInit(":"));
            nodeCount++;
            linkChildtoParent($$, $4);

        }

        elifstmt : 
        ELIF expression COLON Suite  {
            debugging("elifstmt", 1);
            $$ = nodeInit("elif");
            nodeCount++;
            linkChildtoParent($$, $2);
            linkChildtoParent($$, nodeInit(":"));
            nodeCount++;
            linkChildtoParent($$, $4);
         }
        ;

    elifstmts : 
        elifstmt            { 
            debugging("elifstmts", 1);
            $$ = $1;
        }
        | elifstmts elifstmt   {
            debugging("elifstmts", 1);
            $$ = nodeInit("elif");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $2);
        }
        
        ;

    

    elseblock :
        ELSE COLON Suite  { 
            debugging("elseblock", 1);
            $$ = nodeInit("else");
            nodeCount++;
            linkChildtoParent($$, nodeInit(":"));
            nodeCount++;
            linkChildtoParent($$, $3);
        } 
        ;

forstmt :
        FOR forexpr COLON Suite elseblock  {
            debugging("for stmt", 1);
            $$ = nodeInit("for");
            nodeCount++;
            linkChildtoParent($$, $2);
            linkChildtoParent($$, nodeInit(":"));
            nodeCount++;
            linkChildtoParent($$, $4);
            linkChildtoParent($$, $5);
         }
        | FOR forexpr COLON Suite  {
            debugging("for stmt", 1);
            $$ = nodeInit("for");
            nodeCount++;
            linkChildtoParent($$, $2);
            linkChildtoParent($$, nodeInit(":"));
            nodeCount++;
            linkChildtoParent($$, $4);
         }
        ;

        ForList :
        funccall   {
            debugging("for list", 1);
            $$ = $1;
         }
        | ids  {
            debugging("for list", 1);
            $$ = $1;
         }
        | LSQUARE listExpr RSQUARE {
            debugging("for list", 1);
            $$ = nodeInit("[]");
            nodeCount++;
            linkChildtoParent($$, $2);
        
        }

    whilestatement :
        WHILE expression COLON Suite elseblock  {
            debugging("while stmt", 1);
            $$ = nodeInit("while");
            nodeCount++;
            linkChildtoParent($$, $2);
            nodeCount++;
            linkChildtoParent($$, nodeInit(":"));
            linkChildtoParent($$, $4);
            linkChildtoParent($$, $5);
         }
        | WHILE expression COLON Suite  { 
            debugging("while stmt", 1);
            $$ = nodeInit("while");
            nodeCount++;
            linkChildtoParent($$, $2);
            nodeCount++;
            linkChildtoParent($$, nodeInit(":"));
            linkChildtoParent($$, $4);
        }
        ;


     parameters: 
        vardeclaration  {
            debugging("parameters", 1);
            $$ = $1;
        }
        | parameters COMMA vardeclaration {
            debugging("parameters", 1);
            $$ = nodeInit(",");
            nodeCount++;
            linkChildtoParent($$, $1);
            linkChildtoParent($$, $3);
        }
        | NAME {
            debugging("parameters", 1);
            string t= $1;
            string s = "ID(" +t + ")";
            $$ = nodeInit(s);
            nodeCount++;
        }
        | %empty {
            debugging("parameters", 1);
            $$ = -1;
        }
        ;  
    returnType : 
        primitiveType { 
            debugging("return type", 1);
            $$ = $1;
        }
       
        | NONE { 
            debugging("return type", 1);
            $$ = nodeInit("None");
            nodeCount++;
        }
        ;
    
    

    forexpr :
        NAME IN ForList    { 
            debugging("for expression", 1);
            $$ = nodeInit("in");
            nodeCount++;
            
            string t= $1;
            string s = "ID(" +t + ")";
            linkChildtoParent($$, nodeInit(s));
            nodeCount++;
            linkChildtoParent($$, $3);
        }
        
        ;


    funcdef :
        DEF NAME LPAREN parameters RPAREN RARR returnType COLON Suite  { 
            debugging("function definition", 1);
            $$ = nodeInit("def");
            nodeCount++;
            string t= $2;
            string s = "ID(" +t + ")";
            linkChildtoParent($$, nodeInit(s));
            nodeCount++;
            int parens=nodeInit("()");
            nodeCount++;
            linkChildtoParent(parens, $4);
            linkChildtoParent($$, parens);
            linkChildtoParent($$, $7);
            linkChildtoParent($$, nodeInit(":"));
            nodeCount++;
            linkChildtoParent($$, $9);
        }
        | DEF NAME LPAREN parameters RPAREN COLON Suite  { 
            cout << "function definition" << endl;
            $$ = nodeInit("def");
            nodeCount++;
            
            string t= $2;
            string s = "ID(" +t + ")";
            linkChildtoParent($$, nodeInit(s));
            nodeCount++;
            nodeCount++;
            int parens = nodeInit("()");
            linkChildtoParent(parens, $4);
            linkChildtoParent($$, parens);
            nodeCount++;
            linkChildtoParent($$, nodeInit(":"));
            linkChildtoParent($$, $7);
        }
        
        ;

    

    classdef :
        CLASS NAME COLON Suite    { 
            debugging("class definition", 1);
            $$ = nodeInit("class");
            nodeCount++;
            linkChildtoParent($$, nodeInit($2));
            nodeCount++;
            linkChildtoParent($$, nodeInit(":"));
            nodeCount++;
            linkChildtoParent($$, $4);

        }
        | CLASS NAME LPAREN arguments RPAREN COLON Suite  { 
            debugging("class definition", 1);
            $$ = nodeInit("class");
            nodeCount++;

            string t= $2;
            string s = "ID(" +t + ")";

            linkChildtoParent($$, nodeInit(s));
            nodeCount++;
            nodeCount++;
            int PARs = nodeInit("()");
            linkChildtoParent(PARs, $4);
            linkChildtoParent($$, PARs);
            linkChildtoParent($$, nodeInit(":"));
            nodeCount++;
            linkChildtoParent($$, $7);
        }
        ;
     Suite : 
        normalstmt NEWLINE { 
            debugging("suite", 1);
            $$ = $1;
        }
        | NEWLINE INDENT stmts DEDENT { 
            cout << "-----------------" << endl;
            $$ = $3;
        }
        ; 

        ending 
        : NEWLINE ending  {
            debugging("ending", 1);
            $$=nodeInit("newline"); 
            nodeCount++;
            }
        | ENDMARKER { 
            debugging("ending", 1);
            $$=nodeInit("EOF"); 
            nodeCount++;
        }
        ;


    
        ;
    /*  */

        
%%

int main(int argc, char **argv){
    indentStk.push(0);
    
    
    cout << "Starting: 0 pushed "<< indentStk.top() << endl;
    //find if --debug flag is present in the command the arguments
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "--debug") == 0){
            debug = 1;
            break;
        }
    }
    int parsed  = 0;

    //search if -f (file input) is present in the command line arguments
    for(int i = 0; i<argc; i++){
        if(strcmp(argv[i], "-f") == 0){
            if(i+1 < argc){
                FILE *fp = fopen(argv[i+1], "r");
                if(fp){

                    yyin = fp;
                    yyparse();
                    parsed = 1;
                    fclose(fp);
                }
                else{
                    printf("Error: File not found\n");
                }
            }
            else{
                printf("Error: File not found\n");
            }
        }
    }
    if(parsed == 0){
        yyin = stdin;
        yyparse();
    }

    string filename = "AST.dot";
    write_gv(filename);
    return 0;
}

void yyerror(const char *message)
{
    //error with line no and message with yytext
    fprintf(stderr, "Error at line %d: %s\n", yylineno, message);
    cerr<<"Error at "<<yytext<<endl;
    exit(EXIT_FAILURE); 
} 





