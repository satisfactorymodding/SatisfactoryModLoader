#pragma once

#include "CoreMinimal.h"

/** Classification of script opcodes into separate categories based on their behavior */
class SML_API FScriptExprClassification {
public:
	/** Returns true if the opcode is classified as an assignment of a single value. Note that not all assignment opcodes have explicit property name */
	static bool IsSingleAssignmentOpcode(uint8 Opcode);
	/** Returns true if the opcode is classified as a value assignment, but assigns multiple values at once. This is used to classify delegate binding, array and set assignments, and so on */
	static bool IsMultiAssignmentOpcode(uint8 Opcode);
	/** Returns true if this opcode is either a single or multi assignment */
	static bool IsAssignmentOpcode(uint8 Opcode);
	/** Returns true if the opcode is classified as a function call. Delegate calls are also function calls */
	static bool IsFunctionCallOpcode(uint8 Opcode);
	/** Returns true if the opcode is classified as a control flow related statement */
	static bool IsControlFlowOpcode(uint8 Opcode);
	/** Returns true if the opcode is classified as a debugging/instrumentation related statement */
	static bool IsDebugOpcode(uint8 Opcode);
	/** Returns true if the opcode represents an unconditional control flow stop (or jump to a different location), so that the code after will not run sequentially */
	static bool IsUnconditionalControlFlowStop(uint8 Opcode);
	
	/** Returns true if the opcode is a pure "transformation" bytecode. Transformation bytecodes are pure expressions that transform original expression (such as get array element, struct member, cast, etc) */
	static bool IsPureTransformationOpcode(uint8 Opcode);
	/** Returns true if the opcode is classified as property read, with first operand being the property object to read */
	static bool IsPropertyOpcode(uint8 Opcode);
	/** Returns true if the opcode is classified as a cast */
	static bool IsCastOpcode(uint8 Opcode);
	/** Returns true if the opcode is classified as a context opcode */
	static bool IsContextOpcode(uint8 Opcode);
	/** Returns true if the opcode is classified as an int constant */
	static bool IsIntConstantOpcode(uint8 Opcode);
	/** Returns true if the opcode is a numeric constant */
	static bool IsNumericConstantOpcode(uint8 Opcode);
	/** Returns true if opcode is a simple constant opcode. Simple constant opcode is a constant opcode that does not have expressions as operands */
	static bool IsSimpleConstantOpcode(uint8 Opcode);
	/** Returns true if opcode is a complex constant opcode. Complex constants are constants with other expressions as operands */
	static bool IsComplexConstantOpcode(uint8 Opcode);
	/** Returns true if the opcode is a constant. This also includes complex constants like text */
	static bool IsConstantOpcode(uint8 Opcode);
	/** Returns true if the opcode is classified as a struct constant. Vector, Rotator and Transform constants are also struct constants */
	static bool IsStructConstantOpcode(uint8 Opcode);
	/** Returns true if the opcode is considered Pure. Pure opcodes are expressions with no side effects */
	static bool IsPureOpcode(uint8 Opcode);
};
