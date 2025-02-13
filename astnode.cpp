#include "astnode.h"
#include "symtable.h" 
#include <string>
#include <variant>


ASTNode::ASTNode(ASTValue val) : type(NodeType::Literal), value(val) {}


ASTNode::ASTNode(std::string id, int ok) : type(NodeType::Identifier), value(id) {}


ASTNode::ASTNode(std::string op, ASTNode* left, ASTNode* right)
    : type(NodeType::Operator), op(op), left(left), right(right) {}


ASTValue ASTNode::evaluate(SymTable* currentScope) const {
    if (type == NodeType::Literal) {
        return value;
    }
    if (type == NodeType::Identifier) {
        std::string id = std::get<std::string>(value);
        if (currentScope->findVariable(id)) {
            return currentScope->getVariableValue(id);
        }
        throw std::runtime_error("Undefined identifier: " + id);
    }
    if (type == NodeType::Operator) {
        ASTValue leftValue, rightValue;
        if(left->getType(currentScope) == "int" || left->getType(currentScope) == "int[]" || left->getType(currentScope) == "int[][]")
        {
            if(left->type == NodeType::Literal || left->type == NodeType::Operator)
                leftValue = std::get<int>(left->evaluate(currentScope));
            else {
                std::string str = std::get<std::string>(left->evaluate(currentScope));
                if(str.size() == 0)
                    leftValue = 0;
                else
                    leftValue = std::stoi(str);
            }
        }
        if(left->getType(currentScope) == "float")
        {
            if(left->type == NodeType::Literal || left->type == NodeType::Operator)
                leftValue = std::get<float>(left->evaluate(currentScope));
            else {
                std::string str = std::get<std::string>(left->evaluate(currentScope));
                if(str.size() == 0)
                    leftValue = 0.0f;
                else
                    leftValue = std::stof(str);
            }
        }        
        
        if(left->getType(currentScope) == "bool")
        {
            if (left->type == NodeType::Literal || left->type == NodeType::Operator)
                leftValue = std::get<bool>(left->evaluate(currentScope));
            else {
                ASTValue LeftValue = left->evaluate(currentScope);
                if(std::get<std::string>(LeftValue) == "true")
                    leftValue = true;
                else
                    leftValue = false;
            }
        }
        if(right!= nullptr)
        {
            if(right->getType(currentScope) == "int" || right->getType(currentScope) == "int[]" || right->getType(currentScope) == "int[][]")
            {
                if (right->type == NodeType::Literal || right->type == NodeType::Operator)
                    rightValue = std::get<int>(right->evaluate(currentScope));
                else {
                    std::string str = std::get<std::string>(right->evaluate(currentScope));
                    if(str.size() == 0)
                        rightValue = 0;
                    else
                        rightValue = std::stoi(str);
                }
            }

            if(right->getType(currentScope) == "float")
            {
                if (right->type == NodeType::Literal || right->type == NodeType::Operator)
                    rightValue = std::get<float>(right->evaluate(currentScope));
                else {
                    std::string str = std::get<std::string>(right->evaluate(currentScope));
                    if(str.size() == 0)
                        rightValue = 0.0f;
                    else
                        rightValue = std::stof(str);
                }
            }  

            if(right->getType(currentScope) == "bool")
            {
                if (right->type == NodeType::Literal || right->type == NodeType::Operator)
                    rightValue = std::get<bool>(right->evaluate(currentScope));
                else {
                    ASTValue RightValue = right->evaluate(currentScope);
                    if(std::get<std::string>(RightValue) == "true")
                        rightValue = true;
                    else
                        rightValue = false;
                }
            }
        }
        if (op == "+") {
            if(left->getType(currentScope) == "int")
                return std::get<int>(leftValue) + std::get<int>(rightValue);
            else
                return std::get<float>(leftValue) + std::get<float>(rightValue);
        } 
        else if (op == "*") {
            if(left->getType(currentScope) == "int")
                return std::get<int>(leftValue) * std::get<int>(rightValue);
            else
                return std::get<float>(leftValue) * std::get<float>(rightValue);
        } 
        else if (op == "-") {
            if(left->getType(currentScope) == "int")
                return std::get<int>(leftValue) - std::get<int>(rightValue);
            else
                return std::get<float>(leftValue) - std::get<float>(rightValue);
        } 
        else if (op == "/") {
            if(left->getType(currentScope) == "int")
                return std::get<int>(leftValue) / std::get<int>(rightValue);
            else
                return std::get<float>(leftValue) / std::get<float>(rightValue);            
        } 
        else if (op == "||") {
            return std::get<bool>(leftValue) || std::get<bool>(rightValue);
        } 
        else if (op == "&&") {
            return std::get<bool>(leftValue) && std::get<bool>(rightValue);
        }
        else if (op == "<") {
            if(left->getType(currentScope) == "int")
                return std::get<int>(leftValue) < std::get<int>(rightValue);
            else
                return std::get<float>(leftValue) < std::get<float>(rightValue);
        }
        else if (op == ">") {
            if(left->getType(currentScope) == "int")
                return std::get<int>(leftValue) > std::get<int>(rightValue);
            else
                return std::get<float>(leftValue) > std::get<float>(rightValue);
        }
        else if (op == "<=") {
            if(left->getType(currentScope) == "int")
                return std::get<int>(leftValue) <= std::get<int>(rightValue);
            else
                return std::get<float>(leftValue) <= std::get<float>(rightValue);
        }
        else if (op == ">=") {
            if(left->getType(currentScope) == "int")
                return std::get<int>(leftValue) >= std::get<int>(rightValue);
            else
                return std::get<float>(leftValue) >= std::get<float>(rightValue);
        }
        else if (op == "==") {
            if(left->getType(currentScope) == "int")
                return std::get<int>(leftValue) == std::get<int>(rightValue);
            else
                return std::get<float>(leftValue) == std::get<float>(rightValue);
        }
        else if (op == "!=") {
            if(left->getType(currentScope) == "int")
                return std::get<int>(leftValue) != std::get<int>(rightValue);
            else
                return std::get<float>(leftValue) != std::get<float>(rightValue);
        }
        else if (op == "!") {
            return !(std::get<bool>(leftValue));
        }
        throw std::runtime_error("Unknown operator: " + op);
    }
    throw std::runtime_error("Invalid ASTNode");
}


std::string ASTNode::getType(SymTable* currentScope) const {
    if (type == NodeType::Literal) {
        if ((std::holds_alternative<char>(value))) return "char";
        if ((std::holds_alternative<int>(value))) return "int";
        if (std::holds_alternative<float>(value)) return "float";
        if (std::holds_alternative<bool>(value)) return "bool";
    }
    if (type == NodeType::Identifier) {
        std::string id = std::get<std::string>(value);
        if (currentScope->findVariable(id)) {
            return currentScope->getVariableType(id);
        }
        throw std::runtime_error("Undefined identifier: " + id);
    }
    if (type == NodeType::Operator) {
        if (op == "+" || op == "-" || op == "/" || op == "*") 
            return left->getType(currentScope); 
        else 
            return "bool";
    }
    throw std::runtime_error("Invalid ASTNode");
}