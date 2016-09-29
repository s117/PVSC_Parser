#include <stdio.h>
#include <stdlib.h>


#include "801_extreme.h"
#include "PVSC_Parser.h"

int main(int argc, char* argv[]) {
    DSC_Info info;
    PVSC_Parser *parser = new PVSC_Parser();
    parser->parse_dsc(&info, data, sizeof(data));

    return 0;
}

