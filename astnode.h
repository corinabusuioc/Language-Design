#pragma once

#include <memory>
#include <variant>
#include <string>
#include <stdexcept>
#include <iostream>

using ASTValue = std::variant<char, int, float, bool, std::string>;

class SymTable;
class ASTNode {
public:
    enum class NodeType {
        Literal,     
        Identifier, 
        Operator     
    };
    
    ASTNode(ASTValue val);

    ASTNode(std::string id, int ok);
    
    ASTNode(std::string op, ASTNode* left, ASTNode* right);
    
    ASTValue evaluate(SymTable* currentScope) const;
    
    std::string getType(SymTable* currentScope) const;

private:
    NodeType type;                        
    std::string op;                       
    ASTValue value;                        
    ASTNode* left;         
    ASTNode* right;       
};