#pragma once

template <typename T>
class UniverzalnyFilter
{
protected:
	bool prislusnost;
public:
	virtual bool splnaFilter(T prvok, bool prislusnost = false) = 0;
	bool Prislusnost()
	{
		return prislusnost;
	}
	void setPrislusnot(bool f)
	{
		prislusnost = f;
	}
};

