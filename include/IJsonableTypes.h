#pragma once

#include <nlohmann/json_fwd.hpp>

/**
 * @brief Types defined for \ref IJsonable.
*/
namespace futsim::IJsonableTypes
{

//! Type for the json object.
using json = nlohmann::ordered_json;

} // futsim::football::CPlayerSkillsTypes namespace