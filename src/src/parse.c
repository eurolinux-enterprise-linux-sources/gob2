/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 23 "parse.y"


#include "config.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treefuncs.h"
#include "main.h"
#include "util.h"

/* FIXME: add gettext support */
#define _(x) (x)
	
GList *nodes = NULL;

static GList *class_nodes = NULL;
Node *class = NULL;
GList *enums = NULL;
static GList *enum_vals = NULL;
static GList *flag_vals = NULL;
static GList *error_vals = NULL;

static gboolean abstract = FALSE;
static char *chunk_size = NULL;
static char *bonobo_object_class = NULL;
static int glade_xml = FALSE;
static GList *interfaces = NULL;
static GList *typestack = NULL;
static GList *funcargs = NULL;
static GList *checks = NULL;
static int has_self = FALSE;
static int vararg = FALSE;
static Method *last_added_method = NULL;

/* destructor and initializer for variables */
static gboolean destructor_unref = FALSE;
static char *destructor = NULL;
static int destructor_line = 0;
static gboolean destructor_simple = TRUE;
static char *initializer = NULL;
static int initializer_line = 0;
static int glade_widget = FALSE;

static char *funcattrs = NULL;
static char *onerror = NULL;
static char *defreturn = NULL;

static GList *gtktypes = NULL;

static Property *property = NULL;

/* this can be a global as we will only do one function at a time
   anyway */
static int the_scope = NO_SCOPE;

void free(void *ptr);
int yylex(void);

extern int ccode_line;
extern int line_no;
extern gboolean for_cpp;

extern char *yytext;

static void
yyerror(char *str)
{
	char *out=NULL;
	char *p;
	
	if(strcmp(yytext,"\n")==0) {
		out=g_strconcat("Error: ",str," before newline",NULL);
	} else if(yytext[0]=='\0') {
		out=g_strconcat("Error: ", str, " at end of input", NULL);
	} else {
		char *tmp = g_strdup(yytext);
		while((p=strchr(tmp, '\n')))
			*p='.';

		out=g_strconcat("Error: ", str, " before '", tmp, "'", NULL);
		g_free(tmp);
	}

	fprintf(stderr, "%s:%d: %s\n", filename, line_no, out);
	g_free(out);
	
	exit(1);
}

static Type *
pop_type(void)
{
	Type *type = typestack->data;
	typestack = g_list_remove(typestack,typestack->data);
	return type;
}

static void
push_variable (char *name, int scope, int line_no, char *postfix)
{
	Node *var;
	Type *type = pop_type ();

	type->postfix = postfix;
	
	var = node_new (VARIABLE_NODE,
			"scope", scope,
			"vtype:steal", type,
			"glade_widget", glade_widget,
			"id:steal", name,
			"line_no", line_no,
			"destructor_unref", destructor_unref,
			"destructor:steal", destructor,
			"destructor_line", destructor_line,
			"destructor_simple", destructor_simple,
			"initializer:steal", initializer,
			"initializer_line", initializer_line,
			"initializer_simple", TRUE,
			NULL);
	class_nodes = g_list_append(class_nodes, var);
	glade_widget = FALSE;
}

static void
push_function (int scope, int method, char *oid, char *id,
	       GString *cbuf, int line_no, int ccode_line,
	       gboolean vararg, GList *flags)
{
	Node *node;
	Type *type;
	char *c_cbuf;

	g_assert(scope != CLASS_SCOPE);
       
	if(method == INIT_METHOD || method == CLASS_INIT_METHOD) {
		type = (Type *)node_new (TYPE_NODE,
					 "name", "void",
					 NULL);
	} else {
		type = pop_type();
	}
	
	/* a complicated and ugly test to figure out if we have
	   the wrong number of types for a signal */
	if((method == SIGNAL_FIRST_METHOD ||
	    method == SIGNAL_LAST_METHOD) &&
	   g_list_length(gtktypes) != g_list_length(funcargs) &&
	   !(g_list_length(funcargs) == 1 &&
	     g_list_length(gtktypes) == 2 &&
	     strcmp(gtktypes->next->data, "NONE")==0)) {
		error_print(GOB_WARN, line_no,
			    _("The number of GTK arguments and "
			      "function arguments for a signal "
			      "don't seem to match"));
	}
	if(g_list_length(gtktypes) > 2) {
		GList *li;
		for(li = gtktypes->next; li; li = li->next) {
			if(strcmp(li->data, "NONE")==0) {
				error_print(GOB_ERROR, line_no,
					    _("NONE can only appear in an "
					      "argument list by itself"));
			}
		}
	}
	if(cbuf) {
		char *p;
		c_cbuf = p = cbuf->str;
		while(p && *p && (*p==' ' || *p=='\t' || *p=='\n' || *p=='\r'))
			p++;
		if(!p || !*p)
			c_cbuf = NULL;
	} else
		c_cbuf = NULL;

	node = node_new (METHOD_NODE,
			 "scope", scope,
			 "method", method,
			 "mtype:steal", type,
			 "otype:steal", oid,
			 "gtktypes:steal", gtktypes,
			 "flags:steal", flags,
			 "id:steal", id,
			 "args:steal", funcargs,
			 "funcattrs:steal", funcattrs,
			 "onerror:steal", onerror,
			 "defreturn:steal", defreturn,
			 "cbuf:steal", c_cbuf,
			 "line_no", line_no,
			 "ccode_line", ccode_line,
			 "vararg", vararg,
			 "unique_id", method_unique_id++,
			 NULL);

	last_added_method = (Method *)node;

	if(cbuf)
		g_string_free(cbuf,
			      /*only free segment if we haven't passed it
				above */
			      c_cbuf?FALSE:TRUE);
	gtktypes = NULL;
	funcargs = NULL;

	funcattrs = NULL;
	onerror = NULL;
	defreturn = NULL;

	class_nodes = g_list_append(class_nodes, node);
}

static void
free_all_global_state(void)
{
	g_free(funcattrs);
	funcattrs = NULL;
	g_free(onerror);
	onerror = NULL;
	g_free(defreturn);
	defreturn = NULL;

	g_free(chunk_size);
	chunk_size = NULL;
	
	g_list_foreach(gtktypes, (GFunc)g_free, NULL);
	g_list_free(gtktypes);
	gtktypes = NULL;

	node_list_free (funcargs);
	funcargs = NULL;
}

static void
push_funcarg(char *name, char *postfix)
{
	Node *node;
	Type *type = pop_type();

	type->postfix = postfix;
	
	node = node_new (FUNCARG_NODE,
			 "atype:steal", type,
			 "name:steal", name,
			 "checks:steal", checks,
			 NULL);
	checks = NULL;
	
	funcargs = g_list_append(funcargs, node);
}

static void
push_init_arg(char *name, int is_class)
{
	Node *node;
	Node *type;
	char *tn;
	
	if(is_class)
		tn = g_strconcat(((Class *)class)->otype,":Class",NULL);
	else
		tn = g_strdup(((Class *)class)->otype);

	type = node_new (TYPE_NODE,
			 "name:steal", tn,
			 "pointer", "*",
			 NULL);
	node = node_new (FUNCARG_NODE,
			 "atype:steal", (Type *)type,
			 "name:steal", name,
			 NULL);
	funcargs = g_list_prepend(funcargs, node);
}

static void
push_self(char *id, gboolean constant)
{
	Node *node;
	Node *type;
	GList *ch = NULL;
	type = node_new (TYPE_NODE,
			 "name", ((Class *)class)->otype,
			 "pointer", constant ? "const *" : "*",
			 NULL);
	ch = g_list_append (ch, node_new (CHECK_NODE,
					  "chtype", NULL_CHECK,
					  NULL));
	ch = g_list_append (ch, node_new (CHECK_NODE,
					  "chtype", TYPE_CHECK,
					  NULL));
	node = node_new (FUNCARG_NODE,
			 "atype:steal", (Type *)type,
			 "name:steal", id,
			 "checks:steal", ch,
			 NULL);
	funcargs = g_list_prepend(funcargs, node);
}

static Variable *
find_var_or_die(const char *id, int line)
{
	GList *li;

	for(li = class_nodes; li != NULL; li = li->next) {
		Variable *var;
		Node *node = li->data;
		if(node->type != VARIABLE_NODE)
			continue;
		var = li->data;
		if(strcmp(var->id, id)==0)
			return var;
	}

	error_printf(GOB_ERROR, line, _("Variable %s not defined here"), id);

	g_assert_not_reached();
	return NULL;
}

static gboolean
set_attr_value(char *type, char *val)
{
	if(strcmp(type, "attr")==0) {
		if(!funcattrs) {
			funcattrs = val;
			return TRUE;
		} else
			return FALSE;
	} else if(strcmp(type, "onerror")==0) {
		if(!onerror) {
			onerror = val;
			return TRUE;
		} else
			return FALSE;
	} else if(strcmp(type, "defreturn")==0) {
		if(!defreturn) {
			defreturn = val;
			return TRUE;
		} else
			return FALSE;
	}
	return FALSE;
}

static void
export_accessors (const char *var_name,
		  gboolean do_get,
		  int get_lineno,
		  gboolean do_set,
		  int set_lineno,
		  Type *type,
		  const char *gtktype,
		  int lineno)
{	
	Type *the_type;

	if (type != NULL)
		the_type = (Type *)node_copy ((Node *)type);
	else
		the_type = get_tree_type (gtktype, TRUE);

	if (the_type == NULL) {
		error_print (GOB_ERROR, line_no,
			     _("Cannot determine type of property or argument"));
		return;
	}

	if (do_get) {
		char *get_id = g_strdup_printf ("get_%s", var_name);
		GString *get_cbuf = g_string_new (NULL);
		Node *node1 = node_new (TYPE_NODE,
					"name", the_type->name,
					"pointer", the_type->pointer,
					"postfix", the_type->postfix,
					NULL);
		Node *node3 = node_new (TYPE_NODE,
					"name", class->class.otype,
					"pointer", "*",
					NULL);

		g_string_sprintf (get_cbuf,
				  "\t%s%s val; "
				  "g_object_get (G_OBJECT (self), \"%s\", "
				  "&val, NULL); "
				  "return val;\n",
				  the_type->name, 
				  the_type->pointer ? the_type->pointer : "",
				  var_name);
		
		typestack = g_list_prepend (typestack, node1);
		typestack = g_list_prepend (typestack, node3);
		
		push_funcarg ("self", FALSE);
		
		push_function (PUBLIC_SCOPE, REGULAR_METHOD, NULL,
			       get_id, get_cbuf, get_lineno,
			       lineno, FALSE, NULL);
	}
	
	if (do_set) {
		char *set_id = g_strdup_printf ("set_%s", var_name);
		GString *set_cbuf = g_string_new (NULL);
		Node *node1 = node_new (TYPE_NODE, 
					"name", the_type->name,
					"pointer", the_type->pointer,
					"postfix", the_type->postfix,
					NULL);
		Node *node2 = node_new (TYPE_NODE, 
					"name", "void",
					NULL);
		Node *node3 = node_new (TYPE_NODE, 
					"name", class->class.otype,
					"pointer", "*",
					NULL);

		g_string_sprintf (set_cbuf,
				  "\tg_object_set (G_OBJECT (self), "
				  "\"%s\", val, NULL);\n",
				  var_name);

		typestack = g_list_prepend (typestack, node2);
		typestack = g_list_prepend (typestack, node1);
		typestack = g_list_prepend (typestack, node3);
		
		push_funcarg ("self", FALSE);
		push_funcarg ("val", FALSE);
	
		typestack = g_list_prepend (typestack, node2);
		push_function (PUBLIC_SCOPE, REGULAR_METHOD, NULL,
			       set_id, set_cbuf, set_lineno,
			       lineno, FALSE, NULL);
	}

	node_free ((Node *)the_type);
}

static char *
get_prop_enum_flag_cast (Property *prop)
{
	char *tmp, *ret;
	if (prop->extra_gtktype == NULL ||
	/* HACK!  just in case someone made this
	 * work with 2.0.0 by using the TYPE
	 * macro directly */
	    ((strstr (prop->extra_gtktype, "_TYPE_") != NULL ||
	      strstr (prop->extra_gtktype, "TYPE_") == prop->extra_gtktype) &&
	     strchr (prop->extra_gtktype, ':') == NULL)) {
		if (prop->ptype != NULL)
			return get_type (prop->ptype, TRUE);
		else
			return g_strdup ("");
	}
	tmp = remove_sep (prop->extra_gtktype);
	ret = g_strdup_printf ("(%s) ", tmp);
	g_free (tmp);
	return ret;
}

static void
add_construct_glade (char * file, char * root, char * domain)
{
	Node *var;
	Type * type;
	
	type = (Type *)node_new (TYPE_NODE,
				 "name", "GladeXML",
				 "pointer", "*",
				 NULL);
	initializer = g_strdup_printf("\t{\n"
				      "\tGtkWidget * root;\n"
				      "\t%%1$s->_priv->_glade_xml = glade_xml_new(%s, %s, %s);\n"
				      "\troot = glade_xml_get_widget(%%1$s->_priv->_glade_xml, %s);\n"
				      "\tgtk_widget_show(root);\n"
				      "\tgtk_container_add(GTK_CONTAINER(%%1$s), root);\n"
				      "\tglade_xml_signal_autoconnect_full(%%1$s->_priv->_glade_xml, (GladeXMLConnectFunc)___glade_xml_connect_foreach, (gpointer)%%1$s);\n"
				      "}\n", file, root, domain ? domain : "NULL", root);
	
	var = node_new (VARIABLE_NODE,
			"scope", PRIVATE_SCOPE,
			"vtype:steal", type,
			"glade_widget", FALSE,
			"id:steal", "_glade_xml",
			"destructor_unref", FALSE,
			"destructor", "g_object_unref", 
			"destructor_simple", TRUE,
			"initializer", initializer,
			"initializer_simple", FALSE,
			NULL);
	class_nodes = g_list_prepend(class_nodes, var);
}

static void
property_link_and_export (Node *node)
{
	Property *prop = (Property *)node;

	if (prop->link) {
		const char *root;
		char *get = NULL, *set = NULL;
		Variable *var;

		if (prop->set != NULL ||
		    prop->get != NULL) {	
			error_print (GOB_ERROR, prop->line_no,
				     _("Property linking requested, but "
				       "getters and setters exist"));
		}

		var = find_var_or_die (prop->name, prop->line_no);
		if(var->scope == PRIVATE_SCOPE) {
			root = "self->_priv";
		} else if (var->scope == CLASS_SCOPE) {
			root = "SELF_GET_CLASS(self)";
			if (no_self_alias)
				error_print (GOB_ERROR, prop->line_no,
					     _("Self aliases needed when autolinking to a classwide member"));
		} else {
			root = "self";
		}

		if (strcmp (prop->gtktype, "STRING") == 0) {
			set = g_strdup_printf("{ char *old = %s->%s; "
					      "%s->%s = g_value_dup_string (VAL); g_free (old); }",
					      root, prop->name,
					      root, prop->name);
			get = g_strdup_printf("g_value_set_string (VAL, %s->%s);",
					      root, prop->name);
		} else if (strcmp (prop->gtktype, "OBJECT") == 0) {
			char *cast;
			if (prop->extra_gtktype != NULL) {
				cast = remove_sep (prop->extra_gtktype);
			} else {
				cast = g_strdup ("void");
			}
			set = g_strdup_printf("{ GObject *___old = (GObject *)%s->%s; "
					      "%s->%s = (%s *)g_value_dup_object (VAL); "
					      "if (___old != NULL) { "
					        "g_object_unref (G_OBJECT (___old)); "
					      "} "
					      "}",
					      root, prop->name,
					      root, prop->name,
					      cast);
			get = g_strdup_printf ("g_value_set_object (VAL, "
					       "(gpointer)%s->%s);",
					       root, prop->name);
			g_free (cast);
		} else if (strcmp (prop->gtktype, "BOXED") == 0) {
			char *type = make_me_type (prop->extra_gtktype,
						   "G_TYPE_BOXED");
			if (prop->extra_gtktype == NULL) {
				error_print (GOB_ERROR, prop->line_no,
					     _("Property linking requested for BOXED, but "
					       "boxed_type not set"));
			}
			set = g_strdup_printf("{ gpointer ___old = (gpointer)%s->%s; "
					      "gpointer ___new = (gpointer)g_value_get_boxed (VAL); "
					      "if (___new != ___old) { "
					        "if (___old != NULL) g_boxed_free (%s, ___old); "
					        "if (___new != NULL) %s->%s = g_boxed_copy (%s, ___new); "
					        "else %s->%s = NULL;"
					      "} "
					      "}",
					      root, prop->name,
					      type,
					      root, prop->name,
					      type,
					      root, prop->name);
			get = g_strdup_printf("g_value_set_boxed (VAL, %s->%s);",
					      root, prop->name);
			g_free (type);
		} else {
			char *set_func;
			char *get_func;
			const char *getcast = "";
			const char *setcast = "";
			char *to_free = NULL;
			set_func = g_strdup_printf ("g_value_set_%s", prop->gtktype);
			g_strdown (set_func);
			get_func = g_strdup_printf ("g_value_get_%s", prop->gtktype);
			g_strdown (get_func);

			if (for_cpp) {
				if (strcmp (prop->gtktype, "FLAGS") == 0) {
					setcast = "(guint) ";
					getcast = to_free =
						get_prop_enum_flag_cast (prop);
				} else if (strcmp (prop->gtktype, "ENUM") == 0) {
					setcast = "(gint) ";
					getcast = to_free =
						get_prop_enum_flag_cast (prop);
                               }  else if (strcmp (prop->gtktype, "POINTER") == 0) {
                                       setcast = "(gpointer) ";
                                       getcast = g_strdup_printf ("(%s%s) ",
								  prop->ptype->name,
								  prop->ptype->pointer ? prop->ptype->pointer : "");
				}
			}

			set = g_strdup_printf("%s->%s = %s%s (VAL);",
					      root, prop->name,
					      getcast,
					      get_func);
			get = g_strdup_printf("%s (VAL, %s%s->%s);",
					      set_func,
					      setcast,	
					      root, prop->name);

			g_free (get_func);
			g_free (set_func);
			g_free (to_free);
		}

		node_set (node,
			  "get:steal", get,
			  "get_line", prop->line_no,
			  "set:steal", set,
			  "set_line", prop->line_no,
			  NULL);
	}

	if (prop->export) {
		export_accessors (prop->name,
				  prop->get != NULL, prop->get_line,
				  prop->set != NULL,  prop->set_line,
				  prop->ptype,
				  prop->gtktype,
				  prop->line_no);
	} 
}


static char *
debool (char *s)
{
	if (strcmp (s, "BOOL") == 0) {
		error_print (GOB_WARN, line_no,
			    _("BOOL type is deprecated, please use BOOLEAN"));
		g_free (s);
		return g_strdup ("BOOLEAN");
	} else {
		return s;
	}
}

static void
ensure_property (void)
{
	if (property == NULL)
		property = (Property *)node_new (PROPERTY_NODE, NULL);
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 187 of yacc.c.  */
#line 865 "parse.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 878 "parse.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  24
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   640

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  197
/* YYNRULES -- Number of states.  */
#define YYNSTATES  417

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    65,     2,     2,     2,     2,     2,     2,
      56,    57,    62,     2,    60,    66,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    58,
      64,    59,    63,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    54,    61,    55,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    10,    13,    15,    17,    19,    21,
      23,    25,    27,    29,    32,    35,    38,    41,    43,    45,
      47,    49,    54,    58,    64,    65,    70,    76,    82,    88,
      95,   103,   110,   118,   121,   123,   125,   128,   132,   134,
     136,   138,   140,   142,   144,   146,   148,   151,   155,   158,
     162,   165,   168,   170,   172,   174,   175,   181,   188,   201,
     211,   218,   222,   223,   235,   244,   250,   254,   255,   259,
     261,   263,   268,   270,   272,   276,   280,   284,   288,   292,
     296,   300,   304,   308,   312,   316,   320,   324,   328,   332,
     336,   340,   342,   348,   350,   354,   355,   359,   361,   364,
     366,   368,   370,   373,   376,   379,   383,   387,   390,   393,
     396,   398,   401,   403,   406,   408,   410,   412,   414,   416,
     418,   420,   422,   424,   426,   428,   430,   432,   435,   438,
     442,   445,   447,   451,   455,   458,   460,   465,   469,   471,
     474,   476,   487,   499,   509,   519,   528,   540,   549,   555,
     558,   563,   570,   571,   573,   576,   578,   580,   583,   586,
     590,   595,   600,   602,   606,   608,   612,   614,   617,   621,
     628,   636,   639,   641,   643,   646,   649,   653,   657,   661,
     665,   673,   682,   686,   688,   692,   694,   702,   711,   715,
     717,   725,   734,   738,   740,   742,   745,   747
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      68,     0,    -1,    70,    71,    70,    -1,    71,    70,    -1,
      70,    71,    -1,    71,    -1,    24,    -1,    25,    -1,    28,
      -1,    26,    -1,    27,    -1,    29,    -1,    30,    -1,    70,
      69,    -1,    70,   112,    -1,    70,   115,    -1,    70,   117,
      -1,    69,    -1,   112,    -1,   115,    -1,   117,    -1,    72,
      54,    74,    55,    -1,    72,    54,    55,    -1,     3,    21,
       4,    21,    73,    -1,    -1,    56,    19,    57,    73,    -1,
      56,    19,    19,    57,    73,    -1,    56,    19,    21,    57,
      73,    -1,    56,    19,    20,    57,    73,    -1,    56,    19,
      31,    31,    57,    73,    -1,    56,    19,    31,    31,    31,
      57,    73,    -1,    56,    19,    19,    31,    57,    73,    -1,
      56,    19,    19,    31,    31,    57,    73,    -1,    74,    75,
      -1,    75,    -1,   103,    -1,    19,   103,    -1,    19,    21,
     103,    -1,    80,    -1,    81,    -1,    83,    -1,    58,    -1,
      32,    -1,    33,    -1,    34,    -1,    35,    -1,    19,    19,
      -1,    19,    54,    24,    -1,    59,   119,    -1,    59,    54,
      24,    -1,    77,    78,    -1,    78,    77,    -1,    78,    -1,
      77,    -1,    19,    -1,    -1,    76,    92,    19,    79,    58,
      -1,    76,    92,    19,    22,    79,    58,    -1,    37,    90,
      89,    19,    82,    19,    54,    24,    19,    54,    24,    58,
      -1,    37,    90,    89,    19,    82,    19,    54,    24,    58,
      -1,    37,    90,    89,    19,    82,    19,    -1,    56,    19,
      57,    -1,    -1,    36,    19,    19,    84,    19,    54,    24,
      19,    54,    24,    58,    -1,    36,    19,    19,    84,    19,
      54,    24,    58,    -1,    36,    19,    19,    84,    58,    -1,
      56,    85,    57,    -1,    -1,    85,    60,    88,    -1,    88,
      -1,    31,    -1,    19,    56,    31,    57,    -1,   119,    -1,
      86,    -1,    41,    59,    86,    -1,    42,    59,    86,    -1,
      43,    59,   119,    -1,    44,    59,   119,    -1,    45,    59,
      87,    -1,    47,    59,    91,    -1,    48,    59,    92,    -1,
      49,    59,    21,    -1,    49,    59,    19,    -1,    50,    59,
      21,    -1,    50,    59,    19,    -1,    51,    59,    21,    -1,
      51,    59,    19,    -1,    52,    59,    21,    -1,    52,    59,
      19,    -1,    53,    59,    21,    -1,    53,    59,    19,    -1,
      19,    -1,    19,    56,    19,    92,    57,    -1,    19,    -1,
      56,    91,    57,    -1,    -1,    19,    61,    91,    -1,    19,
      -1,    93,    97,    -1,    93,    -1,    94,    -1,    19,    -1,
       5,    19,    -1,    19,     5,    -1,    96,    19,    -1,     5,
      96,    19,    -1,    96,    19,     5,    -1,    95,    94,    -1,
      21,    94,    -1,     5,    94,    -1,    21,    -1,    21,     5,
      -1,    95,    -1,    95,     5,    -1,     6,    -1,    18,    -1,
      14,    -1,    15,    -1,    13,    -1,    16,    -1,    17,    -1,
      11,    -1,    12,    -1,     7,    -1,     8,    -1,     9,    -1,
      62,    -1,    62,     5,    -1,    62,    97,    -1,    62,     5,
      97,    -1,    19,   100,    -1,   100,    -1,    76,    19,   100,
      -1,    19,    76,   100,    -1,    76,   100,    -1,    98,    -1,
      19,    56,   101,    57,    -1,   101,    60,    19,    -1,    19,
      -1,    54,    24,    -1,    58,    -1,    39,    90,    99,    92,
      19,    56,   106,    57,   104,   102,    -1,    76,    39,    90,
      98,    92,    19,    56,   106,    57,   104,   102,    -1,    38,
      76,    92,    19,    56,   106,    57,   104,   102,    -1,    76,
      38,    92,    19,    56,   106,    57,   104,   102,    -1,    38,
      92,    19,    56,   106,    57,   104,   102,    -1,    40,    56,
      21,    57,    92,    19,    56,   106,    57,   104,   102,    -1,
      76,    92,    19,    56,   106,    57,   104,   102,    -1,    19,
      56,    19,    57,   102,    -1,    19,   105,    -1,    19,   105,
      19,   105,    -1,    19,   105,    19,   105,    19,   105,    -1,
      -1,   119,    -1,    54,    24,    -1,     6,    -1,    19,    -1,
      19,     5,    -1,     5,    19,    -1,    19,    60,   107,    -1,
      19,     5,    60,   107,    -1,     5,    19,    60,   107,    -1,
     107,    -1,   108,    60,    10,    -1,   108,    -1,   108,    60,
     109,    -1,   109,    -1,    92,    19,    -1,    92,    19,    22,
      -1,    92,    19,    56,    19,   110,    57,    -1,    92,    19,
      22,    56,    19,   110,    57,    -1,   110,   111,    -1,   111,
      -1,    19,    -1,    63,   119,    -1,    64,   119,    -1,    63,
      59,   119,    -1,    64,    59,   119,    -1,    59,    59,   119,
      -1,    65,    59,   119,    -1,     9,    19,    54,   113,    55,
      21,    58,    -1,     9,    19,    54,   113,    60,    55,    21,
      58,    -1,   113,    60,   114,    -1,   114,    -1,    19,    59,
     119,    -1,    19,    -1,    47,    19,    54,   116,    55,    21,
      58,    -1,    47,    19,    54,   116,    60,    55,    21,    58,
      -1,   116,    60,    19,    -1,    19,    -1,    46,    19,    54,
     118,    55,    21,    58,    -1,    46,    19,    54,   118,    60,
      55,    21,    58,    -1,   118,    60,    19,    -1,    19,    -1,
      20,    -1,    66,    20,    -1,    23,    -1,    19,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   699,   699,   700,   701,   702,   705,   714,   723,   732,
     741,   750,   759,   770,   771,   772,   773,   774,   775,   776,
     777,   780,   785,   792,   809,   810,   818,   830,   839,   851,
     860,   869,   878,   889,   890,   893,   894,   903,   915,   916,
     917,   918,   921,   922,   923,   924,   927,   947,   971,   975,
     983,   984,   985,   986,   987,   995,  1001,  1004,  1009,  1077,
    1131,  1220,  1228,  1233,  1281,  1317,  1333,  1334,  1337,  1338,
    1341,  1342,  1354,  1355,  1358,  1364,  1370,  1376,  1382,  1388,
    1394,  1401,  1407,  1413,  1419,  1425,  1431,  1437,  1443,  1449,
    1455,  1461,  1486,  1495,  1501,  1502,  1505,  1508,  1514,  1521,
    1530,  1533,  1536,  1540,  1544,  1548,  1553,  1561,  1565,  1570,
    1574,  1577,  1581,  1584,  1589,  1590,  1591,  1592,  1593,  1594,
    1595,  1596,  1597,  1600,  1601,  1602,  1605,  1606,  1607,  1611,
    1618,  1630,  1636,  1648,  1660,  1663,  1669,  1674,  1677,  1682,
    1683,  1687,  1710,  1733,  1756,  1779,  1797,  1810,  1820,  1860,
    1872,  1892,  1923,  1930,  1931,  1937,  1938,  1949,  1960,  1971,
    1981,  1991,  2001,  2004,  2005,  2008,  2009,  2012,  2015,  2018,
    2026,  2036,  2037,  2040,  2057,  2064,  2071,  2078,  2085,  2092,
    2101,  2110,  2121,  2122,  2125,  2145,  2155,  2164,  2175,  2178,
    2183,  2192,  2203,  2206,  2212,  2213,  2217,  2218
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLASS", "FROM", "CONST", "VOID",
  "STRUCT", "UNION", "ENUM", "THREEDOTS", "SIGNED", "UNSIGNED", "LONG",
  "SHORT", "INT", "FLOAT", "DOUBLE", "CHAR", "TOKEN", "NUMBER",
  "TYPETOKEN", "ARRAY_DIM", "SINGLE_CHAR", "CCODE", "ADCODE", "HTCODE",
  "PHCODE", "HCODE", "ACODE", "ATCODE", "STRING", "PUBLIC", "PRIVATE",
  "PROTECTED", "CLASSWIDE", "PROPERTY", "ARGUMENT", "VIRTUAL", "SIGNAL",
  "OVERRIDE", "NICK", "BLURB", "MAXIMUM", "MINIMUM", "DEFAULT_VALUE",
  "ERROR", "FLAGS", "TYPE", "FLAGS_TYPE", "ENUM_TYPE", "PARAM_TYPE",
  "BOXED_TYPE", "OBJECT_TYPE", "'{'", "'}'", "'('", "')'", "';'", "'='",
  "','", "'|'", "'*'", "'>'", "'<'", "'!'", "'-'", "$accept", "prog",
  "ccode", "ccodes", "class", "classdec", "classflags", "classcode",
  "thing", "scope", "destructor", "initializer", "varoptions", "variable",
  "argument", "export", "property", "param_spec", "param_spec_list",
  "string", "anyval", "param_spec_value", "argtype", "flags", "flaglist",
  "type", "specifier_list", "spec_list", "specifier", "strunionenum",
  "pointer", "simplesigtype", "fullsigtype", "sigtype", "tokenlist",
  "codenocode", "method", "methodmods", "retcode", "funcargs", "arglist",
  "arglist1", "arg", "checklist", "check", "enumcode", "enumvals",
  "enumval", "flagcode", "flagvals", "errorcode", "errorvals", "numtok", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   123,   125,    40,    41,    59,    61,
      44,   124,    42,    62,    60,    33,    45
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    67,    68,    68,    68,    68,    69,    69,    69,    69,
      69,    69,    69,    70,    70,    70,    70,    70,    70,    70,
      70,    71,    71,    72,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    74,    74,    75,    75,    75,    75,    75,
      75,    75,    76,    76,    76,    76,    77,    77,    78,    78,
      79,    79,    79,    79,    79,    79,    80,    80,    81,    81,
      81,    82,    82,    83,    83,    83,    84,    84,    85,    85,
      86,    86,    87,    87,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    89,    89,    90,    90,    91,    91,    92,    92,
      93,    93,    93,    93,    93,    93,    93,    94,    94,    94,
      94,    94,    94,    94,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    96,    96,    96,    97,    97,    97,    97,
      98,    98,    99,    99,    99,    99,   100,   101,   101,   102,
     102,   103,   103,   103,   103,   103,   103,   103,   103,   104,
     104,   104,   104,   105,   105,   106,   106,   106,   106,   106,
     106,   106,   106,   107,   107,   108,   108,   109,   109,   109,
     109,   110,   110,   111,   111,   111,   111,   111,   111,   111,
     112,   112,   113,   113,   114,   114,   115,   115,   116,   116,
     117,   117,   118,   118,   119,   119,   119,   119
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     1,     1,     1,
       1,     4,     3,     5,     0,     4,     5,     5,     5,     6,
       7,     6,     7,     2,     1,     1,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     2,     3,
       2,     2,     1,     1,     1,     0,     5,     6,    12,     9,
       6,     3,     0,    11,     8,     5,     3,     0,     3,     1,
       1,     4,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     5,     1,     3,     0,     3,     1,     2,     1,
       1,     1,     2,     2,     2,     3,     3,     2,     2,     2,
       1,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     3,
       2,     1,     3,     3,     2,     1,     4,     3,     1,     2,
       1,    10,    11,     9,     9,     8,    11,     8,     5,     2,
       4,     6,     0,     1,     2,     1,     1,     2,     2,     3,
       4,     4,     1,     3,     1,     3,     1,     2,     3,     6,
       7,     2,     1,     1,     2,     2,     3,     3,     3,     3,
       7,     8,     3,     1,     3,     1,     7,     8,     3,     1,
       7,     8,     3,     1,     1,     2,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     6,     7,     9,    10,     8,    11,    12,
       0,     0,     0,    17,     0,     5,     0,    18,    19,    20,
       0,     0,     0,     0,     1,    13,     4,    14,    15,    16,
       3,     0,     0,     0,     0,     0,     2,     0,    42,    43,
      44,    45,     0,    95,     0,    95,     0,    22,    41,     0,
      34,     0,    38,    39,    40,    35,    24,   185,     0,   183,
     193,     0,   189,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,   114,   123,   124,   125,   121,   122,   118,
     116,   117,   119,   120,   115,   101,   110,     0,     0,    99,
     100,   112,     0,     0,     0,    21,    33,     0,    95,     0,
       0,    23,     0,     0,     0,     0,     0,     0,     0,    37,
       0,     0,    67,    97,     0,    93,     0,     0,   102,   109,
       0,   103,   111,   108,     0,     0,   126,    98,   113,   107,
     104,     0,     0,   135,     0,   131,     0,     0,     0,    55,
       0,   197,   194,   196,     0,   184,     0,     0,   182,     0,
     192,     0,     0,   188,     0,     0,     0,     0,     0,     0,
      94,     0,    62,   105,     0,     0,   127,   128,   106,     0,
       0,     0,   130,     0,   134,     0,     0,     0,     0,     0,
      54,    55,     0,     0,    53,    52,     0,     0,     0,     0,
       0,    24,   195,   180,     0,   190,     0,   186,     0,     0,
     140,   148,    91,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    69,     0,    65,    96,
       0,     0,     0,     0,     0,   114,   101,     0,     0,   162,
     164,   166,   129,   138,     0,   133,   132,     0,     0,     0,
       0,    46,     0,     0,     0,     0,    48,    50,     0,    51,
      56,     0,    24,    24,    24,     0,    25,   181,   191,   187,
     139,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    66,     0,     0,     0,     0,    60,     0,
     102,   103,     0,   167,   152,     0,   136,     0,     0,     0,
       0,     0,    47,    57,   152,    49,     0,    24,    26,    28,
      27,     0,    24,     0,    70,    74,    75,    76,    77,   197,
      73,    78,    72,    79,    80,    82,    81,    84,    83,    86,
      85,    88,    87,    90,    89,    68,     0,    92,    61,     0,
     152,     0,     0,   159,   168,     0,     0,     0,   163,   165,
     137,     0,     0,   152,     0,     0,    24,    31,    24,    29,
       0,     0,    64,     0,     0,   161,   160,     0,     0,     0,
     149,   153,   145,   152,     0,     0,     0,   147,    32,    30,
       0,     0,     0,    59,   143,     0,   173,     0,     0,     0,
       0,     0,   172,   154,     0,     0,   152,   144,   152,    71,
       0,     0,     0,     0,     0,   174,     0,   175,     0,   169,
     171,   150,   141,     0,     0,    63,     0,   170,   178,   176,
     177,   179,     0,   146,   142,    58,   151
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    12,    13,    14,    15,    16,   101,    49,    50,    51,
     184,   185,   186,    52,    53,   222,    54,   158,   215,   305,
     311,   216,   116,    71,   114,   227,    89,    90,    91,    92,
     127,   133,   134,   135,   234,   201,    55,   337,   360,   228,
     229,   230,   231,   381,   382,    17,    58,    59,    18,    63,
      19,    61,   361
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -326
static const yytype_int16 yypact[] =
{
     145,    13,    77,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
     108,   196,   146,  -326,   145,   205,   168,  -326,  -326,  -326,
     264,   173,   221,   232,  -326,  -326,   205,  -326,  -326,  -326,
     205,   161,   259,   276,   283,   301,   205,   222,  -326,  -326,
    -326,  -326,   309,   273,   327,   273,   281,  -326,  -326,   170,
    -326,   292,  -326,  -326,  -326,  -326,   291,   290,   -27,  -326,
    -326,    40,  -326,   127,   294,   250,   332,   292,  -326,   333,
     334,   335,   375,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,   350,   443,   392,   337,   295,
    -326,   457,   339,   239,   357,  -326,  -326,   392,   273,   366,
     376,  -326,    27,   381,    71,   391,    95,   398,   124,  -326,
     372,   417,   390,   389,   394,   396,   434,   471,  -326,  -326,
     446,  -326,   471,  -326,   447,   411,     4,  -326,   471,  -326,
     474,   231,   461,  -326,   392,  -326,   424,   472,   475,   122,
     192,  -326,  -326,  -326,   470,  -326,   435,   476,  -326,   437,
    -326,   477,   438,  -326,   478,   163,   444,   274,     0,   334,
    -326,   482,   448,  -326,   449,   409,   295,  -326,  -326,   450,
     483,   484,  -326,     6,  -326,   488,   392,   452,     6,   392,
      64,    38,   409,    32,   451,   490,   453,    80,   455,   456,
     485,   291,  -326,  -326,   459,  -326,   460,  -326,   462,   491,
    -326,  -326,  -326,   463,   464,   465,   466,   467,   468,   469,
     473,   479,   480,   481,   486,   -30,  -326,   487,  -326,  -326,
     392,   495,   500,   409,   426,   489,    11,   502,   492,  -326,
     493,  -326,  -326,  -326,   126,  -326,  -326,   494,   510,   409,
     511,  -326,   507,   496,   498,   509,  -326,  -326,    64,  -326,
    -326,   187,   291,   291,   291,   189,  -326,  -326,  -326,  -326,
    -326,    85,    85,    27,    27,    18,   334,   392,    -6,   219,
     226,   260,   293,  -326,   274,   512,   499,   501,   497,   503,
     128,   179,   392,   100,   515,   358,  -326,   516,   409,   505,
     506,   508,  -326,  -326,   515,  -326,   513,   291,  -326,  -326,
    -326,   514,   291,   517,  -326,  -326,  -326,  -326,  -326,   517,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,    12,  -326,  -326,   518,
     515,   392,   392,  -326,   519,   524,    69,   163,  -326,  -326,
    -326,   520,   409,   515,   409,   163,   291,  -326,   291,  -326,
     521,   522,  -326,    61,   163,  -326,  -326,   525,    66,   523,
     529,  -326,  -326,   515,   526,   163,   527,  -326,  -326,  -326,
     528,   533,   532,  -326,  -326,    66,  -326,   530,    83,   101,
     531,    75,  -326,  -326,    69,   163,   515,  -326,   515,  -326,
     504,   535,    88,    27,    27,  -326,    27,  -326,    27,  -326,
    -326,   546,  -326,   163,   163,  -326,   534,  -326,  -326,  -326,
    -326,  -326,    69,  -326,  -326,  -326,  -326
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -326,  -326,    -4,   102,   552,  -326,  -189,  -326,   538,   -26,
     352,   383,   387,  -326,  -326,  -326,  -326,  -326,  -326,     5,
    -326,   298,  -326,   -24,  -154,   -43,  -326,   -69,  -326,   -66,
     -57,   431,  -326,   -96,  -326,  -325,   -23,  -287,  -297,  -178,
    -259,  -326,   289,   203,  -216,   154,  -326,   536,   212,  -326,
     223,  -326,  -102
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -159
static const yytype_int16 yytable[] =
{
     145,    88,   256,   119,   244,   219,   120,   345,    99,   166,
      25,    67,   362,   315,    68,   316,   281,   123,    87,   217,
     367,    93,   129,   333,   111,   169,    25,   273,   103,   374,
     274,   351,    25,   104,    20,   172,   174,   309,   142,    67,
     387,   143,   109,   354,   124,   279,   141,   142,   119,   304,
     143,   141,   142,   119,   137,   143,   365,   180,   218,   119,
     402,   290,   170,   298,   299,   300,   126,   132,  -156,   167,
     352,   282,   355,   356,   138,   235,   385,   236,   413,   414,
     372,   246,   172,   241,   144,   376,   245,   401,   141,   142,
      57,   175,   143,   144,   376,   105,    21,   183,   144,   403,
     106,   404,   141,   142,   303,   171,   143,   376,   347,   232,
     341,   251,   313,   349,   150,   416,   304,    30,   242,   373,
     141,   142,   334,   359,   143,   377,   147,    22,    36,   378,
     379,   380,   399,   238,   377,   144,   240,   252,   378,   379,
     380,   180,   394,   153,   181,   407,    24,   377,     1,   144,
     151,   378,   379,   380,     2,   119,   335,   368,   120,   369,
     396,   307,   308,   312,   364,   400,   366,   144,    27,     3,
       4,     5,     6,     7,     8,     9,   400,   276,   182,   154,
      37,   183,   107,   286,    27,  -158,   287,   108,   331,    37,
      27,    10,    11,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    38,    39,    40,    41,    42,    43,    44,    45,
      46,   187,   188,   189,     2,    23,    47,   199,   296,    48,
     301,   200,    31,   190,   314,    95,    28,    33,    48,     3,
       4,     5,     6,     7,     8,     9,  -157,    29,   317,   332,
     318,    64,    28,    65,   297,   319,   302,   320,    28,   191,
     169,    10,    11,    29,    38,    39,    40,    41,   131,    29,
      44,    45,    46,    38,    39,    40,    41,   306,    32,    64,
     310,    38,    39,    40,    41,    34,   395,   397,    66,   321,
      56,   322,    38,    39,    40,    41,    35,   170,    44,    45,
      46,   408,   409,   202,   410,    57,   411,    72,    73,    74,
      75,    76,    60,    77,    78,    79,    80,    81,    82,    83,
      84,    85,   323,    86,   324,   203,   204,   205,   206,   207,
      62,   208,   209,   210,   211,   212,   213,   214,    69,    70,
      97,    98,    72,    73,    74,    75,    76,    94,    77,    78,
      79,    80,    81,    82,    83,    84,    85,   100,    86,   102,
      66,   110,   112,   113,   115,   121,   125,   126,   130,    38,
      39,    40,    41,    72,    73,    74,    75,    76,   338,    77,
      78,    79,    80,    81,    82,    83,    84,    85,   136,    86,
     117,    73,    74,    75,    76,   139,    77,    78,    79,    80,
      81,    82,    83,    84,   118,   140,    86,    72,    73,    74,
      75,    76,   146,    77,    78,    79,    80,    81,    82,    83,
      84,    85,   149,    86,   224,   225,    74,    75,    76,   152,
      77,    78,    79,    80,    81,    82,    83,    84,   226,   155,
      86,   117,    73,    74,    75,    76,   156,    77,    78,    79,
      80,    81,    82,    83,    84,   280,   157,    86,   122,    73,
     159,   160,   161,   162,    77,    78,    79,    80,    81,    82,
      83,    84,   128,    73,    86,   163,   164,   165,    77,    78,
      79,    80,    81,    82,    83,    84,   117,    73,    86,   168,
     173,   176,    77,    78,    79,    80,    81,    82,    83,    84,
     192,   177,    86,   193,   178,   195,   197,   194,   196,   198,
     182,   220,   233,   169,   221,   223,   170,   237,   239,   248,
     183,   250,   253,   254,   277,   260,   255,   257,   258,   278,
     259,   283,   261,   262,   263,   264,   265,   266,   267,   289,
     291,   292,   268,   295,   336,   340,   326,   249,   269,   270,
     271,   275,   353,   358,   375,   272,  -155,   383,   384,   284,
     288,   329,   370,   285,   293,   294,   327,   390,   328,   406,
     330,   342,   405,   343,   344,   412,    26,   247,   243,   179,
     346,   348,   325,   350,   339,   357,   371,   363,   392,     0,
       0,     0,     0,   386,   388,   389,   391,    96,     0,   393,
     398,     0,   415,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     148
};

static const yytype_int16 yycheck[] =
{
     102,    44,   191,    72,   182,   159,    72,   294,    51,     5,
      14,    37,   337,    19,    37,    21,     5,    86,    44,    19,
     345,    45,    91,   282,    67,    19,    30,    57,    55,   354,
      60,    19,    36,    60,    21,   131,   132,    19,    20,    65,
     365,    23,    65,   330,    87,   223,    19,    20,   117,    31,
      23,    19,    20,   122,    97,    23,   343,    19,    58,   128,
     385,   239,    56,   252,   253,   254,    62,    93,    57,   126,
      58,    60,   331,   332,    98,   171,   363,   173,   403,   404,
      19,   183,   178,    19,    66,    19,    54,   384,    19,    20,
      19,   134,    23,    66,    19,    55,    19,    59,    66,   386,
      60,   388,    19,    20,    19,   131,    23,    19,   297,   166,
     288,    31,   266,   302,    19,   412,    31,    15,    54,    58,
      19,    20,    22,    54,    23,    59,    55,    19,    26,    63,
      64,    65,    57,   176,    59,    66,   179,    57,    63,    64,
      65,    19,    59,    19,    22,    57,     0,    59,     3,    66,
      55,    63,    64,    65,     9,   224,    56,   346,   224,   348,
      59,   263,   264,   265,   342,   381,   344,    66,    14,    24,
      25,    26,    27,    28,    29,    30,   392,   220,    56,    55,
      19,    59,    55,    57,    30,    57,    60,    60,    60,    19,
      36,    46,    47,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    19,    20,    21,     9,    19,    55,    54,    31,    58,
      31,    58,    54,    31,   267,    55,    14,    54,    58,    24,
      25,    26,    27,    28,    29,    30,    57,    14,    19,    60,
      21,    19,    30,    21,    57,    19,    57,    21,    36,    57,
      19,    46,    47,    30,    32,    33,    34,    35,    19,    36,
      38,    39,    40,    32,    33,    34,    35,   262,     4,    19,
     265,    32,    33,    34,    35,    54,   378,   379,    56,    19,
      21,    21,    32,    33,    34,    35,    54,    56,    38,    39,
      40,   393,   394,    19,   396,    19,   398,     5,     6,     7,
       8,     9,    19,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    19,    21,    21,    41,    42,    43,    44,    45,
      19,    47,    48,    49,    50,    51,    52,    53,    19,    56,
      38,    39,     5,     6,     7,     8,     9,    56,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    56,    21,    59,
      56,    19,    19,    19,    19,     5,    19,    62,    19,    32,
      33,    34,    35,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    21,    21,
       5,     6,     7,     8,     9,    19,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    19,    21,     5,     6,     7,
       8,     9,    21,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    21,    21,     5,     6,     7,     8,     9,    21,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    57,
      21,     5,     6,     7,     8,     9,    19,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    56,    21,     5,     6,
      61,    57,    56,    19,    11,    12,    13,    14,    15,    16,
      17,    18,     5,     6,    21,    19,    19,    56,    11,    12,
      13,    14,    15,    16,    17,    18,     5,     6,    21,     5,
      19,    57,    11,    12,    13,    14,    15,    16,    17,    18,
      20,    19,    21,    58,    19,    58,    58,    21,    21,    21,
      56,    19,    19,    19,    56,    56,    56,    19,    56,    19,
      59,    58,    57,    57,    19,    24,    31,    58,    58,    19,
      58,    19,    59,    59,    59,    59,    59,    59,    59,    19,
      19,    24,    59,    24,    19,    19,    24,   185,    59,    59,
      59,    54,    24,    19,    19,    59,    57,    24,    19,    57,
      56,    54,    31,    60,    58,    57,    57,    24,    57,    24,
      57,    56,    58,    57,    56,    19,    14,   184,   181,   138,
      57,    57,   274,    56,   285,    56,    54,    57,   375,    -1,
      -1,    -1,    -1,    57,    57,    57,    54,    49,    -1,    59,
      59,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     9,    24,    25,    26,    27,    28,    29,    30,
      46,    47,    68,    69,    70,    71,    72,   112,   115,   117,
      21,    19,    19,    19,     0,    69,    71,   112,   115,   117,
      70,    54,     4,    54,    54,    54,    70,    19,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    55,    58,    74,
      75,    76,    80,    81,    83,   103,    21,    19,   113,   114,
      19,   118,    19,   116,    19,    21,    56,    76,   103,    19,
      56,    90,     5,     6,     7,     8,     9,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    21,    76,    92,    93,
      94,    95,    96,    90,    56,    55,    75,    38,    39,    92,
      56,    73,    59,    55,    60,    55,    60,    55,    60,   103,
      19,    92,    19,    19,    91,    19,    89,     5,    19,    94,
      96,     5,     5,    94,    92,    19,    62,    97,     5,    94,
      19,    19,    76,    98,    99,   100,    21,    92,    90,    19,
      19,    19,    20,    23,    66,   119,    21,    55,   114,    21,
      19,    55,    21,    19,    55,    57,    19,    56,    84,    61,
      57,    56,    19,    19,    19,    56,     5,    97,     5,    19,
      56,    76,   100,    19,   100,    92,    57,    19,    19,    98,
      19,    22,    56,    59,    77,    78,    79,    19,    20,    21,
      31,    57,    20,    58,    21,    58,    21,    58,    21,    54,
      58,   102,    19,    41,    42,    43,    44,    45,    47,    48,
      49,    50,    51,    52,    53,    85,    88,    19,    58,    91,
      19,    56,    82,    56,     5,     6,    19,    92,   106,   107,
     108,   109,    97,    19,   101,   100,   100,    19,    92,    56,
      92,    19,    54,    79,   106,    54,   119,    78,    19,    77,
      58,    31,    57,    57,    57,    31,    73,    58,    58,    58,
      24,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    57,    60,    54,    92,    19,    19,   106,
      19,     5,    60,    19,    57,    60,    57,    60,    56,    19,
     106,    19,    24,    58,    57,    24,    31,    57,    73,    73,
      73,    31,    57,    19,    31,    86,    86,   119,   119,    19,
      86,    87,   119,    91,    92,    19,    21,    19,    21,    19,
      21,    19,    21,    19,    21,    88,    24,    57,    57,    54,
      57,    60,    60,   107,    22,    56,    19,   104,    10,   109,
      19,   106,    56,    57,    56,   104,    57,    73,    57,    73,
      56,    19,    58,    24,   104,   107,   107,    56,    19,    54,
     105,   119,   102,    57,   106,   104,   106,   102,    73,    73,
      31,    54,    19,    58,   102,    19,    19,    59,    63,    64,
      65,   110,   111,    24,    19,   104,    57,   102,    57,    57,
      24,    54,   110,    59,    59,   119,    59,   119,    59,    57,
     111,   105,   102,   104,   104,    58,    24,    57,   119,   119,
     119,   119,    19,   102,   102,    58,   105
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 699 "parse.y"
    { ; }
    break;

  case 3:
#line 700 "parse.y"
    { ; }
    break;

  case 4:
#line 701 "parse.y"
    { ; }
    break;

  case 5:
#line 702 "parse.y"
    { ; }
    break;

  case 6:
#line 705 "parse.y"
    {
			Node *node = node_new (CCODE_NODE,
					       "cctype", C_CCODE,
					       "cbuf:steal", ((yyvsp[(1) - (1)].cbuf))->str,
					       "line_no", ccode_line,
					       NULL);
			nodes = g_list_append(nodes,node);
			g_string_free((yyvsp[(1) - (1)].cbuf),FALSE);
					}
    break;

  case 7:
#line 714 "parse.y"
    {
			Node *node = node_new (CCODE_NODE,
					       "cctype", AD_CCODE,
					       "cbuf:steal", ((yyvsp[(1) - (1)].cbuf))->str,
					       "line_no", ccode_line,
					       NULL);
			nodes = g_list_append(nodes,node);
			g_string_free((yyvsp[(1) - (1)].cbuf),FALSE);
					}
    break;

  case 8:
#line 723 "parse.y"
    {
			Node *node = node_new (CCODE_NODE,
					       "cctype", H_CCODE,
					       "cbuf:steal", ((yyvsp[(1) - (1)].cbuf))->str,
					       "line_no", ccode_line,
					       NULL);
			nodes = g_list_append(nodes,node);
			g_string_free((yyvsp[(1) - (1)].cbuf),FALSE);
					}
    break;

  case 9:
#line 732 "parse.y"
    {
			Node *node = node_new (CCODE_NODE,
					       "cctype", HT_CCODE,
					       "cbuf:steal", ((yyvsp[(1) - (1)].cbuf))->str,
					       "line_no", ccode_line,
					       NULL);
			nodes = g_list_append(nodes,node);
			g_string_free((yyvsp[(1) - (1)].cbuf),FALSE);
					}
    break;

  case 10:
#line 741 "parse.y"
    {
			Node *node = node_new (CCODE_NODE,
					       "cctype", PH_CCODE,
					       "cbuf:steal", ((yyvsp[(1) - (1)].cbuf))->str,
					       "line_no", ccode_line,
					       NULL);
			nodes = g_list_append(nodes,node);
			g_string_free((yyvsp[(1) - (1)].cbuf),FALSE);
					}
    break;

  case 11:
#line 750 "parse.y"
    {
			Node *node = node_new (CCODE_NODE,
					       "cctype", A_CCODE,
					       "cbuf:steal", ((yyvsp[(1) - (1)].cbuf))->str,
					       "line_no", ccode_line,
					       NULL);
			nodes = g_list_append(nodes,node);
			g_string_free((yyvsp[(1) - (1)].cbuf),FALSE);
					}
    break;

  case 12:
#line 759 "parse.y"
    {
			Node *node = node_new (CCODE_NODE,
					       "cctype", AT_CCODE,
					       "cbuf:steal", ((yyvsp[(1) - (1)].cbuf))->str,
					       "line_no", ccode_line,
					       NULL);
			nodes = g_list_append(nodes,node);
			g_string_free((yyvsp[(1) - (1)].cbuf),FALSE);
					}
    break;

  case 13:
#line 770 "parse.y"
    { ; }
    break;

  case 14:
#line 771 "parse.y"
    { ; }
    break;

  case 15:
#line 772 "parse.y"
    { ; }
    break;

  case 16:
#line 773 "parse.y"
    { ; }
    break;

  case 17:
#line 774 "parse.y"
    { ; }
    break;

  case 18:
#line 775 "parse.y"
    { ; }
    break;

  case 19:
#line 776 "parse.y"
    { ; }
    break;

  case 20:
#line 777 "parse.y"
    { ; }
    break;

  case 21:
#line 780 "parse.y"
    {
			((Class *)class)->nodes = class_nodes;
			class_nodes = NULL;
			nodes = g_list_append(nodes,class);
						}
    break;

  case 22:
#line 785 "parse.y"
    {
			((Class *)class)->nodes = NULL;
			class_nodes = NULL;
			nodes = g_list_append(nodes,class);
						}
    break;

  case 23:
#line 792 "parse.y"
    {
			class = node_new (CLASS_NODE,
					  "otype:steal", (yyvsp[(2) - (5)].id),
					  "ptype:steal", (yyvsp[(4) - (5)].id),
					  "bonobo_object_class:steal", bonobo_object_class,
					  "glade_xml", glade_xml,
					  "interfaces:steal", interfaces,
					  "chunk_size:steal", chunk_size,
					  "abstract", abstract,
					  NULL);
			bonobo_object_class = NULL;
			glade_xml = FALSE;
			chunk_size = NULL;
			interfaces = NULL;
						}
    break;

  case 25:
#line 810 "parse.y"
    {
			if(strcmp((yyvsp[(2) - (4)].id),"abstract") == 0) {
				abstract = TRUE;
			} else {
				yyerror(_("parse error"));
				YYERROR;
			}
		}
    break;

  case 26:
#line 818 "parse.y"
    {
			if(strcmp((yyvsp[(2) - (5)].id),"chunks") == 0) {
				g_free (chunk_size);
				chunk_size = g_strdup((yyvsp[(3) - (5)].id));
			} else if(strcmp((yyvsp[(2) - (5)].id),"BonoboObject") == 0) {
				g_free (bonobo_object_class);
				bonobo_object_class = g_strdup((yyvsp[(3) - (5)].id));
			} else {
				yyerror(_("parse error"));
				YYERROR;
			}
		}
    break;

  case 27:
#line 830 "parse.y"
    {
			if (strcmp ((yyvsp[(2) - (5)].id), "interface") == 0) {
				interfaces = g_list_append (interfaces,
							    g_strdup ((yyvsp[(3) - (5)].id)));
			} else {
				yyerror(_("parse error"));
				YYERROR;
			}
		}
    break;

  case 28:
#line 839 "parse.y"
    {
			if(strcmp((yyvsp[(2) - (5)].id),"chunks") == 0) {
				g_free (chunk_size);
				if(atoi((yyvsp[(3) - (5)].id)) != 0)
					chunk_size = g_strdup((yyvsp[(3) - (5)].id));
				else
					chunk_size = NULL;
			} else {
				yyerror(_("parse error"));
				YYERROR;
			}
		}
    break;

  case 29:
#line 851 "parse.y"
    {
			if (strcmp ((yyvsp[(2) - (6)].id), "GladeXML") == 0) {
				glade_xml = TRUE;
				add_construct_glade((yyvsp[(3) - (6)].id), (yyvsp[(4) - (6)].id), NULL);
			} else {
				yyerror(_("parse error"));
				YYERROR;
			}
		}
    break;

  case 30:
#line 860 "parse.y"
    {
			if (strcmp ((yyvsp[(2) - (7)].id), "GladeXML") == 0) {
				glade_xml = TRUE;
				add_construct_glade((yyvsp[(3) - (7)].id), (yyvsp[(4) - (7)].id), (yyvsp[(5) - (7)].id));
			} else {
				yyerror(_("parse error"));
				YYERROR;
			}
		}
    break;

  case 31:
#line 869 "parse.y"
    {
			if (strcmp ((yyvsp[(2) - (6)].id), "GladeXML") == 0) {
				glade_xml = TRUE;
				add_construct_glade((yyvsp[(3) - (6)].id), (yyvsp[(4) - (6)].id), NULL);
			} else {
				yyerror(_("parse error"));
				YYERROR;
			}
		}
    break;

  case 32:
#line 878 "parse.y"
    {
			if (strcmp ((yyvsp[(2) - (7)].id), "GladeXML") == 0) {
				glade_xml = TRUE;
				add_construct_glade((yyvsp[(3) - (7)].id), (yyvsp[(4) - (7)].id), (yyvsp[(5) - (7)].id));
			} else {
				yyerror(_("parse error"));
				YYERROR;
			}
		}
    break;

  case 33:
#line 889 "parse.y"
    { ; }
    break;

  case 34:
#line 890 "parse.y"
    { ; }
    break;

  case 35:
#line 893 "parse.y"
    { ; }
    break;

  case 36:
#line 894 "parse.y"
    {
			if (strcmp ((yyvsp[(1) - (2)].id), "BonoboObject") != 0) {
				g_free ((yyvsp[(1) - (2)].id));
				yyerror (_("parse error"));
				YYERROR;
			}
			g_free ((yyvsp[(1) - (2)].id));
			last_added_method->bonobo_object_func = TRUE;
						}
    break;

  case 37:
#line 903 "parse.y"
    {
			if (strcmp ((yyvsp[(1) - (3)].id), "interface") != 0) {
				g_free ((yyvsp[(1) - (3)].id));
				g_free ((yyvsp[(2) - (3)].id));
				yyerror (_("parse error"));
				YYERROR;
			}
			g_free ((yyvsp[(1) - (3)].id));
			node_set ((Node *)last_added_method,
				  "interface:steal", (yyvsp[(2) - (3)].id),
				  NULL);
						}
    break;

  case 38:
#line 915 "parse.y"
    { ; }
    break;

  case 39:
#line 916 "parse.y"
    { ; }
    break;

  case 40:
#line 917 "parse.y"
    { ; }
    break;

  case 41:
#line 918 "parse.y"
    { ; }
    break;

  case 42:
#line 921 "parse.y"
    { the_scope = PUBLIC_SCOPE; }
    break;

  case 43:
#line 922 "parse.y"
    { the_scope = PRIVATE_SCOPE; }
    break;

  case 44:
#line 923 "parse.y"
    { the_scope = PROTECTED_SCOPE; }
    break;

  case 45:
#line 924 "parse.y"
    { the_scope = CLASS_SCOPE; }
    break;

  case 46:
#line 927 "parse.y"
    {
			if (strcmp ((yyvsp[(1) - (2)].id), "destroywith") == 0) {
				g_free ((yyvsp[(1) - (2)].id));
				destructor_unref = FALSE;
				destructor = (yyvsp[(2) - (2)].id);
				destructor_line = line_no;
				destructor_simple = TRUE;
			} else if (strcmp ((yyvsp[(1) - (2)].id), "unrefwith") == 0) {
				g_free ((yyvsp[(1) - (2)].id));
				destructor_unref = TRUE;
				destructor = (yyvsp[(2) - (2)].id);
				destructor_line = line_no;
				destructor_simple = TRUE;
			} else {
				g_free ((yyvsp[(1) - (2)].id));
				g_free ((yyvsp[(2) - (2)].id));
				yyerror (_("parse error"));
				YYERROR;
			}
				}
    break;

  case 47:
#line 947 "parse.y"
    {
			if (strcmp ((yyvsp[(1) - (3)].id), "destroy") == 0) {
				g_free((yyvsp[(1) - (3)].id));
				destructor_unref = FALSE;
				destructor = ((yyvsp[(3) - (3)].cbuf))->str;
				g_string_free((yyvsp[(3) - (3)].cbuf), FALSE);
				destructor_line = ccode_line;
				destructor_simple = FALSE;
			} else if (strcmp ((yyvsp[(1) - (3)].id), "unref") == 0) {
				g_free ((yyvsp[(1) - (3)].id));
				destructor_unref = TRUE;
				destructor = ((yyvsp[(3) - (3)].cbuf))->str;
				g_string_free ((yyvsp[(3) - (3)].cbuf), FALSE);
				destructor_line = ccode_line;
				destructor_simple = FALSE;
			} else {
				g_free ((yyvsp[(1) - (3)].id));
				g_string_free ((yyvsp[(3) - (3)].cbuf), TRUE);
				yyerror (_("parse error"));
				YYERROR;
			}
					}
    break;

  case 48:
#line 971 "parse.y"
    {
			initializer = (yyvsp[(2) - (2)].id);
			initializer_line = ccode_line;
				}
    break;

  case 49:
#line 975 "parse.y"
    {
			initializer = ((yyvsp[(3) - (3)].cbuf))->str;
			initializer_line = ccode_line;
			g_string_free((yyvsp[(3) - (3)].cbuf), FALSE);
				}
    break;

  case 50:
#line 983 "parse.y"
    { ; }
    break;

  case 51:
#line 984 "parse.y"
    { ; }
    break;

  case 52:
#line 985 "parse.y"
    { destructor = NULL; }
    break;

  case 53:
#line 986 "parse.y"
    { initializer = NULL; }
    break;

  case 54:
#line 987 "parse.y"
    {
			if (strcmp ((yyvsp[(1) - (1)].id), "GladeXML") == 0) {
				glade_widget = TRUE;
			} else {
				yyerror(_("parse error"));
				YYERROR;
			}
					}
    break;

  case 55:
#line 995 "parse.y"
    {
			destructor = NULL;
			initializer = NULL;
					}
    break;

  case 56:
#line 1001 "parse.y"
    {
			push_variable((yyvsp[(3) - (5)].id), the_scope,(yyvsp[(1) - (5)].line), NULL);
						}
    break;

  case 57:
#line 1004 "parse.y"
    {
			push_variable((yyvsp[(3) - (6)].id), the_scope, (yyvsp[(1) - (6)].line), (yyvsp[(4) - (6)].id));
						}
    break;

  case 58:
#line 1009 "parse.y"
    {
			Node *node = NULL;
			if(strcmp((yyvsp[(6) - (12)].id),"get")==0 &&
			   strcmp((yyvsp[(9) - (12)].id),"set")==0) {
				Type *type = pop_type();
				g_free ((yyvsp[(6) - (12)].id)); 
				g_free ((yyvsp[(9) - (12)].id));
				node = node_new (ARGUMENT_NODE,
						 "gtktype:steal", (yyvsp[(3) - (12)].id),
						 "atype:steal", type,
						 "flags:steal", (yyvsp[(2) - (12)].list),
						 "name:steal", (yyvsp[(4) - (12)].id),
						 "get:steal", ((yyvsp[(8) - (12)].cbuf))->str,
						 "get_line", (yyvsp[(7) - (12)].line),
						 "set:steal", ((yyvsp[(11) - (12)].cbuf))->str,
						 "set_line", (yyvsp[(10) - (12)].line),
						 "line_no", (yyvsp[(1) - (12)].line),
						 NULL);

				class_nodes = g_list_append(class_nodes,node);

				g_string_free ((yyvsp[(8) - (12)].cbuf), FALSE);
				g_string_free ((yyvsp[(11) - (12)].cbuf), FALSE);

			} else if(strcmp((yyvsp[(6) - (12)].id),"set")==0 &&
				strcmp((yyvsp[(9) - (12)].id),"get")==0) {
				Type *type = pop_type();
				g_free ((yyvsp[(6) - (12)].id)); 
				g_free ((yyvsp[(9) - (12)].id));
				node = node_new (ARGUMENT_NODE,
						 "gtktype:steal", (yyvsp[(3) - (12)].id),
						 "atype:steal", type,
						 "flags:steal", (yyvsp[(2) - (12)].list),
						 "name:steal", (yyvsp[(4) - (12)].id),
						 "get:steal", ((yyvsp[(11) - (12)].cbuf))->str,
						 "get_line", (yyvsp[(10) - (12)].line),
						 "set:steal", ((yyvsp[(8) - (12)].cbuf))->str,
						 "set_line", (yyvsp[(7) - (12)].line),
						 "line_no", (yyvsp[(1) - (12)].line),
						 NULL);
				g_string_free ((yyvsp[(11) - (12)].cbuf), FALSE);
				g_string_free ((yyvsp[(8) - (12)].cbuf), FALSE);
				class_nodes = g_list_append(class_nodes,node);
			} else {
				g_free ((yyvsp[(3) - (12)].id)); 
				g_free ((yyvsp[(4) - (12)].id));
				g_free ((yyvsp[(6) - (12)].id)); 
				g_free ((yyvsp[(9) - (12)].id));
				g_list_foreach ((yyvsp[(2) - (12)].list), (GFunc)g_free, NULL);
				g_list_free ((yyvsp[(2) - (12)].list));
				g_string_free ((yyvsp[(11) - (12)].cbuf), TRUE);
				g_string_free ((yyvsp[(8) - (12)].cbuf), TRUE);
				yyerror (_("parse error"));
				YYERROR;
			}

			if ((yyvsp[(5) - (12)].id) != NULL) {
				Argument *arg = (Argument *)node;
				export_accessors (arg->name,
						  arg->get != NULL, arg->get_line,
						  arg->set != NULL, arg->set_line,
						  arg->atype,
						  arg->gtktype,
						  arg->line_no);
				g_free ((yyvsp[(5) - (12)].id));
			} 

						}
    break;

  case 59:
#line 1077 "parse.y"
    {
			Node *node = NULL;
			if(strcmp((yyvsp[(6) - (9)].id), "get") == 0) {
				Type *type = pop_type();
				g_free ((yyvsp[(6) - (9)].id));
				node = node_new (ARGUMENT_NODE,
						 "gtktype:steal", (yyvsp[(3) - (9)].id),
						 "atype:steal", type,
						 "flags:steal", (yyvsp[(2) - (9)].list),
						 "name:steal", (yyvsp[(4) - (9)].id),
						 "get:steal", ((yyvsp[(8) - (9)].cbuf))->str,
						 "get_line", (yyvsp[(7) - (9)].line),
						 "line_no", (yyvsp[(1) - (9)].line),
						 NULL);

				g_string_free ((yyvsp[(8) - (9)].cbuf), FALSE);
				class_nodes = g_list_append(class_nodes, node);
			} else if(strcmp((yyvsp[(6) - (9)].id), "set") == 0) {
				Type *type = pop_type();
				g_free ((yyvsp[(6) - (9)].id));
				node = node_new (ARGUMENT_NODE,
						 "gtktype:steal", (yyvsp[(3) - (9)].id),
						 "atype:steal", type,
						 "flags:steal", (yyvsp[(2) - (9)].list),
						 "name:steal", (yyvsp[(4) - (9)].id),
						 "set:steal", ((yyvsp[(8) - (9)].cbuf))->str,
						 "set_line", (yyvsp[(7) - (9)].line),
						 "line_no", (yyvsp[(1) - (9)].line),
						 NULL);

				g_string_free ((yyvsp[(8) - (9)].cbuf), FALSE);
				class_nodes = g_list_append (class_nodes, node);
			} else {
				g_free ((yyvsp[(6) - (9)].id)); 
				g_free ((yyvsp[(3) - (9)].id));
				g_free ((yyvsp[(4) - (9)].id));
				g_list_foreach ((yyvsp[(2) - (9)].list), (GFunc)g_free, NULL);
				g_list_free ((yyvsp[(2) - (9)].list));
				g_string_free ((yyvsp[(8) - (9)].cbuf), TRUE);
				yyerror(_("parse error"));
				YYERROR;
			}

			if ((yyvsp[(5) - (9)].id) != NULL) {
				Argument *arg = (Argument *)node;
				export_accessors (arg->name,
						  arg->get != NULL, arg->get_line,
						  arg->set != NULL, arg->set_line,
						  arg->atype,
						  arg->gtktype,
						  arg->line_no);
				g_free ((yyvsp[(5) - (9)].id));
			} 
						}
    break;

  case 60:
#line 1131 "parse.y"
    {
			Node *node;
			char *get, *set = NULL;
			Variable *var;
			Type *type;
			const char *root;
			
			if(strcmp((yyvsp[(6) - (6)].id), "link")!=0 &&
			   strcmp((yyvsp[(6) - (6)].id), "stringlink")!=0 && 
			   strcmp((yyvsp[(6) - (6)].id), "objectlink")!=0) {
				g_free((yyvsp[(6) - (6)].id)); 
				g_free((yyvsp[(3) - (6)].id));
				g_free((yyvsp[(4) - (6)].id));
				g_list_foreach((yyvsp[(2) - (6)].list),(GFunc)g_free,NULL);
				g_list_free((yyvsp[(2) - (6)].list));
				yyerror(_("parse error"));
				YYERROR;
			}

			type = pop_type();

			var = find_var_or_die((yyvsp[(4) - (6)].id), (yyvsp[(1) - (6)].line));
			if(var->scope == PRIVATE_SCOPE) {
				root = "self->_priv";
			} else if(var->scope == CLASS_SCOPE) {
				root = "SELF_GET_CLASS(self)";
				if(no_self_alias)
					error_print(GOB_ERROR, (yyvsp[(1) - (6)].line),
						    _("Self aliases needed when autolinking to a classwide member"));
			} else {
				root = "self";
			}

			if(strcmp((yyvsp[(6) - (6)].id), "link")==0) {
				set = g_strdup_printf("%s->%s = ARG;",
						      root, (yyvsp[(4) - (6)].id));
			} else if(strcmp((yyvsp[(6) - (6)].id), "stringlink")==0) {
				set = g_strdup_printf("g_free (%s->%s); "
						      "%s->%s = g_strdup (ARG);",
						      root, (yyvsp[(4) - (6)].id),
						      root, (yyvsp[(4) - (6)].id));
			} else if(strcmp((yyvsp[(6) - (6)].id), "objectlink")==0) {
				set = g_strdup_printf(
				  "if (ARG != NULL) "
				   "g_object_ref (G_OBJECT (ARG)); "
				  "if (%s->%s != NULL) "
				   "g_object_unref (G_OBJECT (%s->%s)); "
				  "%s->%s = ARG;",
				  root, (yyvsp[(4) - (6)].id),
				  root, (yyvsp[(4) - (6)].id),
				  root, (yyvsp[(4) - (6)].id));
			} else {
				g_assert_not_reached();
			}

			get = g_strdup_printf("ARG = %s->%s;", root, (yyvsp[(4) - (6)].id));
  
			g_free ((yyvsp[(6) - (6)].id));

			if (type == NULL)
				type = (Type *)node_copy ((Node *)var->vtype);

			node = node_new (ARGUMENT_NODE,
					 "gtktype:steal", (yyvsp[(3) - (6)].id),
					 "atype:steal", type,
					 "flags:steal", (yyvsp[(2) - (6)].list),
					 "name:steal", (yyvsp[(4) - (6)].id),
					 "get:steal", get,
					 "get_line", (yyvsp[(1) - (6)].line),
					 "set:steal", set,
					 "set_line", (yyvsp[(1) - (6)].line),
					 "line_no", (yyvsp[(1) - (6)].line),
					 NULL);

			if ((yyvsp[(5) - (6)].id) != NULL) {
				Argument *arg = (Argument *)node;
				export_accessors (arg->name,
						  arg->get != NULL, arg->get_line,
						  arg->set != NULL, arg->set_line,
						  arg->atype,
						  arg->gtktype,
						  arg->line_no);
				g_free ((yyvsp[(5) - (6)].id));
			} 

			class_nodes = g_list_append (class_nodes, node);
						}
    break;

  case 61:
#line 1220 "parse.y"
    {
			if (strcmp ((yyvsp[(2) - (3)].id), "export")!=0) {
				g_free ((yyvsp[(2) - (3)].id)); 
				yyerror (_("parse error"));
				YYERROR;
			}
			(yyval.id) = (yyvsp[(2) - (3)].id);
						}
    break;

  case 62:
#line 1228 "parse.y"
    {
			(yyval.id) = NULL;
						}
    break;

  case 63:
#line 1233 "parse.y"
    {
			ensure_property ();
			node_set ((Node *)property,
				  "line_no", (yyvsp[(1) - (11)].line),
				  "gtktype:steal", debool ((yyvsp[(2) - (11)].id)),
				  "name:steal", (yyvsp[(3) - (11)].id),
				  NULL);
			if (strcmp ((yyvsp[(5) - (11)].id), "get") == 0 &&
			    strcmp ((yyvsp[(8) - (11)].id), "set") == 0) {
				node_set ((Node *)property,
					  "get:steal", ((yyvsp[(7) - (11)].cbuf))->str,
					  "get_line", (yyvsp[(6) - (11)].line),
					  "set:steal", ((yyvsp[(10) - (11)].cbuf))->str,
					  "set_line", (yyvsp[(9) - (11)].line),
					  NULL);
				g_string_free ((yyvsp[(7) - (11)].cbuf), FALSE);
				g_string_free ((yyvsp[(10) - (11)].cbuf), FALSE);
				g_free ((yyvsp[(5) - (11)].id)); 
				g_free ((yyvsp[(8) - (11)].id));
			} else if (strcmp ((yyvsp[(5) - (11)].id), "set") == 0 &&
				   strcmp ((yyvsp[(8) - (11)].id), "get") == 0) {
				node_set ((Node *)property,
					  "get:steal", ((yyvsp[(10) - (11)].cbuf))->str,
					  "get_line", (yyvsp[(9) - (11)].line),
					  "set:steal", ((yyvsp[(7) - (11)].cbuf))->str,
					  "set_line", (yyvsp[(6) - (11)].line),
					  NULL);
				g_string_free ((yyvsp[(7) - (11)].cbuf), FALSE);
				g_string_free ((yyvsp[(10) - (11)].cbuf), FALSE);
				g_free ((yyvsp[(5) - (11)].id)); 
				g_free ((yyvsp[(8) - (11)].id));
			} else {
				g_string_free ((yyvsp[(7) - (11)].cbuf), TRUE);
				g_string_free ((yyvsp[(10) - (11)].cbuf), TRUE);
				g_free ((yyvsp[(5) - (11)].id)); 
				g_free ((yyvsp[(8) - (11)].id));
				node_free ((Node *)property);
				property = NULL;
				yyerror (_("parse error"));
				YYERROR;
			}
			property_link_and_export ((Node *)property);
			if (property != NULL) {
				class_nodes = g_list_append (class_nodes,
							     property);
				property = NULL;
			}
		}
    break;

  case 64:
#line 1281 "parse.y"
    {
			ensure_property ();
			node_set ((Node *)property,
				  "line_no", (yyvsp[(1) - (8)].line),
				  "gtktype:steal", debool ((yyvsp[(2) - (8)].id)),
				  "name:steal", (yyvsp[(3) - (8)].id),
				  NULL);
			if (strcmp ((yyvsp[(5) - (8)].id), "get") == 0) {
				node_set ((Node *)property,
					  "get:steal", ((yyvsp[(7) - (8)].cbuf))->str,
					  "get_line", (yyvsp[(6) - (8)].line),
					  NULL);
				g_string_free ((yyvsp[(7) - (8)].cbuf), FALSE);
				g_free ((yyvsp[(5) - (8)].id)); 
			} else if (strcmp ((yyvsp[(5) - (8)].id), "set") == 0) {
				node_set ((Node *)property,
					  "set:steal", ((yyvsp[(7) - (8)].cbuf))->str,
					  "set_line", (yyvsp[(6) - (8)].line),
					  NULL);
				g_string_free ((yyvsp[(7) - (8)].cbuf), FALSE);
				g_free ((yyvsp[(5) - (8)].id)); 
			} else {
				g_string_free ((yyvsp[(7) - (8)].cbuf), TRUE);
				g_free ((yyvsp[(5) - (8)].id)); 
				node_free ((Node *)property);
				property = NULL;
				yyerror (_("parse error"));
				YYERROR;
			}
			property_link_and_export ((Node *)property);
			if (property != NULL) {
				class_nodes = g_list_append (class_nodes,
							     property);
				property = NULL;
			}
		}
    break;

  case 65:
#line 1317 "parse.y"
    {
			ensure_property ();
			node_set ((Node *)property,
				  "line_no", (yyvsp[(1) - (5)].line),
				  "gtktype:steal", debool ((yyvsp[(2) - (5)].id)),
				  "name:steal", (yyvsp[(3) - (5)].id),
				  NULL);
			property_link_and_export ((Node *)property);
			if (property != NULL) {
				class_nodes = g_list_append (class_nodes,
							     property);
				property = NULL;
			}
		}
    break;

  case 66:
#line 1333 "parse.y"
    { ; }
    break;

  case 67:
#line 1334 "parse.y"
    { ; }
    break;

  case 68:
#line 1337 "parse.y"
    { ; }
    break;

  case 69:
#line 1338 "parse.y"
    { ; }
    break;

  case 70:
#line 1341 "parse.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 71:
#line 1342 "parse.y"
    {
			if (strcmp ((yyvsp[(1) - (4)].id), "_") != 0) {
				g_free ((yyvsp[(1) - (4)].id));
				yyerror(_("parse error"));
				YYERROR;
			}
			g_free ((yyvsp[(1) - (4)].id));
			(yyval.id) = g_strconcat ("_(", (yyvsp[(3) - (4)].id), ")", NULL);
			g_free ((yyvsp[(3) - (4)].id));
		}
    break;

  case 72:
#line 1354 "parse.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 73:
#line 1355 "parse.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 74:
#line 1358 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "nick:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 75:
#line 1364 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "blurb:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 76:
#line 1370 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "maximum:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 77:
#line 1376 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "minimum:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 78:
#line 1382 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "default_value:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 79:
#line 1388 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "flags:steal", (yyvsp[(3) - (3)].list),
			  NULL);
		  }
    break;

  case 80:
#line 1394 "parse.y"
    {
		Type *type = pop_type ();
		ensure_property ();
		node_set ((Node *)property,
			  "ptype:steal", type,
			  NULL);
		  }
    break;

  case 81:
#line 1401 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 82:
#line 1407 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 83:
#line 1413 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 84:
#line 1419 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 85:
#line 1425 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 86:
#line 1431 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 87:
#line 1437 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 88:
#line 1443 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 89:
#line 1449 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 90:
#line 1455 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 91:
#line 1461 "parse.y"
    {
		ensure_property ();
		if (strcmp ((yyvsp[(1) - (1)].id), "override") == 0) {
			g_free((yyvsp[(1) - (1)].id));
			node_set ((Node *)property,
				  "override", TRUE,
				  NULL);
		} else if (strcmp ((yyvsp[(1) - (1)].id), "link") == 0) {
			g_free((yyvsp[(1) - (1)].id));
			node_set ((Node *)property,
				  "link", TRUE,
				  NULL);
		} else if (strcmp ((yyvsp[(1) - (1)].id), "export") == 0) {
			g_free((yyvsp[(1) - (1)].id));
			node_set ((Node *)property,
				  "export", TRUE,
				  NULL);
		} else {
			g_free((yyvsp[(1) - (1)].id));
			yyerror(_("parse error"));
			YYERROR;
		}
		  }
    break;

  case 92:
#line 1486 "parse.y"
    {
			if(strcmp((yyvsp[(3) - (5)].id),"type")!=0) {
				g_free((yyvsp[(1) - (5)].id));
				g_free((yyvsp[(3) - (5)].id));
				yyerror(_("parse error"));
				YYERROR;
			}
			(yyval.id) = debool ((yyvsp[(1) - (5)].id));
						}
    break;

  case 93:
#line 1495 "parse.y"
    {
			(yyval.id) = debool ((yyvsp[(1) - (1)].id));
			typestack = g_list_prepend(typestack,NULL);
						}
    break;

  case 94:
#line 1501 "parse.y"
    { (yyval.list) = (yyvsp[(2) - (3)].list); }
    break;

  case 95:
#line 1502 "parse.y"
    { (yyval.list) = NULL; }
    break;

  case 96:
#line 1505 "parse.y"
    {
			(yyval.list) = g_list_append((yyvsp[(3) - (3)].list),(yyvsp[(1) - (3)].id));
						}
    break;

  case 97:
#line 1508 "parse.y"
    {
			(yyval.list) = g_list_append(NULL,(yyvsp[(1) - (1)].id));
						}
    break;

  case 98:
#line 1514 "parse.y"
    {
			Node *node = node_new (TYPE_NODE, 
					       "name:steal", (yyvsp[(1) - (2)].id),
					       "pointer:steal", (yyvsp[(2) - (2)].id),
					       NULL);
			typestack = g_list_prepend(typestack,node);
							}
    break;

  case 99:
#line 1521 "parse.y"
    {
			Node *node = node_new (TYPE_NODE, 
					       "name:steal", (yyvsp[(1) - (1)].id),
					       NULL);
			typestack = g_list_prepend(typestack,node);
							}
    break;

  case 100:
#line 1530 "parse.y"
    {
			(yyval.id) = (yyvsp[(1) - (1)].id);
							}
    break;

  case 101:
#line 1533 "parse.y"
    {
			(yyval.id) = (yyvsp[(1) - (1)].id);
							}
    break;

  case 102:
#line 1536 "parse.y"
    {
			(yyval.id) = g_strconcat("const ", (yyvsp[(2) - (2)].id), NULL);
			g_free((yyvsp[(2) - (2)].id));
							}
    break;

  case 103:
#line 1540 "parse.y"
    {
			(yyval.id) = g_strconcat((yyvsp[(1) - (2)].id), " const", NULL);
			g_free((yyvsp[(1) - (2)].id));
							}
    break;

  case 104:
#line 1544 "parse.y"
    {
			(yyval.id) = g_strconcat((yyvsp[(1) - (2)].id), " ", (yyvsp[(2) - (2)].id), NULL);
			g_free((yyvsp[(2) - (2)].id));
							}
    break;

  case 105:
#line 1548 "parse.y"
    {
			(yyval.id) = g_strconcat("const ", (yyvsp[(2) - (3)].id), " ",
					     (yyvsp[(3) - (3)].id), NULL);
			g_free((yyvsp[(3) - (3)].id));
							}
    break;

  case 106:
#line 1553 "parse.y"
    {
			(yyval.id) = g_strconcat((yyvsp[(1) - (3)].id), " ",
					     (yyvsp[(2) - (3)].id), " const", NULL);
			g_free((yyvsp[(2) - (3)].id));
							}
    break;

  case 107:
#line 1561 "parse.y"
    {
			(yyval.id) = g_strconcat((yyvsp[(1) - (2)].id), " ", (yyvsp[(2) - (2)].id), NULL);
			g_free((yyvsp[(2) - (2)].id));
							}
    break;

  case 108:
#line 1565 "parse.y"
    {
			(yyval.id) = g_strconcat((yyvsp[(1) - (2)].id), " ", (yyvsp[(2) - (2)].id), NULL);
			g_free((yyvsp[(1) - (2)].id));
			g_free((yyvsp[(2) - (2)].id));
							}
    break;

  case 109:
#line 1570 "parse.y"
    {
			(yyval.id) = g_strconcat("const ", (yyvsp[(2) - (2)].id), NULL);
			g_free((yyvsp[(2) - (2)].id));
							}
    break;

  case 110:
#line 1574 "parse.y"
    {
			(yyval.id) = (yyvsp[(1) - (1)].id);
							}
    break;

  case 111:
#line 1577 "parse.y"
    {
			(yyval.id) = g_strconcat((yyvsp[(1) - (2)].id), " const", NULL);
			g_free((yyvsp[(1) - (2)].id));
							}
    break;

  case 112:
#line 1581 "parse.y"
    {
			(yyval.id) = g_strdup((yyvsp[(1) - (1)].id));
							}
    break;

  case 113:
#line 1584 "parse.y"
    {
			(yyval.id) = g_strconcat((yyvsp[(1) - (2)].id), " const", NULL);
							}
    break;

  case 114:
#line 1589 "parse.y"
    { (yyval.id) = "void"; }
    break;

  case 115:
#line 1590 "parse.y"
    { (yyval.id) = "char"; }
    break;

  case 116:
#line 1591 "parse.y"
    { (yyval.id) = "short"; }
    break;

  case 117:
#line 1592 "parse.y"
    { (yyval.id) = "int"; }
    break;

  case 118:
#line 1593 "parse.y"
    { (yyval.id) = "long"; }
    break;

  case 119:
#line 1594 "parse.y"
    { (yyval.id) = "float"; }
    break;

  case 120:
#line 1595 "parse.y"
    { (yyval.id) = "double"; }
    break;

  case 121:
#line 1596 "parse.y"
    { (yyval.id) = "signed"; }
    break;

  case 122:
#line 1597 "parse.y"
    { (yyval.id) = "unsigned"; }
    break;

  case 123:
#line 1600 "parse.y"
    { (yyval.id) = "struct"; }
    break;

  case 124:
#line 1601 "parse.y"
    { (yyval.id) = "union"; }
    break;

  case 125:
#line 1602 "parse.y"
    { (yyval.id) = "enum"; }
    break;

  case 126:
#line 1605 "parse.y"
    { (yyval.id) = g_strdup("*"); }
    break;

  case 127:
#line 1606 "parse.y"
    { (yyval.id) = g_strdup("* const"); }
    break;

  case 128:
#line 1607 "parse.y"
    {
				(yyval.id) = g_strconcat("*", (yyvsp[(2) - (2)].id), NULL);
				g_free((yyvsp[(2) - (2)].id));
					}
    break;

  case 129:
#line 1611 "parse.y"
    {
				(yyval.id) = g_strconcat("* const", (yyvsp[(3) - (3)].id), NULL);
				g_free((yyvsp[(3) - (3)].id));
					}
    break;

  case 130:
#line 1618 "parse.y"
    {
			if(strcmp((yyvsp[(1) - (2)].id), "first")==0)
				(yyval.sigtype) = SIGNAL_FIRST_METHOD;
			else if(strcmp((yyvsp[(1) - (2)].id), "last")==0)
				(yyval.sigtype) = SIGNAL_LAST_METHOD;
			else {
				yyerror(_("signal must be 'first' or 'last'"));
				g_free((yyvsp[(1) - (2)].id));
				YYERROR;
			}
			g_free((yyvsp[(1) - (2)].id));
					}
    break;

  case 131:
#line 1630 "parse.y"
    {
			(yyval.sigtype) = SIGNAL_LAST_METHOD;
					}
    break;

  case 132:
#line 1636 "parse.y"
    {
			if(strcmp((yyvsp[(2) - (3)].id),"first")==0)
				(yyval.sigtype) = SIGNAL_FIRST_METHOD;
			else if(strcmp((yyvsp[(2) - (3)].id),"last")==0)
				(yyval.sigtype) = SIGNAL_LAST_METHOD;
			else {
				yyerror(_("signal must be 'first' or 'last'"));
				g_free((yyvsp[(2) - (3)].id));
				YYERROR;
			}
			g_free((yyvsp[(2) - (3)].id));
					}
    break;

  case 133:
#line 1648 "parse.y"
    {
			if(strcmp((yyvsp[(1) - (3)].id),"first")==0)
				(yyval.sigtype) = SIGNAL_FIRST_METHOD;
			else if(strcmp((yyvsp[(1) - (3)].id),"last")==0)
				(yyval.sigtype) = SIGNAL_LAST_METHOD;
			else {
				yyerror(_("signal must be 'first' or 'last'"));
				g_free((yyvsp[(1) - (3)].id));
				YYERROR;
			}
			g_free((yyvsp[(1) - (3)].id));
					}
    break;

  case 134:
#line 1660 "parse.y"
    {
			(yyval.sigtype) = SIGNAL_LAST_METHOD;
					}
    break;

  case 135:
#line 1663 "parse.y"
    {
			/* the_scope was default thus public */
			the_scope = PUBLIC_SCOPE;
					}
    break;

  case 136:
#line 1669 "parse.y"
    {
			gtktypes = g_list_prepend(gtktypes, debool ((yyvsp[(1) - (4)].id)));
						}
    break;

  case 137:
#line 1674 "parse.y"
    {
			gtktypes = g_list_append(gtktypes, debool ((yyvsp[(3) - (3)].id)));
						}
    break;

  case 138:
#line 1677 "parse.y"
    { 
			gtktypes = g_list_append(gtktypes, debool ((yyvsp[(1) - (1)].id)));
       						}
    break;

  case 139:
#line 1682 "parse.y"
    { (yyval.cbuf) = (yyvsp[(2) - (2)].cbuf); }
    break;

  case 140:
#line 1683 "parse.y"
    { (yyval.cbuf) = NULL; }
    break;

  case 141:
#line 1687 "parse.y"
    {
			if(!has_self) {
				yyerror(_("signal without 'self' as "
					  "first parameter"));
				free_all_global_state();
				YYERROR;
			}
			if(the_scope == CLASS_SCOPE) {
				yyerror(_("a method cannot be of class scope"));
				free_all_global_state();
				YYERROR;
			}
	                if (funcattrs != NULL) {
				char *error = g_strdup_printf
					(_("function attribute macros ('%s' in this case) may not be used with signal methods"),
					 funcattrs);
	                        yyerror (error);
		                YYERROR;
		        }
			push_function(the_scope, (yyvsp[(3) - (10)].sigtype),NULL,
				      (yyvsp[(5) - (10)].id), (yyvsp[(10) - (10)].cbuf),(yyvsp[(1) - (10)].line),
				      ccode_line, vararg, (yyvsp[(2) - (10)].list));
									}
    break;

  case 142:
#line 1710 "parse.y"
    {
			if(!has_self) {
				yyerror(_("signal without 'self' as "
					  "first parameter"));
				free_all_global_state();
				YYERROR;
			}
			if(the_scope == CLASS_SCOPE) {
				yyerror(_("a method cannot be of class scope"));
				free_all_global_state();
				YYERROR;
			}
	                if (funcattrs != NULL) {
				char *error = g_strdup_printf
					(_("function attribute macros ('%s' in this case) may not be used with signal methods"),
					 funcattrs);
	                        yyerror (error);
		                YYERROR;
		        }
			push_function(the_scope, (yyvsp[(4) - (11)].sigtype), NULL,
				      (yyvsp[(6) - (11)].id), (yyvsp[(11) - (11)].cbuf), (yyvsp[(2) - (11)].line),
				      ccode_line, vararg, (yyvsp[(3) - (11)].list));
									}
    break;

  case 143:
#line 1733 "parse.y"
    {
			if(!has_self) {
				yyerror(_("virtual method without 'self' as "
					  "first parameter"));
				free_all_global_state();
				YYERROR;
			}
			if(the_scope == CLASS_SCOPE) {
				yyerror(_("a method cannot be of class scope"));
				free_all_global_state();
				YYERROR;
			}
	                if (funcattrs != NULL) {
				char *error = g_strdup_printf
					(_("function attribute macros ('%s' in this case) may not be used with virtual methods"),
					 funcattrs);
	                        yyerror (error);
		                YYERROR;
		        }
			push_function(the_scope, VIRTUAL_METHOD, NULL, (yyvsp[(4) - (9)].id),
				      (yyvsp[(9) - (9)].cbuf), (yyvsp[(1) - (9)].line),
				      ccode_line, vararg, NULL);
									}
    break;

  case 144:
#line 1756 "parse.y"
    {
			if(!has_self) {
				yyerror(_("virtual method without 'self' as "
					  "first parameter"));
				free_all_global_state();
				YYERROR;
			}
			if(the_scope == CLASS_SCOPE) {
				yyerror(_("a method cannot be of class scope"));
				free_all_global_state();
				YYERROR;
			}
	                if (funcattrs != NULL) {
				char *error = g_strdup_printf
					(_("function attribute macros ('%s' in this case) may not be used with virtual methods"),
					 funcattrs);
	                        yyerror (error);
		                YYERROR;
		        }
			push_function(the_scope, VIRTUAL_METHOD, NULL, (yyvsp[(4) - (9)].id),
				      (yyvsp[(9) - (9)].cbuf), (yyvsp[(2) - (9)].line),
				      ccode_line, vararg, NULL);
									}
    break;

  case 145:
#line 1779 "parse.y"
    {
			if(!has_self) {
				yyerror(_("virtual method without 'szelf' as "
					  "first parameter"));
				free_all_global_state();
				YYERROR;
			}
	                if (funcattrs != NULL) {
				char *error = g_strdup_printf
					(_("function attribute macros ('%s' in this case) may not be used with virtual methods"),
					 funcattrs);
	                        yyerror (error);
		                YYERROR;
		        }
			push_function(PUBLIC_SCOPE, VIRTUAL_METHOD, NULL,
				      (yyvsp[(3) - (8)].id), (yyvsp[(8) - (8)].cbuf), (yyvsp[(1) - (8)].line),
				      ccode_line, vararg, NULL);
									}
    break;

  case 146:
#line 1797 "parse.y"
    {
	                if (funcattrs != NULL) {
				char *error = g_strdup_printf
					(_("function attribute macros ('%s' in this case) may not be used with override methods"),
					 funcattrs);
	                        yyerror (error);
		                YYERROR;
		        }
			push_function(NO_SCOPE, OVERRIDE_METHOD, (yyvsp[(3) - (11)].id),
				      (yyvsp[(6) - (11)].id), (yyvsp[(11) - (11)].cbuf),
				      (yyvsp[(1) - (11)].line), ccode_line,
				      vararg, NULL);
									}
    break;

  case 147:
#line 1810 "parse.y"
    {
			if(the_scope == CLASS_SCOPE) {
				yyerror(_("a method cannot be of class scope"));
				free_all_global_state();
				YYERROR;
			}
			push_function(the_scope, REGULAR_METHOD, NULL, (yyvsp[(3) - (8)].id),
				      (yyvsp[(8) - (8)].cbuf), (yyvsp[(1) - (8)].line), ccode_line,
				      vararg, NULL);
								}
    break;

  case 148:
#line 1820 "parse.y"
    {
			if(strcmp((yyvsp[(1) - (5)].id), "init")==0) {
				push_init_arg((yyvsp[(3) - (5)].id),FALSE);
				push_function(NO_SCOPE, INIT_METHOD, NULL,
					      (yyvsp[(1) - (5)].id), (yyvsp[(5) - (5)].cbuf), (yyvsp[(2) - (5)].line),
					      ccode_line, FALSE, NULL);
			} else if(strcmp((yyvsp[(1) - (5)].id), "class_init")==0) {
				push_init_arg((yyvsp[(3) - (5)].id),TRUE);
				push_function(NO_SCOPE, CLASS_INIT_METHOD, NULL,
					      (yyvsp[(1) - (5)].id), (yyvsp[(5) - (5)].cbuf), (yyvsp[(2) - (5)].line),
					      ccode_line, FALSE, NULL);
			} else if(strcmp((yyvsp[(1) - (5)].id), "constructor")==0) {
				push_init_arg((yyvsp[(3) - (5)].id), FALSE);
				push_function(NO_SCOPE, CONSTRUCTOR_METHOD, NULL,
					      (yyvsp[(1) - (5)].id), (yyvsp[(5) - (5)].cbuf), (yyvsp[(2) - (5)].line),
					      ccode_line, FALSE, NULL);
			} else if(strcmp((yyvsp[(1) - (5)].id), "dispose")==0) {
				push_init_arg((yyvsp[(3) - (5)].id), FALSE);
				push_function(NO_SCOPE, DISPOSE_METHOD, NULL,
					      (yyvsp[(1) - (5)].id), (yyvsp[(5) - (5)].cbuf), (yyvsp[(2) - (5)].line),
					      ccode_line, FALSE, NULL);
			} else if(strcmp((yyvsp[(1) - (5)].id), "finalize")==0) {
				push_init_arg((yyvsp[(3) - (5)].id), FALSE);
				push_function(NO_SCOPE, FINALIZE_METHOD, NULL,
					      (yyvsp[(1) - (5)].id), (yyvsp[(5) - (5)].cbuf), (yyvsp[(2) - (5)].line),
					      ccode_line, FALSE, NULL);

			} else {
				g_free((yyvsp[(1) - (5)].id));
				g_free((yyvsp[(3) - (5)].id));
				g_string_free((yyvsp[(5) - (5)].cbuf),TRUE);
				yyerror(_("parse error "
					  "(untyped blocks must be init, "
					  "class_init, constructor, dispose "
					  "or finalize)"));
				YYERROR;
			}
						}
    break;

  case 149:
#line 1860 "parse.y"
    {
			g_free(funcattrs); funcattrs = NULL;
			g_free(onerror); onerror = NULL;
			g_free(defreturn); defreturn = NULL;
			if(!set_attr_value((yyvsp[(1) - (2)].id), (yyvsp[(2) - (2)].id))) {
				g_free((yyvsp[(1) - (2)].id));
				g_free((yyvsp[(2) - (2)].id));
				yyerror(_("parse error"));
				YYERROR;
			}
			g_free((yyvsp[(1) - (2)].id));
					}
    break;

  case 150:
#line 1872 "parse.y"
    {
			g_free(funcattrs); funcattrs = NULL;
			g_free(onerror); onerror = NULL;
			g_free(defreturn); defreturn = NULL;
			if(!set_attr_value((yyvsp[(1) - (4)].id), (yyvsp[(2) - (4)].id))) {
				g_free((yyvsp[(1) - (4)].id)); g_free((yyvsp[(2) - (4)].id));
				g_free((yyvsp[(3) - (4)].id)); g_free((yyvsp[(4) - (4)].id));
				yyerror(_("parse error"));
				YYERROR;
			}
			if(!set_attr_value((yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].id))) {
				funcattrs = onerror = defreturn = NULL;
				g_free((yyvsp[(1) - (4)].id)); g_free((yyvsp[(2) - (4)].id));
				g_free((yyvsp[(3) - (4)].id)); g_free((yyvsp[(4) - (4)].id));
				yyerror(_("parse error"));
				YYERROR;
			}
			g_free((yyvsp[(1) - (4)].id));
			g_free((yyvsp[(3) - (4)].id));
						}
    break;

  case 151:
#line 1892 "parse.y"
    {
			g_free(funcattrs); funcattrs = NULL;
			g_free(onerror); onerror = NULL;
			g_free(defreturn); defreturn = NULL;
			if(!set_attr_value((yyvsp[(1) - (6)].id), (yyvsp[(2) - (6)].id))) {
				g_free((yyvsp[(1) - (6)].id)); g_free((yyvsp[(2) - (6)].id));
				g_free((yyvsp[(3) - (6)].id)); g_free((yyvsp[(4) - (6)].id));
				g_free((yyvsp[(5) - (6)].id)); g_free((yyvsp[(6) - (6)].id));
				yyerror(_("parse error"));
				YYERROR;
			}
			if(!set_attr_value((yyvsp[(3) - (6)].id), (yyvsp[(4) - (6)].id))) {
				funcattrs = onerror = defreturn = NULL;
				g_free((yyvsp[(1) - (6)].id)); g_free((yyvsp[(2) - (6)].id));
				g_free((yyvsp[(3) - (6)].id)); g_free((yyvsp[(4) - (6)].id));
				g_free((yyvsp[(5) - (6)].id)); g_free((yyvsp[(6) - (6)].id));
				yyerror(_("parse error"));
				YYERROR;
			}
			if(!set_attr_value((yyvsp[(5) - (6)].id), (yyvsp[(6) - (6)].id))) {
				funcattrs = onerror = defreturn = NULL;
				g_free((yyvsp[(1) - (6)].id)); g_free((yyvsp[(2) - (6)].id));
				g_free((yyvsp[(3) - (6)].id)); g_free((yyvsp[(4) - (6)].id));
				g_free((yyvsp[(5) - (6)].id)); g_free((yyvsp[(6) - (6)].id));
				yyerror(_("parse error"));
				YYERROR;
			}
			g_free((yyvsp[(1) - (6)].id));
			g_free((yyvsp[(3) - (6)].id));
			g_free((yyvsp[(5) - (6)].id));
						}
    break;

  case 152:
#line 1923 "parse.y"
    {
			g_free(funcattrs); funcattrs = NULL;
			g_free(onerror); onerror = NULL;
			g_free(defreturn); defreturn = NULL;
					}
    break;

  case 153:
#line 1930 "parse.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 154:
#line 1931 "parse.y"
    {
			(yyval.id) = ((yyvsp[(2) - (2)].cbuf))->str;
			g_string_free((yyvsp[(2) - (2)].cbuf), FALSE);
					}
    break;

  case 155:
#line 1937 "parse.y"
    { vararg = FALSE; has_self = FALSE; }
    break;

  case 156:
#line 1938 "parse.y"
    {
			vararg = FALSE;
			has_self = TRUE;
			if(strcmp((yyvsp[(1) - (1)].id),"self")==0)
				push_self((yyvsp[(1) - (1)].id), FALSE);
			else {
				g_free((yyvsp[(1) - (1)].id));
				yyerror(_("parse error"));
				YYERROR;
			}
       					}
    break;

  case 157:
#line 1949 "parse.y"
    {
			vararg = FALSE;
			has_self = TRUE;
			if(strcmp((yyvsp[(1) - (2)].id),"self")==0)
				push_self((yyvsp[(1) - (2)].id), TRUE);
			else {
				g_free((yyvsp[(1) - (2)].id));
				yyerror(_("parse error"));
				YYERROR;
			}
       					}
    break;

  case 158:
#line 1960 "parse.y"
    {
			vararg = FALSE;
			has_self = TRUE;
			if(strcmp((yyvsp[(2) - (2)].id),"self")==0)
				push_self((yyvsp[(2) - (2)].id), TRUE);
			else {
				g_free((yyvsp[(2) - (2)].id));
				yyerror(_("parse error"));
				YYERROR;
			}
       					}
    break;

  case 159:
#line 1971 "parse.y"
    {
			has_self = TRUE;
			if(strcmp((yyvsp[(1) - (3)].id),"self")==0)
				push_self((yyvsp[(1) - (3)].id), FALSE);
			else {
				g_free((yyvsp[(1) - (3)].id));
				yyerror(_("parse error"));
				YYERROR;
			}
					}
    break;

  case 160:
#line 1981 "parse.y"
    {
			has_self = TRUE;
			if(strcmp((yyvsp[(1) - (4)].id),"self")==0)
				push_self((yyvsp[(1) - (4)].id), TRUE);
			else {
				g_free((yyvsp[(1) - (4)].id));
				yyerror(_("parse error"));
				YYERROR;
			}
					}
    break;

  case 161:
#line 1991 "parse.y"
    {
			has_self = TRUE;
			if(strcmp((yyvsp[(2) - (4)].id),"self")==0)
				push_self((yyvsp[(2) - (4)].id), TRUE);
			else {
				g_free((yyvsp[(2) - (4)].id));
				yyerror(_("parse error"));
				YYERROR;
			}
					}
    break;

  case 162:
#line 2001 "parse.y"
    { has_self = FALSE; }
    break;

  case 163:
#line 2004 "parse.y"
    { vararg = TRUE; }
    break;

  case 164:
#line 2005 "parse.y"
    { vararg = FALSE; }
    break;

  case 165:
#line 2008 "parse.y"
    { ; }
    break;

  case 166:
#line 2009 "parse.y"
    { ; }
    break;

  case 167:
#line 2012 "parse.y"
    {
			push_funcarg((yyvsp[(2) - (2)].id),NULL);
								}
    break;

  case 168:
#line 2015 "parse.y"
    {
			push_funcarg((yyvsp[(2) - (3)].id),(yyvsp[(3) - (3)].id));
								}
    break;

  case 169:
#line 2018 "parse.y"
    {
			if(strcmp((yyvsp[(4) - (6)].id),"check")!=0) {
				yyerror(_("parse error"));
				YYERROR;
			}
			g_free((yyvsp[(4) - (6)].id));
			push_funcarg((yyvsp[(2) - (6)].id),NULL);
								}
    break;

  case 170:
#line 2026 "parse.y"
    {
			if(strcmp((yyvsp[(5) - (7)].id),"check")!=0) {
				yyerror(_("parse error"));
				YYERROR;
			}
			g_free((yyvsp[(5) - (7)].id));
			push_funcarg((yyvsp[(2) - (7)].id),(yyvsp[(3) - (7)].id));
								}
    break;

  case 171:
#line 2036 "parse.y"
    { ; }
    break;

  case 172:
#line 2037 "parse.y"
    { ; }
    break;

  case 173:
#line 2040 "parse.y"
    {
			if(strcmp((yyvsp[(1) - (1)].id),"type")==0) {
				Node *node = node_new (CHECK_NODE,
						       "chtype", TYPE_CHECK,
						       NULL);
				checks = g_list_append(checks,node);
			} else if(strcmp((yyvsp[(1) - (1)].id),"null")==0) {
				Node *node = node_new (CHECK_NODE,
						       "chtype", NULL_CHECK,
						       NULL);
				checks = g_list_append(checks,node);
			} else {
				yyerror(_("parse error"));
				YYERROR;
			}
			g_free((yyvsp[(1) - (1)].id));
					}
    break;

  case 174:
#line 2057 "parse.y"
    {
			Node *node = node_new (CHECK_NODE,
					       "chtype", GT_CHECK,
					       "number:steal", (yyvsp[(2) - (2)].id),
					       NULL);
			checks = g_list_append(checks,node);
					}
    break;

  case 175:
#line 2064 "parse.y"
    {
			Node *node = node_new (CHECK_NODE,
					       "chtype", LT_CHECK,
					       "number:steal", (yyvsp[(2) - (2)].id),
					       NULL);
			checks = g_list_append(checks,node);
					}
    break;

  case 176:
#line 2071 "parse.y"
    {
			Node *node = node_new (CHECK_NODE,
					       "chtype", GE_CHECK,
					       "number:steal", (yyvsp[(3) - (3)].id),
					       NULL);
			checks = g_list_append(checks,node);
					}
    break;

  case 177:
#line 2078 "parse.y"
    {
			Node *node = node_new (CHECK_NODE,
					       "chtype", LE_CHECK,
					       "number:steal", (yyvsp[(3) - (3)].id),
					       NULL);
			checks = g_list_append(checks,node);
					}
    break;

  case 178:
#line 2085 "parse.y"
    {
			Node *node = node_new (CHECK_NODE,
					       "chtype", EQ_CHECK,
					       "number:steal", (yyvsp[(3) - (3)].id),
					       NULL);
			checks = g_list_append(checks,node);
					}
    break;

  case 179:
#line 2092 "parse.y"
    {
			Node *node = node_new (CHECK_NODE,
					       "chtype", NE_CHECK,
					       "number:steal", (yyvsp[(3) - (3)].id),
					       NULL);
			checks = g_list_append(checks,node);
					}
    break;

  case 180:
#line 2101 "parse.y"
    {
			Node *node = node_new (ENUMDEF_NODE,
					       "etype:steal", (yyvsp[(6) - (7)].id),
					       "prefix:steal", (yyvsp[(2) - (7)].id),
					       "values:steal", enum_vals,
					       NULL);
			enum_vals = NULL;
			nodes = g_list_append (nodes, node);
			}
    break;

  case 181:
#line 2110 "parse.y"
    {
			Node *node = node_new (ENUMDEF_NODE,
					       "etype:steal", (yyvsp[(7) - (8)].id),
					       "prefix:steal", (yyvsp[(2) - (8)].id),
					       "values:steal", enum_vals,
					       NULL);
			enum_vals = NULL;
			nodes = g_list_append (nodes, node);
			}
    break;

  case 182:
#line 2121 "parse.y"
    {;}
    break;

  case 183:
#line 2122 "parse.y"
    {;}
    break;

  case 184:
#line 2125 "parse.y"
    {
			Node *node;
			char *num = (yyvsp[(3) - (3)].id);

			/* A float value, that's a bad enum */
			if (num[0] >= '0' &&
			    num[0] <= '9' &&
			    strchr (num, '.') != NULL) {
				g_free ((yyvsp[(1) - (3)].id));
				g_free (num);
				yyerror(_("parse error (enumerator value not integer constant)"));
				YYERROR;
			}
		       
			node = node_new (ENUMVALUE_NODE,
					 "name:steal", (yyvsp[(1) - (3)].id),
					 "value:steal", num,
					 NULL);
			enum_vals = g_list_append (enum_vals, node);
			}
    break;

  case 185:
#line 2145 "parse.y"
    {
			Node *node;

			node = node_new (ENUMVALUE_NODE,
					 "name:steal", (yyvsp[(1) - (1)].id),
					 NULL);
			enum_vals = g_list_append (enum_vals, node);
	}
    break;

  case 186:
#line 2155 "parse.y"
    {
			Node *node = node_new (FLAGS_NODE,
					       "ftype:steal", (yyvsp[(6) - (7)].id),
					       "prefix:steal", (yyvsp[(2) - (7)].id),
					       "values:steal", flag_vals,
					       NULL);
			flag_vals = NULL;
			nodes = g_list_append (nodes, node);
			}
    break;

  case 187:
#line 2164 "parse.y"
    {
			Node *node = node_new (FLAGS_NODE,
					       "ftype:steal", (yyvsp[(7) - (8)].id),
					       "prefix:steal", (yyvsp[(2) - (8)].id),
					       "values:steal", flag_vals,
					       NULL);
			flag_vals = NULL;
			nodes = g_list_append (nodes, node);
			}
    break;

  case 188:
#line 2175 "parse.y"
    {
			flag_vals = g_list_append (flag_vals, (yyvsp[(3) - (3)].id));
		}
    break;

  case 189:
#line 2178 "parse.y"
    {
			flag_vals = g_list_append (flag_vals, (yyvsp[(1) - (1)].id));
		}
    break;

  case 190:
#line 2183 "parse.y"
    {
			Node *node = node_new (ERROR_NODE,
					       "etype:steal", (yyvsp[(6) - (7)].id),
					       "prefix:steal", (yyvsp[(2) - (7)].id),
					       "values:steal", error_vals,
					       NULL);
			error_vals = NULL;
			nodes = g_list_append (nodes, node);
			}
    break;

  case 191:
#line 2192 "parse.y"
    {
			Node *node = node_new (ERROR_NODE,
					       "etype:steal", (yyvsp[(7) - (8)].id),
					       "prefix:steal", (yyvsp[(2) - (8)].id),
					       "values:steal", error_vals,
					       NULL);
			error_vals = NULL;
			nodes = g_list_append (nodes, node);
			}
    break;

  case 192:
#line 2203 "parse.y"
    {
			error_vals = g_list_append (error_vals, (yyvsp[(3) - (3)].id));
		}
    break;

  case 193:
#line 2206 "parse.y"
    {
			error_vals = g_list_append (error_vals, (yyvsp[(1) - (1)].id));
		}
    break;

  case 194:
#line 2212 "parse.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 195:
#line 2213 "parse.y"
    {
			(yyval.id) = g_strconcat("-",(yyvsp[(2) - (2)].id),NULL);
			g_free((yyvsp[(2) - (2)].id));
					}
    break;

  case 196:
#line 2217 "parse.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 197:
#line 2218 "parse.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;


/* Line 1267 of yacc.c.  */
#line 4685 "parse.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 2221 "parse.y"


