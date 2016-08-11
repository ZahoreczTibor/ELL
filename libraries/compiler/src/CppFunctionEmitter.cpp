#include "CppFunctionEmitter.h"

namespace emll
{
	namespace compiler
	{
		CppFunctionEmitter::CppFunctionEmitter()
		{
		}

		CppFunctionEmitter& CppFunctionEmitter::Begin(const std::string& name, const ValueType returnType, const NamedValueTypeList& args)
		{
			_emitter.Clear()
				.DeclareFunction(name, returnType, args)
				.NewLine()
				.BeginBlock();
			return *this;
		}

		CppFunctionEmitter& CppFunctionEmitter::End()
		{
			_emitter.EndBlock();
			return *this;
		}

		CppFunctionEmitter& CppFunctionEmitter::EndStatement()
		{
			_emitter.Semicolon().NewLine();
			return *this;
		}

		CppFunctionEmitter& CppFunctionEmitter::Var(ValueType type, const std::string& name)
		{
			_emitter.Var(type, name);
			EndStatement();
			return *this;
		}

		CppFunctionEmitter& CppFunctionEmitter::Value(const std::string& varName)
		{
			_emitter.Identifier(varName);
			return *this;
		}

		CppFunctionEmitter& CppFunctionEmitter::ValueAt(const std::string& name, int offset)
		{
			_emitter.Identifier(name)
				.Offset(offset);
			return *this;
		}

		CppFunctionEmitter& CppFunctionEmitter::ValueAt(const std::string& name, const std::string& offsetVarName)
		{
			_emitter.Identifier(name)
				.Offset(offsetVarName);
			return *this;
		}

		CppFunctionEmitter& CppFunctionEmitter::Assign(const std::string& varName)
		{
			_emitter.Assign(varName).Space();
			return *this;
		}

		CppFunctionEmitter& CppFunctionEmitter::AssignValue(const std::string& varName, std::function<void(CppFunctionEmitter& fn)> value)
		{
			_emitter.Assign(varName).Space();
			value(*this);
			EndStatement();
			return *this;
		}

		CppFunctionEmitter& CppFunctionEmitter::AssignValueAt(const std::string& destVarName, int offset)
		{
			_emitter.AssignValueAt(destVarName, offset).Space();
			return *this;
		}

		CppFunctionEmitter& CppFunctionEmitter::AssignValueAt(const std::string& destVarName, const std::string& offsetVarName)
		{
			_emitter.AssignValueAt(destVarName, offsetVarName).Space();
			return *this;
		}

		CppFunctionEmitter& CppFunctionEmitter::AssignValueAt(const std::string& destVarName, int offset, std::function<void(CppFunctionEmitter& fn)> value)
		{
			_emitter.AssignValueAt(destVarName, offset).Space();
			value(*this);
			EndStatement();
			return *this;
		}

		CppFunctionEmitter& CppFunctionEmitter::Op(OperatorType op, std::function<void(CppFunctionEmitter& fn)> lValue, std::function<void(CppFunctionEmitter& fn)> rValue)
		{
			lValue(*this);
			_emitter.Space();
			_emitter.Operator(op).Space();
			rValue(*this);

			return *this;
		}

		CppFunctionEmitter& CppFunctionEmitter::Cmp(ComparisonType cmp, std::function<void(CppFunctionEmitter& fn)> lValue, std::function<void(CppFunctionEmitter& fn)> rValue)
		{
			_emitter.OpenParan();
			lValue(*this);
			_emitter.Space();
			_emitter.Cmp(cmp).Space();
			rValue(*this);
			_emitter.CloseParan();

			return *this;
		}

		CppFunctionEmitter& CppFunctionEmitter::BeginFor(const std::string& iVarName, int count)
		{
			_emitter.For()
				.OpenParan()
				.Var<int>(iVarName).Space()
				.Assign().Space()
				.Literal(0).Semicolon().Space()
				.Cmp<int>(iVarName, ComparisonType::Lt, count).Semicolon().Space()
				.Identifier(iVarName).Increment()
				.CloseParan().NewLine()
				.BeginBlock();

			return *this;
		}

		CppFunctionEmitter& CppFunctionEmitter::EndFor()
		{
			_emitter.EndBlock();
			return *this;
		}

		CppFunctionEmitter& CppFunctionEmitter::BeginElse()
		{
			_emitter.Else().NewLine()
				.BeginBlock();
			return *this;
		}

		CppFunctionEmitter& CppFunctionEmitter::EndIf()
		{
			_emitter.EndBlock();
			return *this;
		}

	}
}