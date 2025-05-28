#pragma once

#include <variant>

namespace futsim
{

//! Evaluates if a given type is one of the types in a pack.
template <typename T, typename U> struct has_type : std::false_type {};

//! Specialization for variants.
template <typename T, typename... Us> struct has_type<T, std::variant<Us...>> : std::disjunction<std::is_same<T, Us>...> {};
//! Associated concept.
template <typename T, typename Variant> concept has_type_c = has_type<T, Variant>::value;

} // futsim namespace
