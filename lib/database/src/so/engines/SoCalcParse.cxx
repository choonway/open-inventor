#include <inventor.h>
#include <Inventor/misc/SoBasic.h>
#include <Inventor/errors/SoDebugError.h>
#include "SoCalcExpr.h"
#include <stdio.h>
#ifndef WIN32
#include <values.h>
#else
#include <float.h>
#define MINFLOAT FLT_MIN
#ifndef MAXFLOAT
#define MAXFLOAT FLT_MAX
#define __cplusplus
#endif
#endif
#include <math.h>
#include <ctype.h>
#ifndef WIN32
#include <strings.h>
#endif
#include <stdlib.h>
void yyerror(const char *);
extern "C" int	yylex();
int yyparse();

static const char *In;
static ExprList	*EList;

static const struct {
    const char *name;
    float	val;
} Constants[] = {
    { "MAXFLOAT",	MAXFLOAT },
    { "MINFLOAT",	MINFLOAT },
    { "M_E",		M_E },
    { "M_LOG2E",	M_LOG2E },
    { "M_LOG10E",	M_LOG10E },
    { "M_LN2",		M_LN2 },
    { "M_LN10",		M_LN10 },
    { "M_PI",		M_PI },
    { "M_SQRT2",	M_SQRT2 },
    { "M_SQRT1_2",	M_SQRT1_2 },
};
#define NCONSTANTS (sizeof(Constants)/sizeof(Constants[0]))

static const struct {
    const char *name;
    Expr::Type	type;
} Inputs[] = {
    { "a", Expr::FLOAT}, { "b", Expr::FLOAT},
    { "c", Expr::FLOAT}, { "d", Expr::FLOAT},
    { "e", Expr::FLOAT}, { "f", Expr::FLOAT},
    { "g", Expr::FLOAT}, { "h", Expr::FLOAT},
    { "A", Expr::VEC3F}, { "B", Expr::VEC3F},
    { "C", Expr::VEC3F}, { "D", Expr::VEC3F},
    { "E", Expr::VEC3F}, { "F", Expr::VEC3F},
    { "G", Expr::VEC3F}, { "H", Expr::VEC3F},
}, Outputs[] = {
    { "oa", Expr::FLOAT}, { "ob", Expr::FLOAT},
    { "oc", Expr::FLOAT}, { "od", Expr::FLOAT},
    { "oA", Expr::VEC3F}, { "oB", Expr::VEC3F},
    { "oC", Expr::VEC3F}, { "oD", Expr::VEC3F},
}, Vars[] = {
    { "ta", Expr::FLOAT}, { "tb", Expr::FLOAT},
    { "tc", Expr::FLOAT}, { "td", Expr::FLOAT},
    { "te", Expr::FLOAT}, { "tf", Expr::FLOAT},
    { "tg", Expr::FLOAT}, { "th", Expr::FLOAT},
    { "tA", Expr::VEC3F}, { "tB", Expr::VEC3F},
    { "tC", Expr::VEC3F}, { "tD", Expr::VEC3F},
    { "tE", Expr::VEC3F}, { "tF", Expr::VEC3F},
    { "tG", Expr::VEC3F}, { "tH", Expr::VEC3F},
};
#define NINPUTS (sizeof(Inputs)/sizeof(Inputs[0]))
#define NOUTPUTS (sizeof(Outputs)/sizeof(Outputs[0]))
#define NVARS (sizeof(Vars)/sizeof(Vars[0]))

#ifdef WIN32
#define drand48() (((double)rand())/double(RAND_MAX))
#endif
static double myrand(double max1) { return max1 * drand48(); }
static SbVec3f cross(const SbVec3f &a, const SbVec3f &b) { return a.cross(b); }
static double dot(const SbVec3f &a, const SbVec3f &b) { return a.dot(b); }
static double length(const SbVec3f &a) { return a.length(); }
static SbVec3f normalize(const SbVec3f &v) { SbVec3f t=v; t.normalize(); return t; }
static SbVec3f vec3f(double a, double b, double c) { return SbVec3f(a,b,c); }

// Keep this up to date with the info in initFuncs()
#define NFUNCS 25

static struct {
    const Func *func;
} Funcs[NFUNCS];


# line 104 "SoCalcParse.y"
typedef union
#ifdef __cplusplus
	YYSTYPE
#endif

{
    Expr	*expr;
    ExprList	*list;
} YYSTYPE;
#ifdef WIN32
#undef CONST
#endif
# define LEXERR 257
# define CONST 258
# define FUNC 259
# define INPUT 260
# define OUTPUT 261
# define VAR 262
# define OROR 263
# define ANDAND 264
# define GEQ 265
# define LEQ 266
# define EQEQ 267
# define NEQ 268

#include <malloc.h>
#include <memory.h>
#ifndef WIN32
#include <unistd.h>
#include <values.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef WIN32
extern char *gettxt(const char *, const char *);
#else
#define gettxt(a,b) (a)
#endif
#if !defined(yylex) && !defined(__my_yylex)
	extern int yylex(void);
#endif

#ifdef __cplusplus
}
#endif

#if (defined(__cplusplus) || defined(_XOPEN_SOURCE)) && !defined(yyerror) && !defined(__my_yyerror)
	void yyerror(const char *);
#endif
int yyparse(void);
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern int yyerrflag;
YYSTYPE yylval;
YYSTYPE yyval;
typedef int yytabelem;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
#if YYMAXDEPTH > 0
int yy_yys[YYMAXDEPTH], *yys = yy_yys;
YYSTYPE yy_yyv[YYMAXDEPTH], *yyv = yy_yyv;
#else	/* user does initial allocation */
int *yys;
YYSTYPE *yyv;
#endif
static int yymaxdepth = YYMAXDEPTH;
# define YYERRCODE 256

# line 220 "SoCalcParse.y"


//
// The static Funcs array contains instances of objects that have
// constructors. Since this wouldn't get set up correctly in a DSO, we
// have to initialize the array at run-time.
//

static void
initFuncs()
{
    int	i = 0;

#define MAKEFUNC(CLASS, NAME)						      \
	Funcs[i++].func = new CLASS(SO__QUOTE(NAME),NAME)

    MAKEFUNC(Func_d, acos);
    MAKEFUNC(Func_d, asin);
    MAKEFUNC(Func_d, atan);
    MAKEFUNC(Func_dd, atan2);
    MAKEFUNC(Func_d, ceil);
    MAKEFUNC(Func_d, cos);
    MAKEFUNC(Func_d, cosh);
    MAKEFUNC(Funcv_vv, cross);
    MAKEFUNC(Func_vv, dot);
    MAKEFUNC(Func_d, exp);
    MAKEFUNC(Func_d, fabs);
    MAKEFUNC(Func_d, floor);
    MAKEFUNC(Func_dd, fmod);
    MAKEFUNC(Func_v, length);
    MAKEFUNC(Func_d, log);
    MAKEFUNC(Func_d, log10);
    MAKEFUNC(Funcv_v, normalize);
    MAKEFUNC(Func_dd, pow);
    MAKEFUNC(Func_d, myrand);
    MAKEFUNC(Func_d, sin);
    MAKEFUNC(Func_d, sinh);
    MAKEFUNC(Func_d, sqrt);
    MAKEFUNC(Func_d, tan);
    MAKEFUNC(Func_d, tanh);
    MAKEFUNC(Funcv_ddd, vec3f);

#ifdef DEBUG
    // Sanity check
    if (i != NFUNCS)
	SoDebugError::post("SoCalcParse initFuncs (internal)",
			   "Wrong number of functions declared");
#endif /* DEBUG */
}

static Const *
isConst(const char *nm)
{
    for (int i=0; i<NCONSTANTS; i++)
	if (strcmp(nm, Constants[i].name)==0)
	    return new Const(Constants[i].val);
    return NULL;
}

static Func *
isFunc(const char *nm)
{
    for (int i=0; i<NFUNCS; i++) {
	const Func *f = Funcs[i].func;
	if (strcmp(nm, f->name)==0)
	    return f->dup();
    }
    return NULL;
}

static Var *
isInput(const char *nm)
{
    for (int i=0; i<NINPUTS; i++) if (strcmp(nm, Inputs[i].name)==0) 
	return new Var(nm, Inputs[i].type);
    return NULL;
}

static Var *
isOutput(const char *nm)
{
    for (int i=0; i<NOUTPUTS; i++) if (strcmp(nm, Outputs[i].name)==0) 
	return new Var(nm, Outputs[i].type);
    return NULL;
}

static Var *
isVar(const char *nm)
{
    for (int i=0; i<NVARS; i++) if (strcmp(nm, Vars[i].name)==0) 
	return new Var(nm, Vars[i].type);
    return NULL;
}

int yylex()
{
#define BSZ 100
    char c, buf[BSZ+1], *cp = buf;

    // skip over blanks
    while (isspace(*In))
	In++;

    if (!In[0])
	return EOF;

    if (isdigit(In[0]) || In[0] == '.') {

	// skip past a valid floating-point number
	// (don't need to compute the number, will
	// use atof() to do that).
	SbBool dot = FALSE;
	SbBool exp = FALSE;
	for (;;) {
	    c = *In++;
	    if (cp - buf < BSZ)
		*cp++ = c;
	    *cp = c;
	    if (isdigit(c))
		continue;
	    if (c== '.') {
		if (dot || exp)
		    return LEXERR;
		dot = TRUE;
		continue;
	    }
	    if (c == 'e' || c == 'E') {
		if (exp)
		    return LEXERR;
		exp = TRUE;
		continue;
	    }
	    // Check for negative exponent
	    if (c == '-' && exp && (In[-2] == 'e' || In[-2] == 'E')) {
		continue;
	    }
	    break;	// end of number
	}
	if (In[-1] == 'e')
	    return LEXERR;

	*cp = 0;
	In--;	// push back last character "read"

	yylval.expr = new Const(atof(buf));
	return CONST;
    }

    if (isalpha(In[0])) {
	while (isalnum(In[0]) || In[0] == '_') {
	    if (cp - buf < BSZ)
		*cp++ = *In++;
	}
	*cp = 0;

	if (yylval.expr = isConst(buf))
	    return CONST;

	if (yylval.expr = isFunc(buf))
	    return FUNC;

	if (yylval.expr = isInput(buf))
	    return INPUT;

	if (yylval.expr = isOutput(buf))
	    return OUTPUT;

	if (yylval.expr = isVar(buf))
	    return VAR;

    }

#define EQ2(x,y)	(x[0]==y[0] && x[1]==y[1])
    if (EQ2(In, "==")) { In += 2; return EQEQ; }
    if (EQ2(In, "!=")) { In += 2; return NEQ; }
    if (EQ2(In, ">=")) { In += 2; return GEQ; }
    if (EQ2(In, "<=")) { In += 2; return LEQ; }
    if (EQ2(In, "&&")) { In += 2; return ANDAND; }
    if (EQ2(In, "||")) { In += 2; return OROR; }

    return *In++;
}

void
yyerror(const char *)
{
    // printf("parse error: %s\n", s);
}

SbBool
SoCalcParse(ExprList *elist, const char *buf)
{
    static SbBool initted = FALSE;

    if (! initted) {
	initFuncs();
	initted = TRUE;
    }

    In = buf;
    EList = elist;
    return(yyparse());
}

#ifdef TESTMAIN

void
main()
{
    char buf[1000];
#if YYDEBUG
    extern int yydebug;
    yydebug = 1;
#endif
    EList = new ExprList;

    while (gets(buf)) {
	In = buf;
	EList->truncate(0);
	if (yyparse())
	    printf("Parse error.\n");
	else {
	    EList->eval();
	    for (int i=0; i<EList->length(); i++) {
		(*EList)[i]->pr();
	    }
	}
    }
}

#endif
yytabelem yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
	};
# define YYNPROD 42
# define YYLAST 230
yytabelem yyact[]={

    21,    37,    34,    38,    35,    36,    74,    28,    33,     3,
     4,    52,    20,    51,     8,     6,    46,    11,    72,    71,
     5,    73,    16,    17,    45,    29,    30,    31,    18,    43,
    70,    41,    75,    42,    44,    76,    49,    13,     1,    15,
    68,     2,    14,    12,     9,     7,    50,    10,    19,    47,
    48,    54,    22,     0,     0,     0,     0,     0,     0,     0,
    58,    59,    60,    61,    67,    62,    63,    69,     0,     0,
    53,     0,    64,    65,    66,    56,    57,    55,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    77,
    78,    79,     0,     0,    80,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    40,    39,    32,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    24,    23,    25,    26,    27 };
yytabelem yypact[]={

  -252,   -39,-10000000,   -46,   -47,  -252,   -33,   -33,   -33,   -33,
-10000000,-10000000,   -55,  -262,  -263,   -59,   -12,   -13,-10000000,   -75,
   -33,   -33,-10000000,    -4,-10000000,-10000000,-10000000,-10000000,   -33,   -80,
-10000000,   -82,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,
   -33,   -33,   -33,   -33,   -33,   -33,   -33,-10000000,-10000000,   -33,
   -11,   -42,   -43,  -262,   -37,  -263,   -59,   -59,   -12,   -12,
   -12,   -12,   -13,   -13,-10000000,-10000000,-10000000,   -87,    -9,-10000000,
-10000000,   -33,   -33,   -33,-10000000,-10000000,   -33,-10000000,-10000000,-10000000,
-10000000 };
yytabelem yypgo[]={

     0,    41,    52,    48,    28,    23,    22,    39,    42,    37,
    43,    17,    40,    38 };
yytabelem yyr1[]={

     0,    13,    13,    13,     1,     1,     1,     1,     2,     2,
     2,     2,     2,     3,     3,     3,    12,    12,     4,     4,
     4,     5,     5,     5,     5,     6,     6,     6,     7,     7,
     7,     7,     7,     8,     8,     8,     9,     9,    10,    10,
    11,    11 };
yytabelem yyr2[]={

     0,     3,     7,     4,     7,    13,     7,    13,     3,     3,
     3,     3,     7,     3,     9,     9,     3,     7,     2,     5,
     5,     2,     7,     7,     7,     2,     7,     7,     2,     7,
     7,     7,     7,     2,     7,     7,     2,     7,     2,     7,
     2,    11 };
yytabelem yychk[]={

-10000000,   -13,    -1,   261,   262,    59,    61,    91,    61,    91,
    -1,   -11,   -10,    -9,    -8,    -7,    -6,    -5,    -4,    -3,
    45,    33,    -2,   259,   258,   260,   261,   262,    40,   -11,
   -11,   -11,   263,    63,   264,   267,   268,    60,    62,   266,
   265,    43,    45,    42,    47,    37,    91,    -4,    -4,    40,
   -11,    93,    93,    -9,   -11,    -8,    -7,    -7,    -6,    -6,
    -6,    -6,    -5,    -5,    -4,    -4,    -4,   -11,   -12,   -11,
    41,    61,    61,    58,    93,    41,    44,   -11,   -11,   -11,
   -11 };
yytabelem yydef[]={

     0,    -2,     1,     0,     0,     3,     0,     0,     0,     0,
     2,     4,    40,    38,    36,    33,    28,    25,    21,    18,
     0,     0,    13,     0,     8,     9,    10,    11,     0,     0,
     6,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    19,    20,     0,
     0,     0,     0,    39,     0,    37,    34,    35,    29,    30,
    31,    32,    26,    27,    22,    23,    24,     0,     0,    16,
    12,     0,     0,     0,    14,    15,     0,     5,     7,    41,
    17 };
typedef struct
#ifdef __cplusplus
	yytoktype
#endif
{ char *t_name; int t_val; } yytoktype;
#ifndef YYDEBUG
#	define YYDEBUG	0	/* don't allow debugging */
#endif

#if YYDEBUG

yytoktype yytoks[] =
{
	"LEXERR",	257,
	"CONST",	258,
	"FUNC",	259,
	"INPUT",	260,
	"OUTPUT",	261,
	"VAR",	262,
	"OROR",	263,
	"ANDAND",	264,
	"GEQ",	265,
	"LEQ",	266,
	"EQEQ",	267,
	"NEQ",	268,
	"-unknown-",	-1	/* ends search */
};

char * yyreds[] =
{
	"-no such reduction-",
	"asgnlist : asgn",
	"asgnlist : asgnlist ';' asgn",
	"asgnlist : asgnlist ';'",
	"asgn : OUTPUT '=' conditional_expression",
	"asgn : OUTPUT '[' conditional_expression ']' '=' conditional_expression",
	"asgn : VAR '=' conditional_expression",
	"asgn : VAR '[' conditional_expression ']' '=' conditional_expression",
	"primary_expression : CONST",
	"primary_expression : INPUT",
	"primary_expression : OUTPUT",
	"primary_expression : VAR",
	"primary_expression : '(' conditional_expression ')'",
	"postfix_expression : primary_expression",
	"postfix_expression : postfix_expression '[' conditional_expression ']'",
	"postfix_expression : FUNC '(' args ')'",
	"args : conditional_expression",
	"args : args ',' conditional_expression",
	"unary_expression : postfix_expression",
	"unary_expression : '-' unary_expression",
	"unary_expression : '!' unary_expression",
	"multiplicative_expression : unary_expression",
	"multiplicative_expression : multiplicative_expression '*' unary_expression",
	"multiplicative_expression : multiplicative_expression '/' unary_expression",
	"multiplicative_expression : multiplicative_expression '%' unary_expression",
	"additive_expression : multiplicative_expression",
	"additive_expression : additive_expression '+' multiplicative_expression",
	"additive_expression : additive_expression '-' multiplicative_expression",
	"relational_expression : additive_expression",
	"relational_expression : relational_expression '<' additive_expression",
	"relational_expression : relational_expression '>' additive_expression",
	"relational_expression : relational_expression LEQ additive_expression",
	"relational_expression : relational_expression GEQ additive_expression",
	"equality_expression : relational_expression",
	"equality_expression : equality_expression EQEQ relational_expression",
	"equality_expression : equality_expression NEQ relational_expression",
	"logical_AND_expression : equality_expression",
	"logical_AND_expression : logical_AND_expression ANDAND equality_expression",
	"logical_OR_expression : logical_AND_expression",
	"logical_OR_expression : logical_OR_expression OROR logical_AND_expression",
	"conditional_expression : logical_OR_expression",
	"conditional_expression : logical_OR_expression '?' conditional_expression ':' conditional_expression",
};
#endif /* YYDEBUG */
/* 
 *	Copyright 1987 Silicon Graphics, Inc. - All Rights Reserved
 */

/* #ident	"@(#)yacc:yaccpar	1.10" */
#ident	"$Revision: 1.11 $"

/*
** Skeleton parser driver for yacc output
*/
#include "stddef.h"

/*
** yacc user known macros and defines
*/
#define YYERROR		goto yyerrlab
#define YYACCEPT	return(0)
#define YYABORT		return(1)
#ifdef __cplusplus
#define YYBACKUP( newtoken, newvalue )\
{\
	if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
	{\
		yyerror( gettxt("uxlibc:78", "syntax error - cannot backup") );\
		goto yyerrlab;\
	}\
	yychar = newtoken;\
	yystate = *yyps;\
	yylval = newvalue;\
	goto yynewstate;\
}
#else
#define YYBACKUP( newtoken, newvalue )\
{\
	if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
	{\
		yyerror( gettxt("uxlibc:78", "Syntax error - cannot backup") );\
		goto yyerrlab;\
	}\
	yychar = newtoken;\
	yystate = *yyps;\
	yylval = newvalue;\
	goto yynewstate;\
}
#endif
#define YYRECOVERING()	(!!yyerrflag)
#define YYNEW(type)	malloc((size_t)(sizeof(type) * yynewmax))
#define YYCOPY(to, from, type) \
	(type *) memcpy(to, (char *) from, (size_t)(yynewmax * sizeof(type)))
#define YYENLARGE( from, type) \
	(type *) realloc((char *) from, (size_t)(yynewmax * sizeof(type)))
#ifndef YYDEBUG
#	define YYDEBUG	1	/* make debugging available */
#endif

/*
** user known globals
*/
int yydebug;			/* set to 1 to get debugging */

/*
** driver internal defines
*/
#define YYFLAG		(-10000000)

/*
** global variables used by the parser
*/
YYSTYPE *yypv;			/* top of value stack */
int *yyps;			/* top of state stack */

int yystate;			/* current state */
int yytmp;			/* extra var (lasts between blocks) */

int yynerrs;			/* number of errors */
int yyerrflag;			/* error recovery flag */
int yychar;			/* current input token number */



/*
** yyparse - return 0 if worked, 1 if syntax error not recovered from
*/
#if defined(__STDC__) || defined(__cplusplus)
int yyparse(void)
#else
int yyparse()
#endif
{
	register YYSTYPE *yypvt;	/* top of value stack for $vars */

	/*
	** Initialize externals - yyparse may be called more than once
	*/
	yypv = &yyv[-1];
	yyps = &yys[-1];
	yystate = 0;
	yytmp = 0;
	yynerrs = 0;
	yyerrflag = 0;
	yychar = -1;

#if YYMAXDEPTH <= 0
	if (yymaxdepth <= 0)
	{
		if ((yymaxdepth = YYEXPAND(0)) <= 0)
		{
#ifdef __cplusplus
			yyerror(gettxt("uxlibc:79", "yacc initialization error"));
#else
			yyerror(gettxt("uxlibc:79", "Yacc initialization error"));
#endif
			YYABORT;
		}
	}
#endif

	goto yystack;
	{
		register YYSTYPE *yy_pv;	/* top of value stack */
		register int *yy_ps;		/* top of state stack */
		register int yy_state;		/* current state */
		register int  yy_n;		/* internal state number info */

		/*
		** get globals into registers.
		** branch to here only if YYBACKUP was called.
		*/
	yynewstate:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;
		goto yy_newstate;

		/*
		** get globals into registers.
		** either we just started, or we just finished a reduction
		*/
	yystack:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;

		/*
		** top of for (;;) loop while no reductions done
		*/
	yy_stack:
		/*
		** put a state and value onto the stacks
		*/
#if YYDEBUG
		/*
		** if debugging, look up token value in list of value vs.
		** name pairs.  0 and negative (-1) are special values.
		** Note: linear search is used since time is not a real
		** consideration while debugging.
		*/
		if ( yydebug )
		{
			register int yy_i;

			printf( "State %d, token ", yy_state );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ++yy_ps >= &yys[ yymaxdepth ] )	/* room on stack? */
		{
			int yynewmax;
			ptrdiff_t yys_off;

			/* The following pointer-differences are safe, since
			 * yypvt, yy_pv, and yypv all are a multiple of
			 * sizeof(YYSTYPE) bytes from yyv.
			 */
			ptrdiff_t yypvt_off = yypvt - yyv;
			ptrdiff_t yy_pv_off = yy_pv - yyv;
			ptrdiff_t yypv_off = yypv - yyv;

			int *yys_base = yys;
#ifdef YYEXPAND
			yynewmax = YYEXPAND(yymaxdepth);
#else
			yynewmax = 2 * yymaxdepth;	/* double table size */
			if (yymaxdepth == YYMAXDEPTH)	/* first time growth */
			{
				void *newyys = YYNEW(int);
				void *newyyv = YYNEW(YYSTYPE);
				if (newyys != 0 && newyyv != 0)
				{
					yys = YYCOPY(newyys, yys, int);
					yyv = YYCOPY(newyyv, yyv, YYSTYPE);
				}
				else
					yynewmax = 0;	/* failed */
			}
			else				/* not first time */
			{
				yys = YYENLARGE(yys, int);
				yyv = YYENLARGE(yyv, YYSTYPE);
				if (yys == 0 || yyv == 0)
					yynewmax = 0;	/* failed */
			}
#endif
			if (yynewmax <= yymaxdepth)	/* tables not expanded */
			{
#ifdef __cplusplus
				yyerror( gettxt("uxlibc:80", "yacc stack overflow") );
#else
				yyerror( gettxt("uxlibc:80", "Yacc stack overflow") );
#endif
				YYABORT;
			}
			yymaxdepth = yynewmax;

			/* reset pointers into yys */
			yys_off = yys - yys_base;
			yy_ps = yy_ps + yys_off;
			yyps = yyps + yys_off;

			/* reset pointers into yyv */
			yypvt = yyv + yypvt_off;
			yy_pv = yyv + yy_pv_off;
			yypv = yyv + yypv_off;
		}
		*yy_ps = yy_state;
		*++yy_pv = yyval;

		/*
		** we have a new state - find out what to do
		*/
	yy_newstate:
		if ( ( yy_n = yypact[ yy_state ] ) <= YYFLAG )
			goto yydefault;		/* simple state */
#if YYDEBUG
		/*
		** if debugging, need to mark whether new token grabbed
		*/
		yytmp = yychar < 0;
#endif
		if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
			yychar = 0;		/* reached EOF */
#if YYDEBUG
		if ( yydebug && yytmp )
		{
			register int yy_i;

			printf( "Received token " );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ( ( yy_n += yychar ) < 0 ) || ( yy_n >= YYLAST ) )
			goto yydefault;
		if ( yychk[ yy_n = yyact[ yy_n ] ] == yychar )	/*valid shift*/
		{
			yychar = -1;
			yyval = yylval;
			yy_state = yy_n;
			if ( yyerrflag > 0 )
				yyerrflag--;
			goto yy_stack;
		}

	yydefault:
		if ( ( yy_n = yydef[ yy_state ] ) == -2 )
		{
#if YYDEBUG
			yytmp = yychar < 0;
#endif
			if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
				yychar = 0;		/* reached EOF */
#if YYDEBUG
			if ( yydebug && yytmp )
			{
				register int yy_i;

				printf( "Received token " );
				if ( yychar == 0 )
					printf( "end-of-file\n" );
				else if ( yychar < 0 )
					printf( "-none-\n" );
				else
				{
					for ( yy_i = 0;
						yytoks[yy_i].t_val >= 0;
						yy_i++ )
					{
						if ( yytoks[yy_i].t_val
							== yychar )
						{
							break;
						}
					}
					printf( "%s\n", yytoks[yy_i].t_name );
				}
			}
#endif /* YYDEBUG */
			/*
			** look through exception table
			*/
			{
				register int *yyxi = yyexca;

				while ( ( *yyxi != -1 ) ||
					( yyxi[1] != yy_state ) )
				{
					yyxi += 2;
				}
				while ( ( *(yyxi += 2) >= 0 ) &&
					( *yyxi != yychar ) )
					;
				if ( ( yy_n = yyxi[1] ) < 0 )
					YYACCEPT;
			}
		}

		/*
		** check for syntax error
		*/
		if ( yy_n == 0 )	/* have an error */
		{
			/* no worry about speed here! */
			switch ( yyerrflag )
			{
			case 0:		/* new error */
#ifdef __cplusplus
				yyerror( gettxt("uxlibc:81", "syntax error") );
#else
				yyerror( gettxt("uxlibc:81", "Syntax error") );
#endif
				goto skip_init;
			yyerrlab:
				/*
				** get globals into registers.
				** we have a user generated syntax type error
				*/
				yy_pv = yypv;
				yy_ps = yyps;
				yy_state = yystate;
				yynerrs++;
				/* FALLTHRU */
			skip_init:
			case 1:
			case 2:		/* incompletely recovered error */
					/* try again... */
				yyerrflag = 3;
				/*
				** find state where "error" is a legal
				** shift action
				*/
				while ( yy_ps >= yys )
				{
					yy_n = yypact[ *yy_ps ] + YYERRCODE;
					if ( yy_n >= 0 && yy_n < YYLAST &&
						yychk[yyact[yy_n]] == YYERRCODE)					{
						/*
						** simulate shift of "error"
						*/
						yy_state = yyact[ yy_n ];
						goto yy_stack;
					}
					/*
					** current state has no shift on
					** "error", pop stack
					*/
#if YYDEBUG
#	define _POP_ "Error recovery pops state %d, uncovers state %d\n"
					if ( yydebug )
						printf( _POP_, *yy_ps,
							yy_ps[-1] );
#	undef _POP_
#endif
					yy_ps--;
					yy_pv--;
				}
				/*
				** there is no state on stack with "error" as
				** a valid shift.  give up.
				*/
				YYABORT;
			case 3:		/* no shift yet; eat a token */
#if YYDEBUG
				/*
				** if debugging, look up token in list of
				** pairs.  0 and negative shouldn't occur,
				** but since timing doesn't matter when
				** debugging, it doesn't hurt to leave the
				** tests here.
				*/
				if ( yydebug )
				{
					register int yy_i;

					printf( "Error recovery discards " );
					if ( yychar == 0 )
						printf( "token end-of-file\n" );
					else if ( yychar < 0 )
						printf( "token -none-\n" );
					else
					{
						for ( yy_i = 0;
							yytoks[yy_i].t_val >= 0;
							yy_i++ )
						{
							if ( yytoks[yy_i].t_val
								== yychar )
							{
								break;
							}
						}
						printf( "token %s\n",
							yytoks[yy_i].t_name );
					}
				}
#endif /* YYDEBUG */
				if ( yychar == 0 )	/* reached EOF. quit */
					YYABORT;
				yychar = -1;
				goto yy_newstate;
			}
		}/* end if ( yy_n == 0 ) */
		/*
		** reduction by production yy_n
		** put stack tops, etc. so things right after switch
		*/
#if YYDEBUG
		/*
		** if debugging, print the string that is the user's
		** specification of the reduction which is just about
		** to be done.
		*/
		if ( yydebug )
			printf( "Reduce by (%d) \"%s\"\n",
				yy_n, yyreds[ yy_n ] );
#endif
		yytmp = yy_n;			/* value to switch over */
		yypvt = yy_pv;			/* $vars top of value stack */
		/*
		** Look in goto table for next state
		** Sorry about using yy_state here as temporary
		** register variable, but why not, if it works...
		** If yyr2[ yy_n ] doesn't have the low order bit
		** set, then there is no action to be done for
		** this reduction.  So, no saving & unsaving of
		** registers done.  The only difference between the
		** code just after the if and the body of the if is
		** the goto yy_stack in the body.  This way the test
		** can be made before the choice of what to do is needed.
		*/
		{
			/* length of production doubled with extra bit */
			register int yy_len = yyr2[ yy_n ];

			if ( !( yy_len & 01 ) )
			{
				yy_len >>= 1;
				yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
				yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
					*( yy_ps -= yy_len ) + 1;
				if ( yy_state >= YYLAST ||
					yychk[ yy_state =
					yyact[ yy_state ] ] != -yy_n )
				{
					yy_state = yyact[ yypgo[ yy_n ] ];
				}
				goto yy_stack;
			}
			yy_len >>= 1;
			yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
			yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
				*( yy_ps -= yy_len ) + 1;
			if ( yy_state >= YYLAST ||
				yychk[ yy_state = yyact[ yy_state ] ] != -yy_n )
			{
				yy_state = yyact[ yypgo[ yy_n ] ];
			}
		}
					/* save until reenter driver code */
		yystate = yy_state;
		yyps = yy_ps;
		yypv = yy_pv;
	}
	/*
	** code supplied by user is placed in this switch
	*/
	switch( yytmp )
	{
		
case 1:
# line 121 "SoCalcParse.y"
{ EList->append(yypvt[-0].expr); } break;
case 2:
# line 122 "SoCalcParse.y"
{ EList->append(yypvt[-0].expr); } break;
case 4:
# line 128 "SoCalcParse.y"
{ yyval.expr = new Assign(yypvt[-2].expr, yypvt[-0].expr); } break;
case 5:
# line 130 "SoCalcParse.y"
{ yyval.expr = new AssignIndex(yypvt[-5].expr, yypvt[-3].expr, yypvt[-0].expr); } break;
case 6:
# line 132 "SoCalcParse.y"
{ yyval.expr = new Assign(yypvt[-2].expr, yypvt[-0].expr); } break;
case 7:
# line 134 "SoCalcParse.y"
{ yyval.expr = new AssignIndex(yypvt[-5].expr, yypvt[-3].expr, yypvt[-0].expr); } break;
case 8:
# line 138 "SoCalcParse.y"
{ yyval.expr = yypvt[-0].expr; } break;
case 9:
# line 139 "SoCalcParse.y"
{ yyval.expr = yypvt[-0].expr; } break;
case 10:
# line 140 "SoCalcParse.y"
{ yyval.expr = yypvt[-0].expr; } break;
case 11:
# line 141 "SoCalcParse.y"
{ yyval.expr = yypvt[-0].expr; } break;
case 12:
# line 142 "SoCalcParse.y"
{ yyval.expr = yypvt[-1].expr; } break;
case 13:
# line 146 "SoCalcParse.y"
{ yyval.expr = yypvt[-0].expr; } break;
case 14:
# line 148 "SoCalcParse.y"
{ yyval.expr = new Index(yypvt[-3].expr, yypvt[-1].expr); } break;
case 15:
# line 149 "SoCalcParse.y"
{ ((Func *)yypvt[-3].expr)->setArgs(yypvt[-1].list); yyval.expr = yypvt[-3].expr; } break;
case 16:
# line 153 "SoCalcParse.y"
{ (yyval.list = new ExprList)->append(yypvt[-0].expr); } break;
case 17:
# line 154 "SoCalcParse.y"
{ yypvt[-2].list->append(yypvt[-0].expr); yyval.list = yypvt[-2].list; } break;
case 19:
# line 159 "SoCalcParse.y"
{ yyval.expr = new Negate(yypvt[-0].expr); } break;
case 20:
# line 160 "SoCalcParse.y"
{ yyval.expr = new Not(yypvt[-0].expr); } break;
case 22:
# line 166 "SoCalcParse.y"
{ yyval.expr = new Mult(yypvt[-2].expr, yypvt[-0].expr); } break;
case 23:
# line 168 "SoCalcParse.y"
{ yyval.expr = new Divide(yypvt[-2].expr, yypvt[-0].expr); } break;
case 24:
# line 170 "SoCalcParse.y"
{ yyval.expr = new Mod(yypvt[-2].expr, yypvt[-0].expr); } break;
case 26:
# line 176 "SoCalcParse.y"
{ yyval.expr = new Plus(yypvt[-2].expr, yypvt[-0].expr); } break;
case 27:
# line 178 "SoCalcParse.y"
{ yyval.expr = new Minus(yypvt[-2].expr, yypvt[-0].expr); } break;
case 29:
# line 184 "SoCalcParse.y"
{ yyval.expr = new LessThan(yypvt[-2].expr, yypvt[-0].expr); } break;
case 30:
# line 186 "SoCalcParse.y"
{ yyval.expr = new GreaterThan(yypvt[-2].expr, yypvt[-0].expr); } break;
case 31:
# line 188 "SoCalcParse.y"
{ yyval.expr = new LessEQ(yypvt[-2].expr, yypvt[-0].expr); } break;
case 32:
# line 190 "SoCalcParse.y"
{ yyval.expr = new GreaterEQ(yypvt[-2].expr, yypvt[-0].expr); } break;
case 34:
# line 196 "SoCalcParse.y"
{ yyval.expr = new Equals(yypvt[-2].expr, yypvt[-0].expr); } break;
case 35:
# line 198 "SoCalcParse.y"
{ yyval.expr = new NotEquals(yypvt[-2].expr, yypvt[-0].expr); } break;
case 37:
# line 204 "SoCalcParse.y"
{ yyval.expr = new And(yypvt[-2].expr, yypvt[-0].expr); } break;
case 39:
# line 210 "SoCalcParse.y"
{ yyval.expr = new Or(yypvt[-2].expr, yypvt[-0].expr); } break;
case 41:
# line 217 "SoCalcParse.y"
{ yyval.expr = new Ternary(yypvt[-4].expr, yypvt[-2].expr, yypvt[-0].expr); } break;
	}
	goto yystack;		/* reset registers in driver code */
}
