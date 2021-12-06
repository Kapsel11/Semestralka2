#pragma once
#include <iostream>

namespace constants {
	const int POCET_UJ = 3014;
	const int POCET_BJ = 550;
	std::string slovensko("Slovensko");
	const int pocet_riadkov_bj = 55;
	const int pocet_stlpcov_bj = 10;
	std::string stringy_BJ[5] = {
		"Byty v budovach s jednym bytom",
		"Byty v budovach s dvoma bytmi",
		"Byty v budovach s troma alebo viac bytmi",
		"Byty v nebytovych budovach",
		"Nezistene"
	};
	std::string stringy_pocet_osob [] = {
		"1 osoba",
		"2 osoby",
		"3 osoby",
		"4 osoby",
		"5 osob",
		"6 osob",
		"7 osob",
		"8 osob",
		"9 osob",
		"10 osob",
		"11 osob a viac"
	};
	std::string stringy_pocet_miestnosti[] = {
		"1 obytna miestnost",
		"2 obytne miestnosti",
		"3 obytne miestnosti",
		"4 obytne miestnosti",
		"5 obytnych miestnosti",
		"6 obytnych miestnosti",
		"7 obytnych miestnosti",
		"8 obytnych miestnosti",
		"9 obytnych miestnosti a viac",
		"Nezistene"
	};

}