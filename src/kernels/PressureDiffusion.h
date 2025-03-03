#pragma once

#include "TimeDerivative.h"  // Use TimeDerivative instead of ADTimeKernel

class PressureDiffusion : public TimeDerivative  // Inherit from TimeDerivative
{
public:
  static InputParameters validParams();
  PressureDiffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;  // Use TimeDerivative's computeQpResidual

private:
  const Real _permeability;
  const Real _viscosity;
  const Real _porosity;
  const Real _compressibility;
};