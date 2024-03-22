#pragma once

#include <nlohmann/json_fwd.hpp>

/**
 * @brief Types defined for \ref IJsonable.
*/
namespace futsim::types::IJsonable
{

//! Type for the json object.
using json = nlohmann::ordered_json;

} // futsim::football::types::CPlayerSkills namespace