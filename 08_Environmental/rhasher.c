#include "config.h"
#include <ctype.h>
#include <errno.h>
#include <rhash.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef USE_READLINE
#include <readline/history.h>
#endif

#DEFINE OUTPUT_LEN 256

int getOutputFormat(char *hashName) {
  if (hashName[0] == tolower(hashName[0])) {
    return RHPR_BASE64;
  }

  return RHPR_HEX;
}

void hashNameToLower(char *hashName) {
  for (size_t i = 0; i < strlen(hashName); ++i) {
    hashName[i] = tolower(hashName[i]);
  }
}

void printHashNames() {
  fprintf(stderr, "Available hash names: md5, sha1, tth\n");
}

void printHelp() {
  fprintf(stderr, "usage: <hash-name> [fileName, \"string]\n");
  printHashNames();
  fprintf(stderr, "Capitalize first hash name symbol if you want print "
                  "result at base64 otherwise hex\n");
}

int main() {
  int outputFormat = 0, hash = 0, isFile = 1;
  char *line = NULL, *hashName = NULL, *inputStr = NULL, output[OUTPUT_LEN];
  unsigned char digest[64];
  size_t len = 0;
  rhash_library_init();

#ifdef USE_READLINE
  while ((line = readline(NULL)))
#else
  while (getline(&line, &len, stdin) != -1)
#endif

  {
    hashName = strtok(line, " ");
    inputStr = strtok(strtok(NULL, " "), "\n");

    if (!inputStr || !hashName) {
      printHelp();
      continue;
    }

    outputFormat = getOutputFormat(hashName);
    hashNameToLower(hashName);

    if (!strcmp(hashName, "md5")) {
      hash = RHASH_MD5;
    } else if (!strcmp(hashName, "sha1")) {
      hash = RHASH_SHA1;
    } else if (!strcmp(hashName, "tth")) {
      hash = RHASH_TTH;
    } else {
      fprintf(stderr, "Wrong hash name\n");
      printHashNames();
      continue;
    }

    if (inputStr[0] == '\"') {
      isFile = 0;
      inputStr++;
    }

    int res = 0;
    if (isFile) {
      res = rhash_file(hash, inputStr, digest);
    } else {
      res = rhash_msg(hash, inputStr, strlen(inputStr), digest);
    }

    if (res < 0) {
      fprintf(stderr, "Error while hashing data!\n");
      fprintf(stderr, "%s\n", strerror(errno));
      continue;
    }

    rhash_print_bytes(output, digest, rhash_get_digest_size(hash),
                      outputFormat);
    fprintf(stdout, "%s\n", output);

    if (line) {
      free(line);
    }
  }

  return 0;
}
