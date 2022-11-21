#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

#define MIN 1
#define MAX 100

int strIsEqual(char *left, char *right){
    return !strcmp(left, right);
}

void guessNumber(){
    int left = MIN - 1, right = MAX;
    char inputAns[11];

    while (right - left > 1) {
        int mid = (left + right) / 2;
        int isOkInput = 0;
        while (!isOkInput) {
            printf("%s %d? %s/%s: ", _("Is number greater than"), mid, _("yes"), _("no"));
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

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    bindtextdomain("main", ".");
    textdomain ("main");

    printf("%s %d %s %d.\n", _("Guess number between"), MIN, _("and"), MAX);
    guessNumber();
    return 0;
}
