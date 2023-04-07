#ifndef AST_H
#define AST_H

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace {
/// Base class for all expression nodes.
class ExprAST
{
public:
  virtual ~ExprAST() = default;
};
/// Expression class for numeric literals
class NumberExprAST : public ExprAST
{
private:
  double Value;

public:
  NumberExprAST(double Value)
    : Value(Value)
  {
  }
};
/// Expression class for referencing a variable
class VariableExprAST : public ExprAST
{
private:
  std::string Name;

public:
  VariableExprAST(const std::string& Name)
    : Name(Name)
  {
  }
};
/// Expression class for a binary operator.
class BinaryExprAST : public ExprAST
{
private:
  char Operation;
  std::unique_ptr<ExprAST> LHS, RHS;

public:
  BinaryExprAST(char Operation,
                std::unique_ptr<ExprAST> LHS,
                std::unique_ptr<ExprAST> RHS)
    : Operation(Operation)
    , LHS(std::move(LHS))
    , RHS(std::move(RHS))
  {
  }
};
/// Expression class for function calls.
class CallExprAST : public ExprAST
{
private:
  std::string Callee;
  std::vector<std::unique_ptr<ExprAST>> Args;

public:
  CallExprAST(const std::string& Callee,
              std::vector<std::unique_ptr<ExprAST>> Args)
    : Callee(Callee)
    , Args(std::move(Args))
  {
  }
};

/// represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).
class PrototypeAST
{
  std::string Name;
  std::vector<std::string> Args;

public:
  PrototypeAST(const std::string& Name, std::vector<std::string> Args)
    : Name(Name)
    , Args(std::move(Args))
  {
  }

  const std::string& getName() const { return Name; }
};

/// represents a function definition itself.
class FunctionAST
{
  std::unique_ptr<PrototypeAST> Proto;
  std::unique_ptr<ExprAST> Body;

public:
  FunctionAST(std::unique_ptr<PrototypeAST> Proto,
              std::unique_ptr<ExprAST> Body)
    : Proto(std::move(Proto))
    , Body(std::move(Body))
  {
  }
};
}

#endif