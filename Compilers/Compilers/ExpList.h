#pragma once

#include "Visitor.h"
#include "Grammar.h"
#include <memory>

class CExp : public IExpList {
public:
	CExp(IExp* _exp) : exp(_exp) {}
	void accept(IVisitor& visitor) { visitor.visit(*this); }
	std::shared_ptr<IExp> exp;
};

class CExpExpRest : public IExpList {
	CExpExpRest(IExpList* _expRest, IExp* _exp) : exp(_exp), expRest(_expRest) {}
	void accept(IVisitor& visitor) { visitor.visit(*this); }
	std::shared_ptr<IExpList> expRest;
	std::shared_ptr<IExp> exp;
};

