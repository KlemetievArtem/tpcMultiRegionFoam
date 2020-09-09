//std::cout.setstate(std::ios_base::failbit);   //turn off calculation output for iteration cycles
scalar Linear = (1-Qrelax)/Qcycles;   //get portion of linear relaxation factor increase
const volScalarField alpha1Lim( max(min(alpha1, scalar(1)), scalar(0)) ); //limit alpha1 to 0 < alpha1 < 1:

volScalarField mdot = q_pc /(dhv * rho1)*runTime.deltaT();
dimensionedScalar mdot_res=1;
dimensionedScalar mdot_meanRes=1;

bool TLoop=true;

  Info << nl <<">>>>>Enthalpy equation (T)" << endl;
     Info <<"-------Energy Loop Iteration 1----------" << "Qrelax: " << Qrelax << "-----" << endl;
while (TLoop)
{
  if(i==1)
  {
    std::cout.setstate(std::ios_base::failbit); //turn off calculation output for iteration cycles
  }
  if(mdot_res.value() < QResidual || i==Qcycles)
  {
    TLoop=false;
    std::cout.clear();//turn on calculation output for iteration cycles

    Info <<"-------Energy Loop Iteration " << i <<" -----" << endl;
//      Info << nl <<"-------pos(0)= " << pos(0) << "-----" << "neg(0)= " << neg(0) << "-----" << endl;
  }
  
  #include "EEqn.H"
  
  volScalarField mdotNew = q_pc /(dhv * rho1)*runTime.deltaT();
  mdot_res = gMax(mag(mdotNew.internalField()-mdot.internalField())()); // added residuum control according to the work of Faden et al. 2017
  mdot_meanRes = gSum(mag(mdotNew-mdot)*mesh.V())/gSum(mesh.V());
  
  mdot = mdotNew;
  i+=1;
}
Info<< "delta m residual: " << mdot_res.value() << " delta m mean residual: "
    << mdot_meanRes.value() << endl;

p == p_rgh + rho*gh;
