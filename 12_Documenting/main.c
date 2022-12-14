#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _(STRING) gettext(STRING)

#define MIN 1
#define MAX 100

const char *roman[] = {
    "I",       "II",     "III",     "IV",       "V",      "VI",      "VII",
    "VIII",    "IX",     "X",       "XI",       "XII",    "XIII",    "XIV",
    "XV",      "XVI",    "XVII",    "XVIII",    "XIX",    "XX",      "XXI",
    "XXII",    "XXIII",  "XXIV",    "XXV",      "XXVI",   "XXVII",   "XXVIII",
    "XXIX",    "XXX",    "XXXI",    "XXXII",    "XXXIII", "XXXIV",   "XXXV",
    "XXXVI",   "XXXVII", "XXXVIII", "XXXIX",    "XL",     "XLI",     "XLII",
    "XLIII",   "XLIV",   "XLV",     "XLVI",     "XLVII",  "XLVIII",  "XLIX",
    "L",       "LI",     "LII",     "LIII",     "LIV",    "LV",      "LVI",
    "LVII",    "LVIII",  "LIX",     "LX",       "LXI",    "LXII",    "LXIII",
    "LXIV",    "LXV",    "LXVI",    "LXVII",    "LXVIII", "LXIX",    "LXX",
    "LXXI",    "LXXII",  "LXXIII",  "LXXIV",    "LXXV",   "LXXVI",   "LXXVII",
    "LXXVIII", "LXXIX",  "LXXX",    "LXXXI",    "LXXXII", "LXXXIII", "LXXXIV",
    "LXXXV",   "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC",      "XCI",
    "XCII",    "XCIII",  "XCIV",    "XCV",      "XCVI",   "XCVII",   "XCVIII",
    "XCIX",    "C"};

int strIsEqual(char *left, char *right) { return !strcmp(left, right); }

const char *toRoman(int num) { return roman[num - 1]; }

int isRoman = 0;

int fromRoman(const char *romanNum) {
  for (int i = 0; i < MAX; ++i) {
    if (strIsEqual((char *)romanNum, (char *)roman[i])) {
      return i + 1;
    }
  }
  return -1;
}

void printHelp() {
  printf(_("usage: main [-r, --help]\n"));
  printf(_("    -r:      use roman numbers\n"));
  printf(_("    --help:  print help text\n"));
  printf(_("In this game you need to guess number and the program\n"));
  printf(_("will try to guess it by asking simple questions\n"));
}

char strNum[5];
const char *numToStr(int isRoman, int num) {
  if (isRoman) {
    return toRoman(num);
  }

  sprintf(strNum, "%d", num);
  return strNum;
}

void guessNumber() {
  int left = MIN - 1, right = MAX;
  char inputAns[11];

  while (right - left > 1) {
    int mid = (left + right) / 2;
    int isOkInput = 0;
    while (!isOkInput) {
      printf("%s %s? %s/%s: ", _("Is number greater than"),
             numToStr(isRoman, mid), _("yes"), _("no"));
      scanf("%3s", inputAns);

      if (strIsEqual(inputAns, _("yes"))) {
        left = mid;
        isOkInput = 1;
      } else if (strIsEqual(inputAns, _("no"))) {
        right = mid;
        isOkInput = 1;
      } else {
        fprintf(stderr, _("Bad input, try again\n"));
      }
    }
  }

  printf("%s %d\n", _("Number is"), right);
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  bindtextdomain("main", ".");
  textdomain("main");

  if (argc > 1) {
    if (strIsEqual(argv[1], "--help")) {
      printHelp();
      return 0;
    }

    if (strIsEqual(argv[1], "-r")) {
      isRoman = 1;
    }
  }

  printf("%s %d %s %d.\n", _("Guess number between"), MIN, _("and"), MAX);
  guessNumber();
  return 0;
}
