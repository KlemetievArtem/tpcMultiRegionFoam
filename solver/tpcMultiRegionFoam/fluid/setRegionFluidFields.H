fvMesh& mesh = fluidRegions[i];
rhoThermo& thermo = thermoFluid[i];
IOdictionary& transportProperties = transportPropertiesFluid[i];
compressible::turbulenceModel& turbulence = turbulenceFluid[i];
//-----------------------------------------------
volVectorField& U = UFluid[i];
surfaceScalarField& phi = phiFluid[i];
surfaceScalarField& rhoPhi = rhoPhiFluid[i];
volScalarField& p_rgh = p_rghFluid[i];
volScalarField& p = thermo.p();


phaseChangeTwoPhaseMixtureCond& mixture = mixtureFluid[i];
volScalarField& alpha1(mixture.alpha1());
volScalarField& alpha2(mixture.alpha2());

interfaceProperties interface(alpha1, U, mixture);

const dimensionedScalar& rho1 = rho1Fluid[i];
const dimensionedScalar& rho2 = rho2Fluid[i];
volScalarField& rho = rhoFluid[i];
const dimensionedScalar& Cp1 = Cp1Fluid[i];
const dimensionedScalar& Cp2 = Cp2Fluid[i];
volScalarField& Cp = CpFluid[i];
const dimensionedScalar& DT1 = DT1Fluid[i];
const dimensionedScalar& DT2 = DT2Fluid[i];
volScalarField& DT = DTFluid[i];

dimensionedScalar& dhv = dhvFluid[i];
dimensionedScalar& Tsat = TsatFluid[i];
volScalarField& dhe = dheFluid[i];
volScalarField& q_pc = q_pcFluid[i];

const volScalarField& gh = ghFluid[i];
const surfaceScalarField& ghf = ghfFluid[i];

pimpleControl& pimple = pimpleFluid[i];
fv::options& fvOptions = fluidFvOptions[i];

p == p_rgh + rho*gh;
label pRefCell = 0;
scalar pRefValue = 0;
setRefCell
( 
  p,
  p_rgh,
  fluidRegions[i].solutionDict().subDict("PIMPLE"),
  pRefCell,
  pRefValue
);
if(p_rgh.needReference())
{
  p+=dimensionedScalar
  (
    "p",
    p.dimensions(),
    pRefValue-getRefCellValue(p,pRefCell)
  );
  p_rgh = p - rho * gh;
}

const int Qcycles = QcyclesFluid[i];
const scalar Qrelax = QrelaxFluid[i];
const int dV = dVFluid[i];
const scalar QResidual = QResidualFluid[i];