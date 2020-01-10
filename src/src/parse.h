/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CLASS = 258,
     FROM = 259,
     CONST = 260,
     VOID = 261,
     STRUCT = 262,
     UNION = 263,
     ENUM = 264,
     THREEDOTS = 265,
     SIGNED = 266,
     UNSIGNED = 267,
     LONG = 268,
     SHORT = 269,
     INT = 270,
     FLOAT = 271,
     DOUBLE = 272,
     CHAR = 273,
     TOKEN = 274,
     NUMBER = 275,
     TYPETOKEN = 276,
     ARRAY_DIM = 277,
     SINGLE_CHAR = 278,
     CCODE = 279,
     CTCODE = 280,
     ADCODE = 281,
     HTCODE = 282,
     PHCODE = 283,
     HCODE = 284,
     ACODE = 285,
     ATCODE = 286,
     STRING = 287,
     PUBLIC = 288,
     PRIVATE = 289,
     PROTECTED = 290,
     CLASSWIDE = 291,
     PROPERTY = 292,
     ARGUMENT = 293,
     VIRTUAL = 294,
     SIGNAL = 295,
     OVERRIDE = 296,
     NICK = 297,
     BLURB = 298,
     MAXIMUM = 299,
     MINIMUM = 300,
     DEFAULT_VALUE = 301,
     ERROR = 302,
     FLAGS = 303,
     TYPE = 304,
     FLAGS_TYPE = 305,
     ENUM_TYPE = 306,
     PARAM_TYPE = 307,
     BOXED_TYPE = 308,
     OBJECT_TYPE = 309
   };
#endif
/* Tokens.  */
#define CLASS 258
#define FROM 259
#define CONST 260
#define VOID 261
#define STRUCT 262
#define UNION 263
#define ENUM 264
#define THREEDOTS 265
#define SIGNED 266
#define UNSIGNED 267
#define LONG 268
#define SHORT 269
#define INT 270
#define FLOAT 271
#define DOUBLE 272
#define CHAR 273
#define TOKEN 274
#define NUMBER 275
#define TYPETOKEN 276
#define ARRAY_DIM 277
#define SINGLE_CHAR 278
#define CCODE 279
#define CTCODE 280
#define ADCODE 281
#define HTCODE 282
#define PHCODE 283
#define HCODE 284
#define ACODE 285
#define ATCODE 286
#define STRING 287
#define PUBLIC 288
#define PRIVATE 289
#define PROTECTED 290
#define CLASSWIDE 291
#define PROPERTY 292
#define ARGUMENT 293
#define VIRTUAL 294
#define SIGNAL 295
#define OVERRIDE 296
#define NICK 297
#define BLURB 298
#define MAXIMUM 299
#define MINIMUM 300
#define DEFAULT_VALUE 301
#define ERROR 302
#define FLAGS 303
#define TYPE 304
#define FLAGS_TYPE 305
#define ENUM_TYPE 306
#define PARAM_TYPE 307
#define BOXED_TYPE 308
#define OBJECT_TYPE 309




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 683 "parse.y"

	char *id;
	GString *cbuf;
	GList *list;
	int line;
	int sigtype;



/* Line 2068 of yacc.c  */
#line 168 "parse.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


