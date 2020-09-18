#include <stdio.h>
#include <stdlib.h>
#include "authentication.h"
#include "bank.h"
#include "utilities.h"

int main()
{
    //FILE* userData = authentication();
    bankMain(authentication());
    return 0;
}
