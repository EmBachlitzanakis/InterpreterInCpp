#pragma once
#include <iostream>
#include <vector>
#include "Statement.h"
#include "token.h"

class BlockStatement : public Statement
{

public:
	std::vector<Statement*> statements_;
	Token token_;


	BlockStatement(const Token& token);

	// Add a statement to the block
	void AddStatement(Statement* statement);

	// Getter for statements
	const std::vector<Statement*>& GetStatements() const;

	// Destructor
	~BlockStatement() override;

	std::string TokenLiteral() const override;

	std::string String() const override;

	void statementNode() override;
};	

