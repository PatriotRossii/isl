module;

export module cstddef;

import type_traits;

// isl::{byte, to_integer, bitwise operators}

export namespace isl {
	enum class byte: unsigned char { };

	template<class IntegerType>
	constexpr IntegerType to_integer(byte b) noexcept requires(
		isl::is_integral_v<IntegerType>
	) {
		return static_cast<IntegerType>(b);
	}

	template<class IntegerType>
	constexpr byte& operator<<=(byte& b, IntegerType shift) noexcept requires(
		isl::is_integral_v<IntegerType>
	) {
		return b = b << shift;
	}
    template<class IntegerType>
    constexpr byte& operator>>=(byte& b, IntegerType shift) noexcept requires(
        isl::is_integral_v<IntegerType>
    ) {
        return b = b >> shift;
    }

    template<class IntegerType>
    constexpr byte operator<<(byte b, IntegerType shift) noexcept requires(
        isl::is_integral_v<IntegerType>
    ) {
        return byte(static_cast<unsigned char>(b) << shift);
    }
	template<class IntegerType>
    constexpr byte operator>>(byte b, IntegerType shift) noexcept requires(
        isl::is_integral_v<IntegerType>
    ) {
        return byte(static_cast<unsigned char>(b) >> shift);
    }

	template<class IntegerType>
    constexpr byte& operator|=(byte& l, byte& r) noexcept {
        return l = l | r;
    }
    template<class IntegerType>
    constexpr byte& operator&=(byte& l, byte& r) noexcept {
        return l = l & r;
    }
    template<class IntegerType>
    constexpr byte& operator^=(byte& l, byte& r) noexcept {
        return l = l ^ r;
    }

    template<class IntegerType>
    constexpr byte operator|(byte l, byte r) noexcept {
        return byte(static_cast<unsigned char>(l) | static_cast<unsigned char>(r));
    }
    template<class IntegerType>
    constexpr byte operator&(byte l, byte r) noexcept {
        return byte(static_cast<unsigned char>(l) & static_cast<unsigned char>(r));
	}
    template<class IntegerType>
    constexpr byte operator^(byte l, byte r) noexcept {
        return byte(static_cast<unsigned char>(l) ^ static_cast<unsigned char>(r));
	}
    template<class IntegerType>
    constexpr byte operator~(byte l) noexcept {
        return byte(~static_cast<unsigned char>(l));
	}
}
