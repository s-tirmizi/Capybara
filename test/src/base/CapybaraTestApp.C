//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "CapybaraTestApp.h"
#include "CapybaraApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"

InputParameters
CapybaraTestApp::validParams()
{
  InputParameters params = CapybaraApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  params.set<bool>("use_legacy_initial_residual_evaluation_behavior") = false;
  return params;
}

CapybaraTestApp::CapybaraTestApp(InputParameters parameters) : MooseApp(parameters)
{
  CapybaraTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

CapybaraTestApp::~CapybaraTestApp() {}

void
CapybaraTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  CapybaraApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"CapybaraTestApp"});
    Registry::registerActionsTo(af, {"CapybaraTestApp"});
  }
}

void
CapybaraTestApp::registerApps()
{
  registerApp(CapybaraApp);
  registerApp(CapybaraTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
CapybaraTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  CapybaraTestApp::registerAll(f, af, s);
}
extern "C" void
CapybaraTestApp__registerApps()
{
  CapybaraTestApp::registerApps();
}
