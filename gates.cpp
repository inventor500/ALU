#include "gates.h"
#include <iostream>
#include <cmath>


void NAND(Wire A, Wire B, Wire Out) {
	// A circular reference is created if the shared_ptr to A is also
	// stored in the lambda that is given to A.on_change. To avoid this,
	// only store raw pointers A and B inside lambda functions.
	WireObject* pA = A.get();
	WireObject* pB = B.get();

	Action action = [=](){Out->set(!(pA->get() && pB->get()));};
	A->on_change(action);
	B->on_change(action);
}


void NOT(Wire In, Wire Out) {
	NAND(In, In, Out);
}

void AND(Wire A, Wire B, Wire Out) {
	auto temp = make_wire("temp");
	NAND(A, B, temp);
	NOT(temp, Out);
}

void OR(Wire A, Wire B, Wire Out) {
	auto temp1 = make_wire("temp1");
	auto temp2 = make_wire("temp2");
	NOT(A, temp1);
	NOT(B, temp2);
	NAND(temp1, temp2, Out);
}

void XOR(Wire A, Wire B, Wire Out) {
	auto temp1 = make_wire("temp1");
	auto temp2 = make_wire("temp2");
	auto temp3 = make_wire("temp3");
	NAND(A, B, temp1);
	NAND(A, temp1, temp2);
	NAND(B, temp1, temp3);
	NAND(temp2, temp3, Out);
}

void HalfAdder(Wire A, Wire B, Wire Sum, Wire Carry) {
	XOR(A, B, Sum);
	AND(A, B, Carry);
}

void FullAdder(Wire A, Wire B, Wire Cin, Wire Sum, Wire Cout) {
	auto tempsum1 = make_wire("tempsum1");
	auto tempcarry1 = make_wire("tempcarry1");
	auto tempcarry2 = make_wire("tempcarry2");
	HalfAdder(A, B, tempsum1, tempcarry1);
	HalfAdder(tempsum1, Cin, Sum, tempcarry2);
	OR(tempcarry1, tempcarry2, Cout);
}

int add_bits(int a, int b, int numbits) {
	auto carryin = make_wire("carryin");
	int returnValue = 0;
	std::vector<bool> output_vector(numbits);
	carryin->set(false);
	for (int x = 0; x < numbits; x++) {
		auto tempsum = make_wire("tempsum");
		auto wa = make_wire("wa");
		auto wb = make_wire("wb");
		auto carryout = make_wire("carryout");
		short sa = a % 2; // get first bit of a
		short sb = b % 2;
		std::cout << "sa: " << sa << '\n' << "sb: " << sb << '\n';
		wa->set(sa);
		wb->set(sb);
		a = a >> 1; // the next loop will get the next bit
		b = b >> 1;
		std::cout << "Carry: " << carryin->get() << '\n';
		FullAdder(wa, wb, carryin, tempsum, carryout);
		carryin = carryout;
		std::cout << "Sum: " << tempsum->get() << '\n';
		std::cout << "New carry: " << carryin->get() << '\n';
		output_vector[x] = tempsum->get();
	}
	if (carryin->get()) {
		output_vector.emplace_back(true);
	}
	std::cout << "Outputing vector: ";
	for (int x = output_vector.size() - 1; x >= 0; x--) {
		std::cout << output_vector[x];
	}
	std::cout << '\n';
	for (size_t x = 0; x < output_vector.size(); x++) {
	  returnValue += output_vector[x] * pow(2,x);
	}
	return returnValue;
}

void Decoder(Wire F0, Wire F1, Wire D0, Wire D1, Wire D2, Wire D3) {
	auto notF0 = make_wire("notF0");
	auto notF1 = make_wire("notF1");
	NOT(F0, notF0);
	NOT(F1, notF1);

	AND(notF0, notF1, D0);
	AND(notF0, F1, D1);
	AND(F0, notF1, D2);
	AND(F0, F1, D3);
}

void Logic(Wire A, Wire B, Wire D0, Wire D1, Wire D2, Wire AandB, Wire AorB, Wire NotB) {
	auto AtB = make_wire("AtB");
	auto ApB = make_wire("ApB");
	auto nB = make_wire("nB");

	AND(A, B, AtB);
	OR(A, B, ApB);
	NOT(B, nB);

	AND(AtB, D0, AandB);
	AND(ApB, D1, AorB);
	AND(nB, D2, NotB);
}

void FullAdderWithEnable(Wire Enable, Wire A, Wire B, Wire Cin, Wire Sum, Wire Cout) {
	auto tempsum = make_wire("tempsum");
	auto tempcout = make_wire("tempcout");
	FullAdder(A, B, Cin, tempsum, tempcout);
	AND(tempsum, Enable, Sum);
	AND(tempcout, Enable, Cout);
}

void ALU(Wire F0, Wire F1, Wire A, Wire B, Wire Cin, Wire Out, Wire Cout) {
	auto D0 = make_wire("D0");
	auto D1 = make_wire("D1");
	auto D2 = make_wire("D2");
	auto D3 = make_wire("D3");
	auto AandB = make_wire("AandB");
	auto AorB = make_wire("AorB");
	auto NotB = make_wire("NotB");
	auto Sum = make_wire("Sum");
	auto tempor1 = make_wire("tempor1");
	auto tempor2 = make_wire("tempor2");
	Decoder(F0, F1, D0, D1, D2, D3);
	Logic(A, B, D0, D1, D2, AandB, AorB, NotB);
	FullAdderWithEnable(D3, A, B, Cin, Sum, Cout);
	OR(AandB, AorB, tempor1);
	OR(NotB, Sum, tempor2);
	OR(tempor1, tempor2, Out);
}
