#include "CapybaraApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
CapybaraApp::validParams()
{
  InputParameters params = MooseApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  params.set<bool>("use_legacy_initial_residual_evaluation_behavior") = false;
  return params;
}

CapybaraApp::CapybaraApp(InputParameters parameters) : MooseApp(parameters)
{
  CapybaraApp::registerAll(_factory, _action_factory, _syntax);
}

CapybaraApp::~CapybaraApp() {}

void
CapybaraApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  ModulesApp::registerAllObjects<CapybaraApp>(f, af, syntax);
  Registry::registerObjectsTo(f, {"CapybaraApp"});
  Registry::registerActionsTo(af, {"CapybaraApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
CapybaraApp::registerApps()
{
  registerApp(CapybaraApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
CapybaraApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  CapybaraApp::registerAll(f, af, s);
}
extern "C" void
CapybaraApp__registerApps()
{
  CapybaraApp::registerApps();
}
