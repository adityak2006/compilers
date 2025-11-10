#include "ast.h"

void ASTNode::visitAcceptor(ASTVisitor &visitor)
{
}

void ASTVisitor::visit(StmtNode &) {}
void ASTVisitor::visit(DeclNode &) {}
void ASTVisitor::visit(ExprNode &) {}
void ASTVisitor::visit(ParamNode &) {}
void ASTVisitor::visit(Declarator &) {}
void ASTVisitor::visit(Initializer &) {}
void ASTVisitor::visit(CmpdStmtNode &) {}
void ASTVisitor::visit(TypeNode &) {}
void ASTVisitor::visit(InitDeclarator &) {}
void ASTVisitor::visit(FuncNode &) {}
void ASTVisitor::visit(GroupNode &) {}
void ASTVisitor::visit(StrategyNode &) {}
void ASTVisitor::visit(StratDeclNode &) {}
void ASTVisitor::visit(IndicatorNode &) {}
void ASTVisitor::visit(RegimeNode &) {}
void ASTVisitor::visit(SignalFuncNode &) {}
void ASTVisitor::visit(ExprStmtNode &) {}
void ASTVisitor::visit(ProgramNode &) {}
void ASTVisitor::visit(GroupDeclaration &) {}
void ASTVisitor::visit(GroupDeclarator &) {}
void ASTVisitor::visit(ASTNode &) {}
void ASTVisitor::visit(ReturnNode &) {}
void ASTVisitor::visit(BreakNode &) {}
void ASTVisitor::visit(ContinueNode &) {}
void ASTVisitor::visit(IfNode &) {}
void ASTVisitor::visit(WhileNode &) {}
void ASTVisitor::visit(ForNode &) {}
void ASTVisitor::visit(LiteralIntNode &) {}
void ASTVisitor::visit(LiteralFloatNode &) {}
void ASTVisitor::visit(LiteralBoolNode &) {}
void ASTVisitor::visit(IdentifierNode &) {}
void ASTVisitor::visit(BinaryExprNode &) {}
void ASTVisitor::visit(UnaryExprNode &) {}
void ASTVisitor::visit(AssignmentNode &) {}
void ASTVisitor::visit(CallNode &) {}
void ASTVisitor::visit(CommaExprNode &) {}
void ASTVisitor::visit(MemberAccessNode &) {}
void ASTVisitor::visit(ArrayAccessNode &) {}
void ASTVisitor::visit(ConditionalExprNode &) {}
void ASTVisitor::visit(TimeseriesNode &) {}
void ASTVisitor::visit(PortfolioStateNode &) {}
void ASTVisitor::visit(CastExprNode &) {}
void ASTVisitor::visit(SignalFuncListNode &) {}
