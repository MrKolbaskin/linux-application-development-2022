#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#define CREATE_REGEXP_ERROR 2
#define PARSE_SUBST_ERROR 3
#define REGEXP_ERROR 4

int MATCH_LEN = 10;
int REGERR_SIZE = 256;

void processReError(int errcode, regex_t *regexp) {
  char errmsg[REGERR_SIZE];
  regerror(errcode, regexp, errmsg, REGERR_SIZE);
  fprintf(stderr, "%s\n", errmsg);
}

int validateSubstitutionError() {
  fprintf(stderr, "Can't parse your substitution.\n");
  return -1;
}

int getGroupNumber(char *p) { return *p - '0'; }

int validateSubstitution(char *substitution, regmatch_t *regmatch) {
  int isGroup = 0;
  char *p = substitution;
  while (1) {
    if (!*p) {
      break;
    } else if (*p == '\\') {
      isGroup = !isGroup;
    } else if (isGroup) {
      if (!isdigit(*p))
        return validateSubstitutionError();

      int groupNumber = getGroupNumber(p);
      if (regmatch[groupNumber].rm_so < 0)
        return validateSubstitutionError();

      isGroup = 0;
    }
    p++;
  }

  if (isGroup)
    return validateSubstitutionError();

  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("usage: ./run regexp substitution string");
    return 0;
  }

  regex_t regexp;
  char *regexpStr = argv[1], *substitution = argv[2], *string = argv[3];

  int regcompErr = regcomp(&regexp, regexpStr, REG_EXTENDED);
  if (regcompErr) {
    processReError(regcompErr, &regexp);
    regfree(&regexp);
    return CREATE_REGEXP_ERROR;
  }

  regmatch_t regmatch[MATCH_LEN];
  int regexecErr = regexec(&regexp, string, MATCH_LEN, regmatch, 0);

  if (regexecErr == 0) {
    if (!validateSubstitution(substitution, regmatch)) {
      printf("%.*s", (int)regmatch[0].rm_so, string);

      char *p = substitution;
      int isGroup = 0;
      while (1) {
        if (!*p)
          break;

        if (*p == '\\') {
          if (isGroup)
            putchar(*p);

          isGroup = !isGroup;
        } else if (isGroup) {
          int groupNumber = getGroupNumber(p);
          int so = (int)regmatch[groupNumber].rm_so,
              eo = (int)regmatch[groupNumber].rm_eo;

          printf("%.*s", eo - so, string + so);
          isGroup = 0;
        } else {
          putchar(*p);
        }

        p++;
      }

      printf("%s\n", string + regmatch[0].rm_eo);
    } else
      return PARSE_SUBST_ERROR;
  } else if (regexecErr == REG_NOMATCH) {
    printf("%s\n", string);
  } else {
    processReError(regexecErr, &regexp);
    return REGEXP_ERROR;
  }

  regfree(&regexp);
  return 0;
}
