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

#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
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
    LIST_T = 258,                  /* LIST_T  */
    ID_T = 259,                    /* ID_T  */
    PRINT_T = 260,                 /* PRINT_T  */
    PRINT_R_T = 261,               /* PRINT_R_T  */
    NUMBER_TYPE_T = 262,           /* NUMBER_TYPE_T  */
    STRING_TYPE_T = 263,           /* STRING_TYPE_T  */
    BROJ_T = 264,                  /* BROJ_T  */
    STRING_T = 265,                /* STRING_T  */
    PUSH_BACK_T = 266,             /* PUSH_BACK_T  */
    PUSH_FRONT_T = 267,            /* PUSH_FRONT_T  */
    PUSH_T = 268,                  /* PUSH_T  */
    POP_BACK_T = 269,              /* POP_BACK_T  */
    POP_FRONT_T = 270,             /* POP_FRONT_T  */
    POP_T = 271,                   /* POP_T  */
    FIND_T = 272,                  /* FIND_T  */
    GET_T = 273,                   /* GET_T  */
    LEQ_T = 274,                   /* LEQ_T  */
    GEQ_T = 275,                   /* GEQ_T  */
    EQ_T = 276,                    /* EQ_T  */
    NEQ_T = 277,                   /* NEQ_T  */
    UMINUS = 278                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "parser.ypp"

    std::string *niska;
    TipPodataka tip;
    Lista *lista;
    std::vector<std::string> *lista_elemenata;

#line 94 "parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */
