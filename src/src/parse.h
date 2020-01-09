/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     ADCODE = 280,
     HTCODE = 281,
     PHCODE = 282,
     HCODE = 283,
     ACODE = 284,
     ATCODE = 285,
     STRING = 286,
     PUBLIC = 287,
     PRIVATE = 288,
     PROTECTED = 289,
     CLASSWIDE = 290,
     PROPERTY = 291,
     ARGUMENT = 292,
     VIRTUAL = 293,
     SIGNAL = 294,
     OVERRIDE = 295,
     NICK = 296,
     BLURB = 297,
     MAXIMUM = 298,
     MINIMUM = 299,
     DEFAULT_VALUE = 300,
     ERROR = 301,
     FLAGS = 302,
     TYPE = 303,
     FLAGS_TYPE = 304,
     ENUM_TYPE = 305,
     PARAM_TYPE = 306,
     BOXED_TYPE = 307,
     OBJECT_TYPE = 308
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
#define ADCODE 280
#define HTCODE 281
#define PHCODE 282
#define HCODE 283
#define ACODE 284
#define ATCODE 285
#define STRING 286
#define PUBLIC 287
#define PRIVATE 288
#define PROTECTED 289
#define CLASSWIDE 290
#define PROPERTY 291
#define ARGUMENT 292
#define VIRTUAL 293
#define SIGNAL 294
#define OVERRIDE 295
#define NICK 296
#define BLURB 297
#define MAXIMUM 298
#define MINIMUM 299
#define DEFAULT_VALUE 300
#define ERROR 301
#define FLAGS 302
#define TYPE 303
#define FLAGS_TYPE 304
#define ENUM_TYPE 305
#define PARAM_TYPE 306
#define BOXED_TYPE 307
#define OBJECT_TYPE 308




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 678 "parse.y"
{
	char *id;
	GString *cbuf;
	GList *list;
	int line;
	int sigtype;
}
/* Line 1489 of yacc.c.  */
#line 163 "parse.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

