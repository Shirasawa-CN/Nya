#include <stdio.h>

#include "cli/cli.h"
#include "tool/result.h"
#include "lexer.h"

int
main(int argc, char** argv)
{
  errno_t result_fopen_src_file;
  char* tmp = (char*)malloc(sizeof(argv));
  tmp = "0";
  if (argc == 1) {
    CliInit();
    CliHelp();
  } else if (argc > 1) {
    CliInit();
    if (*argv == "-H" || *argv == "--help") {
      CliHelp();
    }else if (argv[0] == "-" && argv[1] == "O" || argv[1] == "o")
    {
      //提取地址
      for (int i = 0; i <= sizeof(argv) - 2;i++)
        tmp[i] = *argv[1 + i];
      
      //验证该文件存在且非空
      FILE* src_file;
      result_fopen_src_file = fopen_s(&src_file,tmp, "r");
      if (result_fopen_src_file) {
        buildTokenGroup(src_file);
      }
      free(src_file);
    }
    free(tmp);
  }
  return (0);
}
