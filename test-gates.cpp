// Isaac Ganoung
// Computer Organization
// 2021-10-04
#include "gates.h"
#include "truth.h"
#include <iostream>


void test_nand();
void test_not();
void test_and();
void test_or();
void test_xor();
void test_half_adder();
void test_full_adder();
void test_decoder();
void test_logic_unit();
void test_full_adder_with_enable();
void test_alu();

int main() {
	try {
		int a, b, bits;
		test_nand();
		test_not();
		test_and();
		test_or();
		test_xor();
		test_half_adder();
		test_full_adder();
		test_decoder();
		test_logic_unit();
		test_full_adder_with_enable();
		test_alu();
		std::cout << "Int 1: ";
		std::cin >> a;
		std::cout << "Int 2: ";
		std::cin >> b;
		std::cout << "Bits: ";
		std::cin >> bits;
		int temp = add_bits(a,b,bits);
		std::cout << "Addition result: " << temp << '\n';
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}


void test_nand() {
	auto A = make_wire("A");
	auto B = make_wire("B");
	auto Out = make_wire("Out");
	NAND(A, B, Out);
	std::cout << "NAND(A,B) -> Out\n";
	print_truth_table({A, B}, {Out});
}

void test_not() {
	auto A = make_wire("A");
	auto Out = make_wire("Out");
	NOT(A, Out);
	std::cout << "NOT(A,B) -> Out\n";
	print_truth_table({A}, {Out});
}

void test_and() {
	auto A = make_wire("A");
	auto B = make_wire("B");
	auto Out = make_wire("Out");
	AND(A, B, Out);
	std::cout << "AND(A,B) -> Out\n";
	print_truth_table({A, B}, {Out});
}

void test_or() {
	auto A = make_wire("A");
	auto B = make_wire("B");
	auto Out = make_wire("Out");
	OR(A, B, Out);
	std::cout << "OR(A,B) -> Out\n";
	print_truth_table({A, B}, {Out});
}

void test_xor() {
	auto A = make_wire("A");
	auto B = make_wire("B");
	auto Out = make_wire("Out");
	XOR(A, B, Out);
	std::cout << "XOR(A,B) -> Out\n";
	print_truth_table({A, B}, {Out});
}

void test_half_adder() {
	auto A = make_wire("A");
	auto B = make_wire("B");
	auto Sum = make_wire("Sum");
	auto Carry = make_wire("Carry");
	HalfAdder(A, B, Sum, Carry);
	std::cout << "HalfAdder(A,B) -> Sum,Carry\n";
	print_truth_table({A, B}, {Sum, Carry});
}

void test_full_adder() {
	auto A = make_wire("A");
	auto B = make_wire("B");
	auto Sum = make_wire("Sum");
	auto Cin = make_wire("Cin");
	auto Cout = make_wire("Cout");
	FullAdder(A, B, Cin, Sum, Cout);
	std::cout << "FullAdder(A,B) -> Sum,Cout\n";
	print_truth_table({A, B, Cin}, {Sum, Cout});
}

void test_decoder() {
	auto F0 = make_wire("F0");
	auto F1 = make_wire("F1");
	auto D0 = make_wire("D0");
	auto D1 = make_wire("D1");
	auto D2 = make_wire("D2");
	auto D3 = make_wire("D3");
	Decoder(F0, F1, D0, D1, D2, D3);
	std::cout << "Decoder(F0, F1)-> D0,D1,D2,D3\n";
	print_truth_table({F0, F1}, {D0, D1, D2, D3});
}

void test_logic_unit() {
	auto A = make_wire("A");
	auto B = make_wire("B");
	auto D0 = make_wire("D0");
	auto D1 = make_wire("D1");
	auto D2 = make_wire("D2");
	auto AtB = make_wire("AB");
	auto ApB = make_wire("AplusB");
	auto nB = make_wire("notB");
	Logic(A, B, D0, D1, D2, AtB, ApB, nB);
	std::cout << "Logic(A, B, D0, D1, D2) -> AB, A+B, ~B\n";
	print_truth_table({A, B, D0, D1, D2}, {AtB, ApB, nB});
}

void test_full_adder_with_enable() {
	auto Enable = make_wire("Enable");
	auto A = make_wire("A");
	auto B = make_wire("B");
	auto Cin = make_wire("Cin");
	auto Sum = make_wire("Sum");
	auto Cout = make_wire("Cout");
	FullAdderWithEnable(Enable, A, B, Cin, Sum, Cout);
	std::cout << "FullAdderWithEnable(A, B, Cin) -> Sum, Cout\n";
	print_truth_table({Enable, A, B, Cin}, {Sum, Cout});
}

void test_alu() {
	auto F0 = make_wire("F0");
	auto F1 = make_wire("F1");
	auto A = make_wire("A");
	auto B = make_wire("B");
	auto Cin = make_wire("Cin");
	auto Out = make_wire("Out");
	auto Cout = make_wire("Cout");
	ALU(F0, F1, A, B, Cin, Out, Cout);
	std::cout << "ALU(F0, F1, A, B, Cin) -> Out, Cout\n";
	print_truth_table({F0, F1, A, B, Cin}, {Out, Cout});
}
