// N2O-only embedded build: stub out mixture BIP / departure / predefined-mixture
// libraries. Pure-fluid HEOS only needs an empty Excess term and a
// GERG2008ReducingFunction over a single component.

#include "MixtureParameters.h"
#include "ReducingFunctions.h"
#include "ExcessHEFunction.h"
#include "CoolProp/detail/strings.h"

namespace CoolProp {

std::string get_csv_mixture_binary_pairs() {
    return "";
}

std::string get_csv_predefined_mixtures() {
    return "";
}

bool is_predefined_mixture(const std::string& /*name*/, Dictionary& /*dict*/) {
    return false;
}

void set_predefined_mixtures(const std::string& /*string_data*/) {}

std::string get_mixture_binary_pair_data(const std::string& /*CAS1*/, const std::string& /*CAS2*/, const std::string& /*param*/) {
    throw ValueError("Mixture binary pairs disabled in N2O-only embedded build");
}

void set_mixture_binary_pair_data(const std::string& /*CAS1*/, const std::string& /*CAS2*/, const std::string& /*param*/, const double /*val*/) {
    throw ValueError("Mixture binary pairs disabled in N2O-only embedded build");
}

void apply_simple_mixing_rule(const std::string& /*identifier1*/, const std::string& /*identifier2*/, const std::string& /*rule*/) {
    throw ValueError("Mixing rules disabled in N2O-only embedded build");
}

DepartureFunction* get_departure_function(const std::string& /*Name*/) {
    throw ValueError("Departure functions disabled in N2O-only embedded build");
}

void set_departure_functions(const std::string& /*string_data*/) {}

void set_interaction_parameters(const std::string& /*string_data*/) {}

void MixtureParameters::set_mixture_parameters(HelmholtzEOSMixtureBackend& HEOS) {
    std::vector<CoolPropFluid> components = HEOS.get_components();
    const std::size_t N = components.size();
    if (N != 1) {
        throw ValueError("N2O-only embedded build supports pure fluids only");
    }

    STLMatrix beta_v(N, std::vector<CoolPropDbl>(N, 0));
    STLMatrix gamma_v(N, std::vector<CoolPropDbl>(N, 0));
    STLMatrix beta_T(N, std::vector<CoolPropDbl>(N, 0));
    STLMatrix gamma_T(N, std::vector<CoolPropDbl>(N, 0));

    HEOS.residual_helmholtz->Excess.resize(N);
    HEOS.Reducing = std::make_shared<GERG2008ReducingFunction>(components, beta_v, gamma_v, beta_T, gamma_T);
}

} /* namespace CoolProp */
