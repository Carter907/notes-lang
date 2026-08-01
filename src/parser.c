#include "parser.h"
#include "mpc/mpc.h"
#include <stdio.h>
#include <stdlib.h>

static mpc_parser_t *ident_as;
static mpc_parser_t *ident_is;
static mpc_parser_t *ident_has;
static mpc_parser_t *ident_to;
static mpc_parser_t *ident_by;
static mpc_parser_t *ident_then;
static mpc_parser_t *ident_since;
static mpc_parser_t *ident_because;
static mpc_parser_t *text;
static mpc_parser_t *define_stmt;
static mpc_parser_t *type_stmt;
static mpc_parser_t *set_stmt;
static mpc_parser_t *sequence_stmt;
static mpc_parser_t *relate_stmt;
static mpc_parser_t *if_stmt;
static mpc_parser_t *why_stmt;
static mpc_parser_t *truth_stmt;
static mpc_parser_t *refute_stmt;
static mpc_parser_t *directive;
static mpc_parser_t *love_mind;

void parser_init(void) {
  ident_as = mpc_new("ident_as");
  ident_is = mpc_new("ident_is");
  ident_has = mpc_new("ident_has");
  ident_to = mpc_new("ident_to");
  ident_by = mpc_new("ident_by");
  ident_then = mpc_new("ident_then");
  ident_since = mpc_new("ident_since");
  ident_because = mpc_new("ident_because");

  text = mpc_new("text");

  define_stmt = mpc_new("define");
  type_stmt = mpc_new("type");
  set_stmt = mpc_new("set");
  sequence_stmt = mpc_new("sequence");
  relate_stmt = mpc_new("relate");
  if_stmt = mpc_new("if_stmt");
  why_stmt = mpc_new("why");
  truth_stmt = mpc_new("truth");
  refute_stmt = mpc_new("refute");

  directive = mpc_new("directive");
  love_mind = mpc_new("love_mind");

  mpc_err_t *err = mpca_lang(MPCA_LANG_DEFAULT,
    " ident_as      : /([ \\t]*([^a]|a[^s]|as[^ \\t\\n\\r]))+/ ; "
    " ident_is      : /([ \\t]*([^i]|i[^s]|is[^ \\t\\n\\r]))+/ ; "
    " ident_has     : /([ \\t]*([^h]|h[^a]|ha[^s]|has[^ \\t\\n\\r]))+/ ; "
    " ident_to      : /([ \\t]*([^t]|t[^o]|to[^ \\t\\n\\r]))+/ ; "
    " ident_by      : /([ \\t]*([^b]|b[^y]|by[^ \\t\\n\\r]))+/ ; "
    " ident_then    : /([ \\t]*([^t]|t[^h]|th[^e]|the[^n]|then[^ \\t\\n\\r]))+/ ; "
    " ident_since   : /([ \\t]*([^s]|s[^i]|si[^n]|sin[^c]|sinc[^e]|since[^ \\t\\n\\r]))+/ ; "
    " ident_because : /([ \\t]*([^b]|b[^e]|be[^c]|bec[^a]|beca[^u]|becau[^s]|becaus[^e]|because[^ \\t\\n\\r]))+/ ; "
    " text          : /([^\\n]|\\n[^.])+/ ; "
    " define        : \".define\" <ident_as> \"as\" <text> ; "
    " type          : \".type\" <ident_is> \"is\" <text> ; "
    " set           : \".set\" <ident_has> \"has\" <text> ; "
    " sequence      : \".sequence\" <ident_has> \"has\" <text> ; "
    " relate        : \".relate\" <ident_to> \"to\" <ident_by> \"by\" <text> ; "
    " if_stmt       : \".if\" <ident_then> \"then\" <text> ; "
    " why           : \".why\" <ident_since> \"since\" <text> ; "
    " truth         : \".truth\" <text> ; "
    " refute        : \".refute\" <ident_because> \"because\" <text> ; "
    " directive     : <define> | <type> | <set> | <sequence> | <relate> | <if_stmt> | <why> | <truth> | <refute> ; "
    " love_mind     : /^/ <directive>* /$/ ; ",
    ident_as, ident_is, ident_has, ident_to, ident_by, ident_then, ident_since, ident_because,
    text, define_stmt, type_stmt, set_stmt, sequence_stmt, relate_stmt, if_stmt, why_stmt, truth_stmt, refute_stmt, directive, love_mind);

  if (err != NULL) {
    mpc_err_print(err);
    mpc_err_delete(err);
    exit(1);
  }
}

void parse_and_print(const char *input) {
  mpc_result_t r;
  if (mpc_parse("<stdin>", input, love_mind, &r)) {
    mpc_ast_print(r.output);
    mpc_ast_delete(r.output);
  } else {
    mpc_err_print(r.error);
    mpc_err_delete(r.error);
  }
}

void parser_cleanup(void) {
  mpc_cleanup(20, ident_as, ident_is, ident_has, ident_to, ident_by, ident_then, ident_since, ident_because,
    text, define_stmt, type_stmt, set_stmt, sequence_stmt, relate_stmt, if_stmt, why_stmt, truth_stmt, refute_stmt, directive, love_mind);
}
