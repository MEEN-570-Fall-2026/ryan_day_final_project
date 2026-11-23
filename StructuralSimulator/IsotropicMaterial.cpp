#include "IsotropicMaterial.hpp"
#include "UnassignedMaterialException.hpp"

void IsotropicMaterial::set_poissons_ratio(double value)
{
    poissonsRatio = value;
}

void IsotropicMaterial::set_modulus_of_elasticity(double value)
{
    modulusOfElasticity = value;
}

double IsotropicMaterial::get_poissons_ratio()
{
    if (!poissonsRatio.has_value()) {
        throw UnassignedMaterialException("Material is missing Poisson's Ratio!");
    }
    return *poissonsRatio;
}

double IsotropicMaterial::get_modulus_of_elasticity()
{
    if (!modulusOfElasticity.has_value()) {
        throw UnassignedMaterialException("Material is missing Modulus of Elasticity!");
    }
    return *modulusOfElasticity;
}
