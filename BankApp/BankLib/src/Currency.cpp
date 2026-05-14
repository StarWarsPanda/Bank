#include "../include/Currency.h"

Currency::Currency() {}

Currency::Currency(int64_t dollars, int64_t cents)
{
	m_cents = dollars * 100 + cents;
}

Currency::Currency(double amount)
{
	m_cents = amount * 100.0;
}

Currency Currency::FromCents(int64_t cents)
{
	return Currency(0, cents);
}

int8_t Currency::Cents() const
{
	return m_cents % 100;
}

int64_t Currency::Dollars() const
{
	return m_cents / 100;
}

double Currency::ToDouble() const
{
	return Dollars() + Cents() * 0.01;
}

Currency Currency::operator+(const Currency& other) const
{
	return Currency(m_cents + other.m_cents);
}

Currency Currency::operator-(const Currency& other) const
{
	return Currency(m_cents - other.m_cents);
}

Currency Currency::operator+(const double& other) const
{
	return Currency(ToDouble() + other);
}

Currency Currency::operator-(const double& other) const
{
	return Currency(ToDouble() - other);
}

Currency& Currency::operator+=(const Currency& other)
{
	this->m_cents = this->m_cents + other.m_cents;
	return *this;
}

Currency& Currency::operator-=(const Currency& other)
{
	this->m_cents = this->m_cents - other.m_cents;
	return *this;
}

Currency& Currency::operator+=(const double& other)
{
	*this = Currency(this->ToDouble() + other);
	return *this;
}

Currency& Currency::operator-=(const double& other)
{
	*this = Currency(this->ToDouble() - other);
	return *this;
}

bool Currency::operator==(const Currency& other) const
{
	return m_cents == other.m_cents;
}

bool Currency::operator!=(const Currency& other) const
{
	return m_cents != other.m_cents;
}

bool Currency::operator<(const Currency& other) const
{
	return m_cents < other.m_cents;
}

bool Currency::operator>(const Currency& other) const
{
	return m_cents > other.m_cents;
}

bool Currency::operator<=(const Currency& other) const
{
	return m_cents <= other.m_cents;
}

bool Currency::operator>=(const Currency& other) const
{
	return m_cents >= other.m_cents;
}

bool Currency::operator==(const double& other) const
{
	return ToDouble() == other;
}

bool Currency::operator!=(const double& other) const
{
	return ToDouble() != other;
}

bool Currency::operator<(const double& other) const
{
	return ToDouble() < other;
}

bool Currency::operator>(const double& other) const
{
	return ToDouble() > other;
}

bool Currency::operator<=(const double& other) const
{
	return ToDouble() <= other;
}

bool Currency::operator>=(const double& other) const
{
	return ToDouble() >= other;
}

std::ostream& operator<<(std::ostream& stream, const Currency& currency)
{
	stream << currency.Dollars() << "." << currency.Cents();
	return stream;
}
