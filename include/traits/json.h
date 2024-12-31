#pragma once

namespace futsim
{

//! Macro to instantiate a template trait for every value of an enum.
#define FUTSIM_INSTANTIATE_ENUM_TRAIT(name, id, class, member, enum, suffix, ... ) \
template <> inline constexpr std::string_view json_traits<class>::member<enum::name> = id suffix;

//! JSON traits for any class.
template <typename T> struct json_traits
{
};

} // futsim namespace
