#include <cstddef>
#include <cstdio>
#include <memory>
#include <string>

#include "lexer.h"
#include "cli/cli.h"

int
main(int argc, char** argv)
{
  errno_t result_fopen_src_file;
  lexer* nyaLexer = new lexer;
  char* tmp = (char*)malloc(sizeof(char) * argc);
  if (argc == 1) {
    CliInit();
    CliHelp();
  } else if (argc > 1) {
    CliInit();
    if (*argv == "-H" || *argv == "--help") {
      CliHelp();
    } else if (argv[0] == "-" && argv[1] == "O" || argv[1] == "o") {
      // 提取地址
      if (tmp) {
        for (size_t i = 0; strlen(*argv) - 2; i++)
          tmp[i] = *argv[2 + i];

        // 验证该文件存在且非空
        FILE* src_file;
        result_fopen_src_file = fopen_s(&src_file, tmp, "r");
        if (result_fopen_src_file) {
          nyaLexer->buildTokenGroup(src_file);
        }
        free(src_file);
      }
    }
    free(tmp);
  }
  free(nyaLexer);
  return (0);
}
