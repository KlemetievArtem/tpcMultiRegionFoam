   volScalarField& T_ = thermo.T();
   volScalarField q_pc_old = q_pc ;

	
	scalar Relax = (1-Qrelax)/Qcycles;
	
	volScalarField rhoCp = rho * Cp;
	surfaceScalarField rhoCpPhi = rhoPhi * fvc::interpolate(Cp);
    
	fvScalarMatrix EEqn
    (
       fvm::ddt(rhoCp,T_) + fvm::div(rhoCpPhi, T_)
      - fvm::Sp(fvc::ddt(rhoCp)+fvc::div(rhoCpPhi), T_)
      - fvm::laplacian(DT, T_) 
	 ==
      - q_pc
    );

    EEqn.relax();

    EEqn.solve(mesh.solver(T_.select(finalIter)));

	q_pc = q_pc + (Qrelax + i * Relax) * rho * Cp *((T_ - Tsat) / runTime.deltaT());
	q_pc = q_pc * neg(q_pc) * (1 - alpha1Lim) * pos(Tsat - T_) + q_pc * pos(q_pc) * alpha1Lim * neg(Tsat - T_);
        q_pc = max(q_pc, - (1-alpha1Lim) * dhv * rho1 / runTime.deltaT()) * neg(q_pc) * pos(Tsat - T_) + min(q_pc, alpha1Lim * dhv * rho2 / runTime.deltaT()) * pos(q_pc) * neg(Tsat - T_);//additionally added line inspired from https://github.com/MahdiNabil/CFD-PC


	dhe = q_pc;
  T_.correctBoundaryConditions();

   Info<< "Min/max T: " << min(thermo.T()).value() << ' '
       << max(thermo.T()).value() << endl;
