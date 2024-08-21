/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NEWLINE = 258,                 /* NEWLINE  */
    AS = 259,                      /* AS  */
    ASYNC = 260,                   /* ASYNC  */
    ASSERT = 261,                  /* ASSERT  */
    AWAIT = 262,                   /* AWAIT  */
    BREAK = 263,                   /* BREAK  */
    CLASS = 264,                   /* CLASS  */
    CONTINUE = 265,                /* CONTINUE  */
    DEF = 266,                     /* DEF  */
    DEL = 267,                     /* DEL  */
    ELIF = 268,                    /* ELIF  */
    ELSE = 269,                    /* ELSE  */
    EXCEPT = 270,                  /* EXCEPT  */
    FALSE = 271,                   /* FALSE  */
    FINALLY = 272,                 /* FINALLY  */
    FOR = 273,                     /* FOR  */
    FROM = 274,                    /* FROM  */
    GLOBAL = 275,                  /* GLOBAL  */
    IF = 276,                      /* IF  */
    IMPORT = 277,                  /* IMPORT  */
    IN = 278,                      /* IN  */
    IS = 279,                      /* IS  */
    LAMBDA = 280,                  /* LAMBDA  */
    NONE = 281,                    /* NONE  */
    NONLOCAL = 282,                /* NONLOCAL  */
    PASS = 283,                    /* PASS  */
    RAISE = 284,                   /* RAISE  */
    RETURN = 285,                  /* RETURN  */
    TRUE = 286,                    /* TRUE  */
    TRY = 287,                     /* TRY  */
    WHILE = 288,                   /* WHILE  */
    WITH = 289,                    /* WITH  */
    YIELD = 290,                   /* YIELD  */
    RANGE = 291,                   /* RANGE  */
    LEN = 292,                     /* LEN  */
    PRINT = 293,                   /* PRINT  */
    NAME = 294,                    /* NAME  */
    NUMBER = 295,                  /* NUMBER  */
    NUMBER_INT = 296,              /* NUMBER_INT  */
    NUMBER_FLOAT = 297,            /* NUMBER_FLOAT  */
    INT = 298,                     /* INT  */
    FLOAT = 299,                   /* FLOAT  */
    STR = 300,                     /* STR  */
    BOOL = 301,                    /* BOOL  */
    LIST = 302,                    /* LIST  */
    TRIPLE_DOT = 303,              /* TRIPLE_DOT  */
    MINUS = 304,                   /* MINUS  */
    PLUS = 305,                    /* PLUS  */
    ASTERISK = 306,                /* ASTERISK  */
    FORWARDSLASH = 307,            /* FORWARDSLASH  */
    DOUBLESLASH = 308,             /* DOUBLESLASH  */
    DOUBLE_STAR = 309,             /* DOUBLE_STAR  */
    NOT = 310,                     /* NOT  */
    OR = 311,                      /* OR  */
    AND = 312,                     /* AND  */
    LT_LT = 313,                   /* LT_LT  */
    GT_GT = 314,                   /* GT_GT  */
    AMPERSAND = 315,               /* AMPERSAND  */
    BAR = 316,                     /* BAR  */
    CAP = 317,                     /* CAP  */
    TILDE = 318,                   /* TILDE  */
    COLON_EQ = 319,                /* COLON_EQ  */
    LT = 320,                      /* LT  */
    GT = 321,                      /* GT  */
    LT_EQ = 322,                   /* LT_EQ  */
    GT_EQ = 323,                   /* GT_EQ  */
    EQ_EQ = 324,                   /* EQ_EQ  */
    NOT_EQ = 325,                  /* NOT_EQ  */
    PERCENT = 326,                 /* PERCENT  */
    STRING = 327,                  /* STRING  */
    LPAREN = 328,                  /* LPAREN  */
    RPAREN = 329,                  /* RPAREN  */
    LCURLY = 330,                  /* LCURLY  */
    RCURLY = 331,                  /* RCURLY  */
    LSQUARE = 332,                 /* LSQUARE  */
    RSQUARE = 333,                 /* RSQUARE  */
    DOT = 334,                     /* DOT  */
    COMMA = 335,                   /* COMMA  */
    COLON = 336,                   /* COLON  */
    SEMICOLON = 337,               /* SEMICOLON  */
    RARR = 338,                    /* RARR  */
    AMPERSAND_EQ = 339,            /* AMPERSAND_EQ  */
    AT = 340,                      /* AT  */
    AT_EQ = 341,                   /* AT_EQ  */
    CAP_EQ = 342,                  /* CAP_EQ  */
    DOUBLE_SLASH_EQ = 343,         /* DOUBLE_SLASH_EQ  */
    DOUBLE_STAR_EQ = 344,          /* DOUBLE_STAR_EQ  */
    EQUALS = 345,                  /* EQUALS  */
    FORWARDSLASH_EQ = 346,         /* FORWARDSLASH_EQ  */
    LT_GT = 347,                   /* LT_GT  */
    LT_LT_EQ = 348,                /* LT_LT_EQ  */
    MINUS_EQ = 349,                /* MINUS_EQ  */
    PERCENT_EQ = 350,              /* PERCENT_EQ  */
    PIPE_EQ = 351,                 /* PIPE_EQ  */
    PLUS_EQ = 352,                 /* PLUS_EQ  */
    RT_RT_EQ = 353,                /* RT_RT_EQ  */
    STAR_EQ = 354,                 /* STAR_EQ  */
    INDENT = 355,                  /* INDENT  */
    DEDENT = 356,                  /* DEDENT  */
    ENDMARKER = 357                /* ENDMARKER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 1670 "parser.y"

    int nodeNum;
    char* text;
    
    struct{
        int nodeNum;
        int count;
        int size;
        int ndim;
        int nelem; 
        int is_self;        /*for self.x:int*/
        char lexeme[100];
        char type[100];
        char par_arg_shape[100];

        int list_size;

        char end_label[100];

        char break_[100];
        char cont_[100];

        
        char success_[100];
        char start_[100];
        char end_[100];
        
        char range_start[100];
        char range_end[100];
        char range_step[100];

        char* TAC;
        char res[100];

    } node;


#line 204 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
