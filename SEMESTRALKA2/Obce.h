#pragma once
#include <iostream>

struct Obce {
	std::string nazov;
	int preProObyv;
	int proObyv;
	int poProObyv;
	long vymera;
	long zastavPlocha;
	std::string okres;
	std::string kraj;

	bool operator==(Obce o) {
		return (preProObyv == o.poProObyv && proObyv == o.poProObyv && poProObyv == o.poProObyv && vymera == o.vymera
			&& zastavPlocha == o.zastavPlocha && okres == o.okres && kraj == o.kraj);
	}
};

std::ostream& operator<<(std::ostream& os, const Obce& o) {
	os << o.nazov << " " << o.preProObyv << " " << o.proObyv << " " << o.poProObyv<< " "  << o.vymera 
		<< " " << o.zastavPlocha << " " << o.okres << " " << o.kraj << " " << std::endl;
	return os;
}