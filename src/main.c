#include "mpc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32

static char buffer[2048];

char *readline(char *prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char *cpy = malloc(strlen(buffer) + 1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy) - 1] = '\0';
  return cpy;
}

void add_history(char *unused) {}

#else
#include <editline/history.h>
#include <editline/readline.h>
#endif

int needs_continuation(const char *str) {
  if (!str || strlen(str) == 0)
    return 0;

  size_t len = strlen(str);
  // Check if the last character is a backslash
  if (str[len - 1] == '\\') {
    // Simple check: make sure it's not escaped by another backslash
    if (len == 1 || str[len - 2] != '\\') {
      return 1;
    }
  }
  return 0;
}

int main(int argc, char **argv) {

  /* Create Some Parsers */
  mpc_parser_t *setP = mpc_new("set");
  // mpc_parser_t *identP = mpc_new("identifier");
  mpc_parser_t *notesP = mpc_new("notes");

  /* Context-free grammar is stored in src/lang.txt file */
  mpca_lang_contents(MPCA_LANG_DEFAULT, "src/lang.txt", setP, notesP);

  char *line = NULL;
  char *buffer = NULL;

  puts("Press Ctrl+c to Exit\n");
  FILE *fp = fopen("out.log", "a+");

  while (1) {
    // 1. Read the initial line
    line = readline("notes> ");

    // Handle EOF (Ctrl+D)
    if (!line) {
      break;
    }

    // Initialize or reset our multi-line buffer
    buffer = malloc(strlen(line) + 1);
    strcpy(buffer, line);
    free(line);

    while (needs_continuation(buffer)) {
      size_t len = strlen(buffer);
      buffer[len - 1] = '\0';

      // Read the next line with a continuation prompt
      line = readline("> ");
      if (!line) {
        break; // User hit Ctrl+D during continuation
      }

      // Resize buffer and concatenate
      // Safe realloc standard practice: use a temporary pointer
      char *temp = realloc(buffer, strlen(buffer) + strlen(line) + 2);
      if (!temp) {
        perror("realloc");
        free(buffer);
        free(line);
        exit(1);
      }
      buffer = temp;

      strcat(buffer, "\n");
      strcat(buffer, line);

      free(line);
    }

    if (strlen(buffer) > 0) {
      add_history(buffer);

      mpc_result_t r;

      fprintf(fp, "PARSE: ///>%s<///\n\n", buffer);
      // FIX: Changed 'line' to 'buffer'
      if (mpc_parse("<stdin>", buffer, notesP, &r)) {
        /* On success print and delete the AST */
        mpc_ast_print(r.output);
        mpc_ast_delete(r.output);
      } else {
        /* Otherwise print and delete the Error */
        mpc_err_print(r.error);
        mpc_err_delete(r.error);
      }
    }

    free(buffer);
  }

  fclose(fp);
  /* Undefine and delete our parsers */
  mpc_cleanup(2, setP, notesP);

  return 0;
}
