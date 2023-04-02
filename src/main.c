#include <stdio.h>

#include "cli/cli.h"
#include "tool/result.h"
#include "lexer.h"

int
main(int argc, char** argv)
{
  FILE* src_file;
  errno_t result_fopen_srcfile;
  char* tmp = (char*)malloc(sizeof(argv) - 2);
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
      for (int i = 0; i >= sizeof(argv) - 2;i++)
        tmp[i] = *argv[1 + i];
      
      //验证该文件存在且非空
      result_fopen_srcfile = fopen_s(&src_file,tmp, "r");
      if (result_fopen_srcfile && feof(src_file) != EOF){
        buildTokenGroup(src_file);
      }

    }
    free(tmp);
    free(src_file);
  }
  return (0);
}
