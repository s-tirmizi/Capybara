#include "PressureDiffusion.h"

registerMooseObject("CapybaraApp", PressureDiffusion);

InputParameters
PressureDiffusion::validParams()
{
  InputParameters params = TimeDerivative::validParams();  
  params.addClassDescription("Compute the weak form for the diffusion and time-dependent terms of the diffusivity equation: "
                             "\\( \\left\\langle \\frac{k}{\\mu} \\nabla p, \\nabla v \\right\\rangle + \\left\\langle \\phi c_t \\frac{\\partial p}{\\partial t}, v \\right\\rangle = 0 \\)");

  // Define permeability, viscosity, porosity, and total compressibility as input parameters
  params.addParam<Real>("permeability", 0.2451e-14, "Permeability (k) in m^2");
  params.addParam<Real>("viscosity", 7.98e-04, "Viscosity (mu) in Pa.s");
  params.addParam<Real>("porosity", 0.2, "Porosity (phi) as a fraction");
  params.addParam<Real>("compressibility", 1.0e-9, "Total compressibility (c_t) in 1/Pa");

  return params;
}

PressureDiffusion::PressureDiffusion(const InputParameters & parameters)
  : TimeDerivative(parameters),  
    _permeability(getParam<Real>("permeability")),
    _viscosity(getParam<Real>("viscosity")),
    _porosity(getParam<Real>("porosity")),
    _compressibility(getParam<Real>("compressibility"))
{
}

Real
PressureDiffusion::computeQpResidual()
{
  Real diffusion_residual = (_permeability / _viscosity) * _grad_u[_qp] * _grad_test[_i][_qp];

  Real accumulation_residual = _test[_i][_qp] * _porosity * _compressibility * _u_dot[_qp];

  return diffusion_residual + accumulation_residual;
}
