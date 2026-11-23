#ifndef ISOTROPICMATERIAL
#define ISOTROPICMATERIAL

#include <optional>

class IsotropicMaterial {
    public:
        IsotropicMaterial() = default;
        
        void set_poissons_ratio(double value);
        void set_modulus_of_elasticity(double value);
        
        double get_poissons_ratio();
        double get_modulus_of_elasticity();


    private:
        std::optional<double> poissonsRatio = std::nullopt;
        std::optional<double> modulusOfElasticity = std::nullopt;


};


#endif