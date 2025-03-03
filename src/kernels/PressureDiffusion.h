#pragma once

#include "TimeDerivative.h"  

class PressureDiffusion : public TimeDerivative  
{
public:
  static InputParameters validParams();
  PressureDiffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;  

private:
  const Real _permeability;
  const Real _viscosity;
  const Real _porosity;
  const Real _compressibility;
};
