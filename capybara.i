[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 5
  ny = 5
[]

[Variables]
  [./p]
    initial_condition = 0          # Small positive initial condition
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./diffusion]
    type = PressureDiffusion
    variable = p

    # Parameters for the pressure equation
    permeability = 0.2451e-14     # m^2
    viscosity = 7.98e-04          # Pa.s
    porosity = 0.2                # Fraction
    compressibility = 1.0e-9      # 1/Pa
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = p
    boundary = left
    value = 100.0
  [../]
  
  [./right]
    type = DirichletBC
    variable = p
    boundary = right
    value = 0.0
  [../]
[]

[Materials]
  [./material]
    type = GenericConstantMaterial
    prop_names = 'permeability viscosity porosity compressibility'
    prop_values = '0.2451e-14 7.98e-04 0.2 1.0e-9'
  [../]
[]

[Executioner]
  type = Transient
  solve_type = 'PJFNK'
  dt = 1                # Reduced time step for stability
  num_steps = 100
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  # Solver settings
  #line_search = basic     # Enable line search for PJFNK
  #l_max_its = 200         # Max linear iterations
  #nl_max_its = 40         # Max nonlinear iterations
  #nl_rel_tol = 1e-6       # Relaxed tolerance for faster convergence
  nl_abs_tol = 1e-18
  #l_tol = 1e-1
[]

[Preconditioning]
  [./pc]
    type = SMP
    full = true
  [../]
[]

[Outputs]
  exodus = true
  csv = true
[]
