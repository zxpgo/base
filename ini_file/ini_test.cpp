#include <iostream>
#include "value.h"
#include "ini_file.h"

int main()
{
    IniFile inifile;
    inifile.load("test.ini");
    inifile.print();

    Value value = "cccc";
    inifile.set("test", "ccc", value);
    inifile.save();
    inifile.print();

    return 0;
}