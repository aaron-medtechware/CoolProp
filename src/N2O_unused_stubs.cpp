// Stubs for CoolProp features not required for NitrousOxide PropsSI("T","P",p,"Q",0).
#include "Backends/Helmholtz/PhaseEnvelopeRoutines.h"
#include "CoolProp/expression/ExpressionBlock.h"
#include "CoolProp/expression/ExpressionCorrelation.h"
#include "CoolProp/fluids/MeltingCaloric.h"
#include "CoolProp/Exceptions.h"
#include "CoolProp/detail/strings.h"
#include <functional>

namespace CoolProp {

void PhaseEnvelopeRoutines::build(HelmholtzEOSMixtureBackend& /*HEOS*/, const std::string& /*level*/) {
    throw NotImplementedError("PhaseEnvelopeRoutines disabled in N2O-only embedded build");
}
void PhaseEnvelopeRoutines::refine(HelmholtzEOSMixtureBackend& /*HEOS*/, const std::string& /*level*/) {
    throw NotImplementedError("PhaseEnvelopeRoutines disabled in N2O-only embedded build");
}
void PhaseEnvelopeRoutines::finalize(HelmholtzEOSMixtureBackend& /*HEOS*/) {
    throw NotImplementedError("PhaseEnvelopeRoutines disabled in N2O-only embedded build");
}
std::vector<std::pair<std::size_t, std::size_t>> PhaseEnvelopeRoutines::find_intersections(const PhaseEnvelopeData& /*env*/, parameters /*iInput*/,
                                                                                            double /*value*/) {
    return {};
}
bool PhaseEnvelopeRoutines::is_inside(const PhaseEnvelopeData& /*env*/, parameters /*iInput1*/, CoolPropDbl /*value1*/, parameters /*iInput2*/,
                                      CoolPropDbl /*value2*/, std::size_t& /*iclosest*/, SimpleState& /*closest_state*/) {
    return false;
}
double PhaseEnvelopeRoutines::evaluate(const PhaseEnvelopeData& /*env*/, parameters /*output*/, parameters /*iInput1*/, double /*value1*/,
                                       std::size_t& /*i*/) {
    throw NotImplementedError("PhaseEnvelopeRoutines disabled in N2O-only embedded build");
}

std::shared_ptr<MeltingCaloric> get_melting_caloric_cached(HelmholtzEOSMixtureBackend& /*H*/) {
    return nullptr;
}

bool MeltingCaloric::seed_for_hs(double /*s_cache*/, double /*h_cache*/, double& /*T0*/, double& /*rho0*/) const {
    return false;
}

namespace expression {

Program compile_block(const std::string& /*json_text*/, const std::string& /*context*/) {
    throw ValueError("expression language disabled in N2O-only embedded build");
}

double ExpressionCorrelation::eval(HelmholtzEOSMixtureBackend& /*HEOS*/) const {
    throw ValueError("expression language disabled in N2O-only embedded build");
}

}  // namespace expression

namespace superancillary {
namespace detail {
// Provided so any residual Chebyshev template instantiation can link; unused at runtime
// because the N2O payload has no SUPERANCILLARY tables.
double toms748(const std::function<double(double)>& /*f*/, double /*a*/, double /*b*/, double /*fa*/, double /*fb*/, unsigned int /*bits*/,
               std::size_t /*max_iter*/) {
    throw CoolProp::NotImplementedError("superancillary solvers disabled in N2O-only embedded build");
}
}  // namespace detail
}  // namespace superancillary
}  // namespace CoolProp
