/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
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
	
	if (strcmp (yytext, "\n") == 0 ||
	    strcmp (yytext, "\r") == 0) {
		out = g_strconcat ("Error: ", str, " before end of line", NULL);
	} else if (yytext[0] == '\0') {
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
       
	if(method == INIT_METHOD ||
	   method == CLASS_INIT_METHOD ||
	   method == CONSTRUCTOR_METHOD ||
	   method == DISPOSE_METHOD ||
	   method == FINALIZE_METHOD) {
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



/* Line 268 of yacc.c  */
#line 732 "parse.c"

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

/* Line 293 of yacc.c  */
#line 683 "parse.y"

	char *id;
	GString *cbuf;
	GList *list;
	int line;
	int sigtype;



/* Line 293 of yacc.c  */
#line 886 "parse.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 898 "parse.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  25
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   641

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  198
/* YYNRULES -- Number of states.  */
#define YYNSTATES  418

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    66,     2,     2,     2,     2,     2,     2,
      57,    58,    63,     2,    61,    67,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    59,
      65,    60,    64,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    55,    62,    56,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    10,    13,    15,    17,    19,    21,
      23,    25,    27,    29,    31,    34,    37,    40,    43,    45,
      47,    49,    51,    56,    60,    66,    67,    72,    78,    84,
      90,    97,   105,   112,   120,   123,   125,   127,   130,   134,
     136,   138,   140,   142,   144,   146,   148,   150,   153,   157,
     160,   164,   167,   170,   172,   174,   176,   177,   183,   190,
     203,   213,   220,   224,   225,   237,   246,   252,   256,   257,
     261,   263,   265,   270,   272,   274,   278,   282,   286,   290,
     294,   298,   302,   306,   310,   314,   318,   322,   326,   330,
     334,   338,   342,   344,   350,   352,   356,   357,   361,   363,
     366,   368,   370,   372,   375,   378,   381,   385,   389,   392,
     395,   398,   400,   403,   405,   408,   410,   412,   414,   416,
     418,   420,   422,   424,   426,   428,   430,   432,   434,   437,
     440,   444,   447,   449,   453,   457,   460,   462,   467,   471,
     473,   476,   478,   489,   501,   511,   521,   530,   542,   551,
     557,   560,   565,   572,   573,   575,   578,   580,   582,   585,
     588,   592,   597,   602,   604,   608,   610,   614,   616,   619,
     623,   630,   638,   641,   643,   645,   648,   651,   655,   659,
     663,   667,   675,   684,   688,   690,   694,   696,   704,   713,
     717,   719,   727,   736,   740,   742,   744,   747,   749
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      69,     0,    -1,    71,    72,    71,    -1,    72,    71,    -1,
      71,    72,    -1,    72,    -1,    24,    -1,    26,    -1,    29,
      -1,    27,    -1,    28,    -1,    30,    -1,    31,    -1,    25,
      -1,    71,    70,    -1,    71,   113,    -1,    71,   116,    -1,
      71,   118,    -1,    70,    -1,   113,    -1,   116,    -1,   118,
      -1,    73,    55,    75,    56,    -1,    73,    55,    56,    -1,
       3,    21,     4,    21,    74,    -1,    -1,    57,    19,    58,
      74,    -1,    57,    19,    19,    58,    74,    -1,    57,    19,
      21,    58,    74,    -1,    57,    19,    20,    58,    74,    -1,
      57,    19,    32,    32,    58,    74,    -1,    57,    19,    32,
      32,    32,    58,    74,    -1,    57,    19,    19,    32,    58,
      74,    -1,    57,    19,    19,    32,    32,    58,    74,    -1,
      75,    76,    -1,    76,    -1,   104,    -1,    19,   104,    -1,
      19,    21,   104,    -1,    81,    -1,    82,    -1,    84,    -1,
      59,    -1,    33,    -1,    34,    -1,    35,    -1,    36,    -1,
      19,    19,    -1,    19,    55,    24,    -1,    60,   120,    -1,
      60,    55,    24,    -1,    78,    79,    -1,    79,    78,    -1,
      79,    -1,    78,    -1,    19,    -1,    -1,    77,    93,    19,
      80,    59,    -1,    77,    93,    19,    22,    80,    59,    -1,
      38,    91,    90,    19,    83,    19,    55,    24,    19,    55,
      24,    59,    -1,    38,    91,    90,    19,    83,    19,    55,
      24,    59,    -1,    38,    91,    90,    19,    83,    19,    -1,
      57,    19,    58,    -1,    -1,    37,    19,    19,    85,    19,
      55,    24,    19,    55,    24,    59,    -1,    37,    19,    19,
      85,    19,    55,    24,    59,    -1,    37,    19,    19,    85,
      59,    -1,    57,    86,    58,    -1,    -1,    86,    61,    89,
      -1,    89,    -1,    32,    -1,    19,    57,    32,    58,    -1,
     120,    -1,    87,    -1,    42,    60,    87,    -1,    43,    60,
      87,    -1,    44,    60,   120,    -1,    45,    60,   120,    -1,
      46,    60,    88,    -1,    48,    60,    92,    -1,    49,    60,
      93,    -1,    50,    60,    21,    -1,    50,    60,    19,    -1,
      51,    60,    21,    -1,    51,    60,    19,    -1,    52,    60,
      21,    -1,    52,    60,    19,    -1,    53,    60,    21,    -1,
      53,    60,    19,    -1,    54,    60,    21,    -1,    54,    60,
      19,    -1,    19,    -1,    19,    57,    19,    93,    58,    -1,
      19,    -1,    57,    92,    58,    -1,    -1,    19,    62,    92,
      -1,    19,    -1,    94,    98,    -1,    94,    -1,    95,    -1,
      19,    -1,     5,    19,    -1,    19,     5,    -1,    97,    19,
      -1,     5,    97,    19,    -1,    97,    19,     5,    -1,    96,
      95,    -1,    21,    95,    -1,     5,    95,    -1,    21,    -1,
      21,     5,    -1,    96,    -1,    96,     5,    -1,     6,    -1,
      18,    -1,    14,    -1,    15,    -1,    13,    -1,    16,    -1,
      17,    -1,    11,    -1,    12,    -1,     7,    -1,     8,    -1,
       9,    -1,    63,    -1,    63,     5,    -1,    63,    98,    -1,
      63,     5,    98,    -1,    19,   101,    -1,   101,    -1,    77,
      19,   101,    -1,    19,    77,   101,    -1,    77,   101,    -1,
      99,    -1,    19,    57,   102,    58,    -1,   102,    61,    19,
      -1,    19,    -1,    55,    24,    -1,    59,    -1,    40,    91,
     100,    93,    19,    57,   107,    58,   105,   103,    -1,    77,
      40,    91,    99,    93,    19,    57,   107,    58,   105,   103,
      -1,    39,    77,    93,    19,    57,   107,    58,   105,   103,
      -1,    77,    39,    93,    19,    57,   107,    58,   105,   103,
      -1,    39,    93,    19,    57,   107,    58,   105,   103,    -1,
      41,    57,    21,    58,    93,    19,    57,   107,    58,   105,
     103,    -1,    77,    93,    19,    57,   107,    58,   105,   103,
      -1,    19,    57,    19,    58,   103,    -1,    19,   106,    -1,
      19,   106,    19,   106,    -1,    19,   106,    19,   106,    19,
     106,    -1,    -1,   120,    -1,    55,    24,    -1,     6,    -1,
      19,    -1,    19,     5,    -1,     5,    19,    -1,    19,    61,
     108,    -1,    19,     5,    61,   108,    -1,     5,    19,    61,
     108,    -1,   108,    -1,   109,    61,    10,    -1,   109,    -1,
     109,    61,   110,    -1,   110,    -1,    93,    19,    -1,    93,
      19,    22,    -1,    93,    19,    57,    19,   111,    58,    -1,
      93,    19,    22,    57,    19,   111,    58,    -1,   111,   112,
      -1,   112,    -1,    19,    -1,    64,   120,    -1,    65,   120,
      -1,    64,    60,   120,    -1,    65,    60,   120,    -1,    60,
      60,   120,    -1,    66,    60,   120,    -1,     9,    19,    55,
     114,    56,    21,    59,    -1,     9,    19,    55,   114,    61,
      56,    21,    59,    -1,   114,    61,   115,    -1,   115,    -1,
      19,    60,   120,    -1,    19,    -1,    48,    19,    55,   117,
      56,    21,    59,    -1,    48,    19,    55,   117,    61,    56,
      21,    59,    -1,   117,    61,    19,    -1,    19,    -1,    47,
      19,    55,   119,    56,    21,    59,    -1,    47,    19,    55,
     119,    61,    56,    21,    59,    -1,   119,    61,    19,    -1,
      19,    -1,    20,    -1,    67,    20,    -1,    23,    -1,    19,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   704,   704,   705,   706,   707,   710,   719,   728,   737,
     746,   755,   764,   773,   784,   785,   786,   787,   788,   789,
     790,   791,   794,   799,   806,   823,   824,   832,   844,   853,
     865,   874,   883,   892,   903,   904,   907,   908,   917,   929,
     930,   931,   932,   935,   936,   937,   938,   941,   961,   985,
     989,   997,   998,   999,  1000,  1001,  1009,  1015,  1018,  1023,
    1091,  1145,  1234,  1242,  1247,  1295,  1331,  1347,  1348,  1351,
    1352,  1355,  1356,  1368,  1369,  1372,  1378,  1384,  1390,  1396,
    1402,  1408,  1415,  1421,  1427,  1433,  1439,  1445,  1451,  1457,
    1463,  1469,  1475,  1500,  1509,  1515,  1516,  1519,  1522,  1528,
    1535,  1544,  1547,  1550,  1554,  1558,  1562,  1567,  1575,  1579,
    1584,  1588,  1591,  1595,  1598,  1603,  1604,  1605,  1606,  1607,
    1608,  1609,  1610,  1611,  1614,  1615,  1616,  1619,  1620,  1621,
    1625,  1632,  1644,  1650,  1662,  1674,  1677,  1683,  1688,  1691,
    1696,  1697,  1701,  1724,  1747,  1770,  1793,  1811,  1824,  1834,
    1874,  1886,  1906,  1937,  1944,  1945,  1951,  1952,  1963,  1974,
    1985,  1995,  2005,  2015,  2018,  2019,  2022,  2023,  2026,  2029,
    2032,  2040,  2050,  2051,  2054,  2071,  2078,  2085,  2092,  2099,
    2106,  2115,  2124,  2135,  2136,  2139,  2159,  2169,  2178,  2189,
    2192,  2197,  2206,  2217,  2220,  2226,  2227,  2231,  2232
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
  "TYPETOKEN", "ARRAY_DIM", "SINGLE_CHAR", "CCODE", "CTCODE", "ADCODE",
  "HTCODE", "PHCODE", "HCODE", "ACODE", "ATCODE", "STRING", "PUBLIC",
  "PRIVATE", "PROTECTED", "CLASSWIDE", "PROPERTY", "ARGUMENT", "VIRTUAL",
  "SIGNAL", "OVERRIDE", "NICK", "BLURB", "MAXIMUM", "MINIMUM",
  "DEFAULT_VALUE", "ERROR", "FLAGS", "TYPE", "FLAGS_TYPE", "ENUM_TYPE",
  "PARAM_TYPE", "BOXED_TYPE", "OBJECT_TYPE", "'{'", "'}'", "'('", "')'",
  "';'", "'='", "','", "'|'", "'*'", "'>'", "'<'", "'!'", "'-'", "$accept",
  "prog", "ccode", "ccodes", "class", "classdec", "classflags",
  "classcode", "thing", "scope", "destructor", "initializer", "varoptions",
  "variable", "argument", "export", "property", "param_spec",
  "param_spec_list", "string", "anyval", "param_spec_value", "argtype",
  "flags", "flaglist", "type", "specifier_list", "spec_list", "specifier",
  "strunionenum", "pointer", "simplesigtype", "fullsigtype", "sigtype",
  "tokenlist", "codenocode", "method", "methodmods", "retcode", "funcargs",
  "arglist", "arglist1", "arg", "checklist", "check", "enumcode",
  "enumvals", "enumval", "flagcode", "flagvals", "errorcode", "errorvals",
  "numtok", 0
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
     305,   306,   307,   308,   309,   123,   125,    40,    41,    59,
      61,    44,   124,    42,    62,    60,    33,    45
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    68,    69,    69,    69,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    72,    72,    73,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    75,    75,    76,    76,    76,    76,
      76,    76,    76,    77,    77,    77,    77,    78,    78,    79,
      79,    80,    80,    80,    80,    80,    80,    81,    81,    82,
      82,    82,    83,    83,    84,    84,    84,    85,    85,    86,
      86,    87,    87,    88,    88,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    90,    90,    91,    91,    92,    92,    93,
      93,    94,    94,    94,    94,    94,    94,    94,    95,    95,
      95,    95,    95,    95,    95,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    97,    97,    97,    98,    98,    98,
      98,    99,    99,   100,   100,   100,   100,   101,   102,   102,
     103,   103,   104,   104,   104,   104,   104,   104,   104,   104,
     105,   105,   105,   105,   106,   106,   107,   107,   107,   107,
     107,   107,   107,   107,   108,   108,   109,   109,   110,   110,
     110,   110,   111,   111,   112,   112,   112,   112,   112,   112,
     112,   113,   113,   114,   114,   115,   115,   116,   116,   117,
     117,   118,   118,   119,   119,   120,   120,   120,   120
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     1,     1,
       1,     1,     4,     3,     5,     0,     4,     5,     5,     5,
       6,     7,     6,     7,     2,     1,     1,     2,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     2,
       3,     2,     2,     1,     1,     1,     0,     5,     6,    12,
       9,     6,     3,     0,    11,     8,     5,     3,     0,     3,
       1,     1,     4,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     5,     1,     3,     0,     3,     1,     2,
       1,     1,     1,     2,     2,     2,     3,     3,     2,     2,
       2,     1,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       3,     2,     1,     3,     3,     2,     1,     4,     3,     1,
       2,     1,    10,    11,     9,     9,     8,    11,     8,     5,
       2,     4,     6,     0,     1,     2,     1,     1,     2,     2,
       3,     4,     4,     1,     3,     1,     3,     1,     2,     3,
       6,     7,     2,     1,     1,     2,     2,     3,     3,     3,
       3,     7,     8,     3,     1,     3,     1,     7,     8,     3,
       1,     7,     8,     3,     1,     1,     2,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     6,    13,     7,     9,    10,     8,    11,
      12,     0,     0,     0,    18,     0,     5,     0,    19,    20,
      21,     0,     0,     0,     0,     1,    14,     4,    15,    16,
      17,     3,     0,     0,     0,     0,     0,     2,     0,    43,
      44,    45,    46,     0,    96,     0,    96,     0,    23,    42,
       0,    35,     0,    39,    40,    41,    36,    25,   186,     0,
     184,   194,     0,   190,     0,     0,     0,     0,     0,    37,
       0,     0,     0,     0,   115,   124,   125,   126,   122,   123,
     119,   117,   118,   120,   121,   116,   102,   111,     0,     0,
     100,   101,   113,     0,     0,     0,    22,    34,     0,    96,
       0,     0,    24,     0,     0,     0,     0,     0,     0,     0,
      38,     0,     0,    68,    98,     0,    94,     0,     0,   103,
     110,     0,   104,   112,   109,     0,     0,   127,    99,   114,
     108,   105,     0,     0,   136,     0,   132,     0,     0,     0,
      56,     0,   198,   195,   197,     0,   185,     0,     0,   183,
       0,   193,     0,     0,   189,     0,     0,     0,     0,     0,
       0,    95,     0,    63,   106,     0,     0,   128,   129,   107,
       0,     0,     0,   131,     0,   135,     0,     0,     0,     0,
       0,    55,    56,     0,     0,    54,    53,     0,     0,     0,
       0,     0,    25,   196,   181,     0,   191,     0,   187,     0,
       0,   141,   149,    92,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    70,     0,    66,
      97,     0,     0,     0,     0,     0,   115,   102,     0,     0,
     163,   165,   167,   130,   139,     0,   134,   133,     0,     0,
       0,     0,    47,     0,     0,     0,     0,    49,    51,     0,
      52,    57,     0,    25,    25,    25,     0,    26,   182,   192,
     188,   140,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    67,     0,     0,     0,     0,    61,
       0,   103,   104,     0,   168,   153,     0,   137,     0,     0,
       0,     0,     0,    48,    58,   153,    50,     0,    25,    27,
      29,    28,     0,    25,     0,    71,    75,    76,    77,    78,
     198,    74,    79,    73,    80,    81,    83,    82,    85,    84,
      87,    86,    89,    88,    91,    90,    69,     0,    93,    62,
       0,   153,     0,     0,   160,   169,     0,     0,     0,   164,
     166,   138,     0,     0,   153,     0,     0,    25,    32,    25,
      30,     0,     0,    65,     0,     0,   162,   161,     0,     0,
       0,   150,   154,   146,   153,     0,     0,     0,   148,    33,
      31,     0,     0,     0,    60,   144,     0,   174,     0,     0,
       0,     0,     0,   173,   155,     0,     0,   153,   145,   153,
      72,     0,     0,     0,     0,     0,   175,     0,   176,     0,
     170,   172,   151,   142,     0,     0,    64,     0,   171,   179,
     177,   178,   180,     0,   147,   143,    59,   152
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,    15,    16,    17,   102,    50,    51,    52,
     185,   186,   187,    53,    54,   223,    55,   159,   216,   306,
     312,   217,   117,    72,   115,   228,    90,    91,    92,    93,
     128,   134,   135,   136,   235,   202,    56,   338,   361,   229,
     230,   231,   232,   382,   383,    18,    59,    60,    19,    64,
      20,    62,   362
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -360
static const yytype_int16 yypact[] =
{
     162,    -2,     6,  -360,  -360,  -360,  -360,  -360,  -360,  -360,
    -360,    16,    90,   131,  -360,   162,   210,    77,  -360,  -360,
    -360,   156,   126,   160,   167,  -360,  -360,   210,  -360,  -360,
    -360,   210,   161,   223,   153,   230,   231,   210,   226,  -360,
    -360,  -360,  -360,   244,   207,   309,   207,   214,  -360,  -360,
     192,  -360,   292,  -360,  -360,  -360,  -360,   215,   242,   -28,
    -360,  -360,   151,  -360,   152,   255,   300,   310,   292,  -360,
     319,   330,   336,   376,  -360,  -360,  -360,  -360,  -360,  -360,
    -360,  -360,  -360,  -360,  -360,  -360,   351,   444,   393,   338,
     295,  -360,   458,   360,   327,   365,  -360,  -360,   393,   207,
     377,   384,  -360,     7,   392,    92,   399,    98,   409,   100,
    -360,   379,   428,   394,   390,   395,   397,   447,   472,  -360,
    -360,   448,  -360,   472,  -360,   449,   423,     5,  -360,   472,
    -360,   476,   149,   463,  -360,   393,  -360,   433,   473,   475,
      58,   184,  -360,  -360,  -360,   477,  -360,   436,   478,  -360,
     437,  -360,   479,   439,  -360,   480,   159,   445,   236,    -4,
     330,  -360,   484,   450,  -360,   451,   410,   295,  -360,  -360,
     452,   485,   486,  -360,    69,  -360,   487,   393,   453,    69,
     393,   115,    -3,   410,    18,   454,   492,   456,   117,   455,
     459,   488,   215,  -360,  -360,   457,  -360,   460,  -360,   462,
     494,  -360,  -360,  -360,   464,   465,   466,   467,   468,   469,
     470,   471,   474,   481,   482,   483,   185,  -360,   489,  -360,
    -360,   393,   493,   503,   410,   427,   490,     8,   504,   491,
    -360,   495,  -360,  -360,  -360,   212,  -360,  -360,   496,   513,
     410,   514,  -360,   511,   498,   497,   512,  -360,  -360,   115,
    -360,  -360,   120,   215,   215,   215,   121,  -360,  -360,  -360,
    -360,  -360,   110,   110,     7,     7,    63,   330,   393,   119,
     202,   235,   274,   333,  -360,   236,   515,   500,   501,   499,
     502,   289,   290,   393,    -8,   518,   359,  -360,   519,   410,
     505,   506,   508,  -360,  -360,   518,  -360,   509,   215,  -360,
    -360,  -360,   510,   215,   516,  -360,  -360,  -360,  -360,  -360,
     516,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,
    -360,  -360,  -360,  -360,  -360,  -360,  -360,    13,  -360,  -360,
     521,   518,   393,   393,  -360,   517,   527,    70,   159,  -360,
    -360,  -360,   520,   410,   518,   410,   159,   215,  -360,   215,
    -360,   529,   522,  -360,    65,   159,  -360,  -360,   528,    32,
     526,   532,  -360,  -360,   518,   523,   159,   524,  -360,  -360,
    -360,   525,   539,   530,  -360,  -360,    32,  -360,   531,    27,
      83,   533,    56,  -360,  -360,    70,   159,   518,  -360,   518,
    -360,   507,   545,    81,     7,     7,  -360,     7,  -360,     7,
    -360,  -360,   551,  -360,   159,   159,  -360,   535,  -360,  -360,
    -360,  -360,  -360,    70,  -360,  -360,  -360,  -360
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -360,  -360,    21,    15,   537,  -360,  -190,  -360,   534,   -27,
     354,   386,   398,  -360,  -360,  -360,  -360,  -360,  -360,   -90,
    -360,   297,  -360,   -37,  -155,   -44,  -360,   -70,  -360,   -67,
     -23,   440,  -360,    -5,  -360,  -326,    85,  -288,  -278,  -179,
    -262,  -360,   301,   199,  -359,   237,  -360,   536,   238,  -360,
     322,  -360,  -103
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -160
static const yytype_int16 yytable[] =
{
     146,    89,   257,   120,   245,   220,   121,   346,   100,    94,
     167,    68,   363,   282,   335,   218,   181,   124,    88,    21,
     368,   334,   130,   401,   112,    22,   142,   143,   104,   375,
     144,    31,   352,   105,   401,    23,    26,   142,   143,    68,
     388,   144,    37,   355,   125,   280,   142,   143,   120,   336,
     144,   377,    26,   120,   138,   219,   366,   184,    26,   120,
     403,   291,   139,   299,   300,   301,  -157,   133,   127,   283,
     356,   357,   353,   246,   145,   377,   386,   181,   414,   415,
     182,   247,   310,   143,   373,   145,   144,   395,   170,   142,
     143,   176,   378,   144,   145,   305,   379,   380,   381,   404,
     377,   405,   142,   143,   168,   172,   144,   402,   348,    24,
     342,    58,   314,   350,   400,   183,   378,   151,   184,   154,
     379,   380,   381,    69,   374,   360,   171,   173,   175,   304,
     145,    25,    32,   239,   242,   417,   241,   145,   316,   408,
     317,   378,   305,   397,   233,   379,   380,   381,   148,   252,
     145,   110,   297,   302,   152,   120,   155,   369,   121,   370,
      33,   308,   309,   313,   365,     1,   367,   236,   170,   237,
     243,     2,    58,   307,   173,   253,   311,   277,   298,   303,
      38,    34,    39,    40,    41,    42,     3,     4,     5,     6,
       7,     8,     9,    10,    39,    40,    41,    42,    43,    44,
      45,    46,    47,   188,   189,   190,   171,   106,   108,    11,
      12,    38,   107,   109,   200,    35,   191,    48,   201,     2,
      49,   318,    36,   319,   315,    39,    40,    41,    42,    43,
      44,    45,    46,    47,     3,     4,     5,     6,     7,     8,
       9,    10,   192,   274,    57,    65,   275,    66,    96,    61,
      63,    49,    28,    29,   320,   203,   321,    11,    12,    39,
      40,    41,    42,    70,    71,    45,    46,    47,    28,    29,
     287,    95,   101,   288,    28,    29,   396,   398,   204,   205,
     206,   207,   208,    67,   209,   210,   211,   212,   213,   214,
     215,   409,   410,   322,   411,   323,   412,    73,    74,    75,
      76,    77,   103,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    67,    87,    73,    74,    75,    76,    77,    65,
      78,    79,    80,    81,    82,    83,    84,    85,    86,   111,
      87,    98,    99,    39,    40,    41,    42,    30,   113,    45,
      46,    47,    39,    40,    41,    42,   132,  -159,  -158,   114,
     332,   333,   324,    30,   325,   116,   122,   126,   127,    30,
      39,    40,    41,    42,    73,    74,    75,    76,    77,   339,
      78,    79,    80,    81,    82,    83,    84,    85,    86,   131,
      87,   118,    74,    75,    76,    77,   137,    78,    79,    80,
      81,    82,    83,    84,    85,   119,   140,    87,    73,    74,
      75,    76,    77,   141,    78,    79,    80,    81,    82,    83,
      84,    85,    86,   147,    87,   225,   226,    75,    76,    77,
     150,    78,    79,    80,    81,    82,    83,    84,    85,   227,
     153,    87,   118,    74,    75,    76,    77,   156,    78,    79,
      80,    81,    82,    83,    84,    85,   281,   157,    87,   123,
      74,   158,   160,   161,   162,    78,    79,    80,    81,    82,
      83,    84,    85,   129,    74,    87,   163,   164,   165,    78,
      79,    80,    81,    82,    83,    84,    85,   118,    74,    87,
     166,   169,   174,    78,    79,    80,    81,    82,    83,    84,
      85,   177,   178,    87,   179,   194,   196,   193,   198,   195,
     197,   199,   183,   221,   234,   170,   238,   222,   224,   171,
     240,   249,   278,   254,   184,   251,   258,   255,   261,   259,
     256,   260,   279,   284,   262,   263,   264,   265,   266,   267,
     268,   269,   290,   292,   270,   293,   296,   337,   341,   327,
     250,   271,   272,   273,   276,   354,   359,   376,  -156,   285,
     384,   385,    27,   289,   330,   295,   286,   294,   328,   329,
     331,   371,   343,   391,   344,   345,   406,   347,   349,   407,
     413,   248,   326,   351,   358,   393,     0,   372,   364,   180,
     244,   387,   389,   390,    97,   392,     0,   340,     0,     0,
       0,   394,     0,   399,   416,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   149
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-360))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     103,    45,   192,    73,   183,   160,    73,   295,    52,    46,
       5,    38,   338,     5,    22,    19,    19,    87,    45,    21,
     346,   283,    92,   382,    68,    19,    19,    20,    56,   355,
      23,    16,    19,    61,   393,    19,    15,    19,    20,    66,
     366,    23,    27,   331,    88,   224,    19,    20,   118,    57,
      23,    19,    31,   123,    98,    59,   344,    60,    37,   129,
     386,   240,    99,   253,   254,   255,    58,    94,    63,    61,
     332,   333,    59,    55,    67,    19,   364,    19,   404,   405,
      22,   184,    19,    20,    19,    67,    23,    60,    19,    19,
      20,   135,    60,    23,    67,    32,    64,    65,    66,   387,
      19,   389,    19,    20,   127,   132,    23,   385,   298,    19,
     289,    19,   267,   303,    58,    57,    60,    19,    60,    19,
      64,    65,    66,    38,    59,    55,    57,   132,   133,    19,
      67,     0,    55,   177,    19,   413,   180,    67,    19,    58,
      21,    60,    32,    60,   167,    64,    65,    66,    56,    32,
      67,    66,    32,    32,    56,   225,    56,   347,   225,   349,
       4,   264,   265,   266,   343,     3,   345,   172,    19,   174,
      55,     9,    19,   263,   179,    58,   266,   221,    58,    58,
      19,    55,    33,    34,    35,    36,    24,    25,    26,    27,
      28,    29,    30,    31,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    19,    20,    21,    57,    56,    56,    47,
      48,    19,    61,    61,    55,    55,    32,    56,    59,     9,
      59,    19,    55,    21,   268,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    24,    25,    26,    27,    28,    29,
      30,    31,    58,    58,    21,    19,    61,    21,    56,    19,
      19,    59,    15,    15,    19,    19,    21,    47,    48,    33,
      34,    35,    36,    19,    57,    39,    40,    41,    31,    31,
      58,    57,    57,    61,    37,    37,   379,   380,    42,    43,
      44,    45,    46,    57,    48,    49,    50,    51,    52,    53,
      54,   394,   395,    19,   397,    21,   399,     5,     6,     7,
       8,     9,    60,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    57,    21,     5,     6,     7,     8,     9,    19,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    19,
      21,    39,    40,    33,    34,    35,    36,    15,    19,    39,
      40,    41,    33,    34,    35,    36,    19,    58,    58,    19,
      61,    61,    19,    31,    21,    19,     5,    19,    63,    37,
      33,    34,    35,    36,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    19,
      21,     5,     6,     7,     8,     9,    21,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    19,    21,     5,     6,
       7,     8,     9,    19,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    21,    21,     5,     6,     7,     8,     9,
      21,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      21,    21,     5,     6,     7,     8,     9,    58,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    19,    21,     5,
       6,    57,    62,    58,    57,    11,    12,    13,    14,    15,
      16,    17,    18,     5,     6,    21,    19,    19,    19,    11,
      12,    13,    14,    15,    16,    17,    18,     5,     6,    21,
      57,     5,    19,    11,    12,    13,    14,    15,    16,    17,
      18,    58,    19,    21,    19,    59,    59,    20,    59,    21,
      21,    21,    57,    19,    19,    19,    19,    57,    57,    57,
      57,    19,    19,    58,    60,    59,    59,    58,    24,    59,
      32,    59,    19,    19,    60,    60,    60,    60,    60,    60,
      60,    60,    19,    19,    60,    24,    24,    19,    19,    24,
     186,    60,    60,    60,    55,    24,    19,    19,    58,    58,
      24,    19,    15,    57,    55,    58,    61,    59,    58,    58,
      58,    32,    57,    24,    58,    57,    59,    58,    58,    24,
      19,   185,   275,    57,    57,   376,    -1,    55,    58,   139,
     182,    58,    58,    58,    50,    55,    -1,   286,    -1,    -1,
      -1,    60,    -1,    60,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   105
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     9,    24,    25,    26,    27,    28,    29,    30,
      31,    47,    48,    69,    70,    71,    72,    73,   113,   116,
     118,    21,    19,    19,    19,     0,    70,    72,   113,   116,
     118,    71,    55,     4,    55,    55,    55,    71,    19,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    56,    59,
      75,    76,    77,    81,    82,    84,   104,    21,    19,   114,
     115,    19,   119,    19,   117,    19,    21,    57,    77,   104,
      19,    57,    91,     5,     6,     7,     8,     9,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    21,    77,    93,
      94,    95,    96,    97,    91,    57,    56,    76,    39,    40,
      93,    57,    74,    60,    56,    61,    56,    61,    56,    61,
     104,    19,    93,    19,    19,    92,    19,    90,     5,    19,
      95,    97,     5,     5,    95,    93,    19,    63,    98,     5,
      95,    19,    19,    77,    99,   100,   101,    21,    93,    91,
      19,    19,    19,    20,    23,    67,   120,    21,    56,   115,
      21,    19,    56,    21,    19,    56,    58,    19,    57,    85,
      62,    58,    57,    19,    19,    19,    57,     5,    98,     5,
      19,    57,    77,   101,    19,   101,    93,    58,    19,    19,
      99,    19,    22,    57,    60,    78,    79,    80,    19,    20,
      21,    32,    58,    20,    59,    21,    59,    21,    59,    21,
      55,    59,   103,    19,    42,    43,    44,    45,    46,    48,
      49,    50,    51,    52,    53,    54,    86,    89,    19,    59,
      92,    19,    57,    83,    57,     5,     6,    19,    93,   107,
     108,   109,   110,    98,    19,   102,   101,   101,    19,    93,
      57,    93,    19,    55,    80,   107,    55,   120,    79,    19,
      78,    59,    32,    58,    58,    58,    32,    74,    59,    59,
      59,    24,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    58,    61,    55,    93,    19,    19,
     107,    19,     5,    61,    19,    58,    61,    58,    61,    57,
      19,   107,    19,    24,    59,    58,    24,    32,    58,    74,
      74,    74,    32,    58,    19,    32,    87,    87,   120,   120,
      19,    87,    88,   120,    92,    93,    19,    21,    19,    21,
      19,    21,    19,    21,    19,    21,    89,    24,    58,    58,
      55,    58,    61,    61,   108,    22,    57,    19,   105,    10,
     110,    19,   107,    57,    58,    57,   105,    58,    74,    58,
      74,    57,    19,    59,    24,   105,   108,   108,    57,    19,
      55,   106,   120,   103,    58,   107,   105,   107,   103,    74,
      74,    32,    55,    19,    59,   103,    19,    19,    60,    64,
      65,    66,   111,   112,    24,    19,   105,    58,   103,    58,
      58,    24,    55,   111,    60,    60,   120,    60,   120,    60,
      58,   112,   106,   103,   105,   105,    59,    24,    58,   120,
     120,   120,   120,    19,   103,   103,    59,   106
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

/* Line 1806 of yacc.c  */
#line 704 "parse.y"
    { ; }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 705 "parse.y"
    { ; }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 706 "parse.y"
    { ; }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 707 "parse.y"
    { ; }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 710 "parse.y"
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

/* Line 1806 of yacc.c  */
#line 719 "parse.y"
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

/* Line 1806 of yacc.c  */
#line 728 "parse.y"
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

/* Line 1806 of yacc.c  */
#line 737 "parse.y"
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

/* Line 1806 of yacc.c  */
#line 746 "parse.y"
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

/* Line 1806 of yacc.c  */
#line 755 "parse.y"
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

/* Line 1806 of yacc.c  */
#line 764 "parse.y"
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

/* Line 1806 of yacc.c  */
#line 773 "parse.y"
    {
			Node *node = node_new (CCODE_NODE,
					       "cctype", CT_CCODE,
					       "cbuf:steal", ((yyvsp[(1) - (1)].cbuf))->str,
					       "line_no", ccode_line,
					       NULL);
			nodes = g_list_append(nodes,node);
			g_string_free((yyvsp[(1) - (1)].cbuf),FALSE);
					}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 784 "parse.y"
    { ; }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 785 "parse.y"
    { ; }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 786 "parse.y"
    { ; }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 787 "parse.y"
    { ; }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 788 "parse.y"
    { ; }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 789 "parse.y"
    { ; }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 790 "parse.y"
    { ; }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 791 "parse.y"
    { ; }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 794 "parse.y"
    {
			((Class *)class)->nodes = class_nodes;
			class_nodes = NULL;
			nodes = g_list_append(nodes,class);
						}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 799 "parse.y"
    {
			((Class *)class)->nodes = NULL;
			class_nodes = NULL;
			nodes = g_list_append(nodes,class);
						}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 806 "parse.y"
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

  case 26:

/* Line 1806 of yacc.c  */
#line 824 "parse.y"
    {
			if(strcmp((yyvsp[(2) - (4)].id),"abstract") == 0) {
				abstract = TRUE;
			} else {
				yyerror(_("parse error"));
				YYERROR;
			}
		}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 832 "parse.y"
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

  case 28:

/* Line 1806 of yacc.c  */
#line 844 "parse.y"
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

  case 29:

/* Line 1806 of yacc.c  */
#line 853 "parse.y"
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

  case 30:

/* Line 1806 of yacc.c  */
#line 865 "parse.y"
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

  case 31:

/* Line 1806 of yacc.c  */
#line 874 "parse.y"
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

  case 32:

/* Line 1806 of yacc.c  */
#line 883 "parse.y"
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

  case 33:

/* Line 1806 of yacc.c  */
#line 892 "parse.y"
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

  case 34:

/* Line 1806 of yacc.c  */
#line 903 "parse.y"
    { ; }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 904 "parse.y"
    { ; }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 907 "parse.y"
    { ; }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 908 "parse.y"
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

  case 38:

/* Line 1806 of yacc.c  */
#line 917 "parse.y"
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

  case 39:

/* Line 1806 of yacc.c  */
#line 929 "parse.y"
    { ; }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 930 "parse.y"
    { ; }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 931 "parse.y"
    { ; }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 932 "parse.y"
    { ; }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 935 "parse.y"
    { the_scope = PUBLIC_SCOPE; }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 936 "parse.y"
    { the_scope = PRIVATE_SCOPE; }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 937 "parse.y"
    { the_scope = PROTECTED_SCOPE; }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 938 "parse.y"
    { the_scope = CLASS_SCOPE; }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 941 "parse.y"
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

  case 48:

/* Line 1806 of yacc.c  */
#line 961 "parse.y"
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

  case 49:

/* Line 1806 of yacc.c  */
#line 985 "parse.y"
    {
			initializer = (yyvsp[(2) - (2)].id);
			initializer_line = ccode_line;
				}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 989 "parse.y"
    {
			initializer = ((yyvsp[(3) - (3)].cbuf))->str;
			initializer_line = ccode_line;
			g_string_free((yyvsp[(3) - (3)].cbuf), FALSE);
				}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 997 "parse.y"
    { ; }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 998 "parse.y"
    { ; }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 999 "parse.y"
    { destructor = NULL; }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 1000 "parse.y"
    { initializer = NULL; }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 1001 "parse.y"
    {
			if (strcmp ((yyvsp[(1) - (1)].id), "GladeXML") == 0) {
				glade_widget = TRUE;
			} else {
				yyerror(_("parse error"));
				YYERROR;
			}
					}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 1009 "parse.y"
    {
			destructor = NULL;
			initializer = NULL;
					}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 1015 "parse.y"
    {
			push_variable((yyvsp[(3) - (5)].id), the_scope,(yyvsp[(1) - (5)].line), NULL);
						}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 1018 "parse.y"
    {
			push_variable((yyvsp[(3) - (6)].id), the_scope, (yyvsp[(1) - (6)].line), (yyvsp[(4) - (6)].id));
						}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 1023 "parse.y"
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

  case 60:

/* Line 1806 of yacc.c  */
#line 1091 "parse.y"
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

  case 61:

/* Line 1806 of yacc.c  */
#line 1145 "parse.y"
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

  case 62:

/* Line 1806 of yacc.c  */
#line 1234 "parse.y"
    {
			if (strcmp ((yyvsp[(2) - (3)].id), "export")!=0) {
				g_free ((yyvsp[(2) - (3)].id)); 
				yyerror (_("parse error"));
				YYERROR;
			}
			(yyval.id) = (yyvsp[(2) - (3)].id);
						}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 1242 "parse.y"
    {
			(yyval.id) = NULL;
						}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 1247 "parse.y"
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

  case 65:

/* Line 1806 of yacc.c  */
#line 1295 "parse.y"
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

  case 66:

/* Line 1806 of yacc.c  */
#line 1331 "parse.y"
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

  case 67:

/* Line 1806 of yacc.c  */
#line 1347 "parse.y"
    { ; }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 1348 "parse.y"
    { ; }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 1351 "parse.y"
    { ; }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 1352 "parse.y"
    { ; }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 1355 "parse.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 1356 "parse.y"
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

  case 73:

/* Line 1806 of yacc.c  */
#line 1368 "parse.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 1369 "parse.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 1372 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "nick:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 1378 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "blurb:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 1384 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "maximum:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 1390 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "minimum:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 1396 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "default_value:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 1402 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "flags:steal", (yyvsp[(3) - (3)].list),
			  NULL);
		  }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 1408 "parse.y"
    {
		Type *type = pop_type ();
		ensure_property ();
		node_set ((Node *)property,
			  "ptype:steal", type,
			  NULL);
		  }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 1415 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 1421 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 1427 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 1433 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 1439 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 1445 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 1451 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 1457 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 1463 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 1469 "parse.y"
    {
		ensure_property ();
		node_set ((Node *)property,
			  "extra_gtktype:steal", (yyvsp[(3) - (3)].id),
			  NULL);
		  }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 1475 "parse.y"
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

  case 93:

/* Line 1806 of yacc.c  */
#line 1500 "parse.y"
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

  case 94:

/* Line 1806 of yacc.c  */
#line 1509 "parse.y"
    {
			(yyval.id) = debool ((yyvsp[(1) - (1)].id));
			typestack = g_list_prepend(typestack,NULL);
						}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 1515 "parse.y"
    { (yyval.list) = (yyvsp[(2) - (3)].list); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 1516 "parse.y"
    { (yyval.list) = NULL; }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 1519 "parse.y"
    {
			(yyval.list) = g_list_append((yyvsp[(3) - (3)].list),(yyvsp[(1) - (3)].id));
						}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 1522 "parse.y"
    {
			(yyval.list) = g_list_append(NULL,(yyvsp[(1) - (1)].id));
						}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 1528 "parse.y"
    {
			Node *node = node_new (TYPE_NODE, 
					       "name:steal", (yyvsp[(1) - (2)].id),
					       "pointer:steal", (yyvsp[(2) - (2)].id),
					       NULL);
			typestack = g_list_prepend(typestack,node);
							}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 1535 "parse.y"
    {
			Node *node = node_new (TYPE_NODE, 
					       "name:steal", (yyvsp[(1) - (1)].id),
					       NULL);
			typestack = g_list_prepend(typestack,node);
							}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 1544 "parse.y"
    {
			(yyval.id) = (yyvsp[(1) - (1)].id);
							}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 1547 "parse.y"
    {
			(yyval.id) = (yyvsp[(1) - (1)].id);
							}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1550 "parse.y"
    {
			(yyval.id) = g_strconcat("const ", (yyvsp[(2) - (2)].id), NULL);
			g_free((yyvsp[(2) - (2)].id));
							}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 1554 "parse.y"
    {
			(yyval.id) = g_strconcat((yyvsp[(1) - (2)].id), " const", NULL);
			g_free((yyvsp[(1) - (2)].id));
							}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1558 "parse.y"
    {
			(yyval.id) = g_strconcat((yyvsp[(1) - (2)].id), " ", (yyvsp[(2) - (2)].id), NULL);
			g_free((yyvsp[(2) - (2)].id));
							}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1562 "parse.y"
    {
			(yyval.id) = g_strconcat("const ", (yyvsp[(2) - (3)].id), " ",
					     (yyvsp[(3) - (3)].id), NULL);
			g_free((yyvsp[(3) - (3)].id));
							}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1567 "parse.y"
    {
			(yyval.id) = g_strconcat((yyvsp[(1) - (3)].id), " ",
					     (yyvsp[(2) - (3)].id), " const", NULL);
			g_free((yyvsp[(2) - (3)].id));
							}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1575 "parse.y"
    {
			(yyval.id) = g_strconcat((yyvsp[(1) - (2)].id), " ", (yyvsp[(2) - (2)].id), NULL);
			g_free((yyvsp[(2) - (2)].id));
							}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1579 "parse.y"
    {
			(yyval.id) = g_strconcat((yyvsp[(1) - (2)].id), " ", (yyvsp[(2) - (2)].id), NULL);
			g_free((yyvsp[(1) - (2)].id));
			g_free((yyvsp[(2) - (2)].id));
							}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1584 "parse.y"
    {
			(yyval.id) = g_strconcat("const ", (yyvsp[(2) - (2)].id), NULL);
			g_free((yyvsp[(2) - (2)].id));
							}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 1588 "parse.y"
    {
			(yyval.id) = (yyvsp[(1) - (1)].id);
							}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1591 "parse.y"
    {
			(yyval.id) = g_strconcat((yyvsp[(1) - (2)].id), " const", NULL);
			g_free((yyvsp[(1) - (2)].id));
							}
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 1595 "parse.y"
    {
			(yyval.id) = g_strdup((yyvsp[(1) - (1)].id));
							}
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 1598 "parse.y"
    {
			(yyval.id) = g_strconcat((yyvsp[(1) - (2)].id), " const", NULL);
							}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 1603 "parse.y"
    { (yyval.id) = "void"; }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 1604 "parse.y"
    { (yyval.id) = "char"; }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 1605 "parse.y"
    { (yyval.id) = "short"; }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 1606 "parse.y"
    { (yyval.id) = "int"; }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 1607 "parse.y"
    { (yyval.id) = "long"; }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 1608 "parse.y"
    { (yyval.id) = "float"; }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 1609 "parse.y"
    { (yyval.id) = "double"; }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 1610 "parse.y"
    { (yyval.id) = "signed"; }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 1611 "parse.y"
    { (yyval.id) = "unsigned"; }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 1614 "parse.y"
    { (yyval.id) = "struct"; }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 1615 "parse.y"
    { (yyval.id) = "union"; }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1616 "parse.y"
    { (yyval.id) = "enum"; }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 1619 "parse.y"
    { (yyval.id) = g_strdup("*"); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 1620 "parse.y"
    { (yyval.id) = g_strdup("* const"); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 1621 "parse.y"
    {
				(yyval.id) = g_strconcat("*", (yyvsp[(2) - (2)].id), NULL);
				g_free((yyvsp[(2) - (2)].id));
					}
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 1625 "parse.y"
    {
				(yyval.id) = g_strconcat("* const", (yyvsp[(3) - (3)].id), NULL);
				g_free((yyvsp[(3) - (3)].id));
					}
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 1632 "parse.y"
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

  case 132:

/* Line 1806 of yacc.c  */
#line 1644 "parse.y"
    {
			(yyval.sigtype) = SIGNAL_LAST_METHOD;
					}
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 1650 "parse.y"
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

  case 134:

/* Line 1806 of yacc.c  */
#line 1662 "parse.y"
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

  case 135:

/* Line 1806 of yacc.c  */
#line 1674 "parse.y"
    {
			(yyval.sigtype) = SIGNAL_LAST_METHOD;
					}
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 1677 "parse.y"
    {
			/* the_scope was default thus public */
			the_scope = PUBLIC_SCOPE;
					}
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 1683 "parse.y"
    {
			gtktypes = g_list_prepend(gtktypes, debool ((yyvsp[(1) - (4)].id)));
						}
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 1688 "parse.y"
    {
			gtktypes = g_list_append(gtktypes, debool ((yyvsp[(3) - (3)].id)));
						}
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 1691 "parse.y"
    { 
			gtktypes = g_list_append(gtktypes, debool ((yyvsp[(1) - (1)].id)));
       						}
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 1696 "parse.y"
    { (yyval.cbuf) = (yyvsp[(2) - (2)].cbuf); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 1697 "parse.y"
    { (yyval.cbuf) = NULL; }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 1701 "parse.y"
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

  case 143:

/* Line 1806 of yacc.c  */
#line 1724 "parse.y"
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

  case 144:

/* Line 1806 of yacc.c  */
#line 1747 "parse.y"
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

  case 145:

/* Line 1806 of yacc.c  */
#line 1770 "parse.y"
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

  case 146:

/* Line 1806 of yacc.c  */
#line 1793 "parse.y"
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

  case 147:

/* Line 1806 of yacc.c  */
#line 1811 "parse.y"
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

  case 148:

/* Line 1806 of yacc.c  */
#line 1824 "parse.y"
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

  case 149:

/* Line 1806 of yacc.c  */
#line 1834 "parse.y"
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

  case 150:

/* Line 1806 of yacc.c  */
#line 1874 "parse.y"
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

  case 151:

/* Line 1806 of yacc.c  */
#line 1886 "parse.y"
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

  case 152:

/* Line 1806 of yacc.c  */
#line 1906 "parse.y"
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

  case 153:

/* Line 1806 of yacc.c  */
#line 1937 "parse.y"
    {
			g_free(funcattrs); funcattrs = NULL;
			g_free(onerror); onerror = NULL;
			g_free(defreturn); defreturn = NULL;
					}
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 1944 "parse.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 1945 "parse.y"
    {
			(yyval.id) = ((yyvsp[(2) - (2)].cbuf))->str;
			g_string_free((yyvsp[(2) - (2)].cbuf), FALSE);
					}
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 1951 "parse.y"
    { vararg = FALSE; has_self = FALSE; }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 1952 "parse.y"
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

  case 158:

/* Line 1806 of yacc.c  */
#line 1963 "parse.y"
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

  case 159:

/* Line 1806 of yacc.c  */
#line 1974 "parse.y"
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

  case 160:

/* Line 1806 of yacc.c  */
#line 1985 "parse.y"
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

  case 161:

/* Line 1806 of yacc.c  */
#line 1995 "parse.y"
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

  case 162:

/* Line 1806 of yacc.c  */
#line 2005 "parse.y"
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

  case 163:

/* Line 1806 of yacc.c  */
#line 2015 "parse.y"
    { has_self = FALSE; }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 2018 "parse.y"
    { vararg = TRUE; }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 2019 "parse.y"
    { vararg = FALSE; }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 2022 "parse.y"
    { ; }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 2023 "parse.y"
    { ; }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 2026 "parse.y"
    {
			push_funcarg((yyvsp[(2) - (2)].id),NULL);
								}
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 2029 "parse.y"
    {
			push_funcarg((yyvsp[(2) - (3)].id),(yyvsp[(3) - (3)].id));
								}
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 2032 "parse.y"
    {
			if(strcmp((yyvsp[(4) - (6)].id),"check")!=0) {
				yyerror(_("parse error"));
				YYERROR;
			}
			g_free((yyvsp[(4) - (6)].id));
			push_funcarg((yyvsp[(2) - (6)].id),NULL);
								}
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 2040 "parse.y"
    {
			if(strcmp((yyvsp[(5) - (7)].id),"check")!=0) {
				yyerror(_("parse error"));
				YYERROR;
			}
			g_free((yyvsp[(5) - (7)].id));
			push_funcarg((yyvsp[(2) - (7)].id),(yyvsp[(3) - (7)].id));
								}
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 2050 "parse.y"
    { ; }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 2051 "parse.y"
    { ; }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 2054 "parse.y"
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

  case 175:

/* Line 1806 of yacc.c  */
#line 2071 "parse.y"
    {
			Node *node = node_new (CHECK_NODE,
					       "chtype", GT_CHECK,
					       "number:steal", (yyvsp[(2) - (2)].id),
					       NULL);
			checks = g_list_append(checks,node);
					}
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 2078 "parse.y"
    {
			Node *node = node_new (CHECK_NODE,
					       "chtype", LT_CHECK,
					       "number:steal", (yyvsp[(2) - (2)].id),
					       NULL);
			checks = g_list_append(checks,node);
					}
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 2085 "parse.y"
    {
			Node *node = node_new (CHECK_NODE,
					       "chtype", GE_CHECK,
					       "number:steal", (yyvsp[(3) - (3)].id),
					       NULL);
			checks = g_list_append(checks,node);
					}
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 2092 "parse.y"
    {
			Node *node = node_new (CHECK_NODE,
					       "chtype", LE_CHECK,
					       "number:steal", (yyvsp[(3) - (3)].id),
					       NULL);
			checks = g_list_append(checks,node);
					}
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 2099 "parse.y"
    {
			Node *node = node_new (CHECK_NODE,
					       "chtype", EQ_CHECK,
					       "number:steal", (yyvsp[(3) - (3)].id),
					       NULL);
			checks = g_list_append(checks,node);
					}
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 2106 "parse.y"
    {
			Node *node = node_new (CHECK_NODE,
					       "chtype", NE_CHECK,
					       "number:steal", (yyvsp[(3) - (3)].id),
					       NULL);
			checks = g_list_append(checks,node);
					}
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 2115 "parse.y"
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

  case 182:

/* Line 1806 of yacc.c  */
#line 2124 "parse.y"
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

  case 183:

/* Line 1806 of yacc.c  */
#line 2135 "parse.y"
    {;}
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 2136 "parse.y"
    {;}
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 2139 "parse.y"
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

  case 186:

/* Line 1806 of yacc.c  */
#line 2159 "parse.y"
    {
			Node *node;

			node = node_new (ENUMVALUE_NODE,
					 "name:steal", (yyvsp[(1) - (1)].id),
					 NULL);
			enum_vals = g_list_append (enum_vals, node);
	}
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 2169 "parse.y"
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

  case 188:

/* Line 1806 of yacc.c  */
#line 2178 "parse.y"
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

  case 189:

/* Line 1806 of yacc.c  */
#line 2189 "parse.y"
    {
			flag_vals = g_list_append (flag_vals, (yyvsp[(3) - (3)].id));
		}
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 2192 "parse.y"
    {
			flag_vals = g_list_append (flag_vals, (yyvsp[(1) - (1)].id));
		}
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 2197 "parse.y"
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

  case 192:

/* Line 1806 of yacc.c  */
#line 2206 "parse.y"
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

  case 193:

/* Line 1806 of yacc.c  */
#line 2217 "parse.y"
    {
			error_vals = g_list_append (error_vals, (yyvsp[(3) - (3)].id));
		}
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 2220 "parse.y"
    {
			error_vals = g_list_append (error_vals, (yyvsp[(1) - (1)].id));
		}
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 2226 "parse.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 2227 "parse.y"
    {
			(yyval.id) = g_strconcat("-",(yyvsp[(2) - (2)].id),NULL);
			g_free((yyvsp[(2) - (2)].id));
					}
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 2231 "parse.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 2232 "parse.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;



/* Line 1806 of yacc.c  */
#line 5142 "parse.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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
      if (!yypact_value_is_default (yyn))
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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



/* Line 2067 of yacc.c  */
#line 2235 "parse.y"


