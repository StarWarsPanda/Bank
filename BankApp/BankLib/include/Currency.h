#pragma once

#include <cstdint>
#include <ostream>

#include <nlohmann/json.hpp>

class Currency
{
    public:
        Currency();
        Currency(int64_t dollars, int64_t cents = 0);
        Currency(double amount);

        static Currency FromCents(int64_t cents);

        int8_t Cents() const;
        int64_t Dollars() const;
        double ToDouble() const;

        Currency operator+(const Currency& other) const;
        Currency operator-(const Currency& other) const;
        Currency operator+(const double& other) const;
        Currency operator-(const double& other) const;

        Currency& operator+=(const Currency& other);
        Currency& operator-=(const Currency& other);
        Currency& operator+=(const double& other);
        Currency& operator-=(const double& other);

        bool operator==(const Currency& other) const;
        bool operator!=(const Currency& other) const;
        bool operator<(const Currency& other) const;
        bool operator>(const Currency& other) const;
        bool operator<=(const Currency& other) const;
        bool operator>=(const Currency& other) const;

        bool operator==(const double& other) const;
        bool operator!=(const double& other) const;
        bool operator<(const double& other) const;
        bool operator>(const double& other) const;
        bool operator<=(const double& other) const;
        bool operator>=(const double& other) const;

        friend std::ostream& operator<<(std::ostream& stream, const Currency& currency);

    private:
        int64_t m_cents = 0;
};