#include "cli.h"

#define Version "0.0.1 Dev"
#define getVersion Version " (R) Nya Devlopment"

#if __GNUC__
#define COM "[GNU GCC]"
#elif __clang__
#define COM "[LLVM CLANG]"
#elif _MSC_VER
#define COM "[MicroSoft MSVC]"
#else
#define COM "[UNKNOW COMPILER]"
#endif
#define COMP COM " [LICENSE MPL2.0]"

void
CliInit()
{
  puts(getVersion);
  puts(COMP);
}

const char HELPS[] = "-H --help\n-O -o\n-V --version\n";

void
CliHelp()
{
  puts(HELPS);
}
